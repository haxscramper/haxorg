/* clang-format off */
#include <wrappers/c/haxorg_c.h>
#include <wrappers/c/haxorg_c_vtables.hpp>
#include <wrappers/c/haxorg_c_vtables_manual.hpp>
#include <wrappers/c/haxorg_c_utils.hpp>


































bool haxorg_SemIdOfOrg_isNil_const(OrgContext* org_context, haxorg_SemIdOfOrg __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SemId<org::sem::Org>::*)() const>(&org::sem::SemId<org::sem::Org>::isNil), org_context, __this); }

bool haxorg_SemIdOfOrg___eq___const(OrgContext* org_context, haxorg_SemIdOfOrg __this, haxorg_SemIdOfOrg other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SemId<org::sem::Org>::*)(org::sem::SemId<org::sem::Org> const&) const>(&org::sem::SemId<org::sem::Org>::operator==), org_context, __this, other); }

haxorg_SemIdOfOrg haxorg_SemIdOfOrg_Nil(OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org>(*)()>(&org::sem::SemId<org::sem::Org>::Nil), org_context); }

haxorg_Org haxorg_SemIdOfOrg_get(OrgContext* org_context, haxorg_SemIdOfOrg __this) { return org::bind::c::execute_cpp<haxorg_Org>(static_cast<org::sem::Org*(org::sem::SemId<org::sem::Org>::*)()>(&org::sem::SemId<org::sem::Org>::get), org_context, __this); }

haxorg_Org haxorg_SemIdOfOrg_get_const(OrgContext* org_context, haxorg_SemIdOfOrg __this) { return org::bind::c::execute_cpp<haxorg_Org>(static_cast<org::sem::Org const*(org::sem::SemId<org::sem::Org>::*)() const>(&org::sem::SemId<org::sem::Org>::get), org_context, __this); }

haxorg_SemIdOfOrg haxorg_SemIdOfOrg_asOrg_const(OrgContext* org_context, haxorg_SemIdOfOrg __this) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org>(org::sem::SemId<org::sem::Org>::*)() const>(&org::sem::SemId<org::sem::Org>::asOrg), org_context, __this); }

haxorg_OrgSemKind haxorg_SemIdOfOrg_getNodeKind_const(OrgContext* org_context, haxorg_SemIdOfOrg __this) { return org::bind::c::execute_cpp<haxorg_OrgSemKind>(static_cast<OrgSemKind(org::sem::SemId<org::sem::Org>::*)() const>(&org::sem::SemId<org::sem::Org>::getNodeKind), org_context, __this); }

haxorg_SemIdOfOrg haxorg_SemIdOfOrg_atIndex(OrgContext* org_context, haxorg_SemIdOfOrg __this, int idx) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org>(org::sem::SemId<org::sem::Org>::*)(int)>(&org::sem::SemId<org::sem::Org>::at), org_context, __this, idx); }

haxorg_SemIdOfOrg haxorg_SemIdOfOrg_atIndexBackwards(OrgContext* org_context, haxorg_SemIdOfOrg __this, haxorg_BackwardsIndex idx) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org>(org::sem::SemId<org::sem::Org>::*)(hstd::BackwardsIndex)>(&org::sem::SemId<org::sem::Org>::at), org_context, __this, idx); }

haxorg_StdOptional haxorg_SemIdOfOrg_getIndex(OrgContext* org_context, haxorg_SemIdOfOrg __this, int idx) { return org::bind::c::execute_cpp<haxorg_StdOptional>(static_cast<std::optional<org::sem::SemId<org::sem::Org>>(org::sem::SemId<org::sem::Org>::*)(int)>(&org::sem::SemId<org::sem::Org>::get), org_context, __this, idx); }

haxorg_StdOptional haxorg_SemIdOfOrg_getIndexBackwards(OrgContext* org_context, haxorg_SemIdOfOrg __this, haxorg_BackwardsIndex idx) { return org::bind::c::execute_cpp<haxorg_StdOptional>(static_cast<std::optional<org::sem::SemId<org::sem::Org>>(org::sem::SemId<org::sem::Org>::*)(hstd::BackwardsIndex)>(&org::sem::SemId<org::sem::Org>::get), org_context, __this, idx); }

int haxorg_SemIdOfOrg_size_const(OrgContext* org_context, haxorg_SemIdOfOrg __this) { return org::bind::c::execute_cpp<int>(static_cast<int(org::sem::SemId<org::sem::Org>::*)() const>(&org::sem::SemId<org::sem::Org>::size), org_context, __this); }

void haxorg_destroy_SemIdOfOrg(OrgContext* org_context, haxorg_SemIdOfOrg* obj) { org::bind::c::execute_destroy<org::sem::SemId<org::sem::Org>>(org_context, obj); }

int haxorg_HstdVecOfOrgJson_size_const(OrgContext* org_context, haxorg_HstdVecOfOrgJson __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::OrgJson>::*)() const>(&hstd::Vec<org::sem::OrgJson>::size), org_context, __this); }

haxorg_OrgJson haxorg_HstdVecOfOrgJson_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfOrgJson __this, int idx) { return org::bind::c::execute_cpp<haxorg_OrgJson>(static_cast<org::sem::OrgJson const&(hstd::Vec<org::sem::OrgJson>::*)(int) const>(&hstd::Vec<org::sem::OrgJson>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfOrgJson(OrgContext* org_context, haxorg_HstdVecOfOrgJson* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::OrgJson>>(org_context, obj); }

int haxorg_HstdVecOfSemIdOfOrg_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfOrg __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::Org>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::Org>>::size), org_context, __this); }

haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfOrg_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfOrg __this, int idx) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org> const&(hstd::Vec<org::sem::SemId<org::sem::Org>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::Org>>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSemIdOfOrg(OrgContext* org_context, haxorg_HstdVecOfSemIdOfOrg* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::SemId<org::sem::Org>>>(org_context, obj); }

int haxorg_HstdVecOfReport_size_const(OrgContext* org_context, haxorg_HstdVecOfReport __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<hstd::ext::Report>::*)() const>(&hstd::Vec<hstd::ext::Report>::size), org_context, __this); }

haxorg_Report haxorg_HstdVecOfReport_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfReport __this, int idx) { return org::bind::c::execute_cpp<haxorg_Report>(static_cast<hstd::ext::Report const&(hstd::Vec<hstd::ext::Report>::*)(int) const>(&hstd::Vec<hstd::ext::Report>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfReport(OrgContext* org_context, haxorg_HstdVecOfReport* obj) { org::bind::c::execute_destroy<hstd::Vec<hstd::ext::Report>>(org_context, obj); }

int haxorg_HstdVecOfSemIdOfErrorGroup_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorGroup __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>::size), org_context, __this); }

haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfErrorGroup_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorGroup __this, int idx) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::ErrorGroup> const&(hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSemIdOfErrorGroup(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorGroup* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>>(org_context, obj); }

int haxorg_HstdVecOfInt_size_const(OrgContext* org_context, haxorg_HstdVecOfInt __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<int>::*)() const>(&hstd::Vec<int>::size), org_context, __this); }

int const& haxorg_HstdVecOfInt_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfInt __this, int idx) { return org::bind::c::execute_cpp<int const&>(static_cast<int const&(hstd::Vec<int>::*)(int) const>(&hstd::Vec<int>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfInt(OrgContext* org_context, haxorg_HstdVecOfInt* obj) { org::bind::c::execute_destroy<hstd::Vec<int>>(org_context, obj); }

int haxorg_HstdVecOfImmAdapter_size_const(OrgContext* org_context, haxorg_HstdVecOfImmAdapter __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::imm::ImmAdapter>::*)() const>(&hstd::Vec<org::imm::ImmAdapter>::size), org_context, __this); }

haxorg_ImmAdapter haxorg_HstdVecOfImmAdapter_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfImmAdapter __this, int idx) { return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter const&(hstd::Vec<org::imm::ImmAdapter>::*)(int) const>(&hstd::Vec<org::imm::ImmAdapter>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfImmAdapter(OrgContext* org_context, haxorg_HstdVecOfImmAdapter* obj) { org::bind::c::execute_destroy<hstd::Vec<org::imm::ImmAdapter>>(org_context, obj); }

int haxorg_HstdVecOfSequenceSegment_size_const(OrgContext* org_context, haxorg_HstdVecOfSequenceSegment __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<hstd::SequenceSegment>::*)() const>(&hstd::Vec<hstd::SequenceSegment>::size), org_context, __this); }

haxorg_SequenceSegment haxorg_HstdVecOfSequenceSegment_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSequenceSegment __this, int idx) { return org::bind::c::execute_cpp<haxorg_SequenceSegment>(static_cast<hstd::SequenceSegment const&(hstd::Vec<hstd::SequenceSegment>::*)(int) const>(&hstd::Vec<hstd::SequenceSegment>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSequenceSegment(OrgContext* org_context, haxorg_HstdVecOfSequenceSegment* obj) { org::bind::c::execute_destroy<hstd::Vec<hstd::SequenceSegment>>(org_context, obj); }

int haxorg_HstdVecOfSequenceAnnotationTag_size_const(OrgContext* org_context, haxorg_HstdVecOfSequenceAnnotationTag __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<hstd::SequenceAnnotationTag>::*)() const>(&hstd::Vec<hstd::SequenceAnnotationTag>::size), org_context, __this); }

haxorg_SequenceAnnotationTag haxorg_HstdVecOfSequenceAnnotationTag_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSequenceAnnotationTag __this, int idx) { return org::bind::c::execute_cpp<haxorg_SequenceAnnotationTag>(static_cast<hstd::SequenceAnnotationTag const&(hstd::Vec<hstd::SequenceAnnotationTag>::*)(int) const>(&hstd::Vec<hstd::SequenceAnnotationTag>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSequenceAnnotationTag(OrgContext* org_context, haxorg_HstdVecOfSequenceAnnotationTag* obj) { org::bind::c::execute_destroy<hstd::Vec<hstd::SequenceAnnotationTag>>(org_context, obj); }

int haxorg_HstdVecOfImmUniqId_size_const(OrgContext* org_context, haxorg_HstdVecOfImmUniqId __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::imm::ImmUniqId>::*)() const>(&hstd::Vec<org::imm::ImmUniqId>::size), org_context, __this); }

haxorg_ImmUniqId haxorg_HstdVecOfImmUniqId_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfImmUniqId __this, int idx) { return org::bind::c::execute_cpp<haxorg_ImmUniqId>(static_cast<org::imm::ImmUniqId const&(hstd::Vec<org::imm::ImmUniqId>::*)(int) const>(&hstd::Vec<org::imm::ImmUniqId>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfImmUniqId(OrgContext* org_context, haxorg_HstdVecOfImmUniqId* obj) { org::bind::c::execute_destroy<hstd::Vec<org::imm::ImmUniqId>>(org_context, obj); }

int haxorg_HstdVecOfGraphMapLink_size_const(OrgContext* org_context, haxorg_HstdVecOfGraphMapLink __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::graph::MapLink>::*)() const>(&hstd::Vec<org::graph::MapLink>::size), org_context, __this); }

haxorg_GraphMapLink haxorg_HstdVecOfGraphMapLink_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfGraphMapLink __this, int idx) { return org::bind::c::execute_cpp<haxorg_GraphMapLink>(static_cast<org::graph::MapLink const&(hstd::Vec<org::graph::MapLink>::*)(int) const>(&hstd::Vec<org::graph::MapLink>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfGraphMapLink(OrgContext* org_context, haxorg_HstdVecOfGraphMapLink* obj) { org::bind::c::execute_destroy<hstd::Vec<org::graph::MapLink>>(org_context, obj); }

int haxorg_HstdVecOfGraphMapNode_size_const(OrgContext* org_context, haxorg_HstdVecOfGraphMapNode __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::graph::MapNode>::*)() const>(&hstd::Vec<org::graph::MapNode>::size), org_context, __this); }

haxorg_GraphMapNode haxorg_HstdVecOfGraphMapNode_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfGraphMapNode __this, int idx) { return org::bind::c::execute_cpp<haxorg_GraphMapNode>(static_cast<org::graph::MapNode const&(hstd::Vec<org::graph::MapNode>::*)(int) const>(&hstd::Vec<org::graph::MapNode>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfGraphMapNode(OrgContext* org_context, haxorg_HstdVecOfGraphMapNode* obj) { org::bind::c::execute_destroy<hstd::Vec<org::graph::MapNode>>(org_context, obj); }

int haxorg_HstdVecOfGraphMapEdge_size_const(OrgContext* org_context, haxorg_HstdVecOfGraphMapEdge __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::graph::MapEdge>::*)() const>(&hstd::Vec<org::graph::MapEdge>::size), org_context, __this); }

haxorg_GraphMapEdge haxorg_HstdVecOfGraphMapEdge_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfGraphMapEdge __this, int idx) { return org::bind::c::execute_cpp<haxorg_GraphMapEdge>(static_cast<org::graph::MapEdge const&(hstd::Vec<org::graph::MapEdge>::*)(int) const>(&hstd::Vec<org::graph::MapEdge>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfGraphMapEdge(OrgContext* org_context, haxorg_HstdVecOfGraphMapEdge* obj) { org::bind::c::execute_destroy<hstd::Vec<org::graph::MapEdge>>(org_context, obj); }

int haxorg_HstdVecOfLispCode_size_const(OrgContext* org_context, haxorg_HstdVecOfLispCode __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::LispCode>::*)() const>(&hstd::Vec<org::sem::LispCode>::size), org_context, __this); }

haxorg_LispCode haxorg_HstdVecOfLispCode_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfLispCode __this, int idx) { return org::bind::c::execute_cpp<haxorg_LispCode>(static_cast<org::sem::LispCode const&(hstd::Vec<org::sem::LispCode>::*)(int) const>(&hstd::Vec<org::sem::LispCode>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfLispCode(OrgContext* org_context, haxorg_HstdVecOfLispCode* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::LispCode>>(org_context, obj); }

int haxorg_HstdVecOfTblfmAssign_size_const(OrgContext* org_context, haxorg_HstdVecOfTblfmAssign __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::Tblfm::Assign>::*)() const>(&hstd::Vec<org::sem::Tblfm::Assign>::size), org_context, __this); }

haxorg_TblfmAssign haxorg_HstdVecOfTblfmAssign_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfTblfmAssign __this, int idx) { return org::bind::c::execute_cpp<haxorg_TblfmAssign>(static_cast<org::sem::Tblfm::Assign const&(hstd::Vec<org::sem::Tblfm::Assign>::*)(int) const>(&hstd::Vec<org::sem::Tblfm::Assign>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfTblfmAssign(OrgContext* org_context, haxorg_HstdVecOfTblfmAssign* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::Tblfm::Assign>>(org_context, obj); }

int haxorg_HstdVecOfTblfmExpr_size_const(OrgContext* org_context, haxorg_HstdVecOfTblfmExpr __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::Tblfm::Expr>::*)() const>(&hstd::Vec<org::sem::Tblfm::Expr>::size), org_context, __this); }

haxorg_TblfmExpr haxorg_HstdVecOfTblfmExpr_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfTblfmExpr __this, int idx) { return org::bind::c::execute_cpp<haxorg_TblfmExpr>(static_cast<org::sem::Tblfm::Expr const&(hstd::Vec<org::sem::Tblfm::Expr>::*)(int) const>(&hstd::Vec<org::sem::Tblfm::Expr>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfTblfmExpr(OrgContext* org_context, haxorg_HstdVecOfTblfmExpr* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::Tblfm::Expr>>(org_context, obj); }

int haxorg_HstdVecOfTblfmAssignFlag_size_const(OrgContext* org_context, haxorg_HstdVecOfTblfmAssignFlag __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::Tblfm::Assign::Flag>::*)() const>(&hstd::Vec<org::sem::Tblfm::Assign::Flag>::size), org_context, __this); }

haxorg_TblfmAssignFlag haxorg_HstdVecOfTblfmAssignFlag_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfTblfmAssignFlag __this, int idx) { return org::bind::c::execute_cpp<haxorg_TblfmAssignFlag>(static_cast<org::sem::Tblfm::Assign::Flag const&(hstd::Vec<org::sem::Tblfm::Assign::Flag>::*)(int) const>(&hstd::Vec<org::sem::Tblfm::Assign::Flag>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfTblfmAssignFlag(OrgContext* org_context, haxorg_HstdVecOfTblfmAssignFlag* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::Tblfm::Assign::Flag>>(org_context, obj); }

int haxorg_HstdVecOfAttrValueDimensionSpan_size_const(OrgContext* org_context, haxorg_HstdVecOfAttrValueDimensionSpan __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::AttrValue::DimensionSpan>::*)() const>(&hstd::Vec<org::sem::AttrValue::DimensionSpan>::size), org_context, __this); }

haxorg_AttrValueDimensionSpan haxorg_HstdVecOfAttrValueDimensionSpan_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfAttrValueDimensionSpan __this, int idx) { return org::bind::c::execute_cpp<haxorg_AttrValueDimensionSpan>(static_cast<org::sem::AttrValue::DimensionSpan const&(hstd::Vec<org::sem::AttrValue::DimensionSpan>::*)(int) const>(&hstd::Vec<org::sem::AttrValue::DimensionSpan>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfAttrValueDimensionSpan(OrgContext* org_context, haxorg_HstdVecOfAttrValueDimensionSpan* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::AttrValue::DimensionSpan>>(org_context, obj); }

int haxorg_HstdVecOfStr_size_const(OrgContext* org_context, haxorg_HstdVecOfStr __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<hstd::Str>::*)() const>(&hstd::Vec<hstd::Str>::size), org_context, __this); }

haxorg_HstdStr haxorg_HstdVecOfStr_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfStr __this, int idx) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(hstd::Vec<hstd::Str>::*)(int) const>(&hstd::Vec<hstd::Str>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfStr(OrgContext* org_context, haxorg_HstdVecOfStr* obj) { org::bind::c::execute_destroy<hstd::Vec<hstd::Str>>(org_context, obj); }

int haxorg_HstdVecOfHashTagFlat_size_const(OrgContext* org_context, haxorg_HstdVecOfHashTagFlat __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::HashTagFlat>::*)() const>(&hstd::Vec<org::sem::HashTagFlat>::size), org_context, __this); }

haxorg_HashTagFlat haxorg_HstdVecOfHashTagFlat_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfHashTagFlat __this, int idx) { return org::bind::c::execute_cpp<haxorg_HashTagFlat>(static_cast<org::sem::HashTagFlat const&(hstd::Vec<org::sem::HashTagFlat>::*)(int) const>(&hstd::Vec<org::sem::HashTagFlat>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfHashTagFlat(OrgContext* org_context, haxorg_HstdVecOfHashTagFlat* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::HashTagFlat>>(org_context, obj); }

int haxorg_HstdVecOfHashTagText_size_const(OrgContext* org_context, haxorg_HstdVecOfHashTagText __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::HashTagText>::*)() const>(&hstd::Vec<org::sem::HashTagText>::size), org_context, __this); }

haxorg_HashTagText haxorg_HstdVecOfHashTagText_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfHashTagText __this, int idx) { return org::bind::c::execute_cpp<haxorg_HashTagText>(static_cast<org::sem::HashTagText const&(hstd::Vec<org::sem::HashTagText>::*)(int) const>(&hstd::Vec<org::sem::HashTagText>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfHashTagText(OrgContext* org_context, haxorg_HstdVecOfHashTagText* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::HashTagText>>(org_context, obj); }

int haxorg_HstdVecOfAttrValue_size_const(OrgContext* org_context, haxorg_HstdVecOfAttrValue __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::AttrValue>::*)() const>(&hstd::Vec<org::sem::AttrValue>::size), org_context, __this); }

haxorg_AttrValue haxorg_HstdVecOfAttrValue_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfAttrValue __this, int idx) { return org::bind::c::execute_cpp<haxorg_AttrValue>(static_cast<org::sem::AttrValue const&(hstd::Vec<org::sem::AttrValue>::*)(int) const>(&hstd::Vec<org::sem::AttrValue>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfAttrValue(OrgContext* org_context, haxorg_HstdVecOfAttrValue* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::AttrValue>>(org_context, obj); }

int haxorg_HstdVecOfOrgCodeEvalInputVar_size_const(OrgContext* org_context, haxorg_HstdVecOfOrgCodeEvalInputVar __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::OrgCodeEvalInput::Var>::*)() const>(&hstd::Vec<org::sem::OrgCodeEvalInput::Var>::size), org_context, __this); }

haxorg_OrgCodeEvalInputVar haxorg_HstdVecOfOrgCodeEvalInputVar_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfOrgCodeEvalInputVar __this, int idx) { return org::bind::c::execute_cpp<haxorg_OrgCodeEvalInputVar>(static_cast<org::sem::OrgCodeEvalInput::Var const&(hstd::Vec<org::sem::OrgCodeEvalInput::Var>::*)(int) const>(&hstd::Vec<org::sem::OrgCodeEvalInput::Var>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfOrgCodeEvalInputVar(OrgContext* org_context, haxorg_HstdVecOfOrgCodeEvalInputVar* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::OrgCodeEvalInput::Var>>(org_context, obj); }

int haxorg_HstdVecOfColumnViewColumn_size_const(OrgContext* org_context, haxorg_HstdVecOfColumnViewColumn __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::ColumnView::Column>::*)() const>(&hstd::Vec<org::sem::ColumnView::Column>::size), org_context, __this); }

haxorg_ColumnViewColumn haxorg_HstdVecOfColumnViewColumn_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfColumnViewColumn __this, int idx) { return org::bind::c::execute_cpp<haxorg_ColumnViewColumn>(static_cast<org::sem::ColumnView::Column const&(hstd::Vec<org::sem::ColumnView::Column>::*)(int) const>(&hstd::Vec<org::sem::ColumnView::Column>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfColumnViewColumn(OrgContext* org_context, haxorg_HstdVecOfColumnViewColumn* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::ColumnView::Column>>(org_context, obj); }

int haxorg_HstdVecOfBlockCodeLinePart_size_const(OrgContext* org_context, haxorg_HstdVecOfBlockCodeLinePart __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::BlockCodeLine::Part>::*)() const>(&hstd::Vec<org::sem::BlockCodeLine::Part>::size), org_context, __this); }

haxorg_BlockCodeLinePart haxorg_HstdVecOfBlockCodeLinePart_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfBlockCodeLinePart __this, int idx) { return org::bind::c::execute_cpp<haxorg_BlockCodeLinePart>(static_cast<org::sem::BlockCodeLine::Part const&(hstd::Vec<org::sem::BlockCodeLine::Part>::*)(int) const>(&hstd::Vec<org::sem::BlockCodeLine::Part>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfBlockCodeLinePart(OrgContext* org_context, haxorg_HstdVecOfBlockCodeLinePart* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::BlockCodeLine::Part>>(org_context, obj); }

int haxorg_HstdVecOfSemIdOfErrorItem_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorItem __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>::size), org_context, __this); }

haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfErrorItem_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorItem __this, int idx) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::ErrorItem> const&(hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSemIdOfErrorItem(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorItem* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>>(org_context, obj); }

int haxorg_HstdVecOfTimeRepeat_size_const(OrgContext* org_context, haxorg_HstdVecOfTimeRepeat __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::Time::Repeat>::*)() const>(&hstd::Vec<org::sem::Time::Repeat>::size), org_context, __this); }

haxorg_TimeRepeat haxorg_HstdVecOfTimeRepeat_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfTimeRepeat __this, int idx) { return org::bind::c::execute_cpp<haxorg_TimeRepeat>(static_cast<org::sem::Time::Repeat const&(hstd::Vec<org::sem::Time::Repeat>::*)(int) const>(&hstd::Vec<org::sem::Time::Repeat>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfTimeRepeat(OrgContext* org_context, haxorg_HstdVecOfTimeRepeat* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::Time::Repeat>>(org_context, obj); }

int haxorg_HstdVecOfSymbolParam_size_const(OrgContext* org_context, haxorg_HstdVecOfSymbolParam __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::Symbol::Param>::*)() const>(&hstd::Vec<org::sem::Symbol::Param>::size), org_context, __this); }

haxorg_SymbolParam haxorg_HstdVecOfSymbolParam_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSymbolParam __this, int idx) { return org::bind::c::execute_cpp<haxorg_SymbolParam>(static_cast<org::sem::Symbol::Param const&(hstd::Vec<org::sem::Symbol::Param>::*)(int) const>(&hstd::Vec<org::sem::Symbol::Param>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSymbolParam(OrgContext* org_context, haxorg_HstdVecOfSymbolParam* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::Symbol::Param>>(org_context, obj); }

int haxorg_HstdVecOfSemIdOfErrorSkipToken_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorSkipToken __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>::size), org_context, __this); }

haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfErrorSkipToken_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorSkipToken __this, int idx) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::ErrorSkipToken> const&(hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSemIdOfErrorSkipToken(OrgContext* org_context, haxorg_HstdVecOfSemIdOfErrorSkipToken* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>>(org_context, obj); }

int haxorg_HstdVecOfSubtreePeriod_size_const(OrgContext* org_context, haxorg_HstdVecOfSubtreePeriod __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SubtreePeriod>::*)() const>(&hstd::Vec<org::sem::SubtreePeriod>::size), org_context, __this); }

haxorg_SubtreePeriod haxorg_HstdVecOfSubtreePeriod_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSubtreePeriod __this, int idx) { return org::bind::c::execute_cpp<haxorg_SubtreePeriod>(static_cast<org::sem::SubtreePeriod const&(hstd::Vec<org::sem::SubtreePeriod>::*)(int) const>(&hstd::Vec<org::sem::SubtreePeriod>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSubtreePeriod(OrgContext* org_context, haxorg_HstdVecOfSubtreePeriod* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::SubtreePeriod>>(org_context, obj); }

int haxorg_HstdVecOfNamedProperty_size_const(OrgContext* org_context, haxorg_HstdVecOfNamedProperty __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::NamedProperty>::*)() const>(&hstd::Vec<org::sem::NamedProperty>::size), org_context, __this); }

haxorg_NamedProperty haxorg_HstdVecOfNamedProperty_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfNamedProperty __this, int idx) { return org::bind::c::execute_cpp<haxorg_NamedProperty>(static_cast<org::sem::NamedProperty const&(hstd::Vec<org::sem::NamedProperty>::*)(int) const>(&hstd::Vec<org::sem::NamedProperty>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfNamedProperty(OrgContext* org_context, haxorg_HstdVecOfNamedProperty* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::NamedProperty>>(org_context, obj); }

int haxorg_HstdVecOfSemIdOfHashTag_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfHashTag __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::HashTag>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::HashTag>>::size), org_context, __this); }

haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfHashTag_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfHashTag __this, int idx) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::HashTag> const&(hstd::Vec<org::sem::SemId<org::sem::HashTag>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::HashTag>>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSemIdOfHashTag(OrgContext* org_context, haxorg_HstdVecOfSemIdOfHashTag* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::SemId<org::sem::HashTag>>>(org_context, obj); }

int haxorg_HstdVecOfSemIdOfSubtreeLog_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfSubtreeLog __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>::size), org_context, __this); }

haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfSubtreeLog_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfSubtreeLog __this, int idx) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::SubtreeLog> const&(hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSemIdOfSubtreeLog(OrgContext* org_context, haxorg_HstdVecOfSemIdOfSubtreeLog* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>>(org_context, obj); }

int haxorg_HstdVecOfTodoKeyword_size_const(OrgContext* org_context, haxorg_HstdVecOfTodoKeyword __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::TodoKeyword>::*)() const>(&hstd::Vec<org::sem::TodoKeyword>::size), org_context, __this); }

haxorg_TodoKeyword haxorg_HstdVecOfTodoKeyword_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfTodoKeyword __this, int idx) { return org::bind::c::execute_cpp<haxorg_TodoKeyword>(static_cast<org::sem::TodoKeyword const&(hstd::Vec<org::sem::TodoKeyword>::*)(int) const>(&hstd::Vec<org::sem::TodoKeyword>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfTodoKeyword(OrgContext* org_context, haxorg_HstdVecOfTodoKeyword* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::TodoKeyword>>(org_context, obj); }

int haxorg_HstdVecOfSemIdOfBigIdent_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfBigIdent __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::BigIdent>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::BigIdent>>::size), org_context, __this); }

haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfBigIdent_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfBigIdent __this, int idx) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::BigIdent> const&(hstd::Vec<org::sem::SemId<org::sem::BigIdent>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::BigIdent>>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSemIdOfBigIdent(OrgContext* org_context, haxorg_HstdVecOfSemIdOfBigIdent* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::SemId<org::sem::BigIdent>>>(org_context, obj); }

int haxorg_HstdVecOfUserTime_size_const(OrgContext* org_context, haxorg_HstdVecOfUserTime __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<hstd::UserTime>::*)() const>(&hstd::Vec<hstd::UserTime>::size), org_context, __this); }

haxorg_UserTime haxorg_HstdVecOfUserTime_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfUserTime __this, int idx) { return org::bind::c::execute_cpp<haxorg_UserTime>(static_cast<hstd::UserTime const&(hstd::Vec<hstd::UserTime>::*)(int) const>(&hstd::Vec<hstd::UserTime>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfUserTime(OrgContext* org_context, haxorg_HstdVecOfUserTime* obj) { org::bind::c::execute_destroy<hstd::Vec<hstd::UserTime>>(org_context, obj); }

int haxorg_HstdVecOfSemIdOfTime_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfTime __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::Time>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::Time>>::size), org_context, __this); }

haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfTime_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfTime __this, int idx) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Time> const&(hstd::Vec<org::sem::SemId<org::sem::Time>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::Time>>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSemIdOfTime(OrgContext* org_context, haxorg_HstdVecOfSemIdOfTime* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::SemId<org::sem::Time>>>(org_context, obj); }

int haxorg_HstdVecOfSemIdOfCell_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfCell __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::Cell>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::Cell>>::size), org_context, __this); }

haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfCell_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfCell __this, int idx) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Cell> const&(hstd::Vec<org::sem::SemId<org::sem::Cell>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::Cell>>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSemIdOfCell(OrgContext* org_context, haxorg_HstdVecOfSemIdOfCell* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::SemId<org::sem::Cell>>>(org_context, obj); }

int haxorg_HstdVecOfOrgCodeEvalOutput_size_const(OrgContext* org_context, haxorg_HstdVecOfOrgCodeEvalOutput __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::OrgCodeEvalOutput>::*)() const>(&hstd::Vec<org::sem::OrgCodeEvalOutput>::size), org_context, __this); }

haxorg_OrgCodeEvalOutput haxorg_HstdVecOfOrgCodeEvalOutput_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfOrgCodeEvalOutput __this, int idx) { return org::bind::c::execute_cpp<haxorg_OrgCodeEvalOutput>(static_cast<org::sem::OrgCodeEvalOutput const&(hstd::Vec<org::sem::OrgCodeEvalOutput>::*)(int) const>(&hstd::Vec<org::sem::OrgCodeEvalOutput>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfOrgCodeEvalOutput(OrgContext* org_context, haxorg_HstdVecOfOrgCodeEvalOutput* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::OrgCodeEvalOutput>>(org_context, obj); }

int haxorg_HstdVecOfSemIdOfBlockCodeEvalResult_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfBlockCodeEvalResult __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>::size), org_context, __this); }

haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfBlockCodeEvalResult_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfBlockCodeEvalResult __this, int idx) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::BlockCodeEvalResult> const&(hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSemIdOfBlockCodeEvalResult(OrgContext* org_context, haxorg_HstdVecOfSemIdOfBlockCodeEvalResult* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>>(org_context, obj); }

int haxorg_HstdVecOfBlockCodeLine_size_const(OrgContext* org_context, haxorg_HstdVecOfBlockCodeLine __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::BlockCodeLine>::*)() const>(&hstd::Vec<org::sem::BlockCodeLine>::size), org_context, __this); }

haxorg_BlockCodeLine haxorg_HstdVecOfBlockCodeLine_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfBlockCodeLine __this, int idx) { return org::bind::c::execute_cpp<haxorg_BlockCodeLine>(static_cast<org::sem::BlockCodeLine const&(hstd::Vec<org::sem::BlockCodeLine>::*)(int) const>(&hstd::Vec<org::sem::BlockCodeLine>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfBlockCodeLine(OrgContext* org_context, haxorg_HstdVecOfBlockCodeLine* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::BlockCodeLine>>(org_context, obj); }

int haxorg_HstdVecOfSemIdOfRow_size_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfRow __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::sem::SemId<org::sem::Row>>::*)() const>(&hstd::Vec<org::sem::SemId<org::sem::Row>>::size), org_context, __this); }

haxorg_SemIdOfOrg haxorg_HstdVecOfSemIdOfRow_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSemIdOfRow __this, int idx) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Row> const&(hstd::Vec<org::sem::SemId<org::sem::Row>>::*)(int) const>(&hstd::Vec<org::sem::SemId<org::sem::Row>>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSemIdOfRow(OrgContext* org_context, haxorg_HstdVecOfSemIdOfRow* obj) { org::bind::c::execute_destroy<hstd::Vec<org::sem::SemId<org::sem::Row>>>(org_context, obj); }

int haxorg_HstdVecOfAstTrackingGroup_size_const(OrgContext* org_context, haxorg_HstdVecOfAstTrackingGroup __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<org::AstTrackingGroup>::*)() const>(&hstd::Vec<org::AstTrackingGroup>::size), org_context, __this); }

haxorg_AstTrackingGroup haxorg_HstdVecOfAstTrackingGroup_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfAstTrackingGroup __this, int idx) { return org::bind::c::execute_cpp<haxorg_AstTrackingGroup>(static_cast<org::AstTrackingGroup const&(hstd::Vec<org::AstTrackingGroup>::*)(int) const>(&hstd::Vec<org::AstTrackingGroup>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfAstTrackingGroup(OrgContext* org_context, haxorg_HstdVecOfAstTrackingGroup* obj) { org::bind::c::execute_destroy<hstd::Vec<org::AstTrackingGroup>>(org_context, obj); }

int haxorg_HstdVecOfSequenceAnnotation_size_const(OrgContext* org_context, haxorg_HstdVecOfSequenceAnnotation __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<hstd::SequenceAnnotation>::*)() const>(&hstd::Vec<hstd::SequenceAnnotation>::size), org_context, __this); }

haxorg_SequenceAnnotation haxorg_HstdVecOfSequenceAnnotation_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSequenceAnnotation __this, int idx) { return org::bind::c::execute_cpp<haxorg_SequenceAnnotation>(static_cast<hstd::SequenceAnnotation const&(hstd::Vec<hstd::SequenceAnnotation>::*)(int) const>(&hstd::Vec<hstd::SequenceAnnotation>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSequenceAnnotation(OrgContext* org_context, haxorg_HstdVecOfSequenceAnnotation* obj) { org::bind::c::execute_destroy<hstd::Vec<hstd::SequenceAnnotation>>(org_context, obj); }

int haxorg_HstdVecOfSequenceSegmentGroup_size_const(OrgContext* org_context, haxorg_HstdVecOfSequenceSegmentGroup __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Vec<hstd::SequenceSegmentGroup>::*)() const>(&hstd::Vec<hstd::SequenceSegmentGroup>::size), org_context, __this); }

haxorg_SequenceSegmentGroup haxorg_HstdVecOfSequenceSegmentGroup_atIndex_const(OrgContext* org_context, haxorg_HstdVecOfSequenceSegmentGroup __this, int idx) { return org::bind::c::execute_cpp<haxorg_SequenceSegmentGroup>(static_cast<hstd::SequenceSegmentGroup const&(hstd::Vec<hstd::SequenceSegmentGroup>::*)(int) const>(&hstd::Vec<hstd::SequenceSegmentGroup>::at), org_context, __this, idx); }

void haxorg_destroy_HstdVecOfSequenceSegmentGroup(OrgContext* org_context, haxorg_HstdVecOfSequenceSegmentGroup* obj) { org::bind::c::execute_destroy<hstd::Vec<hstd::SequenceSegmentGroup>>(org_context, obj); }

void haxorg_destroy_IntSetOfSubtreePeriodKind(OrgContext* org_context, haxorg_IntSetOfSubtreePeriodKind* obj) { org::bind::c::execute_destroy<hstd::IntSet<org::sem::SubtreePeriod::Kind>>(org_context, obj); }

haxorg_ptr_payload haxorg_HstdMap_keys_const(OrgContext* org_context, haxorg_HstdMap __this) { return (static_cast<haxorg_HstdMap_vtable const*>(__this.data.vtable)->keys_const)(org_context, __this); }

haxorg_ptr_payload haxorg_ImmMap_get_const(OrgContext* org_context, haxorg_ImmMap __this, haxorg_ptr_payload const& key) { return (static_cast<haxorg_ImmMap_vtable const*>(__this.data.vtable)->get_const)(org_context, __this, key); }

bool haxorg_ImmMap_contains_const(OrgContext* org_context, haxorg_ImmMap __this, haxorg_ptr_payload const& key) { return (static_cast<haxorg_ImmMap_vtable const*>(__this.data.vtable)->contains_const)(org_context, __this, key); }

haxorg_ptr_payload haxorg_ImmMap_keys_const(OrgContext* org_context, haxorg_ImmMap __this) { return (static_cast<haxorg_ImmMap_vtable const*>(__this.data.vtable)->keys_const)(org_context, __this); }

haxorg_ptr_payload haxorg_StdOptional_value(OrgContext* org_context, haxorg_StdOptional __this) { return (static_cast<haxorg_StdOptional_vtable const*>(__this.data.vtable)->value)(org_context, __this); }

int haxorg_BackwardsIndex_get_value(OrgContext* org_context, haxorg_BackwardsIndex __this) { return org::bind::c::get_cpp_field<int, hstd::BackwardsIndex, int, haxorg_BackwardsIndex>(org_context, __this, &hstd::BackwardsIndex::value); }

void haxorg_destroy_BackwardsIndex(OrgContext* org_context, haxorg_BackwardsIndex* obj) { org::bind::c::execute_destroy<hstd::BackwardsIndex>(org_context, obj); }

haxorg_HstdStr haxorg_create_Str_StrFromCString(OrgContext* org_context, char const* conv) { return org::bind::c::execute_cpp<haxorg_HstdStr>(+[](char const* conv) -> hstd::Str { return hstd::Str(conv); }, org_context, conv); }

char* haxorg_Str_data(OrgContext* org_context, haxorg_HstdStr __this) { return org::bind::c::execute_cpp<char*>(static_cast<char*(hstd::Str::*)()>(&hstd::Str::data), org_context, __this); }

char const* haxorg_Str_data_const(OrgContext* org_context, haxorg_HstdStr __this) { return org::bind::c::execute_cpp<char const*>(static_cast<char const*(hstd::Str::*)() const>(&hstd::Str::data), org_context, __this); }

haxorg_HstdStr haxorg_Str_dropPrefix_const(OrgContext* org_context, haxorg_HstdStr __this, haxorg_HstdStr prefix) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str(hstd::Str::*)(hstd::Str const&) const>(&hstd::Str::dropPrefix), org_context, __this, prefix); }

haxorg_HstdStr haxorg_Str_dropSuffix_const(OrgContext* org_context, haxorg_HstdStr __this, haxorg_HstdStr suffix) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str(hstd::Str::*)(hstd::Str const&) const>(&hstd::Str::dropSuffix), org_context, __this, suffix); }

char haxorg_Str_atIndex_const(OrgContext* org_context, haxorg_HstdStr __this, int pos) { return org::bind::c::execute_cpp<char>(static_cast<char(hstd::Str::*)(int) const>(&hstd::Str::at), org_context, __this, pos); }

int haxorg_Str_size_const(OrgContext* org_context, haxorg_HstdStr __this) { return org::bind::c::execute_cpp<int>(static_cast<int(hstd::Str::*)() const>(&hstd::Str::size), org_context, __this); }

void haxorg_destroy_HstdStr(OrgContext* org_context, haxorg_HstdStr* obj) { org::bind::c::execute_destroy<hstd::Str>(org_context, obj); }

haxorg_StdOptional haxorg_UserTimeBreakdown_get_year(OrgContext* org_context, haxorg_UserTimeBreakdown __this) { return org::bind::c::get_cpp_field<haxorg_StdOptional, hstd::UserTimeBreakdown, std::optional<int>, haxorg_UserTimeBreakdown>(org_context, __this, &hstd::UserTimeBreakdown::year); }

haxorg_StdOptional haxorg_UserTimeBreakdown_get_month(OrgContext* org_context, haxorg_UserTimeBreakdown __this) { return org::bind::c::get_cpp_field<haxorg_StdOptional, hstd::UserTimeBreakdown, std::optional<int>, haxorg_UserTimeBreakdown>(org_context, __this, &hstd::UserTimeBreakdown::month); }

haxorg_StdOptional haxorg_UserTimeBreakdown_get_day(OrgContext* org_context, haxorg_UserTimeBreakdown __this) { return org::bind::c::get_cpp_field<haxorg_StdOptional, hstd::UserTimeBreakdown, std::optional<int>, haxorg_UserTimeBreakdown>(org_context, __this, &hstd::UserTimeBreakdown::day); }

haxorg_StdOptional haxorg_UserTimeBreakdown_get_hour(OrgContext* org_context, haxorg_UserTimeBreakdown __this) { return org::bind::c::get_cpp_field<haxorg_StdOptional, hstd::UserTimeBreakdown, std::optional<int>, haxorg_UserTimeBreakdown>(org_context, __this, &hstd::UserTimeBreakdown::hour); }

haxorg_StdOptional haxorg_UserTimeBreakdown_get_minute(OrgContext* org_context, haxorg_UserTimeBreakdown __this) { return org::bind::c::get_cpp_field<haxorg_StdOptional, hstd::UserTimeBreakdown, std::optional<int>, haxorg_UserTimeBreakdown>(org_context, __this, &hstd::UserTimeBreakdown::minute); }

haxorg_StdOptional haxorg_UserTimeBreakdown_get_second(OrgContext* org_context, haxorg_UserTimeBreakdown __this) { return org::bind::c::get_cpp_field<haxorg_StdOptional, hstd::UserTimeBreakdown, std::optional<int>, haxorg_UserTimeBreakdown>(org_context, __this, &hstd::UserTimeBreakdown::second); }

haxorg_StdOptional haxorg_UserTimeBreakdown_get_zone(OrgContext* org_context, haxorg_UserTimeBreakdown __this) { return org::bind::c::get_cpp_field<haxorg_StdOptional, hstd::UserTimeBreakdown, std::optional<std::string>, haxorg_UserTimeBreakdown>(org_context, __this, &hstd::UserTimeBreakdown::zone); }

void haxorg_destroy_UserTimeBreakdown(OrgContext* org_context, haxorg_UserTimeBreakdown* obj) { org::bind::c::execute_destroy<hstd::UserTimeBreakdown>(org_context, obj); }

haxorg_UserTimeBreakdown haxorg_UserTime_getBreakdown_const(OrgContext* org_context, haxorg_UserTime __this) { return org::bind::c::execute_cpp<haxorg_UserTimeBreakdown>(static_cast<hstd::UserTimeBreakdown(hstd::UserTime::*)() const>(&hstd::UserTime::getBreakdown), org_context, __this); }

haxorg_StdString haxorg_UserTime_format_const(OrgContext* org_context, haxorg_UserTime __this) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string(hstd::UserTime::*)() const>(&hstd::UserTime::format), org_context, __this); }

int64_t haxorg_UserTime_getTimeDeltaSeconds_const(OrgContext* org_context, haxorg_UserTime __this, haxorg_UserTime other) { return org::bind::c::execute_cpp<int64_t>(static_cast<int64_t(hstd::UserTime::*)(hstd::UserTime const&) const>(&hstd::UserTime::getTimeDeltaSeconds), org_context, __this, other); }

int64_t haxorg_UserTime_toUnixTimestamp_const(OrgContext* org_context, haxorg_UserTime __this) { return org::bind::c::execute_cpp<int64_t>(static_cast<int64_t(hstd::UserTime::*)() const>(&hstd::UserTime::toUnixTimestamp), org_context, __this); }

void haxorg_destroy_UserTime(OrgContext* org_context, haxorg_UserTime* obj) { org::bind::c::execute_destroy<hstd::UserTime>(org_context, obj); }

void haxorg_destroy_ParseSourceFileId(OrgContext* org_context, haxorg_ParseSourceFileId* obj) { org::bind::c::execute_destroy<org::parse::SourceFileId>(org_context, obj); }

haxorg_StdString haxorg_ParseSourceManager_getPath_const(OrgContext* org_context, haxorg_ParseSourceManager __this, haxorg_ParseSourceFileId id) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string(org::parse::SourceManager::*)(org::parse::SourceFileId const&) const>(&org::parse::SourceManager::getPath), org_context, __this, id); }

haxorg_ParseSourceFileId haxorg_ParseSourceManager_getId_const(OrgContext* org_context, haxorg_ParseSourceManager __this, haxorg_StdString path) { return org::bind::c::execute_cpp<haxorg_ParseSourceFileId>(static_cast<org::parse::SourceFileId(org::parse::SourceManager::*)(std::string const&) const>(&org::parse::SourceManager::getId), org_context, __this, path); }

haxorg_StdString haxorg_ParseSourceManager_getSourceContent_const(OrgContext* org_context, haxorg_ParseSourceManager __this, haxorg_ParseSourceFileId id) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string const&(org::parse::SourceManager::*)(org::parse::SourceFileId const&) const>(&org::parse::SourceManager::getSourceContent), org_context, __this, id); }

haxorg_StdString haxorg_ParseSourceManager_getContentTextForPath_const(OrgContext* org_context, haxorg_ParseSourceManager __this, haxorg_StdString path) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string const&(org::parse::SourceManager::*)(std::string const&) const>(&org::parse::SourceManager::getContentTextForPath), org_context, __this, path); }

haxorg_ParseSourceFileId haxorg_ParseSourceManager_addSource(OrgContext* org_context, haxorg_ParseSourceManager __this, haxorg_StdString path, haxorg_StdString content) { return org::bind::c::execute_cpp<haxorg_ParseSourceFileId>(static_cast<org::parse::SourceFileId(org::parse::SourceManager::*)(std::string const&, std::string const&)>(&org::parse::SourceManager::addSource), org_context, __this, path, content); }

void haxorg_destroy_ParseSourceManager(OrgContext* org_context, haxorg_ParseSourceManager* obj) { org::bind::c::execute_destroy<org::parse::SourceManager>(org_context, obj); }

int haxorg_ParseSourceLoc_get_line(OrgContext* org_context, haxorg_ParseSourceLoc __this) { return org::bind::c::get_cpp_field<int, org::parse::SourceLoc, int, haxorg_ParseSourceLoc>(org_context, __this, &org::parse::SourceLoc::line); }

int haxorg_ParseSourceLoc_get_column(OrgContext* org_context, haxorg_ParseSourceLoc __this) { return org::bind::c::get_cpp_field<int, org::parse::SourceLoc, int, haxorg_ParseSourceLoc>(org_context, __this, &org::parse::SourceLoc::column); }

int haxorg_ParseSourceLoc_get_pos(OrgContext* org_context, haxorg_ParseSourceLoc __this) { return org::bind::c::get_cpp_field<int, org::parse::SourceLoc, int, haxorg_ParseSourceLoc>(org_context, __this, &org::parse::SourceLoc::pos); }

haxorg_ParseSourceFileId haxorg_ParseSourceLoc_get_file_id(OrgContext* org_context, haxorg_ParseSourceLoc __this) { return org::bind::c::get_cpp_field<haxorg_ParseSourceFileId, org::parse::SourceLoc, org::parse::SourceFileId, haxorg_ParseSourceLoc>(org_context, __this, &org::parse::SourceLoc::file_id); }

void haxorg_destroy_ParseSourceLoc(OrgContext* org_context, haxorg_ParseSourceLoc* obj) { org::bind::c::execute_destroy<org::parse::SourceLoc>(org_context, obj); }

haxorg_OrgJsonKind haxorg_OrgJson_getKind_const(OrgContext* org_context, haxorg_OrgJson __this) { return org::bind::c::execute_cpp<haxorg_OrgJsonKind>(static_cast<OrgJsonKind(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getKind), org_context, __this); }

haxorg_StdString haxorg_OrgJson_getJsonString_const(OrgContext* org_context, haxorg_OrgJson __this) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getJsonString), org_context, __this); }

haxorg_OrgJson haxorg_OrgJson_atIndex_const(OrgContext* org_context, haxorg_OrgJson __this, int idx) { return org::bind::c::execute_cpp<haxorg_OrgJson>(static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::at), org_context, __this, idx); }

haxorg_OrgJson haxorg_OrgJson_atField_const(OrgContext* org_context, haxorg_OrgJson __this, haxorg_StdString name) { return org::bind::c::execute_cpp<haxorg_OrgJson>(static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(std::string const&) const>(&org::sem::OrgJson::at), org_context, __this, name); }

haxorg_StdString haxorg_OrgJson_getString_const(OrgContext* org_context, haxorg_OrgJson __this) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getString), org_context, __this); }

haxorg_OrgJson haxorg_OrgJson_getField_const(OrgContext* org_context, haxorg_OrgJson __this, haxorg_StdString name) { return org::bind::c::execute_cpp<haxorg_OrgJson>(static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(std::string const&) const>(&org::sem::OrgJson::getField), org_context, __this, name); }

haxorg_OrgJson haxorg_OrgJson_getItem_const(OrgContext* org_context, haxorg_OrgJson __this, int index) { return org::bind::c::execute_cpp<haxorg_OrgJson>(static_cast<org::sem::OrgJson(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::getItem), org_context, __this, index); }

int haxorg_OrgJson_getInt_const(OrgContext* org_context, haxorg_OrgJson __this) { return org::bind::c::execute_cpp<int>(static_cast<int(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getInt), org_context, __this); }

bool haxorg_OrgJson_getBool_const(OrgContext* org_context, haxorg_OrgJson __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getBool), org_context, __this); }

haxorg_HstdVecOfOrgJson haxorg_OrgJson_getArray_const(OrgContext* org_context, haxorg_OrgJson __this) { return org::bind::c::execute_cpp<haxorg_HstdVecOfOrgJson>(static_cast<hstd::Vec<org::sem::OrgJson>(org::sem::OrgJson::*)() const>(&org::sem::OrgJson::getArray), org_context, __this); }

haxorg_StdString haxorg_OrgJson_dump_const(OrgContext* org_context, haxorg_OrgJson __this, int indent) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string(org::sem::OrgJson::*)(int) const>(&org::sem::OrgJson::dump), org_context, __this, indent); }

void haxorg_destroy_OrgJson(OrgContext* org_context, haxorg_OrgJson* obj) { org::bind::c::execute_destroy<org::sem::OrgJson>(org_context, obj); }

haxorg_StdOptional haxorg_Org_get_loc(OrgContext* org_context, haxorg_Org __this) { return org::bind::c::get_cpp_field<haxorg_StdOptional, org::sem::Org, std::optional<org::parse::SourceLoc>, haxorg_Org>(org_context, __this, &org::sem::Org::loc); }

haxorg_HstdVecOfSemIdOfOrg haxorg_Org_get_subnodes(OrgContext* org_context, haxorg_Org __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSemIdOfOrg, org::sem::Org, hstd::Vec<org::sem::SemId<org::sem::Org>>, haxorg_Org>(org_context, __this, &org::sem::Org::subnodes); }

haxorg_OrgSemKind haxorg_Org_getKind_const(OrgContext* org_context, haxorg_Org __this) { return org::bind::c::execute_cpp<haxorg_OrgSemKind>(static_cast<OrgSemKind(org::sem::Org::*)() const>(&org::sem::Org::getKind), org_context, __this); }

void haxorg_Org_push_back(OrgContext* org_context, haxorg_Org __this, haxorg_SemIdOfOrg sub) { return org::bind::c::execute_cpp<void>(static_cast<void(org::sem::Org::*)(org::sem::SemId<org::sem::Org>)>(&org::sem::Org::push_back), org_context, __this, sub); }

int haxorg_Org_size_const(OrgContext* org_context, haxorg_Org __this) { return org::bind::c::execute_cpp<int>(static_cast<int(org::sem::Org::*)() const>(&org::sem::Org::size), org_context, __this); }

void haxorg_Org_insert(OrgContext* org_context, haxorg_Org __this, int pos, haxorg_SemIdOfOrg node) { return org::bind::c::execute_cpp<void>(static_cast<void(org::sem::Org::*)(int, org::sem::SemId<org::sem::Org>)>(&org::sem::Org::insert), org_context, __this, pos, node); }

haxorg_SemIdOfOrg haxorg_Org_at_const(OrgContext* org_context, haxorg_Org __this, int idx) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org>(org::sem::Org::*)(int) const>(&org::sem::Org::at), org_context, __this, idx); }

bool haxorg_Org_is_const(OrgContext* org_context, haxorg_Org __this, haxorg_OrgSemKind kind) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Org::*)(OrgSemKind) const>(&org::sem::Org::is), org_context, __this, kind); }

void haxorg_destroy_Org(OrgContext* org_context, haxorg_Org* obj) { org::bind::c::execute_destroy<org::sem::Org>(org_context, obj); }

bool haxorg_OperationsTracer_get_TraceState(OrgContext* org_context, haxorg_OperationsTracer __this) { return org::bind::c::get_cpp_field<bool, hstd::OperationsTracer, bool, haxorg_OperationsTracer>(org_context, __this, &hstd::OperationsTracer::TraceState); }

bool haxorg_OperationsTracer_get_traceToFile(OrgContext* org_context, haxorg_OperationsTracer __this) { return org::bind::c::get_cpp_field<bool, hstd::OperationsTracer, bool, haxorg_OperationsTracer>(org_context, __this, &hstd::OperationsTracer::traceToFile); }

bool haxorg_OperationsTracer_get_traceToBuffer(OrgContext* org_context, haxorg_OperationsTracer __this) { return org::bind::c::get_cpp_field<bool, hstd::OperationsTracer, bool, haxorg_OperationsTracer>(org_context, __this, &hstd::OperationsTracer::traceToBuffer); }

bool haxorg_OperationsTracer_get_traceStructured(OrgContext* org_context, haxorg_OperationsTracer __this) { return org::bind::c::get_cpp_field<bool, hstd::OperationsTracer, bool, haxorg_OperationsTracer>(org_context, __this, &hstd::OperationsTracer::traceStructured); }

bool haxorg_OperationsTracer_get_traceColored(OrgContext* org_context, haxorg_OperationsTracer __this) { return org::bind::c::get_cpp_field<bool, hstd::OperationsTracer, bool, haxorg_OperationsTracer>(org_context, __this, &hstd::OperationsTracer::traceColored); }

int haxorg_OperationsTracer_get_activeLevel(OrgContext* org_context, haxorg_OperationsTracer __this) { return org::bind::c::get_cpp_field<int, hstd::OperationsTracer, int, haxorg_OperationsTracer>(org_context, __this, &hstd::OperationsTracer::activeLevel); }

haxorg_StdString haxorg_OperationsTracer_get_traceBuffer(OrgContext* org_context, haxorg_OperationsTracer __this) { return org::bind::c::get_cpp_field<haxorg_StdString, hstd::OperationsTracer, std::string, haxorg_OperationsTracer>(org_context, __this, &hstd::OperationsTracer::traceBuffer); }

void haxorg_OperationsTracer_setTraceFileStr(OrgContext* org_context, haxorg_OperationsTracer __this, haxorg_StdString outfile, bool overwrite) { return org::bind::c::execute_cpp<void>(static_cast<void(hstd::OperationsTracer::*)(std::string const&, bool)>(&hstd::OperationsTracer::setTraceFileStr), org_context, __this, outfile, overwrite); }

void haxorg_OperationsTracer_sendMessage(OrgContext* org_context, haxorg_OperationsTracer __this, haxorg_StdString value, haxorg_StdString function, int line, haxorg_StdString file) { return org::bind::c::execute_cpp<void>(static_cast<void(hstd::OperationsTracer::*)(std::string const&, std::string const&, int, std::string const&)>(&hstd::OperationsTracer::sendMessage), org_context, __this, value, function, line, file); }

void haxorg_destroy_OperationsTracer(OrgContext* org_context, haxorg_OperationsTracer* obj) { org::bind::c::execute_destroy<hstd::OperationsTracer>(org_context, obj); }

void haxorg_destroy_Cache(OrgContext* org_context, haxorg_Cache* obj) { org::bind::c::execute_destroy<hstd::ext::Cache>(org_context, obj); }

void haxorg_destroy_Report(OrgContext* org_context, haxorg_Report* obj) { org::bind::c::execute_destroy<hstd::ext::Report>(org_context, obj); }

int haxorg_ParseOrgParseFragment_get_baseLine(OrgContext* org_context, haxorg_ParseOrgParseFragment __this) { return org::bind::c::get_cpp_field<int, org::parse::OrgParseFragment, int, haxorg_ParseOrgParseFragment>(org_context, __this, &org::parse::OrgParseFragment::baseLine); }

int haxorg_ParseOrgParseFragment_get_baseCol(OrgContext* org_context, haxorg_ParseOrgParseFragment __this) { return org::bind::c::get_cpp_field<int, org::parse::OrgParseFragment, int, haxorg_ParseOrgParseFragment>(org_context, __this, &org::parse::OrgParseFragment::baseCol); }

haxorg_StdString haxorg_ParseOrgParseFragment_get_text(OrgContext* org_context, haxorg_ParseOrgParseFragment __this) { return org::bind::c::get_cpp_field<haxorg_StdString, org::parse::OrgParseFragment, std::string, haxorg_ParseOrgParseFragment>(org_context, __this, &org::parse::OrgParseFragment::text); }

void haxorg_destroy_ParseOrgParseFragment(OrgContext* org_context, haxorg_ParseOrgParseFragment* obj) { org::bind::c::execute_destroy<org::parse::OrgParseFragment>(org_context, obj); }

haxorg_StdOptional haxorg_OrgParseParameters_get_baseTokenTracePath(OrgContext* org_context, haxorg_OrgParseParameters __this) { return org::bind::c::get_cpp_field<haxorg_StdOptional, org::parse::OrgParseParameters, std::optional<std::string>, haxorg_OrgParseParameters>(org_context, __this, &org::parse::OrgParseParameters::baseTokenTracePath); }

haxorg_StdOptional haxorg_OrgParseParameters_get_tokenTracePath(OrgContext* org_context, haxorg_OrgParseParameters __this) { return org::bind::c::get_cpp_field<haxorg_StdOptional, org::parse::OrgParseParameters, std::optional<std::string>, haxorg_OrgParseParameters>(org_context, __this, &org::parse::OrgParseParameters::tokenTracePath); }

haxorg_StdOptional haxorg_OrgParseParameters_get_parseTracePath(OrgContext* org_context, haxorg_OrgParseParameters __this) { return org::bind::c::get_cpp_field<haxorg_StdOptional, org::parse::OrgParseParameters, std::optional<std::string>, haxorg_OrgParseParameters>(org_context, __this, &org::parse::OrgParseParameters::parseTracePath); }

haxorg_StdOptional haxorg_OrgParseParameters_get_semTracePath(OrgContext* org_context, haxorg_OrgParseParameters __this) { return org::bind::c::get_cpp_field<haxorg_StdOptional, org::parse::OrgParseParameters, std::optional<std::string>, haxorg_OrgParseParameters>(org_context, __this, &org::parse::OrgParseParameters::semTracePath); }

void haxorg_destroy_OrgParseParameters(OrgContext* org_context, haxorg_OrgParseParameters* obj) { org::bind::c::execute_destroy<org::parse::OrgParseParameters>(org_context, obj); }

void haxorg_destroy_OrgDirectoryParseParameters(OrgContext* org_context, haxorg_OrgDirectoryParseParameters* obj) { org::bind::c::execute_destroy<org::parse::OrgDirectoryParseParameters>(org_context, obj); }

haxorg_ParseContext haxorg_create_ParseContext_ParseContextDefault(OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ParseContext>(+[]() -> org::parse::ParseContext { return org::parse::ParseContext(); }, org_context); }

haxorg_ParseContext haxorg_create_ParseContext_ParseContextWithManager(OrgContext* org_context, haxorg_ParseSourceManager source) { return org::bind::c::execute_cpp<haxorg_ParseContext>(+[](std::shared_ptr<org::parse::SourceManager> const& source) -> org::parse::ParseContext { return org::parse::ParseContext(source); }, org_context, source); }

haxorg_Cache haxorg_ParseContext_getDiagnosticStrings(OrgContext* org_context, haxorg_ParseContext __this) { return org::bind::c::execute_cpp<haxorg_Cache>(static_cast<std::shared_ptr<hstd::ext::Cache>(org::parse::ParseContext::*)()>(&org::parse::ParseContext::getDiagnosticStrings), org_context, __this); }

haxorg_ParseSourceFileId haxorg_ParseContext_addSource_const(OrgContext* org_context, haxorg_ParseContext __this, haxorg_StdString path, haxorg_StdString content) { return org::bind::c::execute_cpp<haxorg_ParseSourceFileId>(static_cast<org::parse::SourceFileId(org::parse::ParseContext::*)(std::string const&, std::string const&) const>(&org::parse::ParseContext::addSource), org_context, __this, path, content); }

haxorg_SemIdOfOrg haxorg_ParseContext_parseFileOpts(OrgContext* org_context, haxorg_ParseContext __this, haxorg_StdString file, haxorg_OrgParseParameters opts) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org>(org::parse::ParseContext::*)(std::string const&, std::shared_ptr<org::parse::OrgParseParameters> const&)>(&org::parse::ParseContext::parseFileOpts), org_context, __this, file, opts); }

haxorg_SemIdOfOrg haxorg_ParseContext_parseFile(OrgContext* org_context, haxorg_ParseContext __this, haxorg_StdString file) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org>(org::parse::ParseContext::*)(std::string const&)>(&org::parse::ParseContext::parseFile), org_context, __this, file); }

haxorg_SemIdOfOrg haxorg_ParseContext_parseString(OrgContext* org_context, haxorg_ParseContext __this, haxorg_StdString text, haxorg_StdString file_name) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org>(org::parse::ParseContext::*)(std::string const&, std::string const&)>(&org::parse::ParseContext::parseString), org_context, __this, text, file_name); }

haxorg_SemIdOfOrg haxorg_ParseContext_parseStringOpts(OrgContext* org_context, haxorg_ParseContext __this, haxorg_StdString text, haxorg_StdString file_name, haxorg_OrgParseParameters opts) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org>(org::parse::ParseContext::*)(std::string const, std::string const&, std::shared_ptr<org::parse::OrgParseParameters> const&)>(&org::parse::ParseContext::parseStringOpts), org_context, __this, text, file_name, opts); }

haxorg_StdOptional haxorg_ParseContext_parseDirectory(OrgContext* org_context, haxorg_ParseContext __this, haxorg_StdString path) { return org::bind::c::execute_cpp<haxorg_StdOptional>(static_cast<std::optional<org::sem::SemId<org::sem::Org>>(org::parse::ParseContext::*)(std::string const&)>(&org::parse::ParseContext::parseDirectory), org_context, __this, path); }

haxorg_StdOptional haxorg_ParseContext_parseDirectoryOpts(OrgContext* org_context, haxorg_ParseContext __this, haxorg_StdString path, haxorg_OrgDirectoryParseParameters opts) { return org::bind::c::execute_cpp<haxorg_StdOptional>(static_cast<std::optional<org::sem::SemId<org::sem::Org>>(org::parse::ParseContext::*)(std::string const&, std::shared_ptr<org::parse::OrgDirectoryParseParameters> const&)>(&org::parse::ParseContext::parseDirectoryOpts), org_context, __this, path, opts); }

haxorg_SemIdOfOrg haxorg_ParseContext_parseFileWithIncludes(OrgContext* org_context, haxorg_ParseContext __this, haxorg_StdString file, haxorg_OrgDirectoryParseParameters opts) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::File>(org::parse::ParseContext::*)(std::string const&, std::shared_ptr<org::parse::OrgDirectoryParseParameters> const&)>(&org::parse::ParseContext::parseFileWithIncludes), org_context, __this, file, opts); }

haxorg_HstdVecOfReport haxorg_ParseContext_collectDiagnostics(OrgContext* org_context, haxorg_ParseContext __this, haxorg_SemIdOfOrg tree, haxorg_Cache cache) { return org::bind::c::execute_cpp<haxorg_HstdVecOfReport>(static_cast<hstd::Vec<hstd::ext::Report>(org::parse::ParseContext::*)(org::sem::SemId<org::sem::Org> const&, std::shared_ptr<hstd::ext::Cache> const&)>(&org::parse::ParseContext::collectDiagnostics), org_context, __this, tree, cache); }

haxorg_HstdVecOfSemIdOfErrorGroup haxorg_ParseContext_collectErrorNodes(OrgContext* org_context, haxorg_ParseContext __this, haxorg_SemIdOfOrg tree) { return org::bind::c::execute_cpp<haxorg_HstdVecOfSemIdOfErrorGroup>(static_cast<hstd::Vec<org::sem::SemId<org::sem::ErrorGroup>>(org::parse::ParseContext::*)(org::sem::SemId<org::sem::Org> const&)>(&org::parse::ParseContext::collectErrorNodes), org_context, __this, tree); }

void haxorg_destroy_ParseContext(OrgContext* org_context, haxorg_ParseContext* obj) { org::bind::c::execute_destroy<org::parse::ParseContext>(org_context, obj); }

haxorg_HstdStr haxorg_ImmReflFieldId_getName_const(OrgContext* org_context, haxorg_ImmReflFieldId __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str(org::imm::ImmReflFieldId::*)() const>(&org::imm::ImmReflFieldId::getName), org_context, __this); }

void haxorg_destroy_ImmReflFieldId(OrgContext* org_context, haxorg_ImmReflFieldId* obj) { org::bind::c::execute_destroy<org::imm::ImmReflFieldId>(org_context, obj); }

haxorg_OrgSemKind haxorg_ImmId_getKind_const(OrgContext* org_context, haxorg_ImmId __this) { return org::bind::c::execute_cpp<haxorg_OrgSemKind>(static_cast<OrgSemKind(org::imm::ImmId::*)() const>(&org::imm::ImmId::getKind), org_context, __this); }

bool haxorg_ImmId_is_const(OrgContext* org_context, haxorg_ImmId __this, haxorg_OrgSemKind kind) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmId::*)(OrgSemKind) const>(&org::imm::ImmId::is), org_context, __this, kind); }

haxorg_ImmIdNodeIdxT haxorg_ImmId_getNodeIndex_const(OrgContext* org_context, haxorg_ImmId __this) { return org::bind::c::execute_cpp<haxorg_ImmIdNodeIdxT>(static_cast<org::imm::ImmId::NodeIdxT(org::imm::ImmId::*)() const>(&org::imm::ImmId::getNodeIndex), org_context, __this); }

haxorg_StdString haxorg_ImmId_getReadableId_const(OrgContext* org_context, haxorg_ImmId __this) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string(org::imm::ImmId::*)() const>(&org::imm::ImmId::getReadableId), org_context, __this); }

void haxorg_destroy_ImmId(OrgContext* org_context, haxorg_ImmId* obj) { org::bind::c::execute_destroy<org::imm::ImmId>(org_context, obj); }

void haxorg_destroy_ImmOrg(OrgContext* org_context, haxorg_ImmOrg* obj) { org::bind::c::execute_destroy<org::imm::ImmOrg>(org_context, obj); }

void haxorg_destroy_ImmPathStep(OrgContext* org_context, haxorg_ImmPathStep* obj) { org::bind::c::execute_destroy<org::imm::ImmPathStep>(org_context, obj); }

haxorg_ImmId haxorg_ImmPath_get_root(OrgContext* org_context, haxorg_ImmPath __this) { return org::bind::c::get_cpp_field<haxorg_ImmId, org::imm::ImmPath, org::imm::ImmId, haxorg_ImmPath>(org_context, __this, &org::imm::ImmPath::root); }

haxorg_ImmPathStore haxorg_ImmPath_get_path(OrgContext* org_context, haxorg_ImmPath __this) { return org::bind::c::get_cpp_field<haxorg_ImmPathStore, org::imm::ImmPath, org::imm::ImmPath::Store, haxorg_ImmPath>(org_context, __this, &org::imm::ImmPath::path); }

bool haxorg_ImmPath_empty_const(OrgContext* org_context, haxorg_ImmPath __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmPath::*)() const>(&org::imm::ImmPath::empty), org_context, __this); }

void haxorg_destroy_ImmPath(OrgContext* org_context, haxorg_ImmPath* obj) { org::bind::c::execute_destroy<org::imm::ImmPath>(org_context, obj); }

void haxorg_destroy_ImmUniqId(OrgContext* org_context, haxorg_ImmUniqId* obj) { org::bind::c::execute_destroy<org::imm::ImmUniqId>(org_context, obj); }

void haxorg_destroy_ImmAstReplaceEpoch(OrgContext* org_context, haxorg_ImmAstReplaceEpoch* obj) { org::bind::c::execute_destroy<org::imm::ImmAstReplaceEpoch>(org_context, obj); }

haxorg_ImmAstVersion haxorg_ImmAstContext_addRoot(OrgContext* org_context, haxorg_ImmAstContext __this, haxorg_SemIdOfOrg data) { return org::bind::c::execute_cpp<haxorg_ImmAstVersion>(static_cast<org::imm::ImmAstVersion(org::imm::ImmAstContext::*)(org::sem::SemId<org::sem::Org>)>(&org::imm::ImmAstContext::addRoot), org_context, __this, data); }

haxorg_ImmAstVersion haxorg_ImmAstContext_getEmptyVersion(OrgContext* org_context, haxorg_ImmAstContext __this) { return org::bind::c::execute_cpp<haxorg_ImmAstVersion>(static_cast<org::imm::ImmAstVersion(org::imm::ImmAstContext::*)()>(&org::imm::ImmAstContext::getEmptyVersion), org_context, __this); }

haxorg_SemIdOfOrg haxorg_ImmAstContext_get(OrgContext* org_context, haxorg_ImmAstContext __this, haxorg_ImmId id) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org>(org::imm::ImmAstContext::*)(org::imm::ImmId)>(&org::imm::ImmAstContext::get), org_context, __this, id); }

void haxorg_destroy_ImmAstContext(OrgContext* org_context, haxorg_ImmAstContext* obj) { org::bind::c::execute_destroy<org::imm::ImmAstContext>(org_context, obj); }

haxorg_ImmId haxorg_ImmAstVersion_getRoot_const(OrgContext* org_context, haxorg_ImmAstVersion __this) { return org::bind::c::execute_cpp<haxorg_ImmId>(static_cast<org::imm::ImmId(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getRoot), org_context, __this); }

haxorg_ImmAdapter haxorg_ImmAstVersion_getRootAdapter_const(OrgContext* org_context, haxorg_ImmAstVersion __this) { return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getRootAdapter), org_context, __this); }

haxorg_ImmAstContext haxorg_ImmAstVersion_getContext_const(OrgContext* org_context, haxorg_ImmAstVersion __this) { return org::bind::c::execute_cpp<haxorg_ImmAstContext>(static_cast<std::shared_ptr<org::imm::ImmAstContext>(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getContext), org_context, __this); }

haxorg_ImmAstReplaceEpoch haxorg_ImmAstVersion_getEpoch_const(OrgContext* org_context, haxorg_ImmAstVersion __this) { return org::bind::c::execute_cpp<haxorg_ImmAstReplaceEpoch>(static_cast<std::shared_ptr<org::imm::ImmAstReplaceEpoch>(org::imm::ImmAstVersion::*)() const>(&org::imm::ImmAstVersion::getEpoch), org_context, __this); }

void haxorg_destroy_ImmAstVersion(OrgContext* org_context, haxorg_ImmAstVersion* obj) { org::bind::c::execute_destroy<org::imm::ImmAstVersion>(org_context, obj); }

int haxorg_ImmAdapter_size_const(OrgContext* org_context, haxorg_ImmAdapter __this) { return org::bind::c::execute_cpp<int>(static_cast<int(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::size), org_context, __this); }

bool haxorg_ImmAdapter_isNil_const(OrgContext* org_context, haxorg_ImmAdapter __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::isNil), org_context, __this); }

bool haxorg_ImmAdapter_isRoot_const(OrgContext* org_context, haxorg_ImmAdapter __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::isRoot), org_context, __this); }

haxorg_OrgSemKind haxorg_ImmAdapter_getKind_const(OrgContext* org_context, haxorg_ImmAdapter __this) { return org::bind::c::execute_cpp<haxorg_OrgSemKind>(static_cast<OrgSemKind(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getKind), org_context, __this); }

haxorg_ImmUniqId haxorg_ImmAdapter_uniq_const(OrgContext* org_context, haxorg_ImmAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmUniqId>(static_cast<org::imm::ImmUniqId(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::uniq), org_context, __this); }

haxorg_StdString haxorg_ImmAdapter_treeReprString_const(OrgContext* org_context, haxorg_ImmAdapter __this) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::treeReprString), org_context, __this); }

haxorg_StdString haxorg_ImmAdapter_treeReprStringOpts_const(OrgContext* org_context, haxorg_ImmAdapter __this, haxorg_ImmAdapterTreeReprConf conf) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string(org::imm::ImmAdapter::*)(org::imm::ImmAdapter::TreeReprConf const&) const>(&org::imm::ImmAdapter::treeReprStringOpts), org_context, __this, conf); }

bool haxorg_ImmAdapter_isDirectParentOf_const(OrgContext* org_context, haxorg_ImmAdapter __this, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isDirectParentOf), org_context, __this, other); }

bool haxorg_ImmAdapter_isIndirectParentOf_const(OrgContext* org_context, haxorg_ImmAdapter __this, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isIndirectParentOf), org_context, __this, other); }

bool haxorg_ImmAdapter_isSubnodeOf_const(OrgContext* org_context, haxorg_ImmAdapter __this, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapter::*)(org::imm::ImmAdapter const&) const>(&org::imm::ImmAdapter::isSubnodeOf), org_context, __this, other); }

haxorg_StdOptional haxorg_ImmAdapter_getParent_const(OrgContext* org_context, haxorg_ImmAdapter __this) { return org::bind::c::execute_cpp<haxorg_StdOptional>(static_cast<std::optional<org::imm::ImmAdapter>(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getParent), org_context, __this); }

int haxorg_ImmAdapter_getSelfIndex_const(OrgContext* org_context, haxorg_ImmAdapter __this) { return org::bind::c::execute_cpp<int>(static_cast<int(org::imm::ImmAdapter::*)() const>(&org::imm::ImmAdapter::getSelfIndex), org_context, __this); }

haxorg_ImmAdapter haxorg_ImmAdapter_atPathStep_const(OrgContext* org_context, haxorg_ImmAdapter __this, haxorg_ImmId id, haxorg_ImmPathStep idx) { return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(org::imm::ImmId, org::imm::ImmPathStep) const>(&org::imm::ImmAdapter::at), org_context, __this, id, idx); }

haxorg_ImmAdapter haxorg_ImmAdapter_atField_const(OrgContext* org_context, haxorg_ImmAdapter __this, haxorg_ImmReflFieldId field) { return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(org::imm::ImmReflFieldId const&) const>(&org::imm::ImmAdapter::at), org_context, __this, field); }

haxorg_ImmAdapter haxorg_ImmAdapter_atIndex_const(OrgContext* org_context, haxorg_ImmAdapter __this, int idx, bool withPath) { return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(int, bool) const>(&org::imm::ImmAdapter::at), org_context, __this, idx, withPath); }

haxorg_ImmAdapter haxorg_ImmAdapter_atPath_const(OrgContext* org_context, haxorg_ImmAdapter __this, haxorg_HstdVecOfInt path, bool withPath) { return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapter::*)(hstd::Vec<int> const&, bool) const>(&org::imm::ImmAdapter::at), org_context, __this, path, withPath); }

bool haxorg_ImmAdapter_is_const(OrgContext* org_context, haxorg_ImmAdapter __this, haxorg_OrgSemKind kind) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapter::*)(OrgSemKind) const>(&org::imm::ImmAdapter::is), org_context, __this, kind); }

haxorg_HstdVecOfImmAdapter haxorg_ImmAdapter_sub_const(OrgContext* org_context, haxorg_ImmAdapter __this, bool withPath) { return org::bind::c::execute_cpp<haxorg_HstdVecOfImmAdapter>(static_cast<hstd::Vec<org::imm::ImmAdapter>(org::imm::ImmAdapter::*)(bool) const>(&org::imm::ImmAdapter::sub), org_context, __this, withPath); }

int haxorg_ImmAdapterTreeReprConf_get_maxDepth(OrgContext* org_context, haxorg_ImmAdapterTreeReprConf __this) { return org::bind::c::get_cpp_field<int, org::imm::ImmAdapter::TreeReprConf, int, haxorg_ImmAdapterTreeReprConf>(org_context, __this, &org::imm::ImmAdapter::TreeReprConf::maxDepth); }

bool haxorg_ImmAdapterTreeReprConf_get_withAuxFields(OrgContext* org_context, haxorg_ImmAdapterTreeReprConf __this) { return org::bind::c::get_cpp_field<bool, org::imm::ImmAdapter::TreeReprConf, bool, haxorg_ImmAdapterTreeReprConf>(org_context, __this, &org::imm::ImmAdapter::TreeReprConf::withAuxFields); }

bool haxorg_ImmAdapterTreeReprConf_get_withReflFields(OrgContext* org_context, haxorg_ImmAdapterTreeReprConf __this) { return org::bind::c::get_cpp_field<bool, org::imm::ImmAdapter::TreeReprConf, bool, haxorg_ImmAdapterTreeReprConf>(org_context, __this, &org::imm::ImmAdapter::TreeReprConf::withReflFields); }

haxorg_HstdUnorderedSet haxorg_ImmAdapterTreeReprConf_get_withFieldSubset(OrgContext* org_context, haxorg_ImmAdapterTreeReprConf __this) { return org::bind::c::get_cpp_field<haxorg_HstdUnorderedSet, org::imm::ImmAdapter::TreeReprConf, hstd::UnorderedSet<std::pair<OrgSemKind, org::imm::ImmReflFieldId>>, haxorg_ImmAdapterTreeReprConf>(org_context, __this, &org::imm::ImmAdapter::TreeReprConf::withFieldSubset); }

void haxorg_destroy_ImmAdapterTreeReprConf(OrgContext* org_context, haxorg_ImmAdapterTreeReprConf* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapter::TreeReprConf>(org_context, obj); }

void haxorg_destroy_ImmAdapter(OrgContext* org_context, haxorg_ImmAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapter>(org_context, obj); }

void haxorg_destroy_ImmAdapterVirtualBase(OrgContext* org_context, haxorg_ImmAdapterVirtualBase* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterVirtualBase>(org_context, obj); }

bool haxorg_OrgYamlExportOpts_get_skipNullFields(OrgContext* org_context, haxorg_OrgYamlExportOpts __this) { return org::bind::c::get_cpp_field<bool, org::OrgYamlExportOpts, bool, haxorg_OrgYamlExportOpts>(org_context, __this, &org::OrgYamlExportOpts::skipNullFields); }

bool haxorg_OrgYamlExportOpts_get_skipFalseFields(OrgContext* org_context, haxorg_OrgYamlExportOpts __this) { return org::bind::c::get_cpp_field<bool, org::OrgYamlExportOpts, bool, haxorg_OrgYamlExportOpts>(org_context, __this, &org::OrgYamlExportOpts::skipFalseFields); }

bool haxorg_OrgYamlExportOpts_get_skipZeroFields(OrgContext* org_context, haxorg_OrgYamlExportOpts __this) { return org::bind::c::get_cpp_field<bool, org::OrgYamlExportOpts, bool, haxorg_OrgYamlExportOpts>(org_context, __this, &org::OrgYamlExportOpts::skipZeroFields); }

bool haxorg_OrgYamlExportOpts_get_skipLocation(OrgContext* org_context, haxorg_OrgYamlExportOpts __this) { return org::bind::c::get_cpp_field<bool, org::OrgYamlExportOpts, bool, haxorg_OrgYamlExportOpts>(org_context, __this, &org::OrgYamlExportOpts::skipLocation); }

bool haxorg_OrgYamlExportOpts_get_skipId(OrgContext* org_context, haxorg_OrgYamlExportOpts __this) { return org::bind::c::get_cpp_field<bool, org::OrgYamlExportOpts, bool, haxorg_OrgYamlExportOpts>(org_context, __this, &org::OrgYamlExportOpts::skipId); }

void haxorg_destroy_OrgYamlExportOpts(OrgContext* org_context, haxorg_OrgYamlExportOpts* obj) { org::bind::c::execute_destroy<org::OrgYamlExportOpts>(org_context, obj); }

bool haxorg_OrgTreeExportOpts_get_withLineCol(OrgContext* org_context, haxorg_OrgTreeExportOpts __this) { return org::bind::c::get_cpp_field<bool, org::OrgTreeExportOpts, bool, haxorg_OrgTreeExportOpts>(org_context, __this, &org::OrgTreeExportOpts::withLineCol); }

bool haxorg_OrgTreeExportOpts_get_withOriginalId(OrgContext* org_context, haxorg_OrgTreeExportOpts __this) { return org::bind::c::get_cpp_field<bool, org::OrgTreeExportOpts, bool, haxorg_OrgTreeExportOpts>(org_context, __this, &org::OrgTreeExportOpts::withOriginalId); }

bool haxorg_OrgTreeExportOpts_get_withSubnodeIdx(OrgContext* org_context, haxorg_OrgTreeExportOpts __this) { return org::bind::c::get_cpp_field<bool, org::OrgTreeExportOpts, bool, haxorg_OrgTreeExportOpts>(org_context, __this, &org::OrgTreeExportOpts::withSubnodeIdx); }

bool haxorg_OrgTreeExportOpts_get_skipEmptyFields(OrgContext* org_context, haxorg_OrgTreeExportOpts __this) { return org::bind::c::get_cpp_field<bool, org::OrgTreeExportOpts, bool, haxorg_OrgTreeExportOpts>(org_context, __this, &org::OrgTreeExportOpts::skipEmptyFields); }

int haxorg_OrgTreeExportOpts_get_startLevel(OrgContext* org_context, haxorg_OrgTreeExportOpts __this) { return org::bind::c::get_cpp_field<int, org::OrgTreeExportOpts, int, haxorg_OrgTreeExportOpts>(org_context, __this, &org::OrgTreeExportOpts::startLevel); }

bool haxorg_OrgTreeExportOpts_get_withColor(OrgContext* org_context, haxorg_OrgTreeExportOpts __this) { return org::bind::c::get_cpp_field<bool, org::OrgTreeExportOpts, bool, haxorg_OrgTreeExportOpts>(org_context, __this, &org::OrgTreeExportOpts::withColor); }

int haxorg_OrgTreeExportOpts_get_maxDepth(OrgContext* org_context, haxorg_OrgTreeExportOpts __this) { return org::bind::c::get_cpp_field<int, org::OrgTreeExportOpts, int, haxorg_OrgTreeExportOpts>(org_context, __this, &org::OrgTreeExportOpts::maxDepth); }

void haxorg_destroy_OrgTreeExportOpts(OrgContext* org_context, haxorg_OrgTreeExportOpts* obj) { org::bind::c::execute_destroy<org::OrgTreeExportOpts>(org_context, obj); }

haxorg_HstdVecOfSemIdOfOrg haxorg_AstTrackingPath_get_path(OrgContext* org_context, haxorg_AstTrackingPath __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSemIdOfOrg, org::AstTrackingPath, hstd::Vec<org::sem::SemId<org::sem::Org>>, haxorg_AstTrackingPath>(org_context, __this, &org::AstTrackingPath::path); }

haxorg_SemIdOfOrg haxorg_AstTrackingPath_getParent_const(OrgContext* org_context, haxorg_AstTrackingPath __this, int offset) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingPath::*)(int) const>(&org::AstTrackingPath::getParent), org_context, __this, offset); }

haxorg_SemIdOfOrg haxorg_AstTrackingPath_getNode_const(OrgContext* org_context, haxorg_AstTrackingPath __this) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingPath::*)() const>(&org::AstTrackingPath::getNode), org_context, __this); }

void haxorg_destroy_AstTrackingPath(OrgContext* org_context, haxorg_AstTrackingPath* obj) { org::bind::c::execute_destroy<org::AstTrackingPath>(org_context, obj); }

haxorg_HstdVecOfSemIdOfOrg haxorg_AstTrackingAlternatives_getAllNodes_const(OrgContext* org_context, haxorg_AstTrackingAlternatives __this) { return org::bind::c::execute_cpp<haxorg_HstdVecOfSemIdOfOrg>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::AstTrackingAlternatives::*)() const>(&org::AstTrackingAlternatives::getAllNodes), org_context, __this); }

haxorg_SemIdOfOrg haxorg_AstTrackingAlternatives_getNode_const(OrgContext* org_context, haxorg_AstTrackingAlternatives __this) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org>(org::AstTrackingAlternatives::*)() const>(&org::AstTrackingAlternatives::getNode), org_context, __this); }

void haxorg_destroy_AstTrackingAlternatives(OrgContext* org_context, haxorg_AstTrackingAlternatives* obj) { org::bind::c::execute_destroy<org::AstTrackingAlternatives>(org_context, obj); }

haxorg_AstTrackingGroupRadioTarget haxorg_AstTrackingGroup_getRadioTargetConst_const(OrgContext* org_context, haxorg_AstTrackingGroup __this) { return org::bind::c::execute_cpp<haxorg_AstTrackingGroupRadioTarget>(static_cast<org::AstTrackingGroup::RadioTarget const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getRadioTarget), org_context, __this); }

haxorg_AstTrackingGroupTrackedHashtag haxorg_AstTrackingGroup_getTrackedHashtagConst_const(OrgContext* org_context, haxorg_AstTrackingGroup __this) { return org::bind::c::execute_cpp<haxorg_AstTrackingGroupTrackedHashtag>(static_cast<org::AstTrackingGroup::TrackedHashtag const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getTrackedHashtag), org_context, __this); }

haxorg_AstTrackingGroupTrackedHashtag haxorg_AstTrackingGroup_getTrackedHashtagMut(OrgContext* org_context, haxorg_AstTrackingGroup __this) { return org::bind::c::execute_cpp<haxorg_AstTrackingGroupTrackedHashtag>(static_cast<org::AstTrackingGroup::TrackedHashtag&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getTrackedHashtag), org_context, __this); }

haxorg_AstTrackingGroupSingle haxorg_AstTrackingGroup_getSingleConst_const(OrgContext* org_context, haxorg_AstTrackingGroup __this) { return org::bind::c::execute_cpp<haxorg_AstTrackingGroupSingle>(static_cast<org::AstTrackingGroup::Single const&(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::getSingle), org_context, __this); }

haxorg_AstTrackingGroupRadioTarget haxorg_AstTrackingGroup_getRadioTargetMut(OrgContext* org_context, haxorg_AstTrackingGroup __this) { return org::bind::c::execute_cpp<haxorg_AstTrackingGroupRadioTarget>(static_cast<org::AstTrackingGroup::RadioTarget&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getRadioTarget), org_context, __this); }

haxorg_AstTrackingGroupSingle haxorg_AstTrackingGroup_getSingleMut(OrgContext* org_context, haxorg_AstTrackingGroup __this) { return org::bind::c::execute_cpp<haxorg_AstTrackingGroupSingle>(static_cast<org::AstTrackingGroup::Single&(org::AstTrackingGroup::*)()>(&org::AstTrackingGroup::getSingle), org_context, __this); }

bool haxorg_AstTrackingGroup_isSingle_const(OrgContext* org_context, haxorg_AstTrackingGroup __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isSingle), org_context, __this); }

bool haxorg_AstTrackingGroup_isTrackedHashtag_const(OrgContext* org_context, haxorg_AstTrackingGroup __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isTrackedHashtag), org_context, __this); }

bool haxorg_AstTrackingGroup_isRadioTarget_const(OrgContext* org_context, haxorg_AstTrackingGroup __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::AstTrackingGroup::*)() const>(&org::AstTrackingGroup::isRadioTarget), org_context, __this); }

haxorg_AstTrackingPath haxorg_AstTrackingGroupRadioTarget_get_target(OrgContext* org_context, haxorg_AstTrackingGroupRadioTarget __this) { return org::bind::c::get_cpp_field<haxorg_AstTrackingPath, org::AstTrackingGroup::RadioTarget, org::AstTrackingPath, haxorg_AstTrackingGroupRadioTarget>(org_context, __this, &org::AstTrackingGroup::RadioTarget::target); }

haxorg_HstdVecOfSemIdOfOrg haxorg_AstTrackingGroupRadioTarget_get_nodes(OrgContext* org_context, haxorg_AstTrackingGroupRadioTarget __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSemIdOfOrg, org::AstTrackingGroup::RadioTarget, hstd::Vec<org::sem::SemId<org::sem::Org>>, haxorg_AstTrackingGroupRadioTarget>(org_context, __this, &org::AstTrackingGroup::RadioTarget::nodes); }

void haxorg_destroy_AstTrackingGroupRadioTarget(OrgContext* org_context, haxorg_AstTrackingGroupRadioTarget* obj) { org::bind::c::execute_destroy<org::AstTrackingGroup::RadioTarget>(org_context, obj); }

haxorg_SemIdOfOrg haxorg_AstTrackingGroupSingle_get_node(OrgContext* org_context, haxorg_AstTrackingGroupSingle __this) { return org::bind::c::get_cpp_field<haxorg_SemIdOfOrg, org::AstTrackingGroup::Single, org::sem::SemId<org::sem::Org>, haxorg_AstTrackingGroupSingle>(org_context, __this, &org::AstTrackingGroup::Single::node); }

void haxorg_destroy_AstTrackingGroupSingle(OrgContext* org_context, haxorg_AstTrackingGroupSingle* obj) { org::bind::c::execute_destroy<org::AstTrackingGroup::Single>(org_context, obj); }

haxorg_SemIdOfOrg haxorg_AstTrackingGroupTrackedHashtag_get_tag(OrgContext* org_context, haxorg_AstTrackingGroupTrackedHashtag __this) { return org::bind::c::get_cpp_field<haxorg_SemIdOfOrg, org::AstTrackingGroup::TrackedHashtag, org::sem::SemId<org::sem::Org>, haxorg_AstTrackingGroupTrackedHashtag>(org_context, __this, &org::AstTrackingGroup::TrackedHashtag::tag); }

haxorg_HstdMap haxorg_AstTrackingGroupTrackedHashtag_get_targets(OrgContext* org_context, haxorg_AstTrackingGroupTrackedHashtag __this) { return org::bind::c::get_cpp_field<haxorg_HstdMap, org::AstTrackingGroup::TrackedHashtag, hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingPath>, haxorg_AstTrackingGroupTrackedHashtag>(org_context, __this, &org::AstTrackingGroup::TrackedHashtag::targets); }

void haxorg_destroy_AstTrackingGroupTrackedHashtag(OrgContext* org_context, haxorg_AstTrackingGroupTrackedHashtag* obj) { org::bind::c::execute_destroy<org::AstTrackingGroup::TrackedHashtag>(org_context, obj); }

void haxorg_destroy_AstTrackingGroup(OrgContext* org_context, haxorg_AstTrackingGroup* obj) { org::bind::c::execute_destroy<org::AstTrackingGroup>(org_context, obj); }

haxorg_HstdMap haxorg_AstTrackingMap_get_footnotes(OrgContext* org_context, haxorg_AstTrackingMap __this) { return org::bind::c::get_cpp_field<haxorg_HstdMap, org::AstTrackingMap, hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives>, haxorg_AstTrackingMap>(org_context, __this, &org::AstTrackingMap::footnotes); }

haxorg_HstdMap haxorg_AstTrackingMap_get_subtrees(OrgContext* org_context, haxorg_AstTrackingMap __this) { return org::bind::c::get_cpp_field<haxorg_HstdMap, org::AstTrackingMap, hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives>, haxorg_AstTrackingMap>(org_context, __this, &org::AstTrackingMap::subtrees); }

haxorg_HstdMap haxorg_AstTrackingMap_get_names(OrgContext* org_context, haxorg_AstTrackingMap __this) { return org::bind::c::get_cpp_field<haxorg_HstdMap, org::AstTrackingMap, hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives>, haxorg_AstTrackingMap>(org_context, __this, &org::AstTrackingMap::names); }

haxorg_HstdMap haxorg_AstTrackingMap_get_anchorTargets(OrgContext* org_context, haxorg_AstTrackingMap __this) { return org::bind::c::get_cpp_field<haxorg_HstdMap, org::AstTrackingMap, hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives>, haxorg_AstTrackingMap>(org_context, __this, &org::AstTrackingMap::anchorTargets); }

haxorg_HstdMap haxorg_AstTrackingMap_get_radioTargets(OrgContext* org_context, haxorg_AstTrackingMap __this) { return org::bind::c::get_cpp_field<haxorg_HstdMap, org::AstTrackingMap, hstd::UnorderedMap<hstd::Str, org::AstTrackingAlternatives>, haxorg_AstTrackingMap>(org_context, __this, &org::AstTrackingMap::radioTargets); }

haxorg_HstdMap haxorg_AstTrackingMap_get_hashtagDefinitions(OrgContext* org_context, haxorg_AstTrackingMap __this) { return org::bind::c::get_cpp_field<haxorg_HstdMap, org::AstTrackingMap, hstd::UnorderedMap<org::sem::HashTagFlat, org::AstTrackingAlternatives>, haxorg_AstTrackingMap>(org_context, __this, &org::AstTrackingMap::hashtagDefinitions); }

haxorg_StdOptional haxorg_AstTrackingMap_getIdPath_const(OrgContext* org_context, haxorg_AstTrackingMap __this, haxorg_HstdStr id) { return org::bind::c::execute_cpp<haxorg_StdOptional>(static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getIdPath), org_context, __this, id); }

haxorg_StdOptional haxorg_AstTrackingMap_getNamePath_const(OrgContext* org_context, haxorg_AstTrackingMap __this, haxorg_HstdStr id) { return org::bind::c::execute_cpp<haxorg_StdOptional>(static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getNamePath), org_context, __this, id); }

haxorg_StdOptional haxorg_AstTrackingMap_getAnchorTarget_const(OrgContext* org_context, haxorg_AstTrackingMap __this, haxorg_HstdStr id) { return org::bind::c::execute_cpp<haxorg_StdOptional>(static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getAnchorTarget), org_context, __this, id); }

haxorg_StdOptional haxorg_AstTrackingMap_getFootnotePath_const(OrgContext* org_context, haxorg_AstTrackingMap __this, haxorg_HstdStr id) { return org::bind::c::execute_cpp<haxorg_StdOptional>(static_cast<std::optional<org::AstTrackingAlternatives>(org::AstTrackingMap::*)(hstd::Str const&) const>(&org::AstTrackingMap::getFootnotePath), org_context, __this, id); }

void haxorg_destroy_AstTrackingMap(OrgContext* org_context, haxorg_AstTrackingMap* obj) { org::bind::c::execute_destroy<org::AstTrackingMap>(org_context, obj); }

int haxorg_SequenceSegment_get_kind(OrgContext* org_context, haxorg_SequenceSegment __this) { return org::bind::c::get_cpp_field<int, hstd::SequenceSegment, int, haxorg_SequenceSegment>(org_context, __this, &hstd::SequenceSegment::kind); }

int haxorg_SequenceSegment_get_first(OrgContext* org_context, haxorg_SequenceSegment __this) { return org::bind::c::get_cpp_field<int, hstd::SequenceSegment, int, haxorg_SequenceSegment>(org_context, __this, &hstd::SequenceSegment::first); }

int haxorg_SequenceSegment_get_last(OrgContext* org_context, haxorg_SequenceSegment __this) { return org::bind::c::get_cpp_field<int, hstd::SequenceSegment, int, haxorg_SequenceSegment>(org_context, __this, &hstd::SequenceSegment::last); }

void haxorg_destroy_SequenceSegment(OrgContext* org_context, haxorg_SequenceSegment* obj) { org::bind::c::execute_destroy<hstd::SequenceSegment>(org_context, obj); }

int haxorg_SequenceSegmentGroup_get_kind(OrgContext* org_context, haxorg_SequenceSegmentGroup __this) { return org::bind::c::get_cpp_field<int, hstd::SequenceSegmentGroup, int, haxorg_SequenceSegmentGroup>(org_context, __this, &hstd::SequenceSegmentGroup::kind); }

haxorg_HstdVecOfSequenceSegment haxorg_SequenceSegmentGroup_get_segments(OrgContext* org_context, haxorg_SequenceSegmentGroup __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSequenceSegment, hstd::SequenceSegmentGroup, hstd::Vec<hstd::SequenceSegment>, haxorg_SequenceSegmentGroup>(org_context, __this, &hstd::SequenceSegmentGroup::segments); }

void haxorg_destroy_SequenceSegmentGroup(OrgContext* org_context, haxorg_SequenceSegmentGroup* obj) { org::bind::c::execute_destroy<hstd::SequenceSegmentGroup>(org_context, obj); }

int haxorg_SequenceAnnotationTag_get_groupKind(OrgContext* org_context, haxorg_SequenceAnnotationTag __this) { return org::bind::c::get_cpp_field<int, hstd::SequenceAnnotationTag, int, haxorg_SequenceAnnotationTag>(org_context, __this, &hstd::SequenceAnnotationTag::groupKind); }

haxorg_HstdVecOfInt haxorg_SequenceAnnotationTag_get_segmentKinds(OrgContext* org_context, haxorg_SequenceAnnotationTag __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfInt, hstd::SequenceAnnotationTag, hstd::Vec<int>, haxorg_SequenceAnnotationTag>(org_context, __this, &hstd::SequenceAnnotationTag::segmentKinds); }

void haxorg_destroy_SequenceAnnotationTag(OrgContext* org_context, haxorg_SequenceAnnotationTag* obj) { org::bind::c::execute_destroy<hstd::SequenceAnnotationTag>(org_context, obj); }

int haxorg_SequenceAnnotation_get_first(OrgContext* org_context, haxorg_SequenceAnnotation __this) { return org::bind::c::get_cpp_field<int, hstd::SequenceAnnotation, int, haxorg_SequenceAnnotation>(org_context, __this, &hstd::SequenceAnnotation::first); }

int haxorg_SequenceAnnotation_get_last(OrgContext* org_context, haxorg_SequenceAnnotation __this) { return org::bind::c::get_cpp_field<int, hstd::SequenceAnnotation, int, haxorg_SequenceAnnotation>(org_context, __this, &hstd::SequenceAnnotation::last); }

haxorg_HstdVecOfSequenceAnnotationTag haxorg_SequenceAnnotation_get_annotations(OrgContext* org_context, haxorg_SequenceAnnotation __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSequenceAnnotationTag, hstd::SequenceAnnotation, hstd::Vec<hstd::SequenceAnnotationTag>, haxorg_SequenceAnnotation>(org_context, __this, &hstd::SequenceAnnotation::annotations); }

bool haxorg_SequenceAnnotation_isAnnotatedWith_const(OrgContext* org_context, haxorg_SequenceAnnotation __this, int groupKind, int segmentKind) { return org::bind::c::execute_cpp<bool>(static_cast<bool(hstd::SequenceAnnotation::*)(int, int) const>(&hstd::SequenceAnnotation::isAnnotatedWith), org_context, __this, groupKind, segmentKind); }

void haxorg_destroy_SequenceAnnotation(OrgContext* org_context, haxorg_SequenceAnnotation* obj) { org::bind::c::execute_destroy<hstd::SequenceAnnotation>(org_context, obj); }

haxorg_GraphMapLinkRadio haxorg_GraphMapLink_getRadio(OrgContext* org_context, haxorg_GraphMapLink __this) { return org::bind::c::execute_cpp<haxorg_GraphMapLinkRadio>(static_cast<org::graph::MapLink::Radio&(org::graph::MapLink::*)()>(&org::graph::MapLink::getRadio), org_context, __this); }

haxorg_GraphMapLinkRadio haxorg_GraphMapLink_getRadio_const(OrgContext* org_context, haxorg_GraphMapLink __this) { return org::bind::c::execute_cpp<haxorg_GraphMapLinkRadio>(static_cast<org::graph::MapLink::Radio const&(org::graph::MapLink::*)() const>(&org::graph::MapLink::getRadio), org_context, __this); }

bool haxorg_GraphMapLink_isRadio_const(OrgContext* org_context, haxorg_GraphMapLink __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::graph::MapLink::*)() const>(&org::graph::MapLink::isRadio), org_context, __this); }

haxorg_GraphMapLinkLink haxorg_GraphMapLink_getLink(OrgContext* org_context, haxorg_GraphMapLink __this) { return org::bind::c::execute_cpp<haxorg_GraphMapLinkLink>(static_cast<org::graph::MapLink::Link&(org::graph::MapLink::*)()>(&org::graph::MapLink::getLink), org_context, __this); }

haxorg_GraphMapLinkLink haxorg_GraphMapLink_getLink_const(OrgContext* org_context, haxorg_GraphMapLink __this) { return org::bind::c::execute_cpp<haxorg_GraphMapLinkLink>(static_cast<org::graph::MapLink::Link const&(org::graph::MapLink::*)() const>(&org::graph::MapLink::getLink), org_context, __this); }

bool haxorg_GraphMapLink_isLink_const(OrgContext* org_context, haxorg_GraphMapLink __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::graph::MapLink::*)() const>(&org::graph::MapLink::isLink), org_context, __this); }

haxorg_GraphMapLinkKind haxorg_GraphMapLink_getKind_const(OrgContext* org_context, haxorg_GraphMapLink __this) { return org::bind::c::execute_cpp<haxorg_GraphMapLinkKind>(static_cast<org::graph::MapLink::Kind(org::graph::MapLink::*)() const>(&org::graph::MapLink::getKind), org_context, __this); }

haxorg_ImmUniqId haxorg_GraphMapLinkLink_get_link(OrgContext* org_context, haxorg_GraphMapLinkLink __this) { return org::bind::c::get_cpp_field<haxorg_ImmUniqId, org::graph::MapLink::Link, org::imm::ImmUniqId, haxorg_GraphMapLinkLink>(org_context, __this, &org::graph::MapLink::Link::link); }

haxorg_HstdVecOfImmUniqId haxorg_GraphMapLinkLink_get_description(OrgContext* org_context, haxorg_GraphMapLinkLink __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfImmUniqId, org::graph::MapLink::Link, hstd::Vec<org::imm::ImmUniqId>, haxorg_GraphMapLinkLink>(org_context, __this, &org::graph::MapLink::Link::description); }

void haxorg_destroy_GraphMapLinkLink(OrgContext* org_context, haxorg_GraphMapLinkLink* obj) { org::bind::c::execute_destroy<org::graph::MapLink::Link>(org_context, obj); }

haxorg_ImmUniqId haxorg_GraphMapLinkRadio_get_target(OrgContext* org_context, haxorg_GraphMapLinkRadio __this) { return org::bind::c::get_cpp_field<haxorg_ImmUniqId, org::graph::MapLink::Radio, org::imm::ImmUniqId, haxorg_GraphMapLinkRadio>(org_context, __this, &org::graph::MapLink::Radio::target); }

void haxorg_destroy_GraphMapLinkRadio(OrgContext* org_context, haxorg_GraphMapLinkRadio* obj) { org::bind::c::execute_destroy<org::graph::MapLink::Radio>(org_context, obj); }

void haxorg_destroy_GraphMapLink(OrgContext* org_context, haxorg_GraphMapLink* obj) { org::bind::c::execute_destroy<org::graph::MapLink>(org_context, obj); }

haxorg_ImmUniqId haxorg_GraphMapNodeProp_get_id(OrgContext* org_context, haxorg_GraphMapNodeProp __this) { return org::bind::c::get_cpp_field<haxorg_ImmUniqId, org::graph::MapNodeProp, org::imm::ImmUniqId, haxorg_GraphMapNodeProp>(org_context, __this, &org::graph::MapNodeProp::id); }

haxorg_HstdVecOfGraphMapLink haxorg_GraphMapNodeProp_get_unresolved(OrgContext* org_context, haxorg_GraphMapNodeProp __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfGraphMapLink, org::graph::MapNodeProp, hstd::Vec<org::graph::MapLink>, haxorg_GraphMapNodeProp>(org_context, __this, &org::graph::MapNodeProp::unresolved); }

haxorg_ImmAdapter haxorg_GraphMapNodeProp_getAdapter_const(OrgContext* org_context, haxorg_GraphMapNodeProp __this, haxorg_ImmAstContext context) { return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter(org::graph::MapNodeProp::*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&org::graph::MapNodeProp::getAdapter), org_context, __this, context); }

haxorg_StdOptional haxorg_GraphMapNodeProp_getSubtreeId_const(OrgContext* org_context, haxorg_GraphMapNodeProp __this, haxorg_ImmAstContext context) { return org::bind::c::execute_cpp<haxorg_StdOptional>(static_cast<std::optional<hstd::Str>(org::graph::MapNodeProp::*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&org::graph::MapNodeProp::getSubtreeId), org_context, __this, context); }

haxorg_StdOptional haxorg_GraphMapNodeProp_getFootnoteName_const(OrgContext* org_context, haxorg_GraphMapNodeProp __this, haxorg_ImmAstContext context) { return org::bind::c::execute_cpp<haxorg_StdOptional>(static_cast<std::optional<hstd::Str>(org::graph::MapNodeProp::*)(std::shared_ptr<org::imm::ImmAstContext> const&) const>(&org::graph::MapNodeProp::getFootnoteName), org_context, __this, context); }

void haxorg_destroy_GraphMapNodeProp(OrgContext* org_context, haxorg_GraphMapNodeProp* obj) { org::bind::c::execute_destroy<org::graph::MapNodeProp>(org_context, obj); }

haxorg_GraphMapLink haxorg_GraphMapEdgeProp_get_link(OrgContext* org_context, haxorg_GraphMapEdgeProp __this) { return org::bind::c::get_cpp_field<haxorg_GraphMapLink, org::graph::MapEdgeProp, org::graph::MapLink, haxorg_GraphMapEdgeProp>(org_context, __this, &org::graph::MapEdgeProp::link); }

void haxorg_destroy_GraphMapEdgeProp(OrgContext* org_context, haxorg_GraphMapEdgeProp* obj) { org::bind::c::execute_destroy<org::graph::MapEdgeProp>(org_context, obj); }

haxorg_ImmUniqId haxorg_GraphMapNode_get_id(OrgContext* org_context, haxorg_GraphMapNode __this) { return org::bind::c::get_cpp_field<haxorg_ImmUniqId, org::graph::MapNode, org::imm::ImmUniqId, haxorg_GraphMapNode>(org_context, __this, &org::graph::MapNode::id); }

bool haxorg_GraphMapNode___eq___const(OrgContext* org_context, haxorg_GraphMapNode __this, haxorg_GraphMapNode other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::graph::MapNode::*)(org::graph::MapNode const&) const>(&org::graph::MapNode::operator==), org_context, __this, other); }

bool haxorg_GraphMapNode___lt___const(OrgContext* org_context, haxorg_GraphMapNode __this, haxorg_GraphMapNode other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::graph::MapNode::*)(org::graph::MapNode const&) const>(&org::graph::MapNode::operator<), org_context, __this, other); }

void haxorg_destroy_GraphMapNode(OrgContext* org_context, haxorg_GraphMapNode* obj) { org::bind::c::execute_destroy<org::graph::MapNode>(org_context, obj); }

haxorg_GraphMapNode haxorg_GraphMapEdge_get_source(OrgContext* org_context, haxorg_GraphMapEdge __this) { return org::bind::c::get_cpp_field<haxorg_GraphMapNode, org::graph::MapEdge, org::graph::MapNode, haxorg_GraphMapEdge>(org_context, __this, &org::graph::MapEdge::source); }

haxorg_GraphMapNode haxorg_GraphMapEdge_get_target(OrgContext* org_context, haxorg_GraphMapEdge __this) { return org::bind::c::get_cpp_field<haxorg_GraphMapNode, org::graph::MapEdge, org::graph::MapNode, haxorg_GraphMapEdge>(org_context, __this, &org::graph::MapEdge::target); }

void haxorg_destroy_GraphMapEdge(OrgContext* org_context, haxorg_GraphMapEdge* obj) { org::bind::c::execute_destroy<org::graph::MapEdge>(org_context, obj); }

haxorg_GraphNodeProps haxorg_GraphMapGraph_get_nodeProps(OrgContext* org_context, haxorg_GraphMapGraph __this) { return org::bind::c::get_cpp_field<haxorg_GraphNodeProps, org::graph::MapGraph, org::graph::NodeProps, haxorg_GraphMapGraph>(org_context, __this, &org::graph::MapGraph::nodeProps); }

haxorg_GraphEdgeProps haxorg_GraphMapGraph_get_edgeProps(OrgContext* org_context, haxorg_GraphMapGraph __this) { return org::bind::c::get_cpp_field<haxorg_GraphEdgeProps, org::graph::MapGraph, org::graph::EdgeProps, haxorg_GraphMapGraph>(org_context, __this, &org::graph::MapGraph::edgeProps); }

haxorg_GraphAdjList haxorg_GraphMapGraph_get_adjList(OrgContext* org_context, haxorg_GraphMapGraph __this) { return org::bind::c::get_cpp_field<haxorg_GraphAdjList, org::graph::MapGraph, org::graph::AdjList, haxorg_GraphMapGraph>(org_context, __this, &org::graph::MapGraph::adjList); }

haxorg_GraphAdjList haxorg_GraphMapGraph_get_adjListIn(OrgContext* org_context, haxorg_GraphMapGraph __this) { return org::bind::c::get_cpp_field<haxorg_GraphAdjList, org::graph::MapGraph, org::graph::AdjList, haxorg_GraphMapGraph>(org_context, __this, &org::graph::MapGraph::adjListIn); }

int haxorg_GraphMapGraph_nodeCount_const(OrgContext* org_context, haxorg_GraphMapGraph __this) { return org::bind::c::execute_cpp<int>(static_cast<int(org::graph::MapGraph::*)() const>(&org::graph::MapGraph::nodeCount), org_context, __this); }

int haxorg_GraphMapGraph_edgeCount_const(OrgContext* org_context, haxorg_GraphMapGraph __this) { return org::bind::c::execute_cpp<int>(static_cast<int(org::graph::MapGraph::*)() const>(&org::graph::MapGraph::edgeCount), org_context, __this); }

haxorg_GraphAdjNodesList haxorg_GraphMapGraph_outNodes_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node) { return org::bind::c::execute_cpp<haxorg_GraphAdjNodesList>(static_cast<org::graph::AdjNodesList const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outNodes), org_context, __this, node); }

haxorg_GraphAdjNodesList haxorg_GraphMapGraph_inNodes_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node) { return org::bind::c::execute_cpp<haxorg_GraphAdjNodesList>(static_cast<org::graph::AdjNodesList const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inNodes), org_context, __this, node); }

haxorg_HstdVecOfGraphMapEdge haxorg_GraphMapGraph_adjEdges_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node) { return org::bind::c::execute_cpp<haxorg_HstdVecOfGraphMapEdge>(static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::adjEdges), org_context, __this, node); }

haxorg_HstdVecOfGraphMapNode haxorg_GraphMapGraph_adjNodes_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node) { return org::bind::c::execute_cpp<haxorg_HstdVecOfGraphMapNode>(static_cast<hstd::Vec<org::graph::MapNode>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::adjNodes), org_context, __this, node); }

haxorg_HstdVecOfGraphMapEdge haxorg_GraphMapGraph_outEdges_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node) { return org::bind::c::execute_cpp<haxorg_HstdVecOfGraphMapEdge>(static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outEdges), org_context, __this, node); }

haxorg_HstdVecOfGraphMapEdge haxorg_GraphMapGraph_inEdges_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node) { return org::bind::c::execute_cpp<haxorg_HstdVecOfGraphMapEdge>(static_cast<hstd::Vec<org::graph::MapEdge>(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inEdges), org_context, __this, node); }

int haxorg_GraphMapGraph_outDegree_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node) { return org::bind::c::execute_cpp<int>(static_cast<int(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::outDegree), org_context, __this, node); }

int haxorg_GraphMapGraph_inDegree_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node) { return org::bind::c::execute_cpp<int>(static_cast<int(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::inDegree), org_context, __this, node); }

bool haxorg_GraphMapGraph_isRegisteredNode_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode id) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::isRegisteredNode), org_context, __this, id); }

bool haxorg_GraphMapGraph_isRegisteredNodeById_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_ImmUniqId id) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::graph::MapGraph::*)(org::imm::ImmUniqId const&) const>(&org::graph::MapGraph::isRegisteredNode), org_context, __this, id); }

haxorg_GraphMapNodeProp haxorg_GraphMapGraph_atMapNode_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node) { return org::bind::c::execute_cpp<haxorg_GraphMapNodeProp>(static_cast<org::graph::MapNodeProp const&(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::at), org_context, __this, node); }

haxorg_GraphMapEdgeProp haxorg_GraphMapGraph_atMapEdge_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapEdge edge) { return org::bind::c::execute_cpp<haxorg_GraphMapEdgeProp>(static_cast<org::graph::MapEdgeProp const&(org::graph::MapGraph::*)(org::graph::MapEdge const&) const>(&org::graph::MapGraph::at), org_context, __this, edge); }

void haxorg_GraphMapGraph_addEdge(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapEdge edge) { return org::bind::c::execute_cpp<void>(static_cast<void(org::graph::MapGraph::*)(org::graph::MapEdge const&)>(&org::graph::MapGraph::addEdge), org_context, __this, edge); }

void haxorg_GraphMapGraph_addEdgeWithProp(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapEdge edge, haxorg_GraphMapEdgeProp prop) { return org::bind::c::execute_cpp<void>(static_cast<void(org::graph::MapGraph::*)(org::graph::MapEdge const&, org::graph::MapEdgeProp const&)>(&org::graph::MapGraph::addEdge), org_context, __this, edge, prop); }

void haxorg_GraphMapGraph_addNode(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node) { return org::bind::c::execute_cpp<void>(static_cast<void(org::graph::MapGraph::*)(org::graph::MapNode const&)>(&org::graph::MapGraph::addNode), org_context, __this, node); }

void haxorg_GraphMapGraph_addNodeWithProp(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node, haxorg_GraphMapNodeProp prop) { return org::bind::c::execute_cpp<void>(static_cast<void(org::graph::MapGraph::*)(org::graph::MapNode const&, org::graph::MapNodeProp const&)>(&org::graph::MapGraph::addNode), org_context, __this, node, prop); }

bool haxorg_GraphMapGraph_hasEdge_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode source, haxorg_GraphMapNode target) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&, org::graph::MapNode const&) const>(&org::graph::MapGraph::hasEdge), org_context, __this, source, target); }

bool haxorg_GraphMapGraph_hasNode_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_GraphMapNode node) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::graph::MapGraph::*)(org::graph::MapNode const&) const>(&org::graph::MapGraph::hasNode), org_context, __this, node); }

bool haxorg_GraphMapGraph_has2AdapterEdge_const(OrgContext* org_context, haxorg_GraphMapGraph __this, haxorg_ImmAdapter source, haxorg_ImmAdapter target) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::graph::MapGraph::*)(org::imm::ImmAdapter const&, org::imm::ImmAdapter const&) const>(&org::graph::MapGraph::hasEdge), org_context, __this, source, target); }

void haxorg_destroy_GraphMapGraph(OrgContext* org_context, haxorg_GraphMapGraph* obj) { org::bind::c::execute_destroy<org::graph::MapGraph>(org_context, obj); }

haxorg_OperationsTracer haxorg_GraphMapConfig_get_dbg(OrgContext* org_context, haxorg_GraphMapConfig __this) { return org::bind::c::get_cpp_field<haxorg_OperationsTracer, org::graph::MapConfig, hstd::OperationsTracer, haxorg_GraphMapConfig>(org_context, __this, &org::graph::MapConfig::dbg); }

void haxorg_destroy_GraphMapConfig(OrgContext* org_context, haxorg_GraphMapConfig* obj) { org::bind::c::execute_destroy<org::graph::MapConfig>(org_context, obj); }

haxorg_GraphMapGraph haxorg_GraphMapGraphState_get_graph(OrgContext* org_context, haxorg_GraphMapGraphState __this) { return org::bind::c::get_cpp_field<haxorg_GraphMapGraph, org::graph::MapGraphState, std::shared_ptr<org::graph::MapGraph>, haxorg_GraphMapGraphState>(org_context, __this, &org::graph::MapGraphState::graph); }

haxorg_ImmAstContext haxorg_GraphMapGraphState_get_ast(OrgContext* org_context, haxorg_GraphMapGraphState __this) { return org::bind::c::get_cpp_field<haxorg_ImmAstContext, org::graph::MapGraphState, std::shared_ptr<org::imm::ImmAstContext>, haxorg_GraphMapGraphState>(org_context, __this, &org::graph::MapGraphState::ast); }

haxorg_GraphMapGraph haxorg_GraphMapGraphState_getGraph_const(OrgContext* org_context, haxorg_GraphMapGraphState __this) { return org::bind::c::execute_cpp<haxorg_GraphMapGraph>(static_cast<std::shared_ptr<org::graph::MapGraph>(org::graph::MapGraphState::*)() const>(&org::graph::MapGraphState::getGraph), org_context, __this); }

haxorg_GraphMapGraphState haxorg_GraphMapGraphState_FromAstContext(OrgContext* org_context, haxorg_ImmAstContext ast) { return org::bind::c::execute_cpp<haxorg_GraphMapGraphState>(static_cast<std::shared_ptr<org::graph::MapGraphState>(*)(std::shared_ptr<org::imm::ImmAstContext>)>(&org::graph::MapGraphState::FromAstContext), org_context, ast); }

void haxorg_GraphMapGraphState_registerNode(OrgContext* org_context, haxorg_GraphMapGraphState __this, haxorg_GraphMapNodeProp node, haxorg_GraphMapConfig conf) { return org::bind::c::execute_cpp<void>(static_cast<void(org::graph::MapGraphState::*)(org::graph::MapNodeProp const&, std::shared_ptr<org::graph::MapConfig> const&)>(&org::graph::MapGraphState::registerNode), org_context, __this, node, conf); }

void haxorg_GraphMapGraphState_addNode(OrgContext* org_context, haxorg_GraphMapGraphState __this, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf) { return org::bind::c::execute_cpp<void>(static_cast<void(org::graph::MapGraphState::*)(org::imm::ImmAdapter const&, std::shared_ptr<org::graph::MapConfig> const&)>(&org::graph::MapGraphState::addNode), org_context, __this, node, conf); }

void haxorg_GraphMapGraphState_addNodeRec(OrgContext* org_context, haxorg_GraphMapGraphState __this, haxorg_ImmAstContext ast, haxorg_ImmAdapter node, haxorg_GraphMapConfig conf) { return org::bind::c::execute_cpp<void>(static_cast<void(org::graph::MapGraphState::*)(std::shared_ptr<org::imm::ImmAstContext> const&, org::imm::ImmAdapter const&, std::shared_ptr<org::graph::MapConfig> const&)>(&org::graph::MapGraphState::addNodeRec), org_context, __this, ast, node, conf); }

haxorg_HstdVecOfGraphMapLink haxorg_GraphMapGraphState_getUnresolvedSubtreeLinks_const(OrgContext* org_context, haxorg_GraphMapGraphState __this, haxorg_ImmSubtreeAdapter node, haxorg_GraphMapConfig conf) { return org::bind::c::execute_cpp<haxorg_HstdVecOfGraphMapLink>(static_cast<hstd::Vec<org::graph::MapLink>(org::graph::MapGraphState::*)(org::imm::ImmAdapterT<org::imm::ImmSubtree>, std::shared_ptr<org::graph::MapConfig> const&) const>(&org::graph::MapGraphState::getUnresolvedSubtreeLinks), org_context, __this, node, conf); }

haxorg_StdOptional haxorg_GraphMapGraphState_getUnresolvedLink_const(OrgContext* org_context, haxorg_GraphMapGraphState __this, haxorg_ImmLinkAdapter node, haxorg_GraphMapConfig conf) { return org::bind::c::execute_cpp<haxorg_StdOptional>(static_cast<std::optional<org::graph::MapLink>(org::graph::MapGraphState::*)(org::imm::ImmAdapterT<org::imm::ImmLink>, std::shared_ptr<org::graph::MapConfig> const&) const>(&org::graph::MapGraphState::getUnresolvedLink), org_context, __this, node, conf); }

void haxorg_destroy_GraphMapGraphState(OrgContext* org_context, haxorg_GraphMapGraphState* obj) { org::bind::c::execute_destroy<org::graph::MapGraphState>(org_context, obj); }

void haxorg_create_LispCode_LispCode(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::LispCode { return org::sem::LispCode(); }, org_context); }

bool haxorg_LispCode___eq___const(OrgContext* org_context, haxorg_LispCode __this, haxorg_LispCode other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::*)(org::sem::LispCode const&) const>(&org::sem::LispCode::operator==), org_context, __this, other); }

bool haxorg_LispCode_isCall_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isCall), org_context, __this); }

haxorg_LispCodeCall haxorg_LispCode_getCallConst_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeCall>(static_cast<org::sem::LispCode::Call const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getCall), org_context, __this); }

haxorg_LispCodeCall haxorg_LispCode_getCallMut(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeCall>(static_cast<org::sem::LispCode::Call&(org::sem::LispCode::*)()>(&org::sem::LispCode::getCall), org_context, __this); }

bool haxorg_LispCode_isList_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isList), org_context, __this); }

haxorg_LispCodeList haxorg_LispCode_getListConst_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeList>(static_cast<org::sem::LispCode::List const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getList), org_context, __this); }

haxorg_LispCodeList haxorg_LispCode_getListMut(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeList>(static_cast<org::sem::LispCode::List&(org::sem::LispCode::*)()>(&org::sem::LispCode::getList), org_context, __this); }

bool haxorg_LispCode_isKeyValue_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isKeyValue), org_context, __this); }

haxorg_LispCodeKeyValue haxorg_LispCode_getKeyValueConst_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeKeyValue>(static_cast<org::sem::LispCode::KeyValue const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getKeyValue), org_context, __this); }

haxorg_LispCodeKeyValue haxorg_LispCode_getKeyValueMut(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeKeyValue>(static_cast<org::sem::LispCode::KeyValue&(org::sem::LispCode::*)()>(&org::sem::LispCode::getKeyValue), org_context, __this); }

bool haxorg_LispCode_isNumber_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isNumber), org_context, __this); }

haxorg_LispCodeNumber haxorg_LispCode_getNumberConst_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeNumber>(static_cast<org::sem::LispCode::Number const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getNumber), org_context, __this); }

haxorg_LispCodeNumber haxorg_LispCode_getNumberMut(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeNumber>(static_cast<org::sem::LispCode::Number&(org::sem::LispCode::*)()>(&org::sem::LispCode::getNumber), org_context, __this); }

bool haxorg_LispCode_isText_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isText), org_context, __this); }

haxorg_LispCodeText haxorg_LispCode_getTextConst_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeText>(static_cast<org::sem::LispCode::Text const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getText), org_context, __this); }

haxorg_LispCodeText haxorg_LispCode_getTextMut(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeText>(static_cast<org::sem::LispCode::Text&(org::sem::LispCode::*)()>(&org::sem::LispCode::getText), org_context, __this); }

bool haxorg_LispCode_isIdent_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isIdent), org_context, __this); }

haxorg_LispCodeIdent haxorg_LispCode_getIdentConst_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeIdent>(static_cast<org::sem::LispCode::Ident const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getIdent), org_context, __this); }

haxorg_LispCodeIdent haxorg_LispCode_getIdentMut(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeIdent>(static_cast<org::sem::LispCode::Ident&(org::sem::LispCode::*)()>(&org::sem::LispCode::getIdent), org_context, __this); }

bool haxorg_LispCode_isBoolean_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isBoolean), org_context, __this); }

haxorg_LispCodeBoolean haxorg_LispCode_getBooleanConst_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeBoolean>(static_cast<org::sem::LispCode::Boolean const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getBoolean), org_context, __this); }

haxorg_LispCodeBoolean haxorg_LispCode_getBooleanMut(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeBoolean>(static_cast<org::sem::LispCode::Boolean&(org::sem::LispCode::*)()>(&org::sem::LispCode::getBoolean), org_context, __this); }

bool haxorg_LispCode_isReal_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isReal), org_context, __this); }

haxorg_LispCodeReal haxorg_LispCode_getRealConst_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeReal>(static_cast<org::sem::LispCode::Real const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getReal), org_context, __this); }

haxorg_LispCodeReal haxorg_LispCode_getRealMut(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeReal>(static_cast<org::sem::LispCode::Real&(org::sem::LispCode::*)()>(&org::sem::LispCode::getReal), org_context, __this); }

haxorg_LispCodeKind haxorg_LispCode_getKind_const(OrgContext* org_context, haxorg_LispCode __this) { return org::bind::c::execute_cpp<haxorg_LispCodeKind>(static_cast<org::sem::LispCode::Kind(org::sem::LispCode::*)() const>(&org::sem::LispCode::getKind), org_context, __this); }

haxorg_HstdStr haxorg_LispCodeCall_get_name(OrgContext* org_context, haxorg_LispCodeCall __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::LispCode::Call, hstd::Str, haxorg_LispCodeCall>(org_context, __this, &org::sem::LispCode::Call::name); }

haxorg_HstdVecOfLispCode haxorg_LispCodeCall_get_args(OrgContext* org_context, haxorg_LispCodeCall __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfLispCode, org::sem::LispCode::Call, hstd::Vec<org::sem::LispCode>, haxorg_LispCodeCall>(org_context, __this, &org::sem::LispCode::Call::args); }

void haxorg_create_LispCodeCall_Call(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::LispCode::Call { return org::sem::LispCode::Call(); }, org_context); }

bool haxorg_LispCodeCall___eq___const(OrgContext* org_context, haxorg_LispCodeCall __this, haxorg_LispCodeCall other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::Call::*)(org::sem::LispCode::Call const&) const>(&org::sem::LispCode::Call::operator==), org_context, __this, other); }

void haxorg_destroy_LispCodeCall(OrgContext* org_context, haxorg_LispCodeCall* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Call>(org_context, obj); }

haxorg_HstdVecOfLispCode haxorg_LispCodeList_get_items(OrgContext* org_context, haxorg_LispCodeList __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfLispCode, org::sem::LispCode::List, hstd::Vec<org::sem::LispCode>, haxorg_LispCodeList>(org_context, __this, &org::sem::LispCode::List::items); }

void haxorg_create_LispCodeList_List(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::LispCode::List { return org::sem::LispCode::List(); }, org_context); }

bool haxorg_LispCodeList___eq___const(OrgContext* org_context, haxorg_LispCodeList __this, haxorg_LispCodeList other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::List::*)(org::sem::LispCode::List const&) const>(&org::sem::LispCode::List::operator==), org_context, __this, other); }

void haxorg_destroy_LispCodeList(OrgContext* org_context, haxorg_LispCodeList* obj) { org::bind::c::execute_destroy<org::sem::LispCode::List>(org_context, obj); }

haxorg_HstdStr haxorg_LispCodeKeyValue_get_name(OrgContext* org_context, haxorg_LispCodeKeyValue __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::LispCode::KeyValue, hstd::Str, haxorg_LispCodeKeyValue>(org_context, __this, &org::sem::LispCode::KeyValue::name); }

haxorg_HstdVecOfLispCode haxorg_LispCodeKeyValue_get_value(OrgContext* org_context, haxorg_LispCodeKeyValue __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfLispCode, org::sem::LispCode::KeyValue, hstd::Vec<org::sem::LispCode>, haxorg_LispCodeKeyValue>(org_context, __this, &org::sem::LispCode::KeyValue::value); }

void haxorg_create_LispCodeKeyValue_KeyValue(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::LispCode::KeyValue { return org::sem::LispCode::KeyValue(); }, org_context); }

bool haxorg_LispCodeKeyValue___eq___const(OrgContext* org_context, haxorg_LispCodeKeyValue __this, haxorg_LispCodeKeyValue other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::KeyValue::*)(org::sem::LispCode::KeyValue const&) const>(&org::sem::LispCode::KeyValue::operator==), org_context, __this, other); }

void haxorg_destroy_LispCodeKeyValue(OrgContext* org_context, haxorg_LispCodeKeyValue* obj) { org::bind::c::execute_destroy<org::sem::LispCode::KeyValue>(org_context, obj); }

int haxorg_LispCodeNumber_get_value(OrgContext* org_context, haxorg_LispCodeNumber __this) { return org::bind::c::get_cpp_field<int, org::sem::LispCode::Number, int, haxorg_LispCodeNumber>(org_context, __this, &org::sem::LispCode::Number::value); }

void haxorg_create_LispCodeNumber_Number(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::LispCode::Number { return org::sem::LispCode::Number(); }, org_context); }

bool haxorg_LispCodeNumber___eq___const(OrgContext* org_context, haxorg_LispCodeNumber __this, haxorg_LispCodeNumber other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::Number::*)(org::sem::LispCode::Number const&) const>(&org::sem::LispCode::Number::operator==), org_context, __this, other); }

void haxorg_destroy_LispCodeNumber(OrgContext* org_context, haxorg_LispCodeNumber* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Number>(org_context, obj); }

haxorg_HstdStr haxorg_LispCodeText_get_value(OrgContext* org_context, haxorg_LispCodeText __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::LispCode::Text, hstd::Str, haxorg_LispCodeText>(org_context, __this, &org::sem::LispCode::Text::value); }

void haxorg_create_LispCodeText_Text(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::LispCode::Text { return org::sem::LispCode::Text(); }, org_context); }

bool haxorg_LispCodeText___eq___const(OrgContext* org_context, haxorg_LispCodeText __this, haxorg_LispCodeText other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::Text::*)(org::sem::LispCode::Text const&) const>(&org::sem::LispCode::Text::operator==), org_context, __this, other); }

void haxorg_destroy_LispCodeText(OrgContext* org_context, haxorg_LispCodeText* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Text>(org_context, obj); }

haxorg_HstdStr haxorg_LispCodeIdent_get_name(OrgContext* org_context, haxorg_LispCodeIdent __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::LispCode::Ident, hstd::Str, haxorg_LispCodeIdent>(org_context, __this, &org::sem::LispCode::Ident::name); }

void haxorg_create_LispCodeIdent_Ident(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::LispCode::Ident { return org::sem::LispCode::Ident(); }, org_context); }

bool haxorg_LispCodeIdent___eq___const(OrgContext* org_context, haxorg_LispCodeIdent __this, haxorg_LispCodeIdent other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::Ident::*)(org::sem::LispCode::Ident const&) const>(&org::sem::LispCode::Ident::operator==), org_context, __this, other); }

void haxorg_destroy_LispCodeIdent(OrgContext* org_context, haxorg_LispCodeIdent* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Ident>(org_context, obj); }

bool haxorg_LispCodeBoolean_get_value(OrgContext* org_context, haxorg_LispCodeBoolean __this) { return org::bind::c::get_cpp_field<bool, org::sem::LispCode::Boolean, bool, haxorg_LispCodeBoolean>(org_context, __this, &org::sem::LispCode::Boolean::value); }

void haxorg_create_LispCodeBoolean_Boolean(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::LispCode::Boolean { return org::sem::LispCode::Boolean(); }, org_context); }

bool haxorg_LispCodeBoolean___eq___const(OrgContext* org_context, haxorg_LispCodeBoolean __this, haxorg_LispCodeBoolean other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::Boolean::*)(org::sem::LispCode::Boolean const&) const>(&org::sem::LispCode::Boolean::operator==), org_context, __this, other); }

void haxorg_destroy_LispCodeBoolean(OrgContext* org_context, haxorg_LispCodeBoolean* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Boolean>(org_context, obj); }

float haxorg_LispCodeReal_get_value(OrgContext* org_context, haxorg_LispCodeReal __this) { return org::bind::c::get_cpp_field<float, org::sem::LispCode::Real, float, haxorg_LispCodeReal>(org_context, __this, &org::sem::LispCode::Real::value); }

void haxorg_create_LispCodeReal_Real(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::LispCode::Real { return org::sem::LispCode::Real(); }, org_context); }

bool haxorg_LispCodeReal___eq___const(OrgContext* org_context, haxorg_LispCodeReal __this, haxorg_LispCodeReal other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LispCode::Real::*)(org::sem::LispCode::Real const&) const>(&org::sem::LispCode::Real::operator==), org_context, __this, other); }

void haxorg_destroy_LispCodeReal(OrgContext* org_context, haxorg_LispCodeReal* obj) { org::bind::c::execute_destroy<org::sem::LispCode::Real>(org_context, obj); }

void haxorg_destroy_LispCode(OrgContext* org_context, haxorg_LispCode* obj) { org::bind::c::execute_destroy<org::sem::LispCode>(org_context, obj); }

haxorg_HstdVecOfTblfmAssign haxorg_Tblfm_get_exprs(OrgContext* org_context, haxorg_Tblfm __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfTblfmAssign, org::sem::Tblfm, hstd::Vec<org::sem::Tblfm::Assign>, haxorg_Tblfm>(org_context, __this, &org::sem::Tblfm::exprs); }

bool haxorg_Tblfm___eq___const(OrgContext* org_context, haxorg_Tblfm __this, haxorg_Tblfm other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::*)(org::sem::Tblfm const&) const>(&org::sem::Tblfm::operator==), org_context, __this, other); }

bool haxorg_TblfmExpr___eq___const(OrgContext* org_context, haxorg_TblfmExpr __this, haxorg_TblfmExpr other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::*)(org::sem::Tblfm::Expr const&) const>(&org::sem::Tblfm::Expr::operator==), org_context, __this, other); }

bool haxorg_TblfmExpr_isAxisRef_const(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isAxisRef), org_context, __this); }

haxorg_TblfmExprAxisRef haxorg_TblfmExpr_getAxisRefConst_const(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRef>(static_cast<org::sem::Tblfm::Expr::AxisRef const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getAxisRef), org_context, __this); }

haxorg_TblfmExprAxisRef haxorg_TblfmExpr_getAxisRefMut(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRef>(static_cast<org::sem::Tblfm::Expr::AxisRef&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getAxisRef), org_context, __this); }

bool haxorg_TblfmExpr_isAxisName_const(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isAxisName), org_context, __this); }

haxorg_TblfmExprAxisName haxorg_TblfmExpr_getAxisNameConst_const(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisName>(static_cast<org::sem::Tblfm::Expr::AxisName const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getAxisName), org_context, __this); }

haxorg_TblfmExprAxisName haxorg_TblfmExpr_getAxisNameMut(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisName>(static_cast<org::sem::Tblfm::Expr::AxisName&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getAxisName), org_context, __this); }

bool haxorg_TblfmExpr_isIntLiteral_const(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isIntLiteral), org_context, __this); }

haxorg_TblfmExprIntLiteral haxorg_TblfmExpr_getIntLiteralConst_const(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprIntLiteral>(static_cast<org::sem::Tblfm::Expr::IntLiteral const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getIntLiteral), org_context, __this); }

haxorg_TblfmExprIntLiteral haxorg_TblfmExpr_getIntLiteralMut(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprIntLiteral>(static_cast<org::sem::Tblfm::Expr::IntLiteral&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getIntLiteral), org_context, __this); }

bool haxorg_TblfmExpr_isFloatLiteral_const(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isFloatLiteral), org_context, __this); }

haxorg_TblfmExprFloatLiteral haxorg_TblfmExpr_getFloatLiteralConst_const(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprFloatLiteral>(static_cast<org::sem::Tblfm::Expr::FloatLiteral const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getFloatLiteral), org_context, __this); }

haxorg_TblfmExprFloatLiteral haxorg_TblfmExpr_getFloatLiteralMut(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprFloatLiteral>(static_cast<org::sem::Tblfm::Expr::FloatLiteral&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getFloatLiteral), org_context, __this); }

bool haxorg_TblfmExpr_isRangeRef_const(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isRangeRef), org_context, __this); }

haxorg_TblfmExprRangeRef haxorg_TblfmExpr_getRangeRefConst_const(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprRangeRef>(static_cast<org::sem::Tblfm::Expr::RangeRef const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getRangeRef), org_context, __this); }

haxorg_TblfmExprRangeRef haxorg_TblfmExpr_getRangeRefMut(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprRangeRef>(static_cast<org::sem::Tblfm::Expr::RangeRef&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getRangeRef), org_context, __this); }

bool haxorg_TblfmExpr_isCall_const(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isCall), org_context, __this); }

haxorg_TblfmExprCall haxorg_TblfmExpr_getCallConst_const(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprCall>(static_cast<org::sem::Tblfm::Expr::Call const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getCall), org_context, __this); }

haxorg_TblfmExprCall haxorg_TblfmExpr_getCallMut(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprCall>(static_cast<org::sem::Tblfm::Expr::Call&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getCall), org_context, __this); }

bool haxorg_TblfmExpr_isElisp_const(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isElisp), org_context, __this); }

haxorg_TblfmExprElisp haxorg_TblfmExpr_getElispConst_const(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprElisp>(static_cast<org::sem::Tblfm::Expr::Elisp const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getElisp), org_context, __this); }

haxorg_TblfmExprElisp haxorg_TblfmExpr_getElispMut(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprElisp>(static_cast<org::sem::Tblfm::Expr::Elisp&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getElisp), org_context, __this); }

haxorg_TblfmExprKind haxorg_TblfmExpr_getKind_const(OrgContext* org_context, haxorg_TblfmExpr __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprKind>(static_cast<org::sem::Tblfm::Expr::Kind(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getKind), org_context, __this); }

haxorg_TblfmExprAxisRefPosition haxorg_TblfmExprAxisRef_get_col(OrgContext* org_context, haxorg_TblfmExprAxisRef __this) { return org::bind::c::get_cpp_field<haxorg_TblfmExprAxisRefPosition, org::sem::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisRef::Position, haxorg_TblfmExprAxisRef>(org_context, __this, &org::sem::Tblfm::Expr::AxisRef::col); }

haxorg_OptOfTblfmExprAxisRefPosition haxorg_TblfmExprAxisRef_get_row(OrgContext* org_context, haxorg_TblfmExprAxisRef __this) { return org::bind::c::get_cpp_field<haxorg_OptOfTblfmExprAxisRefPosition, org::sem::Tblfm::Expr::AxisRef, hstd::Opt<org::sem::Tblfm::Expr::AxisRef::Position>, haxorg_TblfmExprAxisRef>(org_context, __this, &org::sem::Tblfm::Expr::AxisRef::row); }

bool haxorg_TblfmExprAxisRef___eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRef __this, haxorg_TblfmExprAxisRef other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::*)(org::sem::Tblfm::Expr::AxisRef const&) const>(&org::sem::Tblfm::Expr::AxisRef::operator==), org_context, __this, other); }

void haxorg_create_TblfmExprAxisRefPosition_Position(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::Tblfm::Expr::AxisRef::Position { return org::sem::Tblfm::Expr::AxisRef::Position(); }, org_context); }

bool haxorg_TblfmExprAxisRefPosition___eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition __this, haxorg_TblfmExprAxisRefPosition other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)(org::sem::Tblfm::Expr::AxisRef::Position const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::operator==), org_context, __this, other); }

bool haxorg_TblfmExprAxisRefPosition_isIndex_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::isIndex), org_context, __this); }

haxorg_TblfmExprAxisRefPositionIndex haxorg_TblfmExprAxisRefPosition_getIndexConst_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionIndex>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Index const&(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getIndex), org_context, __this); }

haxorg_TblfmExprAxisRefPositionIndex haxorg_TblfmExprAxisRefPosition_getIndexMut(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionIndex>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Index&(org::sem::Tblfm::Expr::AxisRef::Position::*)()>(&org::sem::Tblfm::Expr::AxisRef::Position::getIndex), org_context, __this); }

bool haxorg_TblfmExprAxisRefPosition_isName_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::isName), org_context, __this); }

haxorg_TblfmExprAxisRefPositionName haxorg_TblfmExprAxisRefPosition_getNameConst_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionName>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Name const&(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getName), org_context, __this); }

haxorg_TblfmExprAxisRefPositionName haxorg_TblfmExprAxisRefPosition_getNameMut(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionName>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Name&(org::sem::Tblfm::Expr::AxisRef::Position::*)()>(&org::sem::Tblfm::Expr::AxisRef::Position::getName), org_context, __this); }

haxorg_TblfmExprAxisRefPositionKind haxorg_TblfmExprAxisRefPosition_getKind_const(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition __this) { return org::bind::c::execute_cpp<haxorg_TblfmExprAxisRefPositionKind>(static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getKind), org_context, __this); }

int haxorg_TblfmExprAxisRefPositionIndex_get_index(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionIndex __this) { return org::bind::c::get_cpp_field<int, org::sem::Tblfm::Expr::AxisRef::Position::Index, int, haxorg_TblfmExprAxisRefPositionIndex>(org_context, __this, &org::sem::Tblfm::Expr::AxisRef::Position::Index::index); }

void haxorg_create_TblfmExprAxisRefPositionIndex_Index(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::Tblfm::Expr::AxisRef::Position::Index { return org::sem::Tblfm::Expr::AxisRef::Position::Index(); }, org_context); }

bool haxorg_TblfmExprAxisRefPositionIndex___eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionIndex __this, haxorg_TblfmExprAxisRefPositionIndex other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::Index::*)(org::sem::Tblfm::Expr::AxisRef::Position::Index const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::Index::operator==), org_context, __this, other); }

void haxorg_destroy_TblfmExprAxisRefPositionIndex(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionIndex* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisRef::Position::Index>(org_context, obj); }

haxorg_HstdStr haxorg_TblfmExprAxisRefPositionName_get_name(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionName __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::Tblfm::Expr::AxisRef::Position::Name, hstd::Str, haxorg_TblfmExprAxisRefPositionName>(org_context, __this, &org::sem::Tblfm::Expr::AxisRef::Position::Name::name); }

void haxorg_create_TblfmExprAxisRefPositionName_Name(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::Tblfm::Expr::AxisRef::Position::Name { return org::sem::Tblfm::Expr::AxisRef::Position::Name(); }, org_context); }

bool haxorg_TblfmExprAxisRefPositionName___eq___const(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionName __this, haxorg_TblfmExprAxisRefPositionName other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::Name::*)(org::sem::Tblfm::Expr::AxisRef::Position::Name const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::Name::operator==), org_context, __this, other); }

void haxorg_destroy_TblfmExprAxisRefPositionName(OrgContext* org_context, haxorg_TblfmExprAxisRefPositionName* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisRef::Position::Name>(org_context, obj); }

void haxorg_destroy_TblfmExprAxisRefPosition(OrgContext* org_context, haxorg_TblfmExprAxisRefPosition* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisRef::Position>(org_context, obj); }

void haxorg_destroy_TblfmExprAxisRef(OrgContext* org_context, haxorg_TblfmExprAxisRef* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisRef>(org_context, obj); }

haxorg_HstdStr haxorg_TblfmExprAxisName_get_name(OrgContext* org_context, haxorg_TblfmExprAxisName __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::Tblfm::Expr::AxisName, hstd::Str, haxorg_TblfmExprAxisName>(org_context, __this, &org::sem::Tblfm::Expr::AxisName::name); }

bool haxorg_TblfmExprAxisName___eq___const(OrgContext* org_context, haxorg_TblfmExprAxisName __this, haxorg_TblfmExprAxisName other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::AxisName::*)(org::sem::Tblfm::Expr::AxisName const&) const>(&org::sem::Tblfm::Expr::AxisName::operator==), org_context, __this, other); }

void haxorg_destroy_TblfmExprAxisName(OrgContext* org_context, haxorg_TblfmExprAxisName* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::AxisName>(org_context, obj); }

int haxorg_TblfmExprIntLiteral_get_value(OrgContext* org_context, haxorg_TblfmExprIntLiteral __this) { return org::bind::c::get_cpp_field<int, org::sem::Tblfm::Expr::IntLiteral, int, haxorg_TblfmExprIntLiteral>(org_context, __this, &org::sem::Tblfm::Expr::IntLiteral::value); }

bool haxorg_TblfmExprIntLiteral___eq___const(OrgContext* org_context, haxorg_TblfmExprIntLiteral __this, haxorg_TblfmExprIntLiteral other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::IntLiteral::*)(org::sem::Tblfm::Expr::IntLiteral const&) const>(&org::sem::Tblfm::Expr::IntLiteral::operator==), org_context, __this, other); }

void haxorg_destroy_TblfmExprIntLiteral(OrgContext* org_context, haxorg_TblfmExprIntLiteral* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::IntLiteral>(org_context, obj); }

float haxorg_TblfmExprFloatLiteral_get_value(OrgContext* org_context, haxorg_TblfmExprFloatLiteral __this) { return org::bind::c::get_cpp_field<float, org::sem::Tblfm::Expr::FloatLiteral, float, haxorg_TblfmExprFloatLiteral>(org_context, __this, &org::sem::Tblfm::Expr::FloatLiteral::value); }

bool haxorg_TblfmExprFloatLiteral___eq___const(OrgContext* org_context, haxorg_TblfmExprFloatLiteral __this, haxorg_TblfmExprFloatLiteral other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::FloatLiteral::*)(org::sem::Tblfm::Expr::FloatLiteral const&) const>(&org::sem::Tblfm::Expr::FloatLiteral::operator==), org_context, __this, other); }

void haxorg_destroy_TblfmExprFloatLiteral(OrgContext* org_context, haxorg_TblfmExprFloatLiteral* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::FloatLiteral>(org_context, obj); }

haxorg_OptOfTblfmExprAxisRef haxorg_TblfmExprRangeRef_get_first(OrgContext* org_context, haxorg_TblfmExprRangeRef __this) { return org::bind::c::get_cpp_field<haxorg_OptOfTblfmExprAxisRef, org::sem::Tblfm::Expr::RangeRef, hstd::Opt<org::sem::Tblfm::Expr::AxisRef>, haxorg_TblfmExprRangeRef>(org_context, __this, &org::sem::Tblfm::Expr::RangeRef::first); }

haxorg_OptOfTblfmExprAxisRef haxorg_TblfmExprRangeRef_get_last(OrgContext* org_context, haxorg_TblfmExprRangeRef __this) { return org::bind::c::get_cpp_field<haxorg_OptOfTblfmExprAxisRef, org::sem::Tblfm::Expr::RangeRef, hstd::Opt<org::sem::Tblfm::Expr::AxisRef>, haxorg_TblfmExprRangeRef>(org_context, __this, &org::sem::Tblfm::Expr::RangeRef::last); }

bool haxorg_TblfmExprRangeRef___eq___const(OrgContext* org_context, haxorg_TblfmExprRangeRef __this, haxorg_TblfmExprRangeRef other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::RangeRef::*)(org::sem::Tblfm::Expr::RangeRef const&) const>(&org::sem::Tblfm::Expr::RangeRef::operator==), org_context, __this, other); }

void haxorg_destroy_TblfmExprRangeRef(OrgContext* org_context, haxorg_TblfmExprRangeRef* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::RangeRef>(org_context, obj); }

haxorg_HstdStr haxorg_TblfmExprCall_get_name(OrgContext* org_context, haxorg_TblfmExprCall __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::Tblfm::Expr::Call, hstd::Str, haxorg_TblfmExprCall>(org_context, __this, &org::sem::Tblfm::Expr::Call::name); }

haxorg_HstdVecOfTblfmExpr haxorg_TblfmExprCall_get_args(OrgContext* org_context, haxorg_TblfmExprCall __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfTblfmExpr, org::sem::Tblfm::Expr::Call, hstd::Vec<org::sem::Tblfm::Expr>, haxorg_TblfmExprCall>(org_context, __this, &org::sem::Tblfm::Expr::Call::args); }

bool haxorg_TblfmExprCall___eq___const(OrgContext* org_context, haxorg_TblfmExprCall __this, haxorg_TblfmExprCall other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::Call::*)(org::sem::Tblfm::Expr::Call const&) const>(&org::sem::Tblfm::Expr::Call::operator==), org_context, __this, other); }

void haxorg_destroy_TblfmExprCall(OrgContext* org_context, haxorg_TblfmExprCall* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::Call>(org_context, obj); }

haxorg_HstdStr haxorg_TblfmExprElisp_get_value(OrgContext* org_context, haxorg_TblfmExprElisp __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::Tblfm::Expr::Elisp, hstd::Str, haxorg_TblfmExprElisp>(org_context, __this, &org::sem::Tblfm::Expr::Elisp::value); }

bool haxorg_TblfmExprElisp___eq___const(OrgContext* org_context, haxorg_TblfmExprElisp __this, haxorg_TblfmExprElisp other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Expr::Elisp::*)(org::sem::Tblfm::Expr::Elisp const&) const>(&org::sem::Tblfm::Expr::Elisp::operator==), org_context, __this, other); }

void haxorg_destroy_TblfmExprElisp(OrgContext* org_context, haxorg_TblfmExprElisp* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr::Elisp>(org_context, obj); }

void haxorg_destroy_TblfmExpr(OrgContext* org_context, haxorg_TblfmExpr* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Expr>(org_context, obj); }

haxorg_TblfmExprAxisRef haxorg_TblfmAssign_get_target(OrgContext* org_context, haxorg_TblfmAssign __this) { return org::bind::c::get_cpp_field<haxorg_TblfmExprAxisRef, org::sem::Tblfm::Assign, org::sem::Tblfm::Expr::AxisRef, haxorg_TblfmAssign>(org_context, __this, &org::sem::Tblfm::Assign::target); }

haxorg_HstdVecOfTblfmExpr haxorg_TblfmAssign_get_expr(OrgContext* org_context, haxorg_TblfmAssign __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfTblfmExpr, org::sem::Tblfm::Assign, hstd::Vec<org::sem::Tblfm::Expr>, haxorg_TblfmAssign>(org_context, __this, &org::sem::Tblfm::Assign::expr); }

haxorg_HstdVecOfTblfmAssignFlag haxorg_TblfmAssign_get_flags(OrgContext* org_context, haxorg_TblfmAssign __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfTblfmAssignFlag, org::sem::Tblfm::Assign, hstd::Vec<org::sem::Tblfm::Assign::Flag>, haxorg_TblfmAssign>(org_context, __this, &org::sem::Tblfm::Assign::flags); }

bool haxorg_TblfmAssign___eq___const(OrgContext* org_context, haxorg_TblfmAssign __this, haxorg_TblfmAssign other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Tblfm::Assign::*)(org::sem::Tblfm::Assign const&) const>(&org::sem::Tblfm::Assign::operator==), org_context, __this, other); }

void haxorg_destroy_TblfmAssign(OrgContext* org_context, haxorg_TblfmAssign* obj) { org::bind::c::execute_destroy<org::sem::Tblfm::Assign>(org_context, obj); }

void haxorg_destroy_Tblfm(OrgContext* org_context, haxorg_Tblfm* obj) { org::bind::c::execute_destroy<org::sem::Tblfm>(org_context, obj); }

haxorg_OptOfStr haxorg_AttrValue_get_name(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::AttrValue, hstd::Opt<hstd::Str>, haxorg_AttrValue>(org_context, __this, &org::sem::AttrValue::name); }

haxorg_OptOfStr haxorg_AttrValue_get_varname(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::AttrValue, hstd::Opt<hstd::Str>, haxorg_AttrValue>(org_context, __this, &org::sem::AttrValue::varname); }

haxorg_HstdVecOfAttrValueDimensionSpan haxorg_AttrValue_get_span(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfAttrValueDimensionSpan, org::sem::AttrValue, hstd::Vec<org::sem::AttrValue::DimensionSpan>, haxorg_AttrValue>(org_context, __this, &org::sem::AttrValue::span); }

bool haxorg_AttrValue_get_isQuoted(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::get_cpp_field<bool, org::sem::AttrValue, bool, haxorg_AttrValue>(org_context, __this, &org::sem::AttrValue::isQuoted); }

haxorg_OptOfBool haxorg_AttrValue_getBool_const(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::execute_cpp<haxorg_OptOfBool>(static_cast<hstd::Opt<bool>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getBool), org_context, __this); }

haxorg_OptOfInt haxorg_AttrValue_getInt_const(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::execute_cpp<haxorg_OptOfInt>(static_cast<hstd::Opt<int>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getInt), org_context, __this); }

haxorg_HstdStr haxorg_AttrValue_getString_const(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getString), org_context, __this); }

haxorg_OptOfDouble haxorg_AttrValue_getDouble_const(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::execute_cpp<haxorg_OptOfDouble>(static_cast<hstd::Opt<double>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getDouble), org_context, __this); }

void haxorg_create_AttrValue_AttrValue(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::AttrValue { return org::sem::AttrValue(); }, org_context); }

bool haxorg_AttrValue___eq___const(OrgContext* org_context, haxorg_AttrValue __this, haxorg_AttrValue other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::AttrValue::*)(org::sem::AttrValue const&) const>(&org::sem::AttrValue::operator==), org_context, __this, other); }

bool haxorg_AttrValue_isTextValue_const(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isTextValue), org_context, __this); }

haxorg_AttrValueTextValue haxorg_AttrValue_getTextValueConst_const(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::execute_cpp<haxorg_AttrValueTextValue>(static_cast<org::sem::AttrValue::TextValue const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getTextValue), org_context, __this); }

haxorg_AttrValueTextValue haxorg_AttrValue_getTextValueMut(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::execute_cpp<haxorg_AttrValueTextValue>(static_cast<org::sem::AttrValue::TextValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getTextValue), org_context, __this); }

bool haxorg_AttrValue_isFileReference_const(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isFileReference), org_context, __this); }

haxorg_AttrValueFileReference haxorg_AttrValue_getFileReferenceConst_const(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::execute_cpp<haxorg_AttrValueFileReference>(static_cast<org::sem::AttrValue::FileReference const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getFileReference), org_context, __this); }

haxorg_AttrValueFileReference haxorg_AttrValue_getFileReferenceMut(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::execute_cpp<haxorg_AttrValueFileReference>(static_cast<org::sem::AttrValue::FileReference&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getFileReference), org_context, __this); }

bool haxorg_AttrValue_isLispValue_const(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isLispValue), org_context, __this); }

haxorg_AttrValueLispValue haxorg_AttrValue_getLispValueConst_const(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::execute_cpp<haxorg_AttrValueLispValue>(static_cast<org::sem::AttrValue::LispValue const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getLispValue), org_context, __this); }

haxorg_AttrValueLispValue haxorg_AttrValue_getLispValueMut(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::execute_cpp<haxorg_AttrValueLispValue>(static_cast<org::sem::AttrValue::LispValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getLispValue), org_context, __this); }

haxorg_AttrValueKind haxorg_AttrValue_getKind_const(OrgContext* org_context, haxorg_AttrValue __this) { return org::bind::c::execute_cpp<haxorg_AttrValueKind>(static_cast<org::sem::AttrValue::Kind(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getKind), org_context, __this); }

int haxorg_AttrValueDimensionSpan_get_first(OrgContext* org_context, haxorg_AttrValueDimensionSpan __this) { return org::bind::c::get_cpp_field<int, org::sem::AttrValue::DimensionSpan, int, haxorg_AttrValueDimensionSpan>(org_context, __this, &org::sem::AttrValue::DimensionSpan::first); }

haxorg_OptOfInt haxorg_AttrValueDimensionSpan_get_last(OrgContext* org_context, haxorg_AttrValueDimensionSpan __this) { return org::bind::c::get_cpp_field<haxorg_OptOfInt, org::sem::AttrValue::DimensionSpan, hstd::Opt<int>, haxorg_AttrValueDimensionSpan>(org_context, __this, &org::sem::AttrValue::DimensionSpan::last); }

void haxorg_create_AttrValueDimensionSpan_DimensionSpan(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::AttrValue::DimensionSpan { return org::sem::AttrValue::DimensionSpan(); }, org_context); }

bool haxorg_AttrValueDimensionSpan___eq___const(OrgContext* org_context, haxorg_AttrValueDimensionSpan __this, haxorg_AttrValueDimensionSpan other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::AttrValue::DimensionSpan::*)(org::sem::AttrValue::DimensionSpan const&) const>(&org::sem::AttrValue::DimensionSpan::operator==), org_context, __this, other); }

void haxorg_destroy_AttrValueDimensionSpan(OrgContext* org_context, haxorg_AttrValueDimensionSpan* obj) { org::bind::c::execute_destroy<org::sem::AttrValue::DimensionSpan>(org_context, obj); }

haxorg_HstdStr haxorg_AttrValueTextValue_get_value(OrgContext* org_context, haxorg_AttrValueTextValue __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::AttrValue::TextValue, hstd::Str, haxorg_AttrValueTextValue>(org_context, __this, &org::sem::AttrValue::TextValue::value); }

void haxorg_create_AttrValueTextValue_TextValue(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::AttrValue::TextValue { return org::sem::AttrValue::TextValue(); }, org_context); }

bool haxorg_AttrValueTextValue___eq___const(OrgContext* org_context, haxorg_AttrValueTextValue __this, haxorg_AttrValueTextValue other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::AttrValue::TextValue::*)(org::sem::AttrValue::TextValue const&) const>(&org::sem::AttrValue::TextValue::operator==), org_context, __this, other); }

void haxorg_destroy_AttrValueTextValue(OrgContext* org_context, haxorg_AttrValueTextValue* obj) { org::bind::c::execute_destroy<org::sem::AttrValue::TextValue>(org_context, obj); }

haxorg_HstdStr haxorg_AttrValueFileReference_get_file(OrgContext* org_context, haxorg_AttrValueFileReference __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::AttrValue::FileReference, hstd::Str, haxorg_AttrValueFileReference>(org_context, __this, &org::sem::AttrValue::FileReference::file); }

haxorg_HstdStr haxorg_AttrValueFileReference_get_reference(OrgContext* org_context, haxorg_AttrValueFileReference __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::AttrValue::FileReference, hstd::Str, haxorg_AttrValueFileReference>(org_context, __this, &org::sem::AttrValue::FileReference::reference); }

void haxorg_create_AttrValueFileReference_FileReference(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::AttrValue::FileReference { return org::sem::AttrValue::FileReference(); }, org_context); }

bool haxorg_AttrValueFileReference___eq___const(OrgContext* org_context, haxorg_AttrValueFileReference __this, haxorg_AttrValueFileReference other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::AttrValue::FileReference::*)(org::sem::AttrValue::FileReference const&) const>(&org::sem::AttrValue::FileReference::operator==), org_context, __this, other); }

void haxorg_destroy_AttrValueFileReference(OrgContext* org_context, haxorg_AttrValueFileReference* obj) { org::bind::c::execute_destroy<org::sem::AttrValue::FileReference>(org_context, obj); }

haxorg_LispCode haxorg_AttrValueLispValue_get_code(OrgContext* org_context, haxorg_AttrValueLispValue __this) { return org::bind::c::get_cpp_field<haxorg_LispCode, org::sem::AttrValue::LispValue, org::sem::LispCode, haxorg_AttrValueLispValue>(org_context, __this, &org::sem::AttrValue::LispValue::code); }

void haxorg_create_AttrValueLispValue_LispValue(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::AttrValue::LispValue { return org::sem::AttrValue::LispValue(); }, org_context); }

bool haxorg_AttrValueLispValue___eq___const(OrgContext* org_context, haxorg_AttrValueLispValue __this, haxorg_AttrValueLispValue other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::AttrValue::LispValue::*)(org::sem::AttrValue::LispValue const&) const>(&org::sem::AttrValue::LispValue::operator==), org_context, __this, other); }

void haxorg_destroy_AttrValueLispValue(OrgContext* org_context, haxorg_AttrValueLispValue* obj) { org::bind::c::execute_destroy<org::sem::AttrValue::LispValue>(org_context, obj); }

void haxorg_destroy_AttrValue(OrgContext* org_context, haxorg_AttrValue* obj) { org::bind::c::execute_destroy<org::sem::AttrValue>(org_context, obj); }

haxorg_HstdVecOfStr haxorg_HashTagFlat_get_tags(OrgContext* org_context, haxorg_HashTagFlat __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfStr, org::sem::HashTagFlat, hstd::Vec<hstd::Str>, haxorg_HashTagFlat>(org_context, __this, &org::sem::HashTagFlat::tags); }

bool haxorg_HashTagFlat___eq___const(OrgContext* org_context, haxorg_HashTagFlat __this, haxorg_HashTagFlat other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator==), org_context, __this, other); }

bool haxorg_HashTagFlat___lt___const(OrgContext* org_context, haxorg_HashTagFlat __this, haxorg_HashTagFlat other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator<), org_context, __this, other); }

void haxorg_destroy_HashTagFlat(OrgContext* org_context, haxorg_HashTagFlat* obj) { org::bind::c::execute_destroy<org::sem::HashTagFlat>(org_context, obj); }

haxorg_HstdStr haxorg_TodoKeyword_get_name(OrgContext* org_context, haxorg_TodoKeyword __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::TodoKeyword, hstd::Str, haxorg_TodoKeyword>(org_context, __this, &org::sem::TodoKeyword::name); }

haxorg_OptOfStr haxorg_TodoKeyword_get_shortcut(OrgContext* org_context, haxorg_TodoKeyword __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::TodoKeyword, hstd::Opt<hstd::Str>, haxorg_TodoKeyword>(org_context, __this, &org::sem::TodoKeyword::shortcut); }

haxorg_TodoKeywordTransition haxorg_TodoKeyword_get_onEnter(OrgContext* org_context, haxorg_TodoKeyword __this) { return org::bind::c::get_cpp_field<haxorg_TodoKeywordTransition, org::sem::TodoKeyword, org::sem::TodoKeyword::Transition, haxorg_TodoKeyword>(org_context, __this, &org::sem::TodoKeyword::onEnter); }

haxorg_TodoKeywordTransition haxorg_TodoKeyword_get_onLeave(OrgContext* org_context, haxorg_TodoKeyword __this) { return org::bind::c::get_cpp_field<haxorg_TodoKeywordTransition, org::sem::TodoKeyword, org::sem::TodoKeyword::Transition, haxorg_TodoKeyword>(org_context, __this, &org::sem::TodoKeyword::onLeave); }

bool haxorg_TodoKeyword___eq___const(OrgContext* org_context, haxorg_TodoKeyword __this, haxorg_TodoKeyword other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::TodoKeyword::*)(org::sem::TodoKeyword const&) const>(&org::sem::TodoKeyword::operator==), org_context, __this, other); }

void haxorg_destroy_TodoKeyword(OrgContext* org_context, haxorg_TodoKeyword* obj) { org::bind::c::execute_destroy<org::sem::TodoKeyword>(org_context, obj); }

haxorg_HstdStr haxorg_HashTagText_get_head(OrgContext* org_context, haxorg_HashTagText __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::HashTagText, hstd::Str, haxorg_HashTagText>(org_context, __this, &org::sem::HashTagText::head); }

haxorg_HstdVecOfHashTagText haxorg_HashTagText_get_subtags(OrgContext* org_context, haxorg_HashTagText __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfHashTagText, org::sem::HashTagText, hstd::Vec<org::sem::HashTagText>, haxorg_HashTagText>(org_context, __this, &org::sem::HashTagText::subtags); }

bool haxorg_HashTagText___eq___const(OrgContext* org_context, haxorg_HashTagText __this, haxorg_HashTagText other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::HashTagText::*)(org::sem::HashTagText const&) const>(&org::sem::HashTagText::operator==), org_context, __this, other); }

bool haxorg_HashTagText_prefixMatch_const(OrgContext* org_context, haxorg_HashTagText __this, haxorg_HstdVecOfStr prefix) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::HashTagText::*)(hstd::Vec<hstd::Str> const&) const>(&org::sem::HashTagText::prefixMatch), org_context, __this, prefix); }

haxorg_HstdVecOfHashTagFlat haxorg_HashTagText_getFlatHashes_const(OrgContext* org_context, haxorg_HashTagText __this, bool withIntermediate) { return org::bind::c::execute_cpp<haxorg_HstdVecOfHashTagFlat>(static_cast<hstd::Vec<org::sem::HashTagFlat>(org::sem::HashTagText::*)(bool) const>(&org::sem::HashTagText::getFlatHashes), org_context, __this, withIntermediate); }

void haxorg_destroy_HashTagText(OrgContext* org_context, haxorg_HashTagText* obj) { org::bind::c::execute_destroy<org::sem::HashTagText>(org_context, obj); }

haxorg_HstdVecOfStr haxorg_SubtreePath_get_path(OrgContext* org_context, haxorg_SubtreePath __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfStr, org::sem::SubtreePath, hstd::Vec<hstd::Str>, haxorg_SubtreePath>(org_context, __this, &org::sem::SubtreePath::path); }

bool haxorg_SubtreePath___eq___const(OrgContext* org_context, haxorg_SubtreePath __this, haxorg_SubtreePath other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreePath::*)(org::sem::SubtreePath const&) const>(&org::sem::SubtreePath::operator==), org_context, __this, other); }

void haxorg_destroy_SubtreePath(OrgContext* org_context, haxorg_SubtreePath* obj) { org::bind::c::execute_destroy<org::sem::SubtreePath>(org_context, obj); }

bool haxorg_LinkTarget___eq___const(OrgContext* org_context, haxorg_LinkTarget __this, haxorg_LinkTarget other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::*)(org::sem::LinkTarget const&) const>(&org::sem::LinkTarget::operator==), org_context, __this, other); }

bool haxorg_LinkTarget_isRaw_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isRaw), org_context, __this); }

haxorg_LinkTargetRaw haxorg_LinkTarget_getRawConst_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetRaw>(static_cast<org::sem::LinkTarget::Raw const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getRaw), org_context, __this); }

haxorg_LinkTargetRaw haxorg_LinkTarget_getRawMut(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetRaw>(static_cast<org::sem::LinkTarget::Raw&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getRaw), org_context, __this); }

bool haxorg_LinkTarget_isId_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isId), org_context, __this); }

haxorg_LinkTargetId haxorg_LinkTarget_getIdConst_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetId>(static_cast<org::sem::LinkTarget::Id const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getId), org_context, __this); }

haxorg_LinkTargetId haxorg_LinkTarget_getIdMut(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetId>(static_cast<org::sem::LinkTarget::Id&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getId), org_context, __this); }

bool haxorg_LinkTarget_isCustomId_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isCustomId), org_context, __this); }

haxorg_LinkTargetCustomId haxorg_LinkTarget_getCustomIdConst_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetCustomId>(static_cast<org::sem::LinkTarget::CustomId const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getCustomId), org_context, __this); }

haxorg_LinkTargetCustomId haxorg_LinkTarget_getCustomIdMut(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetCustomId>(static_cast<org::sem::LinkTarget::CustomId&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getCustomId), org_context, __this); }

bool haxorg_LinkTarget_isSubtreeTitle_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isSubtreeTitle), org_context, __this); }

haxorg_LinkTargetSubtreeTitle haxorg_LinkTarget_getSubtreeTitleConst_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetSubtreeTitle>(static_cast<org::sem::LinkTarget::SubtreeTitle const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getSubtreeTitle), org_context, __this); }

haxorg_LinkTargetSubtreeTitle haxorg_LinkTarget_getSubtreeTitleMut(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetSubtreeTitle>(static_cast<org::sem::LinkTarget::SubtreeTitle&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getSubtreeTitle), org_context, __this); }

bool haxorg_LinkTarget_isPerson_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isPerson), org_context, __this); }

haxorg_LinkTargetPerson haxorg_LinkTarget_getPersonConst_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetPerson>(static_cast<org::sem::LinkTarget::Person const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getPerson), org_context, __this); }

haxorg_LinkTargetPerson haxorg_LinkTarget_getPersonMut(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetPerson>(static_cast<org::sem::LinkTarget::Person&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getPerson), org_context, __this); }

bool haxorg_LinkTarget_isUserProtocol_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isUserProtocol), org_context, __this); }

haxorg_LinkTargetUserProtocol haxorg_LinkTarget_getUserProtocolConst_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetUserProtocol>(static_cast<org::sem::LinkTarget::UserProtocol const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getUserProtocol), org_context, __this); }

haxorg_LinkTargetUserProtocol haxorg_LinkTarget_getUserProtocolMut(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetUserProtocol>(static_cast<org::sem::LinkTarget::UserProtocol&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getUserProtocol), org_context, __this); }

bool haxorg_LinkTarget_isInternal_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isInternal), org_context, __this); }

haxorg_LinkTargetInternal haxorg_LinkTarget_getInternalConst_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetInternal>(static_cast<org::sem::LinkTarget::Internal const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getInternal), org_context, __this); }

haxorg_LinkTargetInternal haxorg_LinkTarget_getInternalMut(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetInternal>(static_cast<org::sem::LinkTarget::Internal&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getInternal), org_context, __this); }

bool haxorg_LinkTarget_isFootnote_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isFootnote), org_context, __this); }

haxorg_LinkTargetFootnote haxorg_LinkTarget_getFootnoteConst_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetFootnote>(static_cast<org::sem::LinkTarget::Footnote const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getFootnote), org_context, __this); }

haxorg_LinkTargetFootnote haxorg_LinkTarget_getFootnoteMut(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetFootnote>(static_cast<org::sem::LinkTarget::Footnote&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getFootnote), org_context, __this); }

bool haxorg_LinkTarget_isFile_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isFile), org_context, __this); }

haxorg_LinkTargetFile haxorg_LinkTarget_getFileConst_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetFile>(static_cast<org::sem::LinkTarget::File const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getFile), org_context, __this); }

haxorg_LinkTargetFile haxorg_LinkTarget_getFileMut(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetFile>(static_cast<org::sem::LinkTarget::File&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getFile), org_context, __this); }

bool haxorg_LinkTarget_isAttachment_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isAttachment), org_context, __this); }

haxorg_LinkTargetAttachment haxorg_LinkTarget_getAttachmentConst_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetAttachment>(static_cast<org::sem::LinkTarget::Attachment const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getAttachment), org_context, __this); }

haxorg_LinkTargetAttachment haxorg_LinkTarget_getAttachmentMut(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetAttachment>(static_cast<org::sem::LinkTarget::Attachment&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getAttachment), org_context, __this); }

haxorg_LinkTargetKind haxorg_LinkTarget_getKind_const(OrgContext* org_context, haxorg_LinkTarget __this) { return org::bind::c::execute_cpp<haxorg_LinkTargetKind>(static_cast<org::sem::LinkTarget::Kind(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getKind), org_context, __this); }

haxorg_HstdStr haxorg_LinkTargetRaw_get_text(OrgContext* org_context, haxorg_LinkTargetRaw __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::LinkTarget::Raw, hstd::Str, haxorg_LinkTargetRaw>(org_context, __this, &org::sem::LinkTarget::Raw::text); }

bool haxorg_LinkTargetRaw___eq___const(OrgContext* org_context, haxorg_LinkTargetRaw __this, haxorg_LinkTargetRaw other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::Raw::*)(org::sem::LinkTarget::Raw const&) const>(&org::sem::LinkTarget::Raw::operator==), org_context, __this, other); }

void haxorg_destroy_LinkTargetRaw(OrgContext* org_context, haxorg_LinkTargetRaw* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Raw>(org_context, obj); }

haxorg_HstdStr haxorg_LinkTargetId_get_text(OrgContext* org_context, haxorg_LinkTargetId __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::LinkTarget::Id, hstd::Str, haxorg_LinkTargetId>(org_context, __this, &org::sem::LinkTarget::Id::text); }

bool haxorg_LinkTargetId___eq___const(OrgContext* org_context, haxorg_LinkTargetId __this, haxorg_LinkTargetId other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::Id::*)(org::sem::LinkTarget::Id const&) const>(&org::sem::LinkTarget::Id::operator==), org_context, __this, other); }

void haxorg_destroy_LinkTargetId(OrgContext* org_context, haxorg_LinkTargetId* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Id>(org_context, obj); }

haxorg_HstdStr haxorg_LinkTargetCustomId_get_text(OrgContext* org_context, haxorg_LinkTargetCustomId __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::LinkTarget::CustomId, hstd::Str, haxorg_LinkTargetCustomId>(org_context, __this, &org::sem::LinkTarget::CustomId::text); }

bool haxorg_LinkTargetCustomId___eq___const(OrgContext* org_context, haxorg_LinkTargetCustomId __this, haxorg_LinkTargetCustomId other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::CustomId::*)(org::sem::LinkTarget::CustomId const&) const>(&org::sem::LinkTarget::CustomId::operator==), org_context, __this, other); }

void haxorg_destroy_LinkTargetCustomId(OrgContext* org_context, haxorg_LinkTargetCustomId* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::CustomId>(org_context, obj); }

haxorg_SubtreePath haxorg_LinkTargetSubtreeTitle_get_title(OrgContext* org_context, haxorg_LinkTargetSubtreeTitle __this) { return org::bind::c::get_cpp_field<haxorg_SubtreePath, org::sem::LinkTarget::SubtreeTitle, org::sem::SubtreePath, haxorg_LinkTargetSubtreeTitle>(org_context, __this, &org::sem::LinkTarget::SubtreeTitle::title); }

int haxorg_LinkTargetSubtreeTitle_get_level(OrgContext* org_context, haxorg_LinkTargetSubtreeTitle __this) { return org::bind::c::get_cpp_field<int, org::sem::LinkTarget::SubtreeTitle, int, haxorg_LinkTargetSubtreeTitle>(org_context, __this, &org::sem::LinkTarget::SubtreeTitle::level); }

bool haxorg_LinkTargetSubtreeTitle___eq___const(OrgContext* org_context, haxorg_LinkTargetSubtreeTitle __this, haxorg_LinkTargetSubtreeTitle other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::SubtreeTitle::*)(org::sem::LinkTarget::SubtreeTitle const&) const>(&org::sem::LinkTarget::SubtreeTitle::operator==), org_context, __this, other); }

void haxorg_destroy_LinkTargetSubtreeTitle(OrgContext* org_context, haxorg_LinkTargetSubtreeTitle* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::SubtreeTitle>(org_context, obj); }

haxorg_HstdStr haxorg_LinkTargetPerson_get_name(OrgContext* org_context, haxorg_LinkTargetPerson __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::LinkTarget::Person, hstd::Str, haxorg_LinkTargetPerson>(org_context, __this, &org::sem::LinkTarget::Person::name); }

bool haxorg_LinkTargetPerson___eq___const(OrgContext* org_context, haxorg_LinkTargetPerson __this, haxorg_LinkTargetPerson other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::Person::*)(org::sem::LinkTarget::Person const&) const>(&org::sem::LinkTarget::Person::operator==), org_context, __this, other); }

void haxorg_destroy_LinkTargetPerson(OrgContext* org_context, haxorg_LinkTargetPerson* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Person>(org_context, obj); }

haxorg_HstdStr haxorg_LinkTargetUserProtocol_get_protocol(OrgContext* org_context, haxorg_LinkTargetUserProtocol __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::LinkTarget::UserProtocol, hstd::Str, haxorg_LinkTargetUserProtocol>(org_context, __this, &org::sem::LinkTarget::UserProtocol::protocol); }

haxorg_HstdStr haxorg_LinkTargetUserProtocol_get_target(OrgContext* org_context, haxorg_LinkTargetUserProtocol __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::LinkTarget::UserProtocol, hstd::Str, haxorg_LinkTargetUserProtocol>(org_context, __this, &org::sem::LinkTarget::UserProtocol::target); }

bool haxorg_LinkTargetUserProtocol___eq___const(OrgContext* org_context, haxorg_LinkTargetUserProtocol __this, haxorg_LinkTargetUserProtocol other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::UserProtocol::*)(org::sem::LinkTarget::UserProtocol const&) const>(&org::sem::LinkTarget::UserProtocol::operator==), org_context, __this, other); }

void haxorg_destroy_LinkTargetUserProtocol(OrgContext* org_context, haxorg_LinkTargetUserProtocol* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::UserProtocol>(org_context, obj); }

haxorg_HstdStr haxorg_LinkTargetInternal_get_target(OrgContext* org_context, haxorg_LinkTargetInternal __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::LinkTarget::Internal, hstd::Str, haxorg_LinkTargetInternal>(org_context, __this, &org::sem::LinkTarget::Internal::target); }

bool haxorg_LinkTargetInternal___eq___const(OrgContext* org_context, haxorg_LinkTargetInternal __this, haxorg_LinkTargetInternal other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::Internal::*)(org::sem::LinkTarget::Internal const&) const>(&org::sem::LinkTarget::Internal::operator==), org_context, __this, other); }

void haxorg_destroy_LinkTargetInternal(OrgContext* org_context, haxorg_LinkTargetInternal* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Internal>(org_context, obj); }

haxorg_HstdStr haxorg_LinkTargetFootnote_get_target(OrgContext* org_context, haxorg_LinkTargetFootnote __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::LinkTarget::Footnote, hstd::Str, haxorg_LinkTargetFootnote>(org_context, __this, &org::sem::LinkTarget::Footnote::target); }

bool haxorg_LinkTargetFootnote___eq___const(OrgContext* org_context, haxorg_LinkTargetFootnote __this, haxorg_LinkTargetFootnote other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::Footnote::*)(org::sem::LinkTarget::Footnote const&) const>(&org::sem::LinkTarget::Footnote::operator==), org_context, __this, other); }

void haxorg_destroy_LinkTargetFootnote(OrgContext* org_context, haxorg_LinkTargetFootnote* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Footnote>(org_context, obj); }

haxorg_HstdStr haxorg_LinkTargetFile_get_file(OrgContext* org_context, haxorg_LinkTargetFile __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::LinkTarget::File, hstd::Str, haxorg_LinkTargetFile>(org_context, __this, &org::sem::LinkTarget::File::file); }

bool haxorg_LinkTargetFile___eq___const(OrgContext* org_context, haxorg_LinkTargetFile __this, haxorg_LinkTargetFile other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::File::*)(org::sem::LinkTarget::File const&) const>(&org::sem::LinkTarget::File::operator==), org_context, __this, other); }

void haxorg_destroy_LinkTargetFile(OrgContext* org_context, haxorg_LinkTargetFile* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::File>(org_context, obj); }

haxorg_HstdStr haxorg_LinkTargetAttachment_get_file(OrgContext* org_context, haxorg_LinkTargetAttachment __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::LinkTarget::Attachment, hstd::Str, haxorg_LinkTargetAttachment>(org_context, __this, &org::sem::LinkTarget::Attachment::file); }

bool haxorg_LinkTargetAttachment___eq___const(OrgContext* org_context, haxorg_LinkTargetAttachment __this, haxorg_LinkTargetAttachment other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::LinkTarget::Attachment::*)(org::sem::LinkTarget::Attachment const&) const>(&org::sem::LinkTarget::Attachment::operator==), org_context, __this, other); }

void haxorg_destroy_LinkTargetAttachment(OrgContext* org_context, haxorg_LinkTargetAttachment* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget::Attachment>(org_context, obj); }

void haxorg_destroy_LinkTarget(OrgContext* org_context, haxorg_LinkTarget* obj) { org::bind::c::execute_destroy<org::sem::LinkTarget>(org_context, obj); }

bool haxorg_SubtreeLogHead___eq___const(OrgContext* org_context, haxorg_SubtreeLogHead __this, haxorg_SubtreeLogHead other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::*)(org::sem::SubtreeLogHead const&) const>(&org::sem::SubtreeLogHead::operator==), org_context, __this, other); }

bool haxorg_SubtreeLogHead_isPriority_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isPriority), org_context, __this); }

haxorg_SubtreeLogHeadPriority haxorg_SubtreeLogHead_getPriorityConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadPriority>(static_cast<org::sem::SubtreeLogHead::Priority const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getPriority), org_context, __this); }

haxorg_SubtreeLogHeadPriority haxorg_SubtreeLogHead_getPriorityMut(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadPriority>(static_cast<org::sem::SubtreeLogHead::Priority&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getPriority), org_context, __this); }

bool haxorg_SubtreeLogHead_isNote_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isNote), org_context, __this); }

haxorg_SubtreeLogHeadNote haxorg_SubtreeLogHead_getNoteConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadNote>(static_cast<org::sem::SubtreeLogHead::Note const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getNote), org_context, __this); }

haxorg_SubtreeLogHeadNote haxorg_SubtreeLogHead_getNoteMut(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadNote>(static_cast<org::sem::SubtreeLogHead::Note&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getNote), org_context, __this); }

bool haxorg_SubtreeLogHead_isRefile_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isRefile), org_context, __this); }

haxorg_SubtreeLogHeadRefile haxorg_SubtreeLogHead_getRefileConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadRefile>(static_cast<org::sem::SubtreeLogHead::Refile const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getRefile), org_context, __this); }

haxorg_SubtreeLogHeadRefile haxorg_SubtreeLogHead_getRefileMut(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadRefile>(static_cast<org::sem::SubtreeLogHead::Refile&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getRefile), org_context, __this); }

bool haxorg_SubtreeLogHead_isClock_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isClock), org_context, __this); }

haxorg_SubtreeLogHeadClock haxorg_SubtreeLogHead_getClockConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadClock>(static_cast<org::sem::SubtreeLogHead::Clock const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getClock), org_context, __this); }

haxorg_SubtreeLogHeadClock haxorg_SubtreeLogHead_getClockMut(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadClock>(static_cast<org::sem::SubtreeLogHead::Clock&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getClock), org_context, __this); }

bool haxorg_SubtreeLogHead_isState_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isState), org_context, __this); }

haxorg_SubtreeLogHeadState haxorg_SubtreeLogHead_getStateConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadState>(static_cast<org::sem::SubtreeLogHead::State const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getState), org_context, __this); }

haxorg_SubtreeLogHeadState haxorg_SubtreeLogHead_getStateMut(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadState>(static_cast<org::sem::SubtreeLogHead::State&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getState), org_context, __this); }

bool haxorg_SubtreeLogHead_isDeadline_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isDeadline), org_context, __this); }

haxorg_SubtreeLogHeadDeadline haxorg_SubtreeLogHead_getDeadlineConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadDeadline>(static_cast<org::sem::SubtreeLogHead::Deadline const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getDeadline), org_context, __this); }

haxorg_SubtreeLogHeadDeadline haxorg_SubtreeLogHead_getDeadlineMut(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadDeadline>(static_cast<org::sem::SubtreeLogHead::Deadline&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getDeadline), org_context, __this); }

bool haxorg_SubtreeLogHead_isSchedule_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isSchedule), org_context, __this); }

haxorg_SubtreeLogHeadSchedule haxorg_SubtreeLogHead_getScheduleConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadSchedule>(static_cast<org::sem::SubtreeLogHead::Schedule const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getSchedule), org_context, __this); }

haxorg_SubtreeLogHeadSchedule haxorg_SubtreeLogHead_getScheduleMut(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadSchedule>(static_cast<org::sem::SubtreeLogHead::Schedule&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getSchedule), org_context, __this); }

bool haxorg_SubtreeLogHead_isTag_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isTag), org_context, __this); }

haxorg_SubtreeLogHeadTag haxorg_SubtreeLogHead_getTagConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadTag>(static_cast<org::sem::SubtreeLogHead::Tag const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getTag), org_context, __this); }

haxorg_SubtreeLogHeadTag haxorg_SubtreeLogHead_getTagMut(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadTag>(static_cast<org::sem::SubtreeLogHead::Tag&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getTag), org_context, __this); }

bool haxorg_SubtreeLogHead_isUnknown_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isUnknown), org_context, __this); }

haxorg_SubtreeLogHeadUnknown haxorg_SubtreeLogHead_getUnknownConst_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadUnknown>(static_cast<org::sem::SubtreeLogHead::Unknown const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getUnknown), org_context, __this); }

haxorg_SubtreeLogHeadUnknown haxorg_SubtreeLogHead_getUnknownMut(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadUnknown>(static_cast<org::sem::SubtreeLogHead::Unknown&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getUnknown), org_context, __this); }

haxorg_SubtreeLogHeadKind haxorg_SubtreeLogHead_getLogKind_const(OrgContext* org_context, haxorg_SubtreeLogHead __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHeadKind>(static_cast<org::sem::SubtreeLogHead::Kind(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getLogKind), org_context, __this); }

haxorg_OptOfStdString haxorg_SubtreeLogHeadPriority_get_oldPriority(OrgContext* org_context, haxorg_SubtreeLogHeadPriority __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStdString, org::sem::SubtreeLogHead::Priority, hstd::Opt<std::string>, haxorg_SubtreeLogHeadPriority>(org_context, __this, &org::sem::SubtreeLogHead::Priority::oldPriority); }

haxorg_OptOfStdString haxorg_SubtreeLogHeadPriority_get_newPriority(OrgContext* org_context, haxorg_SubtreeLogHeadPriority __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStdString, org::sem::SubtreeLogHead::Priority, hstd::Opt<std::string>, haxorg_SubtreeLogHeadPriority>(org_context, __this, &org::sem::SubtreeLogHead::Priority::newPriority); }

haxorg_UserTime haxorg_SubtreeLogHeadPriority_get_on(OrgContext* org_context, haxorg_SubtreeLogHeadPriority __this) { return org::bind::c::get_cpp_field<haxorg_UserTime, org::sem::SubtreeLogHead::Priority, hstd::UserTime, haxorg_SubtreeLogHeadPriority>(org_context, __this, &org::sem::SubtreeLogHead::Priority::on); }

haxorg_SubtreeLogHeadPriorityAction haxorg_SubtreeLogHeadPriority_get_action(OrgContext* org_context, haxorg_SubtreeLogHeadPriority __this) { return org::bind::c::get_cpp_field<haxorg_SubtreeLogHeadPriorityAction, org::sem::SubtreeLogHead::Priority, org::sem::SubtreeLogHead::Priority::Action, haxorg_SubtreeLogHeadPriority>(org_context, __this, &org::sem::SubtreeLogHead::Priority::action); }

bool haxorg_SubtreeLogHeadPriority___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadPriority __this, haxorg_SubtreeLogHeadPriority other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::Priority::*)(org::sem::SubtreeLogHead::Priority const&) const>(&org::sem::SubtreeLogHead::Priority::operator==), org_context, __this, other); }

void haxorg_destroy_SubtreeLogHeadPriority(OrgContext* org_context, haxorg_SubtreeLogHeadPriority* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Priority>(org_context, obj); }

haxorg_UserTime haxorg_SubtreeLogHeadNote_get_on(OrgContext* org_context, haxorg_SubtreeLogHeadNote __this) { return org::bind::c::get_cpp_field<haxorg_UserTime, org::sem::SubtreeLogHead::Note, hstd::UserTime, haxorg_SubtreeLogHeadNote>(org_context, __this, &org::sem::SubtreeLogHead::Note::on); }

bool haxorg_SubtreeLogHeadNote___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadNote __this, haxorg_SubtreeLogHeadNote other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::Note::*)(org::sem::SubtreeLogHead::Note const&) const>(&org::sem::SubtreeLogHead::Note::operator==), org_context, __this, other); }

void haxorg_destroy_SubtreeLogHeadNote(OrgContext* org_context, haxorg_SubtreeLogHeadNote* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Note>(org_context, obj); }

haxorg_UserTime haxorg_SubtreeLogHeadRefile_get_on(OrgContext* org_context, haxorg_SubtreeLogHeadRefile __this) { return org::bind::c::get_cpp_field<haxorg_UserTime, org::sem::SubtreeLogHead::Refile, hstd::UserTime, haxorg_SubtreeLogHeadRefile>(org_context, __this, &org::sem::SubtreeLogHead::Refile::on); }

haxorg_LinkTarget haxorg_SubtreeLogHeadRefile_get_from(OrgContext* org_context, haxorg_SubtreeLogHeadRefile __this) { return org::bind::c::get_cpp_field<haxorg_LinkTarget, org::sem::SubtreeLogHead::Refile, org::sem::LinkTarget, haxorg_SubtreeLogHeadRefile>(org_context, __this, &org::sem::SubtreeLogHead::Refile::from); }

bool haxorg_SubtreeLogHeadRefile___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadRefile __this, haxorg_SubtreeLogHeadRefile other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::Refile::*)(org::sem::SubtreeLogHead::Refile const&) const>(&org::sem::SubtreeLogHead::Refile::operator==), org_context, __this, other); }

void haxorg_destroy_SubtreeLogHeadRefile(OrgContext* org_context, haxorg_SubtreeLogHeadRefile* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Refile>(org_context, obj); }

haxorg_UserTime haxorg_SubtreeLogHeadClock_get_from(OrgContext* org_context, haxorg_SubtreeLogHeadClock __this) { return org::bind::c::get_cpp_field<haxorg_UserTime, org::sem::SubtreeLogHead::Clock, hstd::UserTime, haxorg_SubtreeLogHeadClock>(org_context, __this, &org::sem::SubtreeLogHead::Clock::from); }

haxorg_OptOfUserTime haxorg_SubtreeLogHeadClock_get_to(OrgContext* org_context, haxorg_SubtreeLogHeadClock __this) { return org::bind::c::get_cpp_field<haxorg_OptOfUserTime, org::sem::SubtreeLogHead::Clock, hstd::Opt<hstd::UserTime>, haxorg_SubtreeLogHeadClock>(org_context, __this, &org::sem::SubtreeLogHead::Clock::to); }

bool haxorg_SubtreeLogHeadClock___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadClock __this, haxorg_SubtreeLogHeadClock other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::Clock::*)(org::sem::SubtreeLogHead::Clock const&) const>(&org::sem::SubtreeLogHead::Clock::operator==), org_context, __this, other); }

void haxorg_destroy_SubtreeLogHeadClock(OrgContext* org_context, haxorg_SubtreeLogHeadClock* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Clock>(org_context, obj); }

haxorg_HstdStr haxorg_SubtreeLogHeadState_get_from(OrgContext* org_context, haxorg_SubtreeLogHeadState __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::SubtreeLogHead::State, hstd::Str, haxorg_SubtreeLogHeadState>(org_context, __this, &org::sem::SubtreeLogHead::State::from); }

haxorg_HstdStr haxorg_SubtreeLogHeadState_get_to(OrgContext* org_context, haxorg_SubtreeLogHeadState __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::SubtreeLogHead::State, hstd::Str, haxorg_SubtreeLogHeadState>(org_context, __this, &org::sem::SubtreeLogHead::State::to); }

haxorg_UserTime haxorg_SubtreeLogHeadState_get_on(OrgContext* org_context, haxorg_SubtreeLogHeadState __this) { return org::bind::c::get_cpp_field<haxorg_UserTime, org::sem::SubtreeLogHead::State, hstd::UserTime, haxorg_SubtreeLogHeadState>(org_context, __this, &org::sem::SubtreeLogHead::State::on); }

bool haxorg_SubtreeLogHeadState___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadState __this, haxorg_SubtreeLogHeadState other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::State::*)(org::sem::SubtreeLogHead::State const&) const>(&org::sem::SubtreeLogHead::State::operator==), org_context, __this, other); }

void haxorg_destroy_SubtreeLogHeadState(OrgContext* org_context, haxorg_SubtreeLogHeadState* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::State>(org_context, obj); }

haxorg_OptOfUserTime haxorg_SubtreeLogHeadDeadline_get_from(OrgContext* org_context, haxorg_SubtreeLogHeadDeadline __this) { return org::bind::c::get_cpp_field<haxorg_OptOfUserTime, org::sem::SubtreeLogHead::Deadline, hstd::Opt<hstd::UserTime>, haxorg_SubtreeLogHeadDeadline>(org_context, __this, &org::sem::SubtreeLogHead::Deadline::from); }

haxorg_UserTime haxorg_SubtreeLogHeadDeadline_get_to(OrgContext* org_context, haxorg_SubtreeLogHeadDeadline __this) { return org::bind::c::get_cpp_field<haxorg_UserTime, org::sem::SubtreeLogHead::Deadline, hstd::UserTime, haxorg_SubtreeLogHeadDeadline>(org_context, __this, &org::sem::SubtreeLogHead::Deadline::to); }

haxorg_UserTime haxorg_SubtreeLogHeadDeadline_get_on(OrgContext* org_context, haxorg_SubtreeLogHeadDeadline __this) { return org::bind::c::get_cpp_field<haxorg_UserTime, org::sem::SubtreeLogHead::Deadline, hstd::UserTime, haxorg_SubtreeLogHeadDeadline>(org_context, __this, &org::sem::SubtreeLogHead::Deadline::on); }

bool haxorg_SubtreeLogHeadDeadline___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadDeadline __this, haxorg_SubtreeLogHeadDeadline other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::Deadline::*)(org::sem::SubtreeLogHead::Deadline const&) const>(&org::sem::SubtreeLogHead::Deadline::operator==), org_context, __this, other); }

void haxorg_destroy_SubtreeLogHeadDeadline(OrgContext* org_context, haxorg_SubtreeLogHeadDeadline* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Deadline>(org_context, obj); }

haxorg_OptOfUserTime haxorg_SubtreeLogHeadSchedule_get_from(OrgContext* org_context, haxorg_SubtreeLogHeadSchedule __this) { return org::bind::c::get_cpp_field<haxorg_OptOfUserTime, org::sem::SubtreeLogHead::Schedule, hstd::Opt<hstd::UserTime>, haxorg_SubtreeLogHeadSchedule>(org_context, __this, &org::sem::SubtreeLogHead::Schedule::from); }

haxorg_UserTime haxorg_SubtreeLogHeadSchedule_get_to(OrgContext* org_context, haxorg_SubtreeLogHeadSchedule __this) { return org::bind::c::get_cpp_field<haxorg_UserTime, org::sem::SubtreeLogHead::Schedule, hstd::UserTime, haxorg_SubtreeLogHeadSchedule>(org_context, __this, &org::sem::SubtreeLogHead::Schedule::to); }

haxorg_UserTime haxorg_SubtreeLogHeadSchedule_get_on(OrgContext* org_context, haxorg_SubtreeLogHeadSchedule __this) { return org::bind::c::get_cpp_field<haxorg_UserTime, org::sem::SubtreeLogHead::Schedule, hstd::UserTime, haxorg_SubtreeLogHeadSchedule>(org_context, __this, &org::sem::SubtreeLogHead::Schedule::on); }

bool haxorg_SubtreeLogHeadSchedule___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadSchedule __this, haxorg_SubtreeLogHeadSchedule other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::Schedule::*)(org::sem::SubtreeLogHead::Schedule const&) const>(&org::sem::SubtreeLogHead::Schedule::operator==), org_context, __this, other); }

void haxorg_destroy_SubtreeLogHeadSchedule(OrgContext* org_context, haxorg_SubtreeLogHeadSchedule* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Schedule>(org_context, obj); }

haxorg_UserTime haxorg_SubtreeLogHeadTag_get_on(OrgContext* org_context, haxorg_SubtreeLogHeadTag __this) { return org::bind::c::get_cpp_field<haxorg_UserTime, org::sem::SubtreeLogHead::Tag, hstd::UserTime, haxorg_SubtreeLogHeadTag>(org_context, __this, &org::sem::SubtreeLogHead::Tag::on); }

haxorg_HashTagText haxorg_SubtreeLogHeadTag_get_tag(OrgContext* org_context, haxorg_SubtreeLogHeadTag __this) { return org::bind::c::get_cpp_field<haxorg_HashTagText, org::sem::SubtreeLogHead::Tag, org::sem::HashTagText, haxorg_SubtreeLogHeadTag>(org_context, __this, &org::sem::SubtreeLogHead::Tag::tag); }

bool haxorg_SubtreeLogHeadTag_get_added(OrgContext* org_context, haxorg_SubtreeLogHeadTag __this) { return org::bind::c::get_cpp_field<bool, org::sem::SubtreeLogHead::Tag, bool, haxorg_SubtreeLogHeadTag>(org_context, __this, &org::sem::SubtreeLogHead::Tag::added); }

bool haxorg_SubtreeLogHeadTag___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadTag __this, haxorg_SubtreeLogHeadTag other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::Tag::*)(org::sem::SubtreeLogHead::Tag const&) const>(&org::sem::SubtreeLogHead::Tag::operator==), org_context, __this, other); }

void haxorg_destroy_SubtreeLogHeadTag(OrgContext* org_context, haxorg_SubtreeLogHeadTag* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Tag>(org_context, obj); }

bool haxorg_SubtreeLogHeadUnknown___eq___const(OrgContext* org_context, haxorg_SubtreeLogHeadUnknown __this, haxorg_SubtreeLogHeadUnknown other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeLogHead::Unknown::*)(org::sem::SubtreeLogHead::Unknown const&) const>(&org::sem::SubtreeLogHead::Unknown::operator==), org_context, __this, other); }

void haxorg_destroy_SubtreeLogHeadUnknown(OrgContext* org_context, haxorg_SubtreeLogHeadUnknown* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead::Unknown>(org_context, obj); }

void haxorg_destroy_SubtreeLogHead(OrgContext* org_context, haxorg_SubtreeLogHead* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLogHead>(org_context, obj); }

int haxorg_SubtreeCompletion_get_done(OrgContext* org_context, haxorg_SubtreeCompletion __this) { return org::bind::c::get_cpp_field<int, org::sem::SubtreeCompletion, int, haxorg_SubtreeCompletion>(org_context, __this, &org::sem::SubtreeCompletion::done); }

int haxorg_SubtreeCompletion_get_full(OrgContext* org_context, haxorg_SubtreeCompletion __this) { return org::bind::c::get_cpp_field<int, org::sem::SubtreeCompletion, int, haxorg_SubtreeCompletion>(org_context, __this, &org::sem::SubtreeCompletion::full); }

bool haxorg_SubtreeCompletion_get_isPercent(OrgContext* org_context, haxorg_SubtreeCompletion __this) { return org::bind::c::get_cpp_field<bool, org::sem::SubtreeCompletion, bool, haxorg_SubtreeCompletion>(org_context, __this, &org::sem::SubtreeCompletion::isPercent); }

bool haxorg_SubtreeCompletion___eq___const(OrgContext* org_context, haxorg_SubtreeCompletion __this, haxorg_SubtreeCompletion other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreeCompletion::*)(org::sem::SubtreeCompletion const&) const>(&org::sem::SubtreeCompletion::operator==), org_context, __this, other); }

void haxorg_destroy_SubtreeCompletion(OrgContext* org_context, haxorg_SubtreeCompletion* obj) { org::bind::c::execute_destroy<org::sem::SubtreeCompletion>(org_context, obj); }

haxorg_HstdVecOfAttrValue haxorg_AttrList_get_items(OrgContext* org_context, haxorg_AttrList __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfAttrValue, org::sem::AttrList, hstd::Vec<org::sem::AttrValue>, haxorg_AttrList>(org_context, __this, &org::sem::AttrList::items); }

bool haxorg_AttrList___eq___const(OrgContext* org_context, haxorg_AttrList __this, haxorg_AttrList other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::AttrList::*)(org::sem::AttrList const&) const>(&org::sem::AttrList::operator==), org_context, __this, other); }

void haxorg_destroy_AttrList(OrgContext* org_context, haxorg_AttrList* obj) { org::bind::c::execute_destroy<org::sem::AttrList>(org_context, obj); }

haxorg_AttrList haxorg_AttrGroup_get_positional(OrgContext* org_context, haxorg_AttrGroup __this) { return org::bind::c::get_cpp_field<haxorg_AttrList, org::sem::AttrGroup, org::sem::AttrList, haxorg_AttrGroup>(org_context, __this, &org::sem::AttrGroup::positional); }

haxorg_HstdMap haxorg_AttrGroup_get_named(OrgContext* org_context, haxorg_AttrGroup __this) { return org::bind::c::get_cpp_field<haxorg_HstdMap, org::sem::AttrGroup, hstd::UnorderedMap<hstd::Str, org::sem::AttrList>, haxorg_AttrGroup>(org_context, __this, &org::sem::AttrGroup::named); }

haxorg_HstdVecOfAttrValue haxorg_AttrGroup_getFlatArgs_const(OrgContext* org_context, haxorg_AttrGroup __this) { return org::bind::c::execute_cpp<haxorg_HstdVecOfAttrValue>(static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getFlatArgs), org_context, __this); }

haxorg_HstdVecOfAttrValue haxorg_AttrGroup_getAttrs_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_OptOfStr key) { return org::bind::c::execute_cpp<haxorg_HstdVecOfAttrValue>(static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::AttrGroup::getAttrs), org_context, __this, key); }

void haxorg_AttrGroup_setNamedAttr(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr key, haxorg_HstdVecOfAttrValue attrs) { return org::bind::c::execute_cpp<void>(static_cast<void(org::sem::AttrGroup::*)(hstd::Str const&, hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setNamedAttr), org_context, __this, key, attrs); }

void haxorg_AttrGroup_setPositionalAttr(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdVecOfAttrValue items) { return org::bind::c::execute_cpp<void>(static_cast<void(org::sem::AttrGroup::*)(hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setPositionalAttr), org_context, __this, items); }

int haxorg_AttrGroup_getPositionalSize_const(OrgContext* org_context, haxorg_AttrGroup __this) { return org::bind::c::execute_cpp<int>(static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getPositionalSize), org_context, __this); }

int haxorg_AttrGroup_getNamedSize_const(OrgContext* org_context, haxorg_AttrGroup __this) { return org::bind::c::execute_cpp<int>(static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getNamedSize), org_context, __this); }

bool haxorg_AttrGroup_isEmpty_const(OrgContext* org_context, haxorg_AttrGroup __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::isEmpty), org_context, __this); }

haxorg_AttrList haxorg_AttrGroup_getAll_const(OrgContext* org_context, haxorg_AttrGroup __this) { return org::bind::c::execute_cpp<haxorg_AttrList>(static_cast<org::sem::AttrList(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getAll), org_context, __this); }

haxorg_AttrValue haxorg_AttrGroup_atPositional_const(OrgContext* org_context, haxorg_AttrGroup __this, int index) { return org::bind::c::execute_cpp<haxorg_AttrValue>(static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::atPositional), org_context, __this, index); }

haxorg_OptOfAttrValue haxorg_AttrGroup_getPositional_const(OrgContext* org_context, haxorg_AttrGroup __this, int index) { return org::bind::c::execute_cpp<haxorg_OptOfAttrValue>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::getPositional), org_context, __this, index); }

haxorg_AttrList haxorg_AttrGroup_atNamed_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr index) { return org::bind::c::execute_cpp<haxorg_AttrList>(static_cast<org::sem::AttrList const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atNamed), org_context, __this, index); }

haxorg_OptOfAttrList haxorg_AttrGroup_getNamed_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr index) { return org::bind::c::execute_cpp<haxorg_OptOfAttrList>(static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getNamed), org_context, __this, index); }

haxorg_AttrValue haxorg_AttrGroup_atFirstNamed_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr index) { return org::bind::c::execute_cpp<haxorg_AttrValue>(static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstNamed), org_context, __this, index); }

haxorg_OptOfAttrValue haxorg_AttrGroup_getFirstNamed_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr index) { return org::bind::c::execute_cpp<haxorg_OptOfAttrValue>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstNamed), org_context, __this, index); }

haxorg_AttrList haxorg_AttrGroup_atVarNamed_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr index) { return org::bind::c::execute_cpp<haxorg_AttrList>(static_cast<org::sem::AttrList(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atVarNamed), org_context, __this, index); }

haxorg_OptOfAttrList haxorg_AttrGroup_getVarNamed_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr index) { return org::bind::c::execute_cpp<haxorg_OptOfAttrList>(static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getVarNamed), org_context, __this, index); }

haxorg_AttrValue haxorg_AttrGroup_atFirstVarNamed_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr index) { return org::bind::c::execute_cpp<haxorg_AttrValue>(static_cast<org::sem::AttrValue(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstVarNamed), org_context, __this, index); }

haxorg_OptOfAttrValue haxorg_AttrGroup_getFirstVarNamed_const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_HstdStr index) { return org::bind::c::execute_cpp<haxorg_OptOfAttrValue>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstVarNamed), org_context, __this, index); }

bool haxorg_AttrGroup___eq___const(OrgContext* org_context, haxorg_AttrGroup __this, haxorg_AttrGroup other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::AttrGroup::*)(org::sem::AttrGroup const&) const>(&org::sem::AttrGroup::operator==), org_context, __this, other); }

void haxorg_destroy_AttrGroup(OrgContext* org_context, haxorg_AttrGroup* obj) { org::bind::c::execute_destroy<org::sem::AttrGroup>(org_context, obj); }

haxorg_AttrGroup haxorg_OrgCodeEvalInput_get_blockAttrs(OrgContext* org_context, haxorg_OrgCodeEvalInput __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::sem::OrgCodeEvalInput, org::sem::AttrGroup, haxorg_OrgCodeEvalInput>(org_context, __this, &org::sem::OrgCodeEvalInput::blockAttrs); }

haxorg_HstdStr haxorg_OrgCodeEvalInput_get_tangledCode(OrgContext* org_context, haxorg_OrgCodeEvalInput __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgCodeEvalInput, hstd::Str, haxorg_OrgCodeEvalInput>(org_context, __this, &org::sem::OrgCodeEvalInput::tangledCode); }

haxorg_OptOfStr haxorg_OrgCodeEvalInput_get_exportType(OrgContext* org_context, haxorg_OrgCodeEvalInput __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::OrgCodeEvalInput, hstd::Opt<hstd::Str>, haxorg_OrgCodeEvalInput>(org_context, __this, &org::sem::OrgCodeEvalInput::exportType); }

haxorg_OrgCodeEvalInputResultType haxorg_OrgCodeEvalInput_get_resultType(OrgContext* org_context, haxorg_OrgCodeEvalInput __this) { return org::bind::c::get_cpp_field<haxorg_OrgCodeEvalInputResultType, org::sem::OrgCodeEvalInput, org::sem::OrgCodeEvalInput::ResultType, haxorg_OrgCodeEvalInput>(org_context, __this, &org::sem::OrgCodeEvalInput::resultType); }

haxorg_OrgCodeEvalInputResultFormat haxorg_OrgCodeEvalInput_get_resultFormat(OrgContext* org_context, haxorg_OrgCodeEvalInput __this) { return org::bind::c::get_cpp_field<haxorg_OrgCodeEvalInputResultFormat, org::sem::OrgCodeEvalInput, org::sem::OrgCodeEvalInput::ResultFormat, haxorg_OrgCodeEvalInput>(org_context, __this, &org::sem::OrgCodeEvalInput::resultFormat); }

haxorg_OrgCodeEvalInputResultHandling haxorg_OrgCodeEvalInput_get_resultHandling(OrgContext* org_context, haxorg_OrgCodeEvalInput __this) { return org::bind::c::get_cpp_field<haxorg_OrgCodeEvalInputResultHandling, org::sem::OrgCodeEvalInput, org::sem::OrgCodeEvalInput::ResultHandling, haxorg_OrgCodeEvalInput>(org_context, __this, &org::sem::OrgCodeEvalInput::resultHandling); }

haxorg_HstdStr haxorg_OrgCodeEvalInput_get_language(OrgContext* org_context, haxorg_OrgCodeEvalInput __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgCodeEvalInput, hstd::Str, haxorg_OrgCodeEvalInput>(org_context, __this, &org::sem::OrgCodeEvalInput::language); }

haxorg_HstdVecOfOrgCodeEvalInputVar haxorg_OrgCodeEvalInput_get_argList(OrgContext* org_context, haxorg_OrgCodeEvalInput __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfOrgCodeEvalInputVar, org::sem::OrgCodeEvalInput, hstd::Vec<org::sem::OrgCodeEvalInput::Var>, haxorg_OrgCodeEvalInput>(org_context, __this, &org::sem::OrgCodeEvalInput::argList); }

bool haxorg_OrgCodeEvalInput___eq___const(OrgContext* org_context, haxorg_OrgCodeEvalInput __this, haxorg_OrgCodeEvalInput other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::OrgCodeEvalInput::*)(org::sem::OrgCodeEvalInput const&) const>(&org::sem::OrgCodeEvalInput::operator==), org_context, __this, other); }

haxorg_OptOfOrgCodeEvalInputVar haxorg_OrgCodeEvalInput_getVariable_const(OrgContext* org_context, haxorg_OrgCodeEvalInput __this, haxorg_HstdStr name) { return org::bind::c::execute_cpp<haxorg_OptOfOrgCodeEvalInputVar>(static_cast<hstd::Opt<org::sem::OrgCodeEvalInput::Var>(org::sem::OrgCodeEvalInput::*)(hstd::Str const&) const>(&org::sem::OrgCodeEvalInput::getVariable), org_context, __this, name); }

haxorg_HstdStr haxorg_OrgCodeEvalInputVar_get_name(OrgContext* org_context, haxorg_OrgCodeEvalInputVar __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgCodeEvalInput::Var, hstd::Str, haxorg_OrgCodeEvalInputVar>(org_context, __this, &org::sem::OrgCodeEvalInput::Var::name); }

haxorg_OrgJson haxorg_OrgCodeEvalInputVar_get_value(OrgContext* org_context, haxorg_OrgCodeEvalInputVar __this) { return org::bind::c::get_cpp_field<haxorg_OrgJson, org::sem::OrgCodeEvalInput::Var, org::sem::OrgJson, haxorg_OrgCodeEvalInputVar>(org_context, __this, &org::sem::OrgCodeEvalInput::Var::value); }

void haxorg_create_OrgCodeEvalInputVar_Var(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::OrgCodeEvalInput::Var { return org::sem::OrgCodeEvalInput::Var(); }, org_context); }

bool haxorg_OrgCodeEvalInputVar___eq___const(OrgContext* org_context, haxorg_OrgCodeEvalInputVar __this, haxorg_OrgCodeEvalInputVar other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::OrgCodeEvalInput::Var::*)(org::sem::OrgCodeEvalInput::Var const&) const>(&org::sem::OrgCodeEvalInput::Var::operator==), org_context, __this, other); }

void haxorg_destroy_OrgCodeEvalInputVar(OrgContext* org_context, haxorg_OrgCodeEvalInputVar* obj) { org::bind::c::execute_destroy<org::sem::OrgCodeEvalInput::Var>(org_context, obj); }

void haxorg_destroy_OrgCodeEvalInput(OrgContext* org_context, haxorg_OrgCodeEvalInput* obj) { org::bind::c::execute_destroy<org::sem::OrgCodeEvalInput>(org_context, obj); }

haxorg_HstdStr haxorg_OrgCodeEvalOutput_get_stdoutText(OrgContext* org_context, haxorg_OrgCodeEvalOutput __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgCodeEvalOutput, hstd::Str, haxorg_OrgCodeEvalOutput>(org_context, __this, &org::sem::OrgCodeEvalOutput::stdoutText); }

haxorg_HstdStr haxorg_OrgCodeEvalOutput_get_stderrText(OrgContext* org_context, haxorg_OrgCodeEvalOutput __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgCodeEvalOutput, hstd::Str, haxorg_OrgCodeEvalOutput>(org_context, __this, &org::sem::OrgCodeEvalOutput::stderrText); }

int haxorg_OrgCodeEvalOutput_get_code(OrgContext* org_context, haxorg_OrgCodeEvalOutput __this) { return org::bind::c::get_cpp_field<int, org::sem::OrgCodeEvalOutput, int, haxorg_OrgCodeEvalOutput>(org_context, __this, &org::sem::OrgCodeEvalOutput::code); }

haxorg_OptOfStr haxorg_OrgCodeEvalOutput_get_cmd(OrgContext* org_context, haxorg_OrgCodeEvalOutput __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::OrgCodeEvalOutput, hstd::Opt<hstd::Str>, haxorg_OrgCodeEvalOutput>(org_context, __this, &org::sem::OrgCodeEvalOutput::cmd); }

haxorg_HstdVecOfStr haxorg_OrgCodeEvalOutput_get_args(OrgContext* org_context, haxorg_OrgCodeEvalOutput __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfStr, org::sem::OrgCodeEvalOutput, hstd::Vec<hstd::Str>, haxorg_OrgCodeEvalOutput>(org_context, __this, &org::sem::OrgCodeEvalOutput::args); }

haxorg_HstdStr haxorg_OrgCodeEvalOutput_get_cwd(OrgContext* org_context, haxorg_OrgCodeEvalOutput __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgCodeEvalOutput, hstd::Str, haxorg_OrgCodeEvalOutput>(org_context, __this, &org::sem::OrgCodeEvalOutput::cwd); }

haxorg_AttrGroup haxorg_OrgCodeEvalOutput_get_appliedHeaderArg(OrgContext* org_context, haxorg_OrgCodeEvalOutput __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::sem::OrgCodeEvalOutput, org::sem::AttrGroup, haxorg_OrgCodeEvalOutput>(org_context, __this, &org::sem::OrgCodeEvalOutput::appliedHeaderArg); }

bool haxorg_OrgCodeEvalOutput___eq___const(OrgContext* org_context, haxorg_OrgCodeEvalOutput __this, haxorg_OrgCodeEvalOutput other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::OrgCodeEvalOutput::*)(org::sem::OrgCodeEvalOutput const&) const>(&org::sem::OrgCodeEvalOutput::operator==), org_context, __this, other); }

void haxorg_destroy_OrgCodeEvalOutput(OrgContext* org_context, haxorg_OrgCodeEvalOutput* obj) { org::bind::c::execute_destroy<org::sem::OrgCodeEvalOutput>(org_context, obj); }

haxorg_HstdVecOfColumnViewColumn haxorg_ColumnView_get_columns(OrgContext* org_context, haxorg_ColumnView __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfColumnViewColumn, org::sem::ColumnView, hstd::Vec<org::sem::ColumnView::Column>, haxorg_ColumnView>(org_context, __this, &org::sem::ColumnView::columns); }

bool haxorg_ColumnView___eq___const(OrgContext* org_context, haxorg_ColumnView __this, haxorg_ColumnView other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::ColumnView::*)(org::sem::ColumnView const&) const>(&org::sem::ColumnView::operator==), org_context, __this, other); }

bool haxorg_ColumnViewSummary___eq___const(OrgContext* org_context, haxorg_ColumnViewSummary __this, haxorg_ColumnViewSummary other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::ColumnView::Summary::*)(org::sem::ColumnView::Summary const&) const>(&org::sem::ColumnView::Summary::operator==), org_context, __this, other); }

bool haxorg_ColumnViewSummary_isCheckboxAggregate_const(OrgContext* org_context, haxorg_ColumnViewSummary __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::isCheckboxAggregate), org_context, __this); }

haxorg_ColumnViewSummaryCheckboxAggregate haxorg_ColumnViewSummary_getCheckboxAggregateConst_const(OrgContext* org_context, haxorg_ColumnViewSummary __this) { return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryCheckboxAggregate>(static_cast<org::sem::ColumnView::Summary::CheckboxAggregate const&(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getCheckboxAggregate), org_context, __this); }

haxorg_ColumnViewSummaryCheckboxAggregate haxorg_ColumnViewSummary_getCheckboxAggregateMut(OrgContext* org_context, haxorg_ColumnViewSummary __this) { return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryCheckboxAggregate>(static_cast<org::sem::ColumnView::Summary::CheckboxAggregate&(org::sem::ColumnView::Summary::*)()>(&org::sem::ColumnView::Summary::getCheckboxAggregate), org_context, __this); }

bool haxorg_ColumnViewSummary_isMathAggregate_const(OrgContext* org_context, haxorg_ColumnViewSummary __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::isMathAggregate), org_context, __this); }

haxorg_ColumnViewSummaryMathAggregate haxorg_ColumnViewSummary_getMathAggregateConst_const(OrgContext* org_context, haxorg_ColumnViewSummary __this) { return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryMathAggregate>(static_cast<org::sem::ColumnView::Summary::MathAggregate const&(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getMathAggregate), org_context, __this); }

haxorg_ColumnViewSummaryMathAggregate haxorg_ColumnViewSummary_getMathAggregateMut(OrgContext* org_context, haxorg_ColumnViewSummary __this) { return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryMathAggregate>(static_cast<org::sem::ColumnView::Summary::MathAggregate&(org::sem::ColumnView::Summary::*)()>(&org::sem::ColumnView::Summary::getMathAggregate), org_context, __this); }

haxorg_ColumnViewSummaryKind haxorg_ColumnViewSummary_getKind_const(OrgContext* org_context, haxorg_ColumnViewSummary __this) { return org::bind::c::execute_cpp<haxorg_ColumnViewSummaryKind>(static_cast<org::sem::ColumnView::Summary::Kind(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getKind), org_context, __this); }

haxorg_ColumnViewSummaryCheckboxAggregateKind haxorg_ColumnViewSummaryCheckboxAggregate_get_kind(OrgContext* org_context, haxorg_ColumnViewSummaryCheckboxAggregate __this) { return org::bind::c::get_cpp_field<haxorg_ColumnViewSummaryCheckboxAggregateKind, org::sem::ColumnView::Summary::CheckboxAggregate, org::sem::ColumnView::Summary::CheckboxAggregate::Kind, haxorg_ColumnViewSummaryCheckboxAggregate>(org_context, __this, &org::sem::ColumnView::Summary::CheckboxAggregate::kind); }

bool haxorg_ColumnViewSummaryCheckboxAggregate___eq___const(OrgContext* org_context, haxorg_ColumnViewSummaryCheckboxAggregate __this, haxorg_ColumnViewSummaryCheckboxAggregate other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::ColumnView::Summary::CheckboxAggregate::*)(org::sem::ColumnView::Summary::CheckboxAggregate const&) const>(&org::sem::ColumnView::Summary::CheckboxAggregate::operator==), org_context, __this, other); }

void haxorg_destroy_ColumnViewSummaryCheckboxAggregate(OrgContext* org_context, haxorg_ColumnViewSummaryCheckboxAggregate* obj) { org::bind::c::execute_destroy<org::sem::ColumnView::Summary::CheckboxAggregate>(org_context, obj); }

haxorg_ColumnViewSummaryMathAggregateKind haxorg_ColumnViewSummaryMathAggregate_get_kind(OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate __this) { return org::bind::c::get_cpp_field<haxorg_ColumnViewSummaryMathAggregateKind, org::sem::ColumnView::Summary::MathAggregate, org::sem::ColumnView::Summary::MathAggregate::Kind, haxorg_ColumnViewSummaryMathAggregate>(org_context, __this, &org::sem::ColumnView::Summary::MathAggregate::kind); }

haxorg_OptOfInt haxorg_ColumnViewSummaryMathAggregate_get_formatDigits(OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate __this) { return org::bind::c::get_cpp_field<haxorg_OptOfInt, org::sem::ColumnView::Summary::MathAggregate, hstd::Opt<int>, haxorg_ColumnViewSummaryMathAggregate>(org_context, __this, &org::sem::ColumnView::Summary::MathAggregate::formatDigits); }

haxorg_OptOfInt haxorg_ColumnViewSummaryMathAggregate_get_formatPrecision(OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate __this) { return org::bind::c::get_cpp_field<haxorg_OptOfInt, org::sem::ColumnView::Summary::MathAggregate, hstd::Opt<int>, haxorg_ColumnViewSummaryMathAggregate>(org_context, __this, &org::sem::ColumnView::Summary::MathAggregate::formatPrecision); }

bool haxorg_ColumnViewSummaryMathAggregate___eq___const(OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate __this, haxorg_ColumnViewSummaryMathAggregate other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::ColumnView::Summary::MathAggregate::*)(org::sem::ColumnView::Summary::MathAggregate const&) const>(&org::sem::ColumnView::Summary::MathAggregate::operator==), org_context, __this, other); }

void haxorg_destroy_ColumnViewSummaryMathAggregate(OrgContext* org_context, haxorg_ColumnViewSummaryMathAggregate* obj) { org::bind::c::execute_destroy<org::sem::ColumnView::Summary::MathAggregate>(org_context, obj); }

void haxorg_destroy_ColumnViewSummary(OrgContext* org_context, haxorg_ColumnViewSummary* obj) { org::bind::c::execute_destroy<org::sem::ColumnView::Summary>(org_context, obj); }

haxorg_OptOfColumnViewSummary haxorg_ColumnViewColumn_get_summary(OrgContext* org_context, haxorg_ColumnViewColumn __this) { return org::bind::c::get_cpp_field<haxorg_OptOfColumnViewSummary, org::sem::ColumnView::Column, hstd::Opt<org::sem::ColumnView::Summary>, haxorg_ColumnViewColumn>(org_context, __this, &org::sem::ColumnView::Column::summary); }

haxorg_OptOfInt haxorg_ColumnViewColumn_get_width(OrgContext* org_context, haxorg_ColumnViewColumn __this) { return org::bind::c::get_cpp_field<haxorg_OptOfInt, org::sem::ColumnView::Column, hstd::Opt<int>, haxorg_ColumnViewColumn>(org_context, __this, &org::sem::ColumnView::Column::width); }

haxorg_OptOfStr haxorg_ColumnViewColumn_get_property(OrgContext* org_context, haxorg_ColumnViewColumn __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::ColumnView::Column, hstd::Opt<hstd::Str>, haxorg_ColumnViewColumn>(org_context, __this, &org::sem::ColumnView::Column::property); }

haxorg_OptOfStr haxorg_ColumnViewColumn_get_propertyTitle(OrgContext* org_context, haxorg_ColumnViewColumn __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::ColumnView::Column, hstd::Opt<hstd::Str>, haxorg_ColumnViewColumn>(org_context, __this, &org::sem::ColumnView::Column::propertyTitle); }

bool haxorg_ColumnViewColumn___eq___const(OrgContext* org_context, haxorg_ColumnViewColumn __this, haxorg_ColumnViewColumn other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::ColumnView::Column::*)(org::sem::ColumnView::Column const&) const>(&org::sem::ColumnView::Column::operator==), org_context, __this, other); }

void haxorg_destroy_ColumnViewColumn(OrgContext* org_context, haxorg_ColumnViewColumn* obj) { org::bind::c::execute_destroy<org::sem::ColumnView::Column>(org_context, obj); }

void haxorg_destroy_ColumnView(OrgContext* org_context, haxorg_ColumnView* obj) { org::bind::c::execute_destroy<org::sem::ColumnView>(org_context, obj); }

haxorg_HstdVecOfBlockCodeLinePart haxorg_BlockCodeLine_get_parts(OrgContext* org_context, haxorg_BlockCodeLine __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfBlockCodeLinePart, org::sem::BlockCodeLine, hstd::Vec<org::sem::BlockCodeLine::Part>, haxorg_BlockCodeLine>(org_context, __this, &org::sem::BlockCodeLine::parts); }

bool haxorg_BlockCodeLine___eq___const(OrgContext* org_context, haxorg_BlockCodeLine __this, haxorg_BlockCodeLine other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::BlockCodeLine::*)(org::sem::BlockCodeLine const&) const>(&org::sem::BlockCodeLine::operator==), org_context, __this, other); }

bool haxorg_BlockCodeLinePart___eq___const(OrgContext* org_context, haxorg_BlockCodeLinePart __this, haxorg_BlockCodeLinePart other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::BlockCodeLine::Part::*)(org::sem::BlockCodeLine::Part const&) const>(&org::sem::BlockCodeLine::Part::operator==), org_context, __this, other); }

bool haxorg_BlockCodeLinePart_isRaw_const(OrgContext* org_context, haxorg_BlockCodeLinePart __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isRaw), org_context, __this); }

haxorg_BlockCodeLinePartRaw haxorg_BlockCodeLinePart_getRawConst_const(OrgContext* org_context, haxorg_BlockCodeLinePart __this) { return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartRaw>(static_cast<org::sem::BlockCodeLine::Part::Raw const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getRaw), org_context, __this); }

haxorg_BlockCodeLinePartRaw haxorg_BlockCodeLinePart_getRawMut(OrgContext* org_context, haxorg_BlockCodeLinePart __this) { return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartRaw>(static_cast<org::sem::BlockCodeLine::Part::Raw&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getRaw), org_context, __this); }

bool haxorg_BlockCodeLinePart_isCallout_const(OrgContext* org_context, haxorg_BlockCodeLinePart __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isCallout), org_context, __this); }

haxorg_BlockCodeLinePartCallout haxorg_BlockCodeLinePart_getCalloutConst_const(OrgContext* org_context, haxorg_BlockCodeLinePart __this) { return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartCallout>(static_cast<org::sem::BlockCodeLine::Part::Callout const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getCallout), org_context, __this); }

haxorg_BlockCodeLinePartCallout haxorg_BlockCodeLinePart_getCalloutMut(OrgContext* org_context, haxorg_BlockCodeLinePart __this) { return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartCallout>(static_cast<org::sem::BlockCodeLine::Part::Callout&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getCallout), org_context, __this); }

bool haxorg_BlockCodeLinePart_isTangle_const(OrgContext* org_context, haxorg_BlockCodeLinePart __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isTangle), org_context, __this); }

haxorg_BlockCodeLinePartTangle haxorg_BlockCodeLinePart_getTangleConst_const(OrgContext* org_context, haxorg_BlockCodeLinePart __this) { return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartTangle>(static_cast<org::sem::BlockCodeLine::Part::Tangle const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getTangle), org_context, __this); }

haxorg_BlockCodeLinePartTangle haxorg_BlockCodeLinePart_getTangleMut(OrgContext* org_context, haxorg_BlockCodeLinePart __this) { return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartTangle>(static_cast<org::sem::BlockCodeLine::Part::Tangle&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getTangle), org_context, __this); }

haxorg_BlockCodeLinePartKind haxorg_BlockCodeLinePart_getKind_const(OrgContext* org_context, haxorg_BlockCodeLinePart __this) { return org::bind::c::execute_cpp<haxorg_BlockCodeLinePartKind>(static_cast<org::sem::BlockCodeLine::Part::Kind(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getKind), org_context, __this); }

haxorg_HstdStr haxorg_BlockCodeLinePartRaw_get_code(OrgContext* org_context, haxorg_BlockCodeLinePartRaw __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::BlockCodeLine::Part::Raw, hstd::Str, haxorg_BlockCodeLinePartRaw>(org_context, __this, &org::sem::BlockCodeLine::Part::Raw::code); }

bool haxorg_BlockCodeLinePartRaw___eq___const(OrgContext* org_context, haxorg_BlockCodeLinePartRaw __this, haxorg_BlockCodeLinePartRaw other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::BlockCodeLine::Part::Raw::*)(org::sem::BlockCodeLine::Part::Raw const&) const>(&org::sem::BlockCodeLine::Part::Raw::operator==), org_context, __this, other); }

void haxorg_destroy_BlockCodeLinePartRaw(OrgContext* org_context, haxorg_BlockCodeLinePartRaw* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine::Part::Raw>(org_context, obj); }

haxorg_HstdStr haxorg_BlockCodeLinePartCallout_get_name(OrgContext* org_context, haxorg_BlockCodeLinePartCallout __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::BlockCodeLine::Part::Callout, hstd::Str, haxorg_BlockCodeLinePartCallout>(org_context, __this, &org::sem::BlockCodeLine::Part::Callout::name); }

bool haxorg_BlockCodeLinePartCallout___eq___const(OrgContext* org_context, haxorg_BlockCodeLinePartCallout __this, haxorg_BlockCodeLinePartCallout other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::BlockCodeLine::Part::Callout::*)(org::sem::BlockCodeLine::Part::Callout const&) const>(&org::sem::BlockCodeLine::Part::Callout::operator==), org_context, __this, other); }

void haxorg_destroy_BlockCodeLinePartCallout(OrgContext* org_context, haxorg_BlockCodeLinePartCallout* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine::Part::Callout>(org_context, obj); }

haxorg_HstdStr haxorg_BlockCodeLinePartTangle_get_target(OrgContext* org_context, haxorg_BlockCodeLinePartTangle __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::BlockCodeLine::Part::Tangle, hstd::Str, haxorg_BlockCodeLinePartTangle>(org_context, __this, &org::sem::BlockCodeLine::Part::Tangle::target); }

bool haxorg_BlockCodeLinePartTangle___eq___const(OrgContext* org_context, haxorg_BlockCodeLinePartTangle __this, haxorg_BlockCodeLinePartTangle other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::BlockCodeLine::Part::Tangle::*)(org::sem::BlockCodeLine::Part::Tangle const&) const>(&org::sem::BlockCodeLine::Part::Tangle::operator==), org_context, __this, other); }

void haxorg_destroy_BlockCodeLinePartTangle(OrgContext* org_context, haxorg_BlockCodeLinePartTangle* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine::Part::Tangle>(org_context, obj); }

void haxorg_destroy_BlockCodeLinePart(OrgContext* org_context, haxorg_BlockCodeLinePart* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine::Part>(org_context, obj); }

void haxorg_destroy_BlockCodeLine(OrgContext* org_context, haxorg_BlockCodeLine* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeLine>(org_context, obj); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_inlinetasks(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::inlinetasks); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_footnotes(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::footnotes); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_clock(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::clock); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_author(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::author); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_emphasis(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::emphasis); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_specialStrings(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::specialStrings); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_propertyDrawers(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::propertyDrawers); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_statisticsCookies(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::statisticsCookies); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_todoText(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::todoText); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_smartQuotes(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::smartQuotes); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_fixedWidth(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::fixedWidth); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_timestamps(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::timestamps); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_preserveBreaks(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::preserveBreaks); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_subSuperscripts(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::subSuperscripts); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_expandLinks(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::expandLinks); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_creator(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::creator); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_drawers(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::drawers); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_date(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::date); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_entities(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::entities); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_email(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::email); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_sectionNumbers(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::sectionNumbers); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_planning(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::planning); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_priority(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::priority); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_latex(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::latex); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_timestamp(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::timestamp); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_title(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::title); }

haxorg_OptOfBool haxorg_DocumentExportConfig_get_tables(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentExportConfig, hstd::Opt<bool>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::tables); }

haxorg_OptOfInt haxorg_DocumentExportConfig_get_headlineLevels(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_OptOfInt, org::sem::DocumentExportConfig, hstd::Opt<int>, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::headlineLevels); }

haxorg_DocumentExportConfigBrokenLinks haxorg_DocumentExportConfig_get_brokenLinks(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_DocumentExportConfigBrokenLinks, org::sem::DocumentExportConfig, org::sem::DocumentExportConfig::BrokenLinks, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::brokenLinks); }

haxorg_DocumentExportConfigTagExport haxorg_DocumentExportConfig_get_tagExport(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_DocumentExportConfigTagExport, org::sem::DocumentExportConfig, org::sem::DocumentExportConfig::TagExport, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::tagExport); }

haxorg_DocumentExportConfigTaskFiltering haxorg_DocumentExportConfig_get_taskFiltering(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_DocumentExportConfigTaskFiltering, org::sem::DocumentExportConfig, org::sem::DocumentExportConfig::TaskFiltering, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::taskFiltering); }

haxorg_DocumentExportConfigArchivedTrees haxorg_DocumentExportConfig_get_archivedTrees(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::get_cpp_field<haxorg_DocumentExportConfigArchivedTrees, org::sem::DocumentExportConfig, org::sem::DocumentExportConfig::ArchivedTrees, haxorg_DocumentExportConfig>(org_context, __this, &org::sem::DocumentExportConfig::archivedTrees); }

bool haxorg_DocumentExportConfig___eq___const(OrgContext* org_context, haxorg_DocumentExportConfig __this, haxorg_DocumentExportConfig other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::DocumentExportConfig::*)(org::sem::DocumentExportConfig const&) const>(&org::sem::DocumentExportConfig::operator==), org_context, __this, other); }

bool haxorg_DocumentExportConfig_isDoExport_const(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isDoExport), org_context, __this); }

haxorg_DocumentExportConfigDoExport haxorg_DocumentExportConfig_getDoExportConst_const(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::execute_cpp<haxorg_DocumentExportConfigDoExport>(static_cast<org::sem::DocumentExportConfig::DoExport const&(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getDoExport), org_context, __this); }

haxorg_DocumentExportConfigDoExport haxorg_DocumentExportConfig_getDoExportMut(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::execute_cpp<haxorg_DocumentExportConfigDoExport>(static_cast<org::sem::DocumentExportConfig::DoExport&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getDoExport), org_context, __this); }

bool haxorg_DocumentExportConfig_isExportFixed_const(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isExportFixed), org_context, __this); }

haxorg_DocumentExportConfigExportFixed haxorg_DocumentExportConfig_getExportFixedConst_const(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::execute_cpp<haxorg_DocumentExportConfigExportFixed>(static_cast<org::sem::DocumentExportConfig::ExportFixed const&(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getExportFixed), org_context, __this); }

haxorg_DocumentExportConfigExportFixed haxorg_DocumentExportConfig_getExportFixedMut(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::execute_cpp<haxorg_DocumentExportConfigExportFixed>(static_cast<org::sem::DocumentExportConfig::ExportFixed&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getExportFixed), org_context, __this); }

haxorg_DocumentExportConfigTocExportKind haxorg_DocumentExportConfig_getTocExportKind_const(OrgContext* org_context, haxorg_DocumentExportConfig __this) { return org::bind::c::execute_cpp<haxorg_DocumentExportConfigTocExportKind>(static_cast<org::sem::DocumentExportConfig::TocExportKind(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getTocExportKind), org_context, __this); }

haxorg_HstdVecOfStr haxorg_DocumentExportConfigTaskExport_get_taskWhitelist(OrgContext* org_context, haxorg_DocumentExportConfigTaskExport __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfStr, org::sem::DocumentExportConfig::TaskExport, hstd::Vec<hstd::Str>, haxorg_DocumentExportConfigTaskExport>(org_context, __this, &org::sem::DocumentExportConfig::TaskExport::taskWhitelist); }

bool haxorg_DocumentExportConfigTaskExport___eq___const(OrgContext* org_context, haxorg_DocumentExportConfigTaskExport __this, haxorg_DocumentExportConfigTaskExport other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::DocumentExportConfig::TaskExport::*)(org::sem::DocumentExportConfig::TaskExport const&) const>(&org::sem::DocumentExportConfig::TaskExport::operator==), org_context, __this, other); }

void haxorg_destroy_DocumentExportConfigTaskExport(OrgContext* org_context, haxorg_DocumentExportConfigTaskExport* obj) { org::bind::c::execute_destroy<org::sem::DocumentExportConfig::TaskExport>(org_context, obj); }

bool haxorg_DocumentExportConfigDoExport_get_exportToc(OrgContext* org_context, haxorg_DocumentExportConfigDoExport __this) { return org::bind::c::get_cpp_field<bool, org::sem::DocumentExportConfig::DoExport, bool, haxorg_DocumentExportConfigDoExport>(org_context, __this, &org::sem::DocumentExportConfig::DoExport::exportToc); }

bool haxorg_DocumentExportConfigDoExport___eq___const(OrgContext* org_context, haxorg_DocumentExportConfigDoExport __this, haxorg_DocumentExportConfigDoExport other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::DocumentExportConfig::DoExport::*)(org::sem::DocumentExportConfig::DoExport const&) const>(&org::sem::DocumentExportConfig::DoExport::operator==), org_context, __this, other); }

void haxorg_destroy_DocumentExportConfigDoExport(OrgContext* org_context, haxorg_DocumentExportConfigDoExport* obj) { org::bind::c::execute_destroy<org::sem::DocumentExportConfig::DoExport>(org_context, obj); }

int haxorg_DocumentExportConfigExportFixed_get_exportLevels(OrgContext* org_context, haxorg_DocumentExportConfigExportFixed __this) { return org::bind::c::get_cpp_field<int, org::sem::DocumentExportConfig::ExportFixed, int, haxorg_DocumentExportConfigExportFixed>(org_context, __this, &org::sem::DocumentExportConfig::ExportFixed::exportLevels); }

bool haxorg_DocumentExportConfigExportFixed___eq___const(OrgContext* org_context, haxorg_DocumentExportConfigExportFixed __this, haxorg_DocumentExportConfigExportFixed other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::DocumentExportConfig::ExportFixed::*)(org::sem::DocumentExportConfig::ExportFixed const&) const>(&org::sem::DocumentExportConfig::ExportFixed::operator==), org_context, __this, other); }

void haxorg_destroy_DocumentExportConfigExportFixed(OrgContext* org_context, haxorg_DocumentExportConfigExportFixed* obj) { org::bind::c::execute_destroy<org::sem::DocumentExportConfig::ExportFixed>(org_context, obj); }

void haxorg_destroy_DocumentExportConfig(OrgContext* org_context, haxorg_DocumentExportConfig* obj) { org::bind::c::execute_destroy<org::sem::DocumentExportConfig>(org_context, obj); }

haxorg_SubtreePeriodKind haxorg_SubtreePeriod_get_kind(OrgContext* org_context, haxorg_SubtreePeriod __this) { return org::bind::c::get_cpp_field<haxorg_SubtreePeriodKind, org::sem::SubtreePeriod, org::sem::SubtreePeriod::Kind, haxorg_SubtreePeriod>(org_context, __this, &org::sem::SubtreePeriod::kind); }

haxorg_UserTime haxorg_SubtreePeriod_get_from(OrgContext* org_context, haxorg_SubtreePeriod __this) { return org::bind::c::get_cpp_field<haxorg_UserTime, org::sem::SubtreePeriod, hstd::UserTime, haxorg_SubtreePeriod>(org_context, __this, &org::sem::SubtreePeriod::from); }

haxorg_OptOfUserTime haxorg_SubtreePeriod_get_to(OrgContext* org_context, haxorg_SubtreePeriod __this) { return org::bind::c::get_cpp_field<haxorg_OptOfUserTime, org::sem::SubtreePeriod, hstd::Opt<hstd::UserTime>, haxorg_SubtreePeriod>(org_context, __this, &org::sem::SubtreePeriod::to); }

bool haxorg_SubtreePeriod___eq___const(OrgContext* org_context, haxorg_SubtreePeriod __this, haxorg_SubtreePeriod other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::SubtreePeriod::*)(org::sem::SubtreePeriod const&) const>(&org::sem::SubtreePeriod::operator==), org_context, __this, other); }

void haxorg_destroy_SubtreePeriod(OrgContext* org_context, haxorg_SubtreePeriod* obj) { org::bind::c::execute_destroy<org::sem::SubtreePeriod>(org_context, obj); }

bool haxorg_NamedProperty_isMatching_const(OrgContext* org_context, haxorg_NamedProperty __this, haxorg_HstdStr kind, haxorg_OptOfStr subKind) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::NamedProperty::isMatching), org_context, __this, kind, subKind); }

haxorg_HstdStr haxorg_NamedProperty_getName_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getName), org_context, __this); }

haxorg_OptOfStr haxorg_NamedProperty_getSubKind_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str>(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getSubKind), org_context, __this); }

bool haxorg_NamedProperty___eq___const(OrgContext* org_context, haxorg_NamedProperty __this, haxorg_NamedProperty other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)(org::sem::NamedProperty const&) const>(&org::sem::NamedProperty::operator==), org_context, __this, other); }

bool haxorg_NamedProperty_isNonblocking_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isNonblocking), org_context, __this); }

haxorg_NamedPropertyNonblocking haxorg_NamedProperty_getNonblockingConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyNonblocking>(static_cast<org::sem::NamedProperty::Nonblocking const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getNonblocking), org_context, __this); }

haxorg_NamedPropertyNonblocking haxorg_NamedProperty_getNonblockingMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyNonblocking>(static_cast<org::sem::NamedProperty::Nonblocking&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getNonblocking), org_context, __this); }

bool haxorg_NamedProperty_isArchiveTime_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTime), org_context, __this); }

haxorg_NamedPropertyArchiveTime haxorg_NamedProperty_getArchiveTimeConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTime>(static_cast<org::sem::NamedProperty::ArchiveTime const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTime), org_context, __this); }

haxorg_NamedPropertyArchiveTime haxorg_NamedProperty_getArchiveTimeMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTime>(static_cast<org::sem::NamedProperty::ArchiveTime&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTime), org_context, __this); }

bool haxorg_NamedProperty_isArchiveFile_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveFile), org_context, __this); }

haxorg_NamedPropertyArchiveFile haxorg_NamedProperty_getArchiveFileConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveFile>(static_cast<org::sem::NamedProperty::ArchiveFile const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveFile), org_context, __this); }

haxorg_NamedPropertyArchiveFile haxorg_NamedProperty_getArchiveFileMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveFile>(static_cast<org::sem::NamedProperty::ArchiveFile&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveFile), org_context, __this); }

bool haxorg_NamedProperty_isArchiveOlpath_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveOlpath), org_context, __this); }

haxorg_NamedPropertyArchiveOlpath haxorg_NamedProperty_getArchiveOlpathConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveOlpath>(static_cast<org::sem::NamedProperty::ArchiveOlpath const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveOlpath), org_context, __this); }

haxorg_NamedPropertyArchiveOlpath haxorg_NamedProperty_getArchiveOlpathMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveOlpath>(static_cast<org::sem::NamedProperty::ArchiveOlpath&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveOlpath), org_context, __this); }

bool haxorg_NamedProperty_isArchiveTarget_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTarget), org_context, __this); }

haxorg_NamedPropertyArchiveTarget haxorg_NamedProperty_getArchiveTargetConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTarget>(static_cast<org::sem::NamedProperty::ArchiveTarget const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTarget), org_context, __this); }

haxorg_NamedPropertyArchiveTarget haxorg_NamedProperty_getArchiveTargetMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTarget>(static_cast<org::sem::NamedProperty::ArchiveTarget&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTarget), org_context, __this); }

bool haxorg_NamedProperty_isArchiveCategory_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveCategory), org_context, __this); }

haxorg_NamedPropertyArchiveCategory haxorg_NamedProperty_getArchiveCategoryConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveCategory>(static_cast<org::sem::NamedProperty::ArchiveCategory const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveCategory), org_context, __this); }

haxorg_NamedPropertyArchiveCategory haxorg_NamedProperty_getArchiveCategoryMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveCategory>(static_cast<org::sem::NamedProperty::ArchiveCategory&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveCategory), org_context, __this); }

bool haxorg_NamedProperty_isArchiveTodo_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTodo), org_context, __this); }

haxorg_NamedPropertyArchiveTodo haxorg_NamedProperty_getArchiveTodoConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTodo>(static_cast<org::sem::NamedProperty::ArchiveTodo const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTodo), org_context, __this); }

haxorg_NamedPropertyArchiveTodo haxorg_NamedProperty_getArchiveTodoMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyArchiveTodo>(static_cast<org::sem::NamedProperty::ArchiveTodo&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTodo), org_context, __this); }

bool haxorg_NamedProperty_isTrigger_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isTrigger), org_context, __this); }

haxorg_NamedPropertyTrigger haxorg_NamedProperty_getTriggerConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyTrigger>(static_cast<org::sem::NamedProperty::Trigger const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getTrigger), org_context, __this); }

haxorg_NamedPropertyTrigger haxorg_NamedProperty_getTriggerMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyTrigger>(static_cast<org::sem::NamedProperty::Trigger&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getTrigger), org_context, __this); }

bool haxorg_NamedProperty_isExportLatexClass_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexClass), org_context, __this); }

haxorg_NamedPropertyExportLatexClass haxorg_NamedProperty_getExportLatexClassConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexClass>(static_cast<org::sem::NamedProperty::ExportLatexClass const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexClass), org_context, __this); }

haxorg_NamedPropertyExportLatexClass haxorg_NamedProperty_getExportLatexClassMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexClass>(static_cast<org::sem::NamedProperty::ExportLatexClass&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexClass), org_context, __this); }

bool haxorg_NamedProperty_isCookieData_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCookieData), org_context, __this); }

haxorg_NamedPropertyCookieData haxorg_NamedProperty_getCookieDataConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCookieData>(static_cast<org::sem::NamedProperty::CookieData const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCookieData), org_context, __this); }

haxorg_NamedPropertyCookieData haxorg_NamedProperty_getCookieDataMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCookieData>(static_cast<org::sem::NamedProperty::CookieData&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCookieData), org_context, __this); }

bool haxorg_NamedProperty_isExportLatexClassOptions_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexClassOptions), org_context, __this); }

haxorg_NamedPropertyExportLatexClassOptions haxorg_NamedProperty_getExportLatexClassOptionsConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexClassOptions>(static_cast<org::sem::NamedProperty::ExportLatexClassOptions const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexClassOptions), org_context, __this); }

haxorg_NamedPropertyExportLatexClassOptions haxorg_NamedProperty_getExportLatexClassOptionsMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexClassOptions>(static_cast<org::sem::NamedProperty::ExportLatexClassOptions&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexClassOptions), org_context, __this); }

bool haxorg_NamedProperty_isExportLatexHeader_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexHeader), org_context, __this); }

haxorg_NamedPropertyExportLatexHeader haxorg_NamedProperty_getExportLatexHeaderConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexHeader>(static_cast<org::sem::NamedProperty::ExportLatexHeader const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexHeader), org_context, __this); }

haxorg_NamedPropertyExportLatexHeader haxorg_NamedProperty_getExportLatexHeaderMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexHeader>(static_cast<org::sem::NamedProperty::ExportLatexHeader&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexHeader), org_context, __this); }

bool haxorg_NamedProperty_isExportLatexCompiler_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexCompiler), org_context, __this); }

haxorg_NamedPropertyExportLatexCompiler haxorg_NamedProperty_getExportLatexCompilerConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexCompiler>(static_cast<org::sem::NamedProperty::ExportLatexCompiler const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexCompiler), org_context, __this); }

haxorg_NamedPropertyExportLatexCompiler haxorg_NamedProperty_getExportLatexCompilerMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportLatexCompiler>(static_cast<org::sem::NamedProperty::ExportLatexCompiler&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexCompiler), org_context, __this); }

bool haxorg_NamedProperty_isOrdered_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isOrdered), org_context, __this); }

haxorg_NamedPropertyOrdered haxorg_NamedProperty_getOrderedConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyOrdered>(static_cast<org::sem::NamedProperty::Ordered const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getOrdered), org_context, __this); }

haxorg_NamedPropertyOrdered haxorg_NamedProperty_getOrderedMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyOrdered>(static_cast<org::sem::NamedProperty::Ordered&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getOrdered), org_context, __this); }

bool haxorg_NamedProperty_isEffort_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isEffort), org_context, __this); }

haxorg_NamedPropertyEffort haxorg_NamedProperty_getEffortConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyEffort>(static_cast<org::sem::NamedProperty::Effort const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getEffort), org_context, __this); }

haxorg_NamedPropertyEffort haxorg_NamedProperty_getEffortMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyEffort>(static_cast<org::sem::NamedProperty::Effort&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getEffort), org_context, __this); }

bool haxorg_NamedProperty_isVisibility_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isVisibility), org_context, __this); }

haxorg_NamedPropertyVisibility haxorg_NamedProperty_getVisibilityConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyVisibility>(static_cast<org::sem::NamedProperty::Visibility const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getVisibility), org_context, __this); }

haxorg_NamedPropertyVisibility haxorg_NamedProperty_getVisibilityMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyVisibility>(static_cast<org::sem::NamedProperty::Visibility&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getVisibility), org_context, __this); }

bool haxorg_NamedProperty_isExportOptions_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportOptions), org_context, __this); }

haxorg_NamedPropertyExportOptions haxorg_NamedProperty_getExportOptionsConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportOptions>(static_cast<org::sem::NamedProperty::ExportOptions const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportOptions), org_context, __this); }

haxorg_NamedPropertyExportOptions haxorg_NamedProperty_getExportOptionsMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyExportOptions>(static_cast<org::sem::NamedProperty::ExportOptions&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportOptions), org_context, __this); }

bool haxorg_NamedProperty_isBlocker_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isBlocker), org_context, __this); }

haxorg_NamedPropertyBlocker haxorg_NamedProperty_getBlockerConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyBlocker>(static_cast<org::sem::NamedProperty::Blocker const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getBlocker), org_context, __this); }

haxorg_NamedPropertyBlocker haxorg_NamedProperty_getBlockerMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyBlocker>(static_cast<org::sem::NamedProperty::Blocker&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getBlocker), org_context, __this); }

bool haxorg_NamedProperty_isUnnumbered_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isUnnumbered), org_context, __this); }

haxorg_NamedPropertyUnnumbered haxorg_NamedProperty_getUnnumberedConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyUnnumbered>(static_cast<org::sem::NamedProperty::Unnumbered const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getUnnumbered), org_context, __this); }

haxorg_NamedPropertyUnnumbered haxorg_NamedProperty_getUnnumberedMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyUnnumbered>(static_cast<org::sem::NamedProperty::Unnumbered&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getUnnumbered), org_context, __this); }

bool haxorg_NamedProperty_isCreated_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCreated), org_context, __this); }

haxorg_NamedPropertyCreated haxorg_NamedProperty_getCreatedConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCreated>(static_cast<org::sem::NamedProperty::Created const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCreated), org_context, __this); }

haxorg_NamedPropertyCreated haxorg_NamedProperty_getCreatedMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCreated>(static_cast<org::sem::NamedProperty::Created&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCreated), org_context, __this); }

bool haxorg_NamedProperty_isRadioId_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isRadioId), org_context, __this); }

haxorg_NamedPropertyRadioId haxorg_NamedProperty_getRadioIdConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyRadioId>(static_cast<org::sem::NamedProperty::RadioId const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getRadioId), org_context, __this); }

haxorg_NamedPropertyRadioId haxorg_NamedProperty_getRadioIdMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyRadioId>(static_cast<org::sem::NamedProperty::RadioId&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getRadioId), org_context, __this); }

bool haxorg_NamedProperty_isHashtagDef_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isHashtagDef), org_context, __this); }

haxorg_NamedPropertyHashtagDef haxorg_NamedProperty_getHashtagDefConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyHashtagDef>(static_cast<org::sem::NamedProperty::HashtagDef const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getHashtagDef), org_context, __this); }

haxorg_NamedPropertyHashtagDef haxorg_NamedProperty_getHashtagDefMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyHashtagDef>(static_cast<org::sem::NamedProperty::HashtagDef&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getHashtagDef), org_context, __this); }

bool haxorg_NamedProperty_isCustomArgs_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomArgs), org_context, __this); }

haxorg_NamedPropertyCustomArgs haxorg_NamedProperty_getCustomArgsConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomArgs>(static_cast<org::sem::NamedProperty::CustomArgs const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomArgs), org_context, __this); }

haxorg_NamedPropertyCustomArgs haxorg_NamedProperty_getCustomArgsMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomArgs>(static_cast<org::sem::NamedProperty::CustomArgs&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomArgs), org_context, __this); }

bool haxorg_NamedProperty_isCustomRaw_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomRaw), org_context, __this); }

haxorg_NamedPropertyCustomRaw haxorg_NamedProperty_getCustomRawConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomRaw>(static_cast<org::sem::NamedProperty::CustomRaw const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomRaw), org_context, __this); }

haxorg_NamedPropertyCustomRaw haxorg_NamedProperty_getCustomRawMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomRaw>(static_cast<org::sem::NamedProperty::CustomRaw&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomRaw), org_context, __this); }

bool haxorg_NamedProperty_isCustomId_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomId), org_context, __this); }

haxorg_NamedPropertyCustomId haxorg_NamedProperty_getCustomIdConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomId>(static_cast<org::sem::NamedProperty::CustomId const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomId), org_context, __this); }

haxorg_NamedPropertyCustomId haxorg_NamedProperty_getCustomIdMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomId>(static_cast<org::sem::NamedProperty::CustomId&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomId), org_context, __this); }

bool haxorg_NamedProperty_isCustomSubtreeJson_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeJson), org_context, __this); }

haxorg_NamedPropertyCustomSubtreeJson haxorg_NamedProperty_getCustomSubtreeJsonConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomSubtreeJson>(static_cast<org::sem::NamedProperty::CustomSubtreeJson const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomSubtreeJson), org_context, __this); }

haxorg_NamedPropertyCustomSubtreeJson haxorg_NamedProperty_getCustomSubtreeJsonMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomSubtreeJson>(static_cast<org::sem::NamedProperty::CustomSubtreeJson&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeJson), org_context, __this); }

bool haxorg_NamedProperty_isCustomSubtreeFlags_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeFlags), org_context, __this); }

haxorg_NamedPropertyCustomSubtreeFlags haxorg_NamedProperty_getCustomSubtreeFlagsConst_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomSubtreeFlags>(static_cast<org::sem::NamedProperty::CustomSubtreeFlags const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomSubtreeFlags), org_context, __this); }

haxorg_NamedPropertyCustomSubtreeFlags haxorg_NamedProperty_getCustomSubtreeFlagsMut(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyCustomSubtreeFlags>(static_cast<org::sem::NamedProperty::CustomSubtreeFlags&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeFlags), org_context, __this); }

haxorg_NamedPropertyKind haxorg_NamedProperty_getKind_const(OrgContext* org_context, haxorg_NamedProperty __this) { return org::bind::c::execute_cpp<haxorg_NamedPropertyKind>(static_cast<org::sem::NamedProperty::Kind(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getKind), org_context, __this); }

bool haxorg_NamedPropertyNonblocking_get_isBlocking(OrgContext* org_context, haxorg_NamedPropertyNonblocking __this) { return org::bind::c::get_cpp_field<bool, org::sem::NamedProperty::Nonblocking, bool, haxorg_NamedPropertyNonblocking>(org_context, __this, &org::sem::NamedProperty::Nonblocking::isBlocking); }

bool haxorg_NamedPropertyNonblocking___eq___const(OrgContext* org_context, haxorg_NamedPropertyNonblocking __this, haxorg_NamedPropertyNonblocking other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::Nonblocking::*)(org::sem::NamedProperty::Nonblocking const&) const>(&org::sem::NamedProperty::Nonblocking::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyNonblocking(OrgContext* org_context, haxorg_NamedPropertyNonblocking* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Nonblocking>(org_context, obj); }

haxorg_UserTime haxorg_NamedPropertyArchiveTime_get_time(OrgContext* org_context, haxorg_NamedPropertyArchiveTime __this) { return org::bind::c::get_cpp_field<haxorg_UserTime, org::sem::NamedProperty::ArchiveTime, hstd::UserTime, haxorg_NamedPropertyArchiveTime>(org_context, __this, &org::sem::NamedProperty::ArchiveTime::time); }

bool haxorg_NamedPropertyArchiveTime___eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveTime __this, haxorg_NamedPropertyArchiveTime other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::ArchiveTime::*)(org::sem::NamedProperty::ArchiveTime const&) const>(&org::sem::NamedProperty::ArchiveTime::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyArchiveTime(OrgContext* org_context, haxorg_NamedPropertyArchiveTime* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveTime>(org_context, obj); }

haxorg_HstdStr haxorg_NamedPropertyArchiveFile_get_file(OrgContext* org_context, haxorg_NamedPropertyArchiveFile __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::NamedProperty::ArchiveFile, hstd::Str, haxorg_NamedPropertyArchiveFile>(org_context, __this, &org::sem::NamedProperty::ArchiveFile::file); }

bool haxorg_NamedPropertyArchiveFile___eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveFile __this, haxorg_NamedPropertyArchiveFile other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::ArchiveFile::*)(org::sem::NamedProperty::ArchiveFile const&) const>(&org::sem::NamedProperty::ArchiveFile::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyArchiveFile(OrgContext* org_context, haxorg_NamedPropertyArchiveFile* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveFile>(org_context, obj); }

haxorg_SubtreePath haxorg_NamedPropertyArchiveOlpath_get_path(OrgContext* org_context, haxorg_NamedPropertyArchiveOlpath __this) { return org::bind::c::get_cpp_field<haxorg_SubtreePath, org::sem::NamedProperty::ArchiveOlpath, org::sem::SubtreePath, haxorg_NamedPropertyArchiveOlpath>(org_context, __this, &org::sem::NamedProperty::ArchiveOlpath::path); }

bool haxorg_NamedPropertyArchiveOlpath___eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveOlpath __this, haxorg_NamedPropertyArchiveOlpath other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::ArchiveOlpath::*)(org::sem::NamedProperty::ArchiveOlpath const&) const>(&org::sem::NamedProperty::ArchiveOlpath::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyArchiveOlpath(OrgContext* org_context, haxorg_NamedPropertyArchiveOlpath* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveOlpath>(org_context, obj); }

haxorg_SubtreePath haxorg_NamedPropertyArchiveTarget_get_path(OrgContext* org_context, haxorg_NamedPropertyArchiveTarget __this) { return org::bind::c::get_cpp_field<haxorg_SubtreePath, org::sem::NamedProperty::ArchiveTarget, org::sem::SubtreePath, haxorg_NamedPropertyArchiveTarget>(org_context, __this, &org::sem::NamedProperty::ArchiveTarget::path); }

haxorg_HstdStr haxorg_NamedPropertyArchiveTarget_get_pattern(OrgContext* org_context, haxorg_NamedPropertyArchiveTarget __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::NamedProperty::ArchiveTarget, hstd::Str, haxorg_NamedPropertyArchiveTarget>(org_context, __this, &org::sem::NamedProperty::ArchiveTarget::pattern); }

bool haxorg_NamedPropertyArchiveTarget___eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveTarget __this, haxorg_NamedPropertyArchiveTarget other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::ArchiveTarget::*)(org::sem::NamedProperty::ArchiveTarget const&) const>(&org::sem::NamedProperty::ArchiveTarget::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyArchiveTarget(OrgContext* org_context, haxorg_NamedPropertyArchiveTarget* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveTarget>(org_context, obj); }

haxorg_HstdStr haxorg_NamedPropertyArchiveCategory_get_category(OrgContext* org_context, haxorg_NamedPropertyArchiveCategory __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::NamedProperty::ArchiveCategory, hstd::Str, haxorg_NamedPropertyArchiveCategory>(org_context, __this, &org::sem::NamedProperty::ArchiveCategory::category); }

bool haxorg_NamedPropertyArchiveCategory___eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveCategory __this, haxorg_NamedPropertyArchiveCategory other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::ArchiveCategory::*)(org::sem::NamedProperty::ArchiveCategory const&) const>(&org::sem::NamedProperty::ArchiveCategory::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyArchiveCategory(OrgContext* org_context, haxorg_NamedPropertyArchiveCategory* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveCategory>(org_context, obj); }

haxorg_HstdStr haxorg_NamedPropertyArchiveTodo_get_todo(OrgContext* org_context, haxorg_NamedPropertyArchiveTodo __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::NamedProperty::ArchiveTodo, hstd::Str, haxorg_NamedPropertyArchiveTodo>(org_context, __this, &org::sem::NamedProperty::ArchiveTodo::todo); }

bool haxorg_NamedPropertyArchiveTodo___eq___const(OrgContext* org_context, haxorg_NamedPropertyArchiveTodo __this, haxorg_NamedPropertyArchiveTodo other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::ArchiveTodo::*)(org::sem::NamedProperty::ArchiveTodo const&) const>(&org::sem::NamedProperty::ArchiveTodo::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyArchiveTodo(OrgContext* org_context, haxorg_NamedPropertyArchiveTodo* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ArchiveTodo>(org_context, obj); }

bool haxorg_NamedPropertyTrigger___eq___const(OrgContext* org_context, haxorg_NamedPropertyTrigger __this, haxorg_NamedPropertyTrigger other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::Trigger::*)(org::sem::NamedProperty::Trigger const&) const>(&org::sem::NamedProperty::Trigger::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyTrigger(OrgContext* org_context, haxorg_NamedPropertyTrigger* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Trigger>(org_context, obj); }

haxorg_HstdStr haxorg_NamedPropertyExportLatexClass_get_latexClass(OrgContext* org_context, haxorg_NamedPropertyExportLatexClass __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::NamedProperty::ExportLatexClass, hstd::Str, haxorg_NamedPropertyExportLatexClass>(org_context, __this, &org::sem::NamedProperty::ExportLatexClass::latexClass); }

bool haxorg_NamedPropertyExportLatexClass___eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexClass __this, haxorg_NamedPropertyExportLatexClass other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::ExportLatexClass::*)(org::sem::NamedProperty::ExportLatexClass const&) const>(&org::sem::NamedProperty::ExportLatexClass::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyExportLatexClass(OrgContext* org_context, haxorg_NamedPropertyExportLatexClass* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportLatexClass>(org_context, obj); }

bool haxorg_NamedPropertyCookieData_get_isRecursive(OrgContext* org_context, haxorg_NamedPropertyCookieData __this) { return org::bind::c::get_cpp_field<bool, org::sem::NamedProperty::CookieData, bool, haxorg_NamedPropertyCookieData>(org_context, __this, &org::sem::NamedProperty::CookieData::isRecursive); }

haxorg_SubtreeTodoSource haxorg_NamedPropertyCookieData_get_source(OrgContext* org_context, haxorg_NamedPropertyCookieData __this) { return org::bind::c::get_cpp_field<haxorg_SubtreeTodoSource, org::sem::NamedProperty::CookieData, SubtreeTodoSource, haxorg_NamedPropertyCookieData>(org_context, __this, &org::sem::NamedProperty::CookieData::source); }

bool haxorg_NamedPropertyCookieData___eq___const(OrgContext* org_context, haxorg_NamedPropertyCookieData __this, haxorg_NamedPropertyCookieData other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::CookieData::*)(org::sem::NamedProperty::CookieData const&) const>(&org::sem::NamedProperty::CookieData::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyCookieData(OrgContext* org_context, haxorg_NamedPropertyCookieData* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CookieData>(org_context, obj); }

haxorg_HstdVecOfStr haxorg_NamedPropertyExportLatexClassOptions_get_options(OrgContext* org_context, haxorg_NamedPropertyExportLatexClassOptions __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfStr, org::sem::NamedProperty::ExportLatexClassOptions, hstd::Vec<hstd::Str>, haxorg_NamedPropertyExportLatexClassOptions>(org_context, __this, &org::sem::NamedProperty::ExportLatexClassOptions::options); }

bool haxorg_NamedPropertyExportLatexClassOptions___eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexClassOptions __this, haxorg_NamedPropertyExportLatexClassOptions other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::ExportLatexClassOptions::*)(org::sem::NamedProperty::ExportLatexClassOptions const&) const>(&org::sem::NamedProperty::ExportLatexClassOptions::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyExportLatexClassOptions(OrgContext* org_context, haxorg_NamedPropertyExportLatexClassOptions* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportLatexClassOptions>(org_context, obj); }

haxorg_HstdStr haxorg_NamedPropertyExportLatexHeader_get_header(OrgContext* org_context, haxorg_NamedPropertyExportLatexHeader __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::NamedProperty::ExportLatexHeader, hstd::Str, haxorg_NamedPropertyExportLatexHeader>(org_context, __this, &org::sem::NamedProperty::ExportLatexHeader::header); }

bool haxorg_NamedPropertyExportLatexHeader___eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexHeader __this, haxorg_NamedPropertyExportLatexHeader other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::ExportLatexHeader::*)(org::sem::NamedProperty::ExportLatexHeader const&) const>(&org::sem::NamedProperty::ExportLatexHeader::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyExportLatexHeader(OrgContext* org_context, haxorg_NamedPropertyExportLatexHeader* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportLatexHeader>(org_context, obj); }

haxorg_HstdStr haxorg_NamedPropertyExportLatexCompiler_get_compiler(OrgContext* org_context, haxorg_NamedPropertyExportLatexCompiler __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::NamedProperty::ExportLatexCompiler, hstd::Str, haxorg_NamedPropertyExportLatexCompiler>(org_context, __this, &org::sem::NamedProperty::ExportLatexCompiler::compiler); }

bool haxorg_NamedPropertyExportLatexCompiler___eq___const(OrgContext* org_context, haxorg_NamedPropertyExportLatexCompiler __this, haxorg_NamedPropertyExportLatexCompiler other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::ExportLatexCompiler::*)(org::sem::NamedProperty::ExportLatexCompiler const&) const>(&org::sem::NamedProperty::ExportLatexCompiler::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyExportLatexCompiler(OrgContext* org_context, haxorg_NamedPropertyExportLatexCompiler* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportLatexCompiler>(org_context, obj); }

bool haxorg_NamedPropertyOrdered_get_isOrdered(OrgContext* org_context, haxorg_NamedPropertyOrdered __this) { return org::bind::c::get_cpp_field<bool, org::sem::NamedProperty::Ordered, bool, haxorg_NamedPropertyOrdered>(org_context, __this, &org::sem::NamedProperty::Ordered::isOrdered); }

bool haxorg_NamedPropertyOrdered___eq___const(OrgContext* org_context, haxorg_NamedPropertyOrdered __this, haxorg_NamedPropertyOrdered other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::Ordered::*)(org::sem::NamedProperty::Ordered const&) const>(&org::sem::NamedProperty::Ordered::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyOrdered(OrgContext* org_context, haxorg_NamedPropertyOrdered* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Ordered>(org_context, obj); }

int haxorg_NamedPropertyEffort_get_hours(OrgContext* org_context, haxorg_NamedPropertyEffort __this) { return org::bind::c::get_cpp_field<int, org::sem::NamedProperty::Effort, int, haxorg_NamedPropertyEffort>(org_context, __this, &org::sem::NamedProperty::Effort::hours); }

int haxorg_NamedPropertyEffort_get_minutes(OrgContext* org_context, haxorg_NamedPropertyEffort __this) { return org::bind::c::get_cpp_field<int, org::sem::NamedProperty::Effort, int, haxorg_NamedPropertyEffort>(org_context, __this, &org::sem::NamedProperty::Effort::minutes); }

bool haxorg_NamedPropertyEffort___eq___const(OrgContext* org_context, haxorg_NamedPropertyEffort __this, haxorg_NamedPropertyEffort other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::Effort::*)(org::sem::NamedProperty::Effort const&) const>(&org::sem::NamedProperty::Effort::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyEffort(OrgContext* org_context, haxorg_NamedPropertyEffort* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Effort>(org_context, obj); }

haxorg_NamedPropertyVisibilityLevel haxorg_NamedPropertyVisibility_get_level(OrgContext* org_context, haxorg_NamedPropertyVisibility __this) { return org::bind::c::get_cpp_field<haxorg_NamedPropertyVisibilityLevel, org::sem::NamedProperty::Visibility, org::sem::NamedProperty::Visibility::Level, haxorg_NamedPropertyVisibility>(org_context, __this, &org::sem::NamedProperty::Visibility::level); }

bool haxorg_NamedPropertyVisibility___eq___const(OrgContext* org_context, haxorg_NamedPropertyVisibility __this, haxorg_NamedPropertyVisibility other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::Visibility::*)(org::sem::NamedProperty::Visibility const&) const>(&org::sem::NamedProperty::Visibility::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyVisibility(OrgContext* org_context, haxorg_NamedPropertyVisibility* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Visibility>(org_context, obj); }

haxorg_HstdStr haxorg_NamedPropertyExportOptions_get_backend(OrgContext* org_context, haxorg_NamedPropertyExportOptions __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::NamedProperty::ExportOptions, hstd::Str, haxorg_NamedPropertyExportOptions>(org_context, __this, &org::sem::NamedProperty::ExportOptions::backend); }

haxorg_HstdMap haxorg_NamedPropertyExportOptions_get_values(OrgContext* org_context, haxorg_NamedPropertyExportOptions __this) { return org::bind::c::get_cpp_field<haxorg_HstdMap, org::sem::NamedProperty::ExportOptions, hstd::UnorderedMap<hstd::Str, hstd::Str>, haxorg_NamedPropertyExportOptions>(org_context, __this, &org::sem::NamedProperty::ExportOptions::values); }

bool haxorg_NamedPropertyExportOptions___eq___const(OrgContext* org_context, haxorg_NamedPropertyExportOptions __this, haxorg_NamedPropertyExportOptions other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::ExportOptions::*)(org::sem::NamedProperty::ExportOptions const&) const>(&org::sem::NamedProperty::ExportOptions::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyExportOptions(OrgContext* org_context, haxorg_NamedPropertyExportOptions* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::ExportOptions>(org_context, obj); }

haxorg_HstdVecOfStr haxorg_NamedPropertyBlocker_get_blockers(OrgContext* org_context, haxorg_NamedPropertyBlocker __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfStr, org::sem::NamedProperty::Blocker, hstd::Vec<hstd::Str>, haxorg_NamedPropertyBlocker>(org_context, __this, &org::sem::NamedProperty::Blocker::blockers); }

bool haxorg_NamedPropertyBlocker___eq___const(OrgContext* org_context, haxorg_NamedPropertyBlocker __this, haxorg_NamedPropertyBlocker other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::Blocker::*)(org::sem::NamedProperty::Blocker const&) const>(&org::sem::NamedProperty::Blocker::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyBlocker(OrgContext* org_context, haxorg_NamedPropertyBlocker* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Blocker>(org_context, obj); }

bool haxorg_NamedPropertyUnnumbered___eq___const(OrgContext* org_context, haxorg_NamedPropertyUnnumbered __this, haxorg_NamedPropertyUnnumbered other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::Unnumbered::*)(org::sem::NamedProperty::Unnumbered const&) const>(&org::sem::NamedProperty::Unnumbered::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyUnnumbered(OrgContext* org_context, haxorg_NamedPropertyUnnumbered* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Unnumbered>(org_context, obj); }

haxorg_UserTime haxorg_NamedPropertyCreated_get_time(OrgContext* org_context, haxorg_NamedPropertyCreated __this) { return org::bind::c::get_cpp_field<haxorg_UserTime, org::sem::NamedProperty::Created, hstd::UserTime, haxorg_NamedPropertyCreated>(org_context, __this, &org::sem::NamedProperty::Created::time); }

bool haxorg_NamedPropertyCreated___eq___const(OrgContext* org_context, haxorg_NamedPropertyCreated __this, haxorg_NamedPropertyCreated other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::Created::*)(org::sem::NamedProperty::Created const&) const>(&org::sem::NamedProperty::Created::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyCreated(OrgContext* org_context, haxorg_NamedPropertyCreated* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::Created>(org_context, obj); }

haxorg_HstdVecOfStr haxorg_NamedPropertyRadioId_get_words(OrgContext* org_context, haxorg_NamedPropertyRadioId __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfStr, org::sem::NamedProperty::RadioId, hstd::Vec<hstd::Str>, haxorg_NamedPropertyRadioId>(org_context, __this, &org::sem::NamedProperty::RadioId::words); }

bool haxorg_NamedPropertyRadioId___eq___const(OrgContext* org_context, haxorg_NamedPropertyRadioId __this, haxorg_NamedPropertyRadioId other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::RadioId::*)(org::sem::NamedProperty::RadioId const&) const>(&org::sem::NamedProperty::RadioId::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyRadioId(OrgContext* org_context, haxorg_NamedPropertyRadioId* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::RadioId>(org_context, obj); }

haxorg_HashTagText haxorg_NamedPropertyHashtagDef_get_hashtag(OrgContext* org_context, haxorg_NamedPropertyHashtagDef __this) { return org::bind::c::get_cpp_field<haxorg_HashTagText, org::sem::NamedProperty::HashtagDef, org::sem::HashTagText, haxorg_NamedPropertyHashtagDef>(org_context, __this, &org::sem::NamedProperty::HashtagDef::hashtag); }

bool haxorg_NamedPropertyHashtagDef___eq___const(OrgContext* org_context, haxorg_NamedPropertyHashtagDef __this, haxorg_NamedPropertyHashtagDef other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::HashtagDef::*)(org::sem::NamedProperty::HashtagDef const&) const>(&org::sem::NamedProperty::HashtagDef::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyHashtagDef(OrgContext* org_context, haxorg_NamedPropertyHashtagDef* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::HashtagDef>(org_context, obj); }

haxorg_HstdStr haxorg_NamedPropertyCustomArgs_get_name(OrgContext* org_context, haxorg_NamedPropertyCustomArgs __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::NamedProperty::CustomArgs, hstd::Str, haxorg_NamedPropertyCustomArgs>(org_context, __this, &org::sem::NamedProperty::CustomArgs::name); }

haxorg_OptOfStr haxorg_NamedPropertyCustomArgs_get_sub(OrgContext* org_context, haxorg_NamedPropertyCustomArgs __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::NamedProperty::CustomArgs, hstd::Opt<hstd::Str>, haxorg_NamedPropertyCustomArgs>(org_context, __this, &org::sem::NamedProperty::CustomArgs::sub); }

haxorg_AttrGroup haxorg_NamedPropertyCustomArgs_get_attrs(OrgContext* org_context, haxorg_NamedPropertyCustomArgs __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::sem::NamedProperty::CustomArgs, org::sem::AttrGroup, haxorg_NamedPropertyCustomArgs>(org_context, __this, &org::sem::NamedProperty::CustomArgs::attrs); }

bool haxorg_NamedPropertyCustomArgs___eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomArgs __this, haxorg_NamedPropertyCustomArgs other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::CustomArgs::*)(org::sem::NamedProperty::CustomArgs const&) const>(&org::sem::NamedProperty::CustomArgs::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyCustomArgs(OrgContext* org_context, haxorg_NamedPropertyCustomArgs* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomArgs>(org_context, obj); }

haxorg_HstdStr haxorg_NamedPropertyCustomRaw_get_name(OrgContext* org_context, haxorg_NamedPropertyCustomRaw __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::NamedProperty::CustomRaw, hstd::Str, haxorg_NamedPropertyCustomRaw>(org_context, __this, &org::sem::NamedProperty::CustomRaw::name); }

haxorg_HstdStr haxorg_NamedPropertyCustomRaw_get_value(OrgContext* org_context, haxorg_NamedPropertyCustomRaw __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::NamedProperty::CustomRaw, hstd::Str, haxorg_NamedPropertyCustomRaw>(org_context, __this, &org::sem::NamedProperty::CustomRaw::value); }

bool haxorg_NamedPropertyCustomRaw___eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomRaw __this, haxorg_NamedPropertyCustomRaw other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::CustomRaw::*)(org::sem::NamedProperty::CustomRaw const&) const>(&org::sem::NamedProperty::CustomRaw::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyCustomRaw(OrgContext* org_context, haxorg_NamedPropertyCustomRaw* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomRaw>(org_context, obj); }

haxorg_HstdStr haxorg_NamedPropertyCustomId_get_value(OrgContext* org_context, haxorg_NamedPropertyCustomId __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::NamedProperty::CustomId, hstd::Str, haxorg_NamedPropertyCustomId>(org_context, __this, &org::sem::NamedProperty::CustomId::value); }

bool haxorg_NamedPropertyCustomId___eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomId __this, haxorg_NamedPropertyCustomId other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::CustomId::*)(org::sem::NamedProperty::CustomId const&) const>(&org::sem::NamedProperty::CustomId::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyCustomId(OrgContext* org_context, haxorg_NamedPropertyCustomId* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomId>(org_context, obj); }

haxorg_HstdStr haxorg_NamedPropertyCustomSubtreeJson_get_name(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeJson __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::NamedProperty::CustomSubtreeJson, hstd::Str, haxorg_NamedPropertyCustomSubtreeJson>(org_context, __this, &org::sem::NamedProperty::CustomSubtreeJson::name); }

haxorg_OrgJson haxorg_NamedPropertyCustomSubtreeJson_get_value(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeJson __this) { return org::bind::c::get_cpp_field<haxorg_OrgJson, org::sem::NamedProperty::CustomSubtreeJson, org::sem::OrgJson, haxorg_NamedPropertyCustomSubtreeJson>(org_context, __this, &org::sem::NamedProperty::CustomSubtreeJson::value); }

bool haxorg_NamedPropertyCustomSubtreeJson___eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeJson __this, haxorg_NamedPropertyCustomSubtreeJson other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::CustomSubtreeJson::*)(org::sem::NamedProperty::CustomSubtreeJson const&) const>(&org::sem::NamedProperty::CustomSubtreeJson::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyCustomSubtreeJson(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeJson* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomSubtreeJson>(org_context, obj); }

haxorg_HstdStr haxorg_NamedPropertyCustomSubtreeFlags_get_name(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeFlags __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::NamedProperty::CustomSubtreeFlags, hstd::Str, haxorg_NamedPropertyCustomSubtreeFlags>(org_context, __this, &org::sem::NamedProperty::CustomSubtreeFlags::name); }

haxorg_AttrGroup haxorg_NamedPropertyCustomSubtreeFlags_get_value(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeFlags __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::sem::NamedProperty::CustomSubtreeFlags, org::sem::AttrGroup, haxorg_NamedPropertyCustomSubtreeFlags>(org_context, __this, &org::sem::NamedProperty::CustomSubtreeFlags::value); }

bool haxorg_NamedPropertyCustomSubtreeFlags___eq___const(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeFlags __this, haxorg_NamedPropertyCustomSubtreeFlags other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::NamedProperty::CustomSubtreeFlags::*)(org::sem::NamedProperty::CustomSubtreeFlags const&) const>(&org::sem::NamedProperty::CustomSubtreeFlags::operator==), org_context, __this, other); }

void haxorg_destroy_NamedPropertyCustomSubtreeFlags(OrgContext* org_context, haxorg_NamedPropertyCustomSubtreeFlags* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty::CustomSubtreeFlags>(org_context, obj); }

void haxorg_destroy_NamedProperty(OrgContext* org_context, haxorg_NamedProperty* obj) { org::bind::c::execute_destroy<org::sem::NamedProperty>(org_context, obj); }

bool haxorg_OrgDiagnostics___eq___const(OrgContext* org_context, haxorg_OrgDiagnostics __this, haxorg_OrgDiagnostics other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::OrgDiagnostics::*)(org::sem::OrgDiagnostics const&) const>(&org::sem::OrgDiagnostics::operator==), org_context, __this, other); }

bool haxorg_OrgDiagnostics_isParseTokenError_const(OrgContext* org_context, haxorg_OrgDiagnostics __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isParseTokenError), org_context, __this); }

haxorg_OrgDiagnosticsParseTokenError haxorg_OrgDiagnostics_getParseTokenErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics __this) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsParseTokenError>(static_cast<org::sem::OrgDiagnostics::ParseTokenError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getParseTokenError), org_context, __this); }

haxorg_OrgDiagnosticsParseTokenError haxorg_OrgDiagnostics_getParseTokenErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics __this) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsParseTokenError>(static_cast<org::sem::OrgDiagnostics::ParseTokenError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getParseTokenError), org_context, __this); }

bool haxorg_OrgDiagnostics_isParseError_const(OrgContext* org_context, haxorg_OrgDiagnostics __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isParseError), org_context, __this); }

haxorg_OrgDiagnosticsParseError haxorg_OrgDiagnostics_getParseErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics __this) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsParseError>(static_cast<org::sem::OrgDiagnostics::ParseError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getParseError), org_context, __this); }

haxorg_OrgDiagnosticsParseError haxorg_OrgDiagnostics_getParseErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics __this) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsParseError>(static_cast<org::sem::OrgDiagnostics::ParseError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getParseError), org_context, __this); }

bool haxorg_OrgDiagnostics_isIncludeError_const(OrgContext* org_context, haxorg_OrgDiagnostics __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isIncludeError), org_context, __this); }

haxorg_OrgDiagnosticsIncludeError haxorg_OrgDiagnostics_getIncludeErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics __this) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsIncludeError>(static_cast<org::sem::OrgDiagnostics::IncludeError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getIncludeError), org_context, __this); }

haxorg_OrgDiagnosticsIncludeError haxorg_OrgDiagnostics_getIncludeErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics __this) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsIncludeError>(static_cast<org::sem::OrgDiagnostics::IncludeError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getIncludeError), org_context, __this); }

bool haxorg_OrgDiagnostics_isConvertError_const(OrgContext* org_context, haxorg_OrgDiagnostics __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isConvertError), org_context, __this); }

haxorg_OrgDiagnosticsConvertError haxorg_OrgDiagnostics_getConvertErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics __this) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsConvertError>(static_cast<org::sem::OrgDiagnostics::ConvertError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getConvertError), org_context, __this); }

haxorg_OrgDiagnosticsConvertError haxorg_OrgDiagnostics_getConvertErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics __this) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsConvertError>(static_cast<org::sem::OrgDiagnostics::ConvertError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getConvertError), org_context, __this); }

bool haxorg_OrgDiagnostics_isInternalError_const(OrgContext* org_context, haxorg_OrgDiagnostics __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isInternalError), org_context, __this); }

haxorg_OrgDiagnosticsInternalError haxorg_OrgDiagnostics_getInternalErrorConst_const(OrgContext* org_context, haxorg_OrgDiagnostics __this) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsInternalError>(static_cast<org::sem::OrgDiagnostics::InternalError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getInternalError), org_context, __this); }

haxorg_OrgDiagnosticsInternalError haxorg_OrgDiagnostics_getInternalErrorMut(OrgContext* org_context, haxorg_OrgDiagnostics __this) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsInternalError>(static_cast<org::sem::OrgDiagnostics::InternalError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getInternalError), org_context, __this); }

haxorg_OrgDiagnosticsKind haxorg_OrgDiagnostics_getKind_const(OrgContext* org_context, haxorg_OrgDiagnostics __this) { return org::bind::c::execute_cpp<haxorg_OrgDiagnosticsKind>(static_cast<org::sem::OrgDiagnostics::Kind(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getKind), org_context, __this); }

haxorg_HstdStr haxorg_OrgDiagnosticsParseTokenError_get_brief(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ParseTokenError, hstd::Str, haxorg_OrgDiagnosticsParseTokenError>(org_context, __this, &org::sem::OrgDiagnostics::ParseTokenError::brief); }

haxorg_HstdStr haxorg_OrgDiagnosticsParseTokenError_get_detail(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ParseTokenError, hstd::Str, haxorg_OrgDiagnosticsParseTokenError>(org_context, __this, &org::sem::OrgDiagnostics::ParseTokenError::detail); }

haxorg_HstdStr haxorg_OrgDiagnosticsParseTokenError_get_parserFunction(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ParseTokenError, hstd::Str, haxorg_OrgDiagnosticsParseTokenError>(org_context, __this, &org::sem::OrgDiagnostics::ParseTokenError::parserFunction); }

int haxorg_OrgDiagnosticsParseTokenError_get_parserLine(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this) { return org::bind::c::get_cpp_field<int, org::sem::OrgDiagnostics::ParseTokenError, int, haxorg_OrgDiagnosticsParseTokenError>(org_context, __this, &org::sem::OrgDiagnostics::ParseTokenError::parserLine); }

haxorg_OrgTokenKind haxorg_OrgDiagnosticsParseTokenError_get_tokenKind(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this) { return org::bind::c::get_cpp_field<haxorg_OrgTokenKind, org::sem::OrgDiagnostics::ParseTokenError, OrgTokenKind, haxorg_OrgDiagnosticsParseTokenError>(org_context, __this, &org::sem::OrgDiagnostics::ParseTokenError::tokenKind); }

haxorg_HstdStr haxorg_OrgDiagnosticsParseTokenError_get_tokenText(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ParseTokenError, hstd::Str, haxorg_OrgDiagnosticsParseTokenError>(org_context, __this, &org::sem::OrgDiagnostics::ParseTokenError::tokenText); }

haxorg_ParseSourceLoc haxorg_OrgDiagnosticsParseTokenError_get_loc(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this) { return org::bind::c::get_cpp_field<haxorg_ParseSourceLoc, org::sem::OrgDiagnostics::ParseTokenError, org::parse::SourceLoc, haxorg_OrgDiagnosticsParseTokenError>(org_context, __this, &org::sem::OrgDiagnostics::ParseTokenError::loc); }

haxorg_HstdStr haxorg_OrgDiagnosticsParseTokenError_get_errName(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ParseTokenError, hstd::Str, haxorg_OrgDiagnosticsParseTokenError>(org_context, __this, &org::sem::OrgDiagnostics::ParseTokenError::errName); }

haxorg_HstdStr haxorg_OrgDiagnosticsParseTokenError_get_errCode(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ParseTokenError, hstd::Str, haxorg_OrgDiagnosticsParseTokenError>(org_context, __this, &org::sem::OrgDiagnostics::ParseTokenError::errCode); }

bool haxorg_OrgDiagnosticsParseTokenError___eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError __this, haxorg_OrgDiagnosticsParseTokenError other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::OrgDiagnostics::ParseTokenError::*)(org::sem::OrgDiagnostics::ParseTokenError const&) const>(&org::sem::OrgDiagnostics::ParseTokenError::operator==), org_context, __this, other); }

void haxorg_destroy_OrgDiagnosticsParseTokenError(OrgContext* org_context, haxorg_OrgDiagnosticsParseTokenError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::ParseTokenError>(org_context, obj); }

haxorg_HstdStr haxorg_OrgDiagnosticsParseError_get_brief(OrgContext* org_context, haxorg_OrgDiagnosticsParseError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ParseError, hstd::Str, haxorg_OrgDiagnosticsParseError>(org_context, __this, &org::sem::OrgDiagnostics::ParseError::brief); }

haxorg_HstdStr haxorg_OrgDiagnosticsParseError_get_detail(OrgContext* org_context, haxorg_OrgDiagnosticsParseError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ParseError, hstd::Str, haxorg_OrgDiagnosticsParseError>(org_context, __this, &org::sem::OrgDiagnostics::ParseError::detail); }

haxorg_HstdStr haxorg_OrgDiagnosticsParseError_get_parserFunction(OrgContext* org_context, haxorg_OrgDiagnosticsParseError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ParseError, hstd::Str, haxorg_OrgDiagnosticsParseError>(org_context, __this, &org::sem::OrgDiagnostics::ParseError::parserFunction); }

int haxorg_OrgDiagnosticsParseError_get_parserLine(OrgContext* org_context, haxorg_OrgDiagnosticsParseError __this) { return org::bind::c::get_cpp_field<int, org::sem::OrgDiagnostics::ParseError, int, haxorg_OrgDiagnosticsParseError>(org_context, __this, &org::sem::OrgDiagnostics::ParseError::parserLine); }

haxorg_HstdStr haxorg_OrgDiagnosticsParseError_get_errName(OrgContext* org_context, haxorg_OrgDiagnosticsParseError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ParseError, hstd::Str, haxorg_OrgDiagnosticsParseError>(org_context, __this, &org::sem::OrgDiagnostics::ParseError::errName); }

haxorg_HstdStr haxorg_OrgDiagnosticsParseError_get_errCode(OrgContext* org_context, haxorg_OrgDiagnosticsParseError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ParseError, hstd::Str, haxorg_OrgDiagnosticsParseError>(org_context, __this, &org::sem::OrgDiagnostics::ParseError::errCode); }

haxorg_OptOfParseSourceLoc haxorg_OrgDiagnosticsParseError_get_loc(OrgContext* org_context, haxorg_OrgDiagnosticsParseError __this) { return org::bind::c::get_cpp_field<haxorg_OptOfParseSourceLoc, org::sem::OrgDiagnostics::ParseError, hstd::Opt<org::parse::SourceLoc>, haxorg_OrgDiagnosticsParseError>(org_context, __this, &org::sem::OrgDiagnostics::ParseError::loc); }

bool haxorg_OrgDiagnosticsParseError___eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsParseError __this, haxorg_OrgDiagnosticsParseError other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::OrgDiagnostics::ParseError::*)(org::sem::OrgDiagnostics::ParseError const&) const>(&org::sem::OrgDiagnostics::ParseError::operator==), org_context, __this, other); }

void haxorg_destroy_OrgDiagnosticsParseError(OrgContext* org_context, haxorg_OrgDiagnosticsParseError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::ParseError>(org_context, obj); }

haxorg_HstdStr haxorg_OrgDiagnosticsIncludeError_get_brief(OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::IncludeError, hstd::Str, haxorg_OrgDiagnosticsIncludeError>(org_context, __this, &org::sem::OrgDiagnostics::IncludeError::brief); }

haxorg_HstdStr haxorg_OrgDiagnosticsIncludeError_get_targetPath(OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::IncludeError, hstd::Str, haxorg_OrgDiagnosticsIncludeError>(org_context, __this, &org::sem::OrgDiagnostics::IncludeError::targetPath); }

haxorg_HstdStr haxorg_OrgDiagnosticsIncludeError_get_workingFile(OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::IncludeError, hstd::Str, haxorg_OrgDiagnosticsIncludeError>(org_context, __this, &org::sem::OrgDiagnostics::IncludeError::workingFile); }

bool haxorg_OrgDiagnosticsIncludeError___eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError __this, haxorg_OrgDiagnosticsIncludeError other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::OrgDiagnostics::IncludeError::*)(org::sem::OrgDiagnostics::IncludeError const&) const>(&org::sem::OrgDiagnostics::IncludeError::operator==), org_context, __this, other); }

void haxorg_destroy_OrgDiagnosticsIncludeError(OrgContext* org_context, haxorg_OrgDiagnosticsIncludeError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::IncludeError>(org_context, obj); }

haxorg_HstdStr haxorg_OrgDiagnosticsConvertError_get_brief(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ConvertError, hstd::Str, haxorg_OrgDiagnosticsConvertError>(org_context, __this, &org::sem::OrgDiagnostics::ConvertError::brief); }

haxorg_HstdStr haxorg_OrgDiagnosticsConvertError_get_detail(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ConvertError, hstd::Str, haxorg_OrgDiagnosticsConvertError>(org_context, __this, &org::sem::OrgDiagnostics::ConvertError::detail); }

haxorg_HstdStr haxorg_OrgDiagnosticsConvertError_get_convertFunction(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ConvertError, hstd::Str, haxorg_OrgDiagnosticsConvertError>(org_context, __this, &org::sem::OrgDiagnostics::ConvertError::convertFunction); }

int haxorg_OrgDiagnosticsConvertError_get_convertLine(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this) { return org::bind::c::get_cpp_field<int, org::sem::OrgDiagnostics::ConvertError, int, haxorg_OrgDiagnosticsConvertError>(org_context, __this, &org::sem::OrgDiagnostics::ConvertError::convertLine); }

haxorg_HstdStr haxorg_OrgDiagnosticsConvertError_get_convertFile(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ConvertError, hstd::Str, haxorg_OrgDiagnosticsConvertError>(org_context, __this, &org::sem::OrgDiagnostics::ConvertError::convertFile); }

haxorg_HstdStr haxorg_OrgDiagnosticsConvertError_get_errName(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ConvertError, hstd::Str, haxorg_OrgDiagnosticsConvertError>(org_context, __this, &org::sem::OrgDiagnostics::ConvertError::errName); }

haxorg_HstdStr haxorg_OrgDiagnosticsConvertError_get_errCode(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::ConvertError, hstd::Str, haxorg_OrgDiagnosticsConvertError>(org_context, __this, &org::sem::OrgDiagnostics::ConvertError::errCode); }

haxorg_OptOfParseSourceLoc haxorg_OrgDiagnosticsConvertError_get_loc(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this) { return org::bind::c::get_cpp_field<haxorg_OptOfParseSourceLoc, org::sem::OrgDiagnostics::ConvertError, hstd::Opt<org::parse::SourceLoc>, haxorg_OrgDiagnosticsConvertError>(org_context, __this, &org::sem::OrgDiagnostics::ConvertError::loc); }

bool haxorg_OrgDiagnosticsConvertError___eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError __this, haxorg_OrgDiagnosticsConvertError other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::OrgDiagnostics::ConvertError::*)(org::sem::OrgDiagnostics::ConvertError const&) const>(&org::sem::OrgDiagnostics::ConvertError::operator==), org_context, __this, other); }

void haxorg_destroy_OrgDiagnosticsConvertError(OrgContext* org_context, haxorg_OrgDiagnosticsConvertError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::ConvertError>(org_context, obj); }

haxorg_HstdStr haxorg_OrgDiagnosticsInternalError_get_message(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::InternalError, hstd::Str, haxorg_OrgDiagnosticsInternalError>(org_context, __this, &org::sem::OrgDiagnostics::InternalError::message); }

haxorg_HstdStr haxorg_OrgDiagnosticsInternalError_get_function(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::InternalError, hstd::Str, haxorg_OrgDiagnosticsInternalError>(org_context, __this, &org::sem::OrgDiagnostics::InternalError::function); }

int haxorg_OrgDiagnosticsInternalError_get_line(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError __this) { return org::bind::c::get_cpp_field<int, org::sem::OrgDiagnostics::InternalError, int, haxorg_OrgDiagnosticsInternalError>(org_context, __this, &org::sem::OrgDiagnostics::InternalError::line); }

haxorg_HstdStr haxorg_OrgDiagnosticsInternalError_get_file(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::OrgDiagnostics::InternalError, hstd::Str, haxorg_OrgDiagnosticsInternalError>(org_context, __this, &org::sem::OrgDiagnostics::InternalError::file); }

haxorg_OptOfParseSourceLoc haxorg_OrgDiagnosticsInternalError_get_loc(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError __this) { return org::bind::c::get_cpp_field<haxorg_OptOfParseSourceLoc, org::sem::OrgDiagnostics::InternalError, hstd::Opt<org::parse::SourceLoc>, haxorg_OrgDiagnosticsInternalError>(org_context, __this, &org::sem::OrgDiagnostics::InternalError::loc); }

bool haxorg_OrgDiagnosticsInternalError___eq___const(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError __this, haxorg_OrgDiagnosticsInternalError other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::OrgDiagnostics::InternalError::*)(org::sem::OrgDiagnostics::InternalError const&) const>(&org::sem::OrgDiagnostics::InternalError::operator==), org_context, __this, other); }

void haxorg_destroy_OrgDiagnosticsInternalError(OrgContext* org_context, haxorg_OrgDiagnosticsInternalError* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics::InternalError>(org_context, obj); }

void haxorg_destroy_OrgDiagnostics(OrgContext* org_context, haxorg_OrgDiagnostics* obj) { org::bind::c::execute_destroy<org::sem::OrgDiagnostics>(org_context, obj); }

void haxorg_destroy_NoNode(OrgContext* org_context, haxorg_NoNode* obj) { org::bind::c::execute_destroy<org::sem::NoNode>(org_context, obj); }

haxorg_OrgDiagnostics haxorg_ErrorItem_get_diag(OrgContext* org_context, haxorg_ErrorItem __this) { return org::bind::c::get_cpp_field<haxorg_OrgDiagnostics, org::sem::ErrorItem, org::sem::OrgDiagnostics, haxorg_ErrorItem>(org_context, __this, &org::sem::ErrorItem::diag); }

void haxorg_destroy_ErrorItem(OrgContext* org_context, haxorg_ErrorItem* obj) { org::bind::c::execute_destroy<org::sem::ErrorItem>(org_context, obj); }

haxorg_HstdVecOfSemIdOfErrorItem haxorg_ErrorGroup_get_diagnostics(OrgContext* org_context, haxorg_ErrorGroup __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSemIdOfErrorItem, org::sem::ErrorGroup, hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>, haxorg_ErrorGroup>(org_context, __this, &org::sem::ErrorGroup::diagnostics); }

void haxorg_destroy_ErrorGroup(OrgContext* org_context, haxorg_ErrorGroup* obj) { org::bind::c::execute_destroy<org::sem::ErrorGroup>(org_context, obj); }

haxorg_HstdVecOfSemIdOfOrg haxorg_Stmt_get_attached(OrgContext* org_context, haxorg_Stmt __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSemIdOfOrg, org::sem::Stmt, hstd::Vec<org::sem::SemId<org::sem::Org>>, haxorg_Stmt>(org_context, __this, &org::sem::Stmt::attached); }

haxorg_HstdVecOfSemIdOfOrg haxorg_Stmt_getAttached_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_OptOfStr kind) { return org::bind::c::execute_cpp<haxorg_HstdVecOfSemIdOfOrg>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt::getAttached), org_context, __this, kind); }

haxorg_HstdVecOfSemIdOfOrg haxorg_Stmt_getCaption_const(OrgContext* org_context, haxorg_Stmt __this) { return org::bind::c::execute_cpp<haxorg_HstdVecOfSemIdOfOrg>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt::*)() const>(&org::sem::Stmt::getCaption), org_context, __this); }

haxorg_HstdVecOfStr haxorg_Stmt_getName_const(OrgContext* org_context, haxorg_Stmt __this) { return org::bind::c::execute_cpp<haxorg_HstdVecOfStr>(static_cast<hstd::Vec<hstd::Str>(org::sem::Stmt::*)() const>(&org::sem::Stmt::getName), org_context, __this); }

haxorg_HstdVecOfAttrValue haxorg_Stmt_getAttrs_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_OptOfStr kind) { return org::bind::c::execute_cpp<haxorg_HstdVecOfAttrValue>(static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Stmt::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt::getAttrs), org_context, __this, kind); }

haxorg_OptOfAttrValue haxorg_Stmt_getFirstAttr_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_HstdStr kind) { return org::bind::c::execute_cpp<haxorg_OptOfAttrValue>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttr), org_context, __this, kind); }

haxorg_OptOfStr haxorg_Stmt_getFirstAttrString_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_HstdStr kind) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrString), org_context, __this, kind); }

haxorg_OptOfInt haxorg_Stmt_getFirstAttrInt_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_HstdStr kind) { return org::bind::c::execute_cpp<haxorg_OptOfInt>(static_cast<hstd::Opt<int>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrInt), org_context, __this, kind); }

haxorg_OptOfBool haxorg_Stmt_getFirstAttrBool_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_HstdStr kind) { return org::bind::c::execute_cpp<haxorg_OptOfBool>(static_cast<hstd::Opt<bool>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrBool), org_context, __this, kind); }

haxorg_OptOfDouble haxorg_Stmt_getFirstAttrDouble_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_HstdStr kind) { return org::bind::c::execute_cpp<haxorg_OptOfDouble>(static_cast<hstd::Opt<double>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrDouble), org_context, __this, kind); }

haxorg_OptOfAttrValueLispValue haxorg_Stmt_getFirstAttrLisp_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_HstdStr kind) { return org::bind::c::execute_cpp<haxorg_OptOfAttrValueLispValue>(static_cast<hstd::Opt<org::sem::AttrValue::LispValue>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrLisp), org_context, __this, kind); }

haxorg_OptOfAttrValueKind haxorg_Stmt_getFirstAttrKind_const(OrgContext* org_context, haxorg_Stmt __this, haxorg_HstdStr kind) { return org::bind::c::execute_cpp<haxorg_OptOfAttrValueKind>(static_cast<hstd::Opt<org::sem::AttrValue::Kind>(org::sem::Stmt::*)(hstd::Str const&) const>(&org::sem::Stmt::getFirstAttrKind), org_context, __this, kind); }

void haxorg_destroy_Stmt(OrgContext* org_context, haxorg_Stmt* obj) { org::bind::c::execute_destroy<org::sem::Stmt>(org_context, obj); }

void haxorg_destroy_Inline(OrgContext* org_context, haxorg_Inline* obj) { org::bind::c::execute_destroy<org::sem::Inline>(org_context, obj); }

void haxorg_destroy_StmtList(OrgContext* org_context, haxorg_StmtList* obj) { org::bind::c::execute_destroy<org::sem::StmtList>(org_context, obj); }

void haxorg_destroy_Empty(OrgContext* org_context, haxorg_Empty* obj) { org::bind::c::execute_destroy<org::sem::Empty>(org_context, obj); }

haxorg_HstdStr haxorg_Leaf_get_text(OrgContext* org_context, haxorg_Leaf __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::Leaf, hstd::Str, haxorg_Leaf>(org_context, __this, &org::sem::Leaf::text); }

haxorg_HstdStr haxorg_Leaf_getText_const(OrgContext* org_context, haxorg_Leaf __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str(org::sem::Leaf::*)() const>(&org::sem::Leaf::getText), org_context, __this); }

void haxorg_destroy_Leaf(OrgContext* org_context, haxorg_Leaf* obj) { org::bind::c::execute_destroy<org::sem::Leaf>(org_context, obj); }

bool haxorg_Time_get_isActive(OrgContext* org_context, haxorg_Time __this) { return org::bind::c::get_cpp_field<bool, org::sem::Time, bool, haxorg_Time>(org_context, __this, &org::sem::Time::isActive); }

haxorg_OptOfInt haxorg_Time_getYear_const(OrgContext* org_context, haxorg_Time __this) { return org::bind::c::execute_cpp<haxorg_OptOfInt>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getYear), org_context, __this); }

haxorg_OptOfInt haxorg_Time_getMonth_const(OrgContext* org_context, haxorg_Time __this) { return org::bind::c::execute_cpp<haxorg_OptOfInt>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getMonth), org_context, __this); }

haxorg_OptOfInt haxorg_Time_getDay_const(OrgContext* org_context, haxorg_Time __this) { return org::bind::c::execute_cpp<haxorg_OptOfInt>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getDay), org_context, __this); }

haxorg_OptOfInt haxorg_Time_getHour_const(OrgContext* org_context, haxorg_Time __this) { return org::bind::c::execute_cpp<haxorg_OptOfInt>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getHour), org_context, __this); }

haxorg_OptOfInt haxorg_Time_getMinute_const(OrgContext* org_context, haxorg_Time __this) { return org::bind::c::execute_cpp<haxorg_OptOfInt>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getMinute), org_context, __this); }

haxorg_OptOfInt haxorg_Time_getSecond_const(OrgContext* org_context, haxorg_Time __this) { return org::bind::c::execute_cpp<haxorg_OptOfInt>(static_cast<hstd::Opt<int>(org::sem::Time::*)() const>(&org::sem::Time::getSecond), org_context, __this); }

haxorg_UserTime haxorg_Time_getStaticTime_const(OrgContext* org_context, haxorg_Time __this) { return org::bind::c::execute_cpp<haxorg_UserTime>(static_cast<hstd::UserTime(org::sem::Time::*)() const>(&org::sem::Time::getStaticTime), org_context, __this); }

bool haxorg_Time_isStatic_const(OrgContext* org_context, haxorg_Time __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Time::*)() const>(&org::sem::Time::isStatic), org_context, __this); }

haxorg_TimeStatic haxorg_Time_getStaticConst_const(OrgContext* org_context, haxorg_Time __this) { return org::bind::c::execute_cpp<haxorg_TimeStatic>(static_cast<org::sem::Time::Static const&(org::sem::Time::*)() const>(&org::sem::Time::getStatic), org_context, __this); }

haxorg_TimeStatic haxorg_Time_getStaticMut(OrgContext* org_context, haxorg_Time __this) { return org::bind::c::execute_cpp<haxorg_TimeStatic>(static_cast<org::sem::Time::Static&(org::sem::Time::*)()>(&org::sem::Time::getStatic), org_context, __this); }

bool haxorg_Time_isDynamic_const(OrgContext* org_context, haxorg_Time __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Time::*)() const>(&org::sem::Time::isDynamic), org_context, __this); }

haxorg_TimeDynamic haxorg_Time_getDynamicConst_const(OrgContext* org_context, haxorg_Time __this) { return org::bind::c::execute_cpp<haxorg_TimeDynamic>(static_cast<org::sem::Time::Dynamic const&(org::sem::Time::*)() const>(&org::sem::Time::getDynamic), org_context, __this); }

haxorg_TimeDynamic haxorg_Time_getDynamicMut(OrgContext* org_context, haxorg_Time __this) { return org::bind::c::execute_cpp<haxorg_TimeDynamic>(static_cast<org::sem::Time::Dynamic&(org::sem::Time::*)()>(&org::sem::Time::getDynamic), org_context, __this); }

haxorg_TimeTimeKind haxorg_Time_getTimeKind_const(OrgContext* org_context, haxorg_Time __this) { return org::bind::c::execute_cpp<haxorg_TimeTimeKind>(static_cast<org::sem::Time::TimeKind(org::sem::Time::*)() const>(&org::sem::Time::getTimeKind), org_context, __this); }

haxorg_TimeRepeatMode haxorg_TimeRepeat_get_mode(OrgContext* org_context, haxorg_TimeRepeat __this) { return org::bind::c::get_cpp_field<haxorg_TimeRepeatMode, org::sem::Time::Repeat, org::sem::Time::Repeat::Mode, haxorg_TimeRepeat>(org_context, __this, &org::sem::Time::Repeat::mode); }

haxorg_TimeRepeatPeriod haxorg_TimeRepeat_get_period(OrgContext* org_context, haxorg_TimeRepeat __this) { return org::bind::c::get_cpp_field<haxorg_TimeRepeatPeriod, org::sem::Time::Repeat, org::sem::Time::Repeat::Period, haxorg_TimeRepeat>(org_context, __this, &org::sem::Time::Repeat::period); }

int haxorg_TimeRepeat_get_count(OrgContext* org_context, haxorg_TimeRepeat __this) { return org::bind::c::get_cpp_field<int, org::sem::Time::Repeat, int, haxorg_TimeRepeat>(org_context, __this, &org::sem::Time::Repeat::count); }

void haxorg_destroy_TimeRepeat(OrgContext* org_context, haxorg_TimeRepeat* obj) { org::bind::c::execute_destroy<org::sem::Time::Repeat>(org_context, obj); }

haxorg_HstdVecOfTimeRepeat haxorg_TimeStatic_get_repeat(OrgContext* org_context, haxorg_TimeStatic __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfTimeRepeat, org::sem::Time::Static, hstd::Vec<org::sem::Time::Repeat>, haxorg_TimeStatic>(org_context, __this, &org::sem::Time::Static::repeat); }

haxorg_OptOfTimeRepeat haxorg_TimeStatic_get_warn(OrgContext* org_context, haxorg_TimeStatic __this) { return org::bind::c::get_cpp_field<haxorg_OptOfTimeRepeat, org::sem::Time::Static, hstd::Opt<org::sem::Time::Repeat>, haxorg_TimeStatic>(org_context, __this, &org::sem::Time::Static::warn); }

haxorg_UserTime haxorg_TimeStatic_get_time(OrgContext* org_context, haxorg_TimeStatic __this) { return org::bind::c::get_cpp_field<haxorg_UserTime, org::sem::Time::Static, hstd::UserTime, haxorg_TimeStatic>(org_context, __this, &org::sem::Time::Static::time); }

void haxorg_create_TimeStatic_Static(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::Time::Static { return org::sem::Time::Static(); }, org_context); }

void haxorg_destroy_TimeStatic(OrgContext* org_context, haxorg_TimeStatic* obj) { org::bind::c::execute_destroy<org::sem::Time::Static>(org_context, obj); }

haxorg_LispCode haxorg_TimeDynamic_get_expr(OrgContext* org_context, haxorg_TimeDynamic __this) { return org::bind::c::get_cpp_field<haxorg_LispCode, org::sem::Time::Dynamic, org::sem::LispCode, haxorg_TimeDynamic>(org_context, __this, &org::sem::Time::Dynamic::expr); }

void haxorg_create_TimeDynamic_Dynamic(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::sem::Time::Dynamic { return org::sem::Time::Dynamic(); }, org_context); }

void haxorg_destroy_TimeDynamic(OrgContext* org_context, haxorg_TimeDynamic* obj) { org::bind::c::execute_destroy<org::sem::Time::Dynamic>(org_context, obj); }

void haxorg_destroy_Time(OrgContext* org_context, haxorg_Time* obj) { org::bind::c::execute_destroy<org::sem::Time>(org_context, obj); }

haxorg_SemIdOfOrg haxorg_TimeRange_get_from(OrgContext* org_context, haxorg_TimeRange __this) { return org::bind::c::get_cpp_field<haxorg_SemIdOfOrg, org::sem::TimeRange, org::sem::SemId<org::sem::Time>, haxorg_TimeRange>(org_context, __this, &org::sem::TimeRange::from); }

haxorg_SemIdOfOrg haxorg_TimeRange_get_to(OrgContext* org_context, haxorg_TimeRange __this) { return org::bind::c::get_cpp_field<haxorg_SemIdOfOrg, org::sem::TimeRange, org::sem::SemId<org::sem::Time>, haxorg_TimeRange>(org_context, __this, &org::sem::TimeRange::to); }

haxorg_OptOfInt64_t haxorg_TimeRange_getClockedTimeSeconds_const(OrgContext* org_context, haxorg_TimeRange __this) { return org::bind::c::execute_cpp<haxorg_OptOfInt64_t>(static_cast<hstd::Opt<int64_t>(org::sem::TimeRange::*)() const>(&org::sem::TimeRange::getClockedTimeSeconds), org_context, __this); }

void haxorg_destroy_TimeRange(OrgContext* org_context, haxorg_TimeRange* obj) { org::bind::c::execute_destroy<org::sem::TimeRange>(org_context, obj); }

haxorg_HstdStr haxorg_Macro_get_name(OrgContext* org_context, haxorg_Macro __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::Macro, hstd::Str, haxorg_Macro>(org_context, __this, &org::sem::Macro::name); }

haxorg_AttrGroup haxorg_Macro_get_attrs(OrgContext* org_context, haxorg_Macro __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::sem::Macro, org::sem::AttrGroup, haxorg_Macro>(org_context, __this, &org::sem::Macro::attrs); }

void haxorg_destroy_Macro(OrgContext* org_context, haxorg_Macro* obj) { org::bind::c::execute_destroy<org::sem::Macro>(org_context, obj); }

haxorg_HstdStr haxorg_Symbol_get_name(OrgContext* org_context, haxorg_Symbol __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::Symbol, hstd::Str, haxorg_Symbol>(org_context, __this, &org::sem::Symbol::name); }

haxorg_HstdVecOfSymbolParam haxorg_Symbol_get_parameters(OrgContext* org_context, haxorg_Symbol __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSymbolParam, org::sem::Symbol, hstd::Vec<org::sem::Symbol::Param>, haxorg_Symbol>(org_context, __this, &org::sem::Symbol::parameters); }

haxorg_HstdVecOfSemIdOfOrg haxorg_Symbol_get_positional(OrgContext* org_context, haxorg_Symbol __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSemIdOfOrg, org::sem::Symbol, hstd::Vec<org::sem::SemId<org::sem::Org>>, haxorg_Symbol>(org_context, __this, &org::sem::Symbol::positional); }

haxorg_OptOfStr haxorg_SymbolParam_get_key(OrgContext* org_context, haxorg_SymbolParam __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::Symbol::Param, hstd::Opt<hstd::Str>, haxorg_SymbolParam>(org_context, __this, &org::sem::Symbol::Param::key); }

haxorg_HstdStr haxorg_SymbolParam_get_value(OrgContext* org_context, haxorg_SymbolParam __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::Symbol::Param, hstd::Str, haxorg_SymbolParam>(org_context, __this, &org::sem::Symbol::Param::value); }

void haxorg_destroy_SymbolParam(OrgContext* org_context, haxorg_SymbolParam* obj) { org::bind::c::execute_destroy<org::sem::Symbol::Param>(org_context, obj); }

void haxorg_destroy_Symbol(OrgContext* org_context, haxorg_Symbol* obj) { org::bind::c::execute_destroy<org::sem::Symbol>(org_context, obj); }

haxorg_HstdVecOfSemIdOfErrorSkipToken haxorg_ErrorSkipGroup_get_skipped(OrgContext* org_context, haxorg_ErrorSkipGroup __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSemIdOfErrorSkipToken, org::sem::ErrorSkipGroup, hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>, haxorg_ErrorSkipGroup>(org_context, __this, &org::sem::ErrorSkipGroup::skipped); }

void haxorg_destroy_ErrorSkipGroup(OrgContext* org_context, haxorg_ErrorSkipGroup* obj) { org::bind::c::execute_destroy<org::sem::ErrorSkipGroup>(org_context, obj); }

void haxorg_destroy_Markup(OrgContext* org_context, haxorg_Markup* obj) { org::bind::c::execute_destroy<org::sem::Markup>(org_context, obj); }

haxorg_HstdVecOfStr haxorg_RadioTarget_get_words(OrgContext* org_context, haxorg_RadioTarget __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfStr, org::sem::RadioTarget, hstd::Vec<hstd::Str>, haxorg_RadioTarget>(org_context, __this, &org::sem::RadioTarget::words); }

void haxorg_destroy_RadioTarget(OrgContext* org_context, haxorg_RadioTarget* obj) { org::bind::c::execute_destroy<org::sem::RadioTarget>(org_context, obj); }

void haxorg_destroy_Latex(OrgContext* org_context, haxorg_Latex* obj) { org::bind::c::execute_destroy<org::sem::Latex>(org_context, obj); }

haxorg_SubtreeLogHead haxorg_SubtreeLog_get_head(OrgContext* org_context, haxorg_SubtreeLog __this) { return org::bind::c::get_cpp_field<haxorg_SubtreeLogHead, org::sem::SubtreeLog, org::sem::SubtreeLogHead, haxorg_SubtreeLog>(org_context, __this, &org::sem::SubtreeLog::head); }

haxorg_OptOfSemIdOfStmtList haxorg_SubtreeLog_get_desc(OrgContext* org_context, haxorg_SubtreeLog __this) { return org::bind::c::get_cpp_field<haxorg_OptOfSemIdOfStmtList, org::sem::SubtreeLog, hstd::Opt<org::sem::SemId<org::sem::StmtList>>, haxorg_SubtreeLog>(org_context, __this, &org::sem::SubtreeLog::desc); }

void haxorg_SubtreeLog_setDescription(OrgContext* org_context, haxorg_SubtreeLog __this, haxorg_SemIdOfOrg desc) { return org::bind::c::execute_cpp<void>(static_cast<void(org::sem::SubtreeLog::*)(org::sem::SemId<org::sem::StmtList>)>(&org::sem::SubtreeLog::setDescription), org_context, __this, desc); }

void haxorg_destroy_SubtreeLog(OrgContext* org_context, haxorg_SubtreeLog* obj) { org::bind::c::execute_destroy<org::sem::SubtreeLog>(org_context, obj); }

int haxorg_Subtree_get_level(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::get_cpp_field<int, org::sem::Subtree, int, haxorg_Subtree>(org_context, __this, &org::sem::Subtree::level); }

haxorg_OptOfStr haxorg_Subtree_get_treeId(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::Subtree, hstd::Opt<hstd::Str>, haxorg_Subtree>(org_context, __this, &org::sem::Subtree::treeId); }

haxorg_OptOfStr haxorg_Subtree_get_todo(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::Subtree, hstd::Opt<hstd::Str>, haxorg_Subtree>(org_context, __this, &org::sem::Subtree::todo); }

haxorg_OptOfSubtreeCompletion haxorg_Subtree_get_completion(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::get_cpp_field<haxorg_OptOfSubtreeCompletion, org::sem::Subtree, hstd::Opt<org::sem::SubtreeCompletion>, haxorg_Subtree>(org_context, __this, &org::sem::Subtree::completion); }

haxorg_OptOfSemIdOfParagraph haxorg_Subtree_get_description(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::get_cpp_field<haxorg_OptOfSemIdOfParagraph, org::sem::Subtree, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>, haxorg_Subtree>(org_context, __this, &org::sem::Subtree::description); }

haxorg_HstdVecOfSemIdOfHashTag haxorg_Subtree_get_tags(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSemIdOfHashTag, org::sem::Subtree, hstd::Vec<org::sem::SemId<org::sem::HashTag>>, haxorg_Subtree>(org_context, __this, &org::sem::Subtree::tags); }

haxorg_SemIdOfOrg haxorg_Subtree_get_title(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::get_cpp_field<haxorg_SemIdOfOrg, org::sem::Subtree, org::sem::SemId<org::sem::Paragraph>, haxorg_Subtree>(org_context, __this, &org::sem::Subtree::title); }

haxorg_HstdVecOfSemIdOfSubtreeLog haxorg_Subtree_get_logbook(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSemIdOfSubtreeLog, org::sem::Subtree, hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>, haxorg_Subtree>(org_context, __this, &org::sem::Subtree::logbook); }

haxorg_HstdVecOfNamedProperty haxorg_Subtree_get_properties(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfNamedProperty, org::sem::Subtree, hstd::Vec<org::sem::NamedProperty>, haxorg_Subtree>(org_context, __this, &org::sem::Subtree::properties); }

haxorg_OptOfSemIdOfTime haxorg_Subtree_get_closed(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::get_cpp_field<haxorg_OptOfSemIdOfTime, org::sem::Subtree, hstd::Opt<org::sem::SemId<org::sem::Time>>, haxorg_Subtree>(org_context, __this, &org::sem::Subtree::closed); }

haxorg_OptOfSemIdOfTime haxorg_Subtree_get_deadline(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::get_cpp_field<haxorg_OptOfSemIdOfTime, org::sem::Subtree, hstd::Opt<org::sem::SemId<org::sem::Time>>, haxorg_Subtree>(org_context, __this, &org::sem::Subtree::deadline); }

haxorg_OptOfSemIdOfTime haxorg_Subtree_get_scheduled(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::get_cpp_field<haxorg_OptOfSemIdOfTime, org::sem::Subtree, hstd::Opt<org::sem::SemId<org::sem::Time>>, haxorg_Subtree>(org_context, __this, &org::sem::Subtree::scheduled); }

bool haxorg_Subtree_get_isComment(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::get_cpp_field<bool, org::sem::Subtree, bool, haxorg_Subtree>(org_context, __this, &org::sem::Subtree::isComment); }

bool haxorg_Subtree_get_isArchived(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::get_cpp_field<bool, org::sem::Subtree, bool, haxorg_Subtree>(org_context, __this, &org::sem::Subtree::isArchived); }

haxorg_OptOfStr haxorg_Subtree_get_priority(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::Subtree, hstd::Opt<hstd::Str>, haxorg_Subtree>(org_context, __this, &org::sem::Subtree::priority); }

haxorg_HstdVecOfSubtreePeriod haxorg_Subtree_getTimePeriods_const(OrgContext* org_context, haxorg_Subtree __this, haxorg_IntSetOfSubtreePeriodKind kinds) { return org::bind::c::execute_cpp<haxorg_HstdVecOfSubtreePeriod>(static_cast<hstd::Vec<org::sem::SubtreePeriod>(org::sem::Subtree::*)(hstd::IntSet<org::sem::SubtreePeriod::Kind>) const>(&org::sem::Subtree::getTimePeriods), org_context, __this, kinds); }

haxorg_HstdVecOfNamedProperty haxorg_Subtree_getProperties_const(OrgContext* org_context, haxorg_Subtree __this, haxorg_HstdStr kind, haxorg_OptOfStr subkind) { return org::bind::c::execute_cpp<haxorg_HstdVecOfNamedProperty>(static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree::getProperties), org_context, __this, kind, subkind); }

haxorg_OptOfNamedProperty haxorg_Subtree_getProperty_const(OrgContext* org_context, haxorg_Subtree __this, haxorg_HstdStr kind, haxorg_OptOfStr subkind) { return org::bind::c::execute_cpp<haxorg_OptOfNamedProperty>(static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree::getProperty), org_context, __this, kind, subkind); }

void haxorg_Subtree_removeProperty(OrgContext* org_context, haxorg_Subtree __this, haxorg_HstdStr kind, haxorg_OptOfStr subkind) { return org::bind::c::execute_cpp<void>(static_cast<void(org::sem::Subtree::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree::removeProperty), org_context, __this, kind, subkind); }

void haxorg_Subtree_setProperty(OrgContext* org_context, haxorg_Subtree __this, haxorg_NamedProperty value) { return org::bind::c::execute_cpp<void>(static_cast<void(org::sem::Subtree::*)(org::sem::NamedProperty const&)>(&org::sem::Subtree::setProperty), org_context, __this, value); }

void haxorg_Subtree_setPropertyStrValue(OrgContext* org_context, haxorg_Subtree __this, haxorg_HstdStr value, haxorg_HstdStr kind, haxorg_OptOfStr subkind) { return org::bind::c::execute_cpp<void>(static_cast<void(org::sem::Subtree::*)(hstd::Str const&, hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree::setPropertyStrValue), org_context, __this, value, kind, subkind); }

haxorg_HstdStr haxorg_Subtree_getCleanTitle_const(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str(org::sem::Subtree::*)() const>(&org::sem::Subtree::getCleanTitle), org_context, __this); }

haxorg_OptOfStr haxorg_Subtree_getTodoKeyword_const(OrgContext* org_context, haxorg_Subtree __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str>(org::sem::Subtree::*)() const>(&org::sem::Subtree::getTodoKeyword), org_context, __this); }

void haxorg_destroy_Subtree(OrgContext* org_context, haxorg_Subtree* obj) { org::bind::c::execute_destroy<org::sem::Subtree>(org_context, obj); }

void haxorg_destroy_ColonExample(OrgContext* org_context, haxorg_ColonExample* obj) { org::bind::c::execute_destroy<org::sem::ColonExample>(org_context, obj); }

haxorg_HstdStr haxorg_Call_get_name(OrgContext* org_context, haxorg_Call __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::Call, hstd::Str, haxorg_Call>(org_context, __this, &org::sem::Call::name); }

haxorg_AttrGroup haxorg_Call_get_attrs(OrgContext* org_context, haxorg_Call __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::sem::Call, org::sem::AttrGroup, haxorg_Call>(org_context, __this, &org::sem::Call::attrs); }

bool haxorg_Call_get_isCommand(OrgContext* org_context, haxorg_Call __this) { return org::bind::c::get_cpp_field<bool, org::sem::Call, bool, haxorg_Call>(org_context, __this, &org::sem::Call::isCommand); }

void haxorg_destroy_Call(OrgContext* org_context, haxorg_Call* obj) { org::bind::c::execute_destroy<org::sem::Call>(org_context, obj); }

haxorg_CheckboxState haxorg_ListItem_get_checkbox(OrgContext* org_context, haxorg_ListItem __this) { return org::bind::c::get_cpp_field<haxorg_CheckboxState, org::sem::ListItem, CheckboxState, haxorg_ListItem>(org_context, __this, &org::sem::ListItem::checkbox); }

haxorg_OptOfSemIdOfParagraph haxorg_ListItem_get_header(OrgContext* org_context, haxorg_ListItem __this) { return org::bind::c::get_cpp_field<haxorg_OptOfSemIdOfParagraph, org::sem::ListItem, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>, haxorg_ListItem>(org_context, __this, &org::sem::ListItem::header); }

haxorg_OptOfStr haxorg_ListItem_get_bullet(OrgContext* org_context, haxorg_ListItem __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::ListItem, hstd::Opt<hstd::Str>, haxorg_ListItem>(org_context, __this, &org::sem::ListItem::bullet); }

bool haxorg_ListItem_isDescriptionItem_const(OrgContext* org_context, haxorg_ListItem __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::ListItem::*)() const>(&org::sem::ListItem::isDescriptionItem), org_context, __this); }

haxorg_OptOfStr haxorg_ListItem_getCleanHeader_const(OrgContext* org_context, haxorg_ListItem __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str>(org::sem::ListItem::*)() const>(&org::sem::ListItem::getCleanHeader), org_context, __this); }

void haxorg_destroy_ListItem(OrgContext* org_context, haxorg_ListItem* obj) { org::bind::c::execute_destroy<org::sem::ListItem>(org_context, obj); }

haxorg_InitialSubtreeVisibility haxorg_DocumentOptions_get_initialVisibility(OrgContext* org_context, haxorg_DocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_InitialSubtreeVisibility, org::sem::DocumentOptions, InitialSubtreeVisibility, haxorg_DocumentOptions>(org_context, __this, &org::sem::DocumentOptions::initialVisibility); }

haxorg_HstdVecOfNamedProperty haxorg_DocumentOptions_get_properties(OrgContext* org_context, haxorg_DocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfNamedProperty, org::sem::DocumentOptions, hstd::Vec<org::sem::NamedProperty>, haxorg_DocumentOptions>(org_context, __this, &org::sem::DocumentOptions::properties); }

haxorg_DocumentExportConfig haxorg_DocumentOptions_get_exportConfig(OrgContext* org_context, haxorg_DocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_DocumentExportConfig, org::sem::DocumentOptions, org::sem::DocumentExportConfig, haxorg_DocumentOptions>(org_context, __this, &org::sem::DocumentOptions::exportConfig); }

haxorg_OptOfBool haxorg_DocumentOptions_get_fixedWidthSections(OrgContext* org_context, haxorg_DocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentOptions, hstd::Opt<bool>, haxorg_DocumentOptions>(org_context, __this, &org::sem::DocumentOptions::fixedWidthSections); }

haxorg_OptOfBool haxorg_DocumentOptions_get_startupIndented(OrgContext* org_context, haxorg_DocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::DocumentOptions, hstd::Opt<bool>, haxorg_DocumentOptions>(org_context, __this, &org::sem::DocumentOptions::startupIndented); }

haxorg_OptOfStr haxorg_DocumentOptions_get_category(OrgContext* org_context, haxorg_DocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::DocumentOptions, hstd::Opt<hstd::Str>, haxorg_DocumentOptions>(org_context, __this, &org::sem::DocumentOptions::category); }

haxorg_OptOfStr haxorg_DocumentOptions_get_setupfile(OrgContext* org_context, haxorg_DocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::DocumentOptions, hstd::Opt<hstd::Str>, haxorg_DocumentOptions>(org_context, __this, &org::sem::DocumentOptions::setupfile); }

haxorg_OptOfInt haxorg_DocumentOptions_get_maxSubtreeLevelExport(OrgContext* org_context, haxorg_DocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_OptOfInt, org::sem::DocumentOptions, hstd::Opt<int>, haxorg_DocumentOptions>(org_context, __this, &org::sem::DocumentOptions::maxSubtreeLevelExport); }

haxorg_OptOfColumnView haxorg_DocumentOptions_get_columns(OrgContext* org_context, haxorg_DocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_OptOfColumnView, org::sem::DocumentOptions, hstd::Opt<org::sem::ColumnView>, haxorg_DocumentOptions>(org_context, __this, &org::sem::DocumentOptions::columns); }

haxorg_HstdVecOfTodoKeyword haxorg_DocumentOptions_get_todoKeywords(OrgContext* org_context, haxorg_DocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfTodoKeyword, org::sem::DocumentOptions, hstd::Vec<org::sem::TodoKeyword>, haxorg_DocumentOptions>(org_context, __this, &org::sem::DocumentOptions::todoKeywords); }

haxorg_HstdVecOfTodoKeyword haxorg_DocumentOptions_get_doneKeywords(OrgContext* org_context, haxorg_DocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfTodoKeyword, org::sem::DocumentOptions, hstd::Vec<org::sem::TodoKeyword>, haxorg_DocumentOptions>(org_context, __this, &org::sem::DocumentOptions::doneKeywords); }

haxorg_HstdVecOfNamedProperty haxorg_DocumentOptions_getProperties_const(OrgContext* org_context, haxorg_DocumentOptions __this, haxorg_HstdStr kind, haxorg_OptOfStr subKind) { return org::bind::c::execute_cpp<haxorg_HstdVecOfNamedProperty>(static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::DocumentOptions::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions::getProperties), org_context, __this, kind, subKind); }

haxorg_OptOfNamedProperty haxorg_DocumentOptions_getProperty_const(OrgContext* org_context, haxorg_DocumentOptions __this, haxorg_HstdStr kind, haxorg_OptOfStr subKind) { return org::bind::c::execute_cpp<haxorg_OptOfNamedProperty>(static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::DocumentOptions::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions::getProperty), org_context, __this, kind, subKind); }

void haxorg_destroy_DocumentOptions(OrgContext* org_context, haxorg_DocumentOptions* obj) { org::bind::c::execute_destroy<org::sem::DocumentOptions>(org_context, obj); }

int haxorg_DocumentFragment_get_baseLine(OrgContext* org_context, haxorg_DocumentFragment __this) { return org::bind::c::get_cpp_field<int, org::sem::DocumentFragment, int, haxorg_DocumentFragment>(org_context, __this, &org::sem::DocumentFragment::baseLine); }

int haxorg_DocumentFragment_get_baseCol(OrgContext* org_context, haxorg_DocumentFragment __this) { return org::bind::c::get_cpp_field<int, org::sem::DocumentFragment, int, haxorg_DocumentFragment>(org_context, __this, &org::sem::DocumentFragment::baseCol); }

void haxorg_destroy_DocumentFragment(OrgContext* org_context, haxorg_DocumentFragment* obj) { org::bind::c::execute_destroy<org::sem::DocumentFragment>(org_context, obj); }

haxorg_CriticMarkupKind haxorg_CriticMarkup_get_kind(OrgContext* org_context, haxorg_CriticMarkup __this) { return org::bind::c::get_cpp_field<haxorg_CriticMarkupKind, org::sem::CriticMarkup, org::sem::CriticMarkup::Kind, haxorg_CriticMarkup>(org_context, __this, &org::sem::CriticMarkup::kind); }

void haxorg_destroy_CriticMarkup(OrgContext* org_context, haxorg_CriticMarkup* obj) { org::bind::c::execute_destroy<org::sem::CriticMarkup>(org_context, obj); }

haxorg_OptOfSemIdOfParagraph haxorg_Document_get_title(OrgContext* org_context, haxorg_Document __this) { return org::bind::c::get_cpp_field<haxorg_OptOfSemIdOfParagraph, org::sem::Document, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>, haxorg_Document>(org_context, __this, &org::sem::Document::title); }

haxorg_OptOfSemIdOfParagraph haxorg_Document_get_author(OrgContext* org_context, haxorg_Document __this) { return org::bind::c::get_cpp_field<haxorg_OptOfSemIdOfParagraph, org::sem::Document, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>, haxorg_Document>(org_context, __this, &org::sem::Document::author); }

haxorg_OptOfSemIdOfParagraph haxorg_Document_get_creator(OrgContext* org_context, haxorg_Document __this) { return org::bind::c::get_cpp_field<haxorg_OptOfSemIdOfParagraph, org::sem::Document, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>, haxorg_Document>(org_context, __this, &org::sem::Document::creator); }

haxorg_HstdVecOfSemIdOfHashTag haxorg_Document_get_filetags(OrgContext* org_context, haxorg_Document __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSemIdOfHashTag, org::sem::Document, hstd::Vec<org::sem::SemId<org::sem::HashTag>>, haxorg_Document>(org_context, __this, &org::sem::Document::filetags); }

haxorg_OptOfSemIdOfRawText haxorg_Document_get_email(OrgContext* org_context, haxorg_Document __this) { return org::bind::c::get_cpp_field<haxorg_OptOfSemIdOfRawText, org::sem::Document, hstd::Opt<org::sem::SemId<org::sem::RawText>>, haxorg_Document>(org_context, __this, &org::sem::Document::email); }

haxorg_HstdVecOfStr haxorg_Document_get_language(OrgContext* org_context, haxorg_Document __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfStr, org::sem::Document, hstd::Vec<hstd::Str>, haxorg_Document>(org_context, __this, &org::sem::Document::language); }

haxorg_SemIdOfOrg haxorg_Document_get_options(OrgContext* org_context, haxorg_Document __this) { return org::bind::c::get_cpp_field<haxorg_SemIdOfOrg, org::sem::Document, org::sem::SemId<org::sem::DocumentOptions>, haxorg_Document>(org_context, __this, &org::sem::Document::options); }

haxorg_OptOfStr haxorg_Document_get_exportFileName(OrgContext* org_context, haxorg_Document __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::Document, hstd::Opt<hstd::Str>, haxorg_Document>(org_context, __this, &org::sem::Document::exportFileName); }

haxorg_HstdVecOfNamedProperty haxorg_Document_getProperties_const(OrgContext* org_context, haxorg_Document __this, haxorg_HstdStr kind, haxorg_OptOfStr subKind) { return org::bind::c::execute_cpp<haxorg_HstdVecOfNamedProperty>(static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Document::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document::getProperties), org_context, __this, kind, subKind); }

haxorg_OptOfNamedProperty haxorg_Document_getProperty_const(OrgContext* org_context, haxorg_Document __this, haxorg_HstdStr kind, haxorg_OptOfStr subKind) { return org::bind::c::execute_cpp<haxorg_OptOfNamedProperty>(static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Document::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document::getProperty), org_context, __this, kind, subKind); }

void haxorg_destroy_Document(OrgContext* org_context, haxorg_Document* obj) { org::bind::c::execute_destroy<org::sem::Document>(org_context, obj); }

haxorg_HstdStr haxorg_FileTarget_get_path(OrgContext* org_context, haxorg_FileTarget __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::FileTarget, hstd::Str, haxorg_FileTarget>(org_context, __this, &org::sem::FileTarget::path); }

haxorg_OptOfInt haxorg_FileTarget_get_line(OrgContext* org_context, haxorg_FileTarget __this) { return org::bind::c::get_cpp_field<haxorg_OptOfInt, org::sem::FileTarget, hstd::Opt<int>, haxorg_FileTarget>(org_context, __this, &org::sem::FileTarget::line); }

haxorg_OptOfStr haxorg_FileTarget_get_searchTarget(OrgContext* org_context, haxorg_FileTarget __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::FileTarget, hstd::Opt<hstd::Str>, haxorg_FileTarget>(org_context, __this, &org::sem::FileTarget::searchTarget); }

bool haxorg_FileTarget_get_restrictToHeadlines(OrgContext* org_context, haxorg_FileTarget __this) { return org::bind::c::get_cpp_field<bool, org::sem::FileTarget, bool, haxorg_FileTarget>(org_context, __this, &org::sem::FileTarget::restrictToHeadlines); }

haxorg_OptOfStr haxorg_FileTarget_get_targetId(OrgContext* org_context, haxorg_FileTarget __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::FileTarget, hstd::Opt<hstd::Str>, haxorg_FileTarget>(org_context, __this, &org::sem::FileTarget::targetId); }

haxorg_OptOfStr haxorg_FileTarget_get_regexp(OrgContext* org_context, haxorg_FileTarget __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::FileTarget, hstd::Opt<hstd::Str>, haxorg_FileTarget>(org_context, __this, &org::sem::FileTarget::regexp); }

void haxorg_destroy_FileTarget(OrgContext* org_context, haxorg_FileTarget* obj) { org::bind::c::execute_destroy<org::sem::FileTarget>(org_context, obj); }

void haxorg_destroy_TextSeparator(OrgContext* org_context, haxorg_TextSeparator* obj) { org::bind::c::execute_destroy<org::sem::TextSeparator>(org_context, obj); }

void haxorg_destroy_DocumentGroup(OrgContext* org_context, haxorg_DocumentGroup* obj) { org::bind::c::execute_destroy<org::sem::DocumentGroup>(org_context, obj); }

haxorg_HstdStr haxorg_File_get_relPath(OrgContext* org_context, haxorg_File __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::File, hstd::Str, haxorg_File>(org_context, __this, &org::sem::File::relPath); }

haxorg_HstdStr haxorg_File_get_absPath(OrgContext* org_context, haxorg_File __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::File, hstd::Str, haxorg_File>(org_context, __this, &org::sem::File::absPath); }

bool haxorg_File_isDocument_const(OrgContext* org_context, haxorg_File __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isDocument), org_context, __this); }

haxorg_FileDocument haxorg_File_getDocumentConst_const(OrgContext* org_context, haxorg_File __this) { return org::bind::c::execute_cpp<haxorg_FileDocument>(static_cast<org::sem::File::Document const&(org::sem::File::*)() const>(&org::sem::File::getDocument), org_context, __this); }

haxorg_FileDocument haxorg_File_getDocumentMut(OrgContext* org_context, haxorg_File __this) { return org::bind::c::execute_cpp<haxorg_FileDocument>(static_cast<org::sem::File::Document&(org::sem::File::*)()>(&org::sem::File::getDocument), org_context, __this); }

bool haxorg_File_isAttachment_const(OrgContext* org_context, haxorg_File __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isAttachment), org_context, __this); }

haxorg_FileAttachment haxorg_File_getAttachmentConst_const(OrgContext* org_context, haxorg_File __this) { return org::bind::c::execute_cpp<haxorg_FileAttachment>(static_cast<org::sem::File::Attachment const&(org::sem::File::*)() const>(&org::sem::File::getAttachment), org_context, __this); }

haxorg_FileAttachment haxorg_File_getAttachmentMut(OrgContext* org_context, haxorg_File __this) { return org::bind::c::execute_cpp<haxorg_FileAttachment>(static_cast<org::sem::File::Attachment&(org::sem::File::*)()>(&org::sem::File::getAttachment), org_context, __this); }

bool haxorg_File_isSource_const(OrgContext* org_context, haxorg_File __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::File::*)() const>(&org::sem::File::isSource), org_context, __this); }

haxorg_FileSource haxorg_File_getSourceConst_const(OrgContext* org_context, haxorg_File __this) { return org::bind::c::execute_cpp<haxorg_FileSource>(static_cast<org::sem::File::Source const&(org::sem::File::*)() const>(&org::sem::File::getSource), org_context, __this); }

haxorg_FileSource haxorg_File_getSourceMut(OrgContext* org_context, haxorg_File __this) { return org::bind::c::execute_cpp<haxorg_FileSource>(static_cast<org::sem::File::Source&(org::sem::File::*)()>(&org::sem::File::getSource), org_context, __this); }

haxorg_FileKind haxorg_File_getFileKind_const(OrgContext* org_context, haxorg_File __this) { return org::bind::c::execute_cpp<haxorg_FileKind>(static_cast<org::sem::File::Kind(org::sem::File::*)() const>(&org::sem::File::getFileKind), org_context, __this); }

void haxorg_destroy_FileDocument(OrgContext* org_context, haxorg_FileDocument* obj) { org::bind::c::execute_destroy<org::sem::File::Document>(org_context, obj); }

void haxorg_destroy_FileAttachment(OrgContext* org_context, haxorg_FileAttachment* obj) { org::bind::c::execute_destroy<org::sem::File::Attachment>(org_context, obj); }

void haxorg_destroy_FileSource(OrgContext* org_context, haxorg_FileSource* obj) { org::bind::c::execute_destroy<org::sem::File::Source>(org_context, obj); }

void haxorg_destroy_File(OrgContext* org_context, haxorg_File* obj) { org::bind::c::execute_destroy<org::sem::File>(org_context, obj); }

haxorg_HstdStr haxorg_Directory_get_relPath(OrgContext* org_context, haxorg_Directory __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::Directory, hstd::Str, haxorg_Directory>(org_context, __this, &org::sem::Directory::relPath); }

haxorg_HstdStr haxorg_Directory_get_absPath(OrgContext* org_context, haxorg_Directory __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::Directory, hstd::Str, haxorg_Directory>(org_context, __this, &org::sem::Directory::absPath); }

void haxorg_destroy_Directory(OrgContext* org_context, haxorg_Directory* obj) { org::bind::c::execute_destroy<org::sem::Directory>(org_context, obj); }

bool haxorg_Symlink_get_isDirectory(OrgContext* org_context, haxorg_Symlink __this) { return org::bind::c::get_cpp_field<bool, org::sem::Symlink, bool, haxorg_Symlink>(org_context, __this, &org::sem::Symlink::isDirectory); }

haxorg_HstdStr haxorg_Symlink_get_absPath(OrgContext* org_context, haxorg_Symlink __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::Symlink, hstd::Str, haxorg_Symlink>(org_context, __this, &org::sem::Symlink::absPath); }

void haxorg_destroy_Symlink(OrgContext* org_context, haxorg_Symlink* obj) { org::bind::c::execute_destroy<org::sem::Symlink>(org_context, obj); }

haxorg_HstdStr haxorg_CmdInclude_get_path(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::CmdInclude, hstd::Str, haxorg_CmdInclude>(org_context, __this, &org::sem::CmdInclude::path); }

haxorg_OptOfInt haxorg_CmdInclude_get_firstLine(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::get_cpp_field<haxorg_OptOfInt, org::sem::CmdInclude, hstd::Opt<int>, haxorg_CmdInclude>(org_context, __this, &org::sem::CmdInclude::firstLine); }

haxorg_OptOfInt haxorg_CmdInclude_get_lastLine(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::get_cpp_field<haxorg_OptOfInt, org::sem::CmdInclude, hstd::Opt<int>, haxorg_CmdInclude>(org_context, __this, &org::sem::CmdInclude::lastLine); }

bool haxorg_CmdInclude_isExample_const(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isExample), org_context, __this); }

haxorg_CmdIncludeExample haxorg_CmdInclude_getExampleConst_const(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::execute_cpp<haxorg_CmdIncludeExample>(static_cast<org::sem::CmdInclude::Example const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getExample), org_context, __this); }

haxorg_CmdIncludeExample haxorg_CmdInclude_getExampleMut(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::execute_cpp<haxorg_CmdIncludeExample>(static_cast<org::sem::CmdInclude::Example&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getExample), org_context, __this); }

bool haxorg_CmdInclude_isExport_const(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isExport), org_context, __this); }

haxorg_CmdIncludeExport haxorg_CmdInclude_getExportConst_const(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::execute_cpp<haxorg_CmdIncludeExport>(static_cast<org::sem::CmdInclude::Export const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getExport), org_context, __this); }

haxorg_CmdIncludeExport haxorg_CmdInclude_getExportMut(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::execute_cpp<haxorg_CmdIncludeExport>(static_cast<org::sem::CmdInclude::Export&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getExport), org_context, __this); }

bool haxorg_CmdInclude_isCustom_const(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isCustom), org_context, __this); }

haxorg_CmdIncludeCustom haxorg_CmdInclude_getCustomConst_const(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::execute_cpp<haxorg_CmdIncludeCustom>(static_cast<org::sem::CmdInclude::Custom const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getCustom), org_context, __this); }

haxorg_CmdIncludeCustom haxorg_CmdInclude_getCustomMut(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::execute_cpp<haxorg_CmdIncludeCustom>(static_cast<org::sem::CmdInclude::Custom&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getCustom), org_context, __this); }

bool haxorg_CmdInclude_isSrc_const(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isSrc), org_context, __this); }

haxorg_CmdIncludeSrc haxorg_CmdInclude_getSrcConst_const(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::execute_cpp<haxorg_CmdIncludeSrc>(static_cast<org::sem::CmdInclude::Src const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getSrc), org_context, __this); }

haxorg_CmdIncludeSrc haxorg_CmdInclude_getSrcMut(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::execute_cpp<haxorg_CmdIncludeSrc>(static_cast<org::sem::CmdInclude::Src&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getSrc), org_context, __this); }

bool haxorg_CmdInclude_isOrgDocument_const(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::isOrgDocument), org_context, __this); }

haxorg_CmdIncludeOrgDocument haxorg_CmdInclude_getOrgDocumentConst_const(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::execute_cpp<haxorg_CmdIncludeOrgDocument>(static_cast<org::sem::CmdInclude::OrgDocument const&(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getOrgDocument), org_context, __this); }

haxorg_CmdIncludeOrgDocument haxorg_CmdInclude_getOrgDocumentMut(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::execute_cpp<haxorg_CmdIncludeOrgDocument>(static_cast<org::sem::CmdInclude::OrgDocument&(org::sem::CmdInclude::*)()>(&org::sem::CmdInclude::getOrgDocument), org_context, __this); }

haxorg_CmdIncludeKind haxorg_CmdInclude_getIncludeKind_const(OrgContext* org_context, haxorg_CmdInclude __this) { return org::bind::c::execute_cpp<haxorg_CmdIncludeKind>(static_cast<org::sem::CmdInclude::Kind(org::sem::CmdInclude::*)() const>(&org::sem::CmdInclude::getIncludeKind), org_context, __this); }

void haxorg_destroy_CmdIncludeIncludeBase(OrgContext* org_context, haxorg_CmdIncludeIncludeBase* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::IncludeBase>(org_context, obj); }

void haxorg_destroy_CmdIncludeExample(OrgContext* org_context, haxorg_CmdIncludeExample* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::Example>(org_context, obj); }

haxorg_HstdStr haxorg_CmdIncludeExport_get_language(OrgContext* org_context, haxorg_CmdIncludeExport __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::CmdInclude::Export, hstd::Str, haxorg_CmdIncludeExport>(org_context, __this, &org::sem::CmdInclude::Export::language); }

void haxorg_destroy_CmdIncludeExport(OrgContext* org_context, haxorg_CmdIncludeExport* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::Export>(org_context, obj); }

haxorg_HstdStr haxorg_CmdIncludeCustom_get_blockName(OrgContext* org_context, haxorg_CmdIncludeCustom __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::CmdInclude::Custom, hstd::Str, haxorg_CmdIncludeCustom>(org_context, __this, &org::sem::CmdInclude::Custom::blockName); }

void haxorg_destroy_CmdIncludeCustom(OrgContext* org_context, haxorg_CmdIncludeCustom* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::Custom>(org_context, obj); }

haxorg_HstdStr haxorg_CmdIncludeSrc_get_language(OrgContext* org_context, haxorg_CmdIncludeSrc __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::CmdInclude::Src, hstd::Str, haxorg_CmdIncludeSrc>(org_context, __this, &org::sem::CmdInclude::Src::language); }

void haxorg_destroy_CmdIncludeSrc(OrgContext* org_context, haxorg_CmdIncludeSrc* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::Src>(org_context, obj); }

haxorg_OptOfBool haxorg_CmdIncludeOrgDocument_get_onlyContent(OrgContext* org_context, haxorg_CmdIncludeOrgDocument __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::sem::CmdInclude::OrgDocument, hstd::Opt<bool>, haxorg_CmdIncludeOrgDocument>(org_context, __this, &org::sem::CmdInclude::OrgDocument::onlyContent); }

haxorg_OptOfSubtreePath haxorg_CmdIncludeOrgDocument_get_subtreePath(OrgContext* org_context, haxorg_CmdIncludeOrgDocument __this) { return org::bind::c::get_cpp_field<haxorg_OptOfSubtreePath, org::sem::CmdInclude::OrgDocument, hstd::Opt<org::sem::SubtreePath>, haxorg_CmdIncludeOrgDocument>(org_context, __this, &org::sem::CmdInclude::OrgDocument::subtreePath); }

haxorg_OptOfInt haxorg_CmdIncludeOrgDocument_get_minLevel(OrgContext* org_context, haxorg_CmdIncludeOrgDocument __this) { return org::bind::c::get_cpp_field<haxorg_OptOfInt, org::sem::CmdInclude::OrgDocument, hstd::Opt<int>, haxorg_CmdIncludeOrgDocument>(org_context, __this, &org::sem::CmdInclude::OrgDocument::minLevel); }

haxorg_OptOfStr haxorg_CmdIncludeOrgDocument_get_customIdTarget(OrgContext* org_context, haxorg_CmdIncludeOrgDocument __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::CmdInclude::OrgDocument, hstd::Opt<hstd::Str>, haxorg_CmdIncludeOrgDocument>(org_context, __this, &org::sem::CmdInclude::OrgDocument::customIdTarget); }

void haxorg_destroy_CmdIncludeOrgDocument(OrgContext* org_context, haxorg_CmdIncludeOrgDocument* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude::OrgDocument>(org_context, obj); }

void haxorg_destroy_CmdInclude(OrgContext* org_context, haxorg_CmdInclude* obj) { org::bind::c::execute_destroy<org::sem::CmdInclude>(org_context, obj); }

bool haxorg_ImmNoNode___eq___const(OrgContext* org_context, haxorg_ImmNoNode __this, haxorg_ImmNoNode other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmNoNode::*)(org::imm::ImmNoNode const&) const>(&org::imm::ImmNoNode::operator==), org_context, __this, other); }

void haxorg_destroy_ImmNoNode(OrgContext* org_context, haxorg_ImmNoNode* obj) { org::bind::c::execute_destroy<org::imm::ImmNoNode>(org_context, obj); }

haxorg_OrgDiagnostics haxorg_ImmErrorItem_get_diag(OrgContext* org_context, haxorg_ImmErrorItem __this) { return org::bind::c::get_cpp_field<haxorg_OrgDiagnostics, org::imm::ImmErrorItem, org::sem::OrgDiagnostics, haxorg_ImmErrorItem>(org_context, __this, &org::imm::ImmErrorItem::diag); }

bool haxorg_ImmErrorItem___eq___const(OrgContext* org_context, haxorg_ImmErrorItem __this, haxorg_ImmErrorItem other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmErrorItem::*)(org::imm::ImmErrorItem const&) const>(&org::imm::ImmErrorItem::operator==), org_context, __this, other); }

void haxorg_destroy_ImmErrorItem(OrgContext* org_context, haxorg_ImmErrorItem* obj) { org::bind::c::execute_destroy<org::imm::ImmErrorItem>(org_context, obj); }

haxorg_ImmVec haxorg_ImmErrorGroup_get_diagnostics(OrgContext* org_context, haxorg_ImmErrorGroup __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmErrorGroup, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem>>, haxorg_ImmErrorGroup>(org_context, __this, &org::imm::ImmErrorGroup::diagnostics); }

bool haxorg_ImmErrorGroup___eq___const(OrgContext* org_context, haxorg_ImmErrorGroup __this, haxorg_ImmErrorGroup other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmErrorGroup::*)(org::imm::ImmErrorGroup const&) const>(&org::imm::ImmErrorGroup::operator==), org_context, __this, other); }

void haxorg_destroy_ImmErrorGroup(OrgContext* org_context, haxorg_ImmErrorGroup* obj) { org::bind::c::execute_destroy<org::imm::ImmErrorGroup>(org_context, obj); }

haxorg_ImmVec haxorg_ImmStmt_get_attached(OrgContext* org_context, haxorg_ImmStmt __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmStmt, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>>, haxorg_ImmStmt>(org_context, __this, &org::imm::ImmStmt::attached); }

bool haxorg_ImmStmt___eq___const(OrgContext* org_context, haxorg_ImmStmt __this, haxorg_ImmStmt other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmStmt::*)(org::imm::ImmStmt const&) const>(&org::imm::ImmStmt::operator==), org_context, __this, other); }

void haxorg_destroy_ImmStmt(OrgContext* org_context, haxorg_ImmStmt* obj) { org::bind::c::execute_destroy<org::imm::ImmStmt>(org_context, obj); }

bool haxorg_ImmInline___eq___const(OrgContext* org_context, haxorg_ImmInline __this, haxorg_ImmInline other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmInline::*)(org::imm::ImmInline const&) const>(&org::imm::ImmInline::operator==), org_context, __this, other); }

void haxorg_destroy_ImmInline(OrgContext* org_context, haxorg_ImmInline* obj) { org::bind::c::execute_destroy<org::imm::ImmInline>(org_context, obj); }

bool haxorg_ImmStmtList___eq___const(OrgContext* org_context, haxorg_ImmStmtList __this, haxorg_ImmStmtList other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmStmtList::*)(org::imm::ImmStmtList const&) const>(&org::imm::ImmStmtList::operator==), org_context, __this, other); }

void haxorg_destroy_ImmStmtList(OrgContext* org_context, haxorg_ImmStmtList* obj) { org::bind::c::execute_destroy<org::imm::ImmStmtList>(org_context, obj); }

bool haxorg_ImmEmpty___eq___const(OrgContext* org_context, haxorg_ImmEmpty __this, haxorg_ImmEmpty other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmEmpty::*)(org::imm::ImmEmpty const&) const>(&org::imm::ImmEmpty::operator==), org_context, __this, other); }

void haxorg_destroy_ImmEmpty(OrgContext* org_context, haxorg_ImmEmpty* obj) { org::bind::c::execute_destroy<org::imm::ImmEmpty>(org_context, obj); }

haxorg_HstdStr haxorg_ImmLeaf_get_text(OrgContext* org_context, haxorg_ImmLeaf __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmLeaf, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmLeaf>(org_context, __this, &org::imm::ImmLeaf::text); }

bool haxorg_ImmLeaf___eq___const(OrgContext* org_context, haxorg_ImmLeaf __this, haxorg_ImmLeaf other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmLeaf::*)(org::imm::ImmLeaf const&) const>(&org::imm::ImmLeaf::operator==), org_context, __this, other); }

void haxorg_destroy_ImmLeaf(OrgContext* org_context, haxorg_ImmLeaf* obj) { org::bind::c::execute_destroy<org::imm::ImmLeaf>(org_context, obj); }

bool haxorg_ImmTime_get_isActive(OrgContext* org_context, haxorg_ImmTime __this) { return org::bind::c::get_cpp_field<bool, org::imm::ImmTime, bool, haxorg_ImmTime>(org_context, __this, &org::imm::ImmTime::isActive); }

bool haxorg_ImmTime___eq___const(OrgContext* org_context, haxorg_ImmTime __this, haxorg_ImmTime other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmTime::*)(org::imm::ImmTime const&) const>(&org::imm::ImmTime::operator==), org_context, __this, other); }

bool haxorg_ImmTime_isStatic_const(OrgContext* org_context, haxorg_ImmTime __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::isStatic), org_context, __this); }

haxorg_ImmTimeStatic haxorg_ImmTime_getStaticConst_const(OrgContext* org_context, haxorg_ImmTime __this) { return org::bind::c::execute_cpp<haxorg_ImmTimeStatic>(static_cast<org::imm::ImmTime::Static const&(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::getStatic), org_context, __this); }

haxorg_ImmTimeStatic haxorg_ImmTime_getStaticMut(OrgContext* org_context, haxorg_ImmTime __this) { return org::bind::c::execute_cpp<haxorg_ImmTimeStatic>(static_cast<org::imm::ImmTime::Static&(org::imm::ImmTime::*)()>(&org::imm::ImmTime::getStatic), org_context, __this); }

bool haxorg_ImmTime_isDynamic_const(OrgContext* org_context, haxorg_ImmTime __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::isDynamic), org_context, __this); }

haxorg_ImmTimeDynamic haxorg_ImmTime_getDynamicConst_const(OrgContext* org_context, haxorg_ImmTime __this) { return org::bind::c::execute_cpp<haxorg_ImmTimeDynamic>(static_cast<org::imm::ImmTime::Dynamic const&(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::getDynamic), org_context, __this); }

haxorg_ImmTimeDynamic haxorg_ImmTime_getDynamicMut(OrgContext* org_context, haxorg_ImmTime __this) { return org::bind::c::execute_cpp<haxorg_ImmTimeDynamic>(static_cast<org::imm::ImmTime::Dynamic&(org::imm::ImmTime::*)()>(&org::imm::ImmTime::getDynamic), org_context, __this); }

haxorg_ImmTimeTimeKind haxorg_ImmTime_getTimeKind_const(OrgContext* org_context, haxorg_ImmTime __this) { return org::bind::c::execute_cpp<haxorg_ImmTimeTimeKind>(static_cast<org::imm::ImmTime::TimeKind(org::imm::ImmTime::*)() const>(&org::imm::ImmTime::getTimeKind), org_context, __this); }

haxorg_ImmTimeRepeatMode haxorg_ImmTimeRepeat_get_mode(OrgContext* org_context, haxorg_ImmTimeRepeat __this) { return org::bind::c::get_cpp_field<haxorg_ImmTimeRepeatMode, org::imm::ImmTime::Repeat, org::imm::ImmTime::Repeat::Mode, haxorg_ImmTimeRepeat>(org_context, __this, &org::imm::ImmTime::Repeat::mode); }

haxorg_ImmTimeRepeatPeriod haxorg_ImmTimeRepeat_get_period(OrgContext* org_context, haxorg_ImmTimeRepeat __this) { return org::bind::c::get_cpp_field<haxorg_ImmTimeRepeatPeriod, org::imm::ImmTime::Repeat, org::imm::ImmTime::Repeat::Period, haxorg_ImmTimeRepeat>(org_context, __this, &org::imm::ImmTime::Repeat::period); }

int haxorg_ImmTimeRepeat_get_count(OrgContext* org_context, haxorg_ImmTimeRepeat __this) { return org::bind::c::get_cpp_field<int, org::imm::ImmTime::Repeat, int, haxorg_ImmTimeRepeat>(org_context, __this, &org::imm::ImmTime::Repeat::count); }

bool haxorg_ImmTimeRepeat___eq___const(OrgContext* org_context, haxorg_ImmTimeRepeat __this, haxorg_ImmTimeRepeat other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmTime::Repeat::*)(org::imm::ImmTime::Repeat const&) const>(&org::imm::ImmTime::Repeat::operator==), org_context, __this, other); }

void haxorg_destroy_ImmTimeRepeat(OrgContext* org_context, haxorg_ImmTimeRepeat* obj) { org::bind::c::execute_destroy<org::imm::ImmTime::Repeat>(org_context, obj); }

haxorg_ImmVec haxorg_ImmTimeStatic_get_repeat(OrgContext* org_context, haxorg_ImmTimeStatic __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmTime::Static, hstd::ext::ImmVec<org::imm::ImmTime::Repeat>, haxorg_ImmTimeStatic>(org_context, __this, &org::imm::ImmTime::Static::repeat); }

haxorg_OptOfImmTimeRepeat haxorg_ImmTimeStatic_get_warn(OrgContext* org_context, haxorg_ImmTimeStatic __this) { return org::bind::c::get_cpp_field<haxorg_OptOfImmTimeRepeat, org::imm::ImmTime::Static, hstd::ext::ImmBox<hstd::Opt<org::imm::ImmTime::Repeat>>, haxorg_ImmTimeStatic>(org_context, __this, &org::imm::ImmTime::Static::warn); }

haxorg_UserTime haxorg_ImmTimeStatic_get_time(OrgContext* org_context, haxorg_ImmTimeStatic __this) { return org::bind::c::get_cpp_field<haxorg_UserTime, org::imm::ImmTime::Static, hstd::UserTime, haxorg_ImmTimeStatic>(org_context, __this, &org::imm::ImmTime::Static::time); }

void haxorg_create_ImmTimeStatic_Static(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::imm::ImmTime::Static { return org::imm::ImmTime::Static(); }, org_context); }

bool haxorg_ImmTimeStatic___eq___const(OrgContext* org_context, haxorg_ImmTimeStatic __this, haxorg_ImmTimeStatic other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmTime::Static::*)(org::imm::ImmTime::Static const&) const>(&org::imm::ImmTime::Static::operator==), org_context, __this, other); }

void haxorg_destroy_ImmTimeStatic(OrgContext* org_context, haxorg_ImmTimeStatic* obj) { org::bind::c::execute_destroy<org::imm::ImmTime::Static>(org_context, obj); }

haxorg_LispCode haxorg_ImmTimeDynamic_get_expr(OrgContext* org_context, haxorg_ImmTimeDynamic __this) { return org::bind::c::get_cpp_field<haxorg_LispCode, org::imm::ImmTime::Dynamic, org::sem::LispCode, haxorg_ImmTimeDynamic>(org_context, __this, &org::imm::ImmTime::Dynamic::expr); }

void haxorg_create_ImmTimeDynamic_Dynamic(OrgContext* org_context) { return org::bind::c::execute_cpp<void>(+[]() -> org::imm::ImmTime::Dynamic { return org::imm::ImmTime::Dynamic(); }, org_context); }

bool haxorg_ImmTimeDynamic___eq___const(OrgContext* org_context, haxorg_ImmTimeDynamic __this, haxorg_ImmTimeDynamic other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmTime::Dynamic::*)(org::imm::ImmTime::Dynamic const&) const>(&org::imm::ImmTime::Dynamic::operator==), org_context, __this, other); }

void haxorg_destroy_ImmTimeDynamic(OrgContext* org_context, haxorg_ImmTimeDynamic* obj) { org::bind::c::execute_destroy<org::imm::ImmTime::Dynamic>(org_context, obj); }

void haxorg_destroy_ImmTime(OrgContext* org_context, haxorg_ImmTime* obj) { org::bind::c::execute_destroy<org::imm::ImmTime>(org_context, obj); }

haxorg_ImmId haxorg_ImmTimeRange_get_from(OrgContext* org_context, haxorg_ImmTimeRange __this) { return org::bind::c::get_cpp_field<haxorg_ImmId, org::imm::ImmTimeRange, org::imm::ImmIdT<org::imm::ImmTime>, haxorg_ImmTimeRange>(org_context, __this, &org::imm::ImmTimeRange::from); }

haxorg_ImmId haxorg_ImmTimeRange_get_to(OrgContext* org_context, haxorg_ImmTimeRange __this) { return org::bind::c::get_cpp_field<haxorg_ImmId, org::imm::ImmTimeRange, org::imm::ImmIdT<org::imm::ImmTime>, haxorg_ImmTimeRange>(org_context, __this, &org::imm::ImmTimeRange::to); }

bool haxorg_ImmTimeRange___eq___const(OrgContext* org_context, haxorg_ImmTimeRange __this, haxorg_ImmTimeRange other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmTimeRange::*)(org::imm::ImmTimeRange const&) const>(&org::imm::ImmTimeRange::operator==), org_context, __this, other); }

void haxorg_destroy_ImmTimeRange(OrgContext* org_context, haxorg_ImmTimeRange* obj) { org::bind::c::execute_destroy<org::imm::ImmTimeRange>(org_context, obj); }

haxorg_HstdStr haxorg_ImmMacro_get_name(OrgContext* org_context, haxorg_ImmMacro __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmMacro, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmMacro>(org_context, __this, &org::imm::ImmMacro::name); }

haxorg_AttrGroup haxorg_ImmMacro_get_attrs(OrgContext* org_context, haxorg_ImmMacro __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::imm::ImmMacro, org::sem::AttrGroup, haxorg_ImmMacro>(org_context, __this, &org::imm::ImmMacro::attrs); }

bool haxorg_ImmMacro___eq___const(OrgContext* org_context, haxorg_ImmMacro __this, haxorg_ImmMacro other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmMacro::*)(org::imm::ImmMacro const&) const>(&org::imm::ImmMacro::operator==), org_context, __this, other); }

void haxorg_destroy_ImmMacro(OrgContext* org_context, haxorg_ImmMacro* obj) { org::bind::c::execute_destroy<org::imm::ImmMacro>(org_context, obj); }

haxorg_HstdStr haxorg_ImmSymbol_get_name(OrgContext* org_context, haxorg_ImmSymbol __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmSymbol, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmSymbol>(org_context, __this, &org::imm::ImmSymbol::name); }

haxorg_ImmVec haxorg_ImmSymbol_get_parameters(OrgContext* org_context, haxorg_ImmSymbol __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmSymbol, hstd::ext::ImmVec<org::imm::ImmSymbol::Param>, haxorg_ImmSymbol>(org_context, __this, &org::imm::ImmSymbol::parameters); }

haxorg_ImmVec haxorg_ImmSymbol_get_positional(OrgContext* org_context, haxorg_ImmSymbol __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmSymbol, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>>, haxorg_ImmSymbol>(org_context, __this, &org::imm::ImmSymbol::positional); }

bool haxorg_ImmSymbol___eq___const(OrgContext* org_context, haxorg_ImmSymbol __this, haxorg_ImmSymbol other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmSymbol::*)(org::imm::ImmSymbol const&) const>(&org::imm::ImmSymbol::operator==), org_context, __this, other); }

haxorg_OptOfStr haxorg_ImmSymbolParam_get_key(OrgContext* org_context, haxorg_ImmSymbolParam __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::imm::ImmSymbol::Param, hstd::ext::ImmBox<hstd::Opt<hstd::Str>>, haxorg_ImmSymbolParam>(org_context, __this, &org::imm::ImmSymbol::Param::key); }

haxorg_HstdStr haxorg_ImmSymbolParam_get_value(OrgContext* org_context, haxorg_ImmSymbolParam __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmSymbol::Param, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmSymbolParam>(org_context, __this, &org::imm::ImmSymbol::Param::value); }

bool haxorg_ImmSymbolParam___eq___const(OrgContext* org_context, haxorg_ImmSymbolParam __this, haxorg_ImmSymbolParam other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmSymbol::Param::*)(org::imm::ImmSymbol::Param const&) const>(&org::imm::ImmSymbol::Param::operator==), org_context, __this, other); }

void haxorg_destroy_ImmSymbolParam(OrgContext* org_context, haxorg_ImmSymbolParam* obj) { org::bind::c::execute_destroy<org::imm::ImmSymbol::Param>(org_context, obj); }

void haxorg_destroy_ImmSymbol(OrgContext* org_context, haxorg_ImmSymbol* obj) { org::bind::c::execute_destroy<org::imm::ImmSymbol>(org_context, obj); }

haxorg_ImmVec haxorg_ImmErrorSkipGroup_get_skipped(OrgContext* org_context, haxorg_ImmErrorSkipGroup __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmErrorSkipGroup, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorSkipToken>>, haxorg_ImmErrorSkipGroup>(org_context, __this, &org::imm::ImmErrorSkipGroup::skipped); }

bool haxorg_ImmErrorSkipGroup___eq___const(OrgContext* org_context, haxorg_ImmErrorSkipGroup __this, haxorg_ImmErrorSkipGroup other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmErrorSkipGroup::*)(org::imm::ImmErrorSkipGroup const&) const>(&org::imm::ImmErrorSkipGroup::operator==), org_context, __this, other); }

void haxorg_destroy_ImmErrorSkipGroup(OrgContext* org_context, haxorg_ImmErrorSkipGroup* obj) { org::bind::c::execute_destroy<org::imm::ImmErrorSkipGroup>(org_context, obj); }

bool haxorg_ImmMarkup___eq___const(OrgContext* org_context, haxorg_ImmMarkup __this, haxorg_ImmMarkup other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmMarkup::*)(org::imm::ImmMarkup const&) const>(&org::imm::ImmMarkup::operator==), org_context, __this, other); }

void haxorg_destroy_ImmMarkup(OrgContext* org_context, haxorg_ImmMarkup* obj) { org::bind::c::execute_destroy<org::imm::ImmMarkup>(org_context, obj); }

haxorg_ImmVec haxorg_ImmRadioTarget_get_words(OrgContext* org_context, haxorg_ImmRadioTarget __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmRadioTarget, hstd::ext::ImmVec<hstd::Str>, haxorg_ImmRadioTarget>(org_context, __this, &org::imm::ImmRadioTarget::words); }

bool haxorg_ImmRadioTarget___eq___const(OrgContext* org_context, haxorg_ImmRadioTarget __this, haxorg_ImmRadioTarget other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmRadioTarget::*)(org::imm::ImmRadioTarget const&) const>(&org::imm::ImmRadioTarget::operator==), org_context, __this, other); }

void haxorg_destroy_ImmRadioTarget(OrgContext* org_context, haxorg_ImmRadioTarget* obj) { org::bind::c::execute_destroy<org::imm::ImmRadioTarget>(org_context, obj); }

bool haxorg_ImmLatex___eq___const(OrgContext* org_context, haxorg_ImmLatex __this, haxorg_ImmLatex other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmLatex::*)(org::imm::ImmLatex const&) const>(&org::imm::ImmLatex::operator==), org_context, __this, other); }

void haxorg_destroy_ImmLatex(OrgContext* org_context, haxorg_ImmLatex* obj) { org::bind::c::execute_destroy<org::imm::ImmLatex>(org_context, obj); }

haxorg_SubtreeLogHead haxorg_ImmSubtreeLog_get_head(OrgContext* org_context, haxorg_ImmSubtreeLog __this) { return org::bind::c::get_cpp_field<haxorg_SubtreeLogHead, org::imm::ImmSubtreeLog, org::sem::SubtreeLogHead, haxorg_ImmSubtreeLog>(org_context, __this, &org::imm::ImmSubtreeLog::head); }

haxorg_OptOfImmIdTOfImmStmtList haxorg_ImmSubtreeLog_get_desc(OrgContext* org_context, haxorg_ImmSubtreeLog __this) { return org::bind::c::get_cpp_field<haxorg_OptOfImmIdTOfImmStmtList, org::imm::ImmSubtreeLog, hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmStmtList>>>, haxorg_ImmSubtreeLog>(org_context, __this, &org::imm::ImmSubtreeLog::desc); }

bool haxorg_ImmSubtreeLog___eq___const(OrgContext* org_context, haxorg_ImmSubtreeLog __this, haxorg_ImmSubtreeLog other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmSubtreeLog::*)(org::imm::ImmSubtreeLog const&) const>(&org::imm::ImmSubtreeLog::operator==), org_context, __this, other); }

void haxorg_destroy_ImmSubtreeLog(OrgContext* org_context, haxorg_ImmSubtreeLog* obj) { org::bind::c::execute_destroy<org::imm::ImmSubtreeLog>(org_context, obj); }

int haxorg_ImmSubtree_get_level(OrgContext* org_context, haxorg_ImmSubtree __this) { return org::bind::c::get_cpp_field<int, org::imm::ImmSubtree, int, haxorg_ImmSubtree>(org_context, __this, &org::imm::ImmSubtree::level); }

haxorg_OptOfStr haxorg_ImmSubtree_get_treeId(OrgContext* org_context, haxorg_ImmSubtree __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::imm::ImmSubtree, hstd::ext::ImmBox<hstd::Opt<hstd::Str>>, haxorg_ImmSubtree>(org_context, __this, &org::imm::ImmSubtree::treeId); }

haxorg_OptOfStr haxorg_ImmSubtree_get_todo(OrgContext* org_context, haxorg_ImmSubtree __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::imm::ImmSubtree, hstd::ext::ImmBox<hstd::Opt<hstd::Str>>, haxorg_ImmSubtree>(org_context, __this, &org::imm::ImmSubtree::todo); }

haxorg_OptOfSubtreeCompletion haxorg_ImmSubtree_get_completion(OrgContext* org_context, haxorg_ImmSubtree __this) { return org::bind::c::get_cpp_field<haxorg_OptOfSubtreeCompletion, org::imm::ImmSubtree, hstd::ext::ImmBox<hstd::Opt<org::sem::SubtreeCompletion>>, haxorg_ImmSubtree>(org_context, __this, &org::imm::ImmSubtree::completion); }

haxorg_OptOfImmIdTOfImmParagraph haxorg_ImmSubtree_get_description(OrgContext* org_context, haxorg_ImmSubtree __this) { return org::bind::c::get_cpp_field<haxorg_OptOfImmIdTOfImmParagraph, org::imm::ImmSubtree, hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>, haxorg_ImmSubtree>(org_context, __this, &org::imm::ImmSubtree::description); }

haxorg_ImmVec haxorg_ImmSubtree_get_tags(OrgContext* org_context, haxorg_ImmSubtree __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmSubtree, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>>, haxorg_ImmSubtree>(org_context, __this, &org::imm::ImmSubtree::tags); }

haxorg_ImmId haxorg_ImmSubtree_get_title(OrgContext* org_context, haxorg_ImmSubtree __this) { return org::bind::c::get_cpp_field<haxorg_ImmId, org::imm::ImmSubtree, org::imm::ImmIdT<org::imm::ImmParagraph>, haxorg_ImmSubtree>(org_context, __this, &org::imm::ImmSubtree::title); }

haxorg_ImmVec haxorg_ImmSubtree_get_logbook(OrgContext* org_context, haxorg_ImmSubtree __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmSubtree, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog>>, haxorg_ImmSubtree>(org_context, __this, &org::imm::ImmSubtree::logbook); }

haxorg_ImmVec haxorg_ImmSubtree_get_properties(OrgContext* org_context, haxorg_ImmSubtree __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmSubtree, hstd::ext::ImmVec<org::sem::NamedProperty>, haxorg_ImmSubtree>(org_context, __this, &org::imm::ImmSubtree::properties); }

haxorg_OptOfImmIdTOfImmTime haxorg_ImmSubtree_get_closed(OrgContext* org_context, haxorg_ImmSubtree __this) { return org::bind::c::get_cpp_field<haxorg_OptOfImmIdTOfImmTime, org::imm::ImmSubtree, hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime>>>, haxorg_ImmSubtree>(org_context, __this, &org::imm::ImmSubtree::closed); }

haxorg_OptOfImmIdTOfImmTime haxorg_ImmSubtree_get_deadline(OrgContext* org_context, haxorg_ImmSubtree __this) { return org::bind::c::get_cpp_field<haxorg_OptOfImmIdTOfImmTime, org::imm::ImmSubtree, hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime>>>, haxorg_ImmSubtree>(org_context, __this, &org::imm::ImmSubtree::deadline); }

haxorg_OptOfImmIdTOfImmTime haxorg_ImmSubtree_get_scheduled(OrgContext* org_context, haxorg_ImmSubtree __this) { return org::bind::c::get_cpp_field<haxorg_OptOfImmIdTOfImmTime, org::imm::ImmSubtree, hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime>>>, haxorg_ImmSubtree>(org_context, __this, &org::imm::ImmSubtree::scheduled); }

bool haxorg_ImmSubtree_get_isComment(OrgContext* org_context, haxorg_ImmSubtree __this) { return org::bind::c::get_cpp_field<bool, org::imm::ImmSubtree, bool, haxorg_ImmSubtree>(org_context, __this, &org::imm::ImmSubtree::isComment); }

bool haxorg_ImmSubtree_get_isArchived(OrgContext* org_context, haxorg_ImmSubtree __this) { return org::bind::c::get_cpp_field<bool, org::imm::ImmSubtree, bool, haxorg_ImmSubtree>(org_context, __this, &org::imm::ImmSubtree::isArchived); }

haxorg_OptOfStr haxorg_ImmSubtree_get_priority(OrgContext* org_context, haxorg_ImmSubtree __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::imm::ImmSubtree, hstd::ext::ImmBox<hstd::Opt<hstd::Str>>, haxorg_ImmSubtree>(org_context, __this, &org::imm::ImmSubtree::priority); }

bool haxorg_ImmSubtree___eq___const(OrgContext* org_context, haxorg_ImmSubtree __this, haxorg_ImmSubtree other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmSubtree::*)(org::imm::ImmSubtree const&) const>(&org::imm::ImmSubtree::operator==), org_context, __this, other); }

void haxorg_destroy_ImmSubtree(OrgContext* org_context, haxorg_ImmSubtree* obj) { org::bind::c::execute_destroy<org::imm::ImmSubtree>(org_context, obj); }

bool haxorg_ImmColonExample___eq___const(OrgContext* org_context, haxorg_ImmColonExample __this, haxorg_ImmColonExample other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmColonExample::*)(org::imm::ImmColonExample const&) const>(&org::imm::ImmColonExample::operator==), org_context, __this, other); }

void haxorg_destroy_ImmColonExample(OrgContext* org_context, haxorg_ImmColonExample* obj) { org::bind::c::execute_destroy<org::imm::ImmColonExample>(org_context, obj); }

haxorg_HstdStr haxorg_ImmCall_get_name(OrgContext* org_context, haxorg_ImmCall __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmCall, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmCall>(org_context, __this, &org::imm::ImmCall::name); }

haxorg_AttrGroup haxorg_ImmCall_get_attrs(OrgContext* org_context, haxorg_ImmCall __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::imm::ImmCall, org::sem::AttrGroup, haxorg_ImmCall>(org_context, __this, &org::imm::ImmCall::attrs); }

bool haxorg_ImmCall_get_isCommand(OrgContext* org_context, haxorg_ImmCall __this) { return org::bind::c::get_cpp_field<bool, org::imm::ImmCall, bool, haxorg_ImmCall>(org_context, __this, &org::imm::ImmCall::isCommand); }

bool haxorg_ImmCall___eq___const(OrgContext* org_context, haxorg_ImmCall __this, haxorg_ImmCall other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCall::*)(org::imm::ImmCall const&) const>(&org::imm::ImmCall::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCall(OrgContext* org_context, haxorg_ImmCall* obj) { org::bind::c::execute_destroy<org::imm::ImmCall>(org_context, obj); }

haxorg_CheckboxState haxorg_ImmListItem_get_checkbox(OrgContext* org_context, haxorg_ImmListItem __this) { return org::bind::c::get_cpp_field<haxorg_CheckboxState, org::imm::ImmListItem, CheckboxState, haxorg_ImmListItem>(org_context, __this, &org::imm::ImmListItem::checkbox); }

haxorg_OptOfImmIdTOfImmParagraph haxorg_ImmListItem_get_header(OrgContext* org_context, haxorg_ImmListItem __this) { return org::bind::c::get_cpp_field<haxorg_OptOfImmIdTOfImmParagraph, org::imm::ImmListItem, hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>, haxorg_ImmListItem>(org_context, __this, &org::imm::ImmListItem::header); }

haxorg_OptOfStr haxorg_ImmListItem_get_bullet(OrgContext* org_context, haxorg_ImmListItem __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::imm::ImmListItem, hstd::ext::ImmBox<hstd::Opt<hstd::Str>>, haxorg_ImmListItem>(org_context, __this, &org::imm::ImmListItem::bullet); }

bool haxorg_ImmListItem___eq___const(OrgContext* org_context, haxorg_ImmListItem __this, haxorg_ImmListItem other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmListItem::*)(org::imm::ImmListItem const&) const>(&org::imm::ImmListItem::operator==), org_context, __this, other); }

void haxorg_destroy_ImmListItem(OrgContext* org_context, haxorg_ImmListItem* obj) { org::bind::c::execute_destroy<org::imm::ImmListItem>(org_context, obj); }

haxorg_InitialSubtreeVisibility haxorg_ImmDocumentOptions_get_initialVisibility(OrgContext* org_context, haxorg_ImmDocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_InitialSubtreeVisibility, org::imm::ImmDocumentOptions, InitialSubtreeVisibility, haxorg_ImmDocumentOptions>(org_context, __this, &org::imm::ImmDocumentOptions::initialVisibility); }

haxorg_ImmVec haxorg_ImmDocumentOptions_get_properties(OrgContext* org_context, haxorg_ImmDocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmDocumentOptions, hstd::ext::ImmVec<org::sem::NamedProperty>, haxorg_ImmDocumentOptions>(org_context, __this, &org::imm::ImmDocumentOptions::properties); }

haxorg_DocumentExportConfig haxorg_ImmDocumentOptions_get_exportConfig(OrgContext* org_context, haxorg_ImmDocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_DocumentExportConfig, org::imm::ImmDocumentOptions, org::sem::DocumentExportConfig, haxorg_ImmDocumentOptions>(org_context, __this, &org::imm::ImmDocumentOptions::exportConfig); }

haxorg_OptOfBool haxorg_ImmDocumentOptions_get_fixedWidthSections(OrgContext* org_context, haxorg_ImmDocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::imm::ImmDocumentOptions, hstd::ext::ImmBox<hstd::Opt<bool>>, haxorg_ImmDocumentOptions>(org_context, __this, &org::imm::ImmDocumentOptions::fixedWidthSections); }

haxorg_OptOfBool haxorg_ImmDocumentOptions_get_startupIndented(OrgContext* org_context, haxorg_ImmDocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::imm::ImmDocumentOptions, hstd::ext::ImmBox<hstd::Opt<bool>>, haxorg_ImmDocumentOptions>(org_context, __this, &org::imm::ImmDocumentOptions::startupIndented); }

haxorg_OptOfStr haxorg_ImmDocumentOptions_get_category(OrgContext* org_context, haxorg_ImmDocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::imm::ImmDocumentOptions, hstd::ext::ImmBox<hstd::Opt<hstd::Str>>, haxorg_ImmDocumentOptions>(org_context, __this, &org::imm::ImmDocumentOptions::category); }

haxorg_OptOfStr haxorg_ImmDocumentOptions_get_setupfile(OrgContext* org_context, haxorg_ImmDocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::imm::ImmDocumentOptions, hstd::ext::ImmBox<hstd::Opt<hstd::Str>>, haxorg_ImmDocumentOptions>(org_context, __this, &org::imm::ImmDocumentOptions::setupfile); }

haxorg_OptOfInt haxorg_ImmDocumentOptions_get_maxSubtreeLevelExport(OrgContext* org_context, haxorg_ImmDocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_OptOfInt, org::imm::ImmDocumentOptions, hstd::ext::ImmBox<hstd::Opt<int>>, haxorg_ImmDocumentOptions>(org_context, __this, &org::imm::ImmDocumentOptions::maxSubtreeLevelExport); }

haxorg_OptOfColumnView haxorg_ImmDocumentOptions_get_columns(OrgContext* org_context, haxorg_ImmDocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_OptOfColumnView, org::imm::ImmDocumentOptions, hstd::ext::ImmBox<hstd::Opt<org::sem::ColumnView>>, haxorg_ImmDocumentOptions>(org_context, __this, &org::imm::ImmDocumentOptions::columns); }

haxorg_ImmVec haxorg_ImmDocumentOptions_get_todoKeywords(OrgContext* org_context, haxorg_ImmDocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmDocumentOptions, hstd::ext::ImmVec<org::sem::TodoKeyword>, haxorg_ImmDocumentOptions>(org_context, __this, &org::imm::ImmDocumentOptions::todoKeywords); }

haxorg_ImmVec haxorg_ImmDocumentOptions_get_doneKeywords(OrgContext* org_context, haxorg_ImmDocumentOptions __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmDocumentOptions, hstd::ext::ImmVec<org::sem::TodoKeyword>, haxorg_ImmDocumentOptions>(org_context, __this, &org::imm::ImmDocumentOptions::doneKeywords); }

bool haxorg_ImmDocumentOptions___eq___const(OrgContext* org_context, haxorg_ImmDocumentOptions __this, haxorg_ImmDocumentOptions other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmDocumentOptions::*)(org::imm::ImmDocumentOptions const&) const>(&org::imm::ImmDocumentOptions::operator==), org_context, __this, other); }

void haxorg_destroy_ImmDocumentOptions(OrgContext* org_context, haxorg_ImmDocumentOptions* obj) { org::bind::c::execute_destroy<org::imm::ImmDocumentOptions>(org_context, obj); }

int haxorg_ImmDocumentFragment_get_baseLine(OrgContext* org_context, haxorg_ImmDocumentFragment __this) { return org::bind::c::get_cpp_field<int, org::imm::ImmDocumentFragment, int, haxorg_ImmDocumentFragment>(org_context, __this, &org::imm::ImmDocumentFragment::baseLine); }

int haxorg_ImmDocumentFragment_get_baseCol(OrgContext* org_context, haxorg_ImmDocumentFragment __this) { return org::bind::c::get_cpp_field<int, org::imm::ImmDocumentFragment, int, haxorg_ImmDocumentFragment>(org_context, __this, &org::imm::ImmDocumentFragment::baseCol); }

bool haxorg_ImmDocumentFragment___eq___const(OrgContext* org_context, haxorg_ImmDocumentFragment __this, haxorg_ImmDocumentFragment other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmDocumentFragment::*)(org::imm::ImmDocumentFragment const&) const>(&org::imm::ImmDocumentFragment::operator==), org_context, __this, other); }

void haxorg_destroy_ImmDocumentFragment(OrgContext* org_context, haxorg_ImmDocumentFragment* obj) { org::bind::c::execute_destroy<org::imm::ImmDocumentFragment>(org_context, obj); }

haxorg_ImmCriticMarkupKind haxorg_ImmCriticMarkup_get_kind(OrgContext* org_context, haxorg_ImmCriticMarkup __this) { return org::bind::c::get_cpp_field<haxorg_ImmCriticMarkupKind, org::imm::ImmCriticMarkup, org::imm::ImmCriticMarkup::Kind, haxorg_ImmCriticMarkup>(org_context, __this, &org::imm::ImmCriticMarkup::kind); }

bool haxorg_ImmCriticMarkup___eq___const(OrgContext* org_context, haxorg_ImmCriticMarkup __this, haxorg_ImmCriticMarkup other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCriticMarkup::*)(org::imm::ImmCriticMarkup const&) const>(&org::imm::ImmCriticMarkup::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCriticMarkup(OrgContext* org_context, haxorg_ImmCriticMarkup* obj) { org::bind::c::execute_destroy<org::imm::ImmCriticMarkup>(org_context, obj); }

haxorg_OptOfImmIdTOfImmParagraph haxorg_ImmDocument_get_title(OrgContext* org_context, haxorg_ImmDocument __this) { return org::bind::c::get_cpp_field<haxorg_OptOfImmIdTOfImmParagraph, org::imm::ImmDocument, hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>, haxorg_ImmDocument>(org_context, __this, &org::imm::ImmDocument::title); }

haxorg_OptOfImmIdTOfImmParagraph haxorg_ImmDocument_get_author(OrgContext* org_context, haxorg_ImmDocument __this) { return org::bind::c::get_cpp_field<haxorg_OptOfImmIdTOfImmParagraph, org::imm::ImmDocument, hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>, haxorg_ImmDocument>(org_context, __this, &org::imm::ImmDocument::author); }

haxorg_OptOfImmIdTOfImmParagraph haxorg_ImmDocument_get_creator(OrgContext* org_context, haxorg_ImmDocument __this) { return org::bind::c::get_cpp_field<haxorg_OptOfImmIdTOfImmParagraph, org::imm::ImmDocument, hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>, haxorg_ImmDocument>(org_context, __this, &org::imm::ImmDocument::creator); }

haxorg_ImmVec haxorg_ImmDocument_get_filetags(OrgContext* org_context, haxorg_ImmDocument __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmDocument, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>>, haxorg_ImmDocument>(org_context, __this, &org::imm::ImmDocument::filetags); }

haxorg_OptOfImmIdTOfImmRawText haxorg_ImmDocument_get_email(OrgContext* org_context, haxorg_ImmDocument __this) { return org::bind::c::get_cpp_field<haxorg_OptOfImmIdTOfImmRawText, org::imm::ImmDocument, hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmRawText>>>, haxorg_ImmDocument>(org_context, __this, &org::imm::ImmDocument::email); }

haxorg_ImmVec haxorg_ImmDocument_get_language(OrgContext* org_context, haxorg_ImmDocument __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmDocument, hstd::ext::ImmVec<hstd::Str>, haxorg_ImmDocument>(org_context, __this, &org::imm::ImmDocument::language); }

haxorg_ImmId haxorg_ImmDocument_get_options(OrgContext* org_context, haxorg_ImmDocument __this) { return org::bind::c::get_cpp_field<haxorg_ImmId, org::imm::ImmDocument, org::imm::ImmIdT<org::imm::ImmDocumentOptions>, haxorg_ImmDocument>(org_context, __this, &org::imm::ImmDocument::options); }

haxorg_OptOfStr haxorg_ImmDocument_get_exportFileName(OrgContext* org_context, haxorg_ImmDocument __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::imm::ImmDocument, hstd::ext::ImmBox<hstd::Opt<hstd::Str>>, haxorg_ImmDocument>(org_context, __this, &org::imm::ImmDocument::exportFileName); }

bool haxorg_ImmDocument___eq___const(OrgContext* org_context, haxorg_ImmDocument __this, haxorg_ImmDocument other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmDocument::*)(org::imm::ImmDocument const&) const>(&org::imm::ImmDocument::operator==), org_context, __this, other); }

void haxorg_destroy_ImmDocument(OrgContext* org_context, haxorg_ImmDocument* obj) { org::bind::c::execute_destroy<org::imm::ImmDocument>(org_context, obj); }

haxorg_HstdStr haxorg_ImmFileTarget_get_path(OrgContext* org_context, haxorg_ImmFileTarget __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmFileTarget, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmFileTarget>(org_context, __this, &org::imm::ImmFileTarget::path); }

haxorg_OptOfInt haxorg_ImmFileTarget_get_line(OrgContext* org_context, haxorg_ImmFileTarget __this) { return org::bind::c::get_cpp_field<haxorg_OptOfInt, org::imm::ImmFileTarget, hstd::ext::ImmBox<hstd::Opt<int>>, haxorg_ImmFileTarget>(org_context, __this, &org::imm::ImmFileTarget::line); }

haxorg_OptOfStr haxorg_ImmFileTarget_get_searchTarget(OrgContext* org_context, haxorg_ImmFileTarget __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::imm::ImmFileTarget, hstd::ext::ImmBox<hstd::Opt<hstd::Str>>, haxorg_ImmFileTarget>(org_context, __this, &org::imm::ImmFileTarget::searchTarget); }

bool haxorg_ImmFileTarget_get_restrictToHeadlines(OrgContext* org_context, haxorg_ImmFileTarget __this) { return org::bind::c::get_cpp_field<bool, org::imm::ImmFileTarget, bool, haxorg_ImmFileTarget>(org_context, __this, &org::imm::ImmFileTarget::restrictToHeadlines); }

haxorg_OptOfStr haxorg_ImmFileTarget_get_targetId(OrgContext* org_context, haxorg_ImmFileTarget __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::imm::ImmFileTarget, hstd::ext::ImmBox<hstd::Opt<hstd::Str>>, haxorg_ImmFileTarget>(org_context, __this, &org::imm::ImmFileTarget::targetId); }

haxorg_OptOfStr haxorg_ImmFileTarget_get_regexp(OrgContext* org_context, haxorg_ImmFileTarget __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::imm::ImmFileTarget, hstd::ext::ImmBox<hstd::Opt<hstd::Str>>, haxorg_ImmFileTarget>(org_context, __this, &org::imm::ImmFileTarget::regexp); }

bool haxorg_ImmFileTarget___eq___const(OrgContext* org_context, haxorg_ImmFileTarget __this, haxorg_ImmFileTarget other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmFileTarget::*)(org::imm::ImmFileTarget const&) const>(&org::imm::ImmFileTarget::operator==), org_context, __this, other); }

void haxorg_destroy_ImmFileTarget(OrgContext* org_context, haxorg_ImmFileTarget* obj) { org::bind::c::execute_destroy<org::imm::ImmFileTarget>(org_context, obj); }

bool haxorg_ImmTextSeparator___eq___const(OrgContext* org_context, haxorg_ImmTextSeparator __this, haxorg_ImmTextSeparator other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmTextSeparator::*)(org::imm::ImmTextSeparator const&) const>(&org::imm::ImmTextSeparator::operator==), org_context, __this, other); }

void haxorg_destroy_ImmTextSeparator(OrgContext* org_context, haxorg_ImmTextSeparator* obj) { org::bind::c::execute_destroy<org::imm::ImmTextSeparator>(org_context, obj); }

bool haxorg_ImmDocumentGroup___eq___const(OrgContext* org_context, haxorg_ImmDocumentGroup __this, haxorg_ImmDocumentGroup other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmDocumentGroup::*)(org::imm::ImmDocumentGroup const&) const>(&org::imm::ImmDocumentGroup::operator==), org_context, __this, other); }

void haxorg_destroy_ImmDocumentGroup(OrgContext* org_context, haxorg_ImmDocumentGroup* obj) { org::bind::c::execute_destroy<org::imm::ImmDocumentGroup>(org_context, obj); }

haxorg_HstdStr haxorg_ImmFile_get_relPath(OrgContext* org_context, haxorg_ImmFile __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmFile, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmFile>(org_context, __this, &org::imm::ImmFile::relPath); }

haxorg_HstdStr haxorg_ImmFile_get_absPath(OrgContext* org_context, haxorg_ImmFile __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmFile, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmFile>(org_context, __this, &org::imm::ImmFile::absPath); }

bool haxorg_ImmFile___eq___const(OrgContext* org_context, haxorg_ImmFile __this, haxorg_ImmFile other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmFile::*)(org::imm::ImmFile const&) const>(&org::imm::ImmFile::operator==), org_context, __this, other); }

bool haxorg_ImmFile_isDocument_const(OrgContext* org_context, haxorg_ImmFile __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::isDocument), org_context, __this); }

haxorg_ImmFileDocument haxorg_ImmFile_getDocumentConst_const(OrgContext* org_context, haxorg_ImmFile __this) { return org::bind::c::execute_cpp<haxorg_ImmFileDocument>(static_cast<org::imm::ImmFile::Document const&(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getDocument), org_context, __this); }

haxorg_ImmFileDocument haxorg_ImmFile_getDocumentMut(OrgContext* org_context, haxorg_ImmFile __this) { return org::bind::c::execute_cpp<haxorg_ImmFileDocument>(static_cast<org::imm::ImmFile::Document&(org::imm::ImmFile::*)()>(&org::imm::ImmFile::getDocument), org_context, __this); }

bool haxorg_ImmFile_isAttachment_const(OrgContext* org_context, haxorg_ImmFile __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::isAttachment), org_context, __this); }

haxorg_ImmFileAttachment haxorg_ImmFile_getAttachmentConst_const(OrgContext* org_context, haxorg_ImmFile __this) { return org::bind::c::execute_cpp<haxorg_ImmFileAttachment>(static_cast<org::imm::ImmFile::Attachment const&(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getAttachment), org_context, __this); }

haxorg_ImmFileAttachment haxorg_ImmFile_getAttachmentMut(OrgContext* org_context, haxorg_ImmFile __this) { return org::bind::c::execute_cpp<haxorg_ImmFileAttachment>(static_cast<org::imm::ImmFile::Attachment&(org::imm::ImmFile::*)()>(&org::imm::ImmFile::getAttachment), org_context, __this); }

bool haxorg_ImmFile_isSource_const(OrgContext* org_context, haxorg_ImmFile __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::isSource), org_context, __this); }

haxorg_ImmFileSource haxorg_ImmFile_getSourceConst_const(OrgContext* org_context, haxorg_ImmFile __this) { return org::bind::c::execute_cpp<haxorg_ImmFileSource>(static_cast<org::imm::ImmFile::Source const&(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getSource), org_context, __this); }

haxorg_ImmFileSource haxorg_ImmFile_getSourceMut(OrgContext* org_context, haxorg_ImmFile __this) { return org::bind::c::execute_cpp<haxorg_ImmFileSource>(static_cast<org::imm::ImmFile::Source&(org::imm::ImmFile::*)()>(&org::imm::ImmFile::getSource), org_context, __this); }

haxorg_ImmFileKind haxorg_ImmFile_getFileKind_const(OrgContext* org_context, haxorg_ImmFile __this) { return org::bind::c::execute_cpp<haxorg_ImmFileKind>(static_cast<org::imm::ImmFile::Kind(org::imm::ImmFile::*)() const>(&org::imm::ImmFile::getFileKind), org_context, __this); }

bool haxorg_ImmFileDocument___eq___const(OrgContext* org_context, haxorg_ImmFileDocument __this, haxorg_ImmFileDocument other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmFile::Document::*)(org::imm::ImmFile::Document const&) const>(&org::imm::ImmFile::Document::operator==), org_context, __this, other); }

void haxorg_destroy_ImmFileDocument(OrgContext* org_context, haxorg_ImmFileDocument* obj) { org::bind::c::execute_destroy<org::imm::ImmFile::Document>(org_context, obj); }

bool haxorg_ImmFileAttachment___eq___const(OrgContext* org_context, haxorg_ImmFileAttachment __this, haxorg_ImmFileAttachment other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmFile::Attachment::*)(org::imm::ImmFile::Attachment const&) const>(&org::imm::ImmFile::Attachment::operator==), org_context, __this, other); }

void haxorg_destroy_ImmFileAttachment(OrgContext* org_context, haxorg_ImmFileAttachment* obj) { org::bind::c::execute_destroy<org::imm::ImmFile::Attachment>(org_context, obj); }

bool haxorg_ImmFileSource___eq___const(OrgContext* org_context, haxorg_ImmFileSource __this, haxorg_ImmFileSource other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmFile::Source::*)(org::imm::ImmFile::Source const&) const>(&org::imm::ImmFile::Source::operator==), org_context, __this, other); }

void haxorg_destroy_ImmFileSource(OrgContext* org_context, haxorg_ImmFileSource* obj) { org::bind::c::execute_destroy<org::imm::ImmFile::Source>(org_context, obj); }

void haxorg_destroy_ImmFile(OrgContext* org_context, haxorg_ImmFile* obj) { org::bind::c::execute_destroy<org::imm::ImmFile>(org_context, obj); }

haxorg_HstdStr haxorg_ImmDirectory_get_relPath(OrgContext* org_context, haxorg_ImmDirectory __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmDirectory, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmDirectory>(org_context, __this, &org::imm::ImmDirectory::relPath); }

haxorg_HstdStr haxorg_ImmDirectory_get_absPath(OrgContext* org_context, haxorg_ImmDirectory __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmDirectory, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmDirectory>(org_context, __this, &org::imm::ImmDirectory::absPath); }

bool haxorg_ImmDirectory___eq___const(OrgContext* org_context, haxorg_ImmDirectory __this, haxorg_ImmDirectory other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmDirectory::*)(org::imm::ImmDirectory const&) const>(&org::imm::ImmDirectory::operator==), org_context, __this, other); }

void haxorg_destroy_ImmDirectory(OrgContext* org_context, haxorg_ImmDirectory* obj) { org::bind::c::execute_destroy<org::imm::ImmDirectory>(org_context, obj); }

bool haxorg_ImmSymlink_get_isDirectory(OrgContext* org_context, haxorg_ImmSymlink __this) { return org::bind::c::get_cpp_field<bool, org::imm::ImmSymlink, bool, haxorg_ImmSymlink>(org_context, __this, &org::imm::ImmSymlink::isDirectory); }

haxorg_HstdStr haxorg_ImmSymlink_get_absPath(OrgContext* org_context, haxorg_ImmSymlink __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmSymlink, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmSymlink>(org_context, __this, &org::imm::ImmSymlink::absPath); }

bool haxorg_ImmSymlink___eq___const(OrgContext* org_context, haxorg_ImmSymlink __this, haxorg_ImmSymlink other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmSymlink::*)(org::imm::ImmSymlink const&) const>(&org::imm::ImmSymlink::operator==), org_context, __this, other); }

void haxorg_destroy_ImmSymlink(OrgContext* org_context, haxorg_ImmSymlink* obj) { org::bind::c::execute_destroy<org::imm::ImmSymlink>(org_context, obj); }

haxorg_HstdStr haxorg_ImmCmdInclude_get_path(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmCmdInclude, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmCmdInclude>(org_context, __this, &org::imm::ImmCmdInclude::path); }

haxorg_OptOfInt haxorg_ImmCmdInclude_get_firstLine(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::get_cpp_field<haxorg_OptOfInt, org::imm::ImmCmdInclude, hstd::ext::ImmBox<hstd::Opt<int>>, haxorg_ImmCmdInclude>(org_context, __this, &org::imm::ImmCmdInclude::firstLine); }

haxorg_OptOfInt haxorg_ImmCmdInclude_get_lastLine(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::get_cpp_field<haxorg_OptOfInt, org::imm::ImmCmdInclude, hstd::ext::ImmBox<hstd::Opt<int>>, haxorg_ImmCmdInclude>(org_context, __this, &org::imm::ImmCmdInclude::lastLine); }

bool haxorg_ImmCmdInclude___eq___const(OrgContext* org_context, haxorg_ImmCmdInclude __this, haxorg_ImmCmdInclude other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdInclude::*)(org::imm::ImmCmdInclude const&) const>(&org::imm::ImmCmdInclude::operator==), org_context, __this, other); }

bool haxorg_ImmCmdInclude_isExample_const(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isExample), org_context, __this); }

haxorg_ImmCmdIncludeExample haxorg_ImmCmdInclude_getExampleConst_const(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeExample>(static_cast<org::imm::ImmCmdInclude::Example const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getExample), org_context, __this); }

haxorg_ImmCmdIncludeExample haxorg_ImmCmdInclude_getExampleMut(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeExample>(static_cast<org::imm::ImmCmdInclude::Example&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getExample), org_context, __this); }

bool haxorg_ImmCmdInclude_isExport_const(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isExport), org_context, __this); }

haxorg_ImmCmdIncludeExport haxorg_ImmCmdInclude_getExportConst_const(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeExport>(static_cast<org::imm::ImmCmdInclude::Export const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getExport), org_context, __this); }

haxorg_ImmCmdIncludeExport haxorg_ImmCmdInclude_getExportMut(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeExport>(static_cast<org::imm::ImmCmdInclude::Export&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getExport), org_context, __this); }

bool haxorg_ImmCmdInclude_isCustom_const(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isCustom), org_context, __this); }

haxorg_ImmCmdIncludeCustom haxorg_ImmCmdInclude_getCustomConst_const(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeCustom>(static_cast<org::imm::ImmCmdInclude::Custom const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getCustom), org_context, __this); }

haxorg_ImmCmdIncludeCustom haxorg_ImmCmdInclude_getCustomMut(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeCustom>(static_cast<org::imm::ImmCmdInclude::Custom&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getCustom), org_context, __this); }

bool haxorg_ImmCmdInclude_isSrc_const(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isSrc), org_context, __this); }

haxorg_ImmCmdIncludeSrc haxorg_ImmCmdInclude_getSrcConst_const(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeSrc>(static_cast<org::imm::ImmCmdInclude::Src const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getSrc), org_context, __this); }

haxorg_ImmCmdIncludeSrc haxorg_ImmCmdInclude_getSrcMut(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeSrc>(static_cast<org::imm::ImmCmdInclude::Src&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getSrc), org_context, __this); }

bool haxorg_ImmCmdInclude_isOrgDocument_const(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::isOrgDocument), org_context, __this); }

haxorg_ImmCmdIncludeOrgDocument haxorg_ImmCmdInclude_getOrgDocumentConst_const(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeOrgDocument>(static_cast<org::imm::ImmCmdInclude::OrgDocument const&(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getOrgDocument), org_context, __this); }

haxorg_ImmCmdIncludeOrgDocument haxorg_ImmCmdInclude_getOrgDocumentMut(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeOrgDocument>(static_cast<org::imm::ImmCmdInclude::OrgDocument&(org::imm::ImmCmdInclude::*)()>(&org::imm::ImmCmdInclude::getOrgDocument), org_context, __this); }

haxorg_ImmCmdIncludeKind haxorg_ImmCmdInclude_getIncludeKind_const(OrgContext* org_context, haxorg_ImmCmdInclude __this) { return org::bind::c::execute_cpp<haxorg_ImmCmdIncludeKind>(static_cast<org::imm::ImmCmdInclude::Kind(org::imm::ImmCmdInclude::*)() const>(&org::imm::ImmCmdInclude::getIncludeKind), org_context, __this); }

bool haxorg_ImmCmdIncludeIncludeBase___eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeIncludeBase __this, haxorg_ImmCmdIncludeIncludeBase other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdInclude::IncludeBase::*)(org::imm::ImmCmdInclude::IncludeBase const&) const>(&org::imm::ImmCmdInclude::IncludeBase::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdIncludeIncludeBase(OrgContext* org_context, haxorg_ImmCmdIncludeIncludeBase* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::IncludeBase>(org_context, obj); }

bool haxorg_ImmCmdIncludeExample___eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeExample __this, haxorg_ImmCmdIncludeExample other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdInclude::Example::*)(org::imm::ImmCmdInclude::Example const&) const>(&org::imm::ImmCmdInclude::Example::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdIncludeExample(OrgContext* org_context, haxorg_ImmCmdIncludeExample* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::Example>(org_context, obj); }

haxorg_HstdStr haxorg_ImmCmdIncludeExport_get_language(OrgContext* org_context, haxorg_ImmCmdIncludeExport __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmCmdInclude::Export, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmCmdIncludeExport>(org_context, __this, &org::imm::ImmCmdInclude::Export::language); }

bool haxorg_ImmCmdIncludeExport___eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeExport __this, haxorg_ImmCmdIncludeExport other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdInclude::Export::*)(org::imm::ImmCmdInclude::Export const&) const>(&org::imm::ImmCmdInclude::Export::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdIncludeExport(OrgContext* org_context, haxorg_ImmCmdIncludeExport* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::Export>(org_context, obj); }

haxorg_HstdStr haxorg_ImmCmdIncludeCustom_get_blockName(OrgContext* org_context, haxorg_ImmCmdIncludeCustom __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmCmdInclude::Custom, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmCmdIncludeCustom>(org_context, __this, &org::imm::ImmCmdInclude::Custom::blockName); }

bool haxorg_ImmCmdIncludeCustom___eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeCustom __this, haxorg_ImmCmdIncludeCustom other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdInclude::Custom::*)(org::imm::ImmCmdInclude::Custom const&) const>(&org::imm::ImmCmdInclude::Custom::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdIncludeCustom(OrgContext* org_context, haxorg_ImmCmdIncludeCustom* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::Custom>(org_context, obj); }

haxorg_HstdStr haxorg_ImmCmdIncludeSrc_get_language(OrgContext* org_context, haxorg_ImmCmdIncludeSrc __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmCmdInclude::Src, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmCmdIncludeSrc>(org_context, __this, &org::imm::ImmCmdInclude::Src::language); }

bool haxorg_ImmCmdIncludeSrc___eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeSrc __this, haxorg_ImmCmdIncludeSrc other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdInclude::Src::*)(org::imm::ImmCmdInclude::Src const&) const>(&org::imm::ImmCmdInclude::Src::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdIncludeSrc(OrgContext* org_context, haxorg_ImmCmdIncludeSrc* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::Src>(org_context, obj); }

haxorg_OptOfBool haxorg_ImmCmdIncludeOrgDocument_get_onlyContent(OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument __this) { return org::bind::c::get_cpp_field<haxorg_OptOfBool, org::imm::ImmCmdInclude::OrgDocument, hstd::ext::ImmBox<hstd::Opt<bool>>, haxorg_ImmCmdIncludeOrgDocument>(org_context, __this, &org::imm::ImmCmdInclude::OrgDocument::onlyContent); }

haxorg_OptOfSubtreePath haxorg_ImmCmdIncludeOrgDocument_get_subtreePath(OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument __this) { return org::bind::c::get_cpp_field<haxorg_OptOfSubtreePath, org::imm::ImmCmdInclude::OrgDocument, hstd::ext::ImmBox<hstd::Opt<org::sem::SubtreePath>>, haxorg_ImmCmdIncludeOrgDocument>(org_context, __this, &org::imm::ImmCmdInclude::OrgDocument::subtreePath); }

haxorg_OptOfInt haxorg_ImmCmdIncludeOrgDocument_get_minLevel(OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument __this) { return org::bind::c::get_cpp_field<haxorg_OptOfInt, org::imm::ImmCmdInclude::OrgDocument, hstd::ext::ImmBox<hstd::Opt<int>>, haxorg_ImmCmdIncludeOrgDocument>(org_context, __this, &org::imm::ImmCmdInclude::OrgDocument::minLevel); }

haxorg_OptOfStr haxorg_ImmCmdIncludeOrgDocument_get_customIdTarget(OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::imm::ImmCmdInclude::OrgDocument, hstd::ext::ImmBox<hstd::Opt<hstd::Str>>, haxorg_ImmCmdIncludeOrgDocument>(org_context, __this, &org::imm::ImmCmdInclude::OrgDocument::customIdTarget); }

bool haxorg_ImmCmdIncludeOrgDocument___eq___const(OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument __this, haxorg_ImmCmdIncludeOrgDocument other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdInclude::OrgDocument::*)(org::imm::ImmCmdInclude::OrgDocument const&) const>(&org::imm::ImmCmdInclude::OrgDocument::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdIncludeOrgDocument(OrgContext* org_context, haxorg_ImmCmdIncludeOrgDocument* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude::OrgDocument>(org_context, obj); }

void haxorg_destroy_ImmCmdInclude(OrgContext* org_context, haxorg_ImmCmdInclude* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdInclude>(org_context, obj); }

void haxorg_destroy_ImmAdapterOrgAPI(OrgContext* org_context, haxorg_ImmAdapterOrgAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterOrgAPI>(org_context, obj); }

haxorg_AttrGroup haxorg_Cmd_get_attrs(OrgContext* org_context, haxorg_Cmd __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::sem::Cmd, org::sem::AttrGroup, haxorg_Cmd>(org_context, __this, &org::sem::Cmd::attrs); }

haxorg_HstdVecOfAttrValue haxorg_Cmd_getAttrs_const(OrgContext* org_context, haxorg_Cmd __this, haxorg_OptOfStr key) { return org::bind::c::execute_cpp<haxorg_HstdVecOfAttrValue>(static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Cmd::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Cmd::getAttrs), org_context, __this, key); }

haxorg_OptOfAttrValue haxorg_Cmd_getFirstAttr_const(OrgContext* org_context, haxorg_Cmd __this, haxorg_HstdStr kind) { return org::bind::c::execute_cpp<haxorg_OptOfAttrValue>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Cmd::*)(hstd::Str const&) const>(&org::sem::Cmd::getFirstAttr), org_context, __this, kind); }

void haxorg_destroy_Cmd(OrgContext* org_context, haxorg_Cmd* obj) { org::bind::c::execute_destroy<org::sem::Cmd>(org_context, obj); }

haxorg_HstdStr haxorg_CmdCustomRaw_get_name(OrgContext* org_context, haxorg_CmdCustomRaw __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::CmdCustomRaw, hstd::Str, haxorg_CmdCustomRaw>(org_context, __this, &org::sem::CmdCustomRaw::name); }

bool haxorg_CmdCustomRaw_get_isAttached(OrgContext* org_context, haxorg_CmdCustomRaw __this) { return org::bind::c::get_cpp_field<bool, org::sem::CmdCustomRaw, bool, haxorg_CmdCustomRaw>(org_context, __this, &org::sem::CmdCustomRaw::isAttached); }

haxorg_HstdStr haxorg_CmdCustomRaw_get_text(OrgContext* org_context, haxorg_CmdCustomRaw __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::CmdCustomRaw, hstd::Str, haxorg_CmdCustomRaw>(org_context, __this, &org::sem::CmdCustomRaw::text); }

void haxorg_destroy_CmdCustomRaw(OrgContext* org_context, haxorg_CmdCustomRaw* obj) { org::bind::c::execute_destroy<org::sem::CmdCustomRaw>(org_context, obj); }

haxorg_HstdStr haxorg_CmdCustomText_get_name(OrgContext* org_context, haxorg_CmdCustomText __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::CmdCustomText, hstd::Str, haxorg_CmdCustomText>(org_context, __this, &org::sem::CmdCustomText::name); }

bool haxorg_CmdCustomText_get_isAttached(OrgContext* org_context, haxorg_CmdCustomText __this) { return org::bind::c::get_cpp_field<bool, org::sem::CmdCustomText, bool, haxorg_CmdCustomText>(org_context, __this, &org::sem::CmdCustomText::isAttached); }

haxorg_SemIdOfOrg haxorg_CmdCustomText_get_text(OrgContext* org_context, haxorg_CmdCustomText __this) { return org::bind::c::get_cpp_field<haxorg_SemIdOfOrg, org::sem::CmdCustomText, org::sem::SemId<org::sem::Paragraph>, haxorg_CmdCustomText>(org_context, __this, &org::sem::CmdCustomText::text); }

void haxorg_destroy_CmdCustomText(OrgContext* org_context, haxorg_CmdCustomText* obj) { org::bind::c::execute_destroy<org::sem::CmdCustomText>(org_context, obj); }

haxorg_OptOfSemIdOfParagraph haxorg_Link_get_description(OrgContext* org_context, haxorg_Link __this) { return org::bind::c::get_cpp_field<haxorg_OptOfSemIdOfParagraph, org::sem::Link, hstd::Opt<org::sem::SemId<org::sem::Paragraph>>, haxorg_Link>(org_context, __this, &org::sem::Link::description); }

haxorg_LinkTarget haxorg_Link_get_target(OrgContext* org_context, haxorg_Link __this) { return org::bind::c::get_cpp_field<haxorg_LinkTarget, org::sem::Link, org::sem::LinkTarget, haxorg_Link>(org_context, __this, &org::sem::Link::target); }

void haxorg_destroy_Link(OrgContext* org_context, haxorg_Link* obj) { org::bind::c::execute_destroy<org::sem::Link>(org_context, obj); }

void haxorg_destroy_BlockComment(OrgContext* org_context, haxorg_BlockComment* obj) { org::bind::c::execute_destroy<org::sem::BlockComment>(org_context, obj); }

bool haxorg_Paragraph_isFootnoteDefinition_const(OrgContext* org_context, haxorg_Paragraph __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::isFootnoteDefinition), org_context, __this); }

haxorg_OptOfStr haxorg_Paragraph_getFootnoteName_const(OrgContext* org_context, haxorg_Paragraph __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getFootnoteName), org_context, __this); }

bool haxorg_Paragraph_hasAdmonition_const(OrgContext* org_context, haxorg_Paragraph __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasAdmonition), org_context, __this); }

haxorg_HstdVecOfStr haxorg_Paragraph_getAdmonitions_const(OrgContext* org_context, haxorg_Paragraph __this) { return org::bind::c::execute_cpp<haxorg_HstdVecOfStr>(static_cast<hstd::Vec<hstd::Str>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getAdmonitions), org_context, __this); }

haxorg_HstdVecOfSemIdOfBigIdent haxorg_Paragraph_getAdmonitionNodes_const(OrgContext* org_context, haxorg_Paragraph __this) { return org::bind::c::execute_cpp<haxorg_HstdVecOfSemIdOfBigIdent>(static_cast<hstd::Vec<org::sem::SemId<org::sem::BigIdent>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getAdmonitionNodes), org_context, __this); }

bool haxorg_Paragraph_hasTimestamp_const(OrgContext* org_context, haxorg_Paragraph __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasTimestamp), org_context, __this); }

haxorg_HstdVecOfUserTime haxorg_Paragraph_getTimestamps_const(OrgContext* org_context, haxorg_Paragraph __this) { return org::bind::c::execute_cpp<haxorg_HstdVecOfUserTime>(static_cast<hstd::Vec<hstd::UserTime>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getTimestamps), org_context, __this); }

haxorg_HstdVecOfSemIdOfTime haxorg_Paragraph_getTimestampNodes_const(OrgContext* org_context, haxorg_Paragraph __this) { return org::bind::c::execute_cpp<haxorg_HstdVecOfSemIdOfTime>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Time>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getTimestampNodes), org_context, __this); }

bool haxorg_Paragraph_hasLeadHashtags_const(OrgContext* org_context, haxorg_Paragraph __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::hasLeadHashtags), org_context, __this); }

haxorg_HstdVecOfSemIdOfHashTag haxorg_Paragraph_getLeadHashtags_const(OrgContext* org_context, haxorg_Paragraph __this) { return org::bind::c::execute_cpp<haxorg_HstdVecOfSemIdOfHashTag>(static_cast<hstd::Vec<org::sem::SemId<org::sem::HashTag>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getLeadHashtags), org_context, __this); }

haxorg_HstdVecOfSemIdOfOrg haxorg_Paragraph_getBody_const(OrgContext* org_context, haxorg_Paragraph __this) { return org::bind::c::execute_cpp<haxorg_HstdVecOfSemIdOfOrg>(static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Paragraph::*)() const>(&org::sem::Paragraph::getBody), org_context, __this); }

void haxorg_destroy_Paragraph(OrgContext* org_context, haxorg_Paragraph* obj) { org::bind::c::execute_destroy<org::sem::Paragraph>(org_context, obj); }

haxorg_HstdVecOfAttrValue haxorg_List_getListAttrs_const(OrgContext* org_context, haxorg_List __this, haxorg_HstdStr key) { return org::bind::c::execute_cpp<haxorg_HstdVecOfAttrValue>(static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::List::*)(hstd::Str const&) const>(&org::sem::List::getListAttrs), org_context, __this, key); }

haxorg_ListFormattingMode haxorg_List_getListFormattingMode_const(OrgContext* org_context, haxorg_List __this) { return org::bind::c::execute_cpp<haxorg_ListFormattingMode>(static_cast<ListFormattingMode(org::sem::List::*)() const>(&org::sem::List::getListFormattingMode), org_context, __this); }

bool haxorg_List_isDescriptionList_const(OrgContext* org_context, haxorg_List __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::List::*)() const>(&org::sem::List::isDescriptionList), org_context, __this); }

bool haxorg_List_isNumberedList_const(OrgContext* org_context, haxorg_List __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::sem::List::*)() const>(&org::sem::List::isNumberedList), org_context, __this); }

void haxorg_destroy_List(OrgContext* org_context, haxorg_List* obj) { org::bind::c::execute_destroy<org::sem::List>(org_context, obj); }

haxorg_HashTagText haxorg_HashTag_get_text(OrgContext* org_context, haxorg_HashTag __this) { return org::bind::c::get_cpp_field<haxorg_HashTagText, org::sem::HashTag, org::sem::HashTagText, haxorg_HashTag>(org_context, __this, &org::sem::HashTag::text); }

void haxorg_destroy_HashTag(OrgContext* org_context, haxorg_HashTag* obj) { org::bind::c::execute_destroy<org::sem::HashTag>(org_context, obj); }

haxorg_HstdStr haxorg_InlineFootnote_get_tag(OrgContext* org_context, haxorg_InlineFootnote __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::InlineFootnote, hstd::Str, haxorg_InlineFootnote>(org_context, __this, &org::sem::InlineFootnote::tag); }

haxorg_OptOfSemIdOfOrg haxorg_InlineFootnote_get_definition(OrgContext* org_context, haxorg_InlineFootnote __this) { return org::bind::c::get_cpp_field<haxorg_OptOfSemIdOfOrg, org::sem::InlineFootnote, hstd::Opt<org::sem::SemId<org::sem::Org>>, haxorg_InlineFootnote>(org_context, __this, &org::sem::InlineFootnote::definition); }

void haxorg_destroy_InlineFootnote(OrgContext* org_context, haxorg_InlineFootnote* obj) { org::bind::c::execute_destroy<org::sem::InlineFootnote>(org_context, obj); }

haxorg_HstdStr haxorg_InlineExport_get_exporter(OrgContext* org_context, haxorg_InlineExport __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::InlineExport, hstd::Str, haxorg_InlineExport>(org_context, __this, &org::sem::InlineExport::exporter); }

haxorg_HstdStr haxorg_InlineExport_get_content(OrgContext* org_context, haxorg_InlineExport __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::InlineExport, hstd::Str, haxorg_InlineExport>(org_context, __this, &org::sem::InlineExport::content); }

void haxorg_destroy_InlineExport(OrgContext* org_context, haxorg_InlineExport* obj) { org::bind::c::execute_destroy<org::sem::InlineExport>(org_context, obj); }

void haxorg_destroy_Escaped(OrgContext* org_context, haxorg_Escaped* obj) { org::bind::c::execute_destroy<org::sem::Escaped>(org_context, obj); }

void haxorg_destroy_Newline(OrgContext* org_context, haxorg_Newline* obj) { org::bind::c::execute_destroy<org::sem::Newline>(org_context, obj); }

void haxorg_destroy_Space(OrgContext* org_context, haxorg_Space* obj) { org::bind::c::execute_destroy<org::sem::Space>(org_context, obj); }

void haxorg_destroy_Word(OrgContext* org_context, haxorg_Word* obj) { org::bind::c::execute_destroy<org::sem::Word>(org_context, obj); }

void haxorg_destroy_AtMention(OrgContext* org_context, haxorg_AtMention* obj) { org::bind::c::execute_destroy<org::sem::AtMention>(org_context, obj); }

void haxorg_destroy_RawText(OrgContext* org_context, haxorg_RawText* obj) { org::bind::c::execute_destroy<org::sem::RawText>(org_context, obj); }

void haxorg_destroy_Punctuation(OrgContext* org_context, haxorg_Punctuation* obj) { org::bind::c::execute_destroy<org::sem::Punctuation>(org_context, obj); }

void haxorg_destroy_Placeholder(OrgContext* org_context, haxorg_Placeholder* obj) { org::bind::c::execute_destroy<org::sem::Placeholder>(org_context, obj); }

void haxorg_destroy_BigIdent(OrgContext* org_context, haxorg_BigIdent* obj) { org::bind::c::execute_destroy<org::sem::BigIdent>(org_context, obj); }

void haxorg_destroy_TextTarget(OrgContext* org_context, haxorg_TextTarget* obj) { org::bind::c::execute_destroy<org::sem::TextTarget>(org_context, obj); }

void haxorg_destroy_ErrorSkipToken(OrgContext* org_context, haxorg_ErrorSkipToken* obj) { org::bind::c::execute_destroy<org::sem::ErrorSkipToken>(org_context, obj); }

void haxorg_destroy_Bold(OrgContext* org_context, haxorg_Bold* obj) { org::bind::c::execute_destroy<org::sem::Bold>(org_context, obj); }

void haxorg_destroy_Underline(OrgContext* org_context, haxorg_Underline* obj) { org::bind::c::execute_destroy<org::sem::Underline>(org_context, obj); }

void haxorg_destroy_Monospace(OrgContext* org_context, haxorg_Monospace* obj) { org::bind::c::execute_destroy<org::sem::Monospace>(org_context, obj); }

void haxorg_destroy_MarkQuote(OrgContext* org_context, haxorg_MarkQuote* obj) { org::bind::c::execute_destroy<org::sem::MarkQuote>(org_context, obj); }

void haxorg_destroy_Verbatim(OrgContext* org_context, haxorg_Verbatim* obj) { org::bind::c::execute_destroy<org::sem::Verbatim>(org_context, obj); }

void haxorg_destroy_Italic(OrgContext* org_context, haxorg_Italic* obj) { org::bind::c::execute_destroy<org::sem::Italic>(org_context, obj); }

void haxorg_destroy_Strike(OrgContext* org_context, haxorg_Strike* obj) { org::bind::c::execute_destroy<org::sem::Strike>(org_context, obj); }

void haxorg_destroy_Par(OrgContext* org_context, haxorg_Par* obj) { org::bind::c::execute_destroy<org::sem::Par>(org_context, obj); }

haxorg_AttrGroup haxorg_ImmCmd_get_attrs(OrgContext* org_context, haxorg_ImmCmd __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::imm::ImmCmd, org::sem::AttrGroup, haxorg_ImmCmd>(org_context, __this, &org::imm::ImmCmd::attrs); }

bool haxorg_ImmCmd___eq___const(OrgContext* org_context, haxorg_ImmCmd __this, haxorg_ImmCmd other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmd::*)(org::imm::ImmCmd const&) const>(&org::imm::ImmCmd::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmd(OrgContext* org_context, haxorg_ImmCmd* obj) { org::bind::c::execute_destroy<org::imm::ImmCmd>(org_context, obj); }

haxorg_HstdStr haxorg_ImmCmdCustomRaw_get_name(OrgContext* org_context, haxorg_ImmCmdCustomRaw __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmCmdCustomRaw, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmCmdCustomRaw>(org_context, __this, &org::imm::ImmCmdCustomRaw::name); }

bool haxorg_ImmCmdCustomRaw_get_isAttached(OrgContext* org_context, haxorg_ImmCmdCustomRaw __this) { return org::bind::c::get_cpp_field<bool, org::imm::ImmCmdCustomRaw, bool, haxorg_ImmCmdCustomRaw>(org_context, __this, &org::imm::ImmCmdCustomRaw::isAttached); }

haxorg_HstdStr haxorg_ImmCmdCustomRaw_get_text(OrgContext* org_context, haxorg_ImmCmdCustomRaw __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmCmdCustomRaw, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmCmdCustomRaw>(org_context, __this, &org::imm::ImmCmdCustomRaw::text); }

bool haxorg_ImmCmdCustomRaw___eq___const(OrgContext* org_context, haxorg_ImmCmdCustomRaw __this, haxorg_ImmCmdCustomRaw other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdCustomRaw::*)(org::imm::ImmCmdCustomRaw const&) const>(&org::imm::ImmCmdCustomRaw::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdCustomRaw(OrgContext* org_context, haxorg_ImmCmdCustomRaw* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCustomRaw>(org_context, obj); }

haxorg_HstdStr haxorg_ImmCmdCustomText_get_name(OrgContext* org_context, haxorg_ImmCmdCustomText __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmCmdCustomText, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmCmdCustomText>(org_context, __this, &org::imm::ImmCmdCustomText::name); }

bool haxorg_ImmCmdCustomText_get_isAttached(OrgContext* org_context, haxorg_ImmCmdCustomText __this) { return org::bind::c::get_cpp_field<bool, org::imm::ImmCmdCustomText, bool, haxorg_ImmCmdCustomText>(org_context, __this, &org::imm::ImmCmdCustomText::isAttached); }

haxorg_ImmId haxorg_ImmCmdCustomText_get_text(OrgContext* org_context, haxorg_ImmCmdCustomText __this) { return org::bind::c::get_cpp_field<haxorg_ImmId, org::imm::ImmCmdCustomText, org::imm::ImmIdT<org::imm::ImmParagraph>, haxorg_ImmCmdCustomText>(org_context, __this, &org::imm::ImmCmdCustomText::text); }

bool haxorg_ImmCmdCustomText___eq___const(OrgContext* org_context, haxorg_ImmCmdCustomText __this, haxorg_ImmCmdCustomText other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdCustomText::*)(org::imm::ImmCmdCustomText const&) const>(&org::imm::ImmCmdCustomText::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdCustomText(OrgContext* org_context, haxorg_ImmCmdCustomText* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCustomText>(org_context, obj); }

haxorg_OptOfImmIdTOfImmParagraph haxorg_ImmLink_get_description(OrgContext* org_context, haxorg_ImmLink __this) { return org::bind::c::get_cpp_field<haxorg_OptOfImmIdTOfImmParagraph, org::imm::ImmLink, hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>>, haxorg_ImmLink>(org_context, __this, &org::imm::ImmLink::description); }

haxorg_LinkTarget haxorg_ImmLink_get_target(OrgContext* org_context, haxorg_ImmLink __this) { return org::bind::c::get_cpp_field<haxorg_LinkTarget, org::imm::ImmLink, org::sem::LinkTarget, haxorg_ImmLink>(org_context, __this, &org::imm::ImmLink::target); }

bool haxorg_ImmLink___eq___const(OrgContext* org_context, haxorg_ImmLink __this, haxorg_ImmLink other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmLink::*)(org::imm::ImmLink const&) const>(&org::imm::ImmLink::operator==), org_context, __this, other); }

void haxorg_destroy_ImmLink(OrgContext* org_context, haxorg_ImmLink* obj) { org::bind::c::execute_destroy<org::imm::ImmLink>(org_context, obj); }

bool haxorg_ImmBlockComment___eq___const(OrgContext* org_context, haxorg_ImmBlockComment __this, haxorg_ImmBlockComment other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmBlockComment::*)(org::imm::ImmBlockComment const&) const>(&org::imm::ImmBlockComment::operator==), org_context, __this, other); }

void haxorg_destroy_ImmBlockComment(OrgContext* org_context, haxorg_ImmBlockComment* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockComment>(org_context, obj); }

bool haxorg_ImmParagraph___eq___const(OrgContext* org_context, haxorg_ImmParagraph __this, haxorg_ImmParagraph other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmParagraph::*)(org::imm::ImmParagraph const&) const>(&org::imm::ImmParagraph::operator==), org_context, __this, other); }

void haxorg_destroy_ImmParagraph(OrgContext* org_context, haxorg_ImmParagraph* obj) { org::bind::c::execute_destroy<org::imm::ImmParagraph>(org_context, obj); }

bool haxorg_ImmList___eq___const(OrgContext* org_context, haxorg_ImmList __this, haxorg_ImmList other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmList::*)(org::imm::ImmList const&) const>(&org::imm::ImmList::operator==), org_context, __this, other); }

void haxorg_destroy_ImmList(OrgContext* org_context, haxorg_ImmList* obj) { org::bind::c::execute_destroy<org::imm::ImmList>(org_context, obj); }

haxorg_HashTagText haxorg_ImmHashTag_get_text(OrgContext* org_context, haxorg_ImmHashTag __this) { return org::bind::c::get_cpp_field<haxorg_HashTagText, org::imm::ImmHashTag, org::sem::HashTagText, haxorg_ImmHashTag>(org_context, __this, &org::imm::ImmHashTag::text); }

bool haxorg_ImmHashTag___eq___const(OrgContext* org_context, haxorg_ImmHashTag __this, haxorg_ImmHashTag other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmHashTag::*)(org::imm::ImmHashTag const&) const>(&org::imm::ImmHashTag::operator==), org_context, __this, other); }

void haxorg_destroy_ImmHashTag(OrgContext* org_context, haxorg_ImmHashTag* obj) { org::bind::c::execute_destroy<org::imm::ImmHashTag>(org_context, obj); }

haxorg_HstdStr haxorg_ImmInlineFootnote_get_tag(OrgContext* org_context, haxorg_ImmInlineFootnote __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmInlineFootnote, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmInlineFootnote>(org_context, __this, &org::imm::ImmInlineFootnote::tag); }

haxorg_OptOfImmIdTOfImmOrg haxorg_ImmInlineFootnote_get_definition(OrgContext* org_context, haxorg_ImmInlineFootnote __this) { return org::bind::c::get_cpp_field<haxorg_OptOfImmIdTOfImmOrg, org::imm::ImmInlineFootnote, hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmOrg>>>, haxorg_ImmInlineFootnote>(org_context, __this, &org::imm::ImmInlineFootnote::definition); }

bool haxorg_ImmInlineFootnote___eq___const(OrgContext* org_context, haxorg_ImmInlineFootnote __this, haxorg_ImmInlineFootnote other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmInlineFootnote::*)(org::imm::ImmInlineFootnote const&) const>(&org::imm::ImmInlineFootnote::operator==), org_context, __this, other); }

void haxorg_destroy_ImmInlineFootnote(OrgContext* org_context, haxorg_ImmInlineFootnote* obj) { org::bind::c::execute_destroy<org::imm::ImmInlineFootnote>(org_context, obj); }

haxorg_HstdStr haxorg_ImmInlineExport_get_exporter(OrgContext* org_context, haxorg_ImmInlineExport __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmInlineExport, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmInlineExport>(org_context, __this, &org::imm::ImmInlineExport::exporter); }

haxorg_HstdStr haxorg_ImmInlineExport_get_content(OrgContext* org_context, haxorg_ImmInlineExport __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmInlineExport, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmInlineExport>(org_context, __this, &org::imm::ImmInlineExport::content); }

bool haxorg_ImmInlineExport___eq___const(OrgContext* org_context, haxorg_ImmInlineExport __this, haxorg_ImmInlineExport other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmInlineExport::*)(org::imm::ImmInlineExport const&) const>(&org::imm::ImmInlineExport::operator==), org_context, __this, other); }

void haxorg_destroy_ImmInlineExport(OrgContext* org_context, haxorg_ImmInlineExport* obj) { org::bind::c::execute_destroy<org::imm::ImmInlineExport>(org_context, obj); }

bool haxorg_ImmEscaped___eq___const(OrgContext* org_context, haxorg_ImmEscaped __this, haxorg_ImmEscaped other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmEscaped::*)(org::imm::ImmEscaped const&) const>(&org::imm::ImmEscaped::operator==), org_context, __this, other); }

void haxorg_destroy_ImmEscaped(OrgContext* org_context, haxorg_ImmEscaped* obj) { org::bind::c::execute_destroy<org::imm::ImmEscaped>(org_context, obj); }

bool haxorg_ImmNewline___eq___const(OrgContext* org_context, haxorg_ImmNewline __this, haxorg_ImmNewline other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmNewline::*)(org::imm::ImmNewline const&) const>(&org::imm::ImmNewline::operator==), org_context, __this, other); }

void haxorg_destroy_ImmNewline(OrgContext* org_context, haxorg_ImmNewline* obj) { org::bind::c::execute_destroy<org::imm::ImmNewline>(org_context, obj); }

bool haxorg_ImmSpace___eq___const(OrgContext* org_context, haxorg_ImmSpace __this, haxorg_ImmSpace other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmSpace::*)(org::imm::ImmSpace const&) const>(&org::imm::ImmSpace::operator==), org_context, __this, other); }

void haxorg_destroy_ImmSpace(OrgContext* org_context, haxorg_ImmSpace* obj) { org::bind::c::execute_destroy<org::imm::ImmSpace>(org_context, obj); }

bool haxorg_ImmWord___eq___const(OrgContext* org_context, haxorg_ImmWord __this, haxorg_ImmWord other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmWord::*)(org::imm::ImmWord const&) const>(&org::imm::ImmWord::operator==), org_context, __this, other); }

void haxorg_destroy_ImmWord(OrgContext* org_context, haxorg_ImmWord* obj) { org::bind::c::execute_destroy<org::imm::ImmWord>(org_context, obj); }

bool haxorg_ImmAtMention___eq___const(OrgContext* org_context, haxorg_ImmAtMention __this, haxorg_ImmAtMention other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAtMention::*)(org::imm::ImmAtMention const&) const>(&org::imm::ImmAtMention::operator==), org_context, __this, other); }

void haxorg_destroy_ImmAtMention(OrgContext* org_context, haxorg_ImmAtMention* obj) { org::bind::c::execute_destroy<org::imm::ImmAtMention>(org_context, obj); }

bool haxorg_ImmRawText___eq___const(OrgContext* org_context, haxorg_ImmRawText __this, haxorg_ImmRawText other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmRawText::*)(org::imm::ImmRawText const&) const>(&org::imm::ImmRawText::operator==), org_context, __this, other); }

void haxorg_destroy_ImmRawText(OrgContext* org_context, haxorg_ImmRawText* obj) { org::bind::c::execute_destroy<org::imm::ImmRawText>(org_context, obj); }

bool haxorg_ImmPunctuation___eq___const(OrgContext* org_context, haxorg_ImmPunctuation __this, haxorg_ImmPunctuation other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmPunctuation::*)(org::imm::ImmPunctuation const&) const>(&org::imm::ImmPunctuation::operator==), org_context, __this, other); }

void haxorg_destroy_ImmPunctuation(OrgContext* org_context, haxorg_ImmPunctuation* obj) { org::bind::c::execute_destroy<org::imm::ImmPunctuation>(org_context, obj); }

bool haxorg_ImmPlaceholder___eq___const(OrgContext* org_context, haxorg_ImmPlaceholder __this, haxorg_ImmPlaceholder other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmPlaceholder::*)(org::imm::ImmPlaceholder const&) const>(&org::imm::ImmPlaceholder::operator==), org_context, __this, other); }

void haxorg_destroy_ImmPlaceholder(OrgContext* org_context, haxorg_ImmPlaceholder* obj) { org::bind::c::execute_destroy<org::imm::ImmPlaceholder>(org_context, obj); }

bool haxorg_ImmBigIdent___eq___const(OrgContext* org_context, haxorg_ImmBigIdent __this, haxorg_ImmBigIdent other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmBigIdent::*)(org::imm::ImmBigIdent const&) const>(&org::imm::ImmBigIdent::operator==), org_context, __this, other); }

void haxorg_destroy_ImmBigIdent(OrgContext* org_context, haxorg_ImmBigIdent* obj) { org::bind::c::execute_destroy<org::imm::ImmBigIdent>(org_context, obj); }

bool haxorg_ImmTextTarget___eq___const(OrgContext* org_context, haxorg_ImmTextTarget __this, haxorg_ImmTextTarget other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmTextTarget::*)(org::imm::ImmTextTarget const&) const>(&org::imm::ImmTextTarget::operator==), org_context, __this, other); }

void haxorg_destroy_ImmTextTarget(OrgContext* org_context, haxorg_ImmTextTarget* obj) { org::bind::c::execute_destroy<org::imm::ImmTextTarget>(org_context, obj); }

bool haxorg_ImmErrorSkipToken___eq___const(OrgContext* org_context, haxorg_ImmErrorSkipToken __this, haxorg_ImmErrorSkipToken other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmErrorSkipToken::*)(org::imm::ImmErrorSkipToken const&) const>(&org::imm::ImmErrorSkipToken::operator==), org_context, __this, other); }

void haxorg_destroy_ImmErrorSkipToken(OrgContext* org_context, haxorg_ImmErrorSkipToken* obj) { org::bind::c::execute_destroy<org::imm::ImmErrorSkipToken>(org_context, obj); }

bool haxorg_ImmBold___eq___const(OrgContext* org_context, haxorg_ImmBold __this, haxorg_ImmBold other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmBold::*)(org::imm::ImmBold const&) const>(&org::imm::ImmBold::operator==), org_context, __this, other); }

void haxorg_destroy_ImmBold(OrgContext* org_context, haxorg_ImmBold* obj) { org::bind::c::execute_destroy<org::imm::ImmBold>(org_context, obj); }

bool haxorg_ImmUnderline___eq___const(OrgContext* org_context, haxorg_ImmUnderline __this, haxorg_ImmUnderline other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmUnderline::*)(org::imm::ImmUnderline const&) const>(&org::imm::ImmUnderline::operator==), org_context, __this, other); }

void haxorg_destroy_ImmUnderline(OrgContext* org_context, haxorg_ImmUnderline* obj) { org::bind::c::execute_destroy<org::imm::ImmUnderline>(org_context, obj); }

bool haxorg_ImmMonospace___eq___const(OrgContext* org_context, haxorg_ImmMonospace __this, haxorg_ImmMonospace other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmMonospace::*)(org::imm::ImmMonospace const&) const>(&org::imm::ImmMonospace::operator==), org_context, __this, other); }

void haxorg_destroy_ImmMonospace(OrgContext* org_context, haxorg_ImmMonospace* obj) { org::bind::c::execute_destroy<org::imm::ImmMonospace>(org_context, obj); }

bool haxorg_ImmMarkQuote___eq___const(OrgContext* org_context, haxorg_ImmMarkQuote __this, haxorg_ImmMarkQuote other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmMarkQuote::*)(org::imm::ImmMarkQuote const&) const>(&org::imm::ImmMarkQuote::operator==), org_context, __this, other); }

void haxorg_destroy_ImmMarkQuote(OrgContext* org_context, haxorg_ImmMarkQuote* obj) { org::bind::c::execute_destroy<org::imm::ImmMarkQuote>(org_context, obj); }

bool haxorg_ImmVerbatim___eq___const(OrgContext* org_context, haxorg_ImmVerbatim __this, haxorg_ImmVerbatim other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmVerbatim::*)(org::imm::ImmVerbatim const&) const>(&org::imm::ImmVerbatim::operator==), org_context, __this, other); }

void haxorg_destroy_ImmVerbatim(OrgContext* org_context, haxorg_ImmVerbatim* obj) { org::bind::c::execute_destroy<org::imm::ImmVerbatim>(org_context, obj); }

bool haxorg_ImmItalic___eq___const(OrgContext* org_context, haxorg_ImmItalic __this, haxorg_ImmItalic other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmItalic::*)(org::imm::ImmItalic const&) const>(&org::imm::ImmItalic::operator==), org_context, __this, other); }

void haxorg_destroy_ImmItalic(OrgContext* org_context, haxorg_ImmItalic* obj) { org::bind::c::execute_destroy<org::imm::ImmItalic>(org_context, obj); }

bool haxorg_ImmStrike___eq___const(OrgContext* org_context, haxorg_ImmStrike __this, haxorg_ImmStrike other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmStrike::*)(org::imm::ImmStrike const&) const>(&org::imm::ImmStrike::operator==), org_context, __this, other); }

void haxorg_destroy_ImmStrike(OrgContext* org_context, haxorg_ImmStrike* obj) { org::bind::c::execute_destroy<org::imm::ImmStrike>(org_context, obj); }

bool haxorg_ImmPar___eq___const(OrgContext* org_context, haxorg_ImmPar __this, haxorg_ImmPar other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmPar::*)(org::imm::ImmPar const&) const>(&org::imm::ImmPar::operator==), org_context, __this, other); }

void haxorg_destroy_ImmPar(OrgContext* org_context, haxorg_ImmPar* obj) { org::bind::c::execute_destroy<org::imm::ImmPar>(org_context, obj); }

void haxorg_destroy_ImmAdapterStmtAPI(OrgContext* org_context, haxorg_ImmAdapterStmtAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterStmtAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterSubtreeAPI(OrgContext* org_context, haxorg_ImmAdapterSubtreeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSubtreeAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterNoNodeAPI(OrgContext* org_context, haxorg_ImmAdapterNoNodeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterNoNodeAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterAttrAPI(OrgContext* org_context, haxorg_ImmAdapterAttrAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterAttrAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterAttrListAPI(OrgContext* org_context, haxorg_ImmAdapterAttrListAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterAttrListAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterAttrsAPI(OrgContext* org_context, haxorg_ImmAdapterAttrsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterAttrsAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterErrorItemAPI(OrgContext* org_context, haxorg_ImmAdapterErrorItemAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterErrorItemAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterErrorGroupAPI(OrgContext* org_context, haxorg_ImmAdapterErrorGroupAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterErrorGroupAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterErrorSkipGroupAPI(OrgContext* org_context, haxorg_ImmAdapterErrorSkipGroupAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterErrorSkipGroupAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterErrorSkipTokenAPI(OrgContext* org_context, haxorg_ImmAdapterErrorSkipTokenAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterErrorSkipTokenAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterStmtListAPI(OrgContext* org_context, haxorg_ImmAdapterStmtListAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterStmtListAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterEmptyAPI(OrgContext* org_context, haxorg_ImmAdapterEmptyAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterEmptyAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterInlineAPI(OrgContext* org_context, haxorg_ImmAdapterInlineAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterInlineAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterTimeAPI(OrgContext* org_context, haxorg_ImmAdapterTimeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterTimeAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterTimeRangeAPI(OrgContext* org_context, haxorg_ImmAdapterTimeRangeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterTimeRangeAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterMacroAPI(OrgContext* org_context, haxorg_ImmAdapterMacroAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterMacroAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterSymbolAPI(OrgContext* org_context, haxorg_ImmAdapterSymbolAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSymbolAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterLeafAPI(OrgContext* org_context, haxorg_ImmAdapterLeafAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterLeafAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterMarkupAPI(OrgContext* org_context, haxorg_ImmAdapterMarkupAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterMarkupAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterLatexAPI(OrgContext* org_context, haxorg_ImmAdapterLatexAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterLatexAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterSubtreeLogAPI(OrgContext* org_context, haxorg_ImmAdapterSubtreeLogAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSubtreeLogAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterColonExampleAPI(OrgContext* org_context, haxorg_ImmAdapterColonExampleAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterColonExampleAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCallAPI(OrgContext* org_context, haxorg_ImmAdapterCallAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCallAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterFileAPI(OrgContext* org_context, haxorg_ImmAdapterFileAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterFileAPI>(org_context, obj); }

haxorg_StdOptional haxorg_ImmAdapterDirectoryAPI_getFsSubnode_const(OrgContext* org_context, haxorg_ImmAdapterDirectoryAPI __this, haxorg_HstdStr name, bool withPath) { return org::bind::c::execute_cpp<haxorg_StdOptional>(static_cast<std::optional<org::imm::ImmAdapter>(org::imm::ImmAdapterDirectoryAPI::*)(hstd::Str const&, bool) const>(&org::imm::ImmAdapterDirectoryAPI::getFsSubnode), org_context, __this, name, withPath); }

void haxorg_destroy_ImmAdapterDirectoryAPI(OrgContext* org_context, haxorg_ImmAdapterDirectoryAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterDirectoryAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterSymlinkAPI(OrgContext* org_context, haxorg_ImmAdapterSymlinkAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSymlinkAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterDocumentFragmentAPI(OrgContext* org_context, haxorg_ImmAdapterDocumentFragmentAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterDocumentFragmentAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCriticMarkupAPI(OrgContext* org_context, haxorg_ImmAdapterCriticMarkupAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCriticMarkupAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterListItemAPI(OrgContext* org_context, haxorg_ImmAdapterListItemAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterListItemAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterDocumentOptionsAPI(OrgContext* org_context, haxorg_ImmAdapterDocumentOptionsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterDocumentOptionsAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterDocumentAPI(OrgContext* org_context, haxorg_ImmAdapterDocumentAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterDocumentAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterFileTargetAPI(OrgContext* org_context, haxorg_ImmAdapterFileTargetAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterFileTargetAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterTextSeparatorAPI(OrgContext* org_context, haxorg_ImmAdapterTextSeparatorAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterTextSeparatorAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdIncludeAPI(OrgContext* org_context, haxorg_ImmAdapterCmdIncludeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdIncludeAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterDocumentGroupAPI(OrgContext* org_context, haxorg_ImmAdapterDocumentGroupAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterDocumentGroupAPI>(org_context, obj); }

void haxorg_destroy_Block(OrgContext* org_context, haxorg_Block* obj) { org::bind::c::execute_destroy<org::sem::Block>(org_context, obj); }

void haxorg_destroy_LineCommand(OrgContext* org_context, haxorg_LineCommand* obj) { org::bind::c::execute_destroy<org::sem::LineCommand>(org_context, obj); }

haxorg_SemIdOfOrg haxorg_CmdCreator_get_text(OrgContext* org_context, haxorg_CmdCreator __this) { return org::bind::c::get_cpp_field<haxorg_SemIdOfOrg, org::sem::CmdCreator, org::sem::SemId<org::sem::Paragraph>, haxorg_CmdCreator>(org_context, __this, &org::sem::CmdCreator::text); }

void haxorg_destroy_CmdCreator(OrgContext* org_context, haxorg_CmdCreator* obj) { org::bind::c::execute_destroy<org::sem::CmdCreator>(org_context, obj); }

haxorg_SemIdOfOrg haxorg_CmdAuthor_get_text(OrgContext* org_context, haxorg_CmdAuthor __this) { return org::bind::c::get_cpp_field<haxorg_SemIdOfOrg, org::sem::CmdAuthor, org::sem::SemId<org::sem::Paragraph>, haxorg_CmdAuthor>(org_context, __this, &org::sem::CmdAuthor::text); }

void haxorg_destroy_CmdAuthor(OrgContext* org_context, haxorg_CmdAuthor* obj) { org::bind::c::execute_destroy<org::sem::CmdAuthor>(org_context, obj); }

haxorg_HstdStr haxorg_CmdEmail_get_text(OrgContext* org_context, haxorg_CmdEmail __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::CmdEmail, hstd::Str, haxorg_CmdEmail>(org_context, __this, &org::sem::CmdEmail::text); }

void haxorg_destroy_CmdEmail(OrgContext* org_context, haxorg_CmdEmail* obj) { org::bind::c::execute_destroy<org::sem::CmdEmail>(org_context, obj); }

haxorg_HstdStr haxorg_CmdLanguage_get_text(OrgContext* org_context, haxorg_CmdLanguage __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::CmdLanguage, hstd::Str, haxorg_CmdLanguage>(org_context, __this, &org::sem::CmdLanguage::text); }

void haxorg_destroy_CmdLanguage(OrgContext* org_context, haxorg_CmdLanguage* obj) { org::bind::c::execute_destroy<org::sem::CmdLanguage>(org_context, obj); }

haxorg_HstdStr haxorg_CmdCustomArgs_get_name(OrgContext* org_context, haxorg_CmdCustomArgs __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::CmdCustomArgs, hstd::Str, haxorg_CmdCustomArgs>(org_context, __this, &org::sem::CmdCustomArgs::name); }

bool haxorg_CmdCustomArgs_get_isAttached(OrgContext* org_context, haxorg_CmdCustomArgs __this) { return org::bind::c::get_cpp_field<bool, org::sem::CmdCustomArgs, bool, haxorg_CmdCustomArgs>(org_context, __this, &org::sem::CmdCustomArgs::isAttached); }

void haxorg_destroy_CmdCustomArgs(OrgContext* org_context, haxorg_CmdCustomArgs* obj) { org::bind::c::execute_destroy<org::sem::CmdCustomArgs>(org_context, obj); }

haxorg_Tblfm haxorg_CmdTblfm_get_expr(OrgContext* org_context, haxorg_CmdTblfm __this) { return org::bind::c::get_cpp_field<haxorg_Tblfm, org::sem::CmdTblfm, org::sem::Tblfm, haxorg_CmdTblfm>(org_context, __this, &org::sem::CmdTblfm::expr); }

void haxorg_destroy_CmdTblfm(OrgContext* org_context, haxorg_CmdTblfm* obj) { org::bind::c::execute_destroy<org::sem::CmdTblfm>(org_context, obj); }

bool haxorg_Cell_get_isBlock(OrgContext* org_context, haxorg_Cell __this) { return org::bind::c::get_cpp_field<bool, org::sem::Cell, bool, haxorg_Cell>(org_context, __this, &org::sem::Cell::isBlock); }

void haxorg_destroy_Cell(OrgContext* org_context, haxorg_Cell* obj) { org::bind::c::execute_destroy<org::sem::Cell>(org_context, obj); }

haxorg_HstdVecOfSemIdOfCell haxorg_Row_get_cells(OrgContext* org_context, haxorg_Row __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSemIdOfCell, org::sem::Row, hstd::Vec<org::sem::SemId<org::sem::Cell>>, haxorg_Row>(org_context, __this, &org::sem::Row::cells); }

bool haxorg_Row_get_isBlock(OrgContext* org_context, haxorg_Row __this) { return org::bind::c::get_cpp_field<bool, org::sem::Row, bool, haxorg_Row>(org_context, __this, &org::sem::Row::isBlock); }

void haxorg_destroy_Row(OrgContext* org_context, haxorg_Row* obj) { org::bind::c::execute_destroy<org::sem::Row>(org_context, obj); }

bool haxorg_ImmBlock___eq___const(OrgContext* org_context, haxorg_ImmBlock __this, haxorg_ImmBlock other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmBlock::*)(org::imm::ImmBlock const&) const>(&org::imm::ImmBlock::operator==), org_context, __this, other); }

void haxorg_destroy_ImmBlock(OrgContext* org_context, haxorg_ImmBlock* obj) { org::bind::c::execute_destroy<org::imm::ImmBlock>(org_context, obj); }

bool haxorg_ImmLineCommand___eq___const(OrgContext* org_context, haxorg_ImmLineCommand __this, haxorg_ImmLineCommand other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmLineCommand::*)(org::imm::ImmLineCommand const&) const>(&org::imm::ImmLineCommand::operator==), org_context, __this, other); }

void haxorg_destroy_ImmLineCommand(OrgContext* org_context, haxorg_ImmLineCommand* obj) { org::bind::c::execute_destroy<org::imm::ImmLineCommand>(org_context, obj); }

haxorg_ImmId haxorg_ImmCmdCreator_get_text(OrgContext* org_context, haxorg_ImmCmdCreator __this) { return org::bind::c::get_cpp_field<haxorg_ImmId, org::imm::ImmCmdCreator, org::imm::ImmIdT<org::imm::ImmParagraph>, haxorg_ImmCmdCreator>(org_context, __this, &org::imm::ImmCmdCreator::text); }

bool haxorg_ImmCmdCreator___eq___const(OrgContext* org_context, haxorg_ImmCmdCreator __this, haxorg_ImmCmdCreator other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdCreator::*)(org::imm::ImmCmdCreator const&) const>(&org::imm::ImmCmdCreator::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdCreator(OrgContext* org_context, haxorg_ImmCmdCreator* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCreator>(org_context, obj); }

haxorg_ImmId haxorg_ImmCmdAuthor_get_text(OrgContext* org_context, haxorg_ImmCmdAuthor __this) { return org::bind::c::get_cpp_field<haxorg_ImmId, org::imm::ImmCmdAuthor, org::imm::ImmIdT<org::imm::ImmParagraph>, haxorg_ImmCmdAuthor>(org_context, __this, &org::imm::ImmCmdAuthor::text); }

bool haxorg_ImmCmdAuthor___eq___const(OrgContext* org_context, haxorg_ImmCmdAuthor __this, haxorg_ImmCmdAuthor other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdAuthor::*)(org::imm::ImmCmdAuthor const&) const>(&org::imm::ImmCmdAuthor::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdAuthor(OrgContext* org_context, haxorg_ImmCmdAuthor* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdAuthor>(org_context, obj); }

haxorg_HstdStr haxorg_ImmCmdEmail_get_text(OrgContext* org_context, haxorg_ImmCmdEmail __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmCmdEmail, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmCmdEmail>(org_context, __this, &org::imm::ImmCmdEmail::text); }

bool haxorg_ImmCmdEmail___eq___const(OrgContext* org_context, haxorg_ImmCmdEmail __this, haxorg_ImmCmdEmail other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdEmail::*)(org::imm::ImmCmdEmail const&) const>(&org::imm::ImmCmdEmail::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdEmail(OrgContext* org_context, haxorg_ImmCmdEmail* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdEmail>(org_context, obj); }

haxorg_HstdStr haxorg_ImmCmdLanguage_get_text(OrgContext* org_context, haxorg_ImmCmdLanguage __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmCmdLanguage, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmCmdLanguage>(org_context, __this, &org::imm::ImmCmdLanguage::text); }

bool haxorg_ImmCmdLanguage___eq___const(OrgContext* org_context, haxorg_ImmCmdLanguage __this, haxorg_ImmCmdLanguage other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdLanguage::*)(org::imm::ImmCmdLanguage const&) const>(&org::imm::ImmCmdLanguage::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdLanguage(OrgContext* org_context, haxorg_ImmCmdLanguage* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdLanguage>(org_context, obj); }

haxorg_HstdStr haxorg_ImmCmdCustomArgs_get_name(OrgContext* org_context, haxorg_ImmCmdCustomArgs __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmCmdCustomArgs, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmCmdCustomArgs>(org_context, __this, &org::imm::ImmCmdCustomArgs::name); }

bool haxorg_ImmCmdCustomArgs_get_isAttached(OrgContext* org_context, haxorg_ImmCmdCustomArgs __this) { return org::bind::c::get_cpp_field<bool, org::imm::ImmCmdCustomArgs, bool, haxorg_ImmCmdCustomArgs>(org_context, __this, &org::imm::ImmCmdCustomArgs::isAttached); }

bool haxorg_ImmCmdCustomArgs___eq___const(OrgContext* org_context, haxorg_ImmCmdCustomArgs __this, haxorg_ImmCmdCustomArgs other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdCustomArgs::*)(org::imm::ImmCmdCustomArgs const&) const>(&org::imm::ImmCmdCustomArgs::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdCustomArgs(OrgContext* org_context, haxorg_ImmCmdCustomArgs* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCustomArgs>(org_context, obj); }

haxorg_Tblfm haxorg_ImmCmdTblfm_get_expr(OrgContext* org_context, haxorg_ImmCmdTblfm __this) { return org::bind::c::get_cpp_field<haxorg_Tblfm, org::imm::ImmCmdTblfm, org::sem::Tblfm, haxorg_ImmCmdTblfm>(org_context, __this, &org::imm::ImmCmdTblfm::expr); }

bool haxorg_ImmCmdTblfm___eq___const(OrgContext* org_context, haxorg_ImmCmdTblfm __this, haxorg_ImmCmdTblfm other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdTblfm::*)(org::imm::ImmCmdTblfm const&) const>(&org::imm::ImmCmdTblfm::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdTblfm(OrgContext* org_context, haxorg_ImmCmdTblfm* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdTblfm>(org_context, obj); }

bool haxorg_ImmCell_get_isBlock(OrgContext* org_context, haxorg_ImmCell __this) { return org::bind::c::get_cpp_field<bool, org::imm::ImmCell, bool, haxorg_ImmCell>(org_context, __this, &org::imm::ImmCell::isBlock); }

bool haxorg_ImmCell___eq___const(OrgContext* org_context, haxorg_ImmCell __this, haxorg_ImmCell other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCell::*)(org::imm::ImmCell const&) const>(&org::imm::ImmCell::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCell(OrgContext* org_context, haxorg_ImmCell* obj) { org::bind::c::execute_destroy<org::imm::ImmCell>(org_context, obj); }

haxorg_ImmVec haxorg_ImmRow_get_cells(OrgContext* org_context, haxorg_ImmRow __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmRow, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell>>, haxorg_ImmRow>(org_context, __this, &org::imm::ImmRow::cells); }

bool haxorg_ImmRow_get_isBlock(OrgContext* org_context, haxorg_ImmRow __this) { return org::bind::c::get_cpp_field<bool, org::imm::ImmRow, bool, haxorg_ImmRow>(org_context, __this, &org::imm::ImmRow::isBlock); }

bool haxorg_ImmRow___eq___const(OrgContext* org_context, haxorg_ImmRow __this, haxorg_ImmRow other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmRow::*)(org::imm::ImmRow const&) const>(&org::imm::ImmRow::operator==), org_context, __this, other); }

void haxorg_destroy_ImmRow(OrgContext* org_context, haxorg_ImmRow* obj) { org::bind::c::execute_destroy<org::imm::ImmRow>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdAPI(OrgContext* org_context, haxorg_ImmAdapterCmdAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdCustomRawAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCustomRawAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCustomRawAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdCustomTextAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCustomTextAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCustomTextAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterLinkAPI(OrgContext* org_context, haxorg_ImmAdapterLinkAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterLinkAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockCommentAPI(OrgContext* org_context, haxorg_ImmAdapterBlockCommentAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockCommentAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterParagraphAPI(OrgContext* org_context, haxorg_ImmAdapterParagraphAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterParagraphAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterListAPI(OrgContext* org_context, haxorg_ImmAdapterListAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterListAPI>(org_context, obj); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmStmt_getAttached_const(OrgContext* org_context, haxorg_ImmStmtAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>>(org::imm::ImmAdapterT<org::imm::ImmStmt>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmStmt>::getAttached), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmStmt_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmStmt> { return org::imm::ImmAdapterT<org::imm::ImmStmt>(other); }, org_context, other); }

void haxorg_destroy_ImmStmtAdapter(OrgContext* org_context, haxorg_ImmStmtAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmStmt>>(org_context, obj); }

int haxorg_ImmAdapterTOfImmSubtree_getLevel_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this) { return org::bind::c::execute_cpp<int>(static_cast<int(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getLevel), org_context, __this); }

haxorg_OptOfStr haxorg_ImmAdapterTOfImmSubtree_getTreeId_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTreeId), org_context, __this); }

haxorg_OptOfStr haxorg_ImmAdapterTOfImmSubtree_getTodo_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTodo), org_context, __this); }

haxorg_OptOfSubtreeCompletion haxorg_ImmAdapterTOfImmSubtree_getCompletion_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfSubtreeCompletion>(static_cast<hstd::Opt<org::sem::SubtreeCompletion> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getCompletion), org_context, __this); }

haxorg_OptOfImmAdapterTOfImmParagraph haxorg_ImmAdapterTOfImmSubtree_getDescription_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfImmAdapterTOfImmParagraph>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getDescription), org_context, __this); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmSubtree_getTags_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTags), org_context, __this); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmSubtree_getTitle_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTitle), org_context, __this); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmSubtree_getLogbook_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getLogbook), org_context, __this); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmSubtree_getProperties_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::sem::NamedProperty>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getProperties), org_context, __this); }

haxorg_OptOfImmAdapterTOfImmTime haxorg_ImmAdapterTOfImmSubtree_getClosed_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfImmAdapterTOfImmTime>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getClosed), org_context, __this); }

haxorg_OptOfImmAdapterTOfImmTime haxorg_ImmAdapterTOfImmSubtree_getDeadline_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfImmAdapterTOfImmTime>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getDeadline), org_context, __this); }

haxorg_OptOfImmAdapterTOfImmTime haxorg_ImmAdapterTOfImmSubtree_getScheduled_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfImmAdapterTOfImmTime>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getScheduled), org_context, __this); }

bool haxorg_ImmAdapterTOfImmSubtree_getIsComment_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getIsComment), org_context, __this); }

bool haxorg_ImmAdapterTOfImmSubtree_getIsArchived_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getIsArchived), org_context, __this); }

haxorg_OptOfStr haxorg_ImmAdapterTOfImmSubtree_getPriority_const(OrgContext* org_context, haxorg_ImmSubtreeAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getPriority), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmSubtree_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmSubtree> { return org::imm::ImmAdapterT<org::imm::ImmSubtree>(other); }, org_context, other); }

void haxorg_destroy_ImmSubtreeAdapter(OrgContext* org_context, haxorg_ImmSubtreeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmSubtree>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmNoNode_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmNoNode> { return org::imm::ImmAdapterT<org::imm::ImmNoNode>(other); }, org_context, other); }

void haxorg_destroy_ImmNoNodeAdapter(OrgContext* org_context, haxorg_ImmNoNodeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmNoNode>>(org_context, obj); }

haxorg_OrgDiagnostics haxorg_ImmAdapterTOfImmErrorItem_getDiag_const(OrgContext* org_context, haxorg_ImmErrorItemAdapter __this) { return org::bind::c::execute_cpp<haxorg_OrgDiagnostics>(static_cast<org::sem::OrgDiagnostics(org::imm::ImmAdapterT<org::imm::ImmErrorItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorItem>::getDiag), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmErrorItem_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmErrorItem> { return org::imm::ImmAdapterT<org::imm::ImmErrorItem>(other); }, org_context, other); }

void haxorg_destroy_ImmErrorItemAdapter(OrgContext* org_context, haxorg_ImmErrorItemAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmErrorItem>>(org_context, obj); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmErrorGroup_getDiagnostics_const(OrgContext* org_context, haxorg_ImmErrorGroupAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem>>(org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::getDiagnostics), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmErrorGroup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmErrorGroup> { return org::imm::ImmAdapterT<org::imm::ImmErrorGroup>(other); }, org_context, other); }

void haxorg_destroy_ImmErrorGroupAdapter(OrgContext* org_context, haxorg_ImmErrorGroupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmErrorGroup>>(org_context, obj); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmErrorSkipGroup_getSkipped_const(OrgContext* org_context, haxorg_ImmErrorSkipGroupAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorSkipToken>>(org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>::getSkipped), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmErrorSkipGroup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup> { return org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>(other); }, org_context, other); }

void haxorg_destroy_ImmErrorSkipGroupAdapter(OrgContext* org_context, haxorg_ImmErrorSkipGroupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmErrorSkipToken_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken> { return org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken>(other); }, org_context, other); }

void haxorg_destroy_ImmErrorSkipTokenAdapter(OrgContext* org_context, haxorg_ImmErrorSkipTokenAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmStmtList_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmStmtList> { return org::imm::ImmAdapterT<org::imm::ImmStmtList>(other); }, org_context, other); }

void haxorg_destroy_ImmStmtListAdapter(OrgContext* org_context, haxorg_ImmStmtListAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmStmtList>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmEmpty_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmEmpty> { return org::imm::ImmAdapterT<org::imm::ImmEmpty>(other); }, org_context, other); }

void haxorg_destroy_ImmEmptyAdapter(OrgContext* org_context, haxorg_ImmEmptyAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmEmpty>>(org_context, obj); }

void haxorg_destroy_ImmAdapterHashTagAPI(OrgContext* org_context, haxorg_ImmAdapterHashTagAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterHashTagAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterInlineFootnoteAPI(OrgContext* org_context, haxorg_ImmAdapterInlineFootnoteAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterInlineFootnoteAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterSubtreeCompletionAPI(OrgContext* org_context, haxorg_ImmAdapterSubtreeCompletionAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSubtreeCompletionAPI>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmInline_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmInline> { return org::imm::ImmAdapterT<org::imm::ImmInline>(other); }, org_context, other); }

void haxorg_destroy_ImmInlineAdapter(OrgContext* org_context, haxorg_ImmInlineAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmInline>>(org_context, obj); }

bool haxorg_ImmAdapterTOfImmTime_getIsActive_const(OrgContext* org_context, haxorg_ImmTimeAdapter __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmTime>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTime>::getIsActive), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmTime_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmTime> { return org::imm::ImmAdapterT<org::imm::ImmTime>(other); }, org_context, other); }

void haxorg_destroy_ImmTimeAdapter(OrgContext* org_context, haxorg_ImmTimeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmTime>>(org_context, obj); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmTimeRange_getFrom_const(OrgContext* org_context, haxorg_ImmTimeRangeAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmTimeRange>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTimeRange>::getFrom), org_context, __this); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmTimeRange_getTo_const(OrgContext* org_context, haxorg_ImmTimeRangeAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmTimeRange>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTimeRange>::getTo), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmTimeRange_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmTimeRange> { return org::imm::ImmAdapterT<org::imm::ImmTimeRange>(other); }, org_context, other); }

void haxorg_destroy_ImmTimeRangeAdapter(OrgContext* org_context, haxorg_ImmTimeRangeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmTimeRange>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmMacro_getName_const(OrgContext* org_context, haxorg_ImmMacroAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmMacro>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMacro>::getName), org_context, __this); }

haxorg_AttrGroup haxorg_ImmAdapterTOfImmMacro_getAttrs_const(OrgContext* org_context, haxorg_ImmMacroAdapter __this) { return org::bind::c::execute_cpp<haxorg_AttrGroup>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmMacro>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMacro>::getAttrs), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmMacro_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmMacro> { return org::imm::ImmAdapterT<org::imm::ImmMacro>(other); }, org_context, other); }

void haxorg_destroy_ImmMacroAdapter(OrgContext* org_context, haxorg_ImmMacroAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmMacro>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmSymbol_getName_const(OrgContext* org_context, haxorg_ImmSymbolAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getName), org_context, __this); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmSymbol_getParameters_const(OrgContext* org_context, haxorg_ImmSymbolAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::imm::ImmSymbol::Param>(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getParameters), org_context, __this); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmSymbol_getPositional_const(OrgContext* org_context, haxorg_ImmSymbolAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>>(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getPositional), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmSymbol_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmSymbol> { return org::imm::ImmAdapterT<org::imm::ImmSymbol>(other); }, org_context, other); }

void haxorg_destroy_ImmSymbolAdapter(OrgContext* org_context, haxorg_ImmSymbolAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmSymbol>>(org_context, obj); }

void haxorg_destroy_ImmAdapterEscapedAPI(OrgContext* org_context, haxorg_ImmAdapterEscapedAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterEscapedAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterNewlineAPI(OrgContext* org_context, haxorg_ImmAdapterNewlineAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterNewlineAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterSpaceAPI(OrgContext* org_context, haxorg_ImmAdapterSpaceAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterSpaceAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterWordAPI(OrgContext* org_context, haxorg_ImmAdapterWordAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterWordAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterAtMentionAPI(OrgContext* org_context, haxorg_ImmAdapterAtMentionAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterAtMentionAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterRawTextAPI(OrgContext* org_context, haxorg_ImmAdapterRawTextAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterRawTextAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterPunctuationAPI(OrgContext* org_context, haxorg_ImmAdapterPunctuationAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterPunctuationAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterPlaceholderAPI(OrgContext* org_context, haxorg_ImmAdapterPlaceholderAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterPlaceholderAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBigIdentAPI(OrgContext* org_context, haxorg_ImmAdapterBigIdentAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBigIdentAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterTextTargetAPI(OrgContext* org_context, haxorg_ImmAdapterTextTargetAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterTextTargetAPI>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmLeaf_getText_const(OrgContext* org_context, haxorg_ImmLeafAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmLeaf>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLeaf>::getText), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmLeaf_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmLeaf> { return org::imm::ImmAdapterT<org::imm::ImmLeaf>(other); }, org_context, other); }

void haxorg_destroy_ImmLeafAdapter(OrgContext* org_context, haxorg_ImmLeafAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmLeaf>>(org_context, obj); }

void haxorg_destroy_ImmAdapterBoldAPI(OrgContext* org_context, haxorg_ImmAdapterBoldAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBoldAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterUnderlineAPI(OrgContext* org_context, haxorg_ImmAdapterUnderlineAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterUnderlineAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterMonospaceAPI(OrgContext* org_context, haxorg_ImmAdapterMonospaceAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterMonospaceAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterMarkQuoteAPI(OrgContext* org_context, haxorg_ImmAdapterMarkQuoteAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterMarkQuoteAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterRadioTargetAPI(OrgContext* org_context, haxorg_ImmAdapterRadioTargetAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterRadioTargetAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterVerbatimAPI(OrgContext* org_context, haxorg_ImmAdapterVerbatimAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterVerbatimAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterItalicAPI(OrgContext* org_context, haxorg_ImmAdapterItalicAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterItalicAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterStrikeAPI(OrgContext* org_context, haxorg_ImmAdapterStrikeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterStrikeAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterParAPI(OrgContext* org_context, haxorg_ImmAdapterParAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterParAPI>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmMarkup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmMarkup> { return org::imm::ImmAdapterT<org::imm::ImmMarkup>(other); }, org_context, other); }

void haxorg_destroy_ImmMarkupAdapter(OrgContext* org_context, haxorg_ImmMarkupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmMarkup>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmLatex_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmLatex> { return org::imm::ImmAdapterT<org::imm::ImmLatex>(other); }, org_context, other); }

void haxorg_destroy_ImmLatexAdapter(OrgContext* org_context, haxorg_ImmLatexAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmLatex>>(org_context, obj); }

haxorg_SubtreeLogHead haxorg_ImmAdapterTOfImmSubtreeLog_getHead_const(OrgContext* org_context, haxorg_ImmSubtreeLogAdapter __this) { return org::bind::c::execute_cpp<haxorg_SubtreeLogHead>(static_cast<org::sem::SubtreeLogHead(org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::getHead), org_context, __this); }

haxorg_OptOfImmAdapterTOfImmStmtList haxorg_ImmAdapterTOfImmSubtreeLog_getDesc_const(OrgContext* org_context, haxorg_ImmSubtreeLogAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfImmAdapterTOfImmStmtList>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmStmtList>>(org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::getDesc), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmSubtreeLog_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmSubtreeLog> { return org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>(other); }, org_context, other); }

void haxorg_destroy_ImmSubtreeLogAdapter(OrgContext* org_context, haxorg_ImmSubtreeLogAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmColonExample_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmColonExample> { return org::imm::ImmAdapterT<org::imm::ImmColonExample>(other); }, org_context, other); }

void haxorg_destroy_ImmColonExampleAdapter(OrgContext* org_context, haxorg_ImmColonExampleAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmColonExample>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCall_getName_const(OrgContext* org_context, haxorg_ImmCallAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getName), org_context, __this); }

haxorg_AttrGroup haxorg_ImmAdapterTOfImmCall_getAttrs_const(OrgContext* org_context, haxorg_ImmCallAdapter __this) { return org::bind::c::execute_cpp<haxorg_AttrGroup>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getAttrs), org_context, __this); }

bool haxorg_ImmAdapterTOfImmCall_getIsCommand_const(OrgContext* org_context, haxorg_ImmCallAdapter __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getIsCommand), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCall_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCall> { return org::imm::ImmAdapterT<org::imm::ImmCall>(other); }, org_context, other); }

void haxorg_destroy_ImmCallAdapter(OrgContext* org_context, haxorg_ImmCallAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCall>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmFile_getRelPath_const(OrgContext* org_context, haxorg_ImmFileAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmFile>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFile>::getRelPath), org_context, __this); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmFile_getAbsPath_const(OrgContext* org_context, haxorg_ImmFileAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmFile>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFile>::getAbsPath), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmFile_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmFile> { return org::imm::ImmAdapterT<org::imm::ImmFile>(other); }, org_context, other); }

void haxorg_destroy_ImmFileAdapter(OrgContext* org_context, haxorg_ImmFileAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmFile>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmDirectory_getRelPath_const(OrgContext* org_context, haxorg_ImmDirectoryAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmDirectory>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDirectory>::getRelPath), org_context, __this); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmDirectory_getAbsPath_const(OrgContext* org_context, haxorg_ImmDirectoryAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmDirectory>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDirectory>::getAbsPath), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmDirectory_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmDirectory> { return org::imm::ImmAdapterT<org::imm::ImmDirectory>(other); }, org_context, other); }

void haxorg_destroy_ImmDirectoryAdapter(OrgContext* org_context, haxorg_ImmDirectoryAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmDirectory>>(org_context, obj); }

bool haxorg_ImmAdapterTOfImmSymlink_getIsDirectory_const(OrgContext* org_context, haxorg_ImmSymlinkAdapter __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmSymlink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymlink>::getIsDirectory), org_context, __this); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmSymlink_getAbsPath_const(OrgContext* org_context, haxorg_ImmSymlinkAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmSymlink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymlink>::getAbsPath), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmSymlink_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmSymlink> { return org::imm::ImmAdapterT<org::imm::ImmSymlink>(other); }, org_context, other); }

void haxorg_destroy_ImmSymlinkAdapter(OrgContext* org_context, haxorg_ImmSymlinkAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmSymlink>>(org_context, obj); }

int haxorg_ImmAdapterTOfImmDocumentFragment_getBaseLine_const(OrgContext* org_context, haxorg_ImmDocumentFragmentAdapter __this) { return org::bind::c::execute_cpp<int>(static_cast<int(org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::getBaseLine), org_context, __this); }

int haxorg_ImmAdapterTOfImmDocumentFragment_getBaseCol_const(OrgContext* org_context, haxorg_ImmDocumentFragmentAdapter __this) { return org::bind::c::execute_cpp<int>(static_cast<int(org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::getBaseCol), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmDocumentFragment_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmDocumentFragment> { return org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>(other); }, org_context, other); }

void haxorg_destroy_ImmDocumentFragmentAdapter(OrgContext* org_context, haxorg_ImmDocumentFragmentAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>>(org_context, obj); }

haxorg_ImmCriticMarkupKind haxorg_ImmAdapterTOfImmCriticMarkup_getKind_const(OrgContext* org_context, haxorg_ImmCriticMarkupAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmCriticMarkupKind>(static_cast<org::imm::ImmCriticMarkup::Kind(org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::getKind), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCriticMarkup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCriticMarkup> { return org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>(other); }, org_context, other); }

void haxorg_destroy_ImmCriticMarkupAdapter(OrgContext* org_context, haxorg_ImmCriticMarkupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>>(org_context, obj); }

haxorg_CheckboxState haxorg_ImmAdapterTOfImmListItem_getCheckbox_const(OrgContext* org_context, haxorg_ImmListItemAdapter __this) { return org::bind::c::execute_cpp<haxorg_CheckboxState>(static_cast<CheckboxState(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getCheckbox), org_context, __this); }

haxorg_OptOfImmAdapterTOfImmParagraph haxorg_ImmAdapterTOfImmListItem_getHeader_const(OrgContext* org_context, haxorg_ImmListItemAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfImmAdapterTOfImmParagraph>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getHeader), org_context, __this); }

haxorg_OptOfStr haxorg_ImmAdapterTOfImmListItem_getBullet_const(OrgContext* org_context, haxorg_ImmListItemAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getBullet), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmListItem_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmListItem> { return org::imm::ImmAdapterT<org::imm::ImmListItem>(other); }, org_context, other); }

void haxorg_destroy_ImmListItemAdapter(OrgContext* org_context, haxorg_ImmListItemAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmListItem>>(org_context, obj); }

haxorg_InitialSubtreeVisibility haxorg_ImmAdapterTOfImmDocumentOptions_getInitialVisibility_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this) { return org::bind::c::execute_cpp<haxorg_InitialSubtreeVisibility>(static_cast<InitialSubtreeVisibility(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getInitialVisibility), org_context, __this); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmDocumentOptions_getProperties_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::sem::NamedProperty>(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getProperties), org_context, __this); }

haxorg_DocumentExportConfig haxorg_ImmAdapterTOfImmDocumentOptions_getExportConfig_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this) { return org::bind::c::execute_cpp<haxorg_DocumentExportConfig>(static_cast<org::sem::DocumentExportConfig(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getExportConfig), org_context, __this); }

haxorg_OptOfBool haxorg_ImmAdapterTOfImmDocumentOptions_getFixedWidthSections_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfBool>(static_cast<hstd::Opt<bool> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getFixedWidthSections), org_context, __this); }

haxorg_OptOfBool haxorg_ImmAdapterTOfImmDocumentOptions_getStartupIndented_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfBool>(static_cast<hstd::Opt<bool> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getStartupIndented), org_context, __this); }

haxorg_OptOfStr haxorg_ImmAdapterTOfImmDocumentOptions_getCategory_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getCategory), org_context, __this); }

haxorg_OptOfStr haxorg_ImmAdapterTOfImmDocumentOptions_getSetupfile_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getSetupfile), org_context, __this); }

haxorg_OptOfInt haxorg_ImmAdapterTOfImmDocumentOptions_getMaxSubtreeLevelExport_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfInt>(static_cast<hstd::Opt<int> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getMaxSubtreeLevelExport), org_context, __this); }

haxorg_OptOfColumnView haxorg_ImmAdapterTOfImmDocumentOptions_getColumns_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfColumnView>(static_cast<hstd::Opt<org::sem::ColumnView> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getColumns), org_context, __this); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmDocumentOptions_getTodoKeywords_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::sem::TodoKeyword>(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getTodoKeywords), org_context, __this); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmDocumentOptions_getDoneKeywords_const(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::sem::TodoKeyword>(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getDoneKeywords), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmDocumentOptions_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmDocumentOptions> { return org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>(other); }, org_context, other); }

void haxorg_destroy_ImmDocumentOptionsAdapter(OrgContext* org_context, haxorg_ImmDocumentOptionsAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>>(org_context, obj); }

haxorg_OptOfImmAdapterTOfImmParagraph haxorg_ImmAdapterTOfImmDocument_getTitle_const(OrgContext* org_context, haxorg_ImmDocumentAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfImmAdapterTOfImmParagraph>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getTitle), org_context, __this); }

haxorg_OptOfImmAdapterTOfImmParagraph haxorg_ImmAdapterTOfImmDocument_getAuthor_const(OrgContext* org_context, haxorg_ImmDocumentAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfImmAdapterTOfImmParagraph>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getAuthor), org_context, __this); }

haxorg_OptOfImmAdapterTOfImmParagraph haxorg_ImmAdapterTOfImmDocument_getCreator_const(OrgContext* org_context, haxorg_ImmDocumentAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfImmAdapterTOfImmParagraph>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getCreator), org_context, __this); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmDocument_getFiletags_const(OrgContext* org_context, haxorg_ImmDocumentAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getFiletags), org_context, __this); }

haxorg_OptOfImmAdapterTOfImmRawText haxorg_ImmAdapterTOfImmDocument_getEmail_const(OrgContext* org_context, haxorg_ImmDocumentAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfImmAdapterTOfImmRawText>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmRawText>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getEmail), org_context, __this); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmDocument_getLanguage_const(OrgContext* org_context, haxorg_ImmDocumentAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<hstd::Str>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getLanguage), org_context, __this); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmDocument_getOptions_const(OrgContext* org_context, haxorg_ImmDocumentAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getOptions), org_context, __this); }

haxorg_OptOfStr haxorg_ImmAdapterTOfImmDocument_getExportFileName_const(OrgContext* org_context, haxorg_ImmDocumentAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getExportFileName), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmDocument_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmDocument> { return org::imm::ImmAdapterT<org::imm::ImmDocument>(other); }, org_context, other); }

void haxorg_destroy_ImmDocumentAdapter(OrgContext* org_context, haxorg_ImmDocumentAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmDocument>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmFileTarget_getPath_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getPath), org_context, __this); }

haxorg_OptOfInt haxorg_ImmAdapterTOfImmFileTarget_getLine_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfInt>(static_cast<hstd::Opt<int> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getLine), org_context, __this); }

haxorg_OptOfStr haxorg_ImmAdapterTOfImmFileTarget_getSearchTarget_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getSearchTarget), org_context, __this); }

bool haxorg_ImmAdapterTOfImmFileTarget_getRestrictToHeadlines_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getRestrictToHeadlines), org_context, __this); }

haxorg_OptOfStr haxorg_ImmAdapterTOfImmFileTarget_getTargetId_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getTargetId), org_context, __this); }

haxorg_OptOfStr haxorg_ImmAdapterTOfImmFileTarget_getRegexp_const(OrgContext* org_context, haxorg_ImmFileTargetAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getRegexp), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmFileTarget_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmFileTarget> { return org::imm::ImmAdapterT<org::imm::ImmFileTarget>(other); }, org_context, other); }

void haxorg_destroy_ImmFileTargetAdapter(OrgContext* org_context, haxorg_ImmFileTargetAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmFileTarget>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmTextSeparator_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmTextSeparator> { return org::imm::ImmAdapterT<org::imm::ImmTextSeparator>(other); }, org_context, other); }

void haxorg_destroy_ImmTextSeparatorAdapter(OrgContext* org_context, haxorg_ImmTextSeparatorAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmTextSeparator>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdInclude_getPath_const(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getPath), org_context, __this); }

haxorg_OptOfInt haxorg_ImmAdapterTOfImmCmdInclude_getFirstLine_const(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfInt>(static_cast<hstd::Opt<int> const&(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getFirstLine), org_context, __this); }

haxorg_OptOfInt haxorg_ImmAdapterTOfImmCmdInclude_getLastLine_const(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfInt>(static_cast<hstd::Opt<int> const&(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getLastLine), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCmdInclude_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdInclude> { return org::imm::ImmAdapterT<org::imm::ImmCmdInclude>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdIncludeAdapter(OrgContext* org_context, haxorg_ImmCmdIncludeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdInclude>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmDocumentGroup_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmDocumentGroup> { return org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>(other); }, org_context, other); }

void haxorg_destroy_ImmDocumentGroupAdapter(OrgContext* org_context, haxorg_ImmDocumentGroupAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>>(org_context, obj); }

void haxorg_destroy_BlockCenter(OrgContext* org_context, haxorg_BlockCenter* obj) { org::bind::c::execute_destroy<org::sem::BlockCenter>(org_context, obj); }

void haxorg_destroy_BlockQuote(OrgContext* org_context, haxorg_BlockQuote* obj) { org::bind::c::execute_destroy<org::sem::BlockQuote>(org_context, obj); }

void haxorg_destroy_BlockVerse(OrgContext* org_context, haxorg_BlockVerse* obj) { org::bind::c::execute_destroy<org::sem::BlockVerse>(org_context, obj); }

haxorg_HstdStr haxorg_BlockDynamicFallback_get_name(OrgContext* org_context, haxorg_BlockDynamicFallback __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::BlockDynamicFallback, hstd::Str, haxorg_BlockDynamicFallback>(org_context, __this, &org::sem::BlockDynamicFallback::name); }

void haxorg_destroy_BlockDynamicFallback(OrgContext* org_context, haxorg_BlockDynamicFallback* obj) { org::bind::c::execute_destroy<org::sem::BlockDynamicFallback>(org_context, obj); }

void haxorg_destroy_BlockExample(OrgContext* org_context, haxorg_BlockExample* obj) { org::bind::c::execute_destroy<org::sem::BlockExample>(org_context, obj); }

haxorg_HstdStr haxorg_BlockExport_get_exporter(OrgContext* org_context, haxorg_BlockExport __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::BlockExport, hstd::Str, haxorg_BlockExport>(org_context, __this, &org::sem::BlockExport::exporter); }

haxorg_HstdStr haxorg_BlockExport_get_content(OrgContext* org_context, haxorg_BlockExport __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::BlockExport, hstd::Str, haxorg_BlockExport>(org_context, __this, &org::sem::BlockExport::content); }

haxorg_OptOfStr haxorg_BlockExport_getPlacement_const(OrgContext* org_context, haxorg_BlockExport __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str>(org::sem::BlockExport::*)() const>(&org::sem::BlockExport::getPlacement), org_context, __this); }

void haxorg_destroy_BlockExport(OrgContext* org_context, haxorg_BlockExport* obj) { org::bind::c::execute_destroy<org::sem::BlockExport>(org_context, obj); }

void haxorg_destroy_BlockAdmonition(OrgContext* org_context, haxorg_BlockAdmonition* obj) { org::bind::c::execute_destroy<org::sem::BlockAdmonition>(org_context, obj); }

haxorg_HstdVecOfOrgCodeEvalOutput haxorg_BlockCodeEvalResult_get_raw(OrgContext* org_context, haxorg_BlockCodeEvalResult __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfOrgCodeEvalOutput, org::sem::BlockCodeEvalResult, hstd::Vec<org::sem::OrgCodeEvalOutput>, haxorg_BlockCodeEvalResult>(org_context, __this, &org::sem::BlockCodeEvalResult::raw); }

haxorg_SemIdOfOrg haxorg_BlockCodeEvalResult_get_node(OrgContext* org_context, haxorg_BlockCodeEvalResult __this) { return org::bind::c::get_cpp_field<haxorg_SemIdOfOrg, org::sem::BlockCodeEvalResult, org::sem::SemId<org::sem::Org>, haxorg_BlockCodeEvalResult>(org_context, __this, &org::sem::BlockCodeEvalResult::node); }

void haxorg_destroy_BlockCodeEvalResult(OrgContext* org_context, haxorg_BlockCodeEvalResult* obj) { org::bind::c::execute_destroy<org::sem::BlockCodeEvalResult>(org_context, obj); }

haxorg_OptOfStr haxorg_BlockCode_get_lang(OrgContext* org_context, haxorg_BlockCode __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::BlockCode, hstd::Opt<hstd::Str>, haxorg_BlockCode>(org_context, __this, &org::sem::BlockCode::lang); }

haxorg_HstdVecOfSemIdOfBlockCodeEvalResult haxorg_BlockCode_get_result(OrgContext* org_context, haxorg_BlockCode __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSemIdOfBlockCodeEvalResult, org::sem::BlockCode, hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>, haxorg_BlockCode>(org_context, __this, &org::sem::BlockCode::result); }

haxorg_HstdVecOfBlockCodeLine haxorg_BlockCode_get_lines(OrgContext* org_context, haxorg_BlockCode __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfBlockCodeLine, org::sem::BlockCode, hstd::Vec<org::sem::BlockCodeLine>, haxorg_BlockCode>(org_context, __this, &org::sem::BlockCode::lines); }

haxorg_AttrGroup haxorg_BlockCode_get_switches(OrgContext* org_context, haxorg_BlockCode __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::sem::BlockCode, org::sem::AttrGroup, haxorg_BlockCode>(org_context, __this, &org::sem::BlockCode::switches); }

haxorg_OptOfAttrValue haxorg_BlockCode_getVariable_const(OrgContext* org_context, haxorg_BlockCode __this, haxorg_HstdStr varname) { return org::bind::c::execute_cpp<haxorg_OptOfAttrValue>(static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockCode::*)(hstd::Str const&) const>(&org::sem::BlockCode::getVariable), org_context, __this, varname); }

void haxorg_destroy_BlockCode(OrgContext* org_context, haxorg_BlockCode* obj) { org::bind::c::execute_destroy<org::sem::BlockCode>(org_context, obj); }

haxorg_HstdVecOfSemIdOfRow haxorg_Table_get_rows(OrgContext* org_context, haxorg_Table __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSemIdOfRow, org::sem::Table, hstd::Vec<org::sem::SemId<org::sem::Row>>, haxorg_Table>(org_context, __this, &org::sem::Table::rows); }

bool haxorg_Table_get_isBlock(OrgContext* org_context, haxorg_Table __this) { return org::bind::c::get_cpp_field<bool, org::sem::Table, bool, haxorg_Table>(org_context, __this, &org::sem::Table::isBlock); }

void haxorg_destroy_Table(OrgContext* org_context, haxorg_Table* obj) { org::bind::c::execute_destroy<org::sem::Table>(org_context, obj); }

void haxorg_destroy_Attached(OrgContext* org_context, haxorg_Attached* obj) { org::bind::c::execute_destroy<org::sem::Attached>(org_context, obj); }

bool haxorg_ImmBlockCenter___eq___const(OrgContext* org_context, haxorg_ImmBlockCenter __this, haxorg_ImmBlockCenter other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmBlockCenter::*)(org::imm::ImmBlockCenter const&) const>(&org::imm::ImmBlockCenter::operator==), org_context, __this, other); }

void haxorg_destroy_ImmBlockCenter(OrgContext* org_context, haxorg_ImmBlockCenter* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockCenter>(org_context, obj); }

bool haxorg_ImmBlockQuote___eq___const(OrgContext* org_context, haxorg_ImmBlockQuote __this, haxorg_ImmBlockQuote other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmBlockQuote::*)(org::imm::ImmBlockQuote const&) const>(&org::imm::ImmBlockQuote::operator==), org_context, __this, other); }

void haxorg_destroy_ImmBlockQuote(OrgContext* org_context, haxorg_ImmBlockQuote* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockQuote>(org_context, obj); }

bool haxorg_ImmBlockVerse___eq___const(OrgContext* org_context, haxorg_ImmBlockVerse __this, haxorg_ImmBlockVerse other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmBlockVerse::*)(org::imm::ImmBlockVerse const&) const>(&org::imm::ImmBlockVerse::operator==), org_context, __this, other); }

void haxorg_destroy_ImmBlockVerse(OrgContext* org_context, haxorg_ImmBlockVerse* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockVerse>(org_context, obj); }

haxorg_HstdStr haxorg_ImmBlockDynamicFallback_get_name(OrgContext* org_context, haxorg_ImmBlockDynamicFallback __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmBlockDynamicFallback, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmBlockDynamicFallback>(org_context, __this, &org::imm::ImmBlockDynamicFallback::name); }

bool haxorg_ImmBlockDynamicFallback___eq___const(OrgContext* org_context, haxorg_ImmBlockDynamicFallback __this, haxorg_ImmBlockDynamicFallback other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmBlockDynamicFallback::*)(org::imm::ImmBlockDynamicFallback const&) const>(&org::imm::ImmBlockDynamicFallback::operator==), org_context, __this, other); }

void haxorg_destroy_ImmBlockDynamicFallback(OrgContext* org_context, haxorg_ImmBlockDynamicFallback* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockDynamicFallback>(org_context, obj); }

bool haxorg_ImmBlockExample___eq___const(OrgContext* org_context, haxorg_ImmBlockExample __this, haxorg_ImmBlockExample other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmBlockExample::*)(org::imm::ImmBlockExample const&) const>(&org::imm::ImmBlockExample::operator==), org_context, __this, other); }

void haxorg_destroy_ImmBlockExample(OrgContext* org_context, haxorg_ImmBlockExample* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockExample>(org_context, obj); }

haxorg_HstdStr haxorg_ImmBlockExport_get_exporter(OrgContext* org_context, haxorg_ImmBlockExport __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmBlockExport, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmBlockExport>(org_context, __this, &org::imm::ImmBlockExport::exporter); }

haxorg_HstdStr haxorg_ImmBlockExport_get_content(OrgContext* org_context, haxorg_ImmBlockExport __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmBlockExport, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmBlockExport>(org_context, __this, &org::imm::ImmBlockExport::content); }

bool haxorg_ImmBlockExport___eq___const(OrgContext* org_context, haxorg_ImmBlockExport __this, haxorg_ImmBlockExport other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmBlockExport::*)(org::imm::ImmBlockExport const&) const>(&org::imm::ImmBlockExport::operator==), org_context, __this, other); }

void haxorg_destroy_ImmBlockExport(OrgContext* org_context, haxorg_ImmBlockExport* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockExport>(org_context, obj); }

bool haxorg_ImmBlockAdmonition___eq___const(OrgContext* org_context, haxorg_ImmBlockAdmonition __this, haxorg_ImmBlockAdmonition other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmBlockAdmonition::*)(org::imm::ImmBlockAdmonition const&) const>(&org::imm::ImmBlockAdmonition::operator==), org_context, __this, other); }

void haxorg_destroy_ImmBlockAdmonition(OrgContext* org_context, haxorg_ImmBlockAdmonition* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockAdmonition>(org_context, obj); }

haxorg_ImmVec haxorg_ImmBlockCodeEvalResult_get_raw(OrgContext* org_context, haxorg_ImmBlockCodeEvalResult __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmBlockCodeEvalResult, hstd::ext::ImmVec<org::sem::OrgCodeEvalOutput>, haxorg_ImmBlockCodeEvalResult>(org_context, __this, &org::imm::ImmBlockCodeEvalResult::raw); }

haxorg_ImmId haxorg_ImmBlockCodeEvalResult_get_node(OrgContext* org_context, haxorg_ImmBlockCodeEvalResult __this) { return org::bind::c::get_cpp_field<haxorg_ImmId, org::imm::ImmBlockCodeEvalResult, org::imm::ImmIdT<org::imm::ImmOrg>, haxorg_ImmBlockCodeEvalResult>(org_context, __this, &org::imm::ImmBlockCodeEvalResult::node); }

bool haxorg_ImmBlockCodeEvalResult___eq___const(OrgContext* org_context, haxorg_ImmBlockCodeEvalResult __this, haxorg_ImmBlockCodeEvalResult other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmBlockCodeEvalResult::*)(org::imm::ImmBlockCodeEvalResult const&) const>(&org::imm::ImmBlockCodeEvalResult::operator==), org_context, __this, other); }

void haxorg_destroy_ImmBlockCodeEvalResult(OrgContext* org_context, haxorg_ImmBlockCodeEvalResult* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockCodeEvalResult>(org_context, obj); }

haxorg_OptOfStr haxorg_ImmBlockCode_get_lang(OrgContext* org_context, haxorg_ImmBlockCode __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::imm::ImmBlockCode, hstd::ext::ImmBox<hstd::Opt<hstd::Str>>, haxorg_ImmBlockCode>(org_context, __this, &org::imm::ImmBlockCode::lang); }

haxorg_ImmVec haxorg_ImmBlockCode_get_result(OrgContext* org_context, haxorg_ImmBlockCode __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmBlockCode, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>, haxorg_ImmBlockCode>(org_context, __this, &org::imm::ImmBlockCode::result); }

haxorg_ImmVec haxorg_ImmBlockCode_get_lines(OrgContext* org_context, haxorg_ImmBlockCode __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmBlockCode, hstd::ext::ImmVec<org::sem::BlockCodeLine>, haxorg_ImmBlockCode>(org_context, __this, &org::imm::ImmBlockCode::lines); }

haxorg_AttrGroup haxorg_ImmBlockCode_get_switches(OrgContext* org_context, haxorg_ImmBlockCode __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::imm::ImmBlockCode, org::sem::AttrGroup, haxorg_ImmBlockCode>(org_context, __this, &org::imm::ImmBlockCode::switches); }

bool haxorg_ImmBlockCode___eq___const(OrgContext* org_context, haxorg_ImmBlockCode __this, haxorg_ImmBlockCode other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmBlockCode::*)(org::imm::ImmBlockCode const&) const>(&org::imm::ImmBlockCode::operator==), org_context, __this, other); }

void haxorg_destroy_ImmBlockCode(OrgContext* org_context, haxorg_ImmBlockCode* obj) { org::bind::c::execute_destroy<org::imm::ImmBlockCode>(org_context, obj); }

haxorg_ImmVec haxorg_ImmTable_get_rows(OrgContext* org_context, haxorg_ImmTable __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmTable, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow>>, haxorg_ImmTable>(org_context, __this, &org::imm::ImmTable::rows); }

bool haxorg_ImmTable_get_isBlock(OrgContext* org_context, haxorg_ImmTable __this) { return org::bind::c::get_cpp_field<bool, org::imm::ImmTable, bool, haxorg_ImmTable>(org_context, __this, &org::imm::ImmTable::isBlock); }

bool haxorg_ImmTable___eq___const(OrgContext* org_context, haxorg_ImmTable __this, haxorg_ImmTable other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmTable::*)(org::imm::ImmTable const&) const>(&org::imm::ImmTable::operator==), org_context, __this, other); }

void haxorg_destroy_ImmTable(OrgContext* org_context, haxorg_ImmTable* obj) { org::bind::c::execute_destroy<org::imm::ImmTable>(org_context, obj); }

bool haxorg_ImmAttached___eq___const(OrgContext* org_context, haxorg_ImmAttached __this, haxorg_ImmAttached other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAttached::*)(org::imm::ImmAttached const&) const>(&org::imm::ImmAttached::operator==), org_context, __this, other); }

void haxorg_destroy_ImmAttached(OrgContext* org_context, haxorg_ImmAttached* obj) { org::bind::c::execute_destroy<org::imm::ImmAttached>(org_context, obj); }

void haxorg_destroy_ImmAdapterLineCommandAPI(OrgContext* org_context, haxorg_ImmAdapterLineCommandAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterLineCommandAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdCustomArgsAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCustomArgsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCustomArgsAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdCreatorAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCreatorAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCreatorAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdAuthorAPI(OrgContext* org_context, haxorg_ImmAdapterCmdAuthorAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdAuthorAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdEmailAPI(OrgContext* org_context, haxorg_ImmAdapterCmdEmailAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdEmailAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdLanguageAPI(OrgContext* org_context, haxorg_ImmAdapterCmdLanguageAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdLanguageAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdTblfmAPI(OrgContext* org_context, haxorg_ImmAdapterCmdTblfmAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdTblfmAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockAPI(OrgContext* org_context, haxorg_ImmAdapterBlockAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCellAPI(OrgContext* org_context, haxorg_ImmAdapterCellAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCellAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterRowAPI(OrgContext* org_context, haxorg_ImmAdapterRowAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterRowAPI>(org_context, obj); }

haxorg_AttrGroup haxorg_ImmAdapterTOfImmCmd_getAttrs_const(OrgContext* org_context, haxorg_ImmCmdAdapter __this) { return org::bind::c::execute_cpp<haxorg_AttrGroup>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmd>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmd>::getAttrs), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCmd_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmd> { return org::imm::ImmAdapterT<org::imm::ImmCmd>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdAdapter(OrgContext* org_context, haxorg_ImmCmdAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmd>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdCustomRaw_getName_const(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getName), org_context, __this); }

bool haxorg_ImmAdapterTOfImmCmdCustomRaw_getIsAttached_const(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getIsAttached), org_context, __this); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdCustomRaw_getText_const(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getText), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCmdCustomRaw_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw> { return org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCustomRawAdapter(OrgContext* org_context, haxorg_ImmCmdCustomRawAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdCustomText_getName_const(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getName), org_context, __this); }

bool haxorg_ImmAdapterTOfImmCmdCustomText_getIsAttached_const(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getIsAttached), org_context, __this); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmCmdCustomText_getText_const(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getText), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCmdCustomText_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCustomText> { return org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCustomTextAdapter(OrgContext* org_context, haxorg_ImmCmdCustomTextAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>>(org_context, obj); }

haxorg_OptOfImmAdapterTOfImmParagraph haxorg_ImmAdapterTOfImmLink_getDescription_const(OrgContext* org_context, haxorg_ImmLinkAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfImmAdapterTOfImmParagraph>(static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org::imm::ImmAdapterT<org::imm::ImmLink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLink>::getDescription), org_context, __this); }

haxorg_LinkTarget haxorg_ImmAdapterTOfImmLink_getTarget_const(OrgContext* org_context, haxorg_ImmLinkAdapter __this) { return org::bind::c::execute_cpp<haxorg_LinkTarget>(static_cast<org::sem::LinkTarget(org::imm::ImmAdapterT<org::imm::ImmLink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLink>::getTarget), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmLink_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmLink> { return org::imm::ImmAdapterT<org::imm::ImmLink>(other); }, org_context, other); }

void haxorg_destroy_ImmLinkAdapter(OrgContext* org_context, haxorg_ImmLinkAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmLink>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlockComment_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockComment> { return org::imm::ImmAdapterT<org::imm::ImmBlockComment>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockCommentAdapter(OrgContext* org_context, haxorg_ImmBlockCommentAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockComment>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmParagraph_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmParagraph> { return org::imm::ImmAdapterT<org::imm::ImmParagraph>(other); }, org_context, other); }

void haxorg_destroy_ImmParagraphAdapter(OrgContext* org_context, haxorg_ImmParagraphAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmParagraph>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmList_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmList> { return org::imm::ImmAdapterT<org::imm::ImmList>(other); }, org_context, other); }

void haxorg_destroy_ImmListAdapter(OrgContext* org_context, haxorg_ImmListAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmList>>(org_context, obj); }

haxorg_HashTagText haxorg_ImmAdapterTOfImmHashTag_getText_const(OrgContext* org_context, haxorg_ImmHashTagAdapter __this) { return org::bind::c::execute_cpp<haxorg_HashTagText>(static_cast<org::sem::HashTagText(org::imm::ImmAdapterT<org::imm::ImmHashTag>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmHashTag>::getText), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmHashTag_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmHashTag> { return org::imm::ImmAdapterT<org::imm::ImmHashTag>(other); }, org_context, other); }

void haxorg_destroy_ImmHashTagAdapter(OrgContext* org_context, haxorg_ImmHashTagAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmHashTag>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmInlineFootnote_getTag_const(OrgContext* org_context, haxorg_ImmInlineFootnoteAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::getTag), org_context, __this); }

haxorg_OptOfImmAdapter haxorg_ImmAdapterTOfImmInlineFootnote_getDefinition_const(OrgContext* org_context, haxorg_ImmInlineFootnoteAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfImmAdapter>(static_cast<hstd::Opt<org::imm::ImmAdapter>(org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::getDefinition), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmInlineFootnote_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmInlineFootnote> { return org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>(other); }, org_context, other); }

void haxorg_destroy_ImmInlineFootnoteAdapter(OrgContext* org_context, haxorg_ImmInlineFootnoteAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmEscaped_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmEscaped> { return org::imm::ImmAdapterT<org::imm::ImmEscaped>(other); }, org_context, other); }

void haxorg_destroy_ImmEscapedAdapter(OrgContext* org_context, haxorg_ImmEscapedAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmEscaped>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmNewline_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmNewline> { return org::imm::ImmAdapterT<org::imm::ImmNewline>(other); }, org_context, other); }

void haxorg_destroy_ImmNewlineAdapter(OrgContext* org_context, haxorg_ImmNewlineAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmNewline>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmSpace_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmSpace> { return org::imm::ImmAdapterT<org::imm::ImmSpace>(other); }, org_context, other); }

void haxorg_destroy_ImmSpaceAdapter(OrgContext* org_context, haxorg_ImmSpaceAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmSpace>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmWord_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmWord> { return org::imm::ImmAdapterT<org::imm::ImmWord>(other); }, org_context, other); }

void haxorg_destroy_ImmWordAdapter(OrgContext* org_context, haxorg_ImmWordAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmWord>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmAtMention_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmAtMention> { return org::imm::ImmAdapterT<org::imm::ImmAtMention>(other); }, org_context, other); }

void haxorg_destroy_ImmAtMentionAdapter(OrgContext* org_context, haxorg_ImmAtMentionAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmAtMention>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmRawText_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmRawText> { return org::imm::ImmAdapterT<org::imm::ImmRawText>(other); }, org_context, other); }

void haxorg_destroy_ImmRawTextAdapter(OrgContext* org_context, haxorg_ImmRawTextAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmRawText>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmPunctuation_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmPunctuation> { return org::imm::ImmAdapterT<org::imm::ImmPunctuation>(other); }, org_context, other); }

void haxorg_destroy_ImmPunctuationAdapter(OrgContext* org_context, haxorg_ImmPunctuationAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmPunctuation>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmPlaceholder_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmPlaceholder> { return org::imm::ImmAdapterT<org::imm::ImmPlaceholder>(other); }, org_context, other); }

void haxorg_destroy_ImmPlaceholderAdapter(OrgContext* org_context, haxorg_ImmPlaceholderAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmPlaceholder>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBigIdent_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBigIdent> { return org::imm::ImmAdapterT<org::imm::ImmBigIdent>(other); }, org_context, other); }

void haxorg_destroy_ImmBigIdentAdapter(OrgContext* org_context, haxorg_ImmBigIdentAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBigIdent>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmTextTarget_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmTextTarget> { return org::imm::ImmAdapterT<org::imm::ImmTextTarget>(other); }, org_context, other); }

void haxorg_destroy_ImmTextTargetAdapter(OrgContext* org_context, haxorg_ImmTextTargetAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmTextTarget>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBold_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBold> { return org::imm::ImmAdapterT<org::imm::ImmBold>(other); }, org_context, other); }

void haxorg_destroy_ImmBoldAdapter(OrgContext* org_context, haxorg_ImmBoldAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBold>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmUnderline_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmUnderline> { return org::imm::ImmAdapterT<org::imm::ImmUnderline>(other); }, org_context, other); }

void haxorg_destroy_ImmUnderlineAdapter(OrgContext* org_context, haxorg_ImmUnderlineAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmUnderline>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmMonospace_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmMonospace> { return org::imm::ImmAdapterT<org::imm::ImmMonospace>(other); }, org_context, other); }

void haxorg_destroy_ImmMonospaceAdapter(OrgContext* org_context, haxorg_ImmMonospaceAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmMonospace>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmMarkQuote_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmMarkQuote> { return org::imm::ImmAdapterT<org::imm::ImmMarkQuote>(other); }, org_context, other); }

void haxorg_destroy_ImmMarkQuoteAdapter(OrgContext* org_context, haxorg_ImmMarkQuoteAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmMarkQuote>>(org_context, obj); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmRadioTarget_getWords_const(OrgContext* org_context, haxorg_ImmRadioTargetAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<hstd::Str>(org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::getWords), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmRadioTarget_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmRadioTarget> { return org::imm::ImmAdapterT<org::imm::ImmRadioTarget>(other); }, org_context, other); }

void haxorg_destroy_ImmRadioTargetAdapter(OrgContext* org_context, haxorg_ImmRadioTargetAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmRadioTarget>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmVerbatim_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmVerbatim> { return org::imm::ImmAdapterT<org::imm::ImmVerbatim>(other); }, org_context, other); }

void haxorg_destroy_ImmVerbatimAdapter(OrgContext* org_context, haxorg_ImmVerbatimAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmVerbatim>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmItalic_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmItalic> { return org::imm::ImmAdapterT<org::imm::ImmItalic>(other); }, org_context, other); }

void haxorg_destroy_ImmItalicAdapter(OrgContext* org_context, haxorg_ImmItalicAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmItalic>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmStrike_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmStrike> { return org::imm::ImmAdapterT<org::imm::ImmStrike>(other); }, org_context, other); }

void haxorg_destroy_ImmStrikeAdapter(OrgContext* org_context, haxorg_ImmStrikeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmStrike>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmPar_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmPar> { return org::imm::ImmAdapterT<org::imm::ImmPar>(other); }, org_context, other); }

void haxorg_destroy_ImmParAdapter(OrgContext* org_context, haxorg_ImmParAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmPar>>(org_context, obj); }

haxorg_SemIdOfOrg haxorg_CmdCaption_get_text(OrgContext* org_context, haxorg_CmdCaption __this) { return org::bind::c::get_cpp_field<haxorg_SemIdOfOrg, org::sem::CmdCaption, org::sem::SemId<org::sem::Paragraph>, haxorg_CmdCaption>(org_context, __this, &org::sem::CmdCaption::text); }

void haxorg_destroy_CmdCaption(OrgContext* org_context, haxorg_CmdCaption* obj) { org::bind::c::execute_destroy<org::sem::CmdCaption>(org_context, obj); }

haxorg_ColumnView haxorg_CmdColumns_get_view(OrgContext* org_context, haxorg_CmdColumns __this) { return org::bind::c::get_cpp_field<haxorg_ColumnView, org::sem::CmdColumns, org::sem::ColumnView, haxorg_CmdColumns>(org_context, __this, &org::sem::CmdColumns::view); }

void haxorg_destroy_CmdColumns(OrgContext* org_context, haxorg_CmdColumns* obj) { org::bind::c::execute_destroy<org::sem::CmdColumns>(org_context, obj); }

haxorg_HstdStr haxorg_CmdName_get_name(OrgContext* org_context, haxorg_CmdName __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::CmdName, hstd::Str, haxorg_CmdName>(org_context, __this, &org::sem::CmdName::name); }

void haxorg_destroy_CmdName(OrgContext* org_context, haxorg_CmdName* obj) { org::bind::c::execute_destroy<org::sem::CmdName>(org_context, obj); }

haxorg_HstdStr haxorg_CmdCall_get_name(OrgContext* org_context, haxorg_CmdCall __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::CmdCall, hstd::Str, haxorg_CmdCall>(org_context, __this, &org::sem::CmdCall::name); }

haxorg_OptOfStr haxorg_CmdCall_get_fileName(OrgContext* org_context, haxorg_CmdCall __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::sem::CmdCall, hstd::Opt<hstd::Str>, haxorg_CmdCall>(org_context, __this, &org::sem::CmdCall::fileName); }

haxorg_AttrGroup haxorg_CmdCall_get_insideHeaderAttrs(OrgContext* org_context, haxorg_CmdCall __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::sem::CmdCall, org::sem::AttrGroup, haxorg_CmdCall>(org_context, __this, &org::sem::CmdCall::insideHeaderAttrs); }

haxorg_AttrGroup haxorg_CmdCall_get_callAttrs(OrgContext* org_context, haxorg_CmdCall __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::sem::CmdCall, org::sem::AttrGroup, haxorg_CmdCall>(org_context, __this, &org::sem::CmdCall::callAttrs); }

haxorg_AttrGroup haxorg_CmdCall_get_endHeaderAttrs(OrgContext* org_context, haxorg_CmdCall __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::sem::CmdCall, org::sem::AttrGroup, haxorg_CmdCall>(org_context, __this, &org::sem::CmdCall::endHeaderAttrs); }

haxorg_HstdVecOfSemIdOfBlockCodeEvalResult haxorg_CmdCall_get_result(OrgContext* org_context, haxorg_CmdCall __this) { return org::bind::c::get_cpp_field<haxorg_HstdVecOfSemIdOfBlockCodeEvalResult, org::sem::CmdCall, hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>, haxorg_CmdCall>(org_context, __this, &org::sem::CmdCall::result); }

void haxorg_destroy_CmdCall(OrgContext* org_context, haxorg_CmdCall* obj) { org::bind::c::execute_destroy<org::sem::CmdCall>(org_context, obj); }

haxorg_HstdStr haxorg_CmdAttr_get_target(OrgContext* org_context, haxorg_CmdAttr __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::CmdAttr, hstd::Str, haxorg_CmdAttr>(org_context, __this, &org::sem::CmdAttr::target); }

void haxorg_destroy_CmdAttr(OrgContext* org_context, haxorg_CmdAttr* obj) { org::bind::c::execute_destroy<org::sem::CmdAttr>(org_context, obj); }

haxorg_HstdStr haxorg_CmdExport_get_exporter(OrgContext* org_context, haxorg_CmdExport __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::CmdExport, hstd::Str, haxorg_CmdExport>(org_context, __this, &org::sem::CmdExport::exporter); }

haxorg_HstdStr haxorg_CmdExport_get_content(OrgContext* org_context, haxorg_CmdExport __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::sem::CmdExport, hstd::Str, haxorg_CmdExport>(org_context, __this, &org::sem::CmdExport::content); }

void haxorg_destroy_CmdExport(OrgContext* org_context, haxorg_CmdExport* obj) { org::bind::c::execute_destroy<org::sem::CmdExport>(org_context, obj); }

haxorg_ImmId haxorg_ImmCmdCaption_get_text(OrgContext* org_context, haxorg_ImmCmdCaption __this) { return org::bind::c::get_cpp_field<haxorg_ImmId, org::imm::ImmCmdCaption, org::imm::ImmIdT<org::imm::ImmParagraph>, haxorg_ImmCmdCaption>(org_context, __this, &org::imm::ImmCmdCaption::text); }

bool haxorg_ImmCmdCaption___eq___const(OrgContext* org_context, haxorg_ImmCmdCaption __this, haxorg_ImmCmdCaption other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdCaption::*)(org::imm::ImmCmdCaption const&) const>(&org::imm::ImmCmdCaption::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdCaption(OrgContext* org_context, haxorg_ImmCmdCaption* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCaption>(org_context, obj); }

haxorg_ColumnView haxorg_ImmCmdColumns_get_view(OrgContext* org_context, haxorg_ImmCmdColumns __this) { return org::bind::c::get_cpp_field<haxorg_ColumnView, org::imm::ImmCmdColumns, org::sem::ColumnView, haxorg_ImmCmdColumns>(org_context, __this, &org::imm::ImmCmdColumns::view); }

bool haxorg_ImmCmdColumns___eq___const(OrgContext* org_context, haxorg_ImmCmdColumns __this, haxorg_ImmCmdColumns other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdColumns::*)(org::imm::ImmCmdColumns const&) const>(&org::imm::ImmCmdColumns::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdColumns(OrgContext* org_context, haxorg_ImmCmdColumns* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdColumns>(org_context, obj); }

haxorg_HstdStr haxorg_ImmCmdName_get_name(OrgContext* org_context, haxorg_ImmCmdName __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmCmdName, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmCmdName>(org_context, __this, &org::imm::ImmCmdName::name); }

bool haxorg_ImmCmdName___eq___const(OrgContext* org_context, haxorg_ImmCmdName __this, haxorg_ImmCmdName other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdName::*)(org::imm::ImmCmdName const&) const>(&org::imm::ImmCmdName::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdName(OrgContext* org_context, haxorg_ImmCmdName* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdName>(org_context, obj); }

haxorg_HstdStr haxorg_ImmCmdCall_get_name(OrgContext* org_context, haxorg_ImmCmdCall __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmCmdCall, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmCmdCall>(org_context, __this, &org::imm::ImmCmdCall::name); }

haxorg_OptOfStr haxorg_ImmCmdCall_get_fileName(OrgContext* org_context, haxorg_ImmCmdCall __this) { return org::bind::c::get_cpp_field<haxorg_OptOfStr, org::imm::ImmCmdCall, hstd::ext::ImmBox<hstd::Opt<hstd::Str>>, haxorg_ImmCmdCall>(org_context, __this, &org::imm::ImmCmdCall::fileName); }

haxorg_AttrGroup haxorg_ImmCmdCall_get_insideHeaderAttrs(OrgContext* org_context, haxorg_ImmCmdCall __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::imm::ImmCmdCall, org::sem::AttrGroup, haxorg_ImmCmdCall>(org_context, __this, &org::imm::ImmCmdCall::insideHeaderAttrs); }

haxorg_AttrGroup haxorg_ImmCmdCall_get_callAttrs(OrgContext* org_context, haxorg_ImmCmdCall __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::imm::ImmCmdCall, org::sem::AttrGroup, haxorg_ImmCmdCall>(org_context, __this, &org::imm::ImmCmdCall::callAttrs); }

haxorg_AttrGroup haxorg_ImmCmdCall_get_endHeaderAttrs(OrgContext* org_context, haxorg_ImmCmdCall __this) { return org::bind::c::get_cpp_field<haxorg_AttrGroup, org::imm::ImmCmdCall, org::sem::AttrGroup, haxorg_ImmCmdCall>(org_context, __this, &org::imm::ImmCmdCall::endHeaderAttrs); }

haxorg_ImmVec haxorg_ImmCmdCall_get_result(OrgContext* org_context, haxorg_ImmCmdCall __this) { return org::bind::c::get_cpp_field<haxorg_ImmVec, org::imm::ImmCmdCall, hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>, haxorg_ImmCmdCall>(org_context, __this, &org::imm::ImmCmdCall::result); }

bool haxorg_ImmCmdCall___eq___const(OrgContext* org_context, haxorg_ImmCmdCall __this, haxorg_ImmCmdCall other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdCall::*)(org::imm::ImmCmdCall const&) const>(&org::imm::ImmCmdCall::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdCall(OrgContext* org_context, haxorg_ImmCmdCall* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdCall>(org_context, obj); }

haxorg_HstdStr haxorg_ImmCmdAttr_get_target(OrgContext* org_context, haxorg_ImmCmdAttr __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmCmdAttr, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmCmdAttr>(org_context, __this, &org::imm::ImmCmdAttr::target); }

bool haxorg_ImmCmdAttr___eq___const(OrgContext* org_context, haxorg_ImmCmdAttr __this, haxorg_ImmCmdAttr other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdAttr::*)(org::imm::ImmCmdAttr const&) const>(&org::imm::ImmCmdAttr::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdAttr(OrgContext* org_context, haxorg_ImmCmdAttr* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdAttr>(org_context, obj); }

haxorg_HstdStr haxorg_ImmCmdExport_get_exporter(OrgContext* org_context, haxorg_ImmCmdExport __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmCmdExport, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmCmdExport>(org_context, __this, &org::imm::ImmCmdExport::exporter); }

haxorg_HstdStr haxorg_ImmCmdExport_get_content(OrgContext* org_context, haxorg_ImmCmdExport __this) { return org::bind::c::get_cpp_field<haxorg_HstdStr, org::imm::ImmCmdExport, hstd::ext::ImmBox<hstd::Str>, haxorg_ImmCmdExport>(org_context, __this, &org::imm::ImmCmdExport::content); }

bool haxorg_ImmCmdExport___eq___const(OrgContext* org_context, haxorg_ImmCmdExport __this, haxorg_ImmCmdExport other) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmCmdExport::*)(org::imm::ImmCmdExport const&) const>(&org::imm::ImmCmdExport::operator==), org_context, __this, other); }

void haxorg_destroy_ImmCmdExport(OrgContext* org_context, haxorg_ImmCmdExport* obj) { org::bind::c::execute_destroy<org::imm::ImmCmdExport>(org_context, obj); }

void haxorg_destroy_ImmAdapterAttachedAPI(OrgContext* org_context, haxorg_ImmAdapterAttachedAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterAttachedAPI>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmLineCommand_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmLineCommand> { return org::imm::ImmAdapterT<org::imm::ImmLineCommand>(other); }, org_context, other); }

void haxorg_destroy_ImmLineCommandAdapter(OrgContext* org_context, haxorg_ImmLineCommandAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmLineCommand>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdCustomArgs_getName_const(OrgContext* org_context, haxorg_ImmCmdCustomArgsAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::getName), org_context, __this); }

bool haxorg_ImmAdapterTOfImmCmdCustomArgs_getIsAttached_const(OrgContext* org_context, haxorg_ImmCmdCustomArgsAdapter __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::getIsAttached), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCmdCustomArgs_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs> { return org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCustomArgsAdapter(OrgContext* org_context, haxorg_ImmCmdCustomArgsAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>>(org_context, obj); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmCmdCreator_getText_const(OrgContext* org_context, haxorg_ImmCmdCreatorAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdCreator>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCreator>::getText), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCmdCreator_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCreator> { return org::imm::ImmAdapterT<org::imm::ImmCmdCreator>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCreatorAdapter(OrgContext* org_context, haxorg_ImmCmdCreatorAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCreator>>(org_context, obj); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmCmdAuthor_getText_const(OrgContext* org_context, haxorg_ImmCmdAuthorAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>::getText), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCmdAuthor_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdAuthor> { return org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdAuthorAdapter(OrgContext* org_context, haxorg_ImmCmdAuthorAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdEmail_getText_const(OrgContext* org_context, haxorg_ImmCmdEmailAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdEmail>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdEmail>::getText), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCmdEmail_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdEmail> { return org::imm::ImmAdapterT<org::imm::ImmCmdEmail>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdEmailAdapter(OrgContext* org_context, haxorg_ImmCmdEmailAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdEmail>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdLanguage_getText_const(OrgContext* org_context, haxorg_ImmCmdLanguageAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>::getText), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCmdLanguage_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdLanguage> { return org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdLanguageAdapter(OrgContext* org_context, haxorg_ImmCmdLanguageAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>>(org_context, obj); }

haxorg_Tblfm haxorg_ImmAdapterTOfImmCmdTblfm_getExpr_const(OrgContext* org_context, haxorg_ImmCmdTblfmAdapter __this) { return org::bind::c::execute_cpp<haxorg_Tblfm>(static_cast<org::sem::Tblfm(org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::getExpr), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCmdTblfm_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdTblfm> { return org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdTblfmAdapter(OrgContext* org_context, haxorg_ImmCmdTblfmAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockCenterAPI(OrgContext* org_context, haxorg_ImmAdapterBlockCenterAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockCenterAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockQuoteAPI(OrgContext* org_context, haxorg_ImmAdapterBlockQuoteAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockQuoteAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockVerseAPI(OrgContext* org_context, haxorg_ImmAdapterBlockVerseAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockVerseAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockExampleAPI(OrgContext* org_context, haxorg_ImmAdapterBlockExampleAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockExampleAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterInlineExportAPI(OrgContext* org_context, haxorg_ImmAdapterInlineExportAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterInlineExportAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdExportAPI(OrgContext* org_context, haxorg_ImmAdapterCmdExportAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdExportAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockExportAPI(OrgContext* org_context, haxorg_ImmAdapterBlockExportAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockExportAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockDynamicFallbackAPI(OrgContext* org_context, haxorg_ImmAdapterBlockDynamicFallbackAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockDynamicFallbackAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockAdmonitionAPI(OrgContext* org_context, haxorg_ImmAdapterBlockAdmonitionAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockAdmonitionAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockCodeEvalResultAPI(OrgContext* org_context, haxorg_ImmAdapterBlockCodeEvalResultAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockCodeEvalResultAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterBlockCodeAPI(OrgContext* org_context, haxorg_ImmAdapterBlockCodeAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterBlockCodeAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterTableAPI(OrgContext* org_context, haxorg_ImmAdapterTableAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterTableAPI>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlock_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlock> { return org::imm::ImmAdapterT<org::imm::ImmBlock>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockAdapter(OrgContext* org_context, haxorg_ImmBlockAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlock>>(org_context, obj); }

bool haxorg_ImmAdapterTOfImmCell_getIsBlock_const(OrgContext* org_context, haxorg_ImmCellAdapter __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmCell>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCell>::getIsBlock), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCell_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCell> { return org::imm::ImmAdapterT<org::imm::ImmCell>(other); }, org_context, other); }

void haxorg_destroy_ImmCellAdapter(OrgContext* org_context, haxorg_ImmCellAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCell>>(org_context, obj); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmRow_getCells_const(OrgContext* org_context, haxorg_ImmRowAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell>>(org::imm::ImmAdapterT<org::imm::ImmRow>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRow>::getCells), org_context, __this); }

bool haxorg_ImmAdapterTOfImmRow_getIsBlock_const(OrgContext* org_context, haxorg_ImmRowAdapter __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmRow>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRow>::getIsBlock), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmRow_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmRow> { return org::imm::ImmAdapterT<org::imm::ImmRow>(other); }, org_context, other); }

void haxorg_destroy_ImmRowAdapter(OrgContext* org_context, haxorg_ImmRowAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmRow>>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdCaptionAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCaptionAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCaptionAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdColumnsAPI(OrgContext* org_context, haxorg_ImmAdapterCmdColumnsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdColumnsAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdNameAPI(OrgContext* org_context, haxorg_ImmAdapterCmdNameAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdNameAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdCallAPI(OrgContext* org_context, haxorg_ImmAdapterCmdCallAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdCallAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdResultsAPI(OrgContext* org_context, haxorg_ImmAdapterCmdResultsAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdResultsAPI>(org_context, obj); }

void haxorg_destroy_ImmAdapterCmdAttrAPI(OrgContext* org_context, haxorg_ImmAdapterCmdAttrAPI* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterCmdAttrAPI>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmAttached_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmAttached> { return org::imm::ImmAdapterT<org::imm::ImmAttached>(other); }, org_context, other); }

void haxorg_destroy_ImmAttachedAdapter(OrgContext* org_context, haxorg_ImmAttachedAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmAttached>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlockCenter_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockCenter> { return org::imm::ImmAdapterT<org::imm::ImmBlockCenter>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockCenterAdapter(OrgContext* org_context, haxorg_ImmBlockCenterAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockCenter>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlockQuote_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockQuote> { return org::imm::ImmAdapterT<org::imm::ImmBlockQuote>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockQuoteAdapter(OrgContext* org_context, haxorg_ImmBlockQuoteAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockQuote>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlockVerse_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockVerse> { return org::imm::ImmAdapterT<org::imm::ImmBlockVerse>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockVerseAdapter(OrgContext* org_context, haxorg_ImmBlockVerseAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockVerse>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlockExample_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockExample> { return org::imm::ImmAdapterT<org::imm::ImmBlockExample>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockExampleAdapter(OrgContext* org_context, haxorg_ImmBlockExampleAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockExample>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmInlineExport_getExporter_const(OrgContext* org_context, haxorg_ImmInlineExportAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmInlineExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineExport>::getExporter), org_context, __this); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmInlineExport_getContent_const(OrgContext* org_context, haxorg_ImmInlineExportAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmInlineExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineExport>::getContent), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmInlineExport_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmInlineExport> { return org::imm::ImmAdapterT<org::imm::ImmInlineExport>(other); }, org_context, other); }

void haxorg_destroy_ImmInlineExportAdapter(OrgContext* org_context, haxorg_ImmInlineExportAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmInlineExport>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdExport_getExporter_const(OrgContext* org_context, haxorg_ImmCmdExportAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdExport>::getExporter), org_context, __this); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdExport_getContent_const(OrgContext* org_context, haxorg_ImmCmdExportAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdExport>::getContent), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCmdExport_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdExport> { return org::imm::ImmAdapterT<org::imm::ImmCmdExport>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdExportAdapter(OrgContext* org_context, haxorg_ImmCmdExportAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdExport>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmBlockExport_getExporter_const(OrgContext* org_context, haxorg_ImmBlockExportAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmBlockExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockExport>::getExporter), org_context, __this); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmBlockExport_getContent_const(OrgContext* org_context, haxorg_ImmBlockExportAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmBlockExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockExport>::getContent), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmBlockExport_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockExport> { return org::imm::ImmAdapterT<org::imm::ImmBlockExport>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockExportAdapter(OrgContext* org_context, haxorg_ImmBlockExportAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockExport>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmBlockDynamicFallback_getName_const(OrgContext* org_context, haxorg_ImmBlockDynamicFallbackAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::getName), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmBlockDynamicFallback_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback> { return org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockDynamicFallbackAdapter(OrgContext* org_context, haxorg_ImmBlockDynamicFallbackAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>>(org_context, obj); }

void haxorg_create_ImmAdapterTOfImmBlockAdmonition_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition> { return org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockAdmonitionAdapter(OrgContext* org_context, haxorg_ImmBlockAdmonitionAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>>(org_context, obj); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmBlockCodeEvalResult_getRaw_const(OrgContext* org_context, haxorg_ImmBlockCodeEvalResultAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::sem::OrgCodeEvalOutput>(org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::getRaw), org_context, __this); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmBlockCodeEvalResult_getNode_const(OrgContext* org_context, haxorg_ImmBlockCodeEvalResultAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::getNode), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmBlockCodeEvalResult_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult> { return org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockCodeEvalResultAdapter(OrgContext* org_context, haxorg_ImmBlockCodeEvalResultAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>>(org_context, obj); }

haxorg_OptOfStr haxorg_ImmAdapterTOfImmBlockCode_getLang_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getLang), org_context, __this); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmBlockCode_getResult_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getResult), org_context, __this); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmBlockCode_getLines_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::sem::BlockCodeLine>(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getLines), org_context, __this); }

haxorg_AttrGroup haxorg_ImmAdapterTOfImmBlockCode_getSwitches_const(OrgContext* org_context, haxorg_ImmBlockCodeAdapter __this) { return org::bind::c::execute_cpp<haxorg_AttrGroup>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getSwitches), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmBlockCode_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmBlockCode> { return org::imm::ImmAdapterT<org::imm::ImmBlockCode>(other); }, org_context, other); }

void haxorg_destroy_ImmBlockCodeAdapter(OrgContext* org_context, haxorg_ImmBlockCodeAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmBlockCode>>(org_context, obj); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmTable_getRows_const(OrgContext* org_context, haxorg_ImmTableAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow>>(org::imm::ImmAdapterT<org::imm::ImmTable>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTable>::getRows), org_context, __this); }

bool haxorg_ImmAdapterTOfImmTable_getIsBlock_const(OrgContext* org_context, haxorg_ImmTableAdapter __this) { return org::bind::c::execute_cpp<bool>(static_cast<bool(org::imm::ImmAdapterT<org::imm::ImmTable>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTable>::getIsBlock), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmTable_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmTable> { return org::imm::ImmAdapterT<org::imm::ImmTable>(other); }, org_context, other); }

void haxorg_destroy_ImmTableAdapter(OrgContext* org_context, haxorg_ImmTableAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmTable>>(org_context, obj); }

haxorg_ImmAdapter haxorg_ImmAdapterTOfImmCmdCaption_getText_const(OrgContext* org_context, haxorg_ImmCmdCaptionAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmAdapter>(static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::getText), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCmdCaption_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCaption> { return org::imm::ImmAdapterT<org::imm::ImmCmdCaption>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCaptionAdapter(OrgContext* org_context, haxorg_ImmCmdCaptionAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCaption>>(org_context, obj); }

haxorg_ColumnView haxorg_ImmAdapterTOfImmCmdColumns_getView_const(OrgContext* org_context, haxorg_ImmCmdColumnsAdapter __this) { return org::bind::c::execute_cpp<haxorg_ColumnView>(static_cast<org::sem::ColumnView(org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::getView), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCmdColumns_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdColumns> { return org::imm::ImmAdapterT<org::imm::ImmCmdColumns>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdColumnsAdapter(OrgContext* org_context, haxorg_ImmCmdColumnsAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdColumns>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdName_getName_const(OrgContext* org_context, haxorg_ImmCmdNameAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdName>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdName>::getName), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCmdName_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdName> { return org::imm::ImmAdapterT<org::imm::ImmCmdName>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdNameAdapter(OrgContext* org_context, haxorg_ImmCmdNameAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdName>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdCall_getName_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getName), org_context, __this); }

haxorg_OptOfStr haxorg_ImmAdapterTOfImmCmdCall_getFileName_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter __this) { return org::bind::c::execute_cpp<haxorg_OptOfStr>(static_cast<hstd::Opt<hstd::Str> const&(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getFileName), org_context, __this); }

haxorg_AttrGroup haxorg_ImmAdapterTOfImmCmdCall_getInsideHeaderAttrs_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter __this) { return org::bind::c::execute_cpp<haxorg_AttrGroup>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getInsideHeaderAttrs), org_context, __this); }

haxorg_AttrGroup haxorg_ImmAdapterTOfImmCmdCall_getCallAttrs_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter __this) { return org::bind::c::execute_cpp<haxorg_AttrGroup>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getCallAttrs), org_context, __this); }

haxorg_AttrGroup haxorg_ImmAdapterTOfImmCmdCall_getEndHeaderAttrs_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter __this) { return org::bind::c::execute_cpp<haxorg_AttrGroup>(static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getEndHeaderAttrs), org_context, __this); }

haxorg_ImmVec haxorg_ImmAdapterTOfImmCmdCall_getResult_const(OrgContext* org_context, haxorg_ImmCmdCallAdapter __this) { return org::bind::c::execute_cpp<haxorg_ImmVec>(static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>>(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getResult), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCmdCall_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdCall> { return org::imm::ImmAdapterT<org::imm::ImmCmdCall>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdCallAdapter(OrgContext* org_context, haxorg_ImmCmdCallAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdCall>>(org_context, obj); }

haxorg_HstdStr haxorg_ImmAdapterTOfImmCmdAttr_getTarget_const(OrgContext* org_context, haxorg_ImmCmdAttrAdapter __this) { return org::bind::c::execute_cpp<haxorg_HstdStr>(static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::getTarget), org_context, __this); }

void haxorg_create_ImmAdapterTOfImmCmdAttr_ImmAdapterT(OrgContext* org_context, haxorg_ImmAdapter other) { return org::bind::c::execute_cpp<void>(+[](org::imm::ImmAdapter const& other) -> org::imm::ImmAdapterT<org::imm::ImmCmdAttr> { return org::imm::ImmAdapterT<org::imm::ImmCmdAttr>(other); }, org_context, other); }

void haxorg_destroy_ImmCmdAttrAdapter(OrgContext* org_context, haxorg_ImmCmdAttrAdapter* obj) { org::bind::c::execute_destroy<org::imm::ImmAdapterT<org::imm::ImmCmdAttr>>(org_context, obj); }

haxorg_SemIdOfOrg haxorg_newSemTimeStatic(OrgContext* org_context, haxorg_UserTimeBreakdown breakdown, bool isActive) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Time>(*)(hstd::UserTimeBreakdown const&, bool)>(&org::newSemTimeStatic), org_context, breakdown, isActive); }

haxorg_ImmAstContext haxorg_initImmutableAstContext(OrgContext* org_context) { return org::bind::c::execute_cpp<haxorg_ImmAstContext>(static_cast<std::shared_ptr<org::imm::ImmAstContext>(*)()>(&org::initImmutableAstContext), org_context); }

haxorg_SemIdOfOrg haxorg_asOneNode(OrgContext* org_context, haxorg_SemIdOfOrg arg) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Org>(*)(org::sem::SemId<org::sem::Org> const&)>(&org::asOneNode), org_context, arg); }

haxorg_StdString haxorg_formatToString(OrgContext* org_context, haxorg_SemIdOfOrg arg) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string(*)(org::sem::SemId<org::sem::Org>)>(&org::formatToString), org_context, arg); }

haxorg_StdString haxorg_exportToYamlString(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_OrgYamlExportOpts opts) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&, org::OrgYamlExportOpts const&)>(&org::exportToYamlString), org_context, node, opts); }

void haxorg_exportToYamlFile(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_StdString path, haxorg_OrgYamlExportOpts opts) { return org::bind::c::execute_cpp<void>(static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string, org::OrgYamlExportOpts const&)>(&org::exportToYamlFile), org_context, node, path, opts); }

haxorg_StdString haxorg_exportToJsonString(OrgContext* org_context, haxorg_SemIdOfOrg node) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&)>(&org::exportToJsonString), org_context, node); }

void haxorg_exportToJsonFile(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_StdString path) { return org::bind::c::execute_cpp<void>(static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string)>(&org::exportToJsonFile), org_context, node, path); }

haxorg_SemIdOfOrg haxorg_readProtobufFile(OrgContext* org_context, haxorg_StdString file) { return org::bind::c::execute_cpp<haxorg_SemIdOfOrg>(static_cast<org::sem::SemId<org::sem::Document>(*)(std::string const&)>(&org::readProtobufFile), org_context, file); }

void haxorg_exportToProtobufFile(OrgContext* org_context, haxorg_SemIdOfOrg doc, haxorg_StdString file) { return org::bind::c::execute_cpp<void>(static_cast<void(*)(org::sem::SemId<org::sem::Document>, std::string const&)>(&org::exportToProtobufFile), org_context, doc, file); }

haxorg_StdString haxorg_exportToTreeString(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_OrgTreeExportOpts opts) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string(*)(org::sem::SemId<org::sem::Org> const&, org::OrgTreeExportOpts const&)>(&org::exportToTreeString), org_context, node, opts); }

void haxorg_exportToTreeFile(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_StdString path, haxorg_OrgTreeExportOpts opts) { return org::bind::c::execute_cpp<void>(static_cast<void(*)(org::sem::SemId<org::sem::Org> const&, std::string, org::OrgTreeExportOpts const&)>(&org::exportToTreeFile), org_context, node, path, opts); }

haxorg_AstTrackingMap haxorg_getAstTrackingMap(OrgContext* org_context, haxorg_HstdVecOfSemIdOfOrg nodes) { return org::bind::c::execute_cpp<haxorg_AstTrackingMap>(static_cast<org::AstTrackingMap(*)(hstd::Vec<org::sem::SemId<org::sem::Org>> const&)>(&org::getAstTrackingMap), org_context, nodes); }

haxorg_HstdVecOfAstTrackingGroup haxorg_getSubnodeGroups(OrgContext* org_context, haxorg_SemIdOfOrg node, haxorg_AstTrackingMap map) { return org::bind::c::execute_cpp<haxorg_HstdVecOfAstTrackingGroup>(static_cast<hstd::Vec<org::AstTrackingGroup>(*)(org::sem::SemId<org::sem::Org>, org::AstTrackingMap const&)>(&org::getSubnodeGroups), org_context, node, map); }

haxorg_HstdVecOfSequenceAnnotation haxorg_annotateSequence(OrgContext* org_context, haxorg_HstdVecOfSequenceSegmentGroup groups, int first, int last) { return org::bind::c::execute_cpp<haxorg_HstdVecOfSequenceAnnotation>(static_cast<hstd::Vec<hstd::SequenceAnnotation>(*)(hstd::Vec<hstd::SequenceSegmentGroup> const&, int, int)>(&hstd::annotateSequence), org_context, groups, first, last); }

haxorg_GraphMapGraphState haxorg_initMapGraphState(OrgContext* org_context, haxorg_ImmAstContext ast) { return org::bind::c::execute_cpp<haxorg_GraphMapGraphState>(static_cast<std::shared_ptr<org::graph::MapGraphState>(*)(std::shared_ptr<org::imm::ImmAstContext>)>(&org::graph::initMapGraphState), org_context, ast); }

haxorg_StdString haxorg_serializeAstContextToText(OrgContext* org_context, haxorg_ImmAstContext store) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string(*)(std::shared_ptr<org::imm::ImmAstContext> const&)>(&org::imm::serializeToText), org_context, store); }

void haxorg_serializeAstContextFromText(OrgContext* org_context, haxorg_StdString binary, haxorg_ImmAstContext store) { return org::bind::c::execute_cpp<void>(static_cast<void(*)(std::string const&, std::shared_ptr<org::imm::ImmAstContext> const&)>(&org::imm::serializeFromText), org_context, binary, store); }

haxorg_StdString haxorg_serializeAstEpochToText(OrgContext* org_context, haxorg_ImmAstReplaceEpoch store) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string(*)(std::shared_ptr<org::imm::ImmAstReplaceEpoch> const&)>(&org::imm::serializeToText), org_context, store); }

void haxorg_serializeAstEpochFromText(OrgContext* org_context, haxorg_StdString binary, haxorg_ImmAstReplaceEpoch store) { return org::bind::c::execute_cpp<void>(static_cast<void(*)(std::string const&, std::shared_ptr<org::imm::ImmAstReplaceEpoch> const&)>(&org::imm::serializeFromText), org_context, binary, store); }

haxorg_StdString haxorg_serializeMapGraphToText(OrgContext* org_context, haxorg_GraphMapGraph store) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string(*)(std::shared_ptr<org::graph::MapGraph> const&)>(&org::imm::serializeToText), org_context, store); }

void haxorg_serializeMapGraphFromText(OrgContext* org_context, haxorg_StdString binary, haxorg_GraphMapGraph store) { return org::bind::c::execute_cpp<void>(static_cast<void(*)(std::string const&, std::shared_ptr<org::graph::MapGraph> const&)>(&org::imm::serializeFromText), org_context, binary, store); }

haxorg_StdString haxorg_serializeFromTextToTreeDump(OrgContext* org_context, haxorg_StdString binary) { return org::bind::c::execute_cpp<haxorg_StdString>(static_cast<std::string(*)(std::string const&)>(&org::imm::serializeFromTextToTreeDump), org_context, binary); }

/* clang-format on */
