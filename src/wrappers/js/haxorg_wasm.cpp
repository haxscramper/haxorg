/* clang-format off */
#include "node_utils.hpp"
#include "node_org_include.hpp"
#include "haxorg_wasm_manual.hpp"
using namespace org::bind::js;
void subdivide_0(org::bind::js::type_registration_guard& g) {
  org::bind::js::stdoptional_bind<int /*  [640]Type parameter [905]stdlib/Time.hpp:16:31( [766] >builtin/unqual<>) */>(g, "StdOptionalOfInt");
  org::bind::js::stdoptional_bind<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [640]Type parameter [905]stdlib/Time.hpp:22:31( [735] typedef type bits/stringfwd.h:79:33) */>(g, "StdOptionalOfStdString");
  org::bind::js::hstdVec_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [640]Type parameter [905]sem/SemOrgBaseSharedTypes.hpp:49:33( [780] >record 'OrgJson'<>) */>(g, "HstdVecOfOrgJson");
  org::bind::js::stdvector_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [640]Type parameter [905]sem/SemOrgBaseSharedTypes.hpp:49:33( [780] >record 'OrgJson'<>) */>(g, "StdVecOfOrgJson");
  org::bind::js::stdoptional_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceLoc /*  [640]Type parameter [905]sem/SemOrgBase.hpp:226:42( [780] >record 'SourceLoc'<>) */>(g, "StdOptionalOfParseSourceLoc");
  org::bind::js::hstdVec_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]sem/SemOrgBase.hpp:233:36( [780] >record 'Org'<>) */> /*  [640]Type parameter [905]sem/SemOrgBase.hpp:233:36( [780] >record 'SemId'< [657] templates: template-specialization-type>) */>(g, "HstdVecOfSemIdOfOrg");
  org::bind::js::stdvector_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]sem/SemOrgBase.hpp:233:36( [780] >record 'Org'<>) */> /*  [640]Type parameter [905]sem/SemOrgBase.hpp:233:36( [780] >record 'SemId'< [657] templates: template-specialization-type>) */>(g, "StdVecOfSemIdOfOrg");
  org::bind::js::stdoptional_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:131:46( [780] >record 'Org'<>) */> /*  [640]Type parameter [905]api/ParseContext.hpp:131:46( [780] >record 'SemId'< [657] templates: template-specialization-type>) */>(g, "StdOptionalOfSemIdOfOrg");
  org::bind::js::hstdVec_bind<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ext /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Report /*  [640]Type parameter [905]api/ParseContext.hpp:142:43( [780] >record 'Report'<>) */>(g, "HstdVecOfReport");
  org::bind::js::stdvector_bind<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ext /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Report /*  [640]Type parameter [905]api/ParseContext.hpp:142:43( [780] >record 'Report'<>) */>(g, "StdVecOfReport");
  org::bind::js::hstdVec_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ErrorGroup /*  [640]Type parameter [905]api/ParseContext.hpp:146:53( [780] >record 'ErrorGroup'<>) */> /*  [640]Type parameter [905]api/ParseContext.hpp:146:53( [780] >record 'SemId'< [657] templates: template-specialization-type>) */>(g, "HstdVecOfSemIdOfErrorGroup");
  org::bind::js::stdvector_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ErrorGroup /*  [640]Type parameter [905]api/ParseContext.hpp:146:53( [780] >record 'ErrorGroup'<>) */> /*  [640]Type parameter [905]api/ParseContext.hpp:146:53( [780] >record 'SemId'< [657] templates: template-specialization-type>) */>(g, "StdVecOfSemIdOfErrorGroup");
  org::bind::js::stdoptional_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [640]Type parameter [905]imm/ImmOrg.hpp:1031:36( [780] >record 'ImmAdapter'<>) */>(g, "StdOptionalOfImmAdapter");
  org::bind::js::hstdVec_bind<int /*  [640]Type parameter [905]imm/ImmOrg.hpp:1110:31( [766] >builtin/unqual<>) */>(g, "HstdVecOfInt");
  org::bind::js::stdvector_bind<int /*  [640]Type parameter [905]imm/ImmOrg.hpp:1110:31( [766] >builtin/unqual<>) */>(g, "StdVecOfInt");
  org::bind::js::hstdVec_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [640]Type parameter [905]imm/ImmOrg.hpp:1119:36( [780] >record 'ImmAdapter'<>) */>(g, "HstdVecOfImmAdapter");
  org::bind::js::stdvector_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [640]Type parameter [905]imm/ImmOrg.hpp:1119:36( [780] >record 'ImmAdapter'<>) */>(g, "StdVecOfImmAdapter");
  org::bind::js::hstdUnorderedSet_bind<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::pair<OrgSemKind /*  [640]Type parameter [905]imm/ImmOrg.hpp:984:13( [786] >enum 'OrgSemKind'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmReflFieldId /*  [640]Type parameter [905]imm/ImmOrg.hpp:984:13( [780] >record 'ImmReflFieldId'<>) */> /*  [640]Type parameter [905]imm/ImmOrg.hpp:984:13( [780] >record 'pair'< [657] templates: template-specialization-type>) */>(g, "HstdSetOfStdPairOfOrgSemKindImmReflFieldId");
  org::bind::js::stdpair_bind<OrgSemKind /*  [640]Type parameter [905]imm/ImmOrg.hpp:984:13( [786] >enum 'OrgSemKind'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmReflFieldId /*  [640]Type parameter [905]imm/ImmOrg.hpp:984:13( [780] >record 'ImmReflFieldId'<>) */>(g, "StdPairOfOrgSemKindImmReflFieldId");
  org::bind::js::hstdUnorderedMap_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::HashTagFlat /*  [640]Type parameter [905]api/SemBaseApi.hpp:154:13( [780] >record 'HashTagFlat'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [640]Type parameter [905]api/SemBaseApi.hpp:154:13( [780] >record 'AstTrackingPath'<>) */>(g, "HstdMapOfHashTagFlatAstTrackingPath");
  org::bind::js::stdunordered_map_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::HashTagFlat /*  [640]Type parameter [905]api/SemBaseApi.hpp:154:13( [780] >record 'HashTagFlat'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [640]Type parameter [905]api/SemBaseApi.hpp:154:13( [780] >record 'AstTrackingPath'<>) */>(g, "StdMapOfHashTagFlatAstTrackingPath");
  org::bind::js::stdoptional_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:243:49( [780] >record 'AstTrackingAlternatives'<>) */>(g, "StdOptionalOfAstTrackingAlternatives");
  org::bind::js::hstdUnorderedMap_bind<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str /*  [640]Type parameter [905]api/SemBaseApi.hpp:223:9( [780] >record 'Str'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:223:9( [780] >record 'AstTrackingAlternatives'<>) */>(g, "HstdMapOfStrAstTrackingAlternatives");
  org::bind::js::stdunordered_map_bind<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str /*  [640]Type parameter [905]api/SemBaseApi.hpp:223:9( [780] >record 'Str'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:223:9( [780] >record 'AstTrackingAlternatives'<>) */>(g, "StdMapOfStrAstTrackingAlternatives");
  org::bind::js::hstdUnorderedMap_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::HashTagFlat /*  [640]Type parameter [905]api/SemBaseApi.hpp:232:9( [780] >record 'HashTagFlat'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:232:9( [780] >record 'AstTrackingAlternatives'<>) */>(g, "HstdMapOfHashTagFlatAstTrackingAlternatives");
  org::bind::js::stdunordered_map_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::HashTagFlat /*  [640]Type parameter [905]api/SemBaseApi.hpp:232:9( [780] >record 'HashTagFlat'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:232:9( [780] >record 'AstTrackingAlternatives'<>) */>(g, "StdMapOfHashTagFlatAstTrackingAlternatives");
  org::bind::js::hstdVec_bind<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:38:35( [780] >record 'SequenceSegment'<>) */>(g, "HstdVecOfSequenceSegment");
  org::bind::js::stdvector_bind<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:38:35( [780] >record 'SequenceSegment'<>) */>(g, "StdVecOfSequenceSegment");
  org::bind::js::hstdVec_bind<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotationTag /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:79:41( [780] >record 'SequenceAnnotationTag'<>) */>(g, "HstdVecOfSequenceAnnotationTag");
  org::bind::js::stdvector_bind<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotationTag /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:79:41( [780] >record 'SequenceAnnotationTag'<>) */>(g, "StdVecOfSequenceAnnotationTag");
  org::bind::js::hstdVec_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmUniqId /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:25:49( [780] >record 'ImmUniqId'<>) */>(g, "HstdVecOfImmUniqId");
  org::bind::js::stdvector_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmUniqId /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:25:49( [780] >record 'ImmUniqId'<>) */>(g, "StdVecOfImmUniqId");
  org::bind::js::stdoptional_bind<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:51:35( [780] >record 'Str'<>) */>(g, "StdOptionalOfStr");
  org::bind::js::hstdVec_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:44:34( [780] >record 'MapLink'<>) */>(g, "HstdVecOfGraphMapLink");
  org::bind::js::stdvector_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:44:34( [780] >record 'MapLink'<>) */>(g, "StdVecOfGraphMapLink");
  org::bind::js::hstdVec_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:119:60( [780] >record 'MapNode'<>) */>(g, "HstdVecOfGraphMapNode");
  org::bind::js::stdvector_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:119:60( [780] >record 'MapNode'<>) */>(g, "StdVecOfGraphMapNode");
  org::bind::js::hstdVec_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:163:33( [780] >record 'MapEdge'<>) */>(g, "HstdVecOfGraphMapEdge");
  org::bind::js::stdvector_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:163:33( [780] >record 'MapEdge'<>) */>(g, "StdVecOfGraphMapEdge");
  org::bind::js::hstdUnorderedMap_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:117:60( [780] >record 'MapNode'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:117:60( [780] >record 'MapNodeProp'<>) */>(g, "HstdMapOfGraphMapNodeGraphMapNodeProp");
  org::bind::js::stdunordered_map_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:117:60( [780] >record 'MapNode'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:117:60( [780] >record 'MapNodeProp'<>) */>(g, "StdMapOfGraphMapNodeGraphMapNodeProp");
  org::bind::js::hstdUnorderedMap_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:118:60( [780] >record 'MapEdge'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:118:60( [780] >record 'MapEdgeProp'<>) */>(g, "HstdMapOfGraphMapEdgeGraphMapEdgeProp");
  org::bind::js::stdunordered_map_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:118:60( [780] >record 'MapEdge'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:118:60( [780] >record 'MapEdgeProp'<>) */>(g, "StdMapOfGraphMapEdgeGraphMapEdgeProp");
  org::bind::js::hstdUnorderedMap_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:120:60( [780] >record 'MapNode'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::AdjNodesList /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:120:60( [735] typedef type imm/ImmOrgGraph.hpp:119:60) */>(g, "HstdMapOfGraphMapNodeGraphAdjNodesList");
  org::bind::js::stdunordered_map_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:120:60( [780] >record 'MapNode'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::AdjNodesList /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:120:60( [735] typedef type imm/ImmOrgGraph.hpp:119:60) */>(g, "StdMapOfGraphMapNodeGraphAdjNodesList");
  org::bind::js::stdoptional_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:433:33( [780] >record 'MapLink'<>) */>(g, "StdOptionalOfGraphMapLink");
  org::bind::js::stdvariant_bind<org::sem::LispCode::Call, org::sem::LispCode::List, org::sem::LispCode::KeyValue, org::sem::LispCode::Number, org::sem::LispCode::Text, org::sem::LispCode::Ident, org::sem::LispCode::Boolean, org::sem::LispCode::Real>(g, "StdVariantOfLispCodeCallLispCodeListLispCodeKeyValueLispCodeNumberLispCodeTextLispCodeIdentLispCodeBooleanLispCodeReal");
  org::bind::js::hstdVec_bind<org::sem::LispCode>(g, "HstdVecOfLispCode");
  org::bind::js::stdvector_bind<org::sem::LispCode>(g, "StdVecOfLispCode");
  org::bind::js::hstdVec_bind<org::sem::Tblfm::Assign>(g, "HstdVecOfTblfmAssign");
  org::bind::js::stdvector_bind<org::sem::Tblfm::Assign>(g, "StdVecOfTblfmAssign");
  org::bind::js::stdvariant_bind<org::sem::Tblfm::Expr::AxisRef, org::sem::Tblfm::Expr::AxisName, org::sem::Tblfm::Expr::IntLiteral, org::sem::Tblfm::Expr::FloatLiteral, org::sem::Tblfm::Expr::RangeRef, org::sem::Tblfm::Expr::Call, org::sem::Tblfm::Expr::Elisp>(g, "StdVariantOfTblfmExprAxisRefTblfmExprAxisNameTblfmExprIntLiteralTblfmExprFloatLiteralTblfmExprRangeRefTblfmExprCallTblfmExprElisp");
  org::bind::js::hstdOpt_bind<org::sem::Tblfm::Expr::AxisRef::Position>(g, "OptOfTblfmExprAxisRefPosition");
  org::bind::js::stdvariant_bind<org::sem::Tblfm::Expr::AxisRef::Position::Index, org::sem::Tblfm::Expr::AxisRef::Position::Name>(g, "StdVariantOfTblfmExprAxisRefPositionIndexTblfmExprAxisRefPositionName");
  org::bind::js::hstdOpt_bind<org::sem::Tblfm::Expr::AxisRef>(g, "OptOfTblfmExprAxisRef");
  org::bind::js::hstdVec_bind<org::sem::Tblfm::Expr>(g, "HstdVecOfTblfmExpr");
  org::bind::js::stdvector_bind<org::sem::Tblfm::Expr>(g, "StdVecOfTblfmExpr");
  org::bind::js::hstdVec_bind<org::sem::Tblfm::Assign::Flag>(g, "HstdVecOfTblfmAssignFlag");
  org::bind::js::stdvector_bind<org::sem::Tblfm::Assign::Flag>(g, "StdVecOfTblfmAssignFlag");
  org::bind::js::hstdOpt_bind<bool>(g, "OptOfBool");
  org::bind::js::hstdOpt_bind<int>(g, "OptOfInt");
  org::bind::js::hstdOpt_bind<double>(g, "OptOfDouble");
  org::bind::js::stdvariant_bind<org::sem::AttrValue::TextValue, org::sem::AttrValue::FileReference, org::sem::AttrValue::LispValue>(g, "StdVariantOfAttrValueTextValueAttrValueFileReferenceAttrValueLispValue");
  org::bind::js::hstdOpt_bind<hstd::Str>(g, "OptOfStr");
  org::bind::js::hstdVec_bind<org::sem::AttrValue::DimensionSpan>(g, "HstdVecOfAttrValueDimensionSpan");
  org::bind::js::stdvector_bind<org::sem::AttrValue::DimensionSpan>(g, "StdVecOfAttrValueDimensionSpan");
  org::bind::js::hstdVec_bind<hstd::Str>(g, "HstdVecOfStr");
  org::bind::js::stdvector_bind<hstd::Str>(g, "StdVecOfStr");
  org::bind::js::hstdVec_bind<org::sem::HashTagFlat>(g, "HstdVecOfHashTagFlat");
  org::bind::js::stdvector_bind<org::sem::HashTagFlat>(g, "StdVecOfHashTagFlat");
  org::bind::js::hstdVec_bind<org::sem::HashTagText>(g, "HstdVecOfHashTagText");
  org::bind::js::stdvector_bind<org::sem::HashTagText>(g, "StdVecOfHashTagText");
  org::bind::js::stdvariant_bind<org::sem::LinkTarget::Raw, org::sem::LinkTarget::Id, org::sem::LinkTarget::CustomId, org::sem::LinkTarget::SubtreeTitle, org::sem::LinkTarget::Person, org::sem::LinkTarget::UserProtocol, org::sem::LinkTarget::Internal, org::sem::LinkTarget::Footnote, org::sem::LinkTarget::File, org::sem::LinkTarget::Attachment>(g, "StdVariantOfLinkTargetRawLinkTargetIdLinkTargetCustomIdLinkTargetSubtreeTitleLinkTargetPersonLinkTargetUserProtocolLinkTargetInternalLinkTargetFootnoteLinkTargetFileLinkTargetAttachment");
  org::bind::js::stdvariant_bind<org::sem::SubtreeLogHead::Priority, org::sem::SubtreeLogHead::Note, org::sem::SubtreeLogHead::Refile, org::sem::SubtreeLogHead::Clock, org::sem::SubtreeLogHead::State, org::sem::SubtreeLogHead::Deadline, org::sem::SubtreeLogHead::Schedule, org::sem::SubtreeLogHead::Tag, org::sem::SubtreeLogHead::Unknown>(g, "StdVariantOfSubtreeLogHeadPrioritySubtreeLogHeadNoteSubtreeLogHeadRefileSubtreeLogHeadClockSubtreeLogHeadStateSubtreeLogHeadDeadlineSubtreeLogHeadScheduleSubtreeLogHeadTagSubtreeLogHeadUnknown");
  org::bind::js::hstdOpt_bind<std::string>(g, "OptOfStdString");
  org::bind::js::hstdOpt_bind<hstd::UserTime>(g, "OptOfUserTime");
  org::bind::js::hstdVec_bind<org::sem::AttrValue>(g, "HstdVecOfAttrValue");
  org::bind::js::stdvector_bind<org::sem::AttrValue>(g, "StdVecOfAttrValue");
  org::bind::js::hstdOpt_bind<org::sem::AttrValue>(g, "OptOfAttrValue");
  org::bind::js::hstdOpt_bind<org::sem::AttrList>(g, "OptOfAttrList");
  org::bind::js::hstdUnorderedMap_bind<hstd::Str, org::sem::AttrList>(g, "HstdMapOfStrAttrList");
  org::bind::js::stdunordered_map_bind<hstd::Str, org::sem::AttrList>(g, "StdMapOfStrAttrList");
  org::bind::js::hstdOpt_bind<org::sem::OrgCodeEvalInput::Var>(g, "OptOfOrgCodeEvalInputVar");
  org::bind::js::hstdVec_bind<org::sem::OrgCodeEvalInput::Var>(g, "HstdVecOfOrgCodeEvalInputVar");
  org::bind::js::stdvector_bind<org::sem::OrgCodeEvalInput::Var>(g, "StdVecOfOrgCodeEvalInputVar");
  org::bind::js::hstdVec_bind<org::sem::ColumnView::Column>(g, "HstdVecOfColumnViewColumn");
  org::bind::js::stdvector_bind<org::sem::ColumnView::Column>(g, "StdVecOfColumnViewColumn");
  org::bind::js::stdvariant_bind<org::sem::ColumnView::Summary::CheckboxAggregate, org::sem::ColumnView::Summary::MathAggregate>(g, "StdVariantOfColumnViewSummaryCheckboxAggregateColumnViewSummaryMathAggregate");
  org::bind::js::hstdOpt_bind<org::sem::ColumnView::Summary>(g, "OptOfColumnViewSummary");
  org::bind::js::hstdVec_bind<org::sem::BlockCodeLine::Part>(g, "HstdVecOfBlockCodeLinePart");
  org::bind::js::stdvector_bind<org::sem::BlockCodeLine::Part>(g, "StdVecOfBlockCodeLinePart");
  org::bind::js::stdvariant_bind<org::sem::BlockCodeLine::Part::Raw, org::sem::BlockCodeLine::Part::Callout, org::sem::BlockCodeLine::Part::Tangle>(g, "StdVariantOfBlockCodeLinePartRawBlockCodeLinePartCalloutBlockCodeLinePartTangle");
  org::bind::js::stdvariant_bind<org::sem::DocumentExportConfig::DoExport, org::sem::DocumentExportConfig::ExportFixed>(g, "StdVariantOfDocumentExportConfigDoExportDocumentExportConfigExportFixed");
  org::bind::js::stdvariant_bind<org::sem::NamedProperty::Nonblocking, org::sem::NamedProperty::ArchiveTime, org::sem::NamedProperty::ArchiveFile, org::sem::NamedProperty::ArchiveOlpath, org::sem::NamedProperty::ArchiveTarget, org::sem::NamedProperty::ArchiveCategory, org::sem::NamedProperty::ArchiveTodo, org::sem::NamedProperty::Trigger, org::sem::NamedProperty::ExportLatexClass, org::sem::NamedProperty::CookieData, org::sem::NamedProperty::ExportLatexClassOptions, org::sem::NamedProperty::ExportLatexHeader, org::sem::NamedProperty::ExportLatexCompiler, org::sem::NamedProperty::Ordered, org::sem::NamedProperty::Effort, org::sem::NamedProperty::Visibility, org::sem::NamedProperty::ExportOptions, org::sem::NamedProperty::Blocker, org::sem::NamedProperty::Unnumbered, org::sem::NamedProperty::Created, org::sem::NamedProperty::RadioId, org::sem::NamedProperty::HashtagDef, org::sem::NamedProperty::CustomArgs, org::sem::NamedProperty::CustomRaw, org::sem::NamedProperty::CustomId, org::sem::NamedProperty::CustomSubtreeJson, org::sem::NamedProperty::CustomSubtreeFlags>(g, "StdVariantOfNamedPropertyNonblockingNamedPropertyArchiveTimeNamedPropertyArchiveFileNamedPropertyArchiveOlpathNamedPropertyArchiveTargetNamedPropertyArchiveCategoryNamedPropertyArchiveTodoNamedPropertyTriggerNamedPropertyExportLatexClassNamedPropertyCookieDataNamedPropertyExportLatexClassOptionsNamedPropertyExportLatexHeaderNamedPropertyExportLatexCompilerNamedPropertyOrderedNamedPropertyEffortNamedPropertyVisibilityNamedPropertyExportOptionsNamedPropertyBlockerNamedPropertyUnnumberedNamedPropertyCreatedNamedPropertyRadioIdNamedPropertyHashtagDefNamedPropertyCustomArgsNamedPropertyCustomRawNamedPropertyCustomIdNamedPropertyCustomSubtreeJsonNamedPropertyCustomSubtreeFlags");
  org::bind::js::hstdUnorderedMap_bind<hstd::Str, hstd::Str>(g, "HstdMapOfStrStr");
  org::bind::js::stdunordered_map_bind<hstd::Str, hstd::Str>(g, "StdMapOfStrStr");
  org::bind::js::stdvariant_bind<org::sem::OrgDiagnostics::ParseTokenError, org::sem::OrgDiagnostics::ParseError, org::sem::OrgDiagnostics::IncludeError, org::sem::OrgDiagnostics::ConvertError, org::sem::OrgDiagnostics::InternalError>(g, "StdVariantOfOrgDiagnosticsParseTokenErrorOrgDiagnosticsParseErrorOrgDiagnosticsIncludeErrorOrgDiagnosticsConvertErrorOrgDiagnosticsInternalError");
  org::bind::js::hstdOpt_bind<org::parse::SourceLoc>(g, "OptOfParseSourceLoc");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::ErrorItem>>(g, "HstdVecOfSemIdOfErrorItem");
  org::bind::js::stdvector_bind<org::sem::SemId<org::sem::ErrorItem>>(g, "StdVecOfSemIdOfErrorItem");
  org::bind::js::hstdOpt_bind<org::sem::AttrValue::LispValue>(g, "OptOfAttrValueLispValue");
}

void subdivide_1(org::bind::js::type_registration_guard& g) {
  org::bind::js::hstdOpt_bind<org::sem::AttrValue::Kind>(g, "OptOfAttrValueKind");
  org::bind::js::stdvariant_bind<org::sem::Time::Static, org::sem::Time::Dynamic>(g, "StdVariantOfTimeStaticTimeDynamic");
  org::bind::js::hstdVec_bind<org::sem::Time::Repeat>(g, "HstdVecOfTimeRepeat");
  org::bind::js::stdvector_bind<org::sem::Time::Repeat>(g, "StdVecOfTimeRepeat");
  org::bind::js::hstdOpt_bind<org::sem::Time::Repeat>(g, "OptOfTimeRepeat");
  org::bind::js::hstdOpt_bind<int64_t>(g, "OptOfInt64_t");
  org::bind::js::hstdVec_bind<org::sem::Symbol::Param>(g, "HstdVecOfSymbolParam");
  org::bind::js::stdvector_bind<org::sem::Symbol::Param>(g, "StdVecOfSymbolParam");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::ErrorSkipToken>>(g, "HstdVecOfSemIdOfErrorSkipToken");
  org::bind::js::stdvector_bind<org::sem::SemId<org::sem::ErrorSkipToken>>(g, "StdVecOfSemIdOfErrorSkipToken");
  org::bind::js::hstdOpt_bind<org::sem::SemId<org::sem::StmtList>>(g, "OptOfSemIdOfStmtList");
  org::bind::js::hstdVec_bind<org::sem::SubtreePeriod>(g, "HstdVecOfSubtreePeriod");
  org::bind::js::stdvector_bind<org::sem::SubtreePeriod>(g, "StdVecOfSubtreePeriod");
  org::bind::js::hstdIntSet_bind<org::sem::SubtreePeriod::Kind>(g, "IntSetOfSubtreePeriodKind");
  org::bind::js::hstdVec_bind<org::sem::NamedProperty>(g, "HstdVecOfNamedProperty");
  org::bind::js::stdvector_bind<org::sem::NamedProperty>(g, "StdVecOfNamedProperty");
  org::bind::js::hstdOpt_bind<org::sem::NamedProperty>(g, "OptOfNamedProperty");
  org::bind::js::hstdOpt_bind<org::sem::SubtreeCompletion>(g, "OptOfSubtreeCompletion");
  org::bind::js::hstdOpt_bind<org::sem::SemId<org::sem::Paragraph>>(g, "OptOfSemIdOfParagraph");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::HashTag>>(g, "HstdVecOfSemIdOfHashTag");
  org::bind::js::stdvector_bind<org::sem::SemId<org::sem::HashTag>>(g, "StdVecOfSemIdOfHashTag");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::SubtreeLog>>(g, "HstdVecOfSemIdOfSubtreeLog");
  org::bind::js::stdvector_bind<org::sem::SemId<org::sem::SubtreeLog>>(g, "StdVecOfSemIdOfSubtreeLog");
  org::bind::js::hstdOpt_bind<org::sem::SemId<org::sem::Time>>(g, "OptOfSemIdOfTime");
  org::bind::js::hstdOpt_bind<org::sem::ColumnView>(g, "OptOfColumnView");
  org::bind::js::hstdVec_bind<org::sem::TodoKeyword>(g, "HstdVecOfTodoKeyword");
  org::bind::js::stdvector_bind<org::sem::TodoKeyword>(g, "StdVecOfTodoKeyword");
  org::bind::js::hstdOpt_bind<org::sem::SemId<org::sem::RawText>>(g, "OptOfSemIdOfRawText");
  org::bind::js::stdvariant_bind<org::sem::File::Document, org::sem::File::Attachment, org::sem::File::Source>(g, "StdVariantOfFileDocumentFileAttachmentFileSource");
  org::bind::js::stdvariant_bind<org::sem::CmdInclude::Example, org::sem::CmdInclude::Export, org::sem::CmdInclude::Custom, org::sem::CmdInclude::Src, org::sem::CmdInclude::OrgDocument>(g, "StdVariantOfCmdIncludeExampleCmdIncludeExportCmdIncludeCustomCmdIncludeSrcCmdIncludeOrgDocument");
  org::bind::js::hstdOpt_bind<org::sem::SubtreePath>(g, "OptOfSubtreePath");
  org::bind::js::hstdextImmVec_bind<org::imm::ImmIdT<org::imm::ImmErrorItem /* imm_write */> /* imm_write */>(g, "ImmVecOfImmIdTOfImmErrorItem");
  org::bind::js::hstdextImmVec_bind<org::imm::ImmIdT<org::imm::ImmOrg /* imm_write */> /* imm_write */>(g, "ImmVecOfImmIdTOfImmOrg");
  org::bind::js::hstdextImmBox_bind<hstd::Str>(g, "ImmBoxOfStr");
  org::bind::js::stdvariant_bind<org::imm::ImmTime::Static /* imm_write */, org::imm::ImmTime::Dynamic /* imm_write */>(g, "StdVariantOfImmTimeStaticImmTimeDynamic");
  org::bind::js::hstdextImmVec_bind<org::imm::ImmTime::Repeat /* imm_write */>(g, "ImmVecOfImmTimeRepeat");
  org::bind::js::hstdextImmBox_bind<hstd::Opt<org::imm::ImmTime::Repeat /* imm_write */>>(g, "ImmBoxOfOptOfImmTimeRepeat");
  org::bind::js::hstdOpt_bind<org::imm::ImmTime::Repeat /* imm_write */>(g, "OptOfImmTimeRepeat");
  org::bind::js::hstdextImmVec_bind<org::imm::ImmSymbol::Param /* imm_write */>(g, "ImmVecOfImmSymbolParam");
  org::bind::js::hstdextImmBox_bind<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>>(g, "ImmBoxOfOptOfStr");
  org::bind::js::hstdextImmVec_bind<org::imm::ImmIdT<org::imm::ImmErrorSkipToken /* imm_write */> /* imm_write */>(g, "ImmVecOfImmIdTOfImmErrorSkipToken");
  org::bind::js::hstdextImmVec_bind<hstd /* imm_write */::Str /* imm_write */>(g, "ImmVecOfStr");
  org::bind::js::hstdextImmBox_bind<hstd::Opt<org::imm::ImmIdT<org::imm::ImmStmtList /* imm_write */> /* imm_write */>>(g, "ImmBoxOfOptOfImmIdTOfImmStmtList");
  org::bind::js::hstdOpt_bind<org::imm::ImmIdT<org::imm::ImmStmtList /* imm_write */> /* imm_write */>(g, "OptOfImmIdTOfImmStmtList");
  org::bind::js::hstdextImmBox_bind<hstd::Opt<org::sem::SubtreeCompletion>>(g, "ImmBoxOfOptOfSubtreeCompletion");
  org::bind::js::hstdextImmBox_bind<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph /* imm_write */> /* imm_write */>>(g, "ImmBoxOfOptOfImmIdTOfImmParagraph");
  org::bind::js::hstdOpt_bind<org::imm::ImmIdT<org::imm::ImmParagraph /* imm_write */> /* imm_write */>(g, "OptOfImmIdTOfImmParagraph");
  org::bind::js::hstdextImmVec_bind<org::imm::ImmIdT<org::imm::ImmHashTag /* imm_write */> /* imm_write */>(g, "ImmVecOfImmIdTOfImmHashTag");
  org::bind::js::hstdextImmVec_bind<org::imm::ImmIdT<org::imm::ImmSubtreeLog /* imm_write */> /* imm_write */>(g, "ImmVecOfImmIdTOfImmSubtreeLog");
  org::bind::js::hstdextImmVec_bind<org::sem::NamedProperty>(g, "ImmVecOfNamedProperty");
  org::bind::js::hstdextImmBox_bind<hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime /* imm_write */> /* imm_write */>>(g, "ImmBoxOfOptOfImmIdTOfImmTime");
  org::bind::js::hstdOpt_bind<org::imm::ImmIdT<org::imm::ImmTime /* imm_write */> /* imm_write */>(g, "OptOfImmIdTOfImmTime");
  org::bind::js::hstdextImmBox_bind<hstd::Opt<bool /* imm_write */>>(g, "ImmBoxOfOptOfBool");
  org::bind::js::hstdextImmBox_bind<hstd::Opt<int /* imm_write */>>(g, "ImmBoxOfOptOfInt");
  org::bind::js::hstdextImmBox_bind<hstd::Opt<org::sem::ColumnView>>(g, "ImmBoxOfOptOfColumnView");
  org::bind::js::hstdextImmVec_bind<org::sem::TodoKeyword>(g, "ImmVecOfTodoKeyword");
  org::bind::js::hstdextImmBox_bind<hstd::Opt<org::imm::ImmIdT<org::imm::ImmRawText /* imm_write */> /* imm_write */>>(g, "ImmBoxOfOptOfImmIdTOfImmRawText");
  org::bind::js::hstdOpt_bind<org::imm::ImmIdT<org::imm::ImmRawText /* imm_write */> /* imm_write */>(g, "OptOfImmIdTOfImmRawText");
  org::bind::js::stdvariant_bind<org::imm::ImmFile::Document /* imm_write */, org::imm::ImmFile::Attachment /* imm_write */, org::imm::ImmFile::Source /* imm_write */>(g, "StdVariantOfImmFileDocumentImmFileAttachmentImmFileSource");
  org::bind::js::stdvariant_bind<org::imm::ImmCmdInclude::Example /* imm_write */, org::imm::ImmCmdInclude::Export /* imm_write */, org::imm::ImmCmdInclude::Custom /* imm_write */, org::imm::ImmCmdInclude::Src /* imm_write */, org::imm::ImmCmdInclude::OrgDocument /* imm_write */>(g, "StdVariantOfImmCmdIncludeExampleImmCmdIncludeExportImmCmdIncludeCustomImmCmdIncludeSrcImmCmdIncludeOrgDocument");
  org::bind::js::hstdextImmBox_bind<hstd::Opt<org::sem::SubtreePath>>(g, "ImmBoxOfOptOfSubtreePath");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::BigIdent>>(g, "HstdVecOfSemIdOfBigIdent");
  org::bind::js::stdvector_bind<org::sem::SemId<org::sem::BigIdent>>(g, "StdVecOfSemIdOfBigIdent");
  org::bind::js::hstdVec_bind<hstd::UserTime>(g, "HstdVecOfUserTime");
  org::bind::js::stdvector_bind<hstd::UserTime>(g, "StdVecOfUserTime");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::Time>>(g, "HstdVecOfSemIdOfTime");
  org::bind::js::stdvector_bind<org::sem::SemId<org::sem::Time>>(g, "StdVecOfSemIdOfTime");
  org::bind::js::hstdOpt_bind<org::sem::SemId<org::sem::Org>>(g, "OptOfSemIdOfOrg");
  org::bind::js::hstdextImmBox_bind<hstd::Opt<org::imm::ImmIdT<org::imm::ImmOrg /* imm_write */> /* imm_write */>>(g, "ImmBoxOfOptOfImmIdTOfImmOrg");
  org::bind::js::hstdOpt_bind<org::imm::ImmIdT<org::imm::ImmOrg /* imm_write */> /* imm_write */>(g, "OptOfImmIdTOfImmOrg");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::Cell>>(g, "HstdVecOfSemIdOfCell");
  org::bind::js::stdvector_bind<org::sem::SemId<org::sem::Cell>>(g, "StdVecOfSemIdOfCell");
  org::bind::js::hstdextImmVec_bind<org::imm::ImmIdT<org::imm::ImmCell /* imm_write */> /* imm_write */>(g, "ImmVecOfImmIdTOfImmCell");
  org::bind::js::hstdOpt_bind<org::imm::ImmAdapterT<org::imm::ImmParagraph /* imm_write */>>(g, "OptOfImmAdapterTOfImmParagraph");
  org::bind::js::hstdOpt_bind<org::imm::ImmAdapterT<org::imm::ImmTime /* imm_write */>>(g, "OptOfImmAdapterTOfImmTime");
  org::bind::js::hstdOpt_bind<org::imm::ImmAdapterT<org::imm::ImmStmtList /* imm_write */>>(g, "OptOfImmAdapterTOfImmStmtList");
  org::bind::js::hstdOpt_bind<org::imm::ImmAdapterT<org::imm::ImmRawText /* imm_write */>>(g, "OptOfImmAdapterTOfImmRawText");
  org::bind::js::hstdVec_bind<org::sem::OrgCodeEvalOutput>(g, "HstdVecOfOrgCodeEvalOutput");
  org::bind::js::stdvector_bind<org::sem::OrgCodeEvalOutput>(g, "StdVecOfOrgCodeEvalOutput");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::BlockCodeEvalResult>>(g, "HstdVecOfSemIdOfBlockCodeEvalResult");
  org::bind::js::stdvector_bind<org::sem::SemId<org::sem::BlockCodeEvalResult>>(g, "StdVecOfSemIdOfBlockCodeEvalResult");
  org::bind::js::hstdVec_bind<org::sem::BlockCodeLine>(g, "HstdVecOfBlockCodeLine");
  org::bind::js::stdvector_bind<org::sem::BlockCodeLine>(g, "StdVecOfBlockCodeLine");
  org::bind::js::hstdVec_bind<org::sem::SemId<org::sem::Row>>(g, "HstdVecOfSemIdOfRow");
  org::bind::js::stdvector_bind<org::sem::SemId<org::sem::Row>>(g, "StdVecOfSemIdOfRow");
  org::bind::js::hstdextImmVec_bind<org::sem::OrgCodeEvalOutput>(g, "ImmVecOfOrgCodeEvalOutput");
  org::bind::js::hstdextImmVec_bind<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult /* imm_write */> /* imm_write */>(g, "ImmVecOfImmIdTOfImmBlockCodeEvalResult");
  org::bind::js::hstdextImmVec_bind<org::sem::BlockCodeLine>(g, "ImmVecOfBlockCodeLine");
  org::bind::js::hstdextImmVec_bind<org::imm::ImmIdT<org::imm::ImmRow /* imm_write */> /* imm_write */>(g, "ImmVecOfImmIdTOfImmRow");
  org::bind::js::hstdOpt_bind<org::imm::ImmAdapter>(g, "OptOfImmAdapter");
  org::bind::js::hstdVec_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [640]Type parameter [905]api/SemBaseApi.hpp:268:38( [780] >record 'AstTrackingGroup'<>) */>(g, "HstdVecOfAstTrackingGroup");
  org::bind::js::stdvector_bind<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [640]Type parameter [905]api/SemBaseApi.hpp:268:38( [780] >record 'AstTrackingGroup'<>) */>(g, "StdVecOfAstTrackingGroup");
  org::bind::js::hstdVec_bind<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:93:34( [780] >record 'SequenceAnnotation'<>) */>(g, "HstdVecOfSequenceAnnotation");
  org::bind::js::stdvector_bind<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:93:34( [780] >record 'SequenceAnnotation'<>) */>(g, "StdVecOfSequenceAnnotation");
  org::bind::js::hstdVec_bind<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:94:38( [780] >record 'SequenceSegmentGroup'<>) */>(g, "HstdVecOfSequenceSegmentGroup");
  org::bind::js::stdvector_bind<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:94:38( [780] >record 'SequenceSegmentGroup'<>) */>(g, "StdVecOfSequenceSegmentGroup");
  emscripten::class_<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */>("UserTimeBreakdown")
    .property("year", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */::year)
    .property("month", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */::month)
    .property("day", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */::day)
    .property("hour", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */::hour)
    .property("minute", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */::minute)
    .property("second", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */::second)
    .property("zone", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */::zone)
    .constructor<>()
    ;
  emscripten::class_<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */>("UserTime")
    .function("getBreakdown", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:50:32( [780] >record 'UserTimeBreakdown'<>) */(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */::*)() const>(&hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */::getBreakdown))
    .function("format", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]stdlib/Time.hpp:51:32( [735] typedef type bits/stringfwd.h:79:33) */(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */::*)() const>(&hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */::format))
    .function("getTimeDeltaSeconds", static_cast<int64_t /*  [905]stdlib/Time.hpp:56:22( [735] typedef type bits/stdint-intn.h:27:19) */(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */::*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime const& /*  [905]stdlib/Time.hpp:56:58( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'UserTime'<>)<>) */) const>(&hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */::getTimeDeltaSeconds))
    .function("toUnixTimestamp", static_cast<int64_t /*  [905]stdlib/Time.hpp:57:22( [735] typedef type bits/stdint-intn.h:27:19) */(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */::*)() const>(&hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */::toUnixTimestamp))
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceFileId /*  [905]lexbase/SourceManager.hpp:9:1( [780] >record 'SourceFileId'<>) */>("ParseSourceFileId")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceLoc /*  [905]lexbase/SourceManager.hpp:41:17( [780] >record 'SourceLoc'<>) */>("ParseSourceLoc")
    .property("line", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceLoc /*  [905]lexbase/SourceManager.hpp:41:17( [780] >record 'SourceLoc'<>) */::line)
    .property("column", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceLoc /*  [905]lexbase/SourceManager.hpp:41:17( [780] >record 'SourceLoc'<>) */::column)
    .property("pos", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceLoc /*  [905]lexbase/SourceManager.hpp:41:17( [780] >record 'SourceLoc'<>) */::pos)
    .property("file_id", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceLoc /*  [905]lexbase/SourceManager.hpp:41:17( [780] >record 'SourceLoc'<>) */::file_id)
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */>("OrgJson")
    .function("getKind", static_cast<OrgJsonKind /*  [905]sem/SemOrgBaseSharedTypes.hpp:26:26( [786] >enum 'OrgJsonKind'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::getKind))
    .function("getJsonString", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]sem/SemOrgBaseSharedTypes.hpp:40:26( [735] typedef type bits/stringfwd.h:79:33) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::getJsonString))
    .function("atIndex", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:41:55( [780] >record 'OrgJson'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)(int /*  [905]sem/SemOrgBaseSharedTypes.hpp:41:62( [766] >builtin/unqual<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::at))
    .function("atField", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:42:55( [780] >record 'OrgJson'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]sem/SemOrgBaseSharedTypes.hpp:43:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::at))
    .function("getString", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]sem/SemOrgBaseSharedTypes.hpp:44:33( [735] typedef type bits/stringfwd.h:79:33) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::getString))
    .function("getField", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:45:33( [780] >record 'OrgJson'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]sem/SemOrgBaseSharedTypes.hpp:45:61( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::getField))
    .function("getItem", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:46:33( [780] >record 'OrgJson'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)(int /*  [905]sem/SemOrgBaseSharedTypes.hpp:46:45( [766] >builtin/unqual<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::getItem))
    .function("getInt", static_cast<int /*  [905]sem/SemOrgBaseSharedTypes.hpp:47:33( [766] >builtin/unqual<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::getInt))
    .function("getBool", static_cast<bool /*  [905]sem/SemOrgBaseSharedTypes.hpp:48:33( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::getBool))
    .function("getArray", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [640]Type parameter [905]sem/SemOrgBaseSharedTypes.hpp:49:33( [780] >record 'OrgJson'<>) */> /*  [905]sem/SemOrgBaseSharedTypes.hpp:49:33( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::getArray))
    .function("dump", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]sem/SemOrgBaseSharedTypes.hpp:50:33( [735] typedef type bits/stringfwd.h:79:33) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)(int /*  [905]sem/SemOrgBaseSharedTypes.hpp:50:42( [766] >builtin/unqual<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::dump))
    .constructor<>()
    ;
}

void subdivide_2(org::bind::js::type_registration_guard& g) {
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */>("Org")
    .smart_ptr<org::sem::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */>>("Org")
    .property("loc", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::loc)
    .property("subnodes", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::subnodes)
    .function("getKind", static_cast<OrgSemKind /*  [905]sem/SemOrgBase.hpp:224:33( [786] >enum 'OrgSemKind'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::getKind), emscripten::pure_virtual())
    .function("push_back", static_cast<void /*  [905]sem/SemOrgBase.hpp:235:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]sem/SemOrgBase.hpp:235:40( [780] >record 'Org'<>) */> /*  [905]sem/SemOrgBase.hpp:235:40( [780] >record 'SemId'< [657] templates: template-specialization-type>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::push_back))
    .function("size", static_cast<int /*  [905]sem/SemOrgBase.hpp:244:18( [766] >builtin/unqual<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::size))
    .function("insert", static_cast<void /*  [905]sem/SemOrgBase.hpp:246:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::*)(int /*  [905]sem/SemOrgBase.hpp:246:30( [766] >builtin/unqual<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]sem/SemOrgBase.hpp:246:46( [780] >record 'Org'<>) */> /*  [905]sem/SemOrgBase.hpp:246:46( [780] >record 'SemId'< [657] templates: template-specialization-type>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::insert))
    .function("at", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]sem/SemOrgBase.hpp:261:77( [780] >record 'Org'<>) */> /*  [905]sem/SemOrgBase.hpp:261:77( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::*)(int /*  [905]sem/SemOrgBase.hpp:262:13( [766] >builtin/unqual<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::at))
    .function("is", static_cast<bool /*  [905]sem/SemOrgBase.hpp:306:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::*)(OrgSemKind /*  [905]sem/SemOrgBase.hpp:306:33( [786] >enum 'OrgSemKind'<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::is))
    ;
  emscripten::class_<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */>("OperationsTracer")
    .property("TraceState", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::TraceState)
    .property("traceToFile", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::traceToFile)
    .property("traceToBuffer", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::traceToBuffer)
    .property("traceStructured", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::traceStructured)
    .property("traceColored", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::traceColored)
    .property("activeLevel", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::activeLevel)
    .property("traceBuffer", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::traceBuffer)
    .function("setTraceFileStr", static_cast<void /*  [905]stdlib/TraceBase.hpp:72:19(<>) */(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]stdlib/TraceBase.hpp:73:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, bool /*  [905]stdlib/TraceBase.hpp:74:28( [755] >bool<>) */)>(&hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::setTraceFileStr))
    .function("sendMessage", static_cast<void /*  [905]stdlib/TraceBase.hpp:78:19(<>) */(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]stdlib/TraceBase.hpp:79:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]stdlib/TraceBase.hpp:80:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, int /*  [905]stdlib/TraceBase.hpp:81:28( [766] >builtin/unqual<>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]stdlib/TraceBase.hpp:82:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */)>(&hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::sendMessage))
    .constructor<>()
    ;
  emscripten::class_<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ext /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Cache /*  [905]ext/error_write.hpp:69:16( [780] >record 'Cache'<>) */>("Cache")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseFragment /*  [905]api/ParseContext.hpp:14:17( [780] >record 'OrgParseFragment'<>) */>("ParseOrgParseFragment")
    .property("baseLine", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseFragment /*  [905]api/ParseContext.hpp:14:17( [780] >record 'OrgParseFragment'<>) */::baseLine)
    .property("baseCol", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseFragment /*  [905]api/ParseContext.hpp:14:17( [780] >record 'OrgParseFragment'<>) */::baseCol)
    .property("text", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseFragment /*  [905]api/ParseContext.hpp:14:17( [780] >record 'OrgParseFragment'<>) */::text)
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [905]api/ParseContext.hpp:37:8( [780] >record 'OrgParseParameters'<>) */>("OrgParseParameters")
    .smart_ptr<std::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [905]api/ParseContext.hpp:37:8( [780] >record 'OrgParseParameters'<>) */>>("OrgParseParameters")
    .property("baseTokenTracePath", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [905]api/ParseContext.hpp:37:8( [780] >record 'OrgParseParameters'<>) */::baseTokenTracePath)
    .property("tokenTracePath", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [905]api/ParseContext.hpp:37:8( [780] >record 'OrgParseParameters'<>) */::tokenTracePath)
    .property("parseTracePath", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [905]api/ParseContext.hpp:37:8( [780] >record 'OrgParseParameters'<>) */::parseTracePath)
    .property("semTracePath", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [905]api/ParseContext.hpp:37:8( [780] >record 'OrgParseParameters'<>) */::semTracePath)
    .constructor(&org::bind::js::holder_type_constructor<std::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [905]api/ParseContext.hpp:37:8( [780] >record 'OrgParseParameters'<>) */>>)
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgDirectoryParseParameters /*  [905]api/ParseContext.hpp:64:8( [780] >record 'OrgDirectoryParseParameters'<>) */>("OrgDirectoryParseParameters")
    .smart_ptr<std::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgDirectoryParseParameters /*  [905]api/ParseContext.hpp:64:8( [780] >record 'OrgDirectoryParseParameters'<>) */>>("OrgDirectoryParseParameters")
    .constructor(&org::bind::js::holder_type_constructor<std::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgDirectoryParseParameters /*  [905]api/ParseContext.hpp:64:8( [780] >record 'OrgDirectoryParseParameters'<>) */>>)
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */>("ParseContext")
    .smart_ptr<std::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */>>("ParseContext")
    .function("getDiagnosticStrings", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ext /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Cache /*  [640]Type parameter [905]api/ParseContext.hpp:110:48( [780] >record 'Cache'<>) */> /*  [905]api/ParseContext.hpp:110:48( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)()>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::getDiagnosticStrings))
    .function("addSource", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceFileId /*  [905]api/ParseContext.hpp:112:27( [780] >record 'SourceFileId'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:113:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:114:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::addSource))
    .function("parseFileOpts", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:116:35( [780] >record 'Org'<>) */> /*  [905]api/ParseContext.hpp:116:35( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:117:52( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [640]Type parameter [905]api/ParseContext.hpp:118:52( [780] >record 'OrgParseParameters'<>) */> const& /*  [905]api/ParseContext.hpp:118:52( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::parseFileOpts))
    .function("parseFile", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:120:35( [780] >record 'Org'<>) */> /*  [905]api/ParseContext.hpp:120:35( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:120:64( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::parseFile))
    .function("parseString", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:122:35( [780] >record 'Org'<>) */> /*  [905]api/ParseContext.hpp:122:35( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:123:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:124:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::parseString))
    .function("parseStringOpts", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:126:35( [780] >record 'Org'<>) */> /*  [905]api/ParseContext.hpp:126:35( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const /*  [905]api/ParseContext.hpp:127:52( [707] T-const [735] typedef type bits/stringfwd.h:79:33) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:128:52( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [640]Type parameter [905]api/ParseContext.hpp:129:52( [780] >record 'OrgParseParameters'<>) */> const& /*  [905]api/ParseContext.hpp:129:52( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::parseStringOpts))
    .function("parseDirectory", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:131:46( [780] >record 'Org'<>) */> /*  [640]Type parameter [905]api/ParseContext.hpp:131:46( [780] >record 'SemId'< [657] templates: template-specialization-type>) */> /*  [905]api/ParseContext.hpp:131:46( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:132:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::parseDirectory))
    .function("parseDirectoryOpts", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:134:46( [780] >record 'Org'<>) */> /*  [640]Type parameter [905]api/ParseContext.hpp:134:46( [780] >record 'SemId'< [657] templates: template-specialization-type>) */> /*  [905]api/ParseContext.hpp:134:46( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:135:61( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgDirectoryParseParameters /*  [640]Type parameter [905]api/ParseContext.hpp:136:61( [780] >record 'OrgDirectoryParseParameters'<>) */> const& /*  [905]api/ParseContext.hpp:136:61( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::parseDirectoryOpts))
    .function("parseFileWithIncludes", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::File /*  [640]Type parameter [905]api/ParseContext.hpp:138:36( [780] >record 'File'<>) */> /*  [905]api/ParseContext.hpp:138:36( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:139:61( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgDirectoryParseParameters /*  [640]Type parameter [905]api/ParseContext.hpp:140:61( [780] >record 'OrgDirectoryParseParameters'<>) */> const& /*  [905]api/ParseContext.hpp:140:61( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::parseFileWithIncludes))
    .function("collectDiagnostics", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ext /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Report /*  [640]Type parameter [905]api/ParseContext.hpp:142:43( [780] >record 'Report'<>) */> /*  [905]api/ParseContext.hpp:142:43( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:143:50( [780] >record 'Org'<>) */> const& /*  [905]api/ParseContext.hpp:143:50( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ext /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Cache /*  [640]Type parameter [905]api/ParseContext.hpp:144:50( [780] >record 'Cache'<>) */> const& /*  [905]api/ParseContext.hpp:144:50( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::collectDiagnostics))
    .function("collectErrorNodes", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ErrorGroup /*  [640]Type parameter [905]api/ParseContext.hpp:146:53( [780] >record 'ErrorGroup'<>) */> /*  [640]Type parameter [905]api/ParseContext.hpp:146:53( [780] >record 'SemId'< [657] templates: template-specialization-type>) */> /*  [905]api/ParseContext.hpp:146:53( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:147:47( [780] >record 'Org'<>) */> const& /*  [905]api/ParseContext.hpp:147:47( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::collectErrorNodes))
    .constructor(&org::bind::js::holder_type_constructor<std::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */>>)
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmReflFieldId /*  [905]imm/ImmOrgBase.hpp:37:17( [780] >record 'ImmReflFieldId'<>) */>("ImmReflFieldId")
    .function("getName", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str /*  [905]imm/ImmOrgBase.hpp:38:24( [780] >record 'Str'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmReflFieldId /*  [905]imm/ImmOrgBase.hpp:37:17( [780] >record 'ImmReflFieldId'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmReflFieldId /*  [905]imm/ImmOrgBase.hpp:37:17( [780] >record 'ImmReflFieldId'<>) */::getName))
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */>("ImmId")
    .function("getKind", static_cast<OrgSemKind /*  [905]imm/ImmOrgBase.hpp:293:25( [786] >enum 'OrgSemKind'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */::getKind))
    .function("is", static_cast<bool /*  [905]imm/ImmOrgBase.hpp:294:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */::*)(OrgSemKind /*  [905]imm/ImmOrgBase.hpp:294:33( [786] >enum 'OrgSemKind'<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */::is))
    .function("getNodeIndex", static_cast<org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmId /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [550]type namespace @[0]' */::NodeIdxT /*  [905]imm/ImmOrgBase.hpp:298:23( [735] typedef type imm/ImmOrgBase.hpp:263:11) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */::getNodeIndex))
    .function("getReadableId", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]imm/ImmOrgBase.hpp:321:26( [735] typedef type bits/stringfwd.h:79:33) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */::getReadableId))
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmOrg /*  [905]imm/ImmOrgBase.hpp:352:17( [780] >record 'ImmOrg'<>) */>("ImmOrg")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPathStep /*  [905]imm/ImmOrg.hpp:96:17( [780] >record 'ImmPathStep'<>) */>("ImmPathStep")
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPath /*  [905]imm/ImmOrg.hpp:147:17( [780] >record 'ImmPath'<>) */>("ImmPath")
    .property("root", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPath /*  [905]imm/ImmOrg.hpp:147:17( [780] >record 'ImmPath'<>) */::root)
    .property("path", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPath /*  [905]imm/ImmOrg.hpp:147:17( [780] >record 'ImmPath'<>) */::path)
    .function("empty", static_cast<bool /*  [905]imm/ImmOrg.hpp:160:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPath /*  [905]imm/ImmOrg.hpp:147:17( [780] >record 'ImmPath'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPath /*  [905]imm/ImmOrg.hpp:147:17( [780] >record 'ImmPath'<>) */::empty))
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmUniqId /*  [905]imm/ImmOrg.hpp:243:17( [780] >record 'ImmUniqId'<>) */>("ImmUniqId")
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstReplaceEpoch /*  [905]imm/ImmOrg.hpp:506:8( [780] >record 'ImmAstReplaceEpoch'<>) */>("ImmAstReplaceEpoch")
    .smart_ptr<std::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstReplaceEpoch /*  [905]imm/ImmOrg.hpp:506:8( [780] >record 'ImmAstReplaceEpoch'<>) */>>("ImmAstReplaceEpoch")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */>("ImmAstContext")
    .smart_ptr<std::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */>>("ImmAstContext")
    .function("addRoot", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:663:28( [780] >record 'ImmAstVersion'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]imm/ImmOrg.hpp:663:57( [780] >record 'Org'<>) */> /*  [905]imm/ImmOrg.hpp:663:57( [780] >record 'SemId'< [657] templates: template-specialization-type>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */::addRoot))
    .function("getEmptyVersion", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:666:28( [780] >record 'ImmAstVersion'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */::*)()>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */::getEmptyVersion))
    .function("get", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]imm/ImmOrg.hpp:675:35( [780] >record 'Org'<>) */> /*  [905]imm/ImmOrg.hpp:675:35( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrg.hpp:675:55( [780] >record 'ImmId'<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */::get))
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */>("ImmAstVersion")
    .function("getRoot", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrg.hpp:748:25( [780] >record 'ImmId'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */::getRoot))
    .function("getRootAdapter", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:749:25( [780] >record 'ImmAdapter'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */::getRootAdapter))
    .function("getContext", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]imm/ImmOrg.hpp:751:45( [780] >record 'ImmAstContext'<>) */> /*  [905]imm/ImmOrg.hpp:751:45( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */::getContext))
    .function("getEpoch", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstReplaceEpoch /*  [640]Type parameter [905]imm/ImmOrg.hpp:755:50( [780] >record 'ImmAstReplaceEpoch'<>) */> /*  [905]imm/ImmOrg.hpp:755:50( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */::getEpoch))
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */>("ImmAdapter")
    .function("size", static_cast<int /*  [905]imm/ImmOrg.hpp:908:18( [766] >builtin/unqual<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::size))
    .function("isNil", static_cast<bool /*  [905]imm/ImmOrg.hpp:914:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::isNil))
    .function("isRoot", static_cast<bool /*  [905]imm/ImmOrg.hpp:915:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::isRoot))
    .function("getKind", static_cast<OrgSemKind /*  [905]imm/ImmOrg.hpp:931:25( [786] >enum 'OrgSemKind'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::getKind))
    .function("uniq", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmUniqId /*  [905]imm/ImmOrg.hpp:967:24( [780] >record 'ImmUniqId'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::uniq))
    .function("treeReprString", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]imm/ImmOrg.hpp:1008:26( [735] typedef type bits/stringfwd.h:79:33) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::treeReprString))
    .function("treeReprStringOpts", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]imm/ImmOrg.hpp:1012:26( [735] typedef type bits/stringfwd.h:79:33) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmAdapter /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::TreeReprConf const& /*  [905]imm/ImmOrg.hpp:1013:29( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'TreeReprConf'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::treeReprStringOpts))
    .function("isDirectParentOf", static_cast<bool /*  [905]imm/ImmOrg.hpp:1023:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter const& /*  [905]imm/ImmOrg.hpp:1023:54( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmAdapter'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::isDirectParentOf))
    .function("isIndirectParentOf", static_cast<bool /*  [905]imm/ImmOrg.hpp:1025:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter const& /*  [905]imm/ImmOrg.hpp:1025:56( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmAdapter'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::isIndirectParentOf))
    .function("isSubnodeOf", static_cast<bool /*  [905]imm/ImmOrg.hpp:1027:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter const& /*  [905]imm/ImmOrg.hpp:1027:49( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmAdapter'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::isSubnodeOf))
    .function("getParent", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [640]Type parameter [905]imm/ImmOrg.hpp:1031:36( [780] >record 'ImmAdapter'<>) */> /*  [905]imm/ImmOrg.hpp:1031:36( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::getParent))
    .function("getSelfIndex", static_cast<int /*  [905]imm/ImmOrg.hpp:1041:18( [766] >builtin/unqual<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::getSelfIndex))
    .function("atPathStep", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:1089:61( [780] >record 'ImmAdapter'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrg.hpp:1090:21( [780] >record 'ImmId'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPathStep /*  [905]imm/ImmOrg.hpp:1091:21( [780] >record 'ImmPathStep'<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::at))
    .function("atField", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:1095:58( [780] >record 'ImmAdapter'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmReflFieldId const& /*  [905]imm/ImmOrg.hpp:1096:31( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmReflFieldId'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::at))
    .function("atIndex", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:1105:58( [780] >record 'ImmAdapter'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(int /*  [905]imm/ImmOrg.hpp:1106:14( [766] >builtin/unqual<>) */, bool /*  [905]imm/ImmOrg.hpp:1107:14( [755] >bool<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::at))
    .function("atPath", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:1109:57( [780] >record 'ImmAdapter'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<int /*  [640]Type parameter [905]imm/ImmOrg.hpp:1110:31( [766] >builtin/unqual<>) */> const& /*  [905]imm/ImmOrg.hpp:1110:31( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Vec'< [657] templates: template-specialization-type>)<>) */, bool /*  [905]imm/ImmOrg.hpp:1111:31( [755] >bool<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::at))
    .function("is", static_cast<bool /*  [905]imm/ImmOrg.hpp:1117:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(OrgSemKind /*  [905]imm/ImmOrg.hpp:1117:33( [786] >enum 'OrgSemKind'<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::is))
    .function("sub", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [640]Type parameter [905]imm/ImmOrg.hpp:1119:36( [780] >record 'ImmAdapter'<>) */> /*  [905]imm/ImmOrg.hpp:1119:36( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(bool /*  [905]imm/ImmOrg.hpp:1119:45( [755] >bool<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::sub))
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmAdapter /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::TreeReprConf /*  [905]imm/ImmOrg.hpp:972:21( [780] >record 'TreeReprConf'<>) */>("ImmAdapterTreeReprConf")
    .property("maxDepth", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmAdapter /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::TreeReprConf /*  [905]imm/ImmOrg.hpp:972:21( [780] >record 'TreeReprConf'<>) */::maxDepth)
    .property("withAuxFields", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmAdapter /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::TreeReprConf /*  [905]imm/ImmOrg.hpp:972:21( [780] >record 'TreeReprConf'<>) */::withAuxFields)
    .property("withReflFields", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmAdapter /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::TreeReprConf /*  [905]imm/ImmOrg.hpp:972:21( [780] >record 'TreeReprConf'<>) */::withReflFields)
    .property("withFieldSubset", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmAdapter /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::TreeReprConf /*  [905]imm/ImmOrg.hpp:972:21( [780] >record 'TreeReprConf'<>) */::withFieldSubset)
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterVirtualBase /*  [905]imm/ImmOrg.hpp:1306:17( [780] >record 'ImmAdapterVirtualBase'<>) */>("ImmAdapterVirtualBase")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts /*  [905]api/SemBaseApi.hpp:30:17( [780] >record 'OrgYamlExportOpts'<>) */>("OrgYamlExportOpts")
    .property("skipNullFields", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts /*  [905]api/SemBaseApi.hpp:30:17( [780] >record 'OrgYamlExportOpts'<>) */::skipNullFields)
    .property("skipFalseFields", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts /*  [905]api/SemBaseApi.hpp:30:17( [780] >record 'OrgYamlExportOpts'<>) */::skipFalseFields)
    .property("skipZeroFields", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts /*  [905]api/SemBaseApi.hpp:30:17( [780] >record 'OrgYamlExportOpts'<>) */::skipZeroFields)
    .property("skipLocation", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts /*  [905]api/SemBaseApi.hpp:30:17( [780] >record 'OrgYamlExportOpts'<>) */::skipLocation)
    .property("skipId", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts /*  [905]api/SemBaseApi.hpp:30:17( [780] >record 'OrgYamlExportOpts'<>) */::skipId)
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */>("OrgTreeExportOpts")
    .property("withLineCol", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */::withLineCol)
    .property("withOriginalId", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */::withOriginalId)
    .property("withSubnodeIdx", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */::withSubnodeIdx)
    .property("skipEmptyFields", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */::skipEmptyFields)
    .property("startLevel", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */::startLevel)
    .property("withColor", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */::withColor)
    .property("maxDepth", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */::maxDepth)
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [905]api/SemBaseApi.hpp:102:17( [780] >record 'AstTrackingPath'<>) */>("AstTrackingPath")
    .property("path", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [905]api/SemBaseApi.hpp:102:17( [780] >record 'AstTrackingPath'<>) */::path)
    .function("getParent", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:106:45( [780] >record 'Org'<>) */> /*  [905]api/SemBaseApi.hpp:106:45( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [905]api/SemBaseApi.hpp:102:17( [780] >record 'AstTrackingPath'<>) */::*)(int /*  [905]api/SemBaseApi.hpp:107:13( [766] >builtin/unqual<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [905]api/SemBaseApi.hpp:102:17( [780] >record 'AstTrackingPath'<>) */::getParent))
    .function("getNode", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:119:35( [780] >record 'Org'<>) */> /*  [905]api/SemBaseApi.hpp:119:35( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [905]api/SemBaseApi.hpp:102:17( [780] >record 'AstTrackingPath'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [905]api/SemBaseApi.hpp:102:17( [780] >record 'AstTrackingPath'<>) */::getNode))
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [905]api/SemBaseApi.hpp:126:17( [780] >record 'AstTrackingAlternatives'<>) */>("AstTrackingAlternatives")
    .function("getAllNodes", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:131:46( [780] >record 'Org'<>) */> /*  [640]Type parameter [905]api/SemBaseApi.hpp:131:46( [780] >record 'SemId'< [657] templates: template-specialization-type>) */> /*  [905]api/SemBaseApi.hpp:131:46( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [905]api/SemBaseApi.hpp:126:17( [780] >record 'AstTrackingAlternatives'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [905]api/SemBaseApi.hpp:126:17( [780] >record 'AstTrackingAlternatives'<>) */::getAllNodes))
    .function("getNode", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:134:35( [780] >record 'Org'<>) */> /*  [905]api/SemBaseApi.hpp:134:35( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [905]api/SemBaseApi.hpp:126:17( [780] >record 'AstTrackingAlternatives'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [905]api/SemBaseApi.hpp:126:17( [780] >record 'AstTrackingAlternatives'<>) */::getNode))
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */>("AstTrackingGroup")
    .function("getRadioTargetConst", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::RadioTarget const& /*  [905]api/SemBaseApi.hpp:179:78( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'RadioTarget'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::getRadioTarget))
    .function("getTrackedHashtagConst", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::TrackedHashtag const& /*  [905]api/SemBaseApi.hpp:185:84( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'TrackedHashtag'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::getTrackedHashtag))
    .function("getTrackedHashtagMut", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::TrackedHashtag& /*  [905]api/SemBaseApi.hpp:191:76( [745] T-reference [752] >ref/ptr( [780] >record 'TrackedHashtag'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)()>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::getTrackedHashtag))
    .function("getSingleConst", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::Single const& /*  [905]api/SemBaseApi.hpp:196:68( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Single'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::getSingle))
    .function("getRadioTargetMut", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::RadioTarget& /*  [905]api/SemBaseApi.hpp:201:70( [745] T-reference [752] >ref/ptr( [780] >record 'RadioTarget'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)()>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::getRadioTarget))
    .function("getSingleMut", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::Single& /*  [905]api/SemBaseApi.hpp:205:60( [745] T-reference [752] >ref/ptr( [780] >record 'Single'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)()>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::getSingle))
    .function("isSingle", static_cast<bool /*  [905]api/SemBaseApi.hpp:209:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::isSingle))
    .function("isTrackedHashtag", static_cast<bool /*  [905]api/SemBaseApi.hpp:210:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::isTrackedHashtag))
    .function("isRadioTarget", static_cast<bool /*  [905]api/SemBaseApi.hpp:214:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::isRadioTarget))
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::RadioTarget /*  [905]api/SemBaseApi.hpp:140:21( [780] >record 'RadioTarget'<>) */>("AstTrackingGroupRadioTarget")
    .property("target", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::RadioTarget /*  [905]api/SemBaseApi.hpp:140:21( [780] >record 'RadioTarget'<>) */::target)
    .property("nodes", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::RadioTarget /*  [905]api/SemBaseApi.hpp:140:21( [780] >record 'RadioTarget'<>) */::nodes)
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::Single /*  [905]api/SemBaseApi.hpp:146:21( [780] >record 'Single'<>) */>("AstTrackingGroupSingle")
    .property("node", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::Single /*  [905]api/SemBaseApi.hpp:146:21( [780] >record 'Single'<>) */::node)
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::TrackedHashtag /*  [905]api/SemBaseApi.hpp:151:21( [780] >record 'TrackedHashtag'<>) */>("AstTrackingGroupTrackedHashtag")
    .property("tag", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::TrackedHashtag /*  [905]api/SemBaseApi.hpp:151:21( [780] >record 'TrackedHashtag'<>) */::tag)
    .property("targets", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::TrackedHashtag /*  [905]api/SemBaseApi.hpp:151:21( [780] >record 'TrackedHashtag'<>) */::targets)
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */>("AstTrackingMap")
    .property("footnotes", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::footnotes)
    .property("subtrees", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::subtrees)
    .property("names", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::names)
    .property("anchorTargets", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::anchorTargets)
    .property("radioTargets", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::radioTargets)
    .property("hashtagDefinitions", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::hashtagDefinitions)
    .function("getIdPath", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:243:49( [780] >record 'AstTrackingAlternatives'<>) */> /*  [905]api/SemBaseApi.hpp:243:49( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str const& /*  [905]api/SemBaseApi.hpp:244:26( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Str'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::getIdPath))
    .function("getNamePath", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:248:49( [780] >record 'AstTrackingAlternatives'<>) */> /*  [905]api/SemBaseApi.hpp:248:49( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str const& /*  [905]api/SemBaseApi.hpp:249:26( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Str'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::getNamePath))
    .function("getAnchorTarget", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:254:49( [780] >record 'AstTrackingAlternatives'<>) */> /*  [905]api/SemBaseApi.hpp:254:49( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str const& /*  [905]api/SemBaseApi.hpp:255:26( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Str'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::getAnchorTarget))
    .function("getFootnotePath", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:259:49( [780] >record 'AstTrackingAlternatives'<>) */> /*  [905]api/SemBaseApi.hpp:259:49( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str const& /*  [905]api/SemBaseApi.hpp:260:26( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Str'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::getFootnotePath))
    .constructor<>()
    ;
  emscripten::class_<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment /*  [905]stdlib/RangeSegmentation.hpp:16:17( [780] >record 'SequenceSegment'<>) */>("SequenceSegment")
    .property("kind", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment /*  [905]stdlib/RangeSegmentation.hpp:16:17( [780] >record 'SequenceSegment'<>) */::kind)
    .property("first", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment /*  [905]stdlib/RangeSegmentation.hpp:16:17( [780] >record 'SequenceSegment'<>) */::first)
    .property("last", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment /*  [905]stdlib/RangeSegmentation.hpp:16:17( [780] >record 'SequenceSegment'<>) */::last)
    .constructor<>()
    ;
  emscripten::class_<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup /*  [905]stdlib/RangeSegmentation.hpp:34:17( [780] >record 'SequenceSegmentGroup'<>) */>("SequenceSegmentGroup")
    .property("kind", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup /*  [905]stdlib/RangeSegmentation.hpp:34:17( [780] >record 'SequenceSegmentGroup'<>) */::kind)
    .property("segments", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup /*  [905]stdlib/RangeSegmentation.hpp:34:17( [780] >record 'SequenceSegmentGroup'<>) */::segments)
    .constructor<>()
    ;
  emscripten::class_<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotationTag /*  [905]stdlib/RangeSegmentation.hpp:44:17( [780] >record 'SequenceAnnotationTag'<>) */>("SequenceAnnotationTag")
    .property("groupKind", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotationTag /*  [905]stdlib/RangeSegmentation.hpp:44:17( [780] >record 'SequenceAnnotationTag'<>) */::groupKind)
    .property("segmentKinds", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotationTag /*  [905]stdlib/RangeSegmentation.hpp:44:17( [780] >record 'SequenceAnnotationTag'<>) */::segmentKinds)
    .constructor<>()
    ;
  emscripten::class_<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [905]stdlib/RangeSegmentation.hpp:73:17( [780] >record 'SequenceAnnotation'<>) */>("SequenceAnnotation")
    .property("first", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [905]stdlib/RangeSegmentation.hpp:73:17( [780] >record 'SequenceAnnotation'<>) */::first)
    .property("last", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [905]stdlib/RangeSegmentation.hpp:73:17( [780] >record 'SequenceAnnotation'<>) */::last)
    .property("annotations", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [905]stdlib/RangeSegmentation.hpp:73:17( [780] >record 'SequenceAnnotation'<>) */::annotations)
    .function("isAnnotatedWith", static_cast<bool /*  [905]stdlib/RangeSegmentation.hpp:83:19( [755] >bool<>) */(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [905]stdlib/RangeSegmentation.hpp:73:17( [780] >record 'SequenceAnnotation'<>) */::*)(int /*  [905]stdlib/RangeSegmentation.hpp:83:39( [766] >builtin/unqual<>) */, int /*  [905]stdlib/RangeSegmentation.hpp:83:54( [766] >builtin/unqual<>) */) const>(&hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [905]stdlib/RangeSegmentation.hpp:73:17( [780] >record 'SequenceAnnotation'<>) */::isAnnotatedWith))
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */>("GraphMapLink")
    .function("getRadio", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Radio& /*  [905]imm/ImmOrgGraph.hpp:36:5( [745] T-reference [752] >ref/ptr( [780] >record 'Radio'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::*)()>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::getRadio))
    .function("getRadio", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Radio const& /*  [905]imm/ImmOrgGraph.hpp:36:5( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Radio'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::getRadio))
    .function("isRadio", static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:36:5( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::isRadio))
    .function("getLink", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Link& /*  [905]imm/ImmOrgGraph.hpp:36:5( [745] T-reference [752] >ref/ptr( [780] >record 'Link'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::*)()>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::getLink))
    .function("getLink", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Link const& /*  [905]imm/ImmOrgGraph.hpp:36:5( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Link'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::getLink))
    .function("isLink", static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:36:5( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::isLink))
    .function("getKind", static_cast<org /*  [485]Apply namespace @[0] from 785:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 785:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 785:fillTypeRec ' [550]type namespace @[0]' */::Kind /*  [905]imm/ImmOrgGraph.hpp:36:5( [786] >enum 'Kind'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::getKind))
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Link /*  [905]imm/ImmOrgGraph.hpp:18:21( [780] >record 'Link'<>) */>("GraphMapLinkLink")
    .property("link", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Link /*  [905]imm/ImmOrgGraph.hpp:18:21( [780] >record 'Link'<>) */::link)
    .property("description", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Link /*  [905]imm/ImmOrgGraph.hpp:18:21( [780] >record 'Link'<>) */::description)
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Radio /*  [905]imm/ImmOrgGraph.hpp:31:21( [780] >record 'Radio'<>) */>("GraphMapLinkRadio")
    .property("target", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Radio /*  [905]imm/ImmOrgGraph.hpp:31:21( [780] >record 'Radio'<>) */::target)
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */>("GraphMapNodeProp")
    .property("id", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */::id)
    .property("unresolved", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */::unresolved)
    .function("getAdapter", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrgGraph.hpp:46:35( [780] >record 'ImmAdapter'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */::*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:47:57( [780] >record 'ImmAstContext'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:47:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */::getAdapter))
    .function("getSubtreeId", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:51:35( [780] >record 'Str'<>) */> /*  [905]imm/ImmOrgGraph.hpp:51:35( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */::*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:52:57( [780] >record 'ImmAstContext'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:52:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */::getSubtreeId))
    .function("getFootnoteName", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:54:35( [780] >record 'Str'<>) */> /*  [905]imm/ImmOrgGraph.hpp:54:35( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */::*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:55:57( [780] >record 'ImmAstContext'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:55:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */::getFootnoteName))
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp /*  [905]imm/ImmOrgGraph.hpp:60:17( [780] >record 'MapEdgeProp'<>) */>("GraphMapEdgeProp")
    .property("link", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp /*  [905]imm/ImmOrgGraph.hpp:60:17( [780] >record 'MapEdgeProp'<>) */::link)
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [905]imm/ImmOrgGraph.hpp:66:17( [780] >record 'MapNode'<>) */>("GraphMapNode")
    .property("id", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [905]imm/ImmOrgGraph.hpp:66:17( [780] >record 'MapNode'<>) */::id)
    .function("__eq__", static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:72:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [905]imm/ImmOrgGraph.hpp:66:17( [780] >record 'MapNode'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:72:45( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [905]imm/ImmOrgGraph.hpp:66:17( [780] >record 'MapNode'<>) */::operator==))
    .function("__lt__", static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:76:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [905]imm/ImmOrgGraph.hpp:66:17( [780] >record 'MapNode'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:76:44( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [905]imm/ImmOrgGraph.hpp:66:17( [780] >record 'MapNode'<>) */::operator<))
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [905]imm/ImmOrgGraph.hpp:83:17( [780] >record 'MapEdge'<>) */>("GraphMapEdge")
    .property("source", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [905]imm/ImmOrgGraph.hpp:83:17( [780] >record 'MapEdge'<>) */::source)
    .property("target", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [905]imm/ImmOrgGraph.hpp:83:17( [780] >record 'MapEdge'<>) */::target)
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */>("GraphMapGraph")
    .smart_ptr<std::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */>>("GraphMapGraph")
    .property("nodeProps", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::nodeProps)
    .property("edgeProps", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::edgeProps)
    .property("adjList", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::adjList)
    .property("adjListIn", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::adjListIn)
    .function("nodeCount", static_cast<int /*  [905]imm/ImmOrgGraph.hpp:152:18( [766] >builtin/unqual<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::nodeCount))
    .function("edgeCount", static_cast<int /*  [905]imm/ImmOrgGraph.hpp:153:18( [766] >builtin/unqual<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::edgeCount))
    .function("outNodes", static_cast<org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::AdjNodesList const& /*  [905]imm/ImmOrgGraph.hpp:155:34( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type imm/ImmOrgGraph.hpp:119:60)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:155:58( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::outNodes))
    .function("inNodes", static_cast<org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::AdjNodesList const& /*  [905]imm/ImmOrgGraph.hpp:159:34( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type imm/ImmOrgGraph.hpp:119:60)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:159:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::inNodes))
    .function("adjEdges", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:163:33( [780] >record 'MapEdge'<>) */> /*  [905]imm/ImmOrgGraph.hpp:163:33( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:163:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::adjEdges))
    .function("adjNodes", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:176:33( [780] >record 'MapNode'<>) */> /*  [905]imm/ImmOrgGraph.hpp:176:33( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:176:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::adjNodes))
    .function("outEdges", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:190:33( [780] >record 'MapEdge'<>) */> /*  [905]imm/ImmOrgGraph.hpp:190:33( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:190:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::outEdges))
    .function("inEdges", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:198:33( [780] >record 'MapEdge'<>) */> /*  [905]imm/ImmOrgGraph.hpp:198:33( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:198:56( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::inEdges))
    .function("outDegree", static_cast<int /*  [905]imm/ImmOrgGraph.hpp:206:18( [766] >builtin/unqual<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:206:43( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::outDegree))
    .function("inDegree", static_cast<int /*  [905]imm/ImmOrgGraph.hpp:210:18( [766] >builtin/unqual<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:210:42( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::inDegree))
    .function("isRegisteredNode", static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:214:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:214:51( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::isRegisteredNode))
    .function("isRegisteredNodeById", static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:218:65( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmUniqId const& /*  [905]imm/ImmOrgGraph.hpp:219:36( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmUniqId'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::isRegisteredNode))
    .function("atMapNode", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp const& /*  [905]imm/ImmOrgGraph.hpp:223:68( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNodeProp'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:224:24( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::at))
    .function("atMapEdge", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp const& /*  [905]imm/ImmOrgGraph.hpp:228:68( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapEdgeProp'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge const& /*  [905]imm/ImmOrgGraph.hpp:229:24( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapEdge'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::at))
    .function("addEdge", static_cast<void /*  [905]imm/ImmOrgGraph.hpp:234:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge const& /*  [905]imm/ImmOrgGraph.hpp:234:42( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapEdge'<>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::addEdge))
    .function("addEdgeWithProp", static_cast<void /*  [905]imm/ImmOrgGraph.hpp:237:60(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge const& /*  [905]imm/ImmOrgGraph.hpp:238:28( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapEdge'<>)<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp const& /*  [905]imm/ImmOrgGraph.hpp:239:28( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapEdgeProp'<>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::addEdge))
    .function("addNode", static_cast<void /*  [905]imm/ImmOrgGraph.hpp:242:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:242:42( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::addNode))
    .function("addNodeWithProp", static_cast<void /*  [905]imm/ImmOrgGraph.hpp:243:60(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:244:28( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp const& /*  [905]imm/ImmOrgGraph.hpp:245:28( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNodeProp'<>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::addNode))
    .function("hasEdge", static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:250:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:250:42( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:250:65( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::hasEdge))
    .function("hasNode", static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:261:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:261:42( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::hasNode))
    .function("has2AdapterEdge", static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:265:60( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter const& /*  [905]imm/ImmOrgGraph.hpp:266:37( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmAdapter'<>)<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter const& /*  [905]imm/ImmOrgGraph.hpp:267:37( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmAdapter'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::hasEdge))
    .constructor(&org::bind::js::holder_type_constructor<std::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */>>)
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [905]imm/ImmOrgGraph.hpp:370:8( [780] >record 'MapConfig'<>) */>("GraphMapConfig")
    .smart_ptr<std::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [905]imm/ImmOrgGraph.hpp:370:8( [780] >record 'MapConfig'<>) */>>("GraphMapConfig")
    .property("dbg", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [905]imm/ImmOrgGraph.hpp:370:8( [780] >record 'MapConfig'<>) */::dbg)
    .constructor(&org::bind::js::holder_type_constructor<std::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [905]imm/ImmOrgGraph.hpp:370:8( [780] >record 'MapConfig'<>) */>>)
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */>("GraphMapGraphState")
    .smart_ptr<std::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */>>("GraphMapGraphState")
    .property("graph", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::graph)
    .property("ast", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::ast)
    .function("getGraph", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:405:40( [780] >record 'MapGraph'<>) */> /*  [905]imm/ImmOrgGraph.hpp:405:40( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::getGraph))
    .class_function("FromAstContext", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:410:52( [780] >record 'MapGraphState'<>) */> /*  [905]imm/ImmOrgGraph.hpp:410:52( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */(*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:411:50( [780] >record 'ImmAstContext'<>) */> /*  [905]imm/ImmOrgGraph.hpp:411:50( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::FromAstContext))
    .function("registerNode", static_cast<void /*  [905]imm/ImmOrgGraph.hpp:416:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp const& /*  [905]imm/ImmOrgGraph.hpp:417:43( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNodeProp'<>)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:418:43( [780] >record 'MapConfig'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:418:43( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::registerNode))
    .function("addNode", static_cast<void /*  [905]imm/ImmOrgGraph.hpp:420:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter const& /*  [905]imm/ImmOrgGraph.hpp:421:43( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmAdapter'<>)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:422:43( [780] >record 'MapConfig'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:422:43( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::addNode))
    .function("addNodeRec", static_cast<void /*  [905]imm/ImmOrgGraph.hpp:424:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:425:57( [780] >record 'ImmAstContext'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:425:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter const& /*  [905]imm/ImmOrgGraph.hpp:426:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmAdapter'<>)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:427:57( [780] >record 'MapConfig'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:427:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::addNodeRec))
    .function("getUnresolvedSubtreeLinks", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:429:33( [780] >record 'MapLink'<>) */> /*  [905]imm/ImmOrgGraph.hpp:429:33( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterT<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmSubtree /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:430:53( [780] >record 'ImmSubtree'<>) */> /*  [905]imm/ImmOrgGraph.hpp:430:53( [780] >record 'ImmAdapterT'< [657] templates: template-specialization-type>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:431:53( [780] >record 'MapConfig'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:431:53( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::getUnresolvedSubtreeLinks))
    .function("getUnresolvedLink", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:433:33( [780] >record 'MapLink'<>) */> /*  [905]imm/ImmOrgGraph.hpp:433:33( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterT<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmLink /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:434:50( [780] >record 'ImmLink'<>) */> /*  [905]imm/ImmOrgGraph.hpp:434:50( [780] >record 'ImmAdapterT'< [657] templates: template-specialization-type>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:435:50( [780] >record 'MapConfig'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:435:50( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::getUnresolvedLink))
    ;
  emscripten::class_<org::sem::LispCode>("LispCode")
    .property("data", &org::sem::LispCode::data)
    .function("__eq__", static_cast<bool(org::sem::LispCode::*)(org::sem::LispCode const&) const>(&org::sem::LispCode::operator==))
    .function("isCall", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isCall))
    .function("getCallConst", static_cast<org::sem::LispCode::Call const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getCall))
    .function("getCallMut", static_cast<org::sem::LispCode::Call&(org::sem::LispCode::*)()>(&org::sem::LispCode::getCall))
    .function("isList", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isList))
    .function("getListConst", static_cast<org::sem::LispCode::List const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getList))
    .function("getListMut", static_cast<org::sem::LispCode::List&(org::sem::LispCode::*)()>(&org::sem::LispCode::getList))
    .function("isKeyValue", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isKeyValue))
    .function("getKeyValueConst", static_cast<org::sem::LispCode::KeyValue const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getKeyValue))
    .function("getKeyValueMut", static_cast<org::sem::LispCode::KeyValue&(org::sem::LispCode::*)()>(&org::sem::LispCode::getKeyValue))
    .function("isNumber", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isNumber))
    .function("getNumberConst", static_cast<org::sem::LispCode::Number const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getNumber))
    .function("getNumberMut", static_cast<org::sem::LispCode::Number&(org::sem::LispCode::*)()>(&org::sem::LispCode::getNumber))
    .function("isText", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isText))
    .function("getTextConst", static_cast<org::sem::LispCode::Text const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getText))
    .function("getTextMut", static_cast<org::sem::LispCode::Text&(org::sem::LispCode::*)()>(&org::sem::LispCode::getText))
    .function("isIdent", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isIdent))
    .function("getIdentConst", static_cast<org::sem::LispCode::Ident const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getIdent))
    .function("getIdentMut", static_cast<org::sem::LispCode::Ident&(org::sem::LispCode::*)()>(&org::sem::LispCode::getIdent))
    .function("isBoolean", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isBoolean))
    .function("getBooleanConst", static_cast<org::sem::LispCode::Boolean const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getBoolean))
    .function("getBooleanMut", static_cast<org::sem::LispCode::Boolean&(org::sem::LispCode::*)()>(&org::sem::LispCode::getBoolean))
    .function("isReal", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isReal))
    .function("getRealConst", static_cast<org::sem::LispCode::Real const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::getReal))
    .function("getRealMut", static_cast<org::sem::LispCode::Real&(org::sem::LispCode::*)()>(&org::sem::LispCode::getReal))
    .class_function("getKindStatic", static_cast<org::sem::LispCode::Kind(*)(org::sem::LispCode::Data const&)>(&org::sem::LispCode::getKind))
    .function("getKind", static_cast<org::sem::LispCode::Kind(org::sem::LispCode::*)() const>(&org::sem::LispCode::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LispCode::Call>("LispCodeCall")
    .property("name", &org::sem::LispCode::Call::name)
    .property("args", &org::sem::LispCode::Call::args)
    .function("__eq__", static_cast<bool(org::sem::LispCode::Call::*)(org::sem::LispCode::Call const&) const>(&org::sem::LispCode::Call::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LispCode::List>("LispCodeList")
    .property("items", &org::sem::LispCode::List::items)
    .function("__eq__", static_cast<bool(org::sem::LispCode::List::*)(org::sem::LispCode::List const&) const>(&org::sem::LispCode::List::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LispCode::KeyValue>("LispCodeKeyValue")
    .property("name", &org::sem::LispCode::KeyValue::name)
    .property("value", &org::sem::LispCode::KeyValue::value)
    .function("__eq__", static_cast<bool(org::sem::LispCode::KeyValue::*)(org::sem::LispCode::KeyValue const&) const>(&org::sem::LispCode::KeyValue::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LispCode::Number>("LispCodeNumber")
    .property("value", &org::sem::LispCode::Number::value)
    .function("__eq__", static_cast<bool(org::sem::LispCode::Number::*)(org::sem::LispCode::Number const&) const>(&org::sem::LispCode::Number::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LispCode::Text>("LispCodeText")
    .property("value", &org::sem::LispCode::Text::value)
    .function("__eq__", static_cast<bool(org::sem::LispCode::Text::*)(org::sem::LispCode::Text const&) const>(&org::sem::LispCode::Text::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LispCode::Ident>("LispCodeIdent")
    .property("name", &org::sem::LispCode::Ident::name)
    .function("__eq__", static_cast<bool(org::sem::LispCode::Ident::*)(org::sem::LispCode::Ident const&) const>(&org::sem::LispCode::Ident::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LispCode::Boolean>("LispCodeBoolean")
    .property("value", &org::sem::LispCode::Boolean::value)
    .function("__eq__", static_cast<bool(org::sem::LispCode::Boolean::*)(org::sem::LispCode::Boolean const&) const>(&org::sem::LispCode::Boolean::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LispCode::Real>("LispCodeReal")
    .property("value", &org::sem::LispCode::Real::value)
    .function("__eq__", static_cast<bool(org::sem::LispCode::Real::*)(org::sem::LispCode::Real const&) const>(&org::sem::LispCode::Real::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::LispCode::Kind>("LispCodeKind");
  emscripten::class_<org::sem::Tblfm>("Tblfm")
    .property("exprs", &org::sem::Tblfm::exprs)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::*)(org::sem::Tblfm const&) const>(&org::sem::Tblfm::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr>("TblfmExpr")
    .property("data", &org::sem::Tblfm::Expr::data)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::*)(org::sem::Tblfm::Expr const&) const>(&org::sem::Tblfm::Expr::operator==))
    .function("isAxisRef", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isAxisRef))
    .function("getAxisRefConst", static_cast<org::sem::Tblfm::Expr::AxisRef const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getAxisRef))
    .function("getAxisRefMut", static_cast<org::sem::Tblfm::Expr::AxisRef&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getAxisRef))
    .function("isAxisName", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isAxisName))
    .function("getAxisNameConst", static_cast<org::sem::Tblfm::Expr::AxisName const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getAxisName))
    .function("getAxisNameMut", static_cast<org::sem::Tblfm::Expr::AxisName&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getAxisName))
    .function("isIntLiteral", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isIntLiteral))
    .function("getIntLiteralConst", static_cast<org::sem::Tblfm::Expr::IntLiteral const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getIntLiteral))
    .function("getIntLiteralMut", static_cast<org::sem::Tblfm::Expr::IntLiteral&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getIntLiteral))
    .function("isFloatLiteral", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isFloatLiteral))
    .function("getFloatLiteralConst", static_cast<org::sem::Tblfm::Expr::FloatLiteral const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getFloatLiteral))
    .function("getFloatLiteralMut", static_cast<org::sem::Tblfm::Expr::FloatLiteral&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getFloatLiteral))
    .function("isRangeRef", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isRangeRef))
    .function("getRangeRefConst", static_cast<org::sem::Tblfm::Expr::RangeRef const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getRangeRef))
    .function("getRangeRefMut", static_cast<org::sem::Tblfm::Expr::RangeRef&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getRangeRef))
    .function("isCall", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isCall))
    .function("getCallConst", static_cast<org::sem::Tblfm::Expr::Call const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getCall))
    .function("getCallMut", static_cast<org::sem::Tblfm::Expr::Call&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getCall))
    .function("isElisp", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isElisp))
    .function("getElispConst", static_cast<org::sem::Tblfm::Expr::Elisp const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getElisp))
    .function("getElispMut", static_cast<org::sem::Tblfm::Expr::Elisp&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getElisp))
    .class_function("getKindStatic", static_cast<org::sem::Tblfm::Expr::Kind(*)(org::sem::Tblfm::Expr::Data const&)>(&org::sem::Tblfm::Expr::getKind))
    .function("getKind", static_cast<org::sem::Tblfm::Expr::Kind(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::AxisRef>("TblfmExprAxisRef")
    .property("col", &org::sem::Tblfm::Expr::AxisRef::col)
    .property("row", &org::sem::Tblfm::Expr::AxisRef::row)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::*)(org::sem::Tblfm::Expr::AxisRef const&) const>(&org::sem::Tblfm::Expr::AxisRef::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::AxisRef::Position>("TblfmExprAxisRefPosition")
    .property("data", &org::sem::Tblfm::Expr::AxisRef::Position::data)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)(org::sem::Tblfm::Expr::AxisRef::Position const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::operator==))
    .function("isIndex", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::isIndex))
    .function("getIndexConst", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Index const&(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getIndex))
    .function("getIndexMut", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Index&(org::sem::Tblfm::Expr::AxisRef::Position::*)()>(&org::sem::Tblfm::Expr::AxisRef::Position::getIndex))
    .function("isName", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::isName))
    .function("getNameConst", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Name const&(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getName))
    .function("getNameMut", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Name&(org::sem::Tblfm::Expr::AxisRef::Position::*)()>(&org::sem::Tblfm::Expr::AxisRef::Position::getName))
    .class_function("getKindStatic", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(*)(org::sem::Tblfm::Expr::AxisRef::Position::Data const&)>(&org::sem::Tblfm::Expr::AxisRef::Position::getKind))
    .function("getKind", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::AxisRef::Position::Index>("TblfmExprAxisRefPositionIndex")
    .property("index", &org::sem::Tblfm::Expr::AxisRef::Position::Index::index)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::Index::*)(org::sem::Tblfm::Expr::AxisRef::Position::Index const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::Index::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::AxisRef::Position::Name>("TblfmExprAxisRefPositionName")
    .property("name", &org::sem::Tblfm::Expr::AxisRef::Position::Name::name)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::Name::*)(org::sem::Tblfm::Expr::AxisRef::Position::Name const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::Name::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::Tblfm::Expr::AxisRef::Position::Kind>("TblfmExprAxisRefPositionKind");
  emscripten::class_<org::sem::Tblfm::Expr::AxisName>("TblfmExprAxisName")
    .property("name", &org::sem::Tblfm::Expr::AxisName::name)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::AxisName::*)(org::sem::Tblfm::Expr::AxisName const&) const>(&org::sem::Tblfm::Expr::AxisName::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::IntLiteral>("TblfmExprIntLiteral")
    .property("value", &org::sem::Tblfm::Expr::IntLiteral::value)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::IntLiteral::*)(org::sem::Tblfm::Expr::IntLiteral const&) const>(&org::sem::Tblfm::Expr::IntLiteral::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::FloatLiteral>("TblfmExprFloatLiteral")
    .property("value", &org::sem::Tblfm::Expr::FloatLiteral::value)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::FloatLiteral::*)(org::sem::Tblfm::Expr::FloatLiteral const&) const>(&org::sem::Tblfm::Expr::FloatLiteral::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::RangeRef>("TblfmExprRangeRef")
    .property("first", &org::sem::Tblfm::Expr::RangeRef::first)
    .property("last", &org::sem::Tblfm::Expr::RangeRef::last)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::RangeRef::*)(org::sem::Tblfm::Expr::RangeRef const&) const>(&org::sem::Tblfm::Expr::RangeRef::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::Call>("TblfmExprCall")
    .property("name", &org::sem::Tblfm::Expr::Call::name)
    .property("args", &org::sem::Tblfm::Expr::Call::args)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::Call::*)(org::sem::Tblfm::Expr::Call const&) const>(&org::sem::Tblfm::Expr::Call::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::Tblfm::Expr::Elisp>("TblfmExprElisp")
    .property("value", &org::sem::Tblfm::Expr::Elisp::value)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Expr::Elisp::*)(org::sem::Tblfm::Expr::Elisp const&) const>(&org::sem::Tblfm::Expr::Elisp::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::Tblfm::Expr::Kind>("TblfmExprKind");
  emscripten::class_<org::sem::Tblfm::Assign>("TblfmAssign")
    .property("target", &org::sem::Tblfm::Assign::target)
    .property("expr", &org::sem::Tblfm::Assign::expr)
    .property("flags", &org::sem::Tblfm::Assign::flags)
    .function("__eq__", static_cast<bool(org::sem::Tblfm::Assign::*)(org::sem::Tblfm::Assign const&) const>(&org::sem::Tblfm::Assign::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::Tblfm::Assign::Flag>("TblfmAssignFlag");
  emscripten::class_<org::sem::AttrValue>("AttrValue")
    .property("name", &org::sem::AttrValue::name)
    .property("varname", &org::sem::AttrValue::varname)
    .property("span", &org::sem::AttrValue::span)
    .property("isQuoted", &org::sem::AttrValue::isQuoted)
    .property("data", &org::sem::AttrValue::data)
    .function("getBool", static_cast<hstd::Opt<bool>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getBool))
    .function("getInt", static_cast<hstd::Opt<int>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getInt))
    .function("getString", static_cast<hstd::Str(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getString))
    .function("getDouble", static_cast<hstd::Opt<double>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getDouble))
    .function("__eq__", static_cast<bool(org::sem::AttrValue::*)(org::sem::AttrValue const&) const>(&org::sem::AttrValue::operator==))
    .function("isTextValue", static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isTextValue))
    .function("getTextValueConst", static_cast<org::sem::AttrValue::TextValue const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getTextValue))
    .function("getTextValueMut", static_cast<org::sem::AttrValue::TextValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getTextValue))
    .function("isFileReference", static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isFileReference))
    .function("getFileReferenceConst", static_cast<org::sem::AttrValue::FileReference const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getFileReference))
    .function("getFileReferenceMut", static_cast<org::sem::AttrValue::FileReference&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getFileReference))
    .function("isLispValue", static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isLispValue))
    .function("getLispValueConst", static_cast<org::sem::AttrValue::LispValue const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getLispValue))
    .function("getLispValueMut", static_cast<org::sem::AttrValue::LispValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getLispValue))
    .class_function("getKindStatic", static_cast<org::sem::AttrValue::Kind(*)(org::sem::AttrValue::DataVariant const&)>(&org::sem::AttrValue::getKind))
    .function("getKind", static_cast<org::sem::AttrValue::Kind(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::AttrValue::DimensionSpan>("AttrValueDimensionSpan")
    .property("first", &org::sem::AttrValue::DimensionSpan::first)
    .property("last", &org::sem::AttrValue::DimensionSpan::last)
    .function("__eq__", static_cast<bool(org::sem::AttrValue::DimensionSpan::*)(org::sem::AttrValue::DimensionSpan const&) const>(&org::sem::AttrValue::DimensionSpan::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::AttrValue::TextValue>("AttrValueTextValue")
    .property("value", &org::sem::AttrValue::TextValue::value)
    .function("__eq__", static_cast<bool(org::sem::AttrValue::TextValue::*)(org::sem::AttrValue::TextValue const&) const>(&org::sem::AttrValue::TextValue::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::AttrValue::FileReference>("AttrValueFileReference")
    .property("file", &org::sem::AttrValue::FileReference::file)
    .property("reference", &org::sem::AttrValue::FileReference::reference)
    .function("__eq__", static_cast<bool(org::sem::AttrValue::FileReference::*)(org::sem::AttrValue::FileReference const&) const>(&org::sem::AttrValue::FileReference::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::AttrValue::LispValue>("AttrValueLispValue")
    .property("code", &org::sem::AttrValue::LispValue::code)
    .function("__eq__", static_cast<bool(org::sem::AttrValue::LispValue::*)(org::sem::AttrValue::LispValue const&) const>(&org::sem::AttrValue::LispValue::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::AttrValue::Kind>("AttrValueKind");
  emscripten::class_<org::sem::HashTagFlat>("HashTagFlat")
    .property("tags", &org::sem::HashTagFlat::tags)
    .function("__eq__", static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator==))
    .function("__lt__", static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator<))
    .constructor<>()
    ;
  emscripten::class_<org::sem::TodoKeyword>("TodoKeyword")
    .property("name", &org::sem::TodoKeyword::name)
    .property("shortcut", &org::sem::TodoKeyword::shortcut)
    .property("onEnter", &org::sem::TodoKeyword::onEnter)
    .property("onLeave", &org::sem::TodoKeyword::onLeave)
    .function("__eq__", static_cast<bool(org::sem::TodoKeyword::*)(org::sem::TodoKeyword const&) const>(&org::sem::TodoKeyword::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::TodoKeyword::Transition>("TodoKeywordTransition");
  emscripten::class_<org::sem::HashTagText>("HashTagText")
    .property("head", &org::sem::HashTagText::head)
    .property("subtags", &org::sem::HashTagText::subtags)
    .function("__eq__", static_cast<bool(org::sem::HashTagText::*)(org::sem::HashTagText const&) const>(&org::sem::HashTagText::operator==))
    .function("prefixMatch", static_cast<bool(org::sem::HashTagText::*)(hstd::Vec<hstd::Str> const&) const>(&org::sem::HashTagText::prefixMatch))
    .function("getFlatHashes", static_cast<hstd::Vec<org::sem::HashTagFlat>(org::sem::HashTagText::*)(bool) const>(&org::sem::HashTagText::getFlatHashes))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreePath>("SubtreePath")
    .property("path", &org::sem::SubtreePath::path)
    .function("__eq__", static_cast<bool(org::sem::SubtreePath::*)(org::sem::SubtreePath const&) const>(&org::sem::SubtreePath::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget>("LinkTarget")
    .property("data", &org::sem::LinkTarget::data)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::*)(org::sem::LinkTarget const&) const>(&org::sem::LinkTarget::operator==))
    .function("isRaw", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isRaw))
    .function("getRawConst", static_cast<org::sem::LinkTarget::Raw const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getRaw))
    .function("getRawMut", static_cast<org::sem::LinkTarget::Raw&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getRaw))
    .function("isId", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isId))
    .function("getIdConst", static_cast<org::sem::LinkTarget::Id const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getId))
    .function("getIdMut", static_cast<org::sem::LinkTarget::Id&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getId))
    .function("isCustomId", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isCustomId))
    .function("getCustomIdConst", static_cast<org::sem::LinkTarget::CustomId const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getCustomId))
    .function("getCustomIdMut", static_cast<org::sem::LinkTarget::CustomId&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getCustomId))
    .function("isSubtreeTitle", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isSubtreeTitle))
    .function("getSubtreeTitleConst", static_cast<org::sem::LinkTarget::SubtreeTitle const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getSubtreeTitle))
    .function("getSubtreeTitleMut", static_cast<org::sem::LinkTarget::SubtreeTitle&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getSubtreeTitle))
    .function("isPerson", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isPerson))
    .function("getPersonConst", static_cast<org::sem::LinkTarget::Person const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getPerson))
    .function("getPersonMut", static_cast<org::sem::LinkTarget::Person&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getPerson))
    .function("isUserProtocol", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isUserProtocol))
    .function("getUserProtocolConst", static_cast<org::sem::LinkTarget::UserProtocol const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getUserProtocol))
    .function("getUserProtocolMut", static_cast<org::sem::LinkTarget::UserProtocol&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getUserProtocol))
    .function("isInternal", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isInternal))
    .function("getInternalConst", static_cast<org::sem::LinkTarget::Internal const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getInternal))
    .function("getInternalMut", static_cast<org::sem::LinkTarget::Internal&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getInternal))
    .function("isFootnote", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isFootnote))
    .function("getFootnoteConst", static_cast<org::sem::LinkTarget::Footnote const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getFootnote))
    .function("getFootnoteMut", static_cast<org::sem::LinkTarget::Footnote&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getFootnote))
    .function("isFile", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isFile))
    .function("getFileConst", static_cast<org::sem::LinkTarget::File const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getFile))
    .function("getFileMut", static_cast<org::sem::LinkTarget::File&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getFile))
    .function("isAttachment", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isAttachment))
    .function("getAttachmentConst", static_cast<org::sem::LinkTarget::Attachment const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getAttachment))
    .function("getAttachmentMut", static_cast<org::sem::LinkTarget::Attachment&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getAttachment))
    .class_function("getKindStatic", static_cast<org::sem::LinkTarget::Kind(*)(org::sem::LinkTarget::Data const&)>(&org::sem::LinkTarget::getKind))
    .function("getKind", static_cast<org::sem::LinkTarget::Kind(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::Raw>("LinkTargetRaw")
    .property("text", &org::sem::LinkTarget::Raw::text)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::Raw::*)(org::sem::LinkTarget::Raw const&) const>(&org::sem::LinkTarget::Raw::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::Id>("LinkTargetId")
    .property("text", &org::sem::LinkTarget::Id::text)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::Id::*)(org::sem::LinkTarget::Id const&) const>(&org::sem::LinkTarget::Id::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::CustomId>("LinkTargetCustomId")
    .property("text", &org::sem::LinkTarget::CustomId::text)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::CustomId::*)(org::sem::LinkTarget::CustomId const&) const>(&org::sem::LinkTarget::CustomId::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::SubtreeTitle>("LinkTargetSubtreeTitle")
    .property("title", &org::sem::LinkTarget::SubtreeTitle::title)
    .property("level", &org::sem::LinkTarget::SubtreeTitle::level)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::SubtreeTitle::*)(org::sem::LinkTarget::SubtreeTitle const&) const>(&org::sem::LinkTarget::SubtreeTitle::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::Person>("LinkTargetPerson")
    .property("name", &org::sem::LinkTarget::Person::name)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::Person::*)(org::sem::LinkTarget::Person const&) const>(&org::sem::LinkTarget::Person::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::UserProtocol>("LinkTargetUserProtocol")
    .property("protocol", &org::sem::LinkTarget::UserProtocol::protocol)
    .property("target", &org::sem::LinkTarget::UserProtocol::target)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::UserProtocol::*)(org::sem::LinkTarget::UserProtocol const&) const>(&org::sem::LinkTarget::UserProtocol::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::Internal>("LinkTargetInternal")
    .property("target", &org::sem::LinkTarget::Internal::target)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::Internal::*)(org::sem::LinkTarget::Internal const&) const>(&org::sem::LinkTarget::Internal::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::Footnote>("LinkTargetFootnote")
    .property("target", &org::sem::LinkTarget::Footnote::target)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::Footnote::*)(org::sem::LinkTarget::Footnote const&) const>(&org::sem::LinkTarget::Footnote::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::File>("LinkTargetFile")
    .property("file", &org::sem::LinkTarget::File::file)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::File::*)(org::sem::LinkTarget::File const&) const>(&org::sem::LinkTarget::File::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::LinkTarget::Attachment>("LinkTargetAttachment")
    .property("file", &org::sem::LinkTarget::Attachment::file)
    .function("__eq__", static_cast<bool(org::sem::LinkTarget::Attachment::*)(org::sem::LinkTarget::Attachment const&) const>(&org::sem::LinkTarget::Attachment::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::LinkTarget::Kind>("LinkTargetKind");
  emscripten::class_<org::sem::SubtreeLogHead>("SubtreeLogHead")
    .property("log", &org::sem::SubtreeLogHead::log)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::*)(org::sem::SubtreeLogHead const&) const>(&org::sem::SubtreeLogHead::operator==))
    .function("isPriority", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isPriority))
    .function("getPriorityConst", static_cast<org::sem::SubtreeLogHead::Priority const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getPriority))
    .function("getPriorityMut", static_cast<org::sem::SubtreeLogHead::Priority&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getPriority))
    .function("isNote", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isNote))
    .function("getNoteConst", static_cast<org::sem::SubtreeLogHead::Note const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getNote))
    .function("getNoteMut", static_cast<org::sem::SubtreeLogHead::Note&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getNote))
    .function("isRefile", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isRefile))
    .function("getRefileConst", static_cast<org::sem::SubtreeLogHead::Refile const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getRefile))
    .function("getRefileMut", static_cast<org::sem::SubtreeLogHead::Refile&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getRefile))
    .function("isClock", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isClock))
    .function("getClockConst", static_cast<org::sem::SubtreeLogHead::Clock const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getClock))
    .function("getClockMut", static_cast<org::sem::SubtreeLogHead::Clock&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getClock))
    .function("isState", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isState))
    .function("getStateConst", static_cast<org::sem::SubtreeLogHead::State const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getState))
    .function("getStateMut", static_cast<org::sem::SubtreeLogHead::State&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getState))
    .function("isDeadline", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isDeadline))
    .function("getDeadlineConst", static_cast<org::sem::SubtreeLogHead::Deadline const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getDeadline))
    .function("getDeadlineMut", static_cast<org::sem::SubtreeLogHead::Deadline&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getDeadline))
    .function("isSchedule", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isSchedule))
    .function("getScheduleConst", static_cast<org::sem::SubtreeLogHead::Schedule const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getSchedule))
    .function("getScheduleMut", static_cast<org::sem::SubtreeLogHead::Schedule&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getSchedule))
    .function("isTag", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isTag))
    .function("getTagConst", static_cast<org::sem::SubtreeLogHead::Tag const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getTag))
    .function("getTagMut", static_cast<org::sem::SubtreeLogHead::Tag&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getTag))
    .function("isUnknown", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isUnknown))
    .function("getUnknownConst", static_cast<org::sem::SubtreeLogHead::Unknown const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getUnknown))
    .function("getUnknownMut", static_cast<org::sem::SubtreeLogHead::Unknown&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getUnknown))
    .class_function("getLogKindStatic", static_cast<org::sem::SubtreeLogHead::Kind(*)(org::sem::SubtreeLogHead::LogEntry const&)>(&org::sem::SubtreeLogHead::getLogKind))
    .function("getLogKind", static_cast<org::sem::SubtreeLogHead::Kind(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getLogKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreeLogHead::Priority>("SubtreeLogHeadPriority")
    .property("oldPriority", &org::sem::SubtreeLogHead::Priority::oldPriority)
    .property("newPriority", &org::sem::SubtreeLogHead::Priority::newPriority)
    .property("on", &org::sem::SubtreeLogHead::Priority::on)
    .property("action", &org::sem::SubtreeLogHead::Priority::action)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::Priority::*)(org::sem::SubtreeLogHead::Priority const&) const>(&org::sem::SubtreeLogHead::Priority::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::SubtreeLogHead::Priority::Action>("SubtreeLogHeadPriorityAction");
  emscripten::class_<org::sem::SubtreeLogHead::Note>("SubtreeLogHeadNote")
    .property("on", &org::sem::SubtreeLogHead::Note::on)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::Note::*)(org::sem::SubtreeLogHead::Note const&) const>(&org::sem::SubtreeLogHead::Note::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreeLogHead::Refile>("SubtreeLogHeadRefile")
    .property("on", &org::sem::SubtreeLogHead::Refile::on)
    .property("from", &org::sem::SubtreeLogHead::Refile::from)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::Refile::*)(org::sem::SubtreeLogHead::Refile const&) const>(&org::sem::SubtreeLogHead::Refile::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreeLogHead::Clock>("SubtreeLogHeadClock")
    .property("from", &org::sem::SubtreeLogHead::Clock::from)
    .property("to", &org::sem::SubtreeLogHead::Clock::to)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::Clock::*)(org::sem::SubtreeLogHead::Clock const&) const>(&org::sem::SubtreeLogHead::Clock::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreeLogHead::State>("SubtreeLogHeadState")
    .property("from", &org::sem::SubtreeLogHead::State::from)
    .property("to", &org::sem::SubtreeLogHead::State::to)
    .property("on", &org::sem::SubtreeLogHead::State::on)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::State::*)(org::sem::SubtreeLogHead::State const&) const>(&org::sem::SubtreeLogHead::State::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreeLogHead::Deadline>("SubtreeLogHeadDeadline")
    .property("from", &org::sem::SubtreeLogHead::Deadline::from)
    .property("to", &org::sem::SubtreeLogHead::Deadline::to)
    .property("on", &org::sem::SubtreeLogHead::Deadline::on)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::Deadline::*)(org::sem::SubtreeLogHead::Deadline const&) const>(&org::sem::SubtreeLogHead::Deadline::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreeLogHead::Schedule>("SubtreeLogHeadSchedule")
    .property("from", &org::sem::SubtreeLogHead::Schedule::from)
    .property("to", &org::sem::SubtreeLogHead::Schedule::to)
    .property("on", &org::sem::SubtreeLogHead::Schedule::on)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::Schedule::*)(org::sem::SubtreeLogHead::Schedule const&) const>(&org::sem::SubtreeLogHead::Schedule::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::SubtreeLogHead::Tag>("SubtreeLogHeadTag")
    .property("on", &org::sem::SubtreeLogHead::Tag::on)
    .property("tag", &org::sem::SubtreeLogHead::Tag::tag)
    .property("added", &org::sem::SubtreeLogHead::Tag::added)
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::Tag::*)(org::sem::SubtreeLogHead::Tag const&) const>(&org::sem::SubtreeLogHead::Tag::operator==))
    .constructor<>()
    ;
}

void subdivide_3(org::bind::js::type_registration_guard& g) {
  emscripten::class_<org::sem::SubtreeLogHead::Unknown>("SubtreeLogHeadUnknown")
    .function("__eq__", static_cast<bool(org::sem::SubtreeLogHead::Unknown::*)(org::sem::SubtreeLogHead::Unknown const&) const>(&org::sem::SubtreeLogHead::Unknown::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::SubtreeLogHead::Kind>("SubtreeLogHeadKind");
  emscripten::class_<org::sem::SubtreeCompletion>("SubtreeCompletion")
    .property("done", &org::sem::SubtreeCompletion::done)
    .property("full", &org::sem::SubtreeCompletion::full)
    .property("isPercent", &org::sem::SubtreeCompletion::isPercent)
    .function("__eq__", static_cast<bool(org::sem::SubtreeCompletion::*)(org::sem::SubtreeCompletion const&) const>(&org::sem::SubtreeCompletion::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::AttrList>("AttrList")
    .property("items", &org::sem::AttrList::items)
    .function("__eq__", static_cast<bool(org::sem::AttrList::*)(org::sem::AttrList const&) const>(&org::sem::AttrList::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::AttrGroup>("AttrGroup")
    .property("positional", &org::sem::AttrGroup::positional)
    .property("named", &org::sem::AttrGroup::named)
    .function("getFlatArgs", static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getFlatArgs))
    .function("getAttrs", static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::AttrGroup::getAttrs))
    .function("setNamedAttr", static_cast<void(org::sem::AttrGroup::*)(hstd::Str const&, hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setNamedAttr))
    .function("setPositionalAttr", static_cast<void(org::sem::AttrGroup::*)(hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setPositionalAttr))
    .function("getPositionalSize", static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getPositionalSize))
    .function("getNamedSize", static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getNamedSize))
    .function("isEmpty", static_cast<bool(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::isEmpty))
    .function("getAll", static_cast<org::sem::AttrList(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getAll))
    .function("atPositional", static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::atPositional))
    .function("getPositional", static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::getPositional))
    .function("atNamed", static_cast<org::sem::AttrList const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atNamed))
    .function("getNamed", static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getNamed))
    .function("atFirstNamed", static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstNamed))
    .function("getFirstNamed", static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstNamed))
    .function("atVarNamed", static_cast<org::sem::AttrList(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atVarNamed))
    .function("getVarNamed", static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getVarNamed))
    .function("atFirstVarNamed", static_cast<org::sem::AttrValue(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstVarNamed))
    .function("getFirstVarNamed", static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstVarNamed))
    .function("__eq__", static_cast<bool(org::sem::AttrGroup::*)(org::sem::AttrGroup const&) const>(&org::sem::AttrGroup::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::OrgCodeEvalInput>("OrgCodeEvalInput")
    .property("blockAttrs", &org::sem::OrgCodeEvalInput::blockAttrs)
    .property("tangledCode", &org::sem::OrgCodeEvalInput::tangledCode)
    .property("exportType", &org::sem::OrgCodeEvalInput::exportType)
    .property("resultType", &org::sem::OrgCodeEvalInput::resultType)
    .property("resultFormat", &org::sem::OrgCodeEvalInput::resultFormat)
    .property("resultHandling", &org::sem::OrgCodeEvalInput::resultHandling)
    .property("language", &org::sem::OrgCodeEvalInput::language)
    .property("argList", &org::sem::OrgCodeEvalInput::argList)
    .function("__eq__", static_cast<bool(org::sem::OrgCodeEvalInput::*)(org::sem::OrgCodeEvalInput const&) const>(&org::sem::OrgCodeEvalInput::operator==))
    .function("getVariable", static_cast<hstd::Opt<org::sem::OrgCodeEvalInput::Var>(org::sem::OrgCodeEvalInput::*)(hstd::Str const&) const>(&org::sem::OrgCodeEvalInput::getVariable))
    .constructor<>()
    ;
  emscripten::class_<org::sem::OrgCodeEvalInput::Var>("OrgCodeEvalInputVar")
    .property("name", &org::sem::OrgCodeEvalInput::Var::name)
    .property("value", &org::sem::OrgCodeEvalInput::Var::value)
    .function("__eq__", static_cast<bool(org::sem::OrgCodeEvalInput::Var::*)(org::sem::OrgCodeEvalInput::Var const&) const>(&org::sem::OrgCodeEvalInput::Var::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::OrgCodeEvalInput::ResultType>("OrgCodeEvalInputResultType");
  org::bind::js::bind_enum<org::sem::OrgCodeEvalInput::ResultFormat>("OrgCodeEvalInputResultFormat");
  org::bind::js::bind_enum<org::sem::OrgCodeEvalInput::ResultHandling>("OrgCodeEvalInputResultHandling");
  emscripten::class_<org::sem::OrgCodeEvalOutput>("OrgCodeEvalOutput")
    .property("stdoutText", &org::sem::OrgCodeEvalOutput::stdoutText)
    .property("stderrText", &org::sem::OrgCodeEvalOutput::stderrText)
    .property("code", &org::sem::OrgCodeEvalOutput::code)
    .property("cmd", &org::sem::OrgCodeEvalOutput::cmd)
    .property("args", &org::sem::OrgCodeEvalOutput::args)
    .property("cwd", &org::sem::OrgCodeEvalOutput::cwd)
    .property("appliedHeaderArg", &org::sem::OrgCodeEvalOutput::appliedHeaderArg)
    .function("__eq__", static_cast<bool(org::sem::OrgCodeEvalOutput::*)(org::sem::OrgCodeEvalOutput const&) const>(&org::sem::OrgCodeEvalOutput::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::ColumnView>("ColumnView")
    .property("columns", &org::sem::ColumnView::columns)
    .function("__eq__", static_cast<bool(org::sem::ColumnView::*)(org::sem::ColumnView const&) const>(&org::sem::ColumnView::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::ColumnView::Summary>("ColumnViewSummary")
    .property("data", &org::sem::ColumnView::Summary::data)
    .function("__eq__", static_cast<bool(org::sem::ColumnView::Summary::*)(org::sem::ColumnView::Summary const&) const>(&org::sem::ColumnView::Summary::operator==))
    .function("isCheckboxAggregate", static_cast<bool(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::isCheckboxAggregate))
    .function("getCheckboxAggregateConst", static_cast<org::sem::ColumnView::Summary::CheckboxAggregate const&(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getCheckboxAggregate))
    .function("getCheckboxAggregateMut", static_cast<org::sem::ColumnView::Summary::CheckboxAggregate&(org::sem::ColumnView::Summary::*)()>(&org::sem::ColumnView::Summary::getCheckboxAggregate))
    .function("isMathAggregate", static_cast<bool(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::isMathAggregate))
    .function("getMathAggregateConst", static_cast<org::sem::ColumnView::Summary::MathAggregate const&(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getMathAggregate))
    .function("getMathAggregateMut", static_cast<org::sem::ColumnView::Summary::MathAggregate&(org::sem::ColumnView::Summary::*)()>(&org::sem::ColumnView::Summary::getMathAggregate))
    .class_function("getKindStatic", static_cast<org::sem::ColumnView::Summary::Kind(*)(org::sem::ColumnView::Summary::Data const&)>(&org::sem::ColumnView::Summary::getKind))
    .function("getKind", static_cast<org::sem::ColumnView::Summary::Kind(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::ColumnView::Summary::CheckboxAggregate>("ColumnViewSummaryCheckboxAggregate")
    .property("kind", &org::sem::ColumnView::Summary::CheckboxAggregate::kind)
    .function("__eq__", static_cast<bool(org::sem::ColumnView::Summary::CheckboxAggregate::*)(org::sem::ColumnView::Summary::CheckboxAggregate const&) const>(&org::sem::ColumnView::Summary::CheckboxAggregate::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::ColumnView::Summary::CheckboxAggregate::Kind>("ColumnViewSummaryCheckboxAggregateKind");
  emscripten::class_<org::sem::ColumnView::Summary::MathAggregate>("ColumnViewSummaryMathAggregate")
    .property("kind", &org::sem::ColumnView::Summary::MathAggregate::kind)
    .property("formatDigits", &org::sem::ColumnView::Summary::MathAggregate::formatDigits)
    .property("formatPrecision", &org::sem::ColumnView::Summary::MathAggregate::formatPrecision)
    .function("__eq__", static_cast<bool(org::sem::ColumnView::Summary::MathAggregate::*)(org::sem::ColumnView::Summary::MathAggregate const&) const>(&org::sem::ColumnView::Summary::MathAggregate::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::ColumnView::Summary::MathAggregate::Kind>("ColumnViewSummaryMathAggregateKind");
  org::bind::js::bind_enum<org::sem::ColumnView::Summary::Kind>("ColumnViewSummaryKind");
  emscripten::class_<org::sem::ColumnView::Column>("ColumnViewColumn")
    .property("summary", &org::sem::ColumnView::Column::summary)
    .property("width", &org::sem::ColumnView::Column::width)
    .property("property", &org::sem::ColumnView::Column::property)
    .property("propertyTitle", &org::sem::ColumnView::Column::propertyTitle)
    .function("__eq__", static_cast<bool(org::sem::ColumnView::Column::*)(org::sem::ColumnView::Column const&) const>(&org::sem::ColumnView::Column::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::BlockCodeLine>("BlockCodeLine")
    .property("parts", &org::sem::BlockCodeLine::parts)
    .function("__eq__", static_cast<bool(org::sem::BlockCodeLine::*)(org::sem::BlockCodeLine const&) const>(&org::sem::BlockCodeLine::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::BlockCodeLine::Part>("BlockCodeLinePart")
    .property("data", &org::sem::BlockCodeLine::Part::data)
    .function("__eq__", static_cast<bool(org::sem::BlockCodeLine::Part::*)(org::sem::BlockCodeLine::Part const&) const>(&org::sem::BlockCodeLine::Part::operator==))
    .function("isRaw", static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isRaw))
    .function("getRawConst", static_cast<org::sem::BlockCodeLine::Part::Raw const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getRaw))
    .function("getRawMut", static_cast<org::sem::BlockCodeLine::Part::Raw&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getRaw))
    .function("isCallout", static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isCallout))
    .function("getCalloutConst", static_cast<org::sem::BlockCodeLine::Part::Callout const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getCallout))
    .function("getCalloutMut", static_cast<org::sem::BlockCodeLine::Part::Callout&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getCallout))
    .function("isTangle", static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isTangle))
    .function("getTangleConst", static_cast<org::sem::BlockCodeLine::Part::Tangle const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getTangle))
    .function("getTangleMut", static_cast<org::sem::BlockCodeLine::Part::Tangle&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getTangle))
    .class_function("getKindStatic", static_cast<org::sem::BlockCodeLine::Part::Kind(*)(org::sem::BlockCodeLine::Part::Data const&)>(&org::sem::BlockCodeLine::Part::getKind))
    .function("getKind", static_cast<org::sem::BlockCodeLine::Part::Kind(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::BlockCodeLine::Part::Raw>("BlockCodeLinePartRaw")
    .property("code", &org::sem::BlockCodeLine::Part::Raw::code)
    .function("__eq__", static_cast<bool(org::sem::BlockCodeLine::Part::Raw::*)(org::sem::BlockCodeLine::Part::Raw const&) const>(&org::sem::BlockCodeLine::Part::Raw::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::BlockCodeLine::Part::Callout>("BlockCodeLinePartCallout")
    .property("name", &org::sem::BlockCodeLine::Part::Callout::name)
    .function("__eq__", static_cast<bool(org::sem::BlockCodeLine::Part::Callout::*)(org::sem::BlockCodeLine::Part::Callout const&) const>(&org::sem::BlockCodeLine::Part::Callout::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::BlockCodeLine::Part::Tangle>("BlockCodeLinePartTangle")
    .property("target", &org::sem::BlockCodeLine::Part::Tangle::target)
    .function("__eq__", static_cast<bool(org::sem::BlockCodeLine::Part::Tangle::*)(org::sem::BlockCodeLine::Part::Tangle const&) const>(&org::sem::BlockCodeLine::Part::Tangle::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::BlockCodeLine::Part::Kind>("BlockCodeLinePartKind");
  emscripten::class_<org::sem::DocumentExportConfig>("DocumentExportConfig")
    .property("inlinetasks", &org::sem::DocumentExportConfig::inlinetasks)
    .property("footnotes", &org::sem::DocumentExportConfig::footnotes)
    .property("clock", &org::sem::DocumentExportConfig::clock)
    .property("author", &org::sem::DocumentExportConfig::author)
    .property("emphasis", &org::sem::DocumentExportConfig::emphasis)
    .property("specialStrings", &org::sem::DocumentExportConfig::specialStrings)
    .property("propertyDrawers", &org::sem::DocumentExportConfig::propertyDrawers)
    .property("statisticsCookies", &org::sem::DocumentExportConfig::statisticsCookies)
    .property("todoText", &org::sem::DocumentExportConfig::todoText)
    .property("smartQuotes", &org::sem::DocumentExportConfig::smartQuotes)
    .property("fixedWidth", &org::sem::DocumentExportConfig::fixedWidth)
    .property("timestamps", &org::sem::DocumentExportConfig::timestamps)
    .property("preserveBreaks", &org::sem::DocumentExportConfig::preserveBreaks)
    .property("subSuperscripts", &org::sem::DocumentExportConfig::subSuperscripts)
    .property("expandLinks", &org::sem::DocumentExportConfig::expandLinks)
    .property("creator", &org::sem::DocumentExportConfig::creator)
    .property("drawers", &org::sem::DocumentExportConfig::drawers)
    .property("date", &org::sem::DocumentExportConfig::date)
    .property("entities", &org::sem::DocumentExportConfig::entities)
    .property("email", &org::sem::DocumentExportConfig::email)
    .property("sectionNumbers", &org::sem::DocumentExportConfig::sectionNumbers)
    .property("planning", &org::sem::DocumentExportConfig::planning)
    .property("priority", &org::sem::DocumentExportConfig::priority)
    .property("latex", &org::sem::DocumentExportConfig::latex)
    .property("timestamp", &org::sem::DocumentExportConfig::timestamp)
    .property("title", &org::sem::DocumentExportConfig::title)
    .property("tables", &org::sem::DocumentExportConfig::tables)
    .property("headlineLevels", &org::sem::DocumentExportConfig::headlineLevels)
    .property("brokenLinks", &org::sem::DocumentExportConfig::brokenLinks)
    .property("tocExport", &org::sem::DocumentExportConfig::tocExport)
    .property("tagExport", &org::sem::DocumentExportConfig::tagExport)
    .property("taskFiltering", &org::sem::DocumentExportConfig::taskFiltering)
    .property("archivedTrees", &org::sem::DocumentExportConfig::archivedTrees)
    .property("data", &org::sem::DocumentExportConfig::data)
    .function("__eq__", static_cast<bool(org::sem::DocumentExportConfig::*)(org::sem::DocumentExportConfig const&) const>(&org::sem::DocumentExportConfig::operator==))
    .function("isDoExport", static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isDoExport))
    .function("getDoExportConst", static_cast<org::sem::DocumentExportConfig::DoExport const&(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getDoExport))
    .function("getDoExportMut", static_cast<org::sem::DocumentExportConfig::DoExport&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getDoExport))
    .function("isExportFixed", static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isExportFixed))
    .function("getExportFixedConst", static_cast<org::sem::DocumentExportConfig::ExportFixed const&(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getExportFixed))
    .function("getExportFixedMut", static_cast<org::sem::DocumentExportConfig::ExportFixed&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getExportFixed))
    .class_function("getTocExportKindStatic", static_cast<org::sem::DocumentExportConfig::TocExportKind(*)(org::sem::DocumentExportConfig::TocExport const&)>(&org::sem::DocumentExportConfig::getTocExportKind))
    .function("getTocExportKind", static_cast<org::sem::DocumentExportConfig::TocExportKind(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getTocExportKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::DocumentExportConfig::TaskExport>("DocumentExportConfigTaskExport")
    .property("taskWhitelist", &org::sem::DocumentExportConfig::TaskExport::taskWhitelist)
    .function("__eq__", static_cast<bool(org::sem::DocumentExportConfig::TaskExport::*)(org::sem::DocumentExportConfig::TaskExport const&) const>(&org::sem::DocumentExportConfig::TaskExport::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::DocumentExportConfig::TagExport>("DocumentExportConfigTagExport");
  org::bind::js::bind_enum<org::sem::DocumentExportConfig::TaskFiltering>("DocumentExportConfigTaskFiltering");
  org::bind::js::bind_enum<org::sem::DocumentExportConfig::BrokenLinks>("DocumentExportConfigBrokenLinks");
  org::bind::js::bind_enum<org::sem::DocumentExportConfig::ArchivedTrees>("DocumentExportConfigArchivedTrees");
  emscripten::class_<org::sem::DocumentExportConfig::DoExport>("DocumentExportConfigDoExport")
    .property("exportToc", &org::sem::DocumentExportConfig::DoExport::exportToc)
    .function("__eq__", static_cast<bool(org::sem::DocumentExportConfig::DoExport::*)(org::sem::DocumentExportConfig::DoExport const&) const>(&org::sem::DocumentExportConfig::DoExport::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::DocumentExportConfig::ExportFixed>("DocumentExportConfigExportFixed")
    .property("exportLevels", &org::sem::DocumentExportConfig::ExportFixed::exportLevels)
    .function("__eq__", static_cast<bool(org::sem::DocumentExportConfig::ExportFixed::*)(org::sem::DocumentExportConfig::ExportFixed const&) const>(&org::sem::DocumentExportConfig::ExportFixed::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::DocumentExportConfig::TocExportKind>("DocumentExportConfigTocExportKind");
  emscripten::class_<org::sem::SubtreePeriod>("SubtreePeriod")
    .property("kind", &org::sem::SubtreePeriod::kind)
    .property("from", &org::sem::SubtreePeriod::from)
    .property("to", &org::sem::SubtreePeriod::to)
    .function("__eq__", static_cast<bool(org::sem::SubtreePeriod::*)(org::sem::SubtreePeriod const&) const>(&org::sem::SubtreePeriod::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::SubtreePeriod::Kind>("SubtreePeriodKind");
  emscripten::class_<org::sem::NamedProperty>("NamedProperty")
    .property("data", &org::sem::NamedProperty::data)
    .function("isMatching", static_cast<bool(org::sem::NamedProperty::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::NamedProperty::isMatching))
    .function("getName", static_cast<hstd::Str(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getName))
    .function("getSubKind", static_cast<hstd::Opt<hstd::Str>(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getSubKind))
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::*)(org::sem::NamedProperty const&) const>(&org::sem::NamedProperty::operator==))
    .function("isNonblocking", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isNonblocking))
    .function("getNonblockingConst", static_cast<org::sem::NamedProperty::Nonblocking const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getNonblocking))
    .function("getNonblockingMut", static_cast<org::sem::NamedProperty::Nonblocking&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getNonblocking))
    .function("isArchiveTime", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTime))
    .function("getArchiveTimeConst", static_cast<org::sem::NamedProperty::ArchiveTime const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTime))
    .function("getArchiveTimeMut", static_cast<org::sem::NamedProperty::ArchiveTime&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTime))
    .function("isArchiveFile", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveFile))
    .function("getArchiveFileConst", static_cast<org::sem::NamedProperty::ArchiveFile const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveFile))
    .function("getArchiveFileMut", static_cast<org::sem::NamedProperty::ArchiveFile&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveFile))
    .function("isArchiveOlpath", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveOlpath))
    .function("getArchiveOlpathConst", static_cast<org::sem::NamedProperty::ArchiveOlpath const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveOlpath))
    .function("getArchiveOlpathMut", static_cast<org::sem::NamedProperty::ArchiveOlpath&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveOlpath))
    .function("isArchiveTarget", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTarget))
    .function("getArchiveTargetConst", static_cast<org::sem::NamedProperty::ArchiveTarget const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTarget))
    .function("getArchiveTargetMut", static_cast<org::sem::NamedProperty::ArchiveTarget&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTarget))
    .function("isArchiveCategory", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveCategory))
    .function("getArchiveCategoryConst", static_cast<org::sem::NamedProperty::ArchiveCategory const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveCategory))
    .function("getArchiveCategoryMut", static_cast<org::sem::NamedProperty::ArchiveCategory&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveCategory))
    .function("isArchiveTodo", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTodo))
    .function("getArchiveTodoConst", static_cast<org::sem::NamedProperty::ArchiveTodo const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getArchiveTodo))
    .function("getArchiveTodoMut", static_cast<org::sem::NamedProperty::ArchiveTodo&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTodo))
    .function("isTrigger", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isTrigger))
    .function("getTriggerConst", static_cast<org::sem::NamedProperty::Trigger const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getTrigger))
    .function("getTriggerMut", static_cast<org::sem::NamedProperty::Trigger&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getTrigger))
    .function("isExportLatexClass", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexClass))
    .function("getExportLatexClassConst", static_cast<org::sem::NamedProperty::ExportLatexClass const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexClass))
    .function("getExportLatexClassMut", static_cast<org::sem::NamedProperty::ExportLatexClass&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexClass))
    .function("isCookieData", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCookieData))
    .function("getCookieDataConst", static_cast<org::sem::NamedProperty::CookieData const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCookieData))
    .function("getCookieDataMut", static_cast<org::sem::NamedProperty::CookieData&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCookieData))
    .function("isExportLatexClassOptions", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexClassOptions))
    .function("getExportLatexClassOptionsConst", static_cast<org::sem::NamedProperty::ExportLatexClassOptions const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexClassOptions))
    .function("getExportLatexClassOptionsMut", static_cast<org::sem::NamedProperty::ExportLatexClassOptions&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexClassOptions))
    .function("isExportLatexHeader", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexHeader))
    .function("getExportLatexHeaderConst", static_cast<org::sem::NamedProperty::ExportLatexHeader const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexHeader))
    .function("getExportLatexHeaderMut", static_cast<org::sem::NamedProperty::ExportLatexHeader&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexHeader))
    .function("isExportLatexCompiler", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexCompiler))
    .function("getExportLatexCompilerConst", static_cast<org::sem::NamedProperty::ExportLatexCompiler const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportLatexCompiler))
    .function("getExportLatexCompilerMut", static_cast<org::sem::NamedProperty::ExportLatexCompiler&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexCompiler))
    .function("isOrdered", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isOrdered))
    .function("getOrderedConst", static_cast<org::sem::NamedProperty::Ordered const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getOrdered))
    .function("getOrderedMut", static_cast<org::sem::NamedProperty::Ordered&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getOrdered))
    .function("isEffort", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isEffort))
    .function("getEffortConst", static_cast<org::sem::NamedProperty::Effort const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getEffort))
    .function("getEffortMut", static_cast<org::sem::NamedProperty::Effort&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getEffort))
    .function("isVisibility", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isVisibility))
    .function("getVisibilityConst", static_cast<org::sem::NamedProperty::Visibility const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getVisibility))
    .function("getVisibilityMut", static_cast<org::sem::NamedProperty::Visibility&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getVisibility))
    .function("isExportOptions", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportOptions))
    .function("getExportOptionsConst", static_cast<org::sem::NamedProperty::ExportOptions const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getExportOptions))
    .function("getExportOptionsMut", static_cast<org::sem::NamedProperty::ExportOptions&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportOptions))
    .function("isBlocker", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isBlocker))
    .function("getBlockerConst", static_cast<org::sem::NamedProperty::Blocker const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getBlocker))
    .function("getBlockerMut", static_cast<org::sem::NamedProperty::Blocker&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getBlocker))
    .function("isUnnumbered", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isUnnumbered))
    .function("getUnnumberedConst", static_cast<org::sem::NamedProperty::Unnumbered const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getUnnumbered))
    .function("getUnnumberedMut", static_cast<org::sem::NamedProperty::Unnumbered&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getUnnumbered))
    .function("isCreated", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCreated))
    .function("getCreatedConst", static_cast<org::sem::NamedProperty::Created const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCreated))
    .function("getCreatedMut", static_cast<org::sem::NamedProperty::Created&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCreated))
    .function("isRadioId", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isRadioId))
    .function("getRadioIdConst", static_cast<org::sem::NamedProperty::RadioId const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getRadioId))
    .function("getRadioIdMut", static_cast<org::sem::NamedProperty::RadioId&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getRadioId))
    .function("isHashtagDef", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isHashtagDef))
    .function("getHashtagDefConst", static_cast<org::sem::NamedProperty::HashtagDef const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getHashtagDef))
    .function("getHashtagDefMut", static_cast<org::sem::NamedProperty::HashtagDef&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getHashtagDef))
    .function("isCustomArgs", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomArgs))
    .function("getCustomArgsConst", static_cast<org::sem::NamedProperty::CustomArgs const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomArgs))
    .function("getCustomArgsMut", static_cast<org::sem::NamedProperty::CustomArgs&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomArgs))
    .function("isCustomRaw", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomRaw))
    .function("getCustomRawConst", static_cast<org::sem::NamedProperty::CustomRaw const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomRaw))
    .function("getCustomRawMut", static_cast<org::sem::NamedProperty::CustomRaw&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomRaw))
    .function("isCustomId", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomId))
    .function("getCustomIdConst", static_cast<org::sem::NamedProperty::CustomId const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomId))
    .function("getCustomIdMut", static_cast<org::sem::NamedProperty::CustomId&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomId))
    .function("isCustomSubtreeJson", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeJson))
    .function("getCustomSubtreeJsonConst", static_cast<org::sem::NamedProperty::CustomSubtreeJson const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomSubtreeJson))
    .function("getCustomSubtreeJsonMut", static_cast<org::sem::NamedProperty::CustomSubtreeJson&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeJson))
    .function("isCustomSubtreeFlags", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeFlags))
    .function("getCustomSubtreeFlagsConst", static_cast<org::sem::NamedProperty::CustomSubtreeFlags const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getCustomSubtreeFlags))
    .function("getCustomSubtreeFlagsMut", static_cast<org::sem::NamedProperty::CustomSubtreeFlags&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeFlags))
    .class_function("getKindStatic", static_cast<org::sem::NamedProperty::Kind(*)(org::sem::NamedProperty::Data const&)>(&org::sem::NamedProperty::getKind))
    .function("getKind", static_cast<org::sem::NamedProperty::Kind(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::Nonblocking>("NamedPropertyNonblocking")
    .property("isBlocking", &org::sem::NamedProperty::Nonblocking::isBlocking)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::Nonblocking::*)(org::sem::NamedProperty::Nonblocking const&) const>(&org::sem::NamedProperty::Nonblocking::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ArchiveTime>("NamedPropertyArchiveTime")
    .property("time", &org::sem::NamedProperty::ArchiveTime::time)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ArchiveTime::*)(org::sem::NamedProperty::ArchiveTime const&) const>(&org::sem::NamedProperty::ArchiveTime::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ArchiveFile>("NamedPropertyArchiveFile")
    .property("file", &org::sem::NamedProperty::ArchiveFile::file)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ArchiveFile::*)(org::sem::NamedProperty::ArchiveFile const&) const>(&org::sem::NamedProperty::ArchiveFile::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ArchiveOlpath>("NamedPropertyArchiveOlpath")
    .property("path", &org::sem::NamedProperty::ArchiveOlpath::path)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ArchiveOlpath::*)(org::sem::NamedProperty::ArchiveOlpath const&) const>(&org::sem::NamedProperty::ArchiveOlpath::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ArchiveTarget>("NamedPropertyArchiveTarget")
    .property("path", &org::sem::NamedProperty::ArchiveTarget::path)
    .property("pattern", &org::sem::NamedProperty::ArchiveTarget::pattern)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ArchiveTarget::*)(org::sem::NamedProperty::ArchiveTarget const&) const>(&org::sem::NamedProperty::ArchiveTarget::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ArchiveCategory>("NamedPropertyArchiveCategory")
    .property("category", &org::sem::NamedProperty::ArchiveCategory::category)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ArchiveCategory::*)(org::sem::NamedProperty::ArchiveCategory const&) const>(&org::sem::NamedProperty::ArchiveCategory::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ArchiveTodo>("NamedPropertyArchiveTodo")
    .property("todo", &org::sem::NamedProperty::ArchiveTodo::todo)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ArchiveTodo::*)(org::sem::NamedProperty::ArchiveTodo const&) const>(&org::sem::NamedProperty::ArchiveTodo::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::Trigger>("NamedPropertyTrigger")
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::Trigger::*)(org::sem::NamedProperty::Trigger const&) const>(&org::sem::NamedProperty::Trigger::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ExportLatexClass>("NamedPropertyExportLatexClass")
    .property("latexClass", &org::sem::NamedProperty::ExportLatexClass::latexClass)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ExportLatexClass::*)(org::sem::NamedProperty::ExportLatexClass const&) const>(&org::sem::NamedProperty::ExportLatexClass::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::CookieData>("NamedPropertyCookieData")
    .property("isRecursive", &org::sem::NamedProperty::CookieData::isRecursive)
    .property("source", &org::sem::NamedProperty::CookieData::source)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::CookieData::*)(org::sem::NamedProperty::CookieData const&) const>(&org::sem::NamedProperty::CookieData::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ExportLatexClassOptions>("NamedPropertyExportLatexClassOptions")
    .property("options", &org::sem::NamedProperty::ExportLatexClassOptions::options)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ExportLatexClassOptions::*)(org::sem::NamedProperty::ExportLatexClassOptions const&) const>(&org::sem::NamedProperty::ExportLatexClassOptions::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ExportLatexHeader>("NamedPropertyExportLatexHeader")
    .property("header", &org::sem::NamedProperty::ExportLatexHeader::header)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ExportLatexHeader::*)(org::sem::NamedProperty::ExportLatexHeader const&) const>(&org::sem::NamedProperty::ExportLatexHeader::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::ExportLatexCompiler>("NamedPropertyExportLatexCompiler")
    .property("compiler", &org::sem::NamedProperty::ExportLatexCompiler::compiler)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ExportLatexCompiler::*)(org::sem::NamedProperty::ExportLatexCompiler const&) const>(&org::sem::NamedProperty::ExportLatexCompiler::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::Ordered>("NamedPropertyOrdered")
    .property("isOrdered", &org::sem::NamedProperty::Ordered::isOrdered)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::Ordered::*)(org::sem::NamedProperty::Ordered const&) const>(&org::sem::NamedProperty::Ordered::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::Effort>("NamedPropertyEffort")
    .property("hours", &org::sem::NamedProperty::Effort::hours)
    .property("minutes", &org::sem::NamedProperty::Effort::minutes)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::Effort::*)(org::sem::NamedProperty::Effort const&) const>(&org::sem::NamedProperty::Effort::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::Visibility>("NamedPropertyVisibility")
    .property("level", &org::sem::NamedProperty::Visibility::level)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::Visibility::*)(org::sem::NamedProperty::Visibility const&) const>(&org::sem::NamedProperty::Visibility::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::NamedProperty::Visibility::Level>("NamedPropertyVisibilityLevel");
  emscripten::class_<org::sem::NamedProperty::ExportOptions>("NamedPropertyExportOptions")
    .property("backend", &org::sem::NamedProperty::ExportOptions::backend)
    .property("values", &org::sem::NamedProperty::ExportOptions::values)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::ExportOptions::*)(org::sem::NamedProperty::ExportOptions const&) const>(&org::sem::NamedProperty::ExportOptions::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::Blocker>("NamedPropertyBlocker")
    .property("blockers", &org::sem::NamedProperty::Blocker::blockers)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::Blocker::*)(org::sem::NamedProperty::Blocker const&) const>(&org::sem::NamedProperty::Blocker::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::Unnumbered>("NamedPropertyUnnumbered")
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::Unnumbered::*)(org::sem::NamedProperty::Unnumbered const&) const>(&org::sem::NamedProperty::Unnumbered::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::Created>("NamedPropertyCreated")
    .property("time", &org::sem::NamedProperty::Created::time)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::Created::*)(org::sem::NamedProperty::Created const&) const>(&org::sem::NamedProperty::Created::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::RadioId>("NamedPropertyRadioId")
    .property("words", &org::sem::NamedProperty::RadioId::words)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::RadioId::*)(org::sem::NamedProperty::RadioId const&) const>(&org::sem::NamedProperty::RadioId::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::HashtagDef>("NamedPropertyHashtagDef")
    .property("hashtag", &org::sem::NamedProperty::HashtagDef::hashtag)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::HashtagDef::*)(org::sem::NamedProperty::HashtagDef const&) const>(&org::sem::NamedProperty::HashtagDef::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::CustomArgs>("NamedPropertyCustomArgs")
    .property("name", &org::sem::NamedProperty::CustomArgs::name)
    .property("sub", &org::sem::NamedProperty::CustomArgs::sub)
    .property("attrs", &org::sem::NamedProperty::CustomArgs::attrs)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::CustomArgs::*)(org::sem::NamedProperty::CustomArgs const&) const>(&org::sem::NamedProperty::CustomArgs::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::CustomRaw>("NamedPropertyCustomRaw")
    .property("name", &org::sem::NamedProperty::CustomRaw::name)
    .property("value", &org::sem::NamedProperty::CustomRaw::value)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::CustomRaw::*)(org::sem::NamedProperty::CustomRaw const&) const>(&org::sem::NamedProperty::CustomRaw::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::CustomId>("NamedPropertyCustomId")
    .property("value", &org::sem::NamedProperty::CustomId::value)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::CustomId::*)(org::sem::NamedProperty::CustomId const&) const>(&org::sem::NamedProperty::CustomId::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::CustomSubtreeJson>("NamedPropertyCustomSubtreeJson")
    .property("name", &org::sem::NamedProperty::CustomSubtreeJson::name)
    .property("value", &org::sem::NamedProperty::CustomSubtreeJson::value)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::CustomSubtreeJson::*)(org::sem::NamedProperty::CustomSubtreeJson const&) const>(&org::sem::NamedProperty::CustomSubtreeJson::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::NamedProperty::CustomSubtreeFlags>("NamedPropertyCustomSubtreeFlags")
    .property("name", &org::sem::NamedProperty::CustomSubtreeFlags::name)
    .property("value", &org::sem::NamedProperty::CustomSubtreeFlags::value)
    .function("__eq__", static_cast<bool(org::sem::NamedProperty::CustomSubtreeFlags::*)(org::sem::NamedProperty::CustomSubtreeFlags const&) const>(&org::sem::NamedProperty::CustomSubtreeFlags::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::NamedProperty::Kind>("NamedPropertyKind");
  emscripten::class_<org::sem::OrgDiagnostics>("OrgDiagnostics")
    .property("data", &org::sem::OrgDiagnostics::data)
    .function("__eq__", static_cast<bool(org::sem::OrgDiagnostics::*)(org::sem::OrgDiagnostics const&) const>(&org::sem::OrgDiagnostics::operator==))
    .function("isParseTokenError", static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isParseTokenError))
    .function("getParseTokenErrorConst", static_cast<org::sem::OrgDiagnostics::ParseTokenError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getParseTokenError))
    .function("getParseTokenErrorMut", static_cast<org::sem::OrgDiagnostics::ParseTokenError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getParseTokenError))
    .function("isParseError", static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isParseError))
    .function("getParseErrorConst", static_cast<org::sem::OrgDiagnostics::ParseError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getParseError))
    .function("getParseErrorMut", static_cast<org::sem::OrgDiagnostics::ParseError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getParseError))
    .function("isIncludeError", static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isIncludeError))
    .function("getIncludeErrorConst", static_cast<org::sem::OrgDiagnostics::IncludeError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getIncludeError))
    .function("getIncludeErrorMut", static_cast<org::sem::OrgDiagnostics::IncludeError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getIncludeError))
    .function("isConvertError", static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isConvertError))
    .function("getConvertErrorConst", static_cast<org::sem::OrgDiagnostics::ConvertError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getConvertError))
    .function("getConvertErrorMut", static_cast<org::sem::OrgDiagnostics::ConvertError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getConvertError))
    .function("isInternalError", static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isInternalError))
    .function("getInternalErrorConst", static_cast<org::sem::OrgDiagnostics::InternalError const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getInternalError))
    .function("getInternalErrorMut", static_cast<org::sem::OrgDiagnostics::InternalError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getInternalError))
    .class_function("getKindStatic", static_cast<org::sem::OrgDiagnostics::Kind(*)(org::sem::OrgDiagnostics::Data const&)>(&org::sem::OrgDiagnostics::getKind))
    .function("getKind", static_cast<org::sem::OrgDiagnostics::Kind(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getKind))
    .constructor<>()
    ;
  emscripten::class_<org::sem::OrgDiagnostics::ParseTokenError>("OrgDiagnosticsParseTokenError")
    .property("brief", &org::sem::OrgDiagnostics::ParseTokenError::brief)
    .property("detail", &org::sem::OrgDiagnostics::ParseTokenError::detail)
    .property("parserFunction", &org::sem::OrgDiagnostics::ParseTokenError::parserFunction)
    .property("parserLine", &org::sem::OrgDiagnostics::ParseTokenError::parserLine)
    .property("tokenKind", &org::sem::OrgDiagnostics::ParseTokenError::tokenKind)
    .property("tokenText", &org::sem::OrgDiagnostics::ParseTokenError::tokenText)
    .property("loc", &org::sem::OrgDiagnostics::ParseTokenError::loc)
    .property("errName", &org::sem::OrgDiagnostics::ParseTokenError::errName)
    .property("errCode", &org::sem::OrgDiagnostics::ParseTokenError::errCode)
    .function("__eq__", static_cast<bool(org::sem::OrgDiagnostics::ParseTokenError::*)(org::sem::OrgDiagnostics::ParseTokenError const&) const>(&org::sem::OrgDiagnostics::ParseTokenError::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::OrgDiagnostics::ParseError>("OrgDiagnosticsParseError")
    .property("brief", &org::sem::OrgDiagnostics::ParseError::brief)
    .property("detail", &org::sem::OrgDiagnostics::ParseError::detail)
    .property("parserFunction", &org::sem::OrgDiagnostics::ParseError::parserFunction)
    .property("parserLine", &org::sem::OrgDiagnostics::ParseError::parserLine)
    .property("errName", &org::sem::OrgDiagnostics::ParseError::errName)
    .property("errCode", &org::sem::OrgDiagnostics::ParseError::errCode)
    .property("loc", &org::sem::OrgDiagnostics::ParseError::loc)
    .function("__eq__", static_cast<bool(org::sem::OrgDiagnostics::ParseError::*)(org::sem::OrgDiagnostics::ParseError const&) const>(&org::sem::OrgDiagnostics::ParseError::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::OrgDiagnostics::IncludeError>("OrgDiagnosticsIncludeError")
    .property("brief", &org::sem::OrgDiagnostics::IncludeError::brief)
    .property("targetPath", &org::sem::OrgDiagnostics::IncludeError::targetPath)
    .property("workingFile", &org::sem::OrgDiagnostics::IncludeError::workingFile)
    .function("__eq__", static_cast<bool(org::sem::OrgDiagnostics::IncludeError::*)(org::sem::OrgDiagnostics::IncludeError const&) const>(&org::sem::OrgDiagnostics::IncludeError::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::OrgDiagnostics::ConvertError>("OrgDiagnosticsConvertError")
    .property("brief", &org::sem::OrgDiagnostics::ConvertError::brief)
    .property("detail", &org::sem::OrgDiagnostics::ConvertError::detail)
    .property("convertFunction", &org::sem::OrgDiagnostics::ConvertError::convertFunction)
    .property("convertLine", &org::sem::OrgDiagnostics::ConvertError::convertLine)
    .property("convertFile", &org::sem::OrgDiagnostics::ConvertError::convertFile)
    .property("errName", &org::sem::OrgDiagnostics::ConvertError::errName)
    .property("errCode", &org::sem::OrgDiagnostics::ConvertError::errCode)
    .property("loc", &org::sem::OrgDiagnostics::ConvertError::loc)
    .function("__eq__", static_cast<bool(org::sem::OrgDiagnostics::ConvertError::*)(org::sem::OrgDiagnostics::ConvertError const&) const>(&org::sem::OrgDiagnostics::ConvertError::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::sem::OrgDiagnostics::InternalError>("OrgDiagnosticsInternalError")
    .property("message", &org::sem::OrgDiagnostics::InternalError::message)
    .property("function", &org::sem::OrgDiagnostics::InternalError::function)
    .property("line", &org::sem::OrgDiagnostics::InternalError::line)
    .property("file", &org::sem::OrgDiagnostics::InternalError::file)
    .property("loc", &org::sem::OrgDiagnostics::InternalError::loc)
    .function("__eq__", static_cast<bool(org::sem::OrgDiagnostics::InternalError::*)(org::sem::OrgDiagnostics::InternalError const&) const>(&org::sem::OrgDiagnostics::InternalError::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::OrgDiagnostics::Kind>("OrgDiagnosticsKind");
  emscripten::class_<org::sem::NoNode /* d_org */, emscripten::base<org::sem::Org>>("NoNode")
    .smart_ptr<org::sem::SemId<org::sem::NoNode /* d_org */>>("NoNode")
    .function("getKind", static_cast<OrgSemKind(org::sem::NoNode /* d_org */::*)() const>(&org::sem::NoNode /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::NoNode /* d_org */>>)
    ;
  emscripten::class_<org::sem::ErrorItem /* d_org */, emscripten::base<org::sem::Org>>("ErrorItem")
    .smart_ptr<org::sem::SemId<org::sem::ErrorItem /* d_org */>>("ErrorItem")
    .property("diag", &org::sem::ErrorItem /* d_org */::diag)
    .function("getKind", static_cast<OrgSemKind(org::sem::ErrorItem /* d_org */::*)() const>(&org::sem::ErrorItem /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::ErrorItem /* d_org */>>)
    ;
  emscripten::class_<org::sem::ErrorGroup /* d_org */, emscripten::base<org::sem::Org>>("ErrorGroup")
    .smart_ptr<org::sem::SemId<org::sem::ErrorGroup /* d_org */>>("ErrorGroup")
    .property("diagnostics", &org::sem::ErrorGroup /* d_org */::diagnostics)
    .function("getKind", static_cast<OrgSemKind(org::sem::ErrorGroup /* d_org */::*)() const>(&org::sem::ErrorGroup /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::ErrorGroup /* d_org */>>)
    ;
  emscripten::class_<org::sem::Stmt /* d_org */, emscripten::base<org::sem::Org>>("Stmt")
    .smart_ptr<org::sem::SemId<org::sem::Stmt /* d_org */>>("Stmt")
    .property("attached", &org::sem::Stmt /* d_org */::attached)
    .function("getAttached", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt /* d_org */::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt /* d_org */::getAttached))
    .function("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt /* d_org */::*)() const>(&org::sem::Stmt /* d_org */::getCaption))
    .function("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::Stmt /* d_org */::*)() const>(&org::sem::Stmt /* d_org */::getName))
    .function("getAttrs", static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Stmt /* d_org */::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt /* d_org */::getAttrs))
    .function("getFirstAttr", static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Stmt /* d_org */::*)(hstd::Str const&) const>(&org::sem::Stmt /* d_org */::getFirstAttr))
    .function("getFirstAttrString", static_cast<hstd::Opt<hstd::Str>(org::sem::Stmt /* d_org */::*)(hstd::Str const&) const>(&org::sem::Stmt /* d_org */::getFirstAttrString))
    .function("getFirstAttrInt", static_cast<hstd::Opt<int>(org::sem::Stmt /* d_org */::*)(hstd::Str const&) const>(&org::sem::Stmt /* d_org */::getFirstAttrInt))
    .function("getFirstAttrBool", static_cast<hstd::Opt<bool>(org::sem::Stmt /* d_org */::*)(hstd::Str const&) const>(&org::sem::Stmt /* d_org */::getFirstAttrBool))
    .function("getFirstAttrDouble", static_cast<hstd::Opt<double>(org::sem::Stmt /* d_org */::*)(hstd::Str const&) const>(&org::sem::Stmt /* d_org */::getFirstAttrDouble))
    .function("getFirstAttrLisp", static_cast<hstd::Opt<org::sem::AttrValue::LispValue>(org::sem::Stmt /* d_org */::*)(hstd::Str const&) const>(&org::sem::Stmt /* d_org */::getFirstAttrLisp))
    .function("getFirstAttrKind", static_cast<hstd::Opt<org::sem::AttrValue::Kind>(org::sem::Stmt /* d_org */::*)(hstd::Str const&) const>(&org::sem::Stmt /* d_org */::getFirstAttrKind))
    ;
  emscripten::class_<org::sem::Inline /* d_org */, emscripten::base<org::sem::Org>>("Inline")
    .smart_ptr<org::sem::SemId<org::sem::Inline /* d_org */>>("Inline")
    ;
  emscripten::class_<org::sem::StmtList /* d_org */, emscripten::base<org::sem::Org>>("StmtList")
    .smart_ptr<org::sem::SemId<org::sem::StmtList /* d_org */>>("StmtList")
    .function("getKind", static_cast<OrgSemKind(org::sem::StmtList /* d_org */::*)() const>(&org::sem::StmtList /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::StmtList /* d_org */>>)
    ;
  emscripten::class_<org::sem::Empty /* d_org */, emscripten::base<org::sem::Org>>("Empty")
    .smart_ptr<org::sem::SemId<org::sem::Empty /* d_org */>>("Empty")
    .function("getKind", static_cast<OrgSemKind(org::sem::Empty /* d_org */::*)() const>(&org::sem::Empty /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Empty /* d_org */>>)
    ;
  emscripten::class_<org::sem::Leaf /* d_org */, emscripten::base<org::sem::Org>>("Leaf")
    .smart_ptr<org::sem::SemId<org::sem::Leaf /* d_org */>>("Leaf")
    .property("text", &org::sem::Leaf /* d_org */::text)
    .function("getText", static_cast<hstd::Str(org::sem::Leaf /* d_org */::*)() const>(&org::sem::Leaf /* d_org */::getText))
    ;
  emscripten::class_<org::sem::Time /* d_org */, emscripten::base<org::sem::Org>>("Time")
    .smart_ptr<org::sem::SemId<org::sem::Time /* d_org */>>("Time")
    .property("isActive", &org::sem::Time /* d_org */::isActive)
    .property("time", &org::sem::Time /* d_org */::time)
    .function("getKind", static_cast<OrgSemKind(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getKind))
    .function("getYear", static_cast<hstd::Opt<int>(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getYear))
    .function("getMonth", static_cast<hstd::Opt<int>(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getMonth))
    .function("getDay", static_cast<hstd::Opt<int>(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getDay))
    .function("getHour", static_cast<hstd::Opt<int>(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getHour))
    .function("getMinute", static_cast<hstd::Opt<int>(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getMinute))
    .function("getSecond", static_cast<hstd::Opt<int>(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getSecond))
    .function("getStaticTime", static_cast<hstd::UserTime(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getStaticTime))
    .function("isStatic", static_cast<bool(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::isStatic))
    .function("getStaticConst", static_cast<org::sem::Time::Static const&(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getStatic))
    .function("getStaticMut", static_cast<org::sem::Time::Static&(org::sem::Time /* d_org */::*)()>(&org::sem::Time /* d_org */::getStatic))
    .function("isDynamic", static_cast<bool(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::isDynamic))
    .function("getDynamicConst", static_cast<org::sem::Time::Dynamic const&(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getDynamic))
    .function("getDynamicMut", static_cast<org::sem::Time::Dynamic&(org::sem::Time /* d_org */::*)()>(&org::sem::Time /* d_org */::getDynamic))
    .class_function("getTimeKindStatic", static_cast<org::sem::Time::TimeKind(*)(org::sem::Time::TimeVariant const&)>(&org::sem::Time /* d_org */::getTimeKind))
    .function("getTimeKind", static_cast<org::sem::Time::TimeKind(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getTimeKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Time /* d_org */>>)
    ;
  emscripten::class_<org::sem::Time::Repeat>("TimeRepeat")
    .property("mode", &org::sem::Time::Repeat::mode)
    .property("period", &org::sem::Time::Repeat::period)
    .property("count", &org::sem::Time::Repeat::count)
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::Time::Repeat::Mode>("TimeRepeatMode");
  org::bind::js::bind_enum<org::sem::Time::Repeat::Period>("TimeRepeatPeriod");
  emscripten::class_<org::sem::Time::Static>("TimeStatic")
    .property("repeat", &org::sem::Time::Static::repeat)
    .property("warn", &org::sem::Time::Static::warn)
    .property("time", &org::sem::Time::Static::time)
    .constructor<>()
    ;
  emscripten::class_<org::sem::Time::Dynamic>("TimeDynamic")
    .property("expr", &org::sem::Time::Dynamic::expr)
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::Time::TimeKind>("TimeTimeKind");
  emscripten::class_<org::sem::TimeRange /* d_org */, emscripten::base<org::sem::Org>>("TimeRange")
    .smart_ptr<org::sem::SemId<org::sem::TimeRange /* d_org */>>("TimeRange")
    .property("from", &org::sem::TimeRange /* d_org */::from)
    .property("to", &org::sem::TimeRange /* d_org */::to)
    .function("getKind", static_cast<OrgSemKind(org::sem::TimeRange /* d_org */::*)() const>(&org::sem::TimeRange /* d_org */::getKind))
    .function("getClockedTimeSeconds", static_cast<hstd::Opt<int64_t>(org::sem::TimeRange /* d_org */::*)() const>(&org::sem::TimeRange /* d_org */::getClockedTimeSeconds))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::TimeRange /* d_org */>>)
    ;
  emscripten::class_<org::sem::Macro /* d_org */, emscripten::base<org::sem::Org>>("Macro")
    .smart_ptr<org::sem::SemId<org::sem::Macro /* d_org */>>("Macro")
    .property("name", &org::sem::Macro /* d_org */::name)
    .property("attrs", &org::sem::Macro /* d_org */::attrs)
    .function("getKind", static_cast<OrgSemKind(org::sem::Macro /* d_org */::*)() const>(&org::sem::Macro /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Macro /* d_org */>>)
    ;
  emscripten::class_<org::sem::Symbol /* d_org */, emscripten::base<org::sem::Org>>("Symbol")
    .smart_ptr<org::sem::SemId<org::sem::Symbol /* d_org */>>("Symbol")
    .property("name", &org::sem::Symbol /* d_org */::name)
    .property("parameters", &org::sem::Symbol /* d_org */::parameters)
    .property("positional", &org::sem::Symbol /* d_org */::positional)
    .function("getKind", static_cast<OrgSemKind(org::sem::Symbol /* d_org */::*)() const>(&org::sem::Symbol /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Symbol /* d_org */>>)
    ;
  emscripten::class_<org::sem::Symbol::Param>("SymbolParam")
    .property("key", &org::sem::Symbol::Param::key)
    .property("value", &org::sem::Symbol::Param::value)
    .constructor<>()
    ;
  emscripten::class_<org::sem::ErrorSkipGroup /* d_org */, emscripten::base<org::sem::Org>>("ErrorSkipGroup")
    .smart_ptr<org::sem::SemId<org::sem::ErrorSkipGroup /* d_org */>>("ErrorSkipGroup")
    .property("skipped", &org::sem::ErrorSkipGroup /* d_org */::skipped)
    .function("getKind", static_cast<OrgSemKind(org::sem::ErrorSkipGroup /* d_org */::*)() const>(&org::sem::ErrorSkipGroup /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::ErrorSkipGroup /* d_org */>>)
    ;
  emscripten::class_<org::sem::Markup /* d_org */, emscripten::base<org::sem::Org>>("Markup")
    .smart_ptr<org::sem::SemId<org::sem::Markup /* d_org */>>("Markup")
    ;
  emscripten::class_<org::sem::RadioTarget /* d_org */, emscripten::base<org::sem::Org>>("RadioTarget")
    .smart_ptr<org::sem::SemId<org::sem::RadioTarget /* d_org */>>("RadioTarget")
    .property("words", &org::sem::RadioTarget /* d_org */::words)
    .function("getKind", static_cast<OrgSemKind(org::sem::RadioTarget /* d_org */::*)() const>(&org::sem::RadioTarget /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::RadioTarget /* d_org */>>)
    ;
  emscripten::class_<org::sem::Latex /* d_org */, emscripten::base<org::sem::Org>>("Latex")
    .smart_ptr<org::sem::SemId<org::sem::Latex /* d_org */>>("Latex")
    .function("getKind", static_cast<OrgSemKind(org::sem::Latex /* d_org */::*)() const>(&org::sem::Latex /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Latex /* d_org */>>)
    ;
  emscripten::class_<org::sem::SubtreeLog /* d_org */, emscripten::base<org::sem::Org>>("SubtreeLog")
    .smart_ptr<org::sem::SemId<org::sem::SubtreeLog /* d_org */>>("SubtreeLog")
    .property("head", &org::sem::SubtreeLog /* d_org */::head)
    .property("desc", &org::sem::SubtreeLog /* d_org */::desc)
    .function("getKind", static_cast<OrgSemKind(org::sem::SubtreeLog /* d_org */::*)() const>(&org::sem::SubtreeLog /* d_org */::getKind))
    .function("setDescription", static_cast<void(org::sem::SubtreeLog /* d_org */::*)(org::sem::SemId<org::sem::StmtList>)>(&org::sem::SubtreeLog /* d_org */::setDescription))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::SubtreeLog /* d_org */>>)
    ;
  emscripten::class_<org::sem::Subtree /* d_org */, emscripten::base<org::sem::Org>>("Subtree")
    .smart_ptr<org::sem::SemId<org::sem::Subtree /* d_org */>>("Subtree")
    .property("level", &org::sem::Subtree /* d_org */::level)
    .property("treeId", &org::sem::Subtree /* d_org */::treeId)
    .property("todo", &org::sem::Subtree /* d_org */::todo)
    .property("completion", &org::sem::Subtree /* d_org */::completion)
    .property("description", &org::sem::Subtree /* d_org */::description)
    .property("tags", &org::sem::Subtree /* d_org */::tags)
    .property("title", &org::sem::Subtree /* d_org */::title)
    .property("logbook", &org::sem::Subtree /* d_org */::logbook)
    .property("properties", &org::sem::Subtree /* d_org */::properties)
    .property("closed", &org::sem::Subtree /* d_org */::closed)
    .property("deadline", &org::sem::Subtree /* d_org */::deadline)
    .property("scheduled", &org::sem::Subtree /* d_org */::scheduled)
    .property("isComment", &org::sem::Subtree /* d_org */::isComment)
    .property("isArchived", &org::sem::Subtree /* d_org */::isArchived)
    .property("priority", &org::sem::Subtree /* d_org */::priority)
    .function("getKind", static_cast<OrgSemKind(org::sem::Subtree /* d_org */::*)() const>(&org::sem::Subtree /* d_org */::getKind))
    .function("getTimePeriods", static_cast<hstd::Vec<org::sem::SubtreePeriod>(org::sem::Subtree /* d_org */::*)(hstd::IntSet<org::sem::SubtreePeriod::Kind>) const>(&org::sem::Subtree /* d_org */::getTimePeriods))
    .function("getProperties", static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Subtree /* d_org */::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree /* d_org */::getProperties))
    .function("getProperty", static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Subtree /* d_org */::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree /* d_org */::getProperty))
    .function("removeProperty", static_cast<void(org::sem::Subtree /* d_org */::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree /* d_org */::removeProperty))
    .function("setProperty", static_cast<void(org::sem::Subtree /* d_org */::*)(org::sem::NamedProperty const&)>(&org::sem::Subtree /* d_org */::setProperty))
    .function("setPropertyStrValue", static_cast<void(org::sem::Subtree /* d_org */::*)(hstd::Str const&, hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree /* d_org */::setPropertyStrValue))
    .function("getCleanTitle", static_cast<hstd::Str(org::sem::Subtree /* d_org */::*)() const>(&org::sem::Subtree /* d_org */::getCleanTitle))
    .function("getTodoKeyword", static_cast<hstd::Opt<hstd::Str>(org::sem::Subtree /* d_org */::*)() const>(&org::sem::Subtree /* d_org */::getTodoKeyword))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Subtree /* d_org */>>)
    ;
  emscripten::class_<org::sem::ColonExample /* d_org */, emscripten::base<org::sem::Org>>("ColonExample")
    .smart_ptr<org::sem::SemId<org::sem::ColonExample /* d_org */>>("ColonExample")
    .function("getKind", static_cast<OrgSemKind(org::sem::ColonExample /* d_org */::*)() const>(&org::sem::ColonExample /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::ColonExample /* d_org */>>)
    ;
  emscripten::class_<org::sem::Call /* d_org */, emscripten::base<org::sem::Org>>("Call")
    .smart_ptr<org::sem::SemId<org::sem::Call /* d_org */>>("Call")
    .property("name", &org::sem::Call /* d_org */::name)
    .property("attrs", &org::sem::Call /* d_org */::attrs)
    .property("isCommand", &org::sem::Call /* d_org */::isCommand)
    .function("getKind", static_cast<OrgSemKind(org::sem::Call /* d_org */::*)() const>(&org::sem::Call /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Call /* d_org */>>)
    ;
  emscripten::class_<org::sem::ListItem /* d_org */, emscripten::base<org::sem::Org>>("ListItem")
    .smart_ptr<org::sem::SemId<org::sem::ListItem /* d_org */>>("ListItem")
    .property("checkbox", &org::sem::ListItem /* d_org */::checkbox)
    .property("header", &org::sem::ListItem /* d_org */::header)
    .property("bullet", &org::sem::ListItem /* d_org */::bullet)
    .function("getKind", static_cast<OrgSemKind(org::sem::ListItem /* d_org */::*)() const>(&org::sem::ListItem /* d_org */::getKind))
    .function("isDescriptionItem", static_cast<bool(org::sem::ListItem /* d_org */::*)() const>(&org::sem::ListItem /* d_org */::isDescriptionItem))
    .function("getCleanHeader", static_cast<hstd::Opt<hstd::Str>(org::sem::ListItem /* d_org */::*)() const>(&org::sem::ListItem /* d_org */::getCleanHeader))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::ListItem /* d_org */>>)
    ;
}

void subdivide_4(org::bind::js::type_registration_guard& g) {
  emscripten::class_<org::sem::DocumentOptions /* d_org */, emscripten::base<org::sem::Org>>("DocumentOptions")
    .smart_ptr<org::sem::SemId<org::sem::DocumentOptions /* d_org */>>("DocumentOptions")
    .property("initialVisibility", &org::sem::DocumentOptions /* d_org */::initialVisibility)
    .property("properties", &org::sem::DocumentOptions /* d_org */::properties)
    .property("exportConfig", &org::sem::DocumentOptions /* d_org */::exportConfig)
    .property("fixedWidthSections", &org::sem::DocumentOptions /* d_org */::fixedWidthSections)
    .property("startupIndented", &org::sem::DocumentOptions /* d_org */::startupIndented)
    .property("category", &org::sem::DocumentOptions /* d_org */::category)
    .property("setupfile", &org::sem::DocumentOptions /* d_org */::setupfile)
    .property("maxSubtreeLevelExport", &org::sem::DocumentOptions /* d_org */::maxSubtreeLevelExport)
    .property("columns", &org::sem::DocumentOptions /* d_org */::columns)
    .property("todoKeywords", &org::sem::DocumentOptions /* d_org */::todoKeywords)
    .property("doneKeywords", &org::sem::DocumentOptions /* d_org */::doneKeywords)
    .function("getKind", static_cast<OrgSemKind(org::sem::DocumentOptions /* d_org */::*)() const>(&org::sem::DocumentOptions /* d_org */::getKind))
    .function("getProperties", static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::DocumentOptions /* d_org */::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions /* d_org */::getProperties))
    .function("getProperty", static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::DocumentOptions /* d_org */::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions /* d_org */::getProperty))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::DocumentOptions /* d_org */>>)
    ;
  emscripten::class_<org::sem::DocumentFragment /* d_org */, emscripten::base<org::sem::Org>>("DocumentFragment")
    .smart_ptr<org::sem::SemId<org::sem::DocumentFragment /* d_org */>>("DocumentFragment")
    .property("baseLine", &org::sem::DocumentFragment /* d_org */::baseLine)
    .property("baseCol", &org::sem::DocumentFragment /* d_org */::baseCol)
    .function("getKind", static_cast<OrgSemKind(org::sem::DocumentFragment /* d_org */::*)() const>(&org::sem::DocumentFragment /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::DocumentFragment /* d_org */>>)
    ;
  emscripten::class_<org::sem::CriticMarkup /* d_org */, emscripten::base<org::sem::Org>>("CriticMarkup")
    .smart_ptr<org::sem::SemId<org::sem::CriticMarkup /* d_org */>>("CriticMarkup")
    .property("kind", &org::sem::CriticMarkup /* d_org */::kind)
    .function("getKind", static_cast<OrgSemKind(org::sem::CriticMarkup /* d_org */::*)() const>(&org::sem::CriticMarkup /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CriticMarkup /* d_org */>>)
    ;
  org::bind::js::bind_enum<org::sem::CriticMarkup::Kind>("CriticMarkupKind");
  emscripten::class_<org::sem::Document /* d_org */, emscripten::base<org::sem::Org>>("Document")
    .smart_ptr<org::sem::SemId<org::sem::Document /* d_org */>>("Document")
    .property("title", &org::sem::Document /* d_org */::title)
    .property("author", &org::sem::Document /* d_org */::author)
    .property("creator", &org::sem::Document /* d_org */::creator)
    .property("filetags", &org::sem::Document /* d_org */::filetags)
    .property("email", &org::sem::Document /* d_org */::email)
    .property("language", &org::sem::Document /* d_org */::language)
    .property("options", &org::sem::Document /* d_org */::options)
    .property("exportFileName", &org::sem::Document /* d_org */::exportFileName)
    .function("getKind", static_cast<OrgSemKind(org::sem::Document /* d_org */::*)() const>(&org::sem::Document /* d_org */::getKind))
    .function("getProperties", static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Document /* d_org */::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document /* d_org */::getProperties))
    .function("getProperty", static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Document /* d_org */::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document /* d_org */::getProperty))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Document /* d_org */>>)
    ;
  emscripten::class_<org::sem::FileTarget /* d_org */, emscripten::base<org::sem::Org>>("FileTarget")
    .smart_ptr<org::sem::SemId<org::sem::FileTarget /* d_org */>>("FileTarget")
    .property("path", &org::sem::FileTarget /* d_org */::path)
    .property("line", &org::sem::FileTarget /* d_org */::line)
    .property("searchTarget", &org::sem::FileTarget /* d_org */::searchTarget)
    .property("restrictToHeadlines", &org::sem::FileTarget /* d_org */::restrictToHeadlines)
    .property("targetId", &org::sem::FileTarget /* d_org */::targetId)
    .property("regexp", &org::sem::FileTarget /* d_org */::regexp)
    .function("getKind", static_cast<OrgSemKind(org::sem::FileTarget /* d_org */::*)() const>(&org::sem::FileTarget /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::FileTarget /* d_org */>>)
    ;
  emscripten::class_<org::sem::TextSeparator /* d_org */, emscripten::base<org::sem::Org>>("TextSeparator")
    .smart_ptr<org::sem::SemId<org::sem::TextSeparator /* d_org */>>("TextSeparator")
    .function("getKind", static_cast<OrgSemKind(org::sem::TextSeparator /* d_org */::*)() const>(&org::sem::TextSeparator /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::TextSeparator /* d_org */>>)
    ;
  emscripten::class_<org::sem::DocumentGroup /* d_org */, emscripten::base<org::sem::Org>>("DocumentGroup")
    .smart_ptr<org::sem::SemId<org::sem::DocumentGroup /* d_org */>>("DocumentGroup")
    .function("getKind", static_cast<OrgSemKind(org::sem::DocumentGroup /* d_org */::*)() const>(&org::sem::DocumentGroup /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::DocumentGroup /* d_org */>>)
    ;
  emscripten::class_<org::sem::File /* d_org */, emscripten::base<org::sem::Org>>("File")
    .smart_ptr<org::sem::SemId<org::sem::File /* d_org */>>("File")
    .property("relPath", &org::sem::File /* d_org */::relPath)
    .property("absPath", &org::sem::File /* d_org */::absPath)
    .property("data", &org::sem::File /* d_org */::data)
    .function("getKind", static_cast<OrgSemKind(org::sem::File /* d_org */::*)() const>(&org::sem::File /* d_org */::getKind))
    .function("isDocument", static_cast<bool(org::sem::File /* d_org */::*)() const>(&org::sem::File /* d_org */::isDocument))
    .function("getDocumentConst", static_cast<org::sem::File::Document const&(org::sem::File /* d_org */::*)() const>(&org::sem::File /* d_org */::getDocument))
    .function("getDocumentMut", static_cast<org::sem::File::Document&(org::sem::File /* d_org */::*)()>(&org::sem::File /* d_org */::getDocument))
    .function("isAttachment", static_cast<bool(org::sem::File /* d_org */::*)() const>(&org::sem::File /* d_org */::isAttachment))
    .function("getAttachmentConst", static_cast<org::sem::File::Attachment const&(org::sem::File /* d_org */::*)() const>(&org::sem::File /* d_org */::getAttachment))
    .function("getAttachmentMut", static_cast<org::sem::File::Attachment&(org::sem::File /* d_org */::*)()>(&org::sem::File /* d_org */::getAttachment))
    .function("isSource", static_cast<bool(org::sem::File /* d_org */::*)() const>(&org::sem::File /* d_org */::isSource))
    .function("getSourceConst", static_cast<org::sem::File::Source const&(org::sem::File /* d_org */::*)() const>(&org::sem::File /* d_org */::getSource))
    .function("getSourceMut", static_cast<org::sem::File::Source&(org::sem::File /* d_org */::*)()>(&org::sem::File /* d_org */::getSource))
    .class_function("getFileKindStatic", static_cast<org::sem::File::Kind(*)(org::sem::File::Data const&)>(&org::sem::File /* d_org */::getFileKind))
    .function("getFileKind", static_cast<org::sem::File::Kind(org::sem::File /* d_org */::*)() const>(&org::sem::File /* d_org */::getFileKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::File /* d_org */>>)
    ;
  emscripten::class_<org::sem::File::Document>("FileDocument")
    .constructor<>()
    ;
  emscripten::class_<org::sem::File::Attachment>("FileAttachment")
    .constructor<>()
    ;
  emscripten::class_<org::sem::File::Source>("FileSource")
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::File::Kind>("FileKind");
  emscripten::class_<org::sem::Directory /* d_org */, emscripten::base<org::sem::Org>>("Directory")
    .smart_ptr<org::sem::SemId<org::sem::Directory /* d_org */>>("Directory")
    .property("relPath", &org::sem::Directory /* d_org */::relPath)
    .property("absPath", &org::sem::Directory /* d_org */::absPath)
    .function("getKind", static_cast<OrgSemKind(org::sem::Directory /* d_org */::*)() const>(&org::sem::Directory /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Directory /* d_org */>>)
    ;
  emscripten::class_<org::sem::Symlink /* d_org */, emscripten::base<org::sem::Org>>("Symlink")
    .smart_ptr<org::sem::SemId<org::sem::Symlink /* d_org */>>("Symlink")
    .property("isDirectory", &org::sem::Symlink /* d_org */::isDirectory)
    .property("absPath", &org::sem::Symlink /* d_org */::absPath)
    .function("getKind", static_cast<OrgSemKind(org::sem::Symlink /* d_org */::*)() const>(&org::sem::Symlink /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Symlink /* d_org */>>)
    ;
  emscripten::class_<org::sem::CmdInclude /* d_org */, emscripten::base<org::sem::Org>>("CmdInclude")
    .smart_ptr<org::sem::SemId<org::sem::CmdInclude /* d_org */>>("CmdInclude")
    .property("path", &org::sem::CmdInclude /* d_org */::path)
    .property("firstLine", &org::sem::CmdInclude /* d_org */::firstLine)
    .property("lastLine", &org::sem::CmdInclude /* d_org */::lastLine)
    .property("data", &org::sem::CmdInclude /* d_org */::data)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::getKind))
    .function("isExample", static_cast<bool(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::isExample))
    .function("getExampleConst", static_cast<org::sem::CmdInclude::Example const&(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::getExample))
    .function("getExampleMut", static_cast<org::sem::CmdInclude::Example&(org::sem::CmdInclude /* d_org */::*)()>(&org::sem::CmdInclude /* d_org */::getExample))
    .function("isExport", static_cast<bool(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::isExport))
    .function("getExportConst", static_cast<org::sem::CmdInclude::Export const&(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::getExport))
    .function("getExportMut", static_cast<org::sem::CmdInclude::Export&(org::sem::CmdInclude /* d_org */::*)()>(&org::sem::CmdInclude /* d_org */::getExport))
    .function("isCustom", static_cast<bool(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::isCustom))
    .function("getCustomConst", static_cast<org::sem::CmdInclude::Custom const&(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::getCustom))
    .function("getCustomMut", static_cast<org::sem::CmdInclude::Custom&(org::sem::CmdInclude /* d_org */::*)()>(&org::sem::CmdInclude /* d_org */::getCustom))
    .function("isSrc", static_cast<bool(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::isSrc))
    .function("getSrcConst", static_cast<org::sem::CmdInclude::Src const&(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::getSrc))
    .function("getSrcMut", static_cast<org::sem::CmdInclude::Src&(org::sem::CmdInclude /* d_org */::*)()>(&org::sem::CmdInclude /* d_org */::getSrc))
    .function("isOrgDocument", static_cast<bool(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::isOrgDocument))
    .function("getOrgDocumentConst", static_cast<org::sem::CmdInclude::OrgDocument const&(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::getOrgDocument))
    .function("getOrgDocumentMut", static_cast<org::sem::CmdInclude::OrgDocument&(org::sem::CmdInclude /* d_org */::*)()>(&org::sem::CmdInclude /* d_org */::getOrgDocument))
    .class_function("getIncludeKindStatic", static_cast<org::sem::CmdInclude::Kind(*)(org::sem::CmdInclude::Data const&)>(&org::sem::CmdInclude /* d_org */::getIncludeKind))
    .function("getIncludeKind", static_cast<org::sem::CmdInclude::Kind(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::getIncludeKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdInclude /* d_org */>>)
    ;
  emscripten::class_<org::sem::CmdInclude::IncludeBase>("CmdIncludeIncludeBase")
    .constructor<>()
    ;
  emscripten::class_<org::sem::CmdInclude::Example, emscripten::base<org::sem::CmdInclude::IncludeBase>>("CmdIncludeExample")
    .constructor<>()
    ;
  emscripten::class_<org::sem::CmdInclude::Export, emscripten::base<org::sem::CmdInclude::IncludeBase>>("CmdIncludeExport")
    .property("language", &org::sem::CmdInclude::Export::language)
    .constructor<>()
    ;
  emscripten::class_<org::sem::CmdInclude::Custom, emscripten::base<org::sem::CmdInclude::IncludeBase>>("CmdIncludeCustom")
    .property("blockName", &org::sem::CmdInclude::Custom::blockName)
    .constructor<>()
    ;
  emscripten::class_<org::sem::CmdInclude::Src, emscripten::base<org::sem::CmdInclude::IncludeBase>>("CmdIncludeSrc")
    .property("language", &org::sem::CmdInclude::Src::language)
    .constructor<>()
    ;
  emscripten::class_<org::sem::CmdInclude::OrgDocument, emscripten::base<org::sem::CmdInclude::IncludeBase>>("CmdIncludeOrgDocument")
    .property("onlyContent", &org::sem::CmdInclude::OrgDocument::onlyContent)
    .property("subtreePath", &org::sem::CmdInclude::OrgDocument::subtreePath)
    .property("minLevel", &org::sem::CmdInclude::OrgDocument::minLevel)
    .property("customIdTarget", &org::sem::CmdInclude::OrgDocument::customIdTarget)
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::CmdInclude::Kind>("CmdIncludeKind");
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmNoNode /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmErrorItem /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmErrorGroup /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmStmt /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmInline /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmStmtList /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmEmpty /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmd /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlock /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmLineCommand /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmAttached /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmLeaf /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdCaption /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdCreator /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdAuthor /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdEmail /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdLanguage /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdColumns /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdName /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdCustomArgs /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdCustomRaw /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdCustomText /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdCall /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdTblfm /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmHashTag /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmInlineFootnote /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmInlineExport /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmTime /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmTimeRange /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmMacro /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmSymbol /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmEscaped /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmNewline /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmSpace /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmWord /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmAtMention /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmRawText /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmPunctuation /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmPlaceholder /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBigIdent /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmTextTarget /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmErrorSkipToken /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmErrorSkipGroup /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmMarkup /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBold /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmUnderline /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmMonospace /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmMarkQuote /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmVerbatim /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmItalic /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmStrike /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmPar /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmRadioTarget /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmLatex /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmLink /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockCenter /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockQuote /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockComment /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockVerse /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockDynamicFallback /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockExample /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockExport /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockAdmonition /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmBlockCode /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmSubtreeLog /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmSubtree /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCell /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmRow /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmTable /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmParagraph /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmColonExample /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdAttr /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdExport /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCall /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmList /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmListItem /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmDocumentOptions /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
}

void subdivide_5(org::bind::js::type_registration_guard& g) {
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmDocumentFragment /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCriticMarkup /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmDocument /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmFileTarget /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmTextSeparator /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmDocumentGroup /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmFile /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmDirectory /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmSymlink /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmIdT<org::imm::ImmCmdInclude /* d_orgimm_write */>, emscripten::base<org::imm::ImmId>>("ImmIdT")
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmNoNode /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmNoNode")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmNoNode /* d_orgimm_write */::*)() const>(&org::imm::ImmNoNode /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmNoNode /* d_orgimm_write */::*)(org::imm::ImmNoNode const& /* d_orgimm_write */) const>(&org::imm::ImmNoNode /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmErrorItem /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmErrorItem")
    .property("diag", &org::imm::ImmErrorItem /* d_orgimm_write */::diag)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmErrorItem /* d_orgimm_write */::*)() const>(&org::imm::ImmErrorItem /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmErrorItem /* d_orgimm_write */::*)(org::imm::ImmErrorItem const& /* d_orgimm_write */) const>(&org::imm::ImmErrorItem /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmErrorGroup /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmErrorGroup")
    .property("diagnostics", &org::imm::ImmErrorGroup /* d_orgimm_write */::diagnostics)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmErrorGroup /* d_orgimm_write */::*)() const>(&org::imm::ImmErrorGroup /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmErrorGroup /* d_orgimm_write */::*)(org::imm::ImmErrorGroup const& /* d_orgimm_write */) const>(&org::imm::ImmErrorGroup /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmStmt /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmStmt")
    .property("attached", &org::imm::ImmStmt /* d_orgimm_write */::attached)
    .function("__eq__", static_cast<bool(org::imm::ImmStmt /* d_orgimm_write */::*)(org::imm::ImmStmt const& /* d_orgimm_write */) const>(&org::imm::ImmStmt /* d_orgimm_write */::operator==))
    ;
  emscripten::class_<org::imm::ImmInline /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmInline")
    .function("__eq__", static_cast<bool(org::imm::ImmInline /* d_orgimm_write */::*)(org::imm::ImmInline const& /* d_orgimm_write */) const>(&org::imm::ImmInline /* d_orgimm_write */::operator==))
    ;
  emscripten::class_<org::imm::ImmStmtList /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmStmtList")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmStmtList /* d_orgimm_write */::*)() const>(&org::imm::ImmStmtList /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmStmtList /* d_orgimm_write */::*)(org::imm::ImmStmtList const& /* d_orgimm_write */) const>(&org::imm::ImmStmtList /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmEmpty /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmEmpty")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmEmpty /* d_orgimm_write */::*)() const>(&org::imm::ImmEmpty /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmEmpty /* d_orgimm_write */::*)(org::imm::ImmEmpty const& /* d_orgimm_write */) const>(&org::imm::ImmEmpty /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmLeaf /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmLeaf")
    .property("text", &org::imm::ImmLeaf /* d_orgimm_write */::text)
    .function("__eq__", static_cast<bool(org::imm::ImmLeaf /* d_orgimm_write */::*)(org::imm::ImmLeaf const& /* d_orgimm_write */) const>(&org::imm::ImmLeaf /* d_orgimm_write */::operator==))
    ;
  emscripten::class_<org::imm::ImmTime /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmTime")
    .property("isActive", &org::imm::ImmTime /* d_orgimm_write */::isActive)
    .property("time", &org::imm::ImmTime /* d_orgimm_write */::time)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmTime /* d_orgimm_write */::*)() const>(&org::imm::ImmTime /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmTime /* d_orgimm_write */::*)(org::imm::ImmTime const& /* d_orgimm_write */) const>(&org::imm::ImmTime /* d_orgimm_write */::operator==))
    .function("isStatic", static_cast<bool(org::imm::ImmTime /* d_orgimm_write */::*)() const>(&org::imm::ImmTime /* d_orgimm_write */::isStatic))
    .function("getStaticConst", static_cast<org::imm::ImmTime::Static const& /* imm_write */(org::imm::ImmTime /* d_orgimm_write */::*)() const>(&org::imm::ImmTime /* d_orgimm_write */::getStatic))
    .function("getStaticMut", static_cast<org::imm::ImmTime::Static& /* imm_write */(org::imm::ImmTime /* d_orgimm_write */::*)()>(&org::imm::ImmTime /* d_orgimm_write */::getStatic))
    .function("isDynamic", static_cast<bool(org::imm::ImmTime /* d_orgimm_write */::*)() const>(&org::imm::ImmTime /* d_orgimm_write */::isDynamic))
    .function("getDynamicConst", static_cast<org::imm::ImmTime::Dynamic const& /* imm_write */(org::imm::ImmTime /* d_orgimm_write */::*)() const>(&org::imm::ImmTime /* d_orgimm_write */::getDynamic))
    .function("getDynamicMut", static_cast<org::imm::ImmTime::Dynamic& /* imm_write */(org::imm::ImmTime /* d_orgimm_write */::*)()>(&org::imm::ImmTime /* d_orgimm_write */::getDynamic))
    .class_function("getTimeKindStatic", static_cast<org::imm::ImmTime::TimeKind /* imm_write */(*)(org::imm::ImmTime::TimeVariant const& /* imm_write */)>(&org::imm::ImmTime /* d_orgimm_write */::getTimeKind))
    .function("getTimeKind", static_cast<org::imm::ImmTime::TimeKind /* imm_write */(org::imm::ImmTime /* d_orgimm_write */::*)() const>(&org::imm::ImmTime /* d_orgimm_write */::getTimeKind))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmTime::Repeat /* imm_write */>("ImmTimeRepeat")
    .property("mode", &org::imm::ImmTime::Repeat /* imm_write */::mode)
    .property("period", &org::imm::ImmTime::Repeat /* imm_write */::period)
    .property("count", &org::imm::ImmTime::Repeat /* imm_write */::count)
    .function("__eq__", static_cast<bool(org::imm::ImmTime::Repeat /* imm_write */::*)(org::imm::ImmTime::Repeat const& /* imm_write */) const>(&org::imm::ImmTime::Repeat /* imm_write */::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::Time::Repeat::Mode>("TimeRepeatMode");
  org::bind::js::bind_enum<org::sem::Time::Repeat::Period>("TimeRepeatPeriod");
  emscripten::class_<org::imm::ImmTime::Static /* imm_write */>("ImmTimeStatic")
    .property("repeat", &org::imm::ImmTime::Static /* imm_write */::repeat)
    .property("warn", &org::imm::ImmTime::Static /* imm_write */::warn)
    .property("time", &org::imm::ImmTime::Static /* imm_write */::time)
    .function("__eq__", static_cast<bool(org::imm::ImmTime::Static /* imm_write */::*)(org::imm::ImmTime::Static const& /* imm_write */) const>(&org::imm::ImmTime::Static /* imm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmTime::Dynamic /* imm_write */>("ImmTimeDynamic")
    .property("expr", &org::imm::ImmTime::Dynamic /* imm_write */::expr)
    .function("__eq__", static_cast<bool(org::imm::ImmTime::Dynamic /* imm_write */::*)(org::imm::ImmTime::Dynamic const& /* imm_write */) const>(&org::imm::ImmTime::Dynamic /* imm_write */::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::imm::ImmTime::TimeKind /* imm_write */>("ImmTimeTimeKind");
  emscripten::class_<org::imm::ImmTimeRange /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmTimeRange")
    .property("from", &org::imm::ImmTimeRange /* d_orgimm_write */::from)
    .property("to", &org::imm::ImmTimeRange /* d_orgimm_write */::to)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmTimeRange /* d_orgimm_write */::*)() const>(&org::imm::ImmTimeRange /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmTimeRange /* d_orgimm_write */::*)(org::imm::ImmTimeRange const& /* d_orgimm_write */) const>(&org::imm::ImmTimeRange /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmMacro /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmMacro")
    .property("name", &org::imm::ImmMacro /* d_orgimm_write */::name)
    .property("attrs", &org::imm::ImmMacro /* d_orgimm_write */::attrs)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmMacro /* d_orgimm_write */::*)() const>(&org::imm::ImmMacro /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmMacro /* d_orgimm_write */::*)(org::imm::ImmMacro const& /* d_orgimm_write */) const>(&org::imm::ImmMacro /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmSymbol /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmSymbol")
    .property("name", &org::imm::ImmSymbol /* d_orgimm_write */::name)
    .property("parameters", &org::imm::ImmSymbol /* d_orgimm_write */::parameters)
    .property("positional", &org::imm::ImmSymbol /* d_orgimm_write */::positional)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmSymbol /* d_orgimm_write */::*)() const>(&org::imm::ImmSymbol /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmSymbol /* d_orgimm_write */::*)(org::imm::ImmSymbol const& /* d_orgimm_write */) const>(&org::imm::ImmSymbol /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmSymbol::Param /* imm_write */>("ImmSymbolParam")
    .property("key", &org::imm::ImmSymbol::Param /* imm_write */::key)
    .property("value", &org::imm::ImmSymbol::Param /* imm_write */::value)
    .function("__eq__", static_cast<bool(org::imm::ImmSymbol::Param /* imm_write */::*)(org::imm::ImmSymbol::Param const& /* imm_write */) const>(&org::imm::ImmSymbol::Param /* imm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmErrorSkipGroup /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmErrorSkipGroup")
    .property("skipped", &org::imm::ImmErrorSkipGroup /* d_orgimm_write */::skipped)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmErrorSkipGroup /* d_orgimm_write */::*)() const>(&org::imm::ImmErrorSkipGroup /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmErrorSkipGroup /* d_orgimm_write */::*)(org::imm::ImmErrorSkipGroup const& /* d_orgimm_write */) const>(&org::imm::ImmErrorSkipGroup /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmMarkup /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmMarkup")
    .function("__eq__", static_cast<bool(org::imm::ImmMarkup /* d_orgimm_write */::*)(org::imm::ImmMarkup const& /* d_orgimm_write */) const>(&org::imm::ImmMarkup /* d_orgimm_write */::operator==))
    ;
  emscripten::class_<org::imm::ImmRadioTarget /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmRadioTarget")
    .property("words", &org::imm::ImmRadioTarget /* d_orgimm_write */::words)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmRadioTarget /* d_orgimm_write */::*)() const>(&org::imm::ImmRadioTarget /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmRadioTarget /* d_orgimm_write */::*)(org::imm::ImmRadioTarget const& /* d_orgimm_write */) const>(&org::imm::ImmRadioTarget /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmLatex /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmLatex")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmLatex /* d_orgimm_write */::*)() const>(&org::imm::ImmLatex /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmLatex /* d_orgimm_write */::*)(org::imm::ImmLatex const& /* d_orgimm_write */) const>(&org::imm::ImmLatex /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmSubtreeLog /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmSubtreeLog")
    .property("head", &org::imm::ImmSubtreeLog /* d_orgimm_write */::head)
    .property("desc", &org::imm::ImmSubtreeLog /* d_orgimm_write */::desc)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmSubtreeLog /* d_orgimm_write */::*)() const>(&org::imm::ImmSubtreeLog /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmSubtreeLog /* d_orgimm_write */::*)(org::imm::ImmSubtreeLog const& /* d_orgimm_write */) const>(&org::imm::ImmSubtreeLog /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmSubtree /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmSubtree")
    .property("level", &org::imm::ImmSubtree /* d_orgimm_write */::level)
    .property("treeId", &org::imm::ImmSubtree /* d_orgimm_write */::treeId)
    .property("todo", &org::imm::ImmSubtree /* d_orgimm_write */::todo)
    .property("completion", &org::imm::ImmSubtree /* d_orgimm_write */::completion)
    .property("description", &org::imm::ImmSubtree /* d_orgimm_write */::description)
    .property("tags", &org::imm::ImmSubtree /* d_orgimm_write */::tags)
    .property("title", &org::imm::ImmSubtree /* d_orgimm_write */::title)
    .property("logbook", &org::imm::ImmSubtree /* d_orgimm_write */::logbook)
    .property("properties", &org::imm::ImmSubtree /* d_orgimm_write */::properties)
    .property("closed", &org::imm::ImmSubtree /* d_orgimm_write */::closed)
    .property("deadline", &org::imm::ImmSubtree /* d_orgimm_write */::deadline)
    .property("scheduled", &org::imm::ImmSubtree /* d_orgimm_write */::scheduled)
    .property("isComment", &org::imm::ImmSubtree /* d_orgimm_write */::isComment)
    .property("isArchived", &org::imm::ImmSubtree /* d_orgimm_write */::isArchived)
    .property("priority", &org::imm::ImmSubtree /* d_orgimm_write */::priority)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmSubtree /* d_orgimm_write */::*)() const>(&org::imm::ImmSubtree /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmSubtree /* d_orgimm_write */::*)(org::imm::ImmSubtree const& /* d_orgimm_write */) const>(&org::imm::ImmSubtree /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmColonExample /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmColonExample")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmColonExample /* d_orgimm_write */::*)() const>(&org::imm::ImmColonExample /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmColonExample /* d_orgimm_write */::*)(org::imm::ImmColonExample const& /* d_orgimm_write */) const>(&org::imm::ImmColonExample /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCall /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmCall")
    .property("name", &org::imm::ImmCall /* d_orgimm_write */::name)
    .property("attrs", &org::imm::ImmCall /* d_orgimm_write */::attrs)
    .property("isCommand", &org::imm::ImmCall /* d_orgimm_write */::isCommand)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCall /* d_orgimm_write */::*)() const>(&org::imm::ImmCall /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCall /* d_orgimm_write */::*)(org::imm::ImmCall const& /* d_orgimm_write */) const>(&org::imm::ImmCall /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmListItem /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmListItem")
    .property("checkbox", &org::imm::ImmListItem /* d_orgimm_write */::checkbox)
    .property("header", &org::imm::ImmListItem /* d_orgimm_write */::header)
    .property("bullet", &org::imm::ImmListItem /* d_orgimm_write */::bullet)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmListItem /* d_orgimm_write */::*)() const>(&org::imm::ImmListItem /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmListItem /* d_orgimm_write */::*)(org::imm::ImmListItem const& /* d_orgimm_write */) const>(&org::imm::ImmListItem /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmDocumentOptions /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmDocumentOptions")
    .property("initialVisibility", &org::imm::ImmDocumentOptions /* d_orgimm_write */::initialVisibility)
    .property("properties", &org::imm::ImmDocumentOptions /* d_orgimm_write */::properties)
    .property("exportConfig", &org::imm::ImmDocumentOptions /* d_orgimm_write */::exportConfig)
    .property("fixedWidthSections", &org::imm::ImmDocumentOptions /* d_orgimm_write */::fixedWidthSections)
    .property("startupIndented", &org::imm::ImmDocumentOptions /* d_orgimm_write */::startupIndented)
    .property("category", &org::imm::ImmDocumentOptions /* d_orgimm_write */::category)
    .property("setupfile", &org::imm::ImmDocumentOptions /* d_orgimm_write */::setupfile)
    .property("maxSubtreeLevelExport", &org::imm::ImmDocumentOptions /* d_orgimm_write */::maxSubtreeLevelExport)
    .property("columns", &org::imm::ImmDocumentOptions /* d_orgimm_write */::columns)
    .property("todoKeywords", &org::imm::ImmDocumentOptions /* d_orgimm_write */::todoKeywords)
    .property("doneKeywords", &org::imm::ImmDocumentOptions /* d_orgimm_write */::doneKeywords)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmDocumentOptions /* d_orgimm_write */::*)() const>(&org::imm::ImmDocumentOptions /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmDocumentOptions /* d_orgimm_write */::*)(org::imm::ImmDocumentOptions const& /* d_orgimm_write */) const>(&org::imm::ImmDocumentOptions /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmDocumentFragment /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmDocumentFragment")
    .property("baseLine", &org::imm::ImmDocumentFragment /* d_orgimm_write */::baseLine)
    .property("baseCol", &org::imm::ImmDocumentFragment /* d_orgimm_write */::baseCol)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmDocumentFragment /* d_orgimm_write */::*)() const>(&org::imm::ImmDocumentFragment /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmDocumentFragment /* d_orgimm_write */::*)(org::imm::ImmDocumentFragment const& /* d_orgimm_write */) const>(&org::imm::ImmDocumentFragment /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCriticMarkup /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmCriticMarkup")
    .property("kind", &org::imm::ImmCriticMarkup /* d_orgimm_write */::kind)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCriticMarkup /* d_orgimm_write */::*)() const>(&org::imm::ImmCriticMarkup /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCriticMarkup /* d_orgimm_write */::*)(org::imm::ImmCriticMarkup const& /* d_orgimm_write */) const>(&org::imm::ImmCriticMarkup /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::sem::CriticMarkup::Kind>("CriticMarkupKind");
  emscripten::class_<org::imm::ImmDocument /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmDocument")
    .property("title", &org::imm::ImmDocument /* d_orgimm_write */::title)
    .property("author", &org::imm::ImmDocument /* d_orgimm_write */::author)
    .property("creator", &org::imm::ImmDocument /* d_orgimm_write */::creator)
    .property("filetags", &org::imm::ImmDocument /* d_orgimm_write */::filetags)
    .property("email", &org::imm::ImmDocument /* d_orgimm_write */::email)
    .property("language", &org::imm::ImmDocument /* d_orgimm_write */::language)
    .property("options", &org::imm::ImmDocument /* d_orgimm_write */::options)
    .property("exportFileName", &org::imm::ImmDocument /* d_orgimm_write */::exportFileName)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmDocument /* d_orgimm_write */::*)() const>(&org::imm::ImmDocument /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmDocument /* d_orgimm_write */::*)(org::imm::ImmDocument const& /* d_orgimm_write */) const>(&org::imm::ImmDocument /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmFileTarget /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmFileTarget")
    .property("path", &org::imm::ImmFileTarget /* d_orgimm_write */::path)
    .property("line", &org::imm::ImmFileTarget /* d_orgimm_write */::line)
    .property("searchTarget", &org::imm::ImmFileTarget /* d_orgimm_write */::searchTarget)
    .property("restrictToHeadlines", &org::imm::ImmFileTarget /* d_orgimm_write */::restrictToHeadlines)
    .property("targetId", &org::imm::ImmFileTarget /* d_orgimm_write */::targetId)
    .property("regexp", &org::imm::ImmFileTarget /* d_orgimm_write */::regexp)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmFileTarget /* d_orgimm_write */::*)() const>(&org::imm::ImmFileTarget /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmFileTarget /* d_orgimm_write */::*)(org::imm::ImmFileTarget const& /* d_orgimm_write */) const>(&org::imm::ImmFileTarget /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmTextSeparator /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmTextSeparator")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmTextSeparator /* d_orgimm_write */::*)() const>(&org::imm::ImmTextSeparator /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmTextSeparator /* d_orgimm_write */::*)(org::imm::ImmTextSeparator const& /* d_orgimm_write */) const>(&org::imm::ImmTextSeparator /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmDocumentGroup /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmDocumentGroup")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmDocumentGroup /* d_orgimm_write */::*)() const>(&org::imm::ImmDocumentGroup /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmDocumentGroup /* d_orgimm_write */::*)(org::imm::ImmDocumentGroup const& /* d_orgimm_write */) const>(&org::imm::ImmDocumentGroup /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmFile /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmFile")
    .property("relPath", &org::imm::ImmFile /* d_orgimm_write */::relPath)
    .property("absPath", &org::imm::ImmFile /* d_orgimm_write */::absPath)
    .property("data", &org::imm::ImmFile /* d_orgimm_write */::data)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmFile /* d_orgimm_write */::*)() const>(&org::imm::ImmFile /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmFile /* d_orgimm_write */::*)(org::imm::ImmFile const& /* d_orgimm_write */) const>(&org::imm::ImmFile /* d_orgimm_write */::operator==))
    .function("isDocument", static_cast<bool(org::imm::ImmFile /* d_orgimm_write */::*)() const>(&org::imm::ImmFile /* d_orgimm_write */::isDocument))
    .function("getDocumentConst", static_cast<org::imm::ImmFile::Document const& /* imm_write */(org::imm::ImmFile /* d_orgimm_write */::*)() const>(&org::imm::ImmFile /* d_orgimm_write */::getDocument))
    .function("getDocumentMut", static_cast<org::imm::ImmFile::Document& /* imm_write */(org::imm::ImmFile /* d_orgimm_write */::*)()>(&org::imm::ImmFile /* d_orgimm_write */::getDocument))
    .function("isAttachment", static_cast<bool(org::imm::ImmFile /* d_orgimm_write */::*)() const>(&org::imm::ImmFile /* d_orgimm_write */::isAttachment))
    .function("getAttachmentConst", static_cast<org::imm::ImmFile::Attachment const& /* imm_write */(org::imm::ImmFile /* d_orgimm_write */::*)() const>(&org::imm::ImmFile /* d_orgimm_write */::getAttachment))
    .function("getAttachmentMut", static_cast<org::imm::ImmFile::Attachment& /* imm_write */(org::imm::ImmFile /* d_orgimm_write */::*)()>(&org::imm::ImmFile /* d_orgimm_write */::getAttachment))
    .function("isSource", static_cast<bool(org::imm::ImmFile /* d_orgimm_write */::*)() const>(&org::imm::ImmFile /* d_orgimm_write */::isSource))
    .function("getSourceConst", static_cast<org::imm::ImmFile::Source const& /* imm_write */(org::imm::ImmFile /* d_orgimm_write */::*)() const>(&org::imm::ImmFile /* d_orgimm_write */::getSource))
    .function("getSourceMut", static_cast<org::imm::ImmFile::Source& /* imm_write */(org::imm::ImmFile /* d_orgimm_write */::*)()>(&org::imm::ImmFile /* d_orgimm_write */::getSource))
    .class_function("getFileKindStatic", static_cast<org::imm::ImmFile::Kind /* imm_write */(*)(org::imm::ImmFile::Data const& /* imm_write */)>(&org::imm::ImmFile /* d_orgimm_write */::getFileKind))
    .function("getFileKind", static_cast<org::imm::ImmFile::Kind /* imm_write */(org::imm::ImmFile /* d_orgimm_write */::*)() const>(&org::imm::ImmFile /* d_orgimm_write */::getFileKind))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmFile::Document /* imm_write */>("ImmFileDocument")
    .function("__eq__", static_cast<bool(org::imm::ImmFile::Document /* imm_write */::*)(org::imm::ImmFile::Document const& /* imm_write */) const>(&org::imm::ImmFile::Document /* imm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmFile::Attachment /* imm_write */>("ImmFileAttachment")
    .function("__eq__", static_cast<bool(org::imm::ImmFile::Attachment /* imm_write */::*)(org::imm::ImmFile::Attachment const& /* imm_write */) const>(&org::imm::ImmFile::Attachment /* imm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmFile::Source /* imm_write */>("ImmFileSource")
    .function("__eq__", static_cast<bool(org::imm::ImmFile::Source /* imm_write */::*)(org::imm::ImmFile::Source const& /* imm_write */) const>(&org::imm::ImmFile::Source /* imm_write */::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::imm::ImmFile::Kind /* imm_write */>("ImmFileKind");
  emscripten::class_<org::imm::ImmDirectory /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmDirectory")
    .property("relPath", &org::imm::ImmDirectory /* d_orgimm_write */::relPath)
    .property("absPath", &org::imm::ImmDirectory /* d_orgimm_write */::absPath)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmDirectory /* d_orgimm_write */::*)() const>(&org::imm::ImmDirectory /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmDirectory /* d_orgimm_write */::*)(org::imm::ImmDirectory const& /* d_orgimm_write */) const>(&org::imm::ImmDirectory /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmSymlink /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmSymlink")
    .property("isDirectory", &org::imm::ImmSymlink /* d_orgimm_write */::isDirectory)
    .property("absPath", &org::imm::ImmSymlink /* d_orgimm_write */::absPath)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmSymlink /* d_orgimm_write */::*)() const>(&org::imm::ImmSymlink /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmSymlink /* d_orgimm_write */::*)(org::imm::ImmSymlink const& /* d_orgimm_write */) const>(&org::imm::ImmSymlink /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdInclude /* d_orgimm_write */, emscripten::base<org::imm::ImmOrg /* imm_write */>>("ImmCmdInclude")
    .property("path", &org::imm::ImmCmdInclude /* d_orgimm_write */::path)
    .property("firstLine", &org::imm::ImmCmdInclude /* d_orgimm_write */::firstLine)
    .property("lastLine", &org::imm::ImmCmdInclude /* d_orgimm_write */::lastLine)
    .property("data", &org::imm::ImmCmdInclude /* d_orgimm_write */::data)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCmdInclude /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdInclude /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdInclude /* d_orgimm_write */::*)(org::imm::ImmCmdInclude const& /* d_orgimm_write */) const>(&org::imm::ImmCmdInclude /* d_orgimm_write */::operator==))
    .function("isExample", static_cast<bool(org::imm::ImmCmdInclude /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdInclude /* d_orgimm_write */::isExample))
    .function("getExampleConst", static_cast<org::imm::ImmCmdInclude::Example const& /* imm_write */(org::imm::ImmCmdInclude /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdInclude /* d_orgimm_write */::getExample))
    .function("getExampleMut", static_cast<org::imm::ImmCmdInclude::Example& /* imm_write */(org::imm::ImmCmdInclude /* d_orgimm_write */::*)()>(&org::imm::ImmCmdInclude /* d_orgimm_write */::getExample))
    .function("isExport", static_cast<bool(org::imm::ImmCmdInclude /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdInclude /* d_orgimm_write */::isExport))
    .function("getExportConst", static_cast<org::imm::ImmCmdInclude::Export const& /* imm_write */(org::imm::ImmCmdInclude /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdInclude /* d_orgimm_write */::getExport))
    .function("getExportMut", static_cast<org::imm::ImmCmdInclude::Export& /* imm_write */(org::imm::ImmCmdInclude /* d_orgimm_write */::*)()>(&org::imm::ImmCmdInclude /* d_orgimm_write */::getExport))
    .function("isCustom", static_cast<bool(org::imm::ImmCmdInclude /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdInclude /* d_orgimm_write */::isCustom))
    .function("getCustomConst", static_cast<org::imm::ImmCmdInclude::Custom const& /* imm_write */(org::imm::ImmCmdInclude /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdInclude /* d_orgimm_write */::getCustom))
    .function("getCustomMut", static_cast<org::imm::ImmCmdInclude::Custom& /* imm_write */(org::imm::ImmCmdInclude /* d_orgimm_write */::*)()>(&org::imm::ImmCmdInclude /* d_orgimm_write */::getCustom))
    .function("isSrc", static_cast<bool(org::imm::ImmCmdInclude /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdInclude /* d_orgimm_write */::isSrc))
    .function("getSrcConst", static_cast<org::imm::ImmCmdInclude::Src const& /* imm_write */(org::imm::ImmCmdInclude /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdInclude /* d_orgimm_write */::getSrc))
    .function("getSrcMut", static_cast<org::imm::ImmCmdInclude::Src& /* imm_write */(org::imm::ImmCmdInclude /* d_orgimm_write */::*)()>(&org::imm::ImmCmdInclude /* d_orgimm_write */::getSrc))
    .function("isOrgDocument", static_cast<bool(org::imm::ImmCmdInclude /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdInclude /* d_orgimm_write */::isOrgDocument))
    .function("getOrgDocumentConst", static_cast<org::imm::ImmCmdInclude::OrgDocument const& /* imm_write */(org::imm::ImmCmdInclude /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdInclude /* d_orgimm_write */::getOrgDocument))
    .function("getOrgDocumentMut", static_cast<org::imm::ImmCmdInclude::OrgDocument& /* imm_write */(org::imm::ImmCmdInclude /* d_orgimm_write */::*)()>(&org::imm::ImmCmdInclude /* d_orgimm_write */::getOrgDocument))
    .class_function("getIncludeKindStatic", static_cast<org::imm::ImmCmdInclude::Kind /* imm_write */(*)(org::imm::ImmCmdInclude::Data const& /* imm_write */)>(&org::imm::ImmCmdInclude /* d_orgimm_write */::getIncludeKind))
    .function("getIncludeKind", static_cast<org::imm::ImmCmdInclude::Kind /* imm_write */(org::imm::ImmCmdInclude /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdInclude /* d_orgimm_write */::getIncludeKind))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdInclude::IncludeBase /* imm_write */>("ImmCmdIncludeIncludeBase")
    .function("__eq__", static_cast<bool(org::imm::ImmCmdInclude::IncludeBase /* imm_write */::*)(org::imm::ImmCmdInclude::IncludeBase const& /* imm_write */) const>(&org::imm::ImmCmdInclude::IncludeBase /* imm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdInclude::Example /* imm_write */, emscripten::base<org::imm::ImmCmdInclude::IncludeBase /* imm_write */>>("ImmCmdIncludeExample")
    .function("__eq__", static_cast<bool(org::imm::ImmCmdInclude::Example /* imm_write */::*)(org::imm::ImmCmdInclude::Example const& /* imm_write */) const>(&org::imm::ImmCmdInclude::Example /* imm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdInclude::Export /* imm_write */, emscripten::base<org::imm::ImmCmdInclude::IncludeBase /* imm_write */>>("ImmCmdIncludeExport")
    .property("language", &org::imm::ImmCmdInclude::Export /* imm_write */::language)
    .function("__eq__", static_cast<bool(org::imm::ImmCmdInclude::Export /* imm_write */::*)(org::imm::ImmCmdInclude::Export const& /* imm_write */) const>(&org::imm::ImmCmdInclude::Export /* imm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdInclude::Custom /* imm_write */, emscripten::base<org::imm::ImmCmdInclude::IncludeBase /* imm_write */>>("ImmCmdIncludeCustom")
    .property("blockName", &org::imm::ImmCmdInclude::Custom /* imm_write */::blockName)
    .function("__eq__", static_cast<bool(org::imm::ImmCmdInclude::Custom /* imm_write */::*)(org::imm::ImmCmdInclude::Custom const& /* imm_write */) const>(&org::imm::ImmCmdInclude::Custom /* imm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdInclude::Src /* imm_write */, emscripten::base<org::imm::ImmCmdInclude::IncludeBase /* imm_write */>>("ImmCmdIncludeSrc")
    .property("language", &org::imm::ImmCmdInclude::Src /* imm_write */::language)
    .function("__eq__", static_cast<bool(org::imm::ImmCmdInclude::Src /* imm_write */::*)(org::imm::ImmCmdInclude::Src const& /* imm_write */) const>(&org::imm::ImmCmdInclude::Src /* imm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdInclude::OrgDocument /* imm_write */, emscripten::base<org::imm::ImmCmdInclude::IncludeBase /* imm_write */>>("ImmCmdIncludeOrgDocument")
    .property("onlyContent", &org::imm::ImmCmdInclude::OrgDocument /* imm_write */::onlyContent)
    .property("subtreePath", &org::imm::ImmCmdInclude::OrgDocument /* imm_write */::subtreePath)
    .property("minLevel", &org::imm::ImmCmdInclude::OrgDocument /* imm_write */::minLevel)
    .property("customIdTarget", &org::imm::ImmCmdInclude::OrgDocument /* imm_write */::customIdTarget)
    .function("__eq__", static_cast<bool(org::imm::ImmCmdInclude::OrgDocument /* imm_write */::*)(org::imm::ImmCmdInclude::OrgDocument const& /* imm_write */) const>(&org::imm::ImmCmdInclude::OrgDocument /* imm_write */::operator==))
    .constructor<>()
    ;
  org::bind::js::bind_enum<org::imm::ImmCmdInclude::Kind /* imm_write */>("ImmCmdIncludeKind");
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1343:17( [780] >record 'ImmAdapterOrgAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterVirtualBase /*  [905]imm/ImmOrg.hpp:1343:17( [780] >record 'ImmAdapterVirtualBase'<>) */>>("ImmAdapterOrgAPI")
    ;
  emscripten::class_<org::sem::Cmd /* d_org */, emscripten::base<org::sem::Stmt>>("Cmd")
    .smart_ptr<org::sem::SemId<org::sem::Cmd /* d_org */>>("Cmd")
    .property("attrs", &org::sem::Cmd /* d_org */::attrs)
    .function("getAttrs", static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Cmd /* d_org */::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Cmd /* d_org */::getAttrs))
    .function("getFirstAttr", static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Cmd /* d_org */::*)(hstd::Str const&) const>(&org::sem::Cmd /* d_org */::getFirstAttr))
    ;
  emscripten::class_<org::sem::CmdCustomRaw /* d_org */, emscripten::base<org::sem::Stmt>>("CmdCustomRaw")
    .smart_ptr<org::sem::SemId<org::sem::CmdCustomRaw /* d_org */>>("CmdCustomRaw")
    .property("name", &org::sem::CmdCustomRaw /* d_org */::name)
    .property("isAttached", &org::sem::CmdCustomRaw /* d_org */::isAttached)
    .property("text", &org::sem::CmdCustomRaw /* d_org */::text)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdCustomRaw /* d_org */::*)() const>(&org::sem::CmdCustomRaw /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdCustomRaw /* d_org */>>)
    ;
  emscripten::class_<org::sem::CmdCustomText /* d_org */, emscripten::base<org::sem::Stmt>>("CmdCustomText")
    .smart_ptr<org::sem::SemId<org::sem::CmdCustomText /* d_org */>>("CmdCustomText")
    .property("name", &org::sem::CmdCustomText /* d_org */::name)
    .property("isAttached", &org::sem::CmdCustomText /* d_org */::isAttached)
    .property("text", &org::sem::CmdCustomText /* d_org */::text)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdCustomText /* d_org */::*)() const>(&org::sem::CmdCustomText /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdCustomText /* d_org */>>)
    ;
  emscripten::class_<org::sem::Link /* d_org */, emscripten::base<org::sem::Stmt>>("Link")
    .smart_ptr<org::sem::SemId<org::sem::Link /* d_org */>>("Link")
    .property("description", &org::sem::Link /* d_org */::description)
    .property("target", &org::sem::Link /* d_org */::target)
    .function("getKind", static_cast<OrgSemKind(org::sem::Link /* d_org */::*)() const>(&org::sem::Link /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Link /* d_org */>>)
    ;
  emscripten::class_<org::sem::BlockComment /* d_org */, emscripten::base<org::sem::Stmt>>("BlockComment")
    .smart_ptr<org::sem::SemId<org::sem::BlockComment /* d_org */>>("BlockComment")
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockComment /* d_org */::*)() const>(&org::sem::BlockComment /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockComment /* d_org */>>)
    ;
  emscripten::class_<org::sem::Paragraph /* d_org */, emscripten::base<org::sem::Stmt>>("Paragraph")
    .smart_ptr<org::sem::SemId<org::sem::Paragraph /* d_org */>>("Paragraph")
    .function("getKind", static_cast<OrgSemKind(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::getKind))
    .function("isFootnoteDefinition", static_cast<bool(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::isFootnoteDefinition))
    .function("getFootnoteName", static_cast<hstd::Opt<hstd::Str>(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::getFootnoteName))
    .function("hasAdmonition", static_cast<bool(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::hasAdmonition))
    .function("getAdmonitions", static_cast<hstd::Vec<hstd::Str>(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::getAdmonitions))
    .function("getAdmonitionNodes", static_cast<hstd::Vec<org::sem::SemId<org::sem::BigIdent>>(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::getAdmonitionNodes))
    .function("hasTimestamp", static_cast<bool(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::hasTimestamp))
    .function("getTimestamps", static_cast<hstd::Vec<hstd::UserTime>(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::getTimestamps))
    .function("getTimestampNodes", static_cast<hstd::Vec<org::sem::SemId<org::sem::Time>>(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::getTimestampNodes))
    .function("hasLeadHashtags", static_cast<bool(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::hasLeadHashtags))
    .function("getLeadHashtags", static_cast<hstd::Vec<org::sem::SemId<org::sem::HashTag>>(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::getLeadHashtags))
    .function("getBody", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::getBody))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Paragraph /* d_org */>>)
    ;
  emscripten::class_<org::sem::List /* d_org */, emscripten::base<org::sem::Stmt>>("List")
    .smart_ptr<org::sem::SemId<org::sem::List /* d_org */>>("List")
    .function("getKind", static_cast<OrgSemKind(org::sem::List /* d_org */::*)() const>(&org::sem::List /* d_org */::getKind))
    .function("getListAttrs", static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::List /* d_org */::*)(hstd::Str const&) const>(&org::sem::List /* d_org */::getListAttrs))
    .function("getListFormattingMode", static_cast<ListFormattingMode(org::sem::List /* d_org */::*)() const>(&org::sem::List /* d_org */::getListFormattingMode))
    .function("isDescriptionList", static_cast<bool(org::sem::List /* d_org */::*)() const>(&org::sem::List /* d_org */::isDescriptionList))
    .function("isNumberedList", static_cast<bool(org::sem::List /* d_org */::*)() const>(&org::sem::List /* d_org */::isNumberedList))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::List /* d_org */>>)
    ;
  emscripten::class_<org::sem::HashTag /* d_org */, emscripten::base<org::sem::Inline>>("HashTag")
    .smart_ptr<org::sem::SemId<org::sem::HashTag /* d_org */>>("HashTag")
    .property("text", &org::sem::HashTag /* d_org */::text)
    .function("getKind", static_cast<OrgSemKind(org::sem::HashTag /* d_org */::*)() const>(&org::sem::HashTag /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::HashTag /* d_org */>>)
    ;
  emscripten::class_<org::sem::InlineFootnote /* d_org */, emscripten::base<org::sem::Inline>>("InlineFootnote")
    .smart_ptr<org::sem::SemId<org::sem::InlineFootnote /* d_org */>>("InlineFootnote")
    .property("tag", &org::sem::InlineFootnote /* d_org */::tag)
    .property("definition", &org::sem::InlineFootnote /* d_org */::definition)
    .function("getKind", static_cast<OrgSemKind(org::sem::InlineFootnote /* d_org */::*)() const>(&org::sem::InlineFootnote /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::InlineFootnote /* d_org */>>)
    ;
  emscripten::class_<org::sem::InlineExport /* d_org */, emscripten::base<org::sem::Inline>>("InlineExport")
    .smart_ptr<org::sem::SemId<org::sem::InlineExport /* d_org */>>("InlineExport")
    .property("exporter", &org::sem::InlineExport /* d_org */::exporter)
    .property("content", &org::sem::InlineExport /* d_org */::content)
    .function("getKind", static_cast<OrgSemKind(org::sem::InlineExport /* d_org */::*)() const>(&org::sem::InlineExport /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::InlineExport /* d_org */>>)
    ;
  emscripten::class_<org::sem::Escaped /* d_org */, emscripten::base<org::sem::Leaf>>("Escaped")
    .smart_ptr<org::sem::SemId<org::sem::Escaped /* d_org */>>("Escaped")
    .function("getKind", static_cast<OrgSemKind(org::sem::Escaped /* d_org */::*)() const>(&org::sem::Escaped /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Escaped /* d_org */>>)
    ;
  emscripten::class_<org::sem::Newline /* d_org */, emscripten::base<org::sem::Leaf>>("Newline")
    .smart_ptr<org::sem::SemId<org::sem::Newline /* d_org */>>("Newline")
    .function("getKind", static_cast<OrgSemKind(org::sem::Newline /* d_org */::*)() const>(&org::sem::Newline /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Newline /* d_org */>>)
    ;
  emscripten::class_<org::sem::Space /* d_org */, emscripten::base<org::sem::Leaf>>("Space")
    .smart_ptr<org::sem::SemId<org::sem::Space /* d_org */>>("Space")
    .function("getKind", static_cast<OrgSemKind(org::sem::Space /* d_org */::*)() const>(&org::sem::Space /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Space /* d_org */>>)
    ;
  emscripten::class_<org::sem::Word /* d_org */, emscripten::base<org::sem::Leaf>>("Word")
    .smart_ptr<org::sem::SemId<org::sem::Word /* d_org */>>("Word")
    .function("getKind", static_cast<OrgSemKind(org::sem::Word /* d_org */::*)() const>(&org::sem::Word /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Word /* d_org */>>)
    ;
  emscripten::class_<org::sem::AtMention /* d_org */, emscripten::base<org::sem::Leaf>>("AtMention")
    .smart_ptr<org::sem::SemId<org::sem::AtMention /* d_org */>>("AtMention")
    .function("getKind", static_cast<OrgSemKind(org::sem::AtMention /* d_org */::*)() const>(&org::sem::AtMention /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::AtMention /* d_org */>>)
    ;
  emscripten::class_<org::sem::RawText /* d_org */, emscripten::base<org::sem::Leaf>>("RawText")
    .smart_ptr<org::sem::SemId<org::sem::RawText /* d_org */>>("RawText")
    .function("getKind", static_cast<OrgSemKind(org::sem::RawText /* d_org */::*)() const>(&org::sem::RawText /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::RawText /* d_org */>>)
    ;
  emscripten::class_<org::sem::Punctuation /* d_org */, emscripten::base<org::sem::Leaf>>("Punctuation")
    .smart_ptr<org::sem::SemId<org::sem::Punctuation /* d_org */>>("Punctuation")
    .function("getKind", static_cast<OrgSemKind(org::sem::Punctuation /* d_org */::*)() const>(&org::sem::Punctuation /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Punctuation /* d_org */>>)
    ;
  emscripten::class_<org::sem::Placeholder /* d_org */, emscripten::base<org::sem::Leaf>>("Placeholder")
    .smart_ptr<org::sem::SemId<org::sem::Placeholder /* d_org */>>("Placeholder")
    .function("getKind", static_cast<OrgSemKind(org::sem::Placeholder /* d_org */::*)() const>(&org::sem::Placeholder /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Placeholder /* d_org */>>)
    ;
  emscripten::class_<org::sem::BigIdent /* d_org */, emscripten::base<org::sem::Leaf>>("BigIdent")
    .smart_ptr<org::sem::SemId<org::sem::BigIdent /* d_org */>>("BigIdent")
    .function("getKind", static_cast<OrgSemKind(org::sem::BigIdent /* d_org */::*)() const>(&org::sem::BigIdent /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BigIdent /* d_org */>>)
    ;
  emscripten::class_<org::sem::TextTarget /* d_org */, emscripten::base<org::sem::Leaf>>("TextTarget")
    .smart_ptr<org::sem::SemId<org::sem::TextTarget /* d_org */>>("TextTarget")
    .function("getKind", static_cast<OrgSemKind(org::sem::TextTarget /* d_org */::*)() const>(&org::sem::TextTarget /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::TextTarget /* d_org */>>)
    ;
  emscripten::class_<org::sem::ErrorSkipToken /* d_org */, emscripten::base<org::sem::Leaf>>("ErrorSkipToken")
    .smart_ptr<org::sem::SemId<org::sem::ErrorSkipToken /* d_org */>>("ErrorSkipToken")
    .function("getKind", static_cast<OrgSemKind(org::sem::ErrorSkipToken /* d_org */::*)() const>(&org::sem::ErrorSkipToken /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::ErrorSkipToken /* d_org */>>)
    ;
  emscripten::class_<org::sem::Bold /* d_org */, emscripten::base<org::sem::Markup>>("Bold")
    .smart_ptr<org::sem::SemId<org::sem::Bold /* d_org */>>("Bold")
    .function("getKind", static_cast<OrgSemKind(org::sem::Bold /* d_org */::*)() const>(&org::sem::Bold /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Bold /* d_org */>>)
    ;
  emscripten::class_<org::sem::Underline /* d_org */, emscripten::base<org::sem::Markup>>("Underline")
    .smart_ptr<org::sem::SemId<org::sem::Underline /* d_org */>>("Underline")
    .function("getKind", static_cast<OrgSemKind(org::sem::Underline /* d_org */::*)() const>(&org::sem::Underline /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Underline /* d_org */>>)
    ;
  emscripten::class_<org::sem::Monospace /* d_org */, emscripten::base<org::sem::Markup>>("Monospace")
    .smart_ptr<org::sem::SemId<org::sem::Monospace /* d_org */>>("Monospace")
    .function("getKind", static_cast<OrgSemKind(org::sem::Monospace /* d_org */::*)() const>(&org::sem::Monospace /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Monospace /* d_org */>>)
    ;
  emscripten::class_<org::sem::MarkQuote /* d_org */, emscripten::base<org::sem::Markup>>("MarkQuote")
    .smart_ptr<org::sem::SemId<org::sem::MarkQuote /* d_org */>>("MarkQuote")
    .function("getKind", static_cast<OrgSemKind(org::sem::MarkQuote /* d_org */::*)() const>(&org::sem::MarkQuote /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::MarkQuote /* d_org */>>)
    ;
  emscripten::class_<org::sem::Verbatim /* d_org */, emscripten::base<org::sem::Markup>>("Verbatim")
    .smart_ptr<org::sem::SemId<org::sem::Verbatim /* d_org */>>("Verbatim")
    .function("getKind", static_cast<OrgSemKind(org::sem::Verbatim /* d_org */::*)() const>(&org::sem::Verbatim /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Verbatim /* d_org */>>)
    ;
  emscripten::class_<org::sem::Italic /* d_org */, emscripten::base<org::sem::Markup>>("Italic")
    .smart_ptr<org::sem::SemId<org::sem::Italic /* d_org */>>("Italic")
    .function("getKind", static_cast<OrgSemKind(org::sem::Italic /* d_org */::*)() const>(&org::sem::Italic /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Italic /* d_org */>>)
    ;
  emscripten::class_<org::sem::Strike /* d_org */, emscripten::base<org::sem::Markup>>("Strike")
    .smart_ptr<org::sem::SemId<org::sem::Strike /* d_org */>>("Strike")
    .function("getKind", static_cast<OrgSemKind(org::sem::Strike /* d_org */::*)() const>(&org::sem::Strike /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Strike /* d_org */>>)
    ;
  emscripten::class_<org::sem::Par /* d_org */, emscripten::base<org::sem::Markup>>("Par")
    .smart_ptr<org::sem::SemId<org::sem::Par /* d_org */>>("Par")
    .function("getKind", static_cast<OrgSemKind(org::sem::Par /* d_org */::*)() const>(&org::sem::Par /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Par /* d_org */>>)
    ;
  emscripten::class_<org::imm::ImmCmd /* d_orgimm_write */, emscripten::base<org::imm::ImmStmt /* imm_write */>>("ImmCmd")
    .property("attrs", &org::imm::ImmCmd /* d_orgimm_write */::attrs)
    .function("__eq__", static_cast<bool(org::imm::ImmCmd /* d_orgimm_write */::*)(org::imm::ImmCmd const& /* d_orgimm_write */) const>(&org::imm::ImmCmd /* d_orgimm_write */::operator==))
    ;
  emscripten::class_<org::imm::ImmCmdCustomRaw /* d_orgimm_write */, emscripten::base<org::imm::ImmStmt /* imm_write */>>("ImmCmdCustomRaw")
    .property("name", &org::imm::ImmCmdCustomRaw /* d_orgimm_write */::name)
    .property("isAttached", &org::imm::ImmCmdCustomRaw /* d_orgimm_write */::isAttached)
    .property("text", &org::imm::ImmCmdCustomRaw /* d_orgimm_write */::text)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCmdCustomRaw /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdCustomRaw /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdCustomRaw /* d_orgimm_write */::*)(org::imm::ImmCmdCustomRaw const& /* d_orgimm_write */) const>(&org::imm::ImmCmdCustomRaw /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdCustomText /* d_orgimm_write */, emscripten::base<org::imm::ImmStmt /* imm_write */>>("ImmCmdCustomText")
    .property("name", &org::imm::ImmCmdCustomText /* d_orgimm_write */::name)
    .property("isAttached", &org::imm::ImmCmdCustomText /* d_orgimm_write */::isAttached)
    .property("text", &org::imm::ImmCmdCustomText /* d_orgimm_write */::text)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCmdCustomText /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdCustomText /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdCustomText /* d_orgimm_write */::*)(org::imm::ImmCmdCustomText const& /* d_orgimm_write */) const>(&org::imm::ImmCmdCustomText /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmLink /* d_orgimm_write */, emscripten::base<org::imm::ImmStmt /* imm_write */>>("ImmLink")
    .property("description", &org::imm::ImmLink /* d_orgimm_write */::description)
    .property("target", &org::imm::ImmLink /* d_orgimm_write */::target)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmLink /* d_orgimm_write */::*)() const>(&org::imm::ImmLink /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmLink /* d_orgimm_write */::*)(org::imm::ImmLink const& /* d_orgimm_write */) const>(&org::imm::ImmLink /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockComment /* d_orgimm_write */, emscripten::base<org::imm::ImmStmt /* imm_write */>>("ImmBlockComment")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmBlockComment /* d_orgimm_write */::*)() const>(&org::imm::ImmBlockComment /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockComment /* d_orgimm_write */::*)(org::imm::ImmBlockComment const& /* d_orgimm_write */) const>(&org::imm::ImmBlockComment /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmParagraph /* d_orgimm_write */, emscripten::base<org::imm::ImmStmt /* imm_write */>>("ImmParagraph")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmParagraph /* d_orgimm_write */::*)() const>(&org::imm::ImmParagraph /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmParagraph /* d_orgimm_write */::*)(org::imm::ImmParagraph const& /* d_orgimm_write */) const>(&org::imm::ImmParagraph /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmList /* d_orgimm_write */, emscripten::base<org::imm::ImmStmt /* imm_write */>>("ImmList")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmList /* d_orgimm_write */::*)() const>(&org::imm::ImmList /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmList /* d_orgimm_write */::*)(org::imm::ImmList const& /* d_orgimm_write */) const>(&org::imm::ImmList /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmHashTag /* d_orgimm_write */, emscripten::base<org::imm::ImmInline /* imm_write */>>("ImmHashTag")
    .property("text", &org::imm::ImmHashTag /* d_orgimm_write */::text)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmHashTag /* d_orgimm_write */::*)() const>(&org::imm::ImmHashTag /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmHashTag /* d_orgimm_write */::*)(org::imm::ImmHashTag const& /* d_orgimm_write */) const>(&org::imm::ImmHashTag /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmInlineFootnote /* d_orgimm_write */, emscripten::base<org::imm::ImmInline /* imm_write */>>("ImmInlineFootnote")
    .property("tag", &org::imm::ImmInlineFootnote /* d_orgimm_write */::tag)
    .property("definition", &org::imm::ImmInlineFootnote /* d_orgimm_write */::definition)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmInlineFootnote /* d_orgimm_write */::*)() const>(&org::imm::ImmInlineFootnote /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmInlineFootnote /* d_orgimm_write */::*)(org::imm::ImmInlineFootnote const& /* d_orgimm_write */) const>(&org::imm::ImmInlineFootnote /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmInlineExport /* d_orgimm_write */, emscripten::base<org::imm::ImmInline /* imm_write */>>("ImmInlineExport")
    .property("exporter", &org::imm::ImmInlineExport /* d_orgimm_write */::exporter)
    .property("content", &org::imm::ImmInlineExport /* d_orgimm_write */::content)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmInlineExport /* d_orgimm_write */::*)() const>(&org::imm::ImmInlineExport /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmInlineExport /* d_orgimm_write */::*)(org::imm::ImmInlineExport const& /* d_orgimm_write */) const>(&org::imm::ImmInlineExport /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
}

void subdivide_6(org::bind::js::type_registration_guard& g) {
  emscripten::class_<org::imm::ImmEscaped /* d_orgimm_write */, emscripten::base<org::imm::ImmLeaf /* imm_write */>>("ImmEscaped")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmEscaped /* d_orgimm_write */::*)() const>(&org::imm::ImmEscaped /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmEscaped /* d_orgimm_write */::*)(org::imm::ImmEscaped const& /* d_orgimm_write */) const>(&org::imm::ImmEscaped /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmNewline /* d_orgimm_write */, emscripten::base<org::imm::ImmLeaf /* imm_write */>>("ImmNewline")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmNewline /* d_orgimm_write */::*)() const>(&org::imm::ImmNewline /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmNewline /* d_orgimm_write */::*)(org::imm::ImmNewline const& /* d_orgimm_write */) const>(&org::imm::ImmNewline /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmSpace /* d_orgimm_write */, emscripten::base<org::imm::ImmLeaf /* imm_write */>>("ImmSpace")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmSpace /* d_orgimm_write */::*)() const>(&org::imm::ImmSpace /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmSpace /* d_orgimm_write */::*)(org::imm::ImmSpace const& /* d_orgimm_write */) const>(&org::imm::ImmSpace /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmWord /* d_orgimm_write */, emscripten::base<org::imm::ImmLeaf /* imm_write */>>("ImmWord")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmWord /* d_orgimm_write */::*)() const>(&org::imm::ImmWord /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmWord /* d_orgimm_write */::*)(org::imm::ImmWord const& /* d_orgimm_write */) const>(&org::imm::ImmWord /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmAtMention /* d_orgimm_write */, emscripten::base<org::imm::ImmLeaf /* imm_write */>>("ImmAtMention")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmAtMention /* d_orgimm_write */::*)() const>(&org::imm::ImmAtMention /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmAtMention /* d_orgimm_write */::*)(org::imm::ImmAtMention const& /* d_orgimm_write */) const>(&org::imm::ImmAtMention /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmRawText /* d_orgimm_write */, emscripten::base<org::imm::ImmLeaf /* imm_write */>>("ImmRawText")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmRawText /* d_orgimm_write */::*)() const>(&org::imm::ImmRawText /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmRawText /* d_orgimm_write */::*)(org::imm::ImmRawText const& /* d_orgimm_write */) const>(&org::imm::ImmRawText /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmPunctuation /* d_orgimm_write */, emscripten::base<org::imm::ImmLeaf /* imm_write */>>("ImmPunctuation")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmPunctuation /* d_orgimm_write */::*)() const>(&org::imm::ImmPunctuation /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmPunctuation /* d_orgimm_write */::*)(org::imm::ImmPunctuation const& /* d_orgimm_write */) const>(&org::imm::ImmPunctuation /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmPlaceholder /* d_orgimm_write */, emscripten::base<org::imm::ImmLeaf /* imm_write */>>("ImmPlaceholder")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmPlaceholder /* d_orgimm_write */::*)() const>(&org::imm::ImmPlaceholder /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmPlaceholder /* d_orgimm_write */::*)(org::imm::ImmPlaceholder const& /* d_orgimm_write */) const>(&org::imm::ImmPlaceholder /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBigIdent /* d_orgimm_write */, emscripten::base<org::imm::ImmLeaf /* imm_write */>>("ImmBigIdent")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmBigIdent /* d_orgimm_write */::*)() const>(&org::imm::ImmBigIdent /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBigIdent /* d_orgimm_write */::*)(org::imm::ImmBigIdent const& /* d_orgimm_write */) const>(&org::imm::ImmBigIdent /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmTextTarget /* d_orgimm_write */, emscripten::base<org::imm::ImmLeaf /* imm_write */>>("ImmTextTarget")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmTextTarget /* d_orgimm_write */::*)() const>(&org::imm::ImmTextTarget /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmTextTarget /* d_orgimm_write */::*)(org::imm::ImmTextTarget const& /* d_orgimm_write */) const>(&org::imm::ImmTextTarget /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmErrorSkipToken /* d_orgimm_write */, emscripten::base<org::imm::ImmLeaf /* imm_write */>>("ImmErrorSkipToken")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmErrorSkipToken /* d_orgimm_write */::*)() const>(&org::imm::ImmErrorSkipToken /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmErrorSkipToken /* d_orgimm_write */::*)(org::imm::ImmErrorSkipToken const& /* d_orgimm_write */) const>(&org::imm::ImmErrorSkipToken /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBold /* d_orgimm_write */, emscripten::base<org::imm::ImmMarkup /* imm_write */>>("ImmBold")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmBold /* d_orgimm_write */::*)() const>(&org::imm::ImmBold /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBold /* d_orgimm_write */::*)(org::imm::ImmBold const& /* d_orgimm_write */) const>(&org::imm::ImmBold /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmUnderline /* d_orgimm_write */, emscripten::base<org::imm::ImmMarkup /* imm_write */>>("ImmUnderline")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmUnderline /* d_orgimm_write */::*)() const>(&org::imm::ImmUnderline /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmUnderline /* d_orgimm_write */::*)(org::imm::ImmUnderline const& /* d_orgimm_write */) const>(&org::imm::ImmUnderline /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmMonospace /* d_orgimm_write */, emscripten::base<org::imm::ImmMarkup /* imm_write */>>("ImmMonospace")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmMonospace /* d_orgimm_write */::*)() const>(&org::imm::ImmMonospace /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmMonospace /* d_orgimm_write */::*)(org::imm::ImmMonospace const& /* d_orgimm_write */) const>(&org::imm::ImmMonospace /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmMarkQuote /* d_orgimm_write */, emscripten::base<org::imm::ImmMarkup /* imm_write */>>("ImmMarkQuote")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmMarkQuote /* d_orgimm_write */::*)() const>(&org::imm::ImmMarkQuote /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmMarkQuote /* d_orgimm_write */::*)(org::imm::ImmMarkQuote const& /* d_orgimm_write */) const>(&org::imm::ImmMarkQuote /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmVerbatim /* d_orgimm_write */, emscripten::base<org::imm::ImmMarkup /* imm_write */>>("ImmVerbatim")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmVerbatim /* d_orgimm_write */::*)() const>(&org::imm::ImmVerbatim /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmVerbatim /* d_orgimm_write */::*)(org::imm::ImmVerbatim const& /* d_orgimm_write */) const>(&org::imm::ImmVerbatim /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmItalic /* d_orgimm_write */, emscripten::base<org::imm::ImmMarkup /* imm_write */>>("ImmItalic")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmItalic /* d_orgimm_write */::*)() const>(&org::imm::ImmItalic /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmItalic /* d_orgimm_write */::*)(org::imm::ImmItalic const& /* d_orgimm_write */) const>(&org::imm::ImmItalic /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmStrike /* d_orgimm_write */, emscripten::base<org::imm::ImmMarkup /* imm_write */>>("ImmStrike")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmStrike /* d_orgimm_write */::*)() const>(&org::imm::ImmStrike /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmStrike /* d_orgimm_write */::*)(org::imm::ImmStrike const& /* d_orgimm_write */) const>(&org::imm::ImmStrike /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmPar /* d_orgimm_write */, emscripten::base<org::imm::ImmMarkup /* imm_write */>>("ImmPar")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmPar /* d_orgimm_write */::*)() const>(&org::imm::ImmPar /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmPar /* d_orgimm_write */::*)(org::imm::ImmPar const& /* d_orgimm_write */) const>(&org::imm::ImmPar /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtAPI /*  [905]imm/ImmOrg.hpp:1345:17( [780] >record 'ImmAdapterStmtAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1345:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterStmtAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterSubtreeAPI /*  [905]imm/ImmOrg.hpp:1365:17( [780] >record 'ImmAdapterSubtreeAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1365:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterSubtreeAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterNoNodeAPI /*  [905]imm/ImmOrg.hpp:1384:17( [780] >record 'ImmAdapterNoNodeAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1384:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterNoNodeAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttrAPI /*  [905]imm/ImmOrg.hpp:1385:17( [780] >record 'ImmAdapterAttrAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1385:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterAttrAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttrListAPI /*  [905]imm/ImmOrg.hpp:1386:17( [780] >record 'ImmAdapterAttrListAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1386:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterAttrListAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttrsAPI /*  [905]imm/ImmOrg.hpp:1387:17( [780] >record 'ImmAdapterAttrsAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1387:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterAttrsAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterErrorItemAPI /*  [905]imm/ImmOrg.hpp:1388:17( [780] >record 'ImmAdapterErrorItemAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1388:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterErrorItemAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterErrorGroupAPI /*  [905]imm/ImmOrg.hpp:1389:17( [780] >record 'ImmAdapterErrorGroupAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1389:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterErrorGroupAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterErrorSkipGroupAPI /*  [905]imm/ImmOrg.hpp:1390:17( [780] >record 'ImmAdapterErrorSkipGroupAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1390:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterErrorSkipGroupAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterErrorSkipTokenAPI /*  [905]imm/ImmOrg.hpp:1391:17( [780] >record 'ImmAdapterErrorSkipTokenAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1391:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterErrorSkipTokenAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtListAPI /*  [905]imm/ImmOrg.hpp:1392:17( [780] >record 'ImmAdapterStmtListAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1392:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterStmtListAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterEmptyAPI /*  [905]imm/ImmOrg.hpp:1393:17( [780] >record 'ImmAdapterEmptyAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1393:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterEmptyAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterInlineAPI /*  [905]imm/ImmOrg.hpp:1411:17( [780] >record 'ImmAdapterInlineAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1411:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterInlineAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterTimeAPI /*  [905]imm/ImmOrg.hpp:1414:17( [780] >record 'ImmAdapterTimeAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1414:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterTimeAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterTimeRangeAPI /*  [905]imm/ImmOrg.hpp:1423:17( [780] >record 'ImmAdapterTimeRangeAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1423:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterTimeRangeAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMacroAPI /*  [905]imm/ImmOrg.hpp:1424:17( [780] >record 'ImmAdapterMacroAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1424:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterMacroAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterSymbolAPI /*  [905]imm/ImmOrg.hpp:1425:17( [780] >record 'ImmAdapterSymbolAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1425:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterSymbolAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1426:17( [780] >record 'ImmAdapterLeafAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1426:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterLeafAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1439:17( [780] >record 'ImmAdapterMarkupAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1439:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterMarkupAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLatexAPI /*  [905]imm/ImmOrg.hpp:1449:17( [780] >record 'ImmAdapterLatexAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1449:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterLatexAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterSubtreeLogAPI /*  [905]imm/ImmOrg.hpp:1466:17( [780] >record 'ImmAdapterSubtreeLogAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1466:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterSubtreeLogAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterColonExampleAPI /*  [905]imm/ImmOrg.hpp:1485:17( [780] >record 'ImmAdapterColonExampleAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1485:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterColonExampleAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCallAPI /*  [905]imm/ImmOrg.hpp:1487:17( [780] >record 'ImmAdapterCallAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1487:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterCallAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterFileAPI /*  [905]imm/ImmOrg.hpp:1488:17( [780] >record 'ImmAdapterFileAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1488:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterFileAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterDirectoryAPI /*  [905]imm/ImmOrg.hpp:1489:17( [780] >record 'ImmAdapterDirectoryAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1489:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterDirectoryAPI")
    .function("getFsSubnode", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [640]Type parameter [905]imm/ImmOrg.hpp:1490:46( [780] >record 'ImmAdapter'<>) */> /*  [905]imm/ImmOrg.hpp:1490:46( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterDirectoryAPI /*  [905]imm/ImmOrg.hpp:1489:17( [780] >record 'ImmAdapterDirectoryAPI'<>) */::*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str const& /*  [905]imm/ImmOrg.hpp:1491:26( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Str'<>)<>) */, bool /*  [905]imm/ImmOrg.hpp:1492:26( [755] >bool<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterDirectoryAPI /*  [905]imm/ImmOrg.hpp:1489:17( [780] >record 'ImmAdapterDirectoryAPI'<>) */::getFsSubnode))
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterSymlinkAPI /*  [905]imm/ImmOrg.hpp:1494:17( [780] >record 'ImmAdapterSymlinkAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1494:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterSymlinkAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterDocumentFragmentAPI /*  [905]imm/ImmOrg.hpp:1495:17( [780] >record 'ImmAdapterDocumentFragmentAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1495:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterDocumentFragmentAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCriticMarkupAPI /*  [905]imm/ImmOrg.hpp:1496:17( [780] >record 'ImmAdapterCriticMarkupAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1496:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterCriticMarkupAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterListItemAPI /*  [905]imm/ImmOrg.hpp:1505:17( [780] >record 'ImmAdapterListItemAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1505:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterListItemAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterDocumentOptionsAPI /*  [905]imm/ImmOrg.hpp:1513:17( [780] >record 'ImmAdapterDocumentOptionsAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1513:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterDocumentOptionsAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterDocumentAPI /*  [905]imm/ImmOrg.hpp:1525:17( [780] >record 'ImmAdapterDocumentAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1525:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterDocumentAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterFileTargetAPI /*  [905]imm/ImmOrg.hpp:1534:17( [780] >record 'ImmAdapterFileTargetAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1534:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterFileTargetAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterTextSeparatorAPI /*  [905]imm/ImmOrg.hpp:1535:17( [780] >record 'ImmAdapterTextSeparatorAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1535:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterTextSeparatorAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdIncludeAPI /*  [905]imm/ImmOrg.hpp:1536:17( [780] >record 'ImmAdapterCmdIncludeAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1536:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterCmdIncludeAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterDocumentGroupAPI /*  [905]imm/ImmOrg.hpp:1537:17( [780] >record 'ImmAdapterDocumentGroupAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1537:17( [780] >record 'ImmAdapterOrgAPI'<>) */>>("ImmAdapterDocumentGroupAPI")
    ;
  emscripten::class_<org::sem::Block /* d_org */, emscripten::base<org::sem::Cmd>>("Block")
    .smart_ptr<org::sem::SemId<org::sem::Block /* d_org */>>("Block")
    ;
  emscripten::class_<org::sem::LineCommand /* d_org */, emscripten::base<org::sem::Cmd>>("LineCommand")
    .smart_ptr<org::sem::SemId<org::sem::LineCommand /* d_org */>>("LineCommand")
    ;
  emscripten::class_<org::sem::CmdCreator /* d_org */, emscripten::base<org::sem::Cmd>>("CmdCreator")
    .smart_ptr<org::sem::SemId<org::sem::CmdCreator /* d_org */>>("CmdCreator")
    .property("text", &org::sem::CmdCreator /* d_org */::text)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdCreator /* d_org */::*)() const>(&org::sem::CmdCreator /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdCreator /* d_org */>>)
    ;
  emscripten::class_<org::sem::CmdAuthor /* d_org */, emscripten::base<org::sem::Cmd>>("CmdAuthor")
    .smart_ptr<org::sem::SemId<org::sem::CmdAuthor /* d_org */>>("CmdAuthor")
    .property("text", &org::sem::CmdAuthor /* d_org */::text)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdAuthor /* d_org */::*)() const>(&org::sem::CmdAuthor /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdAuthor /* d_org */>>)
    ;
  emscripten::class_<org::sem::CmdEmail /* d_org */, emscripten::base<org::sem::Cmd>>("CmdEmail")
    .smart_ptr<org::sem::SemId<org::sem::CmdEmail /* d_org */>>("CmdEmail")
    .property("text", &org::sem::CmdEmail /* d_org */::text)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdEmail /* d_org */::*)() const>(&org::sem::CmdEmail /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdEmail /* d_org */>>)
    ;
  emscripten::class_<org::sem::CmdLanguage /* d_org */, emscripten::base<org::sem::Cmd>>("CmdLanguage")
    .smart_ptr<org::sem::SemId<org::sem::CmdLanguage /* d_org */>>("CmdLanguage")
    .property("text", &org::sem::CmdLanguage /* d_org */::text)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdLanguage /* d_org */::*)() const>(&org::sem::CmdLanguage /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdLanguage /* d_org */>>)
    ;
  emscripten::class_<org::sem::CmdCustomArgs /* d_org */, emscripten::base<org::sem::Cmd>>("CmdCustomArgs")
    .smart_ptr<org::sem::SemId<org::sem::CmdCustomArgs /* d_org */>>("CmdCustomArgs")
    .property("name", &org::sem::CmdCustomArgs /* d_org */::name)
    .property("isAttached", &org::sem::CmdCustomArgs /* d_org */::isAttached)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdCustomArgs /* d_org */::*)() const>(&org::sem::CmdCustomArgs /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdCustomArgs /* d_org */>>)
    ;
  emscripten::class_<org::sem::CmdTblfm /* d_org */, emscripten::base<org::sem::Cmd>>("CmdTblfm")
    .smart_ptr<org::sem::SemId<org::sem::CmdTblfm /* d_org */>>("CmdTblfm")
    .property("expr", &org::sem::CmdTblfm /* d_org */::expr)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdTblfm /* d_org */::*)() const>(&org::sem::CmdTblfm /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdTblfm /* d_org */>>)
    ;
  emscripten::class_<org::sem::Cell /* d_org */, emscripten::base<org::sem::Cmd>>("Cell")
    .smart_ptr<org::sem::SemId<org::sem::Cell /* d_org */>>("Cell")
    .property("isBlock", &org::sem::Cell /* d_org */::isBlock)
    .function("getKind", static_cast<OrgSemKind(org::sem::Cell /* d_org */::*)() const>(&org::sem::Cell /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Cell /* d_org */>>)
    ;
  emscripten::class_<org::sem::Row /* d_org */, emscripten::base<org::sem::Cmd>>("Row")
    .smart_ptr<org::sem::SemId<org::sem::Row /* d_org */>>("Row")
    .property("cells", &org::sem::Row /* d_org */::cells)
    .property("isBlock", &org::sem::Row /* d_org */::isBlock)
    .function("getKind", static_cast<OrgSemKind(org::sem::Row /* d_org */::*)() const>(&org::sem::Row /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Row /* d_org */>>)
    ;
  emscripten::class_<org::imm::ImmBlock /* d_orgimm_write */, emscripten::base<org::imm::ImmCmd /* imm_write */>>("ImmBlock")
    .function("__eq__", static_cast<bool(org::imm::ImmBlock /* d_orgimm_write */::*)(org::imm::ImmBlock const& /* d_orgimm_write */) const>(&org::imm::ImmBlock /* d_orgimm_write */::operator==))
    ;
  emscripten::class_<org::imm::ImmLineCommand /* d_orgimm_write */, emscripten::base<org::imm::ImmCmd /* imm_write */>>("ImmLineCommand")
    .function("__eq__", static_cast<bool(org::imm::ImmLineCommand /* d_orgimm_write */::*)(org::imm::ImmLineCommand const& /* d_orgimm_write */) const>(&org::imm::ImmLineCommand /* d_orgimm_write */::operator==))
    ;
  emscripten::class_<org::imm::ImmCmdCreator /* d_orgimm_write */, emscripten::base<org::imm::ImmCmd /* imm_write */>>("ImmCmdCreator")
    .property("text", &org::imm::ImmCmdCreator /* d_orgimm_write */::text)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCmdCreator /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdCreator /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdCreator /* d_orgimm_write */::*)(org::imm::ImmCmdCreator const& /* d_orgimm_write */) const>(&org::imm::ImmCmdCreator /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdAuthor /* d_orgimm_write */, emscripten::base<org::imm::ImmCmd /* imm_write */>>("ImmCmdAuthor")
    .property("text", &org::imm::ImmCmdAuthor /* d_orgimm_write */::text)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCmdAuthor /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdAuthor /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdAuthor /* d_orgimm_write */::*)(org::imm::ImmCmdAuthor const& /* d_orgimm_write */) const>(&org::imm::ImmCmdAuthor /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdEmail /* d_orgimm_write */, emscripten::base<org::imm::ImmCmd /* imm_write */>>("ImmCmdEmail")
    .property("text", &org::imm::ImmCmdEmail /* d_orgimm_write */::text)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCmdEmail /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdEmail /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdEmail /* d_orgimm_write */::*)(org::imm::ImmCmdEmail const& /* d_orgimm_write */) const>(&org::imm::ImmCmdEmail /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdLanguage /* d_orgimm_write */, emscripten::base<org::imm::ImmCmd /* imm_write */>>("ImmCmdLanguage")
    .property("text", &org::imm::ImmCmdLanguage /* d_orgimm_write */::text)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCmdLanguage /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdLanguage /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdLanguage /* d_orgimm_write */::*)(org::imm::ImmCmdLanguage const& /* d_orgimm_write */) const>(&org::imm::ImmCmdLanguage /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdCustomArgs /* d_orgimm_write */, emscripten::base<org::imm::ImmCmd /* imm_write */>>("ImmCmdCustomArgs")
    .property("name", &org::imm::ImmCmdCustomArgs /* d_orgimm_write */::name)
    .property("isAttached", &org::imm::ImmCmdCustomArgs /* d_orgimm_write */::isAttached)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCmdCustomArgs /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdCustomArgs /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdCustomArgs /* d_orgimm_write */::*)(org::imm::ImmCmdCustomArgs const& /* d_orgimm_write */) const>(&org::imm::ImmCmdCustomArgs /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdTblfm /* d_orgimm_write */, emscripten::base<org::imm::ImmCmd /* imm_write */>>("ImmCmdTblfm")
    .property("expr", &org::imm::ImmCmdTblfm /* d_orgimm_write */::expr)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCmdTblfm /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdTblfm /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdTblfm /* d_orgimm_write */::*)(org::imm::ImmCmdTblfm const& /* d_orgimm_write */) const>(&org::imm::ImmCmdTblfm /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCell /* d_orgimm_write */, emscripten::base<org::imm::ImmCmd /* imm_write */>>("ImmCell")
    .property("isBlock", &org::imm::ImmCell /* d_orgimm_write */::isBlock)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCell /* d_orgimm_write */::*)() const>(&org::imm::ImmCell /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCell /* d_orgimm_write */::*)(org::imm::ImmCell const& /* d_orgimm_write */) const>(&org::imm::ImmCell /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmRow /* d_orgimm_write */, emscripten::base<org::imm::ImmCmd /* imm_write */>>("ImmRow")
    .property("cells", &org::imm::ImmRow /* d_orgimm_write */::cells)
    .property("isBlock", &org::imm::ImmRow /* d_orgimm_write */::isBlock)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmRow /* d_orgimm_write */::*)() const>(&org::imm::ImmRow /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmRow /* d_orgimm_write */::*)(org::imm::ImmRow const& /* d_orgimm_write */) const>(&org::imm::ImmRow /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1357:17( [780] >record 'ImmAdapterCmdAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtAPI /*  [905]imm/ImmOrg.hpp:1357:17( [780] >record 'ImmAdapterStmtAPI'<>) */>>("ImmAdapterCmdAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdCustomRawAPI /*  [905]imm/ImmOrg.hpp:1407:17( [780] >record 'ImmAdapterCmdCustomRawAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtAPI /*  [905]imm/ImmOrg.hpp:1407:17( [780] >record 'ImmAdapterStmtAPI'<>) */>>("ImmAdapterCmdCustomRawAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdCustomTextAPI /*  [905]imm/ImmOrg.hpp:1408:17( [780] >record 'ImmAdapterCmdCustomTextAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtAPI /*  [905]imm/ImmOrg.hpp:1408:17( [780] >record 'ImmAdapterStmtAPI'<>) */>>("ImmAdapterCmdCustomTextAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLinkAPI /*  [905]imm/ImmOrg.hpp:1450:17( [780] >record 'ImmAdapterLinkAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtAPI /*  [905]imm/ImmOrg.hpp:1450:17( [780] >record 'ImmAdapterStmtAPI'<>) */>>("ImmAdapterLinkAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockCommentAPI /*  [905]imm/ImmOrg.hpp:1454:17( [780] >record 'ImmAdapterBlockCommentAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtAPI /*  [905]imm/ImmOrg.hpp:1454:17( [780] >record 'ImmAdapterStmtAPI'<>) */>>("ImmAdapterBlockCommentAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterParagraphAPI /*  [905]imm/ImmOrg.hpp:1471:17( [780] >record 'ImmAdapterParagraphAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtAPI /*  [905]imm/ImmOrg.hpp:1471:17( [780] >record 'ImmAdapterStmtAPI'<>) */>>("ImmAdapterParagraphAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterListAPI /*  [905]imm/ImmOrg.hpp:1498:17( [780] >record 'ImmAdapterListAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtAPI /*  [905]imm/ImmOrg.hpp:1498:17( [780] >record 'ImmAdapterStmtAPI'<>) */>>("ImmAdapterListAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmStmt>, emscripten::base<org::imm::ImmAdapterStmtAPI>>("ImmAdapterT")
    .function("getAttached", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmStmt>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmStmt>::getAttached))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmSubtree>, emscripten::base<org::imm::ImmAdapterSubtreeAPI>>("ImmAdapterT")
    .function("getLevel", static_cast<int /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getLevel))
    .function("getTreeId", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTreeId))
    .function("getTodo", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTodo))
    .function("getCompletion", static_cast<hstd::Opt<org::sem::SubtreeCompletion> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getCompletion))
    .function("getDescription", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getDescription))
    .function("getTags", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTags))
    .function("getTitle", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTitle))
    .function("getLogbook", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getLogbook))
    .function("getProperties", static_cast<hstd::ext::ImmVec<org::sem::NamedProperty> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getProperties))
    .function("getClosed", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getClosed))
    .function("getDeadline", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getDeadline))
    .function("getScheduled", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getScheduled))
    .function("getIsComment", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getIsComment))
    .function("getIsArchived", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getIsArchived))
    .function("getPriority", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getPriority))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmNoNode>, emscripten::base<org::imm::ImmAdapterNoNodeAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmErrorItem>, emscripten::base<org::imm::ImmAdapterErrorItemAPI>>("ImmAdapterT")
    .function("getDiag", static_cast<org::sem::OrgDiagnostics(org::imm::ImmAdapterT<org::imm::ImmErrorItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorItem>::getDiag))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmErrorGroup>, emscripten::base<org::imm::ImmAdapterErrorGroupAPI>>("ImmAdapterT")
    .function("getDiagnostics", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::getDiagnostics))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>, emscripten::base<org::imm::ImmAdapterErrorSkipGroupAPI>>("ImmAdapterT")
    .function("getSkipped", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorSkipToken /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>::getSkipped))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken>, emscripten::base<org::imm::ImmAdapterErrorSkipTokenAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmStmtList>, emscripten::base<org::imm::ImmAdapterStmtListAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmEmpty>, emscripten::base<org::imm::ImmAdapterEmptyAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterHashTagAPI /*  [905]imm/ImmOrg.hpp:1412:17( [780] >record 'ImmAdapterHashTagAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterInlineAPI /*  [905]imm/ImmOrg.hpp:1412:17( [780] >record 'ImmAdapterInlineAPI'<>) */>>("ImmAdapterHashTagAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterInlineFootnoteAPI /*  [905]imm/ImmOrg.hpp:1413:17( [780] >record 'ImmAdapterInlineFootnoteAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterInlineAPI /*  [905]imm/ImmOrg.hpp:1413:17( [780] >record 'ImmAdapterInlineAPI'<>) */>>("ImmAdapterInlineFootnoteAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterSubtreeCompletionAPI /*  [905]imm/ImmOrg.hpp:1467:17( [780] >record 'ImmAdapterSubtreeCompletionAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterInlineAPI /*  [905]imm/ImmOrg.hpp:1467:17( [780] >record 'ImmAdapterInlineAPI'<>) */>>("ImmAdapterSubtreeCompletionAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmInline>, emscripten::base<org::imm::ImmAdapterInlineAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmTime>, emscripten::base<org::imm::ImmAdapterTimeAPI>>("ImmAdapterT")
    .function("getIsActive", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmTime>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTime>::getIsActive))
    .function("getTime", static_cast<org::imm::ImmTime::TimeVariant /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmTime>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTime>::getTime))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmTimeRange>, emscripten::base<org::imm::ImmAdapterTimeRangeAPI>>("ImmAdapterT")
    .function("getFrom", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmTimeRange>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTimeRange>::getFrom))
    .function("getTo", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmTimeRange>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTimeRange>::getTo))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmMacro>, emscripten::base<org::imm::ImmAdapterMacroAPI>>("ImmAdapterT")
    .function("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmMacro>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMacro>::getName))
    .function("getAttrs", static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmMacro>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMacro>::getAttrs))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmSymbol>, emscripten::base<org::imm::ImmAdapterSymbolAPI>>("ImmAdapterT")
    .function("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getName))
    .function("getParameters", static_cast<hstd::ext::ImmVec<org::imm::ImmSymbol::Param /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getParameters))
    .function("getPositional", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getPositional))
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterEscapedAPI /*  [905]imm/ImmOrg.hpp:1429:17( [780] >record 'ImmAdapterEscapedAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1429:17( [780] >record 'ImmAdapterLeafAPI'<>) */>>("ImmAdapterEscapedAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterNewlineAPI /*  [905]imm/ImmOrg.hpp:1430:17( [780] >record 'ImmAdapterNewlineAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1430:17( [780] >record 'ImmAdapterLeafAPI'<>) */>>("ImmAdapterNewlineAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterSpaceAPI /*  [905]imm/ImmOrg.hpp:1431:17( [780] >record 'ImmAdapterSpaceAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1431:17( [780] >record 'ImmAdapterLeafAPI'<>) */>>("ImmAdapterSpaceAPI")
    ;
}

void subdivide_7(org::bind::js::type_registration_guard& g) {
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterWordAPI /*  [905]imm/ImmOrg.hpp:1432:17( [780] >record 'ImmAdapterWordAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1432:17( [780] >record 'ImmAdapterLeafAPI'<>) */>>("ImmAdapterWordAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAtMentionAPI /*  [905]imm/ImmOrg.hpp:1433:17( [780] >record 'ImmAdapterAtMentionAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1433:17( [780] >record 'ImmAdapterLeafAPI'<>) */>>("ImmAdapterAtMentionAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterRawTextAPI /*  [905]imm/ImmOrg.hpp:1434:17( [780] >record 'ImmAdapterRawTextAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1434:17( [780] >record 'ImmAdapterLeafAPI'<>) */>>("ImmAdapterRawTextAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterPunctuationAPI /*  [905]imm/ImmOrg.hpp:1435:17( [780] >record 'ImmAdapterPunctuationAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1435:17( [780] >record 'ImmAdapterLeafAPI'<>) */>>("ImmAdapterPunctuationAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterPlaceholderAPI /*  [905]imm/ImmOrg.hpp:1436:17( [780] >record 'ImmAdapterPlaceholderAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1436:17( [780] >record 'ImmAdapterLeafAPI'<>) */>>("ImmAdapterPlaceholderAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBigIdentAPI /*  [905]imm/ImmOrg.hpp:1437:17( [780] >record 'ImmAdapterBigIdentAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1437:17( [780] >record 'ImmAdapterLeafAPI'<>) */>>("ImmAdapterBigIdentAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterTextTargetAPI /*  [905]imm/ImmOrg.hpp:1438:17( [780] >record 'ImmAdapterTextTargetAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1438:17( [780] >record 'ImmAdapterLeafAPI'<>) */>>("ImmAdapterTextTargetAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmLeaf>, emscripten::base<org::imm::ImmAdapterLeafAPI>>("ImmAdapterT")
    .function("getText", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmLeaf>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLeaf>::getText))
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBoldAPI /*  [905]imm/ImmOrg.hpp:1440:17( [780] >record 'ImmAdapterBoldAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1440:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>>("ImmAdapterBoldAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterUnderlineAPI /*  [905]imm/ImmOrg.hpp:1441:17( [780] >record 'ImmAdapterUnderlineAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1441:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>>("ImmAdapterUnderlineAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMonospaceAPI /*  [905]imm/ImmOrg.hpp:1442:17( [780] >record 'ImmAdapterMonospaceAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1442:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>>("ImmAdapterMonospaceAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkQuoteAPI /*  [905]imm/ImmOrg.hpp:1443:17( [780] >record 'ImmAdapterMarkQuoteAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1443:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>>("ImmAdapterMarkQuoteAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterRadioTargetAPI /*  [905]imm/ImmOrg.hpp:1444:17( [780] >record 'ImmAdapterRadioTargetAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1444:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>>("ImmAdapterRadioTargetAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterVerbatimAPI /*  [905]imm/ImmOrg.hpp:1445:17( [780] >record 'ImmAdapterVerbatimAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1445:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>>("ImmAdapterVerbatimAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterItalicAPI /*  [905]imm/ImmOrg.hpp:1446:17( [780] >record 'ImmAdapterItalicAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1446:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>>("ImmAdapterItalicAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStrikeAPI /*  [905]imm/ImmOrg.hpp:1447:17( [780] >record 'ImmAdapterStrikeAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1447:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>>("ImmAdapterStrikeAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterParAPI /*  [905]imm/ImmOrg.hpp:1448:17( [780] >record 'ImmAdapterParAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1448:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>>("ImmAdapterParAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmMarkup>, emscripten::base<org::imm::ImmAdapterMarkupAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmLatex>, emscripten::base<org::imm::ImmAdapterLatexAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>, emscripten::base<org::imm::ImmAdapterSubtreeLogAPI>>("ImmAdapterT")
    .function("getHead", static_cast<org::sem::SubtreeLogHead(org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::getHead))
    .function("getDesc", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmStmtList /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::getDesc))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmColonExample>, emscripten::base<org::imm::ImmAdapterColonExampleAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCall>, emscripten::base<org::imm::ImmAdapterCallAPI>>("ImmAdapterT")
    .function("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getName))
    .function("getAttrs", static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getAttrs))
    .function("getIsCommand", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getIsCommand))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmFile>, emscripten::base<org::imm::ImmAdapterFileAPI>>("ImmAdapterT")
    .function("getRelPath", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmFile>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFile>::getRelPath))
    .function("getAbsPath", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmFile>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFile>::getAbsPath))
    .function("getData", static_cast<org::imm::ImmFile::Data /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmFile>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFile>::getData))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmDirectory>, emscripten::base<org::imm::ImmAdapterDirectoryAPI>>("ImmAdapterT")
    .function("getRelPath", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmDirectory>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDirectory>::getRelPath))
    .function("getAbsPath", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmDirectory>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDirectory>::getAbsPath))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmSymlink>, emscripten::base<org::imm::ImmAdapterSymlinkAPI>>("ImmAdapterT")
    .function("getIsDirectory", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSymlink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymlink>::getIsDirectory))
    .function("getAbsPath", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmSymlink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymlink>::getAbsPath))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>, emscripten::base<org::imm::ImmAdapterDocumentFragmentAPI>>("ImmAdapterT")
    .function("getBaseLine", static_cast<int /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::getBaseLine))
    .function("getBaseCol", static_cast<int /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::getBaseCol))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>, emscripten::base<org::imm::ImmAdapterCriticMarkupAPI>>("ImmAdapterT")
    .function("getKind", static_cast<org::imm::ImmCriticMarkup::Kind /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::getKind))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmListItem>, emscripten::base<org::imm::ImmAdapterListItemAPI>>("ImmAdapterT")
    .function("getCheckbox", static_cast<CheckboxState /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getCheckbox))
    .function("getHeader", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getHeader))
    .function("getBullet", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getBullet))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>, emscripten::base<org::imm::ImmAdapterDocumentOptionsAPI>>("ImmAdapterT")
    .function("getInitialVisibility", static_cast<InitialSubtreeVisibility /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getInitialVisibility))
    .function("getProperties", static_cast<hstd::ext::ImmVec<org::sem::NamedProperty> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getProperties))
    .function("getExportConfig", static_cast<org::sem::DocumentExportConfig(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getExportConfig))
    .function("getFixedWidthSections", static_cast<hstd::Opt<bool /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getFixedWidthSections))
    .function("getStartupIndented", static_cast<hstd::Opt<bool /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getStartupIndented))
    .function("getCategory", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getCategory))
    .function("getSetupfile", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getSetupfile))
    .function("getMaxSubtreeLevelExport", static_cast<hstd::Opt<int /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getMaxSubtreeLevelExport))
    .function("getColumns", static_cast<hstd::Opt<org::sem::ColumnView> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getColumns))
    .function("getTodoKeywords", static_cast<hstd::ext::ImmVec<org::sem::TodoKeyword> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getTodoKeywords))
    .function("getDoneKeywords", static_cast<hstd::ext::ImmVec<org::sem::TodoKeyword> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getDoneKeywords))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmDocument>, emscripten::base<org::imm::ImmAdapterDocumentAPI>>("ImmAdapterT")
    .function("getTitle", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getTitle))
    .function("getAuthor", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getAuthor))
    .function("getCreator", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getCreator))
    .function("getFiletags", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getFiletags))
    .function("getEmail", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmRawText /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getEmail))
    .function("getLanguage", static_cast<hstd::ext::ImmVec<hstd /* imm_write */::Str /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getLanguage))
    .function("getOptions", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getOptions))
    .function("getExportFileName", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getExportFileName))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmFileTarget>, emscripten::base<org::imm::ImmAdapterFileTargetAPI>>("ImmAdapterT")
    .function("getPath", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getPath))
    .function("getLine", static_cast<hstd::Opt<int /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getLine))
    .function("getSearchTarget", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getSearchTarget))
    .function("getRestrictToHeadlines", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getRestrictToHeadlines))
    .function("getTargetId", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getTargetId))
    .function("getRegexp", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getRegexp))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmTextSeparator>, emscripten::base<org::imm::ImmAdapterTextSeparatorAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdInclude>, emscripten::base<org::imm::ImmAdapterCmdIncludeAPI>>("ImmAdapterT")
    .function("getPath", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getPath))
    .function("getFirstLine", static_cast<hstd::Opt<int /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getFirstLine))
    .function("getLastLine", static_cast<hstd::Opt<int /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getLastLine))
    .function("getData", static_cast<org::imm::ImmCmdInclude::Data /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getData))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>, emscripten::base<org::imm::ImmAdapterDocumentGroupAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::sem::BlockCenter /* d_org */, emscripten::base<org::sem::Block>>("BlockCenter")
    .smart_ptr<org::sem::SemId<org::sem::BlockCenter /* d_org */>>("BlockCenter")
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockCenter /* d_org */::*)() const>(&org::sem::BlockCenter /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockCenter /* d_org */>>)
    ;
  emscripten::class_<org::sem::BlockQuote /* d_org */, emscripten::base<org::sem::Block>>("BlockQuote")
    .smart_ptr<org::sem::SemId<org::sem::BlockQuote /* d_org */>>("BlockQuote")
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockQuote /* d_org */::*)() const>(&org::sem::BlockQuote /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockQuote /* d_org */>>)
    ;
  emscripten::class_<org::sem::BlockVerse /* d_org */, emscripten::base<org::sem::Block>>("BlockVerse")
    .smart_ptr<org::sem::SemId<org::sem::BlockVerse /* d_org */>>("BlockVerse")
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockVerse /* d_org */::*)() const>(&org::sem::BlockVerse /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockVerse /* d_org */>>)
    ;
  emscripten::class_<org::sem::BlockDynamicFallback /* d_org */, emscripten::base<org::sem::Block>>("BlockDynamicFallback")
    .smart_ptr<org::sem::SemId<org::sem::BlockDynamicFallback /* d_org */>>("BlockDynamicFallback")
    .property("name", &org::sem::BlockDynamicFallback /* d_org */::name)
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockDynamicFallback /* d_org */::*)() const>(&org::sem::BlockDynamicFallback /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockDynamicFallback /* d_org */>>)
    ;
  emscripten::class_<org::sem::BlockExample /* d_org */, emscripten::base<org::sem::Block>>("BlockExample")
    .smart_ptr<org::sem::SemId<org::sem::BlockExample /* d_org */>>("BlockExample")
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockExample /* d_org */::*)() const>(&org::sem::BlockExample /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockExample /* d_org */>>)
    ;
  emscripten::class_<org::sem::BlockExport /* d_org */, emscripten::base<org::sem::Block>>("BlockExport")
    .smart_ptr<org::sem::SemId<org::sem::BlockExport /* d_org */>>("BlockExport")
    .property("exporter", &org::sem::BlockExport /* d_org */::exporter)
    .property("content", &org::sem::BlockExport /* d_org */::content)
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockExport /* d_org */::*)() const>(&org::sem::BlockExport /* d_org */::getKind))
    .function("getPlacement", static_cast<hstd::Opt<hstd::Str>(org::sem::BlockExport /* d_org */::*)() const>(&org::sem::BlockExport /* d_org */::getPlacement))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockExport /* d_org */>>)
    ;
  emscripten::class_<org::sem::BlockAdmonition /* d_org */, emscripten::base<org::sem::Block>>("BlockAdmonition")
    .smart_ptr<org::sem::SemId<org::sem::BlockAdmonition /* d_org */>>("BlockAdmonition")
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockAdmonition /* d_org */::*)() const>(&org::sem::BlockAdmonition /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockAdmonition /* d_org */>>)
    ;
  emscripten::class_<org::sem::BlockCodeEvalResult /* d_org */, emscripten::base<org::sem::Block>>("BlockCodeEvalResult")
    .smart_ptr<org::sem::SemId<org::sem::BlockCodeEvalResult /* d_org */>>("BlockCodeEvalResult")
    .property("raw", &org::sem::BlockCodeEvalResult /* d_org */::raw)
    .property("node", &org::sem::BlockCodeEvalResult /* d_org */::node)
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockCodeEvalResult /* d_org */::*)() const>(&org::sem::BlockCodeEvalResult /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockCodeEvalResult /* d_org */>>)
    ;
  emscripten::class_<org::sem::BlockCode /* d_org */, emscripten::base<org::sem::Block>>("BlockCode")
    .smart_ptr<org::sem::SemId<org::sem::BlockCode /* d_org */>>("BlockCode")
    .property("lang", &org::sem::BlockCode /* d_org */::lang)
    .property("result", &org::sem::BlockCode /* d_org */::result)
    .property("lines", &org::sem::BlockCode /* d_org */::lines)
    .property("switches", &org::sem::BlockCode /* d_org */::switches)
    .function("getKind", static_cast<OrgSemKind(org::sem::BlockCode /* d_org */::*)() const>(&org::sem::BlockCode /* d_org */::getKind))
    .function("getVariable", static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockCode /* d_org */::*)(hstd::Str const&) const>(&org::sem::BlockCode /* d_org */::getVariable))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::BlockCode /* d_org */>>)
    ;
  emscripten::class_<org::sem::Table /* d_org */, emscripten::base<org::sem::Block>>("Table")
    .smart_ptr<org::sem::SemId<org::sem::Table /* d_org */>>("Table")
    .property("rows", &org::sem::Table /* d_org */::rows)
    .property("isBlock", &org::sem::Table /* d_org */::isBlock)
    .function("getKind", static_cast<OrgSemKind(org::sem::Table /* d_org */::*)() const>(&org::sem::Table /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::Table /* d_org */>>)
    ;
  emscripten::class_<org::sem::Attached /* d_org */, emscripten::base<org::sem::LineCommand>>("Attached")
    .smart_ptr<org::sem::SemId<org::sem::Attached /* d_org */>>("Attached")
    ;
  emscripten::class_<org::imm::ImmBlockCenter /* d_orgimm_write */, emscripten::base<org::imm::ImmBlock /* imm_write */>>("ImmBlockCenter")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmBlockCenter /* d_orgimm_write */::*)() const>(&org::imm::ImmBlockCenter /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockCenter /* d_orgimm_write */::*)(org::imm::ImmBlockCenter const& /* d_orgimm_write */) const>(&org::imm::ImmBlockCenter /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockQuote /* d_orgimm_write */, emscripten::base<org::imm::ImmBlock /* imm_write */>>("ImmBlockQuote")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmBlockQuote /* d_orgimm_write */::*)() const>(&org::imm::ImmBlockQuote /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockQuote /* d_orgimm_write */::*)(org::imm::ImmBlockQuote const& /* d_orgimm_write */) const>(&org::imm::ImmBlockQuote /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockVerse /* d_orgimm_write */, emscripten::base<org::imm::ImmBlock /* imm_write */>>("ImmBlockVerse")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmBlockVerse /* d_orgimm_write */::*)() const>(&org::imm::ImmBlockVerse /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockVerse /* d_orgimm_write */::*)(org::imm::ImmBlockVerse const& /* d_orgimm_write */) const>(&org::imm::ImmBlockVerse /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockDynamicFallback /* d_orgimm_write */, emscripten::base<org::imm::ImmBlock /* imm_write */>>("ImmBlockDynamicFallback")
    .property("name", &org::imm::ImmBlockDynamicFallback /* d_orgimm_write */::name)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmBlockDynamicFallback /* d_orgimm_write */::*)() const>(&org::imm::ImmBlockDynamicFallback /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockDynamicFallback /* d_orgimm_write */::*)(org::imm::ImmBlockDynamicFallback const& /* d_orgimm_write */) const>(&org::imm::ImmBlockDynamicFallback /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockExample /* d_orgimm_write */, emscripten::base<org::imm::ImmBlock /* imm_write */>>("ImmBlockExample")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmBlockExample /* d_orgimm_write */::*)() const>(&org::imm::ImmBlockExample /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockExample /* d_orgimm_write */::*)(org::imm::ImmBlockExample const& /* d_orgimm_write */) const>(&org::imm::ImmBlockExample /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockExport /* d_orgimm_write */, emscripten::base<org::imm::ImmBlock /* imm_write */>>("ImmBlockExport")
    .property("exporter", &org::imm::ImmBlockExport /* d_orgimm_write */::exporter)
    .property("content", &org::imm::ImmBlockExport /* d_orgimm_write */::content)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmBlockExport /* d_orgimm_write */::*)() const>(&org::imm::ImmBlockExport /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockExport /* d_orgimm_write */::*)(org::imm::ImmBlockExport const& /* d_orgimm_write */) const>(&org::imm::ImmBlockExport /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockAdmonition /* d_orgimm_write */, emscripten::base<org::imm::ImmBlock /* imm_write */>>("ImmBlockAdmonition")
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmBlockAdmonition /* d_orgimm_write */::*)() const>(&org::imm::ImmBlockAdmonition /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockAdmonition /* d_orgimm_write */::*)(org::imm::ImmBlockAdmonition const& /* d_orgimm_write */) const>(&org::imm::ImmBlockAdmonition /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockCodeEvalResult /* d_orgimm_write */, emscripten::base<org::imm::ImmBlock /* imm_write */>>("ImmBlockCodeEvalResult")
    .property("raw", &org::imm::ImmBlockCodeEvalResult /* d_orgimm_write */::raw)
    .property("node", &org::imm::ImmBlockCodeEvalResult /* d_orgimm_write */::node)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmBlockCodeEvalResult /* d_orgimm_write */::*)() const>(&org::imm::ImmBlockCodeEvalResult /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockCodeEvalResult /* d_orgimm_write */::*)(org::imm::ImmBlockCodeEvalResult const& /* d_orgimm_write */) const>(&org::imm::ImmBlockCodeEvalResult /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmBlockCode /* d_orgimm_write */, emscripten::base<org::imm::ImmBlock /* imm_write */>>("ImmBlockCode")
    .property("lang", &org::imm::ImmBlockCode /* d_orgimm_write */::lang)
    .property("result", &org::imm::ImmBlockCode /* d_orgimm_write */::result)
    .property("lines", &org::imm::ImmBlockCode /* d_orgimm_write */::lines)
    .property("switches", &org::imm::ImmBlockCode /* d_orgimm_write */::switches)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmBlockCode /* d_orgimm_write */::*)() const>(&org::imm::ImmBlockCode /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmBlockCode /* d_orgimm_write */::*)(org::imm::ImmBlockCode const& /* d_orgimm_write */) const>(&org::imm::ImmBlockCode /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmTable /* d_orgimm_write */, emscripten::base<org::imm::ImmBlock /* imm_write */>>("ImmTable")
    .property("rows", &org::imm::ImmTable /* d_orgimm_write */::rows)
    .property("isBlock", &org::imm::ImmTable /* d_orgimm_write */::isBlock)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmTable /* d_orgimm_write */::*)() const>(&org::imm::ImmTable /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmTable /* d_orgimm_write */::*)(org::imm::ImmTable const& /* d_orgimm_write */) const>(&org::imm::ImmTable /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmAttached /* d_orgimm_write */, emscripten::base<org::imm::ImmLineCommand /* imm_write */>>("ImmAttached")
    .function("__eq__", static_cast<bool(org::imm::ImmAttached /* d_orgimm_write */::*)(org::imm::ImmAttached const& /* d_orgimm_write */) const>(&org::imm::ImmAttached /* d_orgimm_write */::operator==))
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLineCommandAPI /*  [905]imm/ImmOrg.hpp:1394:17( [780] >record 'ImmAdapterLineCommandAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1394:17( [780] >record 'ImmAdapterCmdAPI'<>) */>>("ImmAdapterLineCommandAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdCustomArgsAPI /*  [905]imm/ImmOrg.hpp:1402:17( [780] >record 'ImmAdapterCmdCustomArgsAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1402:17( [780] >record 'ImmAdapterCmdAPI'<>) */>>("ImmAdapterCmdCustomArgsAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdCreatorAPI /*  [905]imm/ImmOrg.hpp:1403:17( [780] >record 'ImmAdapterCmdCreatorAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1403:17( [780] >record 'ImmAdapterCmdAPI'<>) */>>("ImmAdapterCmdCreatorAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAuthorAPI /*  [905]imm/ImmOrg.hpp:1404:17( [780] >record 'ImmAdapterCmdAuthorAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1404:17( [780] >record 'ImmAdapterCmdAPI'<>) */>>("ImmAdapterCmdAuthorAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdEmailAPI /*  [905]imm/ImmOrg.hpp:1405:17( [780] >record 'ImmAdapterCmdEmailAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1405:17( [780] >record 'ImmAdapterCmdAPI'<>) */>>("ImmAdapterCmdEmailAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdLanguageAPI /*  [905]imm/ImmOrg.hpp:1406:17( [780] >record 'ImmAdapterCmdLanguageAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1406:17( [780] >record 'ImmAdapterCmdAPI'<>) */>>("ImmAdapterCmdLanguageAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdTblfmAPI /*  [905]imm/ImmOrg.hpp:1410:17( [780] >record 'ImmAdapterCmdTblfmAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1410:17( [780] >record 'ImmAdapterCmdAPI'<>) */>>("ImmAdapterCmdTblfmAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1451:17( [780] >record 'ImmAdapterBlockAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1451:17( [780] >record 'ImmAdapterCmdAPI'<>) */>>("ImmAdapterBlockAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCellAPI /*  [905]imm/ImmOrg.hpp:1468:17( [780] >record 'ImmAdapterCellAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1468:17( [780] >record 'ImmAdapterCmdAPI'<>) */>>("ImmAdapterCellAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterRowAPI /*  [905]imm/ImmOrg.hpp:1469:17( [780] >record 'ImmAdapterRowAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1469:17( [780] >record 'ImmAdapterCmdAPI'<>) */>>("ImmAdapterRowAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmd>, emscripten::base<org::imm::ImmAdapterCmdAPI>>("ImmAdapterT")
    .function("getAttrs", static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmd>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmd>::getAttrs))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>, emscripten::base<org::imm::ImmAdapterCmdCustomRawAPI>>("ImmAdapterT")
    .function("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getName))
    .function("getIsAttached", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getIsAttached))
    .function("getText", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getText))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>, emscripten::base<org::imm::ImmAdapterCmdCustomTextAPI>>("ImmAdapterT")
    .function("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getName))
    .function("getIsAttached", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getIsAttached))
    .function("getText", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getText))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmLink>, emscripten::base<org::imm::ImmAdapterLinkAPI>>("ImmAdapterT")
    .function("getDescription", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmLink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLink>::getDescription))
    .function("getTarget", static_cast<org::sem::LinkTarget(org::imm::ImmAdapterT<org::imm::ImmLink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLink>::getTarget))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockComment>, emscripten::base<org::imm::ImmAdapterBlockCommentAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmParagraph>, emscripten::base<org::imm::ImmAdapterParagraphAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmList>, emscripten::base<org::imm::ImmAdapterListAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmHashTag>, emscripten::base<org::imm::ImmAdapterHashTagAPI>>("ImmAdapterT")
    .function("getText", static_cast<org::sem::HashTagText(org::imm::ImmAdapterT<org::imm::ImmHashTag>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmHashTag>::getText))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>, emscripten::base<org::imm::ImmAdapterInlineFootnoteAPI>>("ImmAdapterT")
    .function("getTag", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::getTag))
    .function("getDefinition", static_cast<hstd::Opt<org::imm::ImmAdapter>(org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::getDefinition))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmEscaped>, emscripten::base<org::imm::ImmAdapterEscapedAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmNewline>, emscripten::base<org::imm::ImmAdapterNewlineAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmSpace>, emscripten::base<org::imm::ImmAdapterSpaceAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmWord>, emscripten::base<org::imm::ImmAdapterWordAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmAtMention>, emscripten::base<org::imm::ImmAdapterAtMentionAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmRawText>, emscripten::base<org::imm::ImmAdapterRawTextAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmPunctuation>, emscripten::base<org::imm::ImmAdapterPunctuationAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmPlaceholder>, emscripten::base<org::imm::ImmAdapterPlaceholderAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBigIdent>, emscripten::base<org::imm::ImmAdapterBigIdentAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmTextTarget>, emscripten::base<org::imm::ImmAdapterTextTargetAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBold>, emscripten::base<org::imm::ImmAdapterBoldAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmUnderline>, emscripten::base<org::imm::ImmAdapterUnderlineAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmMonospace>, emscripten::base<org::imm::ImmAdapterMonospaceAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmMarkQuote>, emscripten::base<org::imm::ImmAdapterMarkQuoteAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmRadioTarget>, emscripten::base<org::imm::ImmAdapterRadioTargetAPI>>("ImmAdapterT")
    .function("getWords", static_cast<hstd::ext::ImmVec<hstd /* imm_write */::Str /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::getWords))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmVerbatim>, emscripten::base<org::imm::ImmAdapterVerbatimAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmItalic>, emscripten::base<org::imm::ImmAdapterItalicAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmStrike>, emscripten::base<org::imm::ImmAdapterStrikeAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmPar>, emscripten::base<org::imm::ImmAdapterParAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::sem::CmdCaption /* d_org */, emscripten::base<org::sem::Attached>>("CmdCaption")
    .smart_ptr<org::sem::SemId<org::sem::CmdCaption /* d_org */>>("CmdCaption")
    .property("text", &org::sem::CmdCaption /* d_org */::text)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdCaption /* d_org */::*)() const>(&org::sem::CmdCaption /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdCaption /* d_org */>>)
    ;
  emscripten::class_<org::sem::CmdColumns /* d_org */, emscripten::base<org::sem::Attached>>("CmdColumns")
    .smart_ptr<org::sem::SemId<org::sem::CmdColumns /* d_org */>>("CmdColumns")
    .property("view", &org::sem::CmdColumns /* d_org */::view)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdColumns /* d_org */::*)() const>(&org::sem::CmdColumns /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdColumns /* d_org */>>)
    ;
  emscripten::class_<org::sem::CmdName /* d_org */, emscripten::base<org::sem::Attached>>("CmdName")
    .smart_ptr<org::sem::SemId<org::sem::CmdName /* d_org */>>("CmdName")
    .property("name", &org::sem::CmdName /* d_org */::name)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdName /* d_org */::*)() const>(&org::sem::CmdName /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdName /* d_org */>>)
    ;
  emscripten::class_<org::sem::CmdCall /* d_org */, emscripten::base<org::sem::Attached>>("CmdCall")
    .smart_ptr<org::sem::SemId<org::sem::CmdCall /* d_org */>>("CmdCall")
    .property("name", &org::sem::CmdCall /* d_org */::name)
    .property("fileName", &org::sem::CmdCall /* d_org */::fileName)
    .property("insideHeaderAttrs", &org::sem::CmdCall /* d_org */::insideHeaderAttrs)
    .property("callAttrs", &org::sem::CmdCall /* d_org */::callAttrs)
    .property("endHeaderAttrs", &org::sem::CmdCall /* d_org */::endHeaderAttrs)
    .property("result", &org::sem::CmdCall /* d_org */::result)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdCall /* d_org */::*)() const>(&org::sem::CmdCall /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdCall /* d_org */>>)
    ;
  emscripten::class_<org::sem::CmdAttr /* d_org */, emscripten::base<org::sem::Attached>>("CmdAttr")
    .smart_ptr<org::sem::SemId<org::sem::CmdAttr /* d_org */>>("CmdAttr")
    .property("target", &org::sem::CmdAttr /* d_org */::target)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdAttr /* d_org */::*)() const>(&org::sem::CmdAttr /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdAttr /* d_org */>>)
    ;
  emscripten::class_<org::sem::CmdExport /* d_org */, emscripten::base<org::sem::Attached>>("CmdExport")
    .smart_ptr<org::sem::SemId<org::sem::CmdExport /* d_org */>>("CmdExport")
    .property("exporter", &org::sem::CmdExport /* d_org */::exporter)
    .property("content", &org::sem::CmdExport /* d_org */::content)
    .function("getKind", static_cast<OrgSemKind(org::sem::CmdExport /* d_org */::*)() const>(&org::sem::CmdExport /* d_org */::getKind))
    .constructor(&org::bind::js::holder_type_constructor<org::sem::SemId<org::sem::CmdExport /* d_org */>>)
    ;
  emscripten::class_<org::imm::ImmCmdCaption /* d_orgimm_write */, emscripten::base<org::imm::ImmAttached /* imm_write */>>("ImmCmdCaption")
    .property("text", &org::imm::ImmCmdCaption /* d_orgimm_write */::text)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCmdCaption /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdCaption /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdCaption /* d_orgimm_write */::*)(org::imm::ImmCmdCaption const& /* d_orgimm_write */) const>(&org::imm::ImmCmdCaption /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
}

void subdivide_8(org::bind::js::type_registration_guard& g) {
  emscripten::class_<org::imm::ImmCmdColumns /* d_orgimm_write */, emscripten::base<org::imm::ImmAttached /* imm_write */>>("ImmCmdColumns")
    .property("view", &org::imm::ImmCmdColumns /* d_orgimm_write */::view)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCmdColumns /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdColumns /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdColumns /* d_orgimm_write */::*)(org::imm::ImmCmdColumns const& /* d_orgimm_write */) const>(&org::imm::ImmCmdColumns /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdName /* d_orgimm_write */, emscripten::base<org::imm::ImmAttached /* imm_write */>>("ImmCmdName")
    .property("name", &org::imm::ImmCmdName /* d_orgimm_write */::name)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCmdName /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdName /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdName /* d_orgimm_write */::*)(org::imm::ImmCmdName const& /* d_orgimm_write */) const>(&org::imm::ImmCmdName /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdCall /* d_orgimm_write */, emscripten::base<org::imm::ImmAttached /* imm_write */>>("ImmCmdCall")
    .property("name", &org::imm::ImmCmdCall /* d_orgimm_write */::name)
    .property("fileName", &org::imm::ImmCmdCall /* d_orgimm_write */::fileName)
    .property("insideHeaderAttrs", &org::imm::ImmCmdCall /* d_orgimm_write */::insideHeaderAttrs)
    .property("callAttrs", &org::imm::ImmCmdCall /* d_orgimm_write */::callAttrs)
    .property("endHeaderAttrs", &org::imm::ImmCmdCall /* d_orgimm_write */::endHeaderAttrs)
    .property("result", &org::imm::ImmCmdCall /* d_orgimm_write */::result)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCmdCall /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdCall /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdCall /* d_orgimm_write */::*)(org::imm::ImmCmdCall const& /* d_orgimm_write */) const>(&org::imm::ImmCmdCall /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdAttr /* d_orgimm_write */, emscripten::base<org::imm::ImmAttached /* imm_write */>>("ImmCmdAttr")
    .property("target", &org::imm::ImmCmdAttr /* d_orgimm_write */::target)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCmdAttr /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdAttr /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdAttr /* d_orgimm_write */::*)(org::imm::ImmCmdAttr const& /* d_orgimm_write */) const>(&org::imm::ImmCmdAttr /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org::imm::ImmCmdExport /* d_orgimm_write */, emscripten::base<org::imm::ImmAttached /* imm_write */>>("ImmCmdExport")
    .property("exporter", &org::imm::ImmCmdExport /* d_orgimm_write */::exporter)
    .property("content", &org::imm::ImmCmdExport /* d_orgimm_write */::content)
    .function("getKind", static_cast<OrgSemKind /* imm_write */(org::imm::ImmCmdExport /* d_orgimm_write */::*)() const>(&org::imm::ImmCmdExport /* d_orgimm_write */::getKind))
    .function("__eq__", static_cast<bool(org::imm::ImmCmdExport /* d_orgimm_write */::*)(org::imm::ImmCmdExport const& /* d_orgimm_write */) const>(&org::imm::ImmCmdExport /* d_orgimm_write */::operator==))
    .constructor<>()
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttachedAPI /*  [905]imm/ImmOrg.hpp:1395:17( [780] >record 'ImmAdapterAttachedAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLineCommandAPI /*  [905]imm/ImmOrg.hpp:1395:17( [780] >record 'ImmAdapterLineCommandAPI'<>) */>>("ImmAdapterAttachedAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmLineCommand>, emscripten::base<org::imm::ImmAdapterLineCommandAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>, emscripten::base<org::imm::ImmAdapterCmdCustomArgsAPI>>("ImmAdapterT")
    .function("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::getName))
    .function("getIsAttached", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::getIsAttached))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCreator>, emscripten::base<org::imm::ImmAdapterCmdCreatorAPI>>("ImmAdapterT")
    .function("getText", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdCreator>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCreator>::getText))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>, emscripten::base<org::imm::ImmAdapterCmdAuthorAPI>>("ImmAdapterT")
    .function("getText", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>::getText))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdEmail>, emscripten::base<org::imm::ImmAdapterCmdEmailAPI>>("ImmAdapterT")
    .function("getText", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdEmail>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdEmail>::getText))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>, emscripten::base<org::imm::ImmAdapterCmdLanguageAPI>>("ImmAdapterT")
    .function("getText", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>::getText))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>, emscripten::base<org::imm::ImmAdapterCmdTblfmAPI>>("ImmAdapterT")
    .function("getExpr", static_cast<org::sem::Tblfm(org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::getExpr))
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockCenterAPI /*  [905]imm/ImmOrg.hpp:1452:17( [780] >record 'ImmAdapterBlockCenterAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1452:17( [780] >record 'ImmAdapterBlockAPI'<>) */>>("ImmAdapterBlockCenterAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockQuoteAPI /*  [905]imm/ImmOrg.hpp:1453:17( [780] >record 'ImmAdapterBlockQuoteAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1453:17( [780] >record 'ImmAdapterBlockAPI'<>) */>>("ImmAdapterBlockQuoteAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockVerseAPI /*  [905]imm/ImmOrg.hpp:1455:17( [780] >record 'ImmAdapterBlockVerseAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1455:17( [780] >record 'ImmAdapterBlockAPI'<>) */>>("ImmAdapterBlockVerseAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockExampleAPI /*  [905]imm/ImmOrg.hpp:1456:17( [780] >record 'ImmAdapterBlockExampleAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1456:17( [780] >record 'ImmAdapterBlockAPI'<>) */>>("ImmAdapterBlockExampleAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterInlineExportAPI /*  [905]imm/ImmOrg.hpp:1457:17( [780] >record 'ImmAdapterInlineExportAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1457:17( [780] >record 'ImmAdapterBlockAPI'<>) */>>("ImmAdapterInlineExportAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdExportAPI /*  [905]imm/ImmOrg.hpp:1458:17( [780] >record 'ImmAdapterCmdExportAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1458:17( [780] >record 'ImmAdapterBlockAPI'<>) */>>("ImmAdapterCmdExportAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockExportAPI /*  [905]imm/ImmOrg.hpp:1459:17( [780] >record 'ImmAdapterBlockExportAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1459:17( [780] >record 'ImmAdapterBlockAPI'<>) */>>("ImmAdapterBlockExportAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockDynamicFallbackAPI /*  [905]imm/ImmOrg.hpp:1462:17( [780] >record 'ImmAdapterBlockDynamicFallbackAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1462:17( [780] >record 'ImmAdapterBlockAPI'<>) */>>("ImmAdapterBlockDynamicFallbackAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAdmonitionAPI /*  [905]imm/ImmOrg.hpp:1463:17( [780] >record 'ImmAdapterBlockAdmonitionAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1463:17( [780] >record 'ImmAdapterBlockAPI'<>) */>>("ImmAdapterBlockAdmonitionAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockCodeEvalResultAPI /*  [905]imm/ImmOrg.hpp:1464:17( [780] >record 'ImmAdapterBlockCodeEvalResultAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1464:17( [780] >record 'ImmAdapterBlockAPI'<>) */>>("ImmAdapterBlockCodeEvalResultAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockCodeAPI /*  [905]imm/ImmOrg.hpp:1465:17( [780] >record 'ImmAdapterBlockCodeAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1465:17( [780] >record 'ImmAdapterBlockAPI'<>) */>>("ImmAdapterBlockCodeAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterTableAPI /*  [905]imm/ImmOrg.hpp:1470:17( [780] >record 'ImmAdapterTableAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1470:17( [780] >record 'ImmAdapterBlockAPI'<>) */>>("ImmAdapterTableAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlock>, emscripten::base<org::imm::ImmAdapterBlockAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCell>, emscripten::base<org::imm::ImmAdapterCellAPI>>("ImmAdapterT")
    .function("getIsBlock", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmCell>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCell>::getIsBlock))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmRow>, emscripten::base<org::imm::ImmAdapterRowAPI>>("ImmAdapterT")
    .function("getCells", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmRow>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRow>::getCells))
    .function("getIsBlock", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmRow>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRow>::getIsBlock))
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdCaptionAPI /*  [905]imm/ImmOrg.hpp:1396:17( [780] >record 'ImmAdapterCmdCaptionAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttachedAPI /*  [905]imm/ImmOrg.hpp:1396:17( [780] >record 'ImmAdapterAttachedAPI'<>) */>>("ImmAdapterCmdCaptionAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdColumnsAPI /*  [905]imm/ImmOrg.hpp:1399:17( [780] >record 'ImmAdapterCmdColumnsAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttachedAPI /*  [905]imm/ImmOrg.hpp:1399:17( [780] >record 'ImmAdapterAttachedAPI'<>) */>>("ImmAdapterCmdColumnsAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdNameAPI /*  [905]imm/ImmOrg.hpp:1400:17( [780] >record 'ImmAdapterCmdNameAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttachedAPI /*  [905]imm/ImmOrg.hpp:1400:17( [780] >record 'ImmAdapterAttachedAPI'<>) */>>("ImmAdapterCmdNameAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdCallAPI /*  [905]imm/ImmOrg.hpp:1401:17( [780] >record 'ImmAdapterCmdCallAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttachedAPI /*  [905]imm/ImmOrg.hpp:1401:17( [780] >record 'ImmAdapterAttachedAPI'<>) */>>("ImmAdapterCmdCallAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdResultsAPI /*  [905]imm/ImmOrg.hpp:1409:17( [780] >record 'ImmAdapterCmdResultsAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttachedAPI /*  [905]imm/ImmOrg.hpp:1409:17( [780] >record 'ImmAdapterAttachedAPI'<>) */>>("ImmAdapterCmdResultsAPI")
    ;
  emscripten::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAttrAPI /*  [905]imm/ImmOrg.hpp:1486:17( [780] >record 'ImmAdapterCmdAttrAPI'<>) */, emscripten::base<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttachedAPI /*  [905]imm/ImmOrg.hpp:1486:17( [780] >record 'ImmAdapterAttachedAPI'<>) */>>("ImmAdapterCmdAttrAPI")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmAttached>, emscripten::base<org::imm::ImmAdapterAttachedAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockCenter>, emscripten::base<org::imm::ImmAdapterBlockCenterAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockQuote>, emscripten::base<org::imm::ImmAdapterBlockQuoteAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockVerse>, emscripten::base<org::imm::ImmAdapterBlockVerseAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockExample>, emscripten::base<org::imm::ImmAdapterBlockExampleAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmInlineExport>, emscripten::base<org::imm::ImmAdapterInlineExportAPI>>("ImmAdapterT")
    .function("getExporter", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmInlineExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineExport>::getExporter))
    .function("getContent", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmInlineExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineExport>::getContent))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdExport>, emscripten::base<org::imm::ImmAdapterCmdExportAPI>>("ImmAdapterT")
    .function("getExporter", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdExport>::getExporter))
    .function("getContent", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdExport>::getContent))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockExport>, emscripten::base<org::imm::ImmAdapterBlockExportAPI>>("ImmAdapterT")
    .function("getExporter", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmBlockExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockExport>::getExporter))
    .function("getContent", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmBlockExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockExport>::getContent))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>, emscripten::base<org::imm::ImmAdapterBlockDynamicFallbackAPI>>("ImmAdapterT")
    .function("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::getName))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>, emscripten::base<org::imm::ImmAdapterBlockAdmonitionAPI>>("ImmAdapterT")
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>, emscripten::base<org::imm::ImmAdapterBlockCodeEvalResultAPI>>("ImmAdapterT")
    .function("getRaw", static_cast<hstd::ext::ImmVec<org::sem::OrgCodeEvalOutput> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::getRaw))
    .function("getNode", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::getNode))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmBlockCode>, emscripten::base<org::imm::ImmAdapterBlockCodeAPI>>("ImmAdapterT")
    .function("getLang", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getLang))
    .function("getResult", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getResult))
    .function("getLines", static_cast<hstd::ext::ImmVec<org::sem::BlockCodeLine> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getLines))
    .function("getSwitches", static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getSwitches))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmTable>, emscripten::base<org::imm::ImmAdapterTableAPI>>("ImmAdapterT")
    .function("getRows", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmTable>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTable>::getRows))
    .function("getIsBlock", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmTable>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTable>::getIsBlock))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCaption>, emscripten::base<org::imm::ImmAdapterCmdCaptionAPI>>("ImmAdapterT")
    .function("getText", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::getText))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdColumns>, emscripten::base<org::imm::ImmAdapterCmdColumnsAPI>>("ImmAdapterT")
    .function("getView", static_cast<org::sem::ColumnView(org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::getView))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdName>, emscripten::base<org::imm::ImmAdapterCmdNameAPI>>("ImmAdapterT")
    .function("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdName>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdName>::getName))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCall>, emscripten::base<org::imm::ImmAdapterCmdCallAPI>>("ImmAdapterT")
    .function("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getName))
    .function("getFileName", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getFileName))
    .function("getInsideHeaderAttrs", static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getInsideHeaderAttrs))
    .function("getCallAttrs", static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getCallAttrs))
    .function("getEndHeaderAttrs", static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getEndHeaderAttrs))
    .function("getResult", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getResult))
    ;
  emscripten::class_<org::imm::ImmAdapterT<org::imm::ImmCmdAttr>, emscripten::base<org::imm::ImmAdapterCmdAttrAPI>>("ImmAdapterT")
    .function("getTarget", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::getTarget))
    ;
  org::bind::js::bind_enum<CheckboxState>("CheckboxState");
  org::bind::js::bind_enum<SubtreeTodoSource>("SubtreeTodoSource");
  org::bind::js::bind_enum<ListFormattingMode>("ListFormattingMode");
  org::bind::js::bind_enum<InitialSubtreeVisibility>("InitialSubtreeVisibility");
  org::bind::js::bind_enum<OrgSpecName>("OrgSpecName");
  org::bind::js::bind_enum<OrgNodeKind>("OrgNodeKind");
  org::bind::js::bind_enum<OrgTokenKind>("OrgTokenKind");
  org::bind::js::bind_enum<OrgJsonKind>("OrgJsonKind");
  org::bind::js::bind_enum<OrgSemKind>("OrgSemKind");
  org::bind::js::bind_enum<org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct api/SemBaseApi.hpp:162:25 */>("AstTrackingGroupKind");
  org::bind::js::bind_enum<org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct imm/ImmOrgGraph.hpp:36:5 */>("GraphMapLinkKind");
  emscripten::function("newSemTimeStatic", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Time /*  [640]Type parameter [905]api/SemBaseApi.hpp:12:32( [780] >record 'Time'<>) */> /*  [905]api/SemBaseApi.hpp:12:32( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown const& /*  [905]api/SemBaseApi.hpp:13:36( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'UserTimeBreakdown'<>)<>) */, bool /*  [905]api/SemBaseApi.hpp:14:36( [755] >bool<>) */)>(&org::newSemTimeStatic));
  emscripten::function("initImmutableAstContext", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]api/SemBaseApi.hpp:16:46( [780] >record 'ImmAstContext'<>) */> /*  [905]api/SemBaseApi.hpp:16:46( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */(*)()>(&org::initImmutableAstContext));
  emscripten::function("asOneNode", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:25:31( [780] >record 'Org'<>) */> /*  [905]api/SemBaseApi.hpp:25:31( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:26:43( [780] >record 'Org'<>) */> const& /*  [905]api/SemBaseApi.hpp:26:43( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */)>(&org::asOneNode));
  emscripten::function("formatToString", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]api/SemBaseApi.hpp:28:22( [735] typedef type bits/stringfwd.h:79:33) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:28:58( [780] >record 'Org'<>) */> /*  [905]api/SemBaseApi.hpp:28:58( [780] >record 'SemId'< [657] templates: template-specialization-type>) */)>(&org::formatToString));
  emscripten::function("exportToYamlString", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]api/SemBaseApi.hpp:49:22( [735] typedef type bits/stringfwd.h:79:33) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:50:33( [780] >record 'Org'<>) */> const& /*  [905]api/SemBaseApi.hpp:50:33( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts const& /*  [905]api/SemBaseApi.hpp:51:33( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'OrgYamlExportOpts'<>)<>) */)>(&org::exportToYamlString));
  emscripten::function("exportToYamlFile", static_cast<void /*  [905]api/SemBaseApi.hpp:52:15(<>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:53:33( [780] >record 'Org'<>) */> const& /*  [905]api/SemBaseApi.hpp:53:33( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]api/SemBaseApi.hpp:54:33( [735] typedef type bits/stringfwd.h:79:33) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts const& /*  [905]api/SemBaseApi.hpp:55:33( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'OrgYamlExportOpts'<>)<>) */)>(&org::exportToYamlFile));
  emscripten::function("exportToJsonString", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]api/SemBaseApi.hpp:57:22( [735] typedef type bits/stringfwd.h:79:33) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:57:69( [780] >record 'Org'<>) */> const& /*  [905]api/SemBaseApi.hpp:57:69( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */)>(&org::exportToJsonString));
  emscripten::function("exportToJsonFile", static_cast<void /*  [905]api/SemBaseApi.hpp:58:22(<>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:59:40( [780] >record 'Org'<>) */> const& /*  [905]api/SemBaseApi.hpp:59:40( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]api/SemBaseApi.hpp:60:40( [735] typedef type bits/stringfwd.h:79:33) */)>(&org::exportToJsonFile));
  emscripten::function("readProtobufFile", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Document /*  [640]Type parameter [905]api/SemBaseApi.hpp:62:36( [780] >record 'Document'<>) */> /*  [905]api/SemBaseApi.hpp:62:36( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/SemBaseApi.hpp:63:24( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */)>(&org::readProtobufFile));
  emscripten::function("exportToProtobufFile", static_cast<void /*  [905]api/SemBaseApi.hpp:65:15(<>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Document /*  [640]Type parameter [905]api/SemBaseApi.hpp:66:31( [780] >record 'Document'<>) */> /*  [905]api/SemBaseApi.hpp:66:31( [780] >record 'SemId'< [657] templates: template-specialization-type>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/SemBaseApi.hpp:67:31( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */)>(&org::exportToProtobufFile));
  emscripten::function("exportToTreeString", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]api/SemBaseApi.hpp:92:22( [735] typedef type bits/stringfwd.h:79:33) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:93:33( [780] >record 'Org'<>) */> const& /*  [905]api/SemBaseApi.hpp:93:33( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts const& /*  [905]api/SemBaseApi.hpp:94:33( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'OrgTreeExportOpts'<>)<>) */)>(&org::exportToTreeString));
  emscripten::function("exportToTreeFile", static_cast<void /*  [905]api/SemBaseApi.hpp:96:15(<>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:97:33( [780] >record 'Org'<>) */> const& /*  [905]api/SemBaseApi.hpp:97:33( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]api/SemBaseApi.hpp:98:33( [735] typedef type bits/stringfwd.h:79:33) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts const& /*  [905]api/SemBaseApi.hpp:99:33( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'OrgTreeExportOpts'<>)<>) */)>(&org::exportToTreeFile));
  emscripten::function("getAstTrackingMap", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:265:25( [780] >record 'AstTrackingMap'<>) */(*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:266:44( [780] >record 'Org'<>) */> /*  [640]Type parameter [905]api/SemBaseApi.hpp:266:44( [780] >record 'SemId'< [657] templates: template-specialization-type>) */> const& /*  [905]api/SemBaseApi.hpp:266:44( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Vec'< [657] templates: template-specialization-type>)<>) */)>(&org::getAstTrackingMap));
  emscripten::function("getSubnodeGroups", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [640]Type parameter [905]api/SemBaseApi.hpp:268:38( [780] >record 'AstTrackingGroup'<>) */> /*  [905]api/SemBaseApi.hpp:268:38( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:269:27( [780] >record 'Org'<>) */> /*  [905]api/SemBaseApi.hpp:269:27( [780] >record 'SemId'< [657] templates: template-specialization-type>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap const& /*  [905]api/SemBaseApi.hpp:270:27( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'AstTrackingMap'<>)<>) */)>(&org::getSubnodeGroups));
  emscripten::function("annotateSequence", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:93:34( [780] >record 'SequenceAnnotation'<>) */> /*  [905]stdlib/RangeSegmentation.hpp:93:34( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:94:38( [780] >record 'SequenceSegmentGroup'<>) */> const& /*  [905]stdlib/RangeSegmentation.hpp:94:38( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Vec'< [657] templates: template-specialization-type>)<>) */, int /*  [905]stdlib/RangeSegmentation.hpp:95:38( [766] >builtin/unqual<>) */, int /*  [905]stdlib/RangeSegmentation.hpp:96:38( [766] >builtin/unqual<>) */)>(&hstd::annotateSequence));
  emscripten::function("initMapGraphState", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:441:41( [780] >record 'MapGraphState'<>) */> /*  [905]imm/ImmOrgGraph.hpp:441:41( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */(*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:442:46( [780] >record 'ImmAstContext'<>) */> /*  [905]imm/ImmOrgGraph.hpp:442:46( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */)>(&org /*  [539]regular type namespaces @[1] */::graph::initMapGraphState));
  emscripten::function("serializeAstContextToText", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]serde/SemOrgCereal.hpp:7:73( [735] typedef type bits/stringfwd.h:79:33) */(*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]serde/SemOrgCereal.hpp:8:43( [780] >record 'ImmAstContext'<>) */> const& /*  [905]serde/SemOrgCereal.hpp:8:43( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[1] */::imm::serializeToText));
  emscripten::function("serializeAstContextFromText", static_cast<void /*  [905]serde/SemOrgCereal.hpp:9:68(<>) */(*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]serde/SemOrgCereal.hpp:10:43( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]serde/SemOrgCereal.hpp:11:43( [780] >record 'ImmAstContext'<>) */> const& /*  [905]serde/SemOrgCereal.hpp:11:43( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[1] */::imm::serializeFromText));
  emscripten::function("serializeAstEpochToText", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]serde/SemOrgCereal.hpp:13:71( [735] typedef type bits/stringfwd.h:79:33) */(*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstReplaceEpoch /*  [640]Type parameter [905]serde/SemOrgCereal.hpp:14:48( [780] >record 'ImmAstReplaceEpoch'<>) */> const& /*  [905]serde/SemOrgCereal.hpp:14:48( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[1] */::imm::serializeToText));
  emscripten::function("serializeAstEpochFromText", static_cast<void /*  [905]serde/SemOrgCereal.hpp:15:66(<>) */(*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]serde/SemOrgCereal.hpp:16:48( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstReplaceEpoch /*  [640]Type parameter [905]serde/SemOrgCereal.hpp:17:48( [780] >record 'ImmAstReplaceEpoch'<>) */> const& /*  [905]serde/SemOrgCereal.hpp:17:48( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[1] */::imm::serializeFromText));
  emscripten::function("serializeMapGraphToText", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]serde/SemOrgCereal.hpp:19:71( [735] typedef type bits/stringfwd.h:79:33) */(*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [640]Type parameter [905]serde/SemOrgCereal.hpp:20:50( [780] >record 'MapGraph'<>) */> const& /*  [905]serde/SemOrgCereal.hpp:20:50( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[1] */::imm::serializeToText));
  emscripten::function("serializeMapGraphFromText", static_cast<void /*  [905]serde/SemOrgCereal.hpp:21:66(<>) */(*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]serde/SemOrgCereal.hpp:22:50( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [640]Type parameter [905]serde/SemOrgCereal.hpp:23:50( [780] >record 'MapGraph'<>) */> const& /*  [905]serde/SemOrgCereal.hpp:23:50( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[1] */::imm::serializeFromText));
  emscripten::function("serializeFromTextToTreeDump", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]serde/SemOrgCereal.hpp:27:22( [735] typedef type bits/stringfwd.h:79:33) */(*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]serde/SemOrgCereal.hpp:28:24( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */)>(&org /*  [539]regular type namespaces @[1] */::imm::serializeFromTextToTreeDump));
  haxorg_wasm_manual_register();
}

EMSCRIPTEN_BINDINGS(haxorg_wasm) {
  org::bind::js::type_registration_guard g;
  subdivide_0(g);
  subdivide_1(g);
  subdivide_2(g);
  subdivide_3(g);
  subdivide_4(g);
  subdivide_5(g);
  subdivide_6(g);
  subdivide_7(g);
  subdivide_8(g);
}
/* clang-format on */