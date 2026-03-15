/* clang-format off */
#undef slots
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/map.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/filesystem.h>
#include <nanobind/stl/function.h>
#include <nanobind/stl/map.h>
#include <nanobind/stl/optional.h>
#include <nanobind/stl/set.h>
#include <nanobind/stl/shared_ptr.h>
#include <nanobind/stl/string_view.h>
#include <nanobind/stl/tuple.h>
#include <nanobind/stl/unique_ptr.h>
#include <nanobind/stl/unordered_map.h>
#include <nanobind/stl/variant.h>
#include <nanobind/operators.h>
#include <nanobind/make_iterator.h>
#include <nanobind/ndarray.h>
#include <haxorg/imm/ImmOrgAdapter.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include "pyhaxorg_manual_impl.hpp"
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [640]Type parameter [905]sem/SemOrgBaseSharedTypes.hpp:49:33( [780] >record 'OrgJson'<>) */> /*  [905]sem/SemOrgBaseSharedTypes.hpp:49:33( [780] >record 'Vec'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::vector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [640]Type parameter [905]sem/SemOrgBaseSharedTypes.hpp:49:33( [780] >record 'OrgJson'<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]sem/SemOrgBase.hpp:233:36( [780] >record 'Org'<>) */> /*  [640]Type parameter [905]sem/SemOrgBase.hpp:233:36( [780] >record 'SemId'< [657] templates: template-specialization-type>) */> /*  [905]sem/SemOrgBase.hpp:233:36( [780] >record 'Vec'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::vector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]sem/SemOrgBase.hpp:233:36( [780] >record 'Org'<>) */> /*  [640]Type parameter [905]sem/SemOrgBase.hpp:233:36( [780] >record 'SemId'< [657] templates: template-specialization-type>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ext /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Report /*  [640]Type parameter [905]api/ParseContext.hpp:142:43( [780] >record 'Report'<>) */> /*  [905]api/ParseContext.hpp:142:43( [780] >record 'Vec'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::vector<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ext /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Report /*  [640]Type parameter [905]api/ParseContext.hpp:142:43( [780] >record 'Report'<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ErrorGroup /*  [640]Type parameter [905]api/ParseContext.hpp:146:53( [780] >record 'ErrorGroup'<>) */> /*  [640]Type parameter [905]api/ParseContext.hpp:146:53( [780] >record 'SemId'< [657] templates: template-specialization-type>) */> /*  [905]api/ParseContext.hpp:146:53( [780] >record 'Vec'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::vector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ErrorGroup /*  [640]Type parameter [905]api/ParseContext.hpp:146:53( [780] >record 'ErrorGroup'<>) */> /*  [640]Type parameter [905]api/ParseContext.hpp:146:53( [780] >record 'SemId'< [657] templates: template-specialization-type>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<int /*  [640]Type parameter [905]imm/ImmOrg.hpp:1110:31( [766] >builtin/unqual<>) */> /*  [905]imm/ImmOrg.hpp:1110:31( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Vec'< [657] templates: template-specialization-type>)<>) */)
NB_MAKE_OPAQUE(std::vector<int /*  [640]Type parameter [905]imm/ImmOrg.hpp:1110:31( [766] >builtin/unqual<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [640]Type parameter [905]imm/ImmOrg.hpp:1119:36( [780] >record 'ImmAdapter'<>) */> /*  [905]imm/ImmOrg.hpp:1119:36( [780] >record 'Vec'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::vector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [640]Type parameter [905]imm/ImmOrg.hpp:1119:36( [780] >record 'ImmAdapter'<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UnorderedSet<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::pair<OrgSemKind /*  [640]Type parameter [905]imm/ImmOrg.hpp:984:13( [786] >enum 'OrgSemKind'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmReflFieldId /*  [640]Type parameter [905]imm/ImmOrg.hpp:984:13( [780] >record 'ImmReflFieldId'<>) */> /*  [640]Type parameter [905]imm/ImmOrg.hpp:984:13( [780] >record 'pair'< [657] templates: template-specialization-type>) */> /*  [905]imm/ImmOrg.hpp:984:13( [780] >record 'UnorderedSet'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UnorderedMap<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::HashTagFlat /*  [640]Type parameter [905]api/SemBaseApi.hpp:154:13( [780] >record 'HashTagFlat'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [640]Type parameter [905]api/SemBaseApi.hpp:154:13( [780] >record 'AstTrackingPath'<>) */> /*  [905]api/SemBaseApi.hpp:154:13( [780] >record 'UnorderedMap'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::unordered_map<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::HashTagFlat /*  [640]Type parameter [905]api/SemBaseApi.hpp:154:13( [780] >record 'HashTagFlat'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [640]Type parameter [905]api/SemBaseApi.hpp:154:13( [780] >record 'AstTrackingPath'<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UnorderedMap<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str /*  [640]Type parameter [905]api/SemBaseApi.hpp:223:9( [780] >record 'Str'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:223:9( [780] >record 'AstTrackingAlternatives'<>) */> /*  [905]api/SemBaseApi.hpp:223:9( [780] >record 'UnorderedMap'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::unordered_map<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str /*  [640]Type parameter [905]api/SemBaseApi.hpp:223:9( [780] >record 'Str'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:223:9( [780] >record 'AstTrackingAlternatives'<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UnorderedMap<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::HashTagFlat /*  [640]Type parameter [905]api/SemBaseApi.hpp:232:9( [780] >record 'HashTagFlat'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:232:9( [780] >record 'AstTrackingAlternatives'<>) */> /*  [905]api/SemBaseApi.hpp:232:9( [780] >record 'UnorderedMap'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::unordered_map<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::HashTagFlat /*  [640]Type parameter [905]api/SemBaseApi.hpp:232:9( [780] >record 'HashTagFlat'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:232:9( [780] >record 'AstTrackingAlternatives'<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:38:35( [780] >record 'SequenceSegment'<>) */> /*  [905]stdlib/RangeSegmentation.hpp:38:35( [780] >record 'Vec'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::vector<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:38:35( [780] >record 'SequenceSegment'<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotationTag /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:79:41( [780] >record 'SequenceAnnotationTag'<>) */> /*  [905]stdlib/RangeSegmentation.hpp:79:41( [780] >record 'Vec'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::vector<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotationTag /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:79:41( [780] >record 'SequenceAnnotationTag'<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmUniqId /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:25:49( [780] >record 'ImmUniqId'<>) */> /*  [905]imm/ImmOrgGraph.hpp:25:49( [780] >record 'Vec'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::vector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmUniqId /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:25:49( [780] >record 'ImmUniqId'<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:44:34( [780] >record 'MapLink'<>) */> /*  [905]imm/ImmOrgGraph.hpp:44:34( [780] >record 'Vec'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::vector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:44:34( [780] >record 'MapLink'<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:119:60( [780] >record 'MapNode'<>) */> /*  [1555] Typedef Decl Visit [905]imm/ImmOrgGraph.hpp:119:60( [780] >record 'Vec'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::vector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:119:60( [780] >record 'MapNode'<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:163:33( [780] >record 'MapEdge'<>) */> /*  [905]imm/ImmOrgGraph.hpp:163:33( [780] >record 'Vec'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::vector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:163:33( [780] >record 'MapEdge'<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UnorderedMap<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:117:60( [780] >record 'MapNode'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:117:60( [780] >record 'MapNodeProp'<>) */> /*  [1555] Typedef Decl Visit [905]imm/ImmOrgGraph.hpp:117:60( [780] >record 'UnorderedMap'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::unordered_map<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:117:60( [780] >record 'MapNode'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:117:60( [780] >record 'MapNodeProp'<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UnorderedMap<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:118:60( [780] >record 'MapEdge'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:118:60( [780] >record 'MapEdgeProp'<>) */> /*  [1555] Typedef Decl Visit [905]imm/ImmOrgGraph.hpp:118:60( [780] >record 'UnorderedMap'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::unordered_map<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:118:60( [780] >record 'MapEdge'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:118:60( [780] >record 'MapEdgeProp'<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UnorderedMap<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:120:60( [780] >record 'MapNode'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::AdjNodesList /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:120:60( [735] typedef type imm/ImmOrgGraph.hpp:119:60) */> /*  [1555] Typedef Decl Visit [905]imm/ImmOrgGraph.hpp:120:60( [780] >record 'UnorderedMap'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::unordered_map<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:120:60( [780] >record 'MapNode'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::AdjNodesList /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:120:60( [735] typedef type imm/ImmOrgGraph.hpp:119:60) */>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::LispCode>)
NB_MAKE_OPAQUE(std::vector<org::sem::LispCode>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::Tblfm::Assign>)
NB_MAKE_OPAQUE(std::vector<org::sem::Tblfm::Assign>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::Tblfm::Expr>)
NB_MAKE_OPAQUE(std::vector<org::sem::Tblfm::Expr>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::Tblfm::Assign::Flag>)
NB_MAKE_OPAQUE(std::vector<org::sem::Tblfm::Assign::Flag>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::AttrValue::DimensionSpan>)
NB_MAKE_OPAQUE(std::vector<org::sem::AttrValue::DimensionSpan>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::Str>)
NB_MAKE_OPAQUE(std::vector<hstd::Str>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::HashTagFlat>)
NB_MAKE_OPAQUE(std::vector<org::sem::HashTagFlat>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::HashTagText>)
NB_MAKE_OPAQUE(std::vector<org::sem::HashTagText>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::AttrValue>)
NB_MAKE_OPAQUE(std::vector<org::sem::AttrValue>)
NB_MAKE_OPAQUE(hstd::UnorderedMap<hstd::Str, org::sem::AttrList>)
NB_MAKE_OPAQUE(std::unordered_map<hstd::Str, org::sem::AttrList>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::OrgCodeEvalInput::Var>)
NB_MAKE_OPAQUE(std::vector<org::sem::OrgCodeEvalInput::Var>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::ColumnView::Column>)
NB_MAKE_OPAQUE(std::vector<org::sem::ColumnView::Column>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::BlockCodeLine::Part>)
NB_MAKE_OPAQUE(std::vector<org::sem::BlockCodeLine::Part>)
NB_MAKE_OPAQUE(hstd::UnorderedMap<hstd::Str, hstd::Str>)
NB_MAKE_OPAQUE(std::unordered_map<hstd::Str, hstd::Str>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::ErrorItem>>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::ErrorItem>>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::Time::Repeat>)
NB_MAKE_OPAQUE(std::vector<org::sem::Time::Repeat>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::Symbol::Param>)
NB_MAKE_OPAQUE(std::vector<org::sem::Symbol::Param>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::ErrorSkipToken>>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::ErrorSkipToken>>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SubtreePeriod>)
NB_MAKE_OPAQUE(std::vector<org::sem::SubtreePeriod>)
NB_MAKE_OPAQUE(hstd::IntSet<org::sem::SubtreePeriod::Kind>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::NamedProperty>)
NB_MAKE_OPAQUE(std::vector<org::sem::NamedProperty>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::HashTag>>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::HashTag>>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::SubtreeLog>>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::SubtreeLog>>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::TodoKeyword>)
NB_MAKE_OPAQUE(std::vector<org::sem::TodoKeyword>)
NB_MAKE_OPAQUE(hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem /* imm_write */> /* imm_write */> /* imm_write */)
NB_MAKE_OPAQUE(hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg /* imm_write */> /* imm_write */> /* imm_write */)
NB_MAKE_OPAQUE(hstd::ext::ImmBox<hstd::Str> /* rewrite_field */)
NB_MAKE_OPAQUE(hstd::ext::ImmVec<org::imm::ImmTime::Repeat /* imm_write */> /* imm_write */)
NB_MAKE_OPAQUE(hstd::ext::ImmBox<hstd::Opt<org::imm::ImmTime::Repeat /* imm_write */>> /* rewrite_field */)
NB_MAKE_OPAQUE(hstd::ext::ImmVec<org::imm::ImmSymbol::Param /* imm_write */> /* imm_write */)
NB_MAKE_OPAQUE(hstd::ext::ImmBox<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>> /* rewrite_field */)
NB_MAKE_OPAQUE(hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorSkipToken /* imm_write */> /* imm_write */> /* imm_write */)
NB_MAKE_OPAQUE(hstd::ext::ImmVec<hstd /* imm_write */::Str /* imm_write */> /* imm_write */)
NB_MAKE_OPAQUE(hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmStmtList /* imm_write */> /* imm_write */>> /* rewrite_field */)
NB_MAKE_OPAQUE(hstd::ext::ImmBox<hstd::Opt<org::sem::SubtreeCompletion>> /* rewrite_field */)
NB_MAKE_OPAQUE(hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph /* imm_write */> /* imm_write */>> /* rewrite_field */)
NB_MAKE_OPAQUE(hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag /* imm_write */> /* imm_write */> /* imm_write */)
NB_MAKE_OPAQUE(hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog /* imm_write */> /* imm_write */> /* imm_write */)
NB_MAKE_OPAQUE(hstd::ext::ImmVec<org::sem::NamedProperty> /* imm_write */)
NB_MAKE_OPAQUE(hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime /* imm_write */> /* imm_write */>> /* rewrite_field */)
NB_MAKE_OPAQUE(hstd::ext::ImmBox<hstd::Opt<bool /* imm_write */>> /* rewrite_field */)
NB_MAKE_OPAQUE(hstd::ext::ImmBox<hstd::Opt<int /* imm_write */>> /* rewrite_field */)
NB_MAKE_OPAQUE(hstd::ext::ImmBox<hstd::Opt<org::sem::ColumnView>> /* rewrite_field */)
NB_MAKE_OPAQUE(hstd::ext::ImmVec<org::sem::TodoKeyword> /* imm_write */)
NB_MAKE_OPAQUE(hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmRawText /* imm_write */> /* imm_write */>> /* rewrite_field */)
NB_MAKE_OPAQUE(hstd::ext::ImmBox<hstd::Opt<org::sem::SubtreePath>> /* rewrite_field */)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::BigIdent>>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::BigIdent>>)
NB_MAKE_OPAQUE(hstd::Vec<hstd::UserTime>)
NB_MAKE_OPAQUE(std::vector<hstd::UserTime>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::Time>>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::Time>>)
NB_MAKE_OPAQUE(hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmOrg /* imm_write */> /* imm_write */>> /* rewrite_field */)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::Cell>>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::Cell>>)
NB_MAKE_OPAQUE(hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell /* imm_write */> /* imm_write */> /* imm_write */)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::OrgCodeEvalOutput>)
NB_MAKE_OPAQUE(std::vector<org::sem::OrgCodeEvalOutput>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::BlockCodeEvalResult>>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::BlockCodeEvalResult>>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::BlockCodeLine>)
NB_MAKE_OPAQUE(std::vector<org::sem::BlockCodeLine>)
NB_MAKE_OPAQUE(hstd::Vec<org::sem::SemId<org::sem::Row>>)
NB_MAKE_OPAQUE(std::vector<org::sem::SemId<org::sem::Row>>)
NB_MAKE_OPAQUE(hstd::ext::ImmVec<org::sem::OrgCodeEvalOutput> /* imm_write */)
NB_MAKE_OPAQUE(hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult /* imm_write */> /* imm_write */> /* imm_write */)
NB_MAKE_OPAQUE(hstd::ext::ImmVec<org::sem::BlockCodeLine> /* imm_write */)
NB_MAKE_OPAQUE(hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow /* imm_write */> /* imm_write */> /* imm_write */)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [640]Type parameter [905]api/SemBaseApi.hpp:268:38( [780] >record 'AstTrackingGroup'<>) */> /*  [905]api/SemBaseApi.hpp:268:38( [780] >record 'Vec'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::vector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [640]Type parameter [905]api/SemBaseApi.hpp:268:38( [780] >record 'AstTrackingGroup'<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:93:34( [780] >record 'SequenceAnnotation'<>) */> /*  [905]stdlib/RangeSegmentation.hpp:93:34( [780] >record 'Vec'< [657] templates: template-specialization-type>) */)
NB_MAKE_OPAQUE(std::vector<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:93:34( [780] >record 'SequenceAnnotation'<>) */>)
NB_MAKE_OPAQUE(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:94:38( [780] >record 'SequenceSegmentGroup'<>) */> /*  [905]stdlib/RangeSegmentation.hpp:94:38( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Vec'< [657] templates: template-specialization-type>)<>) */)
NB_MAKE_OPAQUE(std::vector<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:94:38( [780] >record 'SequenceSegmentGroup'<>) */>)
NB_MODULE(pyhaxorg, m) {
  org::bind::python::PyTypeRegistryGuard type_registry_guard{};
  org::bind::python::bind_hstdVec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [640]Type parameter [905]sem/SemOrgBaseSharedTypes.hpp:49:33( [780] >record 'OrgJson'<>) */>(m, "HstdVecOfOrgJson", type_registry_guard);
  org::bind::python::bind_stdvector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [640]Type parameter [905]sem/SemOrgBaseSharedTypes.hpp:49:33( [780] >record 'OrgJson'<>) */>(m, "StdVecOfOrgJson", type_registry_guard);
  org::bind::python::bind_hstdVec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]sem/SemOrgBase.hpp:233:36( [780] >record 'Org'<>) */> /*  [640]Type parameter [905]sem/SemOrgBase.hpp:233:36( [780] >record 'SemId'< [657] templates: template-specialization-type>) */>(m, "HstdVecOfSemIdOfOrg", type_registry_guard);
  org::bind::python::bind_stdvector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]sem/SemOrgBase.hpp:233:36( [780] >record 'Org'<>) */> /*  [640]Type parameter [905]sem/SemOrgBase.hpp:233:36( [780] >record 'SemId'< [657] templates: template-specialization-type>) */>(m, "StdVecOfSemIdOfOrg", type_registry_guard);
  org::bind::python::bind_hstdVec<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ext /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Report /*  [640]Type parameter [905]api/ParseContext.hpp:142:43( [780] >record 'Report'<>) */>(m, "HstdVecOfReport", type_registry_guard);
  org::bind::python::bind_stdvector<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ext /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Report /*  [640]Type parameter [905]api/ParseContext.hpp:142:43( [780] >record 'Report'<>) */>(m, "StdVecOfReport", type_registry_guard);
  org::bind::python::bind_hstdVec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ErrorGroup /*  [640]Type parameter [905]api/ParseContext.hpp:146:53( [780] >record 'ErrorGroup'<>) */> /*  [640]Type parameter [905]api/ParseContext.hpp:146:53( [780] >record 'SemId'< [657] templates: template-specialization-type>) */>(m, "HstdVecOfSemIdOfErrorGroup", type_registry_guard);
  org::bind::python::bind_stdvector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ErrorGroup /*  [640]Type parameter [905]api/ParseContext.hpp:146:53( [780] >record 'ErrorGroup'<>) */> /*  [640]Type parameter [905]api/ParseContext.hpp:146:53( [780] >record 'SemId'< [657] templates: template-specialization-type>) */>(m, "StdVecOfSemIdOfErrorGroup", type_registry_guard);
  org::bind::python::bind_hstdVec<int /*  [640]Type parameter [905]imm/ImmOrg.hpp:1110:31( [766] >builtin/unqual<>) */>(m, "HstdVecOfInt", type_registry_guard);
  org::bind::python::bind_stdvector<int /*  [640]Type parameter [905]imm/ImmOrg.hpp:1110:31( [766] >builtin/unqual<>) */>(m, "StdVecOfInt", type_registry_guard);
  org::bind::python::bind_hstdVec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [640]Type parameter [905]imm/ImmOrg.hpp:1119:36( [780] >record 'ImmAdapter'<>) */>(m, "HstdVecOfImmAdapter", type_registry_guard);
  org::bind::python::bind_stdvector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [640]Type parameter [905]imm/ImmOrg.hpp:1119:36( [780] >record 'ImmAdapter'<>) */>(m, "StdVecOfImmAdapter", type_registry_guard);
  org::bind::python::bind_hstdUnorderedSet<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::pair<OrgSemKind /*  [640]Type parameter [905]imm/ImmOrg.hpp:984:13( [786] >enum 'OrgSemKind'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmReflFieldId /*  [640]Type parameter [905]imm/ImmOrg.hpp:984:13( [780] >record 'ImmReflFieldId'<>) */> /*  [640]Type parameter [905]imm/ImmOrg.hpp:984:13( [780] >record 'pair'< [657] templates: template-specialization-type>) */>(m, "HstdSetOfStdPairOfOrgSemKindImmReflFieldId", type_registry_guard);
  org::bind::python::bind_hstdUnorderedMap<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::HashTagFlat /*  [640]Type parameter [905]api/SemBaseApi.hpp:154:13( [780] >record 'HashTagFlat'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [640]Type parameter [905]api/SemBaseApi.hpp:154:13( [780] >record 'AstTrackingPath'<>) */>(m, "HstdMapOfHashTagFlatAstTrackingPath", type_registry_guard);
  org::bind::python::bind_stdunordered_map<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::HashTagFlat /*  [640]Type parameter [905]api/SemBaseApi.hpp:154:13( [780] >record 'HashTagFlat'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [640]Type parameter [905]api/SemBaseApi.hpp:154:13( [780] >record 'AstTrackingPath'<>) */>(m, "StdMapOfHashTagFlatAstTrackingPath", type_registry_guard);
  org::bind::python::bind_hstdUnorderedMap<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str /*  [640]Type parameter [905]api/SemBaseApi.hpp:223:9( [780] >record 'Str'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:223:9( [780] >record 'AstTrackingAlternatives'<>) */>(m, "HstdMapOfStrAstTrackingAlternatives", type_registry_guard);
  org::bind::python::bind_stdunordered_map<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str /*  [640]Type parameter [905]api/SemBaseApi.hpp:223:9( [780] >record 'Str'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:223:9( [780] >record 'AstTrackingAlternatives'<>) */>(m, "StdMapOfStrAstTrackingAlternatives", type_registry_guard);
  org::bind::python::bind_hstdUnorderedMap<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::HashTagFlat /*  [640]Type parameter [905]api/SemBaseApi.hpp:232:9( [780] >record 'HashTagFlat'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:232:9( [780] >record 'AstTrackingAlternatives'<>) */>(m, "HstdMapOfHashTagFlatAstTrackingAlternatives", type_registry_guard);
  org::bind::python::bind_stdunordered_map<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::HashTagFlat /*  [640]Type parameter [905]api/SemBaseApi.hpp:232:9( [780] >record 'HashTagFlat'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:232:9( [780] >record 'AstTrackingAlternatives'<>) */>(m, "StdMapOfHashTagFlatAstTrackingAlternatives", type_registry_guard);
  org::bind::python::bind_hstdVec<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:38:35( [780] >record 'SequenceSegment'<>) */>(m, "HstdVecOfSequenceSegment", type_registry_guard);
  org::bind::python::bind_stdvector<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:38:35( [780] >record 'SequenceSegment'<>) */>(m, "StdVecOfSequenceSegment", type_registry_guard);
  org::bind::python::bind_hstdVec<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotationTag /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:79:41( [780] >record 'SequenceAnnotationTag'<>) */>(m, "HstdVecOfSequenceAnnotationTag", type_registry_guard);
  org::bind::python::bind_stdvector<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotationTag /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:79:41( [780] >record 'SequenceAnnotationTag'<>) */>(m, "StdVecOfSequenceAnnotationTag", type_registry_guard);
  org::bind::python::bind_hstdVec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmUniqId /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:25:49( [780] >record 'ImmUniqId'<>) */>(m, "HstdVecOfImmUniqId", type_registry_guard);
  org::bind::python::bind_stdvector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmUniqId /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:25:49( [780] >record 'ImmUniqId'<>) */>(m, "StdVecOfImmUniqId", type_registry_guard);
  org::bind::python::bind_hstdVec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:44:34( [780] >record 'MapLink'<>) */>(m, "HstdVecOfGraphMapLink", type_registry_guard);
  org::bind::python::bind_stdvector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:44:34( [780] >record 'MapLink'<>) */>(m, "StdVecOfGraphMapLink", type_registry_guard);
  org::bind::python::bind_hstdVec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:119:60( [780] >record 'MapNode'<>) */>(m, "HstdVecOfGraphMapNode", type_registry_guard);
  org::bind::python::bind_stdvector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:119:60( [780] >record 'MapNode'<>) */>(m, "StdVecOfGraphMapNode", type_registry_guard);
  org::bind::python::bind_hstdVec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:163:33( [780] >record 'MapEdge'<>) */>(m, "HstdVecOfGraphMapEdge", type_registry_guard);
  org::bind::python::bind_stdvector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:163:33( [780] >record 'MapEdge'<>) */>(m, "StdVecOfGraphMapEdge", type_registry_guard);
  org::bind::python::bind_hstdUnorderedMap<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:117:60( [780] >record 'MapNode'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:117:60( [780] >record 'MapNodeProp'<>) */>(m, "HstdMapOfGraphMapNodeGraphMapNodeProp", type_registry_guard);
  org::bind::python::bind_stdunordered_map<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:117:60( [780] >record 'MapNode'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:117:60( [780] >record 'MapNodeProp'<>) */>(m, "StdMapOfGraphMapNodeGraphMapNodeProp", type_registry_guard);
  org::bind::python::bind_hstdUnorderedMap<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:118:60( [780] >record 'MapEdge'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:118:60( [780] >record 'MapEdgeProp'<>) */>(m, "HstdMapOfGraphMapEdgeGraphMapEdgeProp", type_registry_guard);
  org::bind::python::bind_stdunordered_map<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:118:60( [780] >record 'MapEdge'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:118:60( [780] >record 'MapEdgeProp'<>) */>(m, "StdMapOfGraphMapEdgeGraphMapEdgeProp", type_registry_guard);
  org::bind::python::bind_hstdUnorderedMap<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:120:60( [780] >record 'MapNode'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::AdjNodesList /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:120:60( [735] typedef type imm/ImmOrgGraph.hpp:119:60) */>(m, "HstdMapOfGraphMapNodeGraphAdjNodesList", type_registry_guard);
  org::bind::python::bind_stdunordered_map<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:120:60( [780] >record 'MapNode'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::AdjNodesList /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:120:60( [735] typedef type imm/ImmOrgGraph.hpp:119:60) */>(m, "StdMapOfGraphMapNodeGraphAdjNodesList", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::LispCode>(m, "HstdVecOfLispCode", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::LispCode>(m, "StdVecOfLispCode", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::Tblfm::Assign>(m, "HstdVecOfTblfmAssign", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::Tblfm::Assign>(m, "StdVecOfTblfmAssign", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::Tblfm::Expr>(m, "HstdVecOfTblfmExpr", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::Tblfm::Expr>(m, "StdVecOfTblfmExpr", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::Tblfm::Assign::Flag>(m, "HstdVecOfTblfmAssignFlag", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::Tblfm::Assign::Flag>(m, "StdVecOfTblfmAssignFlag", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::AttrValue::DimensionSpan>(m, "HstdVecOfAttrValueDimensionSpan", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::AttrValue::DimensionSpan>(m, "StdVecOfAttrValueDimensionSpan", type_registry_guard);
  org::bind::python::bind_hstdVec<hstd::Str>(m, "HstdVecOfStr", type_registry_guard);
  org::bind::python::bind_stdvector<hstd::Str>(m, "StdVecOfStr", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::HashTagFlat>(m, "HstdVecOfHashTagFlat", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::HashTagFlat>(m, "StdVecOfHashTagFlat", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::HashTagText>(m, "HstdVecOfHashTagText", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::HashTagText>(m, "StdVecOfHashTagText", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::AttrValue>(m, "HstdVecOfAttrValue", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::AttrValue>(m, "StdVecOfAttrValue", type_registry_guard);
  org::bind::python::bind_hstdUnorderedMap<hstd::Str, org::sem::AttrList>(m, "HstdMapOfStrAttrList", type_registry_guard);
  org::bind::python::bind_stdunordered_map<hstd::Str, org::sem::AttrList>(m, "StdMapOfStrAttrList", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::OrgCodeEvalInput::Var>(m, "HstdVecOfOrgCodeEvalInputVar", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::OrgCodeEvalInput::Var>(m, "StdVecOfOrgCodeEvalInputVar", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::ColumnView::Column>(m, "HstdVecOfColumnViewColumn", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::ColumnView::Column>(m, "StdVecOfColumnViewColumn", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::BlockCodeLine::Part>(m, "HstdVecOfBlockCodeLinePart", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::BlockCodeLine::Part>(m, "StdVecOfBlockCodeLinePart", type_registry_guard);
  org::bind::python::bind_hstdUnorderedMap<hstd::Str, hstd::Str>(m, "HstdMapOfStrStr", type_registry_guard);
  org::bind::python::bind_stdunordered_map<hstd::Str, hstd::Str>(m, "StdMapOfStrStr", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::SemId<org::sem::ErrorItem>>(m, "HstdVecOfSemIdOfErrorItem", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::SemId<org::sem::ErrorItem>>(m, "StdVecOfSemIdOfErrorItem", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::Time::Repeat>(m, "HstdVecOfTimeRepeat", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::Time::Repeat>(m, "StdVecOfTimeRepeat", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::Symbol::Param>(m, "HstdVecOfSymbolParam", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::Symbol::Param>(m, "StdVecOfSymbolParam", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::SemId<org::sem::ErrorSkipToken>>(m, "HstdVecOfSemIdOfErrorSkipToken", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::SemId<org::sem::ErrorSkipToken>>(m, "StdVecOfSemIdOfErrorSkipToken", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::SubtreePeriod>(m, "HstdVecOfSubtreePeriod", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::SubtreePeriod>(m, "StdVecOfSubtreePeriod", type_registry_guard);
  org::bind::python::bind_hstdIntSet<org::sem::SubtreePeriod::Kind>(m, "IntSetOfSubtreePeriodKind", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::NamedProperty>(m, "HstdVecOfNamedProperty", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::NamedProperty>(m, "StdVecOfNamedProperty", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::SemId<org::sem::HashTag>>(m, "HstdVecOfSemIdOfHashTag", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::SemId<org::sem::HashTag>>(m, "StdVecOfSemIdOfHashTag", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::SemId<org::sem::SubtreeLog>>(m, "HstdVecOfSemIdOfSubtreeLog", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::SemId<org::sem::SubtreeLog>>(m, "StdVecOfSemIdOfSubtreeLog", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::TodoKeyword>(m, "HstdVecOfTodoKeyword", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::TodoKeyword>(m, "StdVecOfTodoKeyword", type_registry_guard);
  org::bind::python::bind_hstdextImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem /* imm_write */> /* imm_write */>(m, "ImmVecOfImmIdTOfImmErrorItem", type_registry_guard);
  org::bind::python::bind_hstdextImmVec<org::imm::ImmIdT<org::imm::ImmOrg /* imm_write */> /* imm_write */>(m, "ImmVecOfImmIdTOfImmOrg", type_registry_guard);
  org::bind::python::bind_hstdextImmBox<hstd::Str>(m, "ImmBoxOfStr", type_registry_guard);
  org::bind::python::bind_hstdextImmVec<org::imm::ImmTime::Repeat /* imm_write */>(m, "ImmVecOfImmTimeRepeat", type_registry_guard);
  org::bind::python::bind_hstdextImmBox<hstd::Opt<org::imm::ImmTime::Repeat /* imm_write */>>(m, "ImmBoxOfOptOfImmTimeRepeat", type_registry_guard);
  org::bind::python::bind_hstdextImmVec<org::imm::ImmSymbol::Param /* imm_write */>(m, "ImmVecOfImmSymbolParam", type_registry_guard);
  org::bind::python::bind_hstdextImmBox<hstd::Opt<hstd /* imm_write */::Str /* imm_write */>>(m, "ImmBoxOfOptOfStr", type_registry_guard);
  org::bind::python::bind_hstdextImmVec<org::imm::ImmIdT<org::imm::ImmErrorSkipToken /* imm_write */> /* imm_write */>(m, "ImmVecOfImmIdTOfImmErrorSkipToken", type_registry_guard);
  org::bind::python::bind_hstdextImmVec<hstd /* imm_write */::Str /* imm_write */>(m, "ImmVecOfStr", type_registry_guard);
  org::bind::python::bind_hstdextImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmStmtList /* imm_write */> /* imm_write */>>(m, "ImmBoxOfOptOfImmIdTOfImmStmtList", type_registry_guard);
  org::bind::python::bind_hstdextImmBox<hstd::Opt<org::sem::SubtreeCompletion>>(m, "ImmBoxOfOptOfSubtreeCompletion", type_registry_guard);
  org::bind::python::bind_hstdextImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph /* imm_write */> /* imm_write */>>(m, "ImmBoxOfOptOfImmIdTOfImmParagraph", type_registry_guard);
  org::bind::python::bind_hstdextImmVec<org::imm::ImmIdT<org::imm::ImmHashTag /* imm_write */> /* imm_write */>(m, "ImmVecOfImmIdTOfImmHashTag", type_registry_guard);
  org::bind::python::bind_hstdextImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog /* imm_write */> /* imm_write */>(m, "ImmVecOfImmIdTOfImmSubtreeLog", type_registry_guard);
  org::bind::python::bind_hstdextImmVec<org::sem::NamedProperty>(m, "ImmVecOfNamedProperty", type_registry_guard);
  org::bind::python::bind_hstdextImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime /* imm_write */> /* imm_write */>>(m, "ImmBoxOfOptOfImmIdTOfImmTime", type_registry_guard);
  org::bind::python::bind_hstdextImmBox<hstd::Opt<bool /* imm_write */>>(m, "ImmBoxOfOptOfBool", type_registry_guard);
  org::bind::python::bind_hstdextImmBox<hstd::Opt<int /* imm_write */>>(m, "ImmBoxOfOptOfInt", type_registry_guard);
  org::bind::python::bind_hstdextImmBox<hstd::Opt<org::sem::ColumnView>>(m, "ImmBoxOfOptOfColumnView", type_registry_guard);
  org::bind::python::bind_hstdextImmVec<org::sem::TodoKeyword>(m, "ImmVecOfTodoKeyword", type_registry_guard);
  org::bind::python::bind_hstdextImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmRawText /* imm_write */> /* imm_write */>>(m, "ImmBoxOfOptOfImmIdTOfImmRawText", type_registry_guard);
  org::bind::python::bind_hstdextImmBox<hstd::Opt<org::sem::SubtreePath>>(m, "ImmBoxOfOptOfSubtreePath", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::SemId<org::sem::BigIdent>>(m, "HstdVecOfSemIdOfBigIdent", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::SemId<org::sem::BigIdent>>(m, "StdVecOfSemIdOfBigIdent", type_registry_guard);
  org::bind::python::bind_hstdVec<hstd::UserTime>(m, "HstdVecOfUserTime", type_registry_guard);
  org::bind::python::bind_stdvector<hstd::UserTime>(m, "StdVecOfUserTime", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::SemId<org::sem::Time>>(m, "HstdVecOfSemIdOfTime", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::SemId<org::sem::Time>>(m, "StdVecOfSemIdOfTime", type_registry_guard);
  org::bind::python::bind_hstdextImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmOrg /* imm_write */> /* imm_write */>>(m, "ImmBoxOfOptOfImmIdTOfImmOrg", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::SemId<org::sem::Cell>>(m, "HstdVecOfSemIdOfCell", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::SemId<org::sem::Cell>>(m, "StdVecOfSemIdOfCell", type_registry_guard);
  org::bind::python::bind_hstdextImmVec<org::imm::ImmIdT<org::imm::ImmCell /* imm_write */> /* imm_write */>(m, "ImmVecOfImmIdTOfImmCell", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::OrgCodeEvalOutput>(m, "HstdVecOfOrgCodeEvalOutput", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::OrgCodeEvalOutput>(m, "StdVecOfOrgCodeEvalOutput", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::SemId<org::sem::BlockCodeEvalResult>>(m, "HstdVecOfSemIdOfBlockCodeEvalResult", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::SemId<org::sem::BlockCodeEvalResult>>(m, "StdVecOfSemIdOfBlockCodeEvalResult", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::BlockCodeLine>(m, "HstdVecOfBlockCodeLine", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::BlockCodeLine>(m, "StdVecOfBlockCodeLine", type_registry_guard);
  org::bind::python::bind_hstdVec<org::sem::SemId<org::sem::Row>>(m, "HstdVecOfSemIdOfRow", type_registry_guard);
  org::bind::python::bind_stdvector<org::sem::SemId<org::sem::Row>>(m, "StdVecOfSemIdOfRow", type_registry_guard);
  org::bind::python::bind_hstdextImmVec<org::sem::OrgCodeEvalOutput>(m, "ImmVecOfOrgCodeEvalOutput", type_registry_guard);
  org::bind::python::bind_hstdextImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult /* imm_write */> /* imm_write */>(m, "ImmVecOfImmIdTOfImmBlockCodeEvalResult", type_registry_guard);
  org::bind::python::bind_hstdextImmVec<org::sem::BlockCodeLine>(m, "ImmVecOfBlockCodeLine", type_registry_guard);
  org::bind::python::bind_hstdextImmVec<org::imm::ImmIdT<org::imm::ImmRow /* imm_write */> /* imm_write */>(m, "ImmVecOfImmIdTOfImmRow", type_registry_guard);
  org::bind::python::bind_hstdVec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [640]Type parameter [905]api/SemBaseApi.hpp:268:38( [780] >record 'AstTrackingGroup'<>) */>(m, "HstdVecOfAstTrackingGroup", type_registry_guard);
  org::bind::python::bind_stdvector<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [640]Type parameter [905]api/SemBaseApi.hpp:268:38( [780] >record 'AstTrackingGroup'<>) */>(m, "StdVecOfAstTrackingGroup", type_registry_guard);
  org::bind::python::bind_hstdVec<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:93:34( [780] >record 'SequenceAnnotation'<>) */>(m, "HstdVecOfSequenceAnnotation", type_registry_guard);
  org::bind::python::bind_stdvector<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:93:34( [780] >record 'SequenceAnnotation'<>) */>(m, "StdVecOfSequenceAnnotation", type_registry_guard);
  org::bind::python::bind_hstdVec<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:94:38( [780] >record 'SequenceSegmentGroup'<>) */>(m, "HstdVecOfSequenceSegmentGroup", type_registry_guard);
  org::bind::python::bind_stdvector<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:94:38( [780] >record 'SequenceSegmentGroup'<>) */>(m, "StdVecOfSequenceSegmentGroup", type_registry_guard);
  nanobind::class_<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */>(m, "UserTimeBreakdown")
    .def("__init__",
         [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown* /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("year", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */::year)
    .def_rw("month", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */::month)
    .def_rw("day", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */::day)
    .def_rw("hour", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */::hour)
    .def_rw("minute", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */::minute)
    .def_rw("second", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */::second)
    .def_rw("zone", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */::zone)
    .def("__repr__", [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown const& /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown const& /*  [905]stdlib/Time.hpp:15:17( [780] >record 'UserTimeBreakdown'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */>(m, "UserTime")
    .def("__init__",
         [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime* /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getBreakdown", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown /*  [905]stdlib/Time.hpp:50:32( [780] >record 'UserTimeBreakdown'<>) */(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */::*)() const>(&hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */::getBreakdown))
    .def("format", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]stdlib/Time.hpp:51:32( [735] typedef type bits/stringfwd.h:79:33) */(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */::*)() const>(&hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */::format))
    .def("getTimeDeltaSeconds",
         static_cast<int64_t /*  [905]stdlib/Time.hpp:56:22( [735] typedef type bits/stdint-intn.h:27:19) */(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */::*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime const& /*  [905]stdlib/Time.hpp:56:58( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'UserTime'<>)<>) */) const>(&hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */::getTimeDeltaSeconds),
         nanobind::arg("other"))
    .def("toUnixTimestamp", static_cast<int64_t /*  [905]stdlib/Time.hpp:57:22( [735] typedef type bits/stdint-intn.h:27:19) */(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */::*)() const>(&hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */::toUnixTimestamp))
    .def("__repr__", [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime const& /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTime const& /*  [905]stdlib/Time.hpp:41:17( [780] >record 'UserTime'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceFileId /*  [905]lexbase/SourceManager.hpp:9:1( [780] >record 'SourceFileId'<>) */>(m, "ParseSourceFileId")
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceFileId const& /*  [905]lexbase/SourceManager.hpp:9:1( [780] >record 'SourceFileId'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceFileId const& /*  [905]lexbase/SourceManager.hpp:9:1( [780] >record 'SourceFileId'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceLoc /*  [905]lexbase/SourceManager.hpp:41:17( [780] >record 'SourceLoc'<>) */>(m, "ParseSourceLoc")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceLoc* /*  [905]lexbase/SourceManager.hpp:41:17( [780] >record 'SourceLoc'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceLoc /*  [905]lexbase/SourceManager.hpp:41:17( [780] >record 'SourceLoc'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("line", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceLoc /*  [905]lexbase/SourceManager.hpp:41:17( [780] >record 'SourceLoc'<>) */::line)
    .def_rw("column", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceLoc /*  [905]lexbase/SourceManager.hpp:41:17( [780] >record 'SourceLoc'<>) */::column)
    .def_rw("pos", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceLoc /*  [905]lexbase/SourceManager.hpp:41:17( [780] >record 'SourceLoc'<>) */::pos)
    .def_rw("file_id", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceLoc /*  [905]lexbase/SourceManager.hpp:41:17( [780] >record 'SourceLoc'<>) */::file_id)
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceLoc const& /*  [905]lexbase/SourceManager.hpp:41:17( [780] >record 'SourceLoc'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceLoc const& /*  [905]lexbase/SourceManager.hpp:41:17( [780] >record 'SourceLoc'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */>(m, "OrgJson")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson* /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getKind", static_cast<OrgJsonKind /*  [905]sem/SemOrgBaseSharedTypes.hpp:26:26( [786] >enum 'OrgJsonKind'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::getKind))
    .def("getJsonString", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]sem/SemOrgBaseSharedTypes.hpp:40:26( [735] typedef type bits/stringfwd.h:79:33) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::getJsonString))
    .def("at",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:41:55( [780] >record 'OrgJson'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)(int /*  [905]sem/SemOrgBaseSharedTypes.hpp:41:62( [766] >builtin/unqual<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::at),
         nanobind::arg("idx"))
    .def("at",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:42:55( [780] >record 'OrgJson'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]sem/SemOrgBaseSharedTypes.hpp:43:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::at),
         nanobind::arg("name"))
    .def("getString", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]sem/SemOrgBaseSharedTypes.hpp:44:33( [735] typedef type bits/stringfwd.h:79:33) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::getString))
    .def("getField",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:45:33( [780] >record 'OrgJson'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]sem/SemOrgBaseSharedTypes.hpp:45:61( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::getField),
         nanobind::arg("name"))
    .def("getItem",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:46:33( [780] >record 'OrgJson'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)(int /*  [905]sem/SemOrgBaseSharedTypes.hpp:46:45( [766] >builtin/unqual<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::getItem),
         nanobind::arg("index"))
    .def("getInt", static_cast<int /*  [905]sem/SemOrgBaseSharedTypes.hpp:47:33( [766] >builtin/unqual<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::getInt))
    .def("getBool", static_cast<bool /*  [905]sem/SemOrgBaseSharedTypes.hpp:48:33( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::getBool))
    .def("getArray", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [640]Type parameter [905]sem/SemOrgBaseSharedTypes.hpp:49:33( [780] >record 'OrgJson'<>) */> /*  [905]sem/SemOrgBaseSharedTypes.hpp:49:33( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::getArray))
    .def("dump",
         static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]sem/SemOrgBaseSharedTypes.hpp:50:33( [735] typedef type bits/stringfwd.h:79:33) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::*)(int /*  [905]sem/SemOrgBaseSharedTypes.hpp:50:42( [766] >builtin/unqual<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */::dump),
         nanobind::arg("indent"))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson const& /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgJson const& /*  [905]sem/SemOrgBaseSharedTypes.hpp:20:17( [780] >record 'OrgJson'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */>(m, "Org")
    .def_rw("loc", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::loc, R"RAW(\brief Location of the node in the original source file)RAW")
    .def_rw("subnodes", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::subnodes, R"RAW(\brief List of subnodes.

Some of the derived nodes don't make the use of subnode list
(word, punctuation etc), but it was left on the top level of the
hierarchy for conveinience purposes. It is not expected that 'any'
node can have subnodes.)RAW")
    .def("getKind", static_cast<OrgSemKind /*  [905]sem/SemOrgBase.hpp:224:33( [786] >enum 'OrgSemKind'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::getKind), R"RAW(\brief Get kind of this sem node)RAW")
    .def("push_back",
         static_cast<void /*  [905]sem/SemOrgBase.hpp:235:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]sem/SemOrgBase.hpp:235:40( [780] >record 'Org'<>) */> /*  [905]sem/SemOrgBase.hpp:235:40( [780] >record 'SemId'< [657] templates: template-specialization-type>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::push_back),
         nanobind::arg("sub"))
    .def("size", static_cast<int /*  [905]sem/SemOrgBase.hpp:244:18( [766] >builtin/unqual<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::size))
    .def("insert",
         static_cast<void /*  [905]sem/SemOrgBase.hpp:246:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::*)(int /*  [905]sem/SemOrgBase.hpp:246:30( [766] >builtin/unqual<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]sem/SemOrgBase.hpp:246:46( [780] >record 'Org'<>) */> /*  [905]sem/SemOrgBase.hpp:246:46( [780] >record 'SemId'< [657] templates: template-specialization-type>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::insert),
         nanobind::arg("pos"),
         nanobind::arg("node"))
    .def("at",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]sem/SemOrgBase.hpp:261:77( [780] >record 'Org'<>) */> /*  [905]sem/SemOrgBase.hpp:261:77( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::*)(int /*  [905]sem/SemOrgBase.hpp:262:13( [766] >builtin/unqual<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::at),
         nanobind::arg("idx"))
    .def("is_",
         static_cast<bool /*  [905]sem/SemOrgBase.hpp:306:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::*)(OrgSemKind /*  [905]sem/SemOrgBase.hpp:306:33( [786] >enum 'OrgSemKind'<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::is),
         nanobind::arg("kind"))
    .def("__getitem__",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]sem/SemOrgBase.hpp:261:77( [780] >record 'Org'<>) */> /*  [905]sem/SemOrgBase.hpp:261:77( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::*)(int /*  [905]sem/SemOrgBase.hpp:262:13( [766] >builtin/unqual<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */::at),
         nanobind::arg("idx"))
    .def("__iter__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org const& /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */ node) -> auto {
         return nanobind::make_iterator(nanobind::type<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [905]sem/SemOrgBase.hpp:213:8( [780] >record 'Org'<>) */>(), "Org__iter__", node.begin(), node.end());
         },
         nanobind::keep_alive<0, 1>())
    ;
  nanobind::class_<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */>(m, "OperationsTracer")
    .def("__init__",
         [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer* /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("TraceState", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::TraceState)
    .def_rw("traceToFile", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::traceToFile)
    .def_rw("traceToBuffer", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::traceToBuffer)
    .def_rw("traceStructured", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::traceStructured)
    .def_rw("traceColored", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::traceColored)
    .def_rw("activeLevel", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::activeLevel)
    .def_rw("traceBuffer", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::traceBuffer)
    .def("setTraceFileStr",
         static_cast<void /*  [905]stdlib/TraceBase.hpp:72:19(<>) */(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]stdlib/TraceBase.hpp:73:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, bool /*  [905]stdlib/TraceBase.hpp:74:28( [755] >bool<>) */)>(&hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::setTraceFileStr),
         nanobind::arg("outfile"),
         nanobind::arg("overwrite"),
         R"RAW(\brief Helper method for reflection)RAW")
    .def("sendMessage",
         static_cast<void /*  [905]stdlib/TraceBase.hpp:78:19(<>) */(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]stdlib/TraceBase.hpp:79:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]stdlib/TraceBase.hpp:80:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, int /*  [905]stdlib/TraceBase.hpp:81:28( [766] >builtin/unqual<>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]stdlib/TraceBase.hpp:82:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */)>(&hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */::sendMessage),
         nanobind::arg("value"),
         nanobind::arg("function"),
         nanobind::arg("line"),
         nanobind::arg("file"))
    .def("__repr__", [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer const& /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OperationsTracer const& /*  [905]stdlib/TraceBase.hpp:31:17( [780] >record 'OperationsTracer'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ext /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Cache /*  [905]ext/error_write.hpp:69:16( [780] >record 'Cache'<>) */>(m, "Cache")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseFragment /*  [905]api/ParseContext.hpp:14:17( [780] >record 'OrgParseFragment'<>) */>(m, "ParseOrgParseFragment")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseFragment* /*  [905]api/ParseContext.hpp:14:17( [780] >record 'OrgParseFragment'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseFragment /*  [905]api/ParseContext.hpp:14:17( [780] >record 'OrgParseFragment'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("baseLine", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseFragment /*  [905]api/ParseContext.hpp:14:17( [780] >record 'OrgParseFragment'<>) */::baseLine)
    .def_rw("baseCol", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseFragment /*  [905]api/ParseContext.hpp:14:17( [780] >record 'OrgParseFragment'<>) */::baseCol)
    .def_rw("text", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseFragment /*  [905]api/ParseContext.hpp:14:17( [780] >record 'OrgParseFragment'<>) */::text)
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseFragment const& /*  [905]api/ParseContext.hpp:14:17( [780] >record 'OrgParseFragment'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseFragment const& /*  [905]api/ParseContext.hpp:14:17( [780] >record 'OrgParseFragment'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [905]api/ParseContext.hpp:37:8( [780] >record 'OrgParseParameters'<>) */>(m, "OrgParseParameters")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters* /*  [905]api/ParseContext.hpp:37:8( [780] >record 'OrgParseParameters'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [905]api/ParseContext.hpp:37:8( [780] >record 'OrgParseParameters'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("baseTokenTracePath", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [905]api/ParseContext.hpp:37:8( [780] >record 'OrgParseParameters'<>) */::baseTokenTracePath)
    .def_rw("tokenTracePath", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [905]api/ParseContext.hpp:37:8( [780] >record 'OrgParseParameters'<>) */::tokenTracePath)
    .def_rw("parseTracePath", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [905]api/ParseContext.hpp:37:8( [780] >record 'OrgParseParameters'<>) */::parseTracePath)
    .def_rw("semTracePath", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [905]api/ParseContext.hpp:37:8( [780] >record 'OrgParseParameters'<>) */::semTracePath)
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters const& /*  [905]api/ParseContext.hpp:37:8( [780] >record 'OrgParseParameters'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters const& /*  [905]api/ParseContext.hpp:37:8( [780] >record 'OrgParseParameters'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgDirectoryParseParameters /*  [905]api/ParseContext.hpp:64:8( [780] >record 'OrgDirectoryParseParameters'<>) */>(m, "OrgDirectoryParseParameters")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgDirectoryParseParameters* /*  [905]api/ParseContext.hpp:64:8( [780] >record 'OrgDirectoryParseParameters'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgDirectoryParseParameters /*  [905]api/ParseContext.hpp:64:8( [780] >record 'OrgDirectoryParseParameters'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgDirectoryParseParameters const& /*  [905]api/ParseContext.hpp:64:8( [780] >record 'OrgDirectoryParseParameters'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgDirectoryParseParameters const& /*  [905]api/ParseContext.hpp:64:8( [780] >record 'OrgDirectoryParseParameters'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */>(m, "ParseContext")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext* /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getDiagnosticStrings", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ext /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Cache /*  [640]Type parameter [905]api/ParseContext.hpp:110:48( [780] >record 'Cache'<>) */> /*  [905]api/ParseContext.hpp:110:48( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)()>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::getDiagnosticStrings))
    .def("addSource",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SourceFileId /*  [905]api/ParseContext.hpp:112:27( [780] >record 'SourceFileId'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:113:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:114:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::addSource),
         nanobind::arg("path"),
         nanobind::arg("content"))
    .def("parseFileOpts",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:116:35( [780] >record 'Org'<>) */> /*  [905]api/ParseContext.hpp:116:35( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:117:52( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [640]Type parameter [905]api/ParseContext.hpp:118:52( [780] >record 'OrgParseParameters'<>) */> const& /*  [905]api/ParseContext.hpp:118:52( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::parseFileOpts),
         nanobind::arg("file"),
         nanobind::arg("opts"))
    .def("parseFile",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:120:35( [780] >record 'Org'<>) */> /*  [905]api/ParseContext.hpp:120:35( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:120:64( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::parseFile),
         nanobind::arg("file"))
    .def("parseString",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:122:35( [780] >record 'Org'<>) */> /*  [905]api/ParseContext.hpp:122:35( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:123:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:124:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::parseString),
         nanobind::arg("text"),
         nanobind::arg("file_name"))
    .def("parseStringOpts",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:126:35( [780] >record 'Org'<>) */> /*  [905]api/ParseContext.hpp:126:35( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const /*  [905]api/ParseContext.hpp:127:52( [707] T-const [735] typedef type bits/stringfwd.h:79:33) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:128:52( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgParseParameters /*  [640]Type parameter [905]api/ParseContext.hpp:129:52( [780] >record 'OrgParseParameters'<>) */> const& /*  [905]api/ParseContext.hpp:129:52( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::parseStringOpts),
         nanobind::arg("text"),
         nanobind::arg("file_name"),
         nanobind::arg("opts"))
    .def("parseDirectory",
         static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:131:46( [780] >record 'Org'<>) */> /*  [640]Type parameter [905]api/ParseContext.hpp:131:46( [780] >record 'SemId'< [657] templates: template-specialization-type>) */> /*  [905]api/ParseContext.hpp:131:46( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:132:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::parseDirectory),
         nanobind::arg("path"))
    .def("parseDirectoryOpts",
         static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:134:46( [780] >record 'Org'<>) */> /*  [640]Type parameter [905]api/ParseContext.hpp:134:46( [780] >record 'SemId'< [657] templates: template-specialization-type>) */> /*  [905]api/ParseContext.hpp:134:46( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:135:61( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgDirectoryParseParameters /*  [640]Type parameter [905]api/ParseContext.hpp:136:61( [780] >record 'OrgDirectoryParseParameters'<>) */> const& /*  [905]api/ParseContext.hpp:136:61( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::parseDirectoryOpts),
         nanobind::arg("path"),
         nanobind::arg("opts"))
    .def("parseFileWithIncludes",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::File /*  [640]Type parameter [905]api/ParseContext.hpp:138:36( [780] >record 'File'<>) */> /*  [905]api/ParseContext.hpp:138:36( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/ParseContext.hpp:139:61( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgDirectoryParseParameters /*  [640]Type parameter [905]api/ParseContext.hpp:140:61( [780] >record 'OrgDirectoryParseParameters'<>) */> const& /*  [905]api/ParseContext.hpp:140:61( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::parseFileWithIncludes),
         nanobind::arg("file"),
         nanobind::arg("opts"))
    .def("collectDiagnostics",
         static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ext /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Report /*  [640]Type parameter [905]api/ParseContext.hpp:142:43( [780] >record 'Report'<>) */> /*  [905]api/ParseContext.hpp:142:43( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:143:50( [780] >record 'Org'<>) */> const& /*  [905]api/ParseContext.hpp:143:50( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ext /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Cache /*  [640]Type parameter [905]api/ParseContext.hpp:144:50( [780] >record 'Cache'<>) */> const& /*  [905]api/ParseContext.hpp:144:50( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::collectDiagnostics),
         nanobind::arg("tree"),
         nanobind::arg("cache"))
    .def("collectErrorNodes",
         static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ErrorGroup /*  [640]Type parameter [905]api/ParseContext.hpp:146:53( [780] >record 'ErrorGroup'<>) */> /*  [640]Type parameter [905]api/ParseContext.hpp:146:53( [780] >record 'SemId'< [657] templates: template-specialization-type>) */> /*  [905]api/ParseContext.hpp:146:53( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/ParseContext.hpp:147:47( [780] >record 'Org'<>) */> const& /*  [905]api/ParseContext.hpp:147:47( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */::collectErrorNodes),
         nanobind::arg("tree"))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext const& /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext const& /*  [905]api/ParseContext.hpp:102:8( [780] >record 'ParseContext'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmReflFieldId /*  [905]imm/ImmOrgBase.hpp:37:17( [780] >record 'ImmReflFieldId'<>) */>(m, "ImmReflFieldId")
    .def("getName", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str /*  [905]imm/ImmOrgBase.hpp:38:24( [780] >record 'Str'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmReflFieldId /*  [905]imm/ImmOrgBase.hpp:37:17( [780] >record 'ImmReflFieldId'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmReflFieldId /*  [905]imm/ImmOrgBase.hpp:37:17( [780] >record 'ImmReflFieldId'<>) */::getName))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */>(m, "ImmId")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId* /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getKind", static_cast<OrgSemKind /*  [905]imm/ImmOrgBase.hpp:293:25( [786] >enum 'OrgSemKind'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */::getKind))
    .def("is_",
         static_cast<bool /*  [905]imm/ImmOrgBase.hpp:294:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */::*)(OrgSemKind /*  [905]imm/ImmOrgBase.hpp:294:33( [786] >enum 'OrgSemKind'<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */::is),
         nanobind::arg("kind"))
    .def("getNodeIndex", static_cast<org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmId /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [550]type namespace @[0]' */::NodeIdxT /*  [905]imm/ImmOrgBase.hpp:298:23( [735] typedef type imm/ImmOrgBase.hpp:263:11) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */::getNodeIndex), R"RAW(\brief Get index of the node in associated kind store. NOTE: The
node must not be nil)RAW")
    .def("getReadableId", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]imm/ImmOrgBase.hpp:321:26( [735] typedef type bits/stringfwd.h:79:33) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */::getReadableId))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId const& /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId const& /*  [905]imm/ImmOrgBase.hpp:260:17( [780] >record 'ImmId'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmOrg /*  [905]imm/ImmOrgBase.hpp:352:17( [780] >record 'ImmOrg'<>) */>(m, "ImmOrg")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPathStep /*  [905]imm/ImmOrg.hpp:96:17( [780] >record 'ImmPathStep'<>) */>(m, "ImmPathStep")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPathStep* /*  [905]imm/ImmOrg.hpp:96:17( [780] >record 'ImmPathStep'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPathStep /*  [905]imm/ImmOrg.hpp:96:17( [780] >record 'ImmPathStep'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPathStep const& /*  [905]imm/ImmOrg.hpp:96:17( [780] >record 'ImmPathStep'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPathStep const& /*  [905]imm/ImmOrg.hpp:96:17( [780] >record 'ImmPathStep'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPath /*  [905]imm/ImmOrg.hpp:147:17( [780] >record 'ImmPath'<>) */>(m, "ImmPath")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPath* /*  [905]imm/ImmOrg.hpp:147:17( [780] >record 'ImmPath'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPath /*  [905]imm/ImmOrg.hpp:147:17( [780] >record 'ImmPath'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("root", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPath /*  [905]imm/ImmOrg.hpp:147:17( [780] >record 'ImmPath'<>) */::root, R"RAW(\brief Root ID node)RAW")
    .def_rw("path", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPath /*  [905]imm/ImmOrg.hpp:147:17( [780] >record 'ImmPath'<>) */::path, R"RAW(\brief Sequence of jumps from the root of the document down to the
specified target node. For the path iteration structure see \see
ImmPathStep documentation.)RAW")
    .def("empty", static_cast<bool /*  [905]imm/ImmOrg.hpp:160:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPath /*  [905]imm/ImmOrg.hpp:147:17( [780] >record 'ImmPath'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPath /*  [905]imm/ImmOrg.hpp:147:17( [780] >record 'ImmPath'<>) */::empty), R"RAW(\brief Empty path refers to the root of the document)RAW")
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPath const& /*  [905]imm/ImmOrg.hpp:147:17( [780] >record 'ImmPath'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPath const& /*  [905]imm/ImmOrg.hpp:147:17( [780] >record 'ImmPath'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmUniqId /*  [905]imm/ImmOrg.hpp:243:17( [780] >record 'ImmUniqId'<>) */>(m, "ImmUniqId")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmUniqId* /*  [905]imm/ImmOrg.hpp:243:17( [780] >record 'ImmUniqId'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmUniqId /*  [905]imm/ImmOrg.hpp:243:17( [780] >record 'ImmUniqId'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmUniqId const& /*  [905]imm/ImmOrg.hpp:243:17( [780] >record 'ImmUniqId'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmUniqId const& /*  [905]imm/ImmOrg.hpp:243:17( [780] >record 'ImmUniqId'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstReplaceEpoch /*  [905]imm/ImmOrg.hpp:506:8( [780] >record 'ImmAstReplaceEpoch'<>) */>(m, "ImmAstReplaceEpoch")
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstReplaceEpoch const& /*  [905]imm/ImmOrg.hpp:506:8( [780] >record 'ImmAstReplaceEpoch'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstReplaceEpoch const& /*  [905]imm/ImmOrg.hpp:506:8( [780] >record 'ImmAstReplaceEpoch'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */>(m, "ImmAstContext")
    .def("addRoot",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:663:28( [780] >record 'ImmAstVersion'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]imm/ImmOrg.hpp:663:57( [780] >record 'Org'<>) */> /*  [905]imm/ImmOrg.hpp:663:57( [780] >record 'SemId'< [657] templates: template-specialization-type>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */::addRoot),
         nanobind::arg("data"),
         R"RAW(\brief Add new root node to the store, create a new AST version
with a new root, new epoch and new AST context tracking the updated
state of the tree.)RAW")
    .def("getEmptyVersion", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:666:28( [780] >record 'ImmAstVersion'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */::*)()>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */::getEmptyVersion), R"RAW(\brief Create empty AST version with no edits, no root, and linked
to the current context.)RAW")
    .def("get",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]imm/ImmOrg.hpp:675:35( [780] >record 'Org'<>) */> /*  [905]imm/ImmOrg.hpp:675:35( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrg.hpp:675:55( [780] >record 'ImmId'<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */::get),
         nanobind::arg("id"),
         R"RAW(\brief Convert immutable AST tree to the sem AST -- the sem AST is
created anew following the immutable ID structure.)RAW")
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext const& /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext const& /*  [905]imm/ImmOrg.hpp:612:8( [780] >record 'ImmAstContext'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */>(m, "ImmAstVersion")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion* /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getRoot", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrg.hpp:748:25( [780] >record 'ImmId'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */::getRoot))
    .def("getRootAdapter", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:749:25( [780] >record 'ImmAdapter'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */::getRootAdapter))
    .def("getContext", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]imm/ImmOrg.hpp:751:45( [780] >record 'ImmAstContext'<>) */> /*  [905]imm/ImmOrg.hpp:751:45( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */::getContext))
    .def("getEpoch", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstReplaceEpoch /*  [640]Type parameter [905]imm/ImmOrg.hpp:755:50( [780] >record 'ImmAstReplaceEpoch'<>) */> /*  [905]imm/ImmOrg.hpp:755:50( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */::getEpoch))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion const& /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstVersion const& /*  [905]imm/ImmOrg.hpp:743:17( [780] >record 'ImmAstVersion'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmAdapter /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::TreeReprConf /*  [905]imm/ImmOrg.hpp:972:21( [780] >record 'TreeReprConf'<>) */>(m, "ImmAdapterTreeReprConf")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmAdapter /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::TreeReprConf* /*  [905]imm/ImmOrg.hpp:972:21( [780] >record 'TreeReprConf'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmAdapter /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::TreeReprConf /*  [905]imm/ImmOrg.hpp:972:21( [780] >record 'TreeReprConf'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("maxDepth", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmAdapter /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::TreeReprConf /*  [905]imm/ImmOrg.hpp:972:21( [780] >record 'TreeReprConf'<>) */::maxDepth, R"RAW(\brief Do not print nodes that are more than N levels deep from
the root)RAW")
    .def_rw("withAuxFields", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmAdapter /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::TreeReprConf /*  [905]imm/ImmOrg.hpp:972:21( [780] >record 'TreeReprConf'<>) */::withAuxFields, R"RAW(\brief Include auxiliary subnodes in the tree repr -- `.title`
field and other locations outside of standard `.subnodes`)RAW")
    .def_rw("withReflFields", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmAdapter /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::TreeReprConf /*  [905]imm/ImmOrg.hpp:972:21( [780] >record 'TreeReprConf'<>) */::withReflFields, R"RAW(\brief Format full immutable node value as a part of tree repr)RAW")
    .def_rw("withFieldSubset", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmAdapter /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::TreeReprConf /*  [905]imm/ImmOrg.hpp:972:21( [780] >record 'TreeReprConf'<>) */::withFieldSubset, R"RAW(\brief Profide extra pretty-printed information for a given
field subset.)RAW")
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmAdapter /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::TreeReprConf const& /*  [905]imm/ImmOrg.hpp:972:21( [780] >record 'TreeReprConf'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmAdapter /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::TreeReprConf const& /*  [905]imm/ImmOrg.hpp:972:21( [780] >record 'TreeReprConf'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */>(m, "ImmAdapter")
    .def("size", static_cast<int /*  [905]imm/ImmOrg.hpp:908:18( [766] >builtin/unqual<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::size))
    .def("isNil", static_cast<bool /*  [905]imm/ImmOrg.hpp:914:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::isNil))
    .def("isRoot", static_cast<bool /*  [905]imm/ImmOrg.hpp:915:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::isRoot))
    .def("getKind", static_cast<OrgSemKind /*  [905]imm/ImmOrg.hpp:931:25( [786] >enum 'OrgSemKind'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::getKind))
    .def("uniq", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmUniqId /*  [905]imm/ImmOrg.hpp:967:24( [780] >record 'ImmUniqId'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::uniq))
    .def("treeReprString", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]imm/ImmOrg.hpp:1008:26( [735] typedef type bits/stringfwd.h:79:33) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::treeReprString))
    .def("treeReprStringOpts",
         static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]imm/ImmOrg.hpp:1012:26( [735] typedef type bits/stringfwd.h:79:33) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::ImmAdapter /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::TreeReprConf const& /*  [905]imm/ImmOrg.hpp:1013:29( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'TreeReprConf'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::treeReprStringOpts),
         nanobind::arg("conf"))
    .def("isDirectParentOf",
         static_cast<bool /*  [905]imm/ImmOrg.hpp:1023:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter const& /*  [905]imm/ImmOrg.hpp:1023:54( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmAdapter'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::isDirectParentOf),
         nanobind::arg("other"))
    .def("isIndirectParentOf",
         static_cast<bool /*  [905]imm/ImmOrg.hpp:1025:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter const& /*  [905]imm/ImmOrg.hpp:1025:56( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmAdapter'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::isIndirectParentOf),
         nanobind::arg("other"))
    .def("isSubnodeOf",
         static_cast<bool /*  [905]imm/ImmOrg.hpp:1027:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter const& /*  [905]imm/ImmOrg.hpp:1027:49( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmAdapter'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::isSubnodeOf),
         nanobind::arg("other"))
    .def("getParent", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [640]Type parameter [905]imm/ImmOrg.hpp:1031:36( [780] >record 'ImmAdapter'<>) */> /*  [905]imm/ImmOrg.hpp:1031:36( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::getParent))
    .def("getSelfIndex", static_cast<int /*  [905]imm/ImmOrg.hpp:1041:18( [766] >builtin/unqual<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::getSelfIndex))
    .def("at",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:1089:61( [780] >record 'ImmAdapter'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmId /*  [905]imm/ImmOrg.hpp:1090:21( [780] >record 'ImmId'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmPathStep /*  [905]imm/ImmOrg.hpp:1091:21( [780] >record 'ImmPathStep'<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::at),
         nanobind::arg("id"),
         nanobind::arg("idx"))
    .def("at",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:1095:58( [780] >record 'ImmAdapter'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmReflFieldId const& /*  [905]imm/ImmOrg.hpp:1096:31( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmReflFieldId'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::at),
         nanobind::arg("field"))
    .def("at",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:1105:58( [780] >record 'ImmAdapter'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(int /*  [905]imm/ImmOrg.hpp:1106:14( [766] >builtin/unqual<>) */, bool /*  [905]imm/ImmOrg.hpp:1107:14( [755] >bool<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::at),
         nanobind::arg("idx"),
         nanobind::arg("withPath") = true)
    .def("at",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:1109:57( [780] >record 'ImmAdapter'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<int /*  [640]Type parameter [905]imm/ImmOrg.hpp:1110:31( [766] >builtin/unqual<>) */> const& /*  [905]imm/ImmOrg.hpp:1110:31( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Vec'< [657] templates: template-specialization-type>)<>) */, bool /*  [905]imm/ImmOrg.hpp:1111:31( [755] >bool<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::at),
         nanobind::arg("path"),
         nanobind::arg("withPath") = true)
    .def("is_",
         static_cast<bool /*  [905]imm/ImmOrg.hpp:1117:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(OrgSemKind /*  [905]imm/ImmOrg.hpp:1117:33( [786] >enum 'OrgSemKind'<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::is),
         nanobind::arg("kind"))
    .def("sub",
         static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [640]Type parameter [905]imm/ImmOrg.hpp:1119:36( [780] >record 'ImmAdapter'<>) */> /*  [905]imm/ImmOrg.hpp:1119:36( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::*)(bool /*  [905]imm/ImmOrg.hpp:1119:45( [755] >bool<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */::sub),
         nanobind::arg("withPath") = true)
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter const& /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter const& /*  [905]imm/ImmOrg.hpp:866:54( [780] >record 'ImmAdapter'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterVirtualBase /*  [905]imm/ImmOrg.hpp:1306:17( [780] >record 'ImmAdapterVirtualBase'<>) */>(m, "ImmAdapterVirtualBase")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts /*  [905]api/SemBaseApi.hpp:30:17( [780] >record 'OrgYamlExportOpts'<>) */>(m, "OrgYamlExportOpts")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts* /*  [905]api/SemBaseApi.hpp:30:17( [780] >record 'OrgYamlExportOpts'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts /*  [905]api/SemBaseApi.hpp:30:17( [780] >record 'OrgYamlExportOpts'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("skipNullFields", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts /*  [905]api/SemBaseApi.hpp:30:17( [780] >record 'OrgYamlExportOpts'<>) */::skipNullFields)
    .def_rw("skipFalseFields", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts /*  [905]api/SemBaseApi.hpp:30:17( [780] >record 'OrgYamlExportOpts'<>) */::skipFalseFields)
    .def_rw("skipZeroFields", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts /*  [905]api/SemBaseApi.hpp:30:17( [780] >record 'OrgYamlExportOpts'<>) */::skipZeroFields)
    .def_rw("skipLocation", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts /*  [905]api/SemBaseApi.hpp:30:17( [780] >record 'OrgYamlExportOpts'<>) */::skipLocation)
    .def_rw("skipId", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts /*  [905]api/SemBaseApi.hpp:30:17( [780] >record 'OrgYamlExportOpts'<>) */::skipId)
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts const& /*  [905]api/SemBaseApi.hpp:30:17( [780] >record 'OrgYamlExportOpts'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts const& /*  [905]api/SemBaseApi.hpp:30:17( [780] >record 'OrgYamlExportOpts'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */>(m, "OrgTreeExportOpts")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts* /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("withLineCol", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */::withLineCol)
    .def_rw("withOriginalId", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */::withOriginalId)
    .def_rw("withSubnodeIdx", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */::withSubnodeIdx)
    .def_rw("skipEmptyFields", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */::skipEmptyFields)
    .def_rw("startLevel", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */::startLevel)
    .def_rw("withColor", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */::withColor)
    .def_rw("maxDepth", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */::maxDepth)
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts const& /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts const& /*  [905]api/SemBaseApi.hpp:69:17( [780] >record 'OrgTreeExportOpts'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [905]api/SemBaseApi.hpp:102:17( [780] >record 'AstTrackingPath'<>) */>(m, "AstTrackingPath")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath* /*  [905]api/SemBaseApi.hpp:102:17( [780] >record 'AstTrackingPath'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [905]api/SemBaseApi.hpp:102:17( [780] >record 'AstTrackingPath'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("path", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [905]api/SemBaseApi.hpp:102:17( [780] >record 'AstTrackingPath'<>) */::path)
    .def("getParent",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:106:45( [780] >record 'Org'<>) */> /*  [905]api/SemBaseApi.hpp:106:45( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [905]api/SemBaseApi.hpp:102:17( [780] >record 'AstTrackingPath'<>) */::*)(int /*  [905]api/SemBaseApi.hpp:107:13( [766] >builtin/unqual<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [905]api/SemBaseApi.hpp:102:17( [780] >record 'AstTrackingPath'<>) */::getParent),
         nanobind::arg("offset") = 0)
    .def("getNode", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:119:35( [780] >record 'Org'<>) */> /*  [905]api/SemBaseApi.hpp:119:35( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [905]api/SemBaseApi.hpp:102:17( [780] >record 'AstTrackingPath'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath /*  [905]api/SemBaseApi.hpp:102:17( [780] >record 'AstTrackingPath'<>) */::getNode))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath const& /*  [905]api/SemBaseApi.hpp:102:17( [780] >record 'AstTrackingPath'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingPath const& /*  [905]api/SemBaseApi.hpp:102:17( [780] >record 'AstTrackingPath'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [905]api/SemBaseApi.hpp:126:17( [780] >record 'AstTrackingAlternatives'<>) */>(m, "AstTrackingAlternatives")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives* /*  [905]api/SemBaseApi.hpp:126:17( [780] >record 'AstTrackingAlternatives'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [905]api/SemBaseApi.hpp:126:17( [780] >record 'AstTrackingAlternatives'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getAllNodes", static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:131:46( [780] >record 'Org'<>) */> /*  [640]Type parameter [905]api/SemBaseApi.hpp:131:46( [780] >record 'SemId'< [657] templates: template-specialization-type>) */> /*  [905]api/SemBaseApi.hpp:131:46( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [905]api/SemBaseApi.hpp:126:17( [780] >record 'AstTrackingAlternatives'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [905]api/SemBaseApi.hpp:126:17( [780] >record 'AstTrackingAlternatives'<>) */::getAllNodes), R"RAW(\brief Return final nodes for all tracking alternatives.)RAW")
    .def("getNode", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:134:35( [780] >record 'Org'<>) */> /*  [905]api/SemBaseApi.hpp:134:35( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [905]api/SemBaseApi.hpp:126:17( [780] >record 'AstTrackingAlternatives'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [905]api/SemBaseApi.hpp:126:17( [780] >record 'AstTrackingAlternatives'<>) */::getNode), R"RAW(\brief Return first node from the alternatives.)RAW")
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives const& /*  [905]api/SemBaseApi.hpp:126:17( [780] >record 'AstTrackingAlternatives'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives const& /*  [905]api/SemBaseApi.hpp:126:17( [780] >record 'AstTrackingAlternatives'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::RadioTarget /*  [905]api/SemBaseApi.hpp:140:21( [780] >record 'RadioTarget'<>) */>(m, "AstTrackingGroupRadioTarget")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::RadioTarget* /*  [905]api/SemBaseApi.hpp:140:21( [780] >record 'RadioTarget'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::RadioTarget /*  [905]api/SemBaseApi.hpp:140:21( [780] >record 'RadioTarget'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("target", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::RadioTarget /*  [905]api/SemBaseApi.hpp:140:21( [780] >record 'RadioTarget'<>) */::target)
    .def_rw("nodes", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::RadioTarget /*  [905]api/SemBaseApi.hpp:140:21( [780] >record 'RadioTarget'<>) */::nodes)
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::RadioTarget const& /*  [905]api/SemBaseApi.hpp:140:21( [780] >record 'RadioTarget'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::RadioTarget const& /*  [905]api/SemBaseApi.hpp:140:21( [780] >record 'RadioTarget'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::Single /*  [905]api/SemBaseApi.hpp:146:21( [780] >record 'Single'<>) */>(m, "AstTrackingGroupSingle")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::Single* /*  [905]api/SemBaseApi.hpp:146:21( [780] >record 'Single'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::Single /*  [905]api/SemBaseApi.hpp:146:21( [780] >record 'Single'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("node", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::Single /*  [905]api/SemBaseApi.hpp:146:21( [780] >record 'Single'<>) */::node)
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::Single const& /*  [905]api/SemBaseApi.hpp:146:21( [780] >record 'Single'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::Single const& /*  [905]api/SemBaseApi.hpp:146:21( [780] >record 'Single'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::TrackedHashtag /*  [905]api/SemBaseApi.hpp:151:21( [780] >record 'TrackedHashtag'<>) */>(m, "AstTrackingGroupTrackedHashtag")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::TrackedHashtag* /*  [905]api/SemBaseApi.hpp:151:21( [780] >record 'TrackedHashtag'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::TrackedHashtag /*  [905]api/SemBaseApi.hpp:151:21( [780] >record 'TrackedHashtag'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("tag", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::TrackedHashtag /*  [905]api/SemBaseApi.hpp:151:21( [780] >record 'TrackedHashtag'<>) */::tag)
    .def_rw("targets", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::TrackedHashtag /*  [905]api/SemBaseApi.hpp:151:21( [780] >record 'TrackedHashtag'<>) */::targets)
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::TrackedHashtag const& /*  [905]api/SemBaseApi.hpp:151:21( [780] >record 'TrackedHashtag'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::TrackedHashtag const& /*  [905]api/SemBaseApi.hpp:151:21( [780] >record 'TrackedHashtag'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */>(m, "AstTrackingGroup")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup* /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getRadioTarget", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::RadioTarget const& /*  [905]api/SemBaseApi.hpp:179:78( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'RadioTarget'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::getRadioTarget))
    .def("getTrackedHashtag", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::TrackedHashtag& /*  [905]api/SemBaseApi.hpp:191:76( [745] T-reference [752] >ref/ptr( [780] >record 'TrackedHashtag'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)()>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::getTrackedHashtag))
    .def("getSingle", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::Single const& /*  [905]api/SemBaseApi.hpp:196:68( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Single'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::getSingle))
    .def("getRadioTarget", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::RadioTarget& /*  [905]api/SemBaseApi.hpp:201:70( [745] T-reference [752] >ref/ptr( [780] >record 'RadioTarget'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)()>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::getRadioTarget))
    .def("getSingle", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [550]type namespace @[0]' */::Single& /*  [905]api/SemBaseApi.hpp:205:60( [745] T-reference [752] >ref/ptr( [780] >record 'Single'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)()>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::getSingle))
    .def("isSingle", static_cast<bool /*  [905]api/SemBaseApi.hpp:209:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::isSingle))
    .def("isTrackedHashtag", static_cast<bool /*  [905]api/SemBaseApi.hpp:210:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::isTrackedHashtag))
    .def("isRadioTarget", static_cast<bool /*  [905]api/SemBaseApi.hpp:214:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */::isRadioTarget))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup const& /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup const& /*  [905]api/SemBaseApi.hpp:139:17( [780] >record 'AstTrackingGroup'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */>(m, "AstTrackingMap")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap* /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("footnotes", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::footnotes)
    .def_rw("subtrees", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::subtrees)
    .def_rw("names", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::names)
    .def_rw("anchorTargets", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::anchorTargets)
    .def_rw("radioTargets", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::radioTargets)
    .def_rw("hashtagDefinitions", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::hashtagDefinitions)
    .def("getIdPath",
         static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:243:49( [780] >record 'AstTrackingAlternatives'<>) */> /*  [905]api/SemBaseApi.hpp:243:49( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str const& /*  [905]api/SemBaseApi.hpp:244:26( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Str'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::getIdPath),
         nanobind::arg("id"))
    .def("getNamePath",
         static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:248:49( [780] >record 'AstTrackingAlternatives'<>) */> /*  [905]api/SemBaseApi.hpp:248:49( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str const& /*  [905]api/SemBaseApi.hpp:249:26( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Str'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::getNamePath),
         nanobind::arg("id"))
    .def("getAnchorTarget",
         static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:254:49( [780] >record 'AstTrackingAlternatives'<>) */> /*  [905]api/SemBaseApi.hpp:254:49( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str const& /*  [905]api/SemBaseApi.hpp:255:26( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Str'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::getAnchorTarget),
         nanobind::arg("id"))
    .def("getFootnotePath",
         static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingAlternatives /*  [640]Type parameter [905]api/SemBaseApi.hpp:259:49( [780] >record 'AstTrackingAlternatives'<>) */> /*  [905]api/SemBaseApi.hpp:259:49( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str const& /*  [905]api/SemBaseApi.hpp:260:26( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Str'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */::getFootnotePath),
         nanobind::arg("id"))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap const& /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap const& /*  [905]api/SemBaseApi.hpp:221:17( [780] >record 'AstTrackingMap'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment /*  [905]stdlib/RangeSegmentation.hpp:16:17( [780] >record 'SequenceSegment'<>) */>(m, "SequenceSegment")
    .def("__init__",
         [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment* /*  [905]stdlib/RangeSegmentation.hpp:16:17( [780] >record 'SequenceSegment'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment /*  [905]stdlib/RangeSegmentation.hpp:16:17( [780] >record 'SequenceSegment'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("kind", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment /*  [905]stdlib/RangeSegmentation.hpp:16:17( [780] >record 'SequenceSegment'<>) */::kind, R"RAW(\brief Kind of the segment, does not have to be unique for all
segments, and different sequence segment groups can have segments
with identical kinds.)RAW")
    .def_rw("first", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment /*  [905]stdlib/RangeSegmentation.hpp:16:17( [780] >record 'SequenceSegment'<>) */::first, R"RAW(\brief Inclusive left boundary of the segment. Mustnot overlap with
other segments' boundaries,but can be identical to the `last`,
to create a point segment (spans 1 element).)RAW")
    .def_rw("last", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment /*  [905]stdlib/RangeSegmentation.hpp:16:17( [780] >record 'SequenceSegment'<>) */::last, R"RAW(\brief Inclusive right boundary for the segment)RAW")
    .def("__repr__", [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment const& /*  [905]stdlib/RangeSegmentation.hpp:16:17( [780] >record 'SequenceSegment'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegment const& /*  [905]stdlib/RangeSegmentation.hpp:16:17( [780] >record 'SequenceSegment'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup /*  [905]stdlib/RangeSegmentation.hpp:34:17( [780] >record 'SequenceSegmentGroup'<>) */>(m, "SequenceSegmentGroup")
    .def("__init__",
         [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup* /*  [905]stdlib/RangeSegmentation.hpp:34:17( [780] >record 'SequenceSegmentGroup'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup /*  [905]stdlib/RangeSegmentation.hpp:34:17( [780] >record 'SequenceSegmentGroup'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("kind", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup /*  [905]stdlib/RangeSegmentation.hpp:34:17( [780] >record 'SequenceSegmentGroup'<>) */::kind, R"RAW(\brief An kind of the segment group, does not have to be unique)RAW")
    .def_rw("segments", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup /*  [905]stdlib/RangeSegmentation.hpp:34:17( [780] >record 'SequenceSegmentGroup'<>) */::segments, R"RAW(\brief List of input segments for grouping)RAW")
    .def("__repr__", [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup const& /*  [905]stdlib/RangeSegmentation.hpp:34:17( [780] >record 'SequenceSegmentGroup'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup const& /*  [905]stdlib/RangeSegmentation.hpp:34:17( [780] >record 'SequenceSegmentGroup'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotationTag /*  [905]stdlib/RangeSegmentation.hpp:44:17( [780] >record 'SequenceAnnotationTag'<>) */>(m, "SequenceAnnotationTag")
    .def("__init__",
         [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotationTag* /*  [905]stdlib/RangeSegmentation.hpp:44:17( [780] >record 'SequenceAnnotationTag'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotationTag /*  [905]stdlib/RangeSegmentation.hpp:44:17( [780] >record 'SequenceAnnotationTag'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("groupKind", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotationTag /*  [905]stdlib/RangeSegmentation.hpp:44:17( [780] >record 'SequenceAnnotationTag'<>) */::groupKind, R"RAW(\brief ID of the original group this segment came from)RAW")
    .def_rw("segmentKinds", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotationTag /*  [905]stdlib/RangeSegmentation.hpp:44:17( [780] >record 'SequenceAnnotationTag'<>) */::segmentKinds, R"RAW(\brief ID of the segment in this group.

Segment kinds are constructed from all ranges
that overlap points in the segment.
In the example below, there are 3 separate slices, `[2,3]`, `[1,4]`
and finally `[6,7]`. The resulting segmentation will have 4
different sequence segments from these ranges. The first one is
`[1,1]`, then `[2,3]`, `[4]`, and `[6,7]`.
```
0
1   |
2 | |
3 | |
4   |
5
6   |
7   |
```)RAW")
    .def("__repr__", [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotationTag const& /*  [905]stdlib/RangeSegmentation.hpp:44:17( [780] >record 'SequenceAnnotationTag'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotationTag const& /*  [905]stdlib/RangeSegmentation.hpp:44:17( [780] >record 'SequenceAnnotationTag'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [905]stdlib/RangeSegmentation.hpp:73:17( [780] >record 'SequenceAnnotation'<>) */>(m, "SequenceAnnotation")
    .def("__init__",
         [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation* /*  [905]stdlib/RangeSegmentation.hpp:73:17( [780] >record 'SequenceAnnotation'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [905]stdlib/RangeSegmentation.hpp:73:17( [780] >record 'SequenceAnnotation'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("first", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [905]stdlib/RangeSegmentation.hpp:73:17( [780] >record 'SequenceAnnotation'<>) */::first, R"RAW(\brief Inclusive left boundary for the sequence segment annotation)RAW")
    .def_rw("last", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [905]stdlib/RangeSegmentation.hpp:73:17( [780] >record 'SequenceAnnotation'<>) */::last, R"RAW(\brief Inclusive right boundary for the sequence segment)RAW")
    .def_rw("annotations", &hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [905]stdlib/RangeSegmentation.hpp:73:17( [780] >record 'SequenceAnnotation'<>) */::annotations, R"RAW(\brief Full list of all annotated segments.)RAW")
    .def("isAnnotatedWith",
         static_cast<bool /*  [905]stdlib/RangeSegmentation.hpp:83:19( [755] >bool<>) */(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [905]stdlib/RangeSegmentation.hpp:73:17( [780] >record 'SequenceAnnotation'<>) */::*)(int /*  [905]stdlib/RangeSegmentation.hpp:83:39( [766] >builtin/unqual<>) */, int /*  [905]stdlib/RangeSegmentation.hpp:83:54( [766] >builtin/unqual<>) */) const>(&hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [905]stdlib/RangeSegmentation.hpp:73:17( [780] >record 'SequenceAnnotation'<>) */::isAnnotatedWith),
         nanobind::arg("groupKind"),
         nanobind::arg("segmentKind"),
         R"RAW(\brief Check if the segment is annotated with a given group kind
and a segment kind.)RAW")
    .def("__repr__", [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation const& /*  [905]stdlib/RangeSegmentation.hpp:73:17( [780] >record 'SequenceAnnotation'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation const& /*  [905]stdlib/RangeSegmentation.hpp:73:17( [780] >record 'SequenceAnnotation'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Link /*  [905]imm/ImmOrgGraph.hpp:18:21( [780] >record 'Link'<>) */>(m, "GraphMapLinkLink")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Link* /*  [905]imm/ImmOrgGraph.hpp:18:21( [780] >record 'Link'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Link /*  [905]imm/ImmOrgGraph.hpp:18:21( [780] >record 'Link'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("link", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Link /*  [905]imm/ImmOrgGraph.hpp:18:21( [780] >record 'Link'<>) */::link, R"RAW(\brief Original link used to create the graph edge. Used to
return an edge to unresolved state when target is deleted. When
source is deleted the edge is simply dropped.)RAW")
    .def_rw("description", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Link /*  [905]imm/ImmOrgGraph.hpp:18:21( [780] >record 'Link'<>) */::description, R"RAW(MapLink description field can be reused or, for description
list items, this field contains a newly created statment list)RAW")
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Link const& /*  [905]imm/ImmOrgGraph.hpp:18:21( [780] >record 'Link'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Link const& /*  [905]imm/ImmOrgGraph.hpp:18:21( [780] >record 'Link'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Radio /*  [905]imm/ImmOrgGraph.hpp:31:21( [780] >record 'Radio'<>) */>(m, "GraphMapLinkRadio")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Radio* /*  [905]imm/ImmOrgGraph.hpp:31:21( [780] >record 'Radio'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Radio /*  [905]imm/ImmOrgGraph.hpp:31:21( [780] >record 'Radio'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("target", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Radio /*  [905]imm/ImmOrgGraph.hpp:31:21( [780] >record 'Radio'<>) */::target)
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Radio const& /*  [905]imm/ImmOrgGraph.hpp:31:21( [780] >record 'Radio'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Radio const& /*  [905]imm/ImmOrgGraph.hpp:31:21( [780] >record 'Radio'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */>(m, "GraphMapLink")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink* /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getRadio", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Radio& /*  [905]imm/ImmOrgGraph.hpp:36:5( [745] T-reference [752] >ref/ptr( [780] >record 'Radio'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::*)()>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::getRadio))
    .def("isRadio", static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:36:5( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::isRadio))
    .def("getLink", static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [550]type namespace @[0]' */::Link& /*  [905]imm/ImmOrgGraph.hpp:36:5( [745] T-reference [752] >ref/ptr( [780] >record 'Link'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::*)()>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::getLink))
    .def("isLink", static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:36:5( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::isLink))
    .def("getKind", static_cast<org /*  [485]Apply namespace @[0] from 785:fillTypeRec ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 785:fillTypeRec ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 785:fillTypeRec ' [550]type namespace @[0]' */::Kind /*  [905]imm/ImmOrgGraph.hpp:36:5( [786] >enum 'Kind'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */::getKind))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink const& /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink const& /*  [905]imm/ImmOrgGraph.hpp:17:17( [780] >record 'MapLink'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */>(m, "GraphMapNodeProp")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp* /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("id", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */::id)
    .def_rw("unresolved", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */::unresolved)
    .def("getAdapter",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [905]imm/ImmOrgGraph.hpp:46:35( [780] >record 'ImmAdapter'<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */::*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:47:57( [780] >record 'ImmAstContext'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:47:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */::getAdapter),
         nanobind::arg("context"))
    .def("getSubtreeId",
         static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:51:35( [780] >record 'Str'<>) */> /*  [905]imm/ImmOrgGraph.hpp:51:35( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */::*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:52:57( [780] >record 'ImmAstContext'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:52:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */::getSubtreeId),
         nanobind::arg("context"))
    .def("getFootnoteName",
         static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:54:35( [780] >record 'Str'<>) */> /*  [905]imm/ImmOrgGraph.hpp:54:35( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */::*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:55:57( [780] >record 'ImmAstContext'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:55:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */::getFootnoteName),
         nanobind::arg("context"))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp const& /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp const& /*  [905]imm/ImmOrgGraph.hpp:42:17( [780] >record 'MapNodeProp'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp /*  [905]imm/ImmOrgGraph.hpp:60:17( [780] >record 'MapEdgeProp'<>) */>(m, "GraphMapEdgeProp")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp* /*  [905]imm/ImmOrgGraph.hpp:60:17( [780] >record 'MapEdgeProp'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp /*  [905]imm/ImmOrgGraph.hpp:60:17( [780] >record 'MapEdgeProp'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("link", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp /*  [905]imm/ImmOrgGraph.hpp:60:17( [780] >record 'MapEdgeProp'<>) */::link)
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp const& /*  [905]imm/ImmOrgGraph.hpp:60:17( [780] >record 'MapEdgeProp'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp const& /*  [905]imm/ImmOrgGraph.hpp:60:17( [780] >record 'MapEdgeProp'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [905]imm/ImmOrgGraph.hpp:66:17( [780] >record 'MapNode'<>) */>(m, "GraphMapNode")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode* /*  [905]imm/ImmOrgGraph.hpp:66:17( [780] >record 'MapNode'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [905]imm/ImmOrgGraph.hpp:66:17( [780] >record 'MapNode'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("id", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [905]imm/ImmOrgGraph.hpp:66:17( [780] >record 'MapNode'<>) */::id)
    .def("__eq__",
         static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:72:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [905]imm/ImmOrgGraph.hpp:66:17( [780] >record 'MapNode'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:72:45( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [905]imm/ImmOrgGraph.hpp:66:17( [780] >record 'MapNode'<>) */::operator==),
         nanobind::arg("other"))
    .def("__lt__",
         static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:76:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [905]imm/ImmOrgGraph.hpp:66:17( [780] >record 'MapNode'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:76:44( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [905]imm/ImmOrgGraph.hpp:66:17( [780] >record 'MapNode'<>) */::operator<),
         nanobind::arg("other"))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:66:17( [780] >record 'MapNode'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:66:17( [780] >record 'MapNode'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [905]imm/ImmOrgGraph.hpp:83:17( [780] >record 'MapEdge'<>) */>(m, "GraphMapEdge")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge* /*  [905]imm/ImmOrgGraph.hpp:83:17( [780] >record 'MapEdge'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [905]imm/ImmOrgGraph.hpp:83:17( [780] >record 'MapEdge'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("source", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [905]imm/ImmOrgGraph.hpp:83:17( [780] >record 'MapEdge'<>) */::source)
    .def_rw("target", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [905]imm/ImmOrgGraph.hpp:83:17( [780] >record 'MapEdge'<>) */::target)
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge const& /*  [905]imm/ImmOrgGraph.hpp:83:17( [780] >record 'MapEdge'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge const& /*  [905]imm/ImmOrgGraph.hpp:83:17( [780] >record 'MapEdge'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */>(m, "GraphMapGraph")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph* /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("nodeProps", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::nodeProps)
    .def_rw("edgeProps", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::edgeProps)
    .def_rw("adjList", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::adjList)
    .def_rw("adjListIn", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::adjListIn)
    .def("nodeCount", static_cast<int /*  [905]imm/ImmOrgGraph.hpp:152:18( [766] >builtin/unqual<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::nodeCount))
    .def("edgeCount", static_cast<int /*  [905]imm/ImmOrgGraph.hpp:153:18( [766] >builtin/unqual<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::edgeCount))
    .def("outNodes",
         static_cast<org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::AdjNodesList const& /*  [905]imm/ImmOrgGraph.hpp:155:34( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type imm/ImmOrgGraph.hpp:119:60)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:155:58( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::outNodes),
         nanobind::arg("node"))
    .def("inNodes",
         static_cast<org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::AdjNodesList const& /*  [905]imm/ImmOrgGraph.hpp:159:34( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type imm/ImmOrgGraph.hpp:119:60)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:159:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::inNodes),
         nanobind::arg("node"))
    .def("adjEdges",
         static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:163:33( [780] >record 'MapEdge'<>) */> /*  [905]imm/ImmOrgGraph.hpp:163:33( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:163:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::adjEdges),
         nanobind::arg("node"))
    .def("adjNodes",
         static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:176:33( [780] >record 'MapNode'<>) */> /*  [905]imm/ImmOrgGraph.hpp:176:33( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:176:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::adjNodes),
         nanobind::arg("node"))
    .def("outEdges",
         static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:190:33( [780] >record 'MapEdge'<>) */> /*  [905]imm/ImmOrgGraph.hpp:190:33( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:190:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::outEdges),
         nanobind::arg("node"))
    .def("inEdges",
         static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:198:33( [780] >record 'MapEdge'<>) */> /*  [905]imm/ImmOrgGraph.hpp:198:33( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:198:56( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::inEdges),
         nanobind::arg("node"))
    .def("outDegree",
         static_cast<int /*  [905]imm/ImmOrgGraph.hpp:206:18( [766] >builtin/unqual<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:206:43( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::outDegree),
         nanobind::arg("node"))
    .def("inDegree",
         static_cast<int /*  [905]imm/ImmOrgGraph.hpp:210:18( [766] >builtin/unqual<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:210:42( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::inDegree),
         nanobind::arg("node"))
    .def("isRegisteredNode",
         static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:214:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:214:51( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::isRegisteredNode),
         nanobind::arg("id"))
    .def("isRegisteredNode",
         static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:218:65( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmUniqId const& /*  [905]imm/ImmOrgGraph.hpp:219:36( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmUniqId'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::isRegisteredNode),
         nanobind::arg("id"))
    .def("at",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp const& /*  [905]imm/ImmOrgGraph.hpp:223:68( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNodeProp'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:224:24( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::at),
         nanobind::arg("node"))
    .def("at",
         static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp const& /*  [905]imm/ImmOrgGraph.hpp:228:68( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapEdgeProp'<>)<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge const& /*  [905]imm/ImmOrgGraph.hpp:229:24( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapEdge'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::at),
         nanobind::arg("edge"))
    .def("addEdge",
         static_cast<void /*  [905]imm/ImmOrgGraph.hpp:234:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge const& /*  [905]imm/ImmOrgGraph.hpp:234:42( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapEdge'<>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::addEdge),
         nanobind::arg("edge"))
    .def("addEdge",
         static_cast<void /*  [905]imm/ImmOrgGraph.hpp:237:60(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdge const& /*  [905]imm/ImmOrgGraph.hpp:238:28( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapEdge'<>)<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapEdgeProp const& /*  [905]imm/ImmOrgGraph.hpp:239:28( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapEdgeProp'<>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::addEdge),
         nanobind::arg("edge"),
         nanobind::arg("prop"))
    .def("addNode",
         static_cast<void /*  [905]imm/ImmOrgGraph.hpp:242:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:242:42( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::addNode),
         nanobind::arg("node"),
         R"RAW(\brief Add node to the graph, without registering any outgoing or
ingoing elements.)RAW")
    .def("addNode",
         static_cast<void /*  [905]imm/ImmOrgGraph.hpp:243:60(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:244:28( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp const& /*  [905]imm/ImmOrgGraph.hpp:245:28( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNodeProp'<>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::addNode),
         nanobind::arg("node"),
         nanobind::arg("prop"))
    .def("hasEdge",
         static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:250:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:250:42( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:250:65( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::hasEdge),
         nanobind::arg("source"),
         nanobind::arg("target"))
    .def("hasNode",
         static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:261:19( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNode const& /*  [905]imm/ImmOrgGraph.hpp:261:42( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNode'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::hasNode),
         nanobind::arg("node"))
    .def("hasEdge",
         static_cast<bool /*  [905]imm/ImmOrgGraph.hpp:265:60( [755] >bool<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter const& /*  [905]imm/ImmOrgGraph.hpp:266:37( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmAdapter'<>)<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter const& /*  [905]imm/ImmOrgGraph.hpp:267:37( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmAdapter'<>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */::hasEdge),
         nanobind::arg("source"),
         nanobind::arg("target"))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph const& /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph const& /*  [905]imm/ImmOrgGraph.hpp:137:8( [780] >record 'MapGraph'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [905]imm/ImmOrgGraph.hpp:370:8( [780] >record 'MapConfig'<>) */>(m, "GraphMapConfig")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig* /*  [905]imm/ImmOrgGraph.hpp:370:8( [780] >record 'MapConfig'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [905]imm/ImmOrgGraph.hpp:370:8( [780] >record 'MapConfig'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("dbg", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [905]imm/ImmOrgGraph.hpp:370:8( [780] >record 'MapConfig'<>) */::dbg)
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig const& /*  [905]imm/ImmOrgGraph.hpp:370:8( [780] >record 'MapConfig'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig const& /*  [905]imm/ImmOrgGraph.hpp:370:8( [780] >record 'MapConfig'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */>(m, "GraphMapGraphState")
    .def_rw("graph", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::graph)
    .def_rw("ast", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::ast)
    .def("getGraph", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:405:40( [780] >record 'MapGraph'<>) */> /*  [905]imm/ImmOrgGraph.hpp:405:40( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::getGraph))
    .def_static("FromAstContextStatic",
                static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:410:52( [780] >record 'MapGraphState'<>) */> /*  [905]imm/ImmOrgGraph.hpp:410:52( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */(*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:411:50( [780] >record 'ImmAstContext'<>) */> /*  [905]imm/ImmOrgGraph.hpp:411:50( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::FromAstContext),
                nanobind::arg("ast"))
    .def("registerNode",
         static_cast<void /*  [905]imm/ImmOrgGraph.hpp:416:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapNodeProp const& /*  [905]imm/ImmOrgGraph.hpp:417:43( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'MapNodeProp'<>)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:418:43( [780] >record 'MapConfig'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:418:43( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::registerNode),
         nanobind::arg("node"),
         nanobind::arg("conf"))
    .def("addNode",
         static_cast<void /*  [905]imm/ImmOrgGraph.hpp:420:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter const& /*  [905]imm/ImmOrgGraph.hpp:421:43( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmAdapter'<>)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:422:43( [780] >record 'MapConfig'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:422:43( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::addNode),
         nanobind::arg("node"),
         nanobind::arg("conf"))
    .def("addNodeRec",
         static_cast<void /*  [905]imm/ImmOrgGraph.hpp:424:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:425:57( [780] >record 'ImmAstContext'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:425:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter const& /*  [905]imm/ImmOrgGraph.hpp:426:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'ImmAdapter'<>)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:427:57( [780] >record 'MapConfig'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:427:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::addNodeRec),
         nanobind::arg("ast"),
         nanobind::arg("node"),
         nanobind::arg("conf"))
    .def("getUnresolvedSubtreeLinks",
         static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:429:33( [780] >record 'MapLink'<>) */> /*  [905]imm/ImmOrgGraph.hpp:429:33( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterT<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmSubtree /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:430:53( [780] >record 'ImmSubtree'<>) */> /*  [905]imm/ImmOrgGraph.hpp:430:53( [780] >record 'ImmAdapterT'< [657] templates: template-specialization-type>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:431:53( [780] >record 'MapConfig'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:431:53( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::getUnresolvedSubtreeLinks),
         nanobind::arg("node"),
         nanobind::arg("conf"))
    .def("getUnresolvedLink",
         static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapLink /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:433:33( [780] >record 'MapLink'<>) */> /*  [905]imm/ImmOrgGraph.hpp:433:33( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterT<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmLink /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:434:50( [780] >record 'ImmLink'<>) */> /*  [905]imm/ImmOrgGraph.hpp:434:50( [780] >record 'ImmAdapterT'< [657] templates: template-specialization-type>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapConfig /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:435:50( [780] >record 'MapConfig'<>) */> const& /*  [905]imm/ImmOrgGraph.hpp:435:50( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */::getUnresolvedLink),
         nanobind::arg("node"),
         nanobind::arg("conf"))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState const& /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState const& /*  [905]imm/ImmOrgGraph.hpp:399:8( [780] >record 'MapGraphState'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::PyCodeEvalParameters /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:132:1( [780] >record 'PyCodeEvalParameters'<>) */>(m, "PyCodeEvalParameters")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::PyCodeEvalParameters* /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:132:1( [780] >record 'PyCodeEvalParameters'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::PyCodeEvalParameters /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:132:1( [780] >record 'PyCodeEvalParameters'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("evalBlock", &org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::PyCodeEvalParameters /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:132:1( [780] >record 'PyCodeEvalParameters'<>) */::evalBlock)
    .def("setTraceFile",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:136:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::PyCodeEvalParameters /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:132:1( [780] >record 'PyCodeEvalParameters'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:136:51( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::PyCodeEvalParameters /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:132:1( [780] >record 'PyCodeEvalParameters'<>) */::setTraceFile),
         nanobind::arg("path"))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::PyCodeEvalParameters const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:132:1( [780] >record 'PyCodeEvalParameters'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::PyCodeEvalParameters const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:132:1( [780] >record 'PyCodeEvalParameters'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */>(m, "ExporterPython")
    .def("__init__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython* /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("enableBufferTrace", static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:369:26(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)()>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::enableBufferTrace))
    .def("getTraceBuffer", static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:370:26( [735] typedef type bits/stringfwd.h:79:33) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)() const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::getTraceBuffer))
    .def("enableFileTrace",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:371:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:371:54( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, bool /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:371:65( [755] >bool<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::enableFileTrace),
         nanobind::arg("path"),
         nanobind::arg("colored"))
    .def("setVisitAnyIdAround",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:374:23(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:374:50( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setVisitAnyIdAround),
         nanobind::arg("cb"))
    .def("setVisitAnyIdIn",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:379:23(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:379:46( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setVisitAnyIdIn),
         nanobind::arg("cb"))
    .def("setVisitAnyField",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:382:23(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:382:47( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setVisitAnyField),
         nanobind::arg("cb"))
    .def("setEvalTopCb",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:385:23(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:385:43( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setEvalTopCb),
         nanobind::arg("cb"))
    .def("setVisitIdAround",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:388:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(OrgSemKind /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:388:47( [786] >enum 'OrgSemKind'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:388:60( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setVisitIdAround),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setEvalIdAround",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:393:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(OrgSemKind /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:393:46( [786] >enum 'OrgSemKind'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:393:59( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setEvalIdAround),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setVisitIdInCb",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:398:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(OrgSemKind /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:398:45( [786] >enum 'OrgSemKind'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:398:58( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setVisitIdInCb),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setEvalIdIn",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:403:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(OrgSemKind /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:403:42( [786] >enum 'OrgSemKind'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:403:55( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setEvalIdIn),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setVisitLeafField",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:408:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(org /*  [485]Apply namespace @[0] from 785:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 785:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 785:fillTypeRec ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:409:42( [786] >enum 'LeafFieldType'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:410:42( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setVisitLeafField),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setEvalLeafField",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:415:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(org /*  [485]Apply namespace @[0] from 785:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 785:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 785:fillTypeRec ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:416:42( [786] >enum 'LeafFieldType'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:417:42( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setEvalLeafField),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setVisitOrgField",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:422:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(OrgSemKind /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:422:47( [786] >enum 'OrgSemKind'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:422:60( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setVisitOrgField),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setEvalOrgField",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:427:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(OrgSemKind /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:427:46( [786] >enum 'OrgSemKind'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:427:59( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setEvalOrgField),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setSelf",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:432:22(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(nanobind /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::object /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:432:47( [780] >record 'object'<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setSelf),
         nanobind::arg("val"))
    .def("setNewOrgRes",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:436:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(OrgSemKind /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:436:43( [786] >enum 'OrgSemKind'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:436:56( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setNewOrgRes),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setNewAnyOrgRes",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:441:23(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:441:46( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setNewAnyOrgRes),
         nanobind::arg("cb"))
    .def("setNewLeafRes",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:444:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(org /*  [485]Apply namespace @[0] from 785:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 785:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 785:fillTypeRec ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:445:42( [786] >enum 'LeafFieldType'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:446:42( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setNewLeafRes),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setNewAnyLeafRes",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:451:23(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:451:47( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setNewAnyLeafRes),
         nanobind::arg("cb"))
    .def("setPushVisitAnyId",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:454:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:454:44( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setPushVisitAnyId),
         nanobind::arg("cb"))
    .def("setPopVisitAnyId",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:457:23(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:457:47( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setPopVisitAnyId),
         nanobind::arg("cb"))
    .def("setPushVisitId",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:460:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(OrgSemKind /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:460:45( [786] >enum 'OrgSemKind'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:460:58( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setPushVisitId),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setPopVisitIdCb",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:465:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(OrgSemKind /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:465:46( [786] >enum 'OrgSemKind'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:465:59( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setPopVisitIdCb),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("setVisitAnyHookCb",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:470:23(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:470:48( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setVisitAnyHookCb),
         nanobind::arg("cb"))
    .def("setVisitIdHook",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:473:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(OrgSemKind /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:473:45( [786] >enum 'OrgSemKind'<>) */, org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::PyFunc /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:473:58( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:317:11) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::setVisitIdHook),
         nanobind::arg("kind"),
         nanobind::arg("cb"))
    .def("print_trace",
         static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:477:19(<>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:478:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:479:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:480:28( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, int /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:481:28( [766] >builtin/unqual<>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::print_trace),
         nanobind::arg("trace"),
         nanobind::arg("file"),
         nanobind::arg("function"),
         nanobind::arg("line"))
    .def("evalTop",
         static_cast<org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::Res /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:725:18( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:318:11) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]pyhaxorg/pyhaxorg_manual_impl.hpp:725:57( [780] >record 'Org'<>) */> /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:725:57( [780] >record 'SemId'< [657] templates: template-specialization-type>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::evalTop),
         nanobind::arg("org"))
    .def("eval",
         static_cast<org /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[3]' */::bind /*  [485]Apply namespace @[1] from 741:fillTypeRec ' [539]regular type namespaces @[2]' */::python /*  [485]Apply namespace @[2] from 741:fillTypeRec ' [539]regular type namespaces @[1]' */::ExporterPython /*  [485]Apply namespace @[3] from 741:fillTypeRec ' [550]type namespace @[0]' */::Res /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:727:18( [735] typedef type pyhaxorg/pyhaxorg_manual_impl.hpp:318:11) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]pyhaxorg/pyhaxorg_manual_impl.hpp:727:54( [780] >record 'Org'<>) */> /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:727:54( [780] >record 'SemId'< [657] templates: template-specialization-type>) */)>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */::eval),
         nanobind::arg("org"))
    .def("__repr__", [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ExporterPython const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:309:1( [780] >record 'ExporterPython'<>) */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LispCode::Call>(m, "LispCodeCall")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::LispCode::Call* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LispCode::Call();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::LispCode::Call::name)
    .def_rw("args", &org::sem::LispCode::Call::args)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::Call::*)(org::sem::LispCode::Call const&) const>(&org::sem::LispCode::Call::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Call const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Call const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LispCode::List>(m, "LispCodeList")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::LispCode::List* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LispCode::List();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("items", &org::sem::LispCode::List::items)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::List::*)(org::sem::LispCode::List const&) const>(&org::sem::LispCode::List::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LispCode::List const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::List const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LispCode::KeyValue>(m, "LispCodeKeyValue")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::LispCode::KeyValue* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LispCode::KeyValue();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::LispCode::KeyValue::name)
    .def_rw("value", &org::sem::LispCode::KeyValue::value)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::KeyValue::*)(org::sem::LispCode::KeyValue const&) const>(&org::sem::LispCode::KeyValue::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LispCode::KeyValue const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::KeyValue const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LispCode::Number>(m, "LispCodeNumber")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::LispCode::Number* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LispCode::Number();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::LispCode::Number::value)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::Number::*)(org::sem::LispCode::Number const&) const>(&org::sem::LispCode::Number::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Number const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Number const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LispCode::Text>(m, "LispCodeText")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::LispCode::Text* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LispCode::Text();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::LispCode::Text::value)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::Text::*)(org::sem::LispCode::Text const&) const>(&org::sem::LispCode::Text::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Text const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Text const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LispCode::Ident>(m, "LispCodeIdent")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::LispCode::Ident* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LispCode::Ident();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::LispCode::Ident::name)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::Ident::*)(org::sem::LispCode::Ident const&) const>(&org::sem::LispCode::Ident::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Ident const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Ident const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LispCode::Boolean>(m, "LispCodeBoolean")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::LispCode::Boolean* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LispCode::Boolean();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::LispCode::Boolean::value)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::Boolean::*)(org::sem::LispCode::Boolean const&) const>(&org::sem::LispCode::Boolean::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Boolean const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Boolean const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LispCode::Real>(m, "LispCodeReal")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::LispCode::Real* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LispCode::Real();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::LispCode::Real::value)
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::Real::*)(org::sem::LispCode::Real const&) const>(&org::sem::LispCode::Real::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LispCode::Real const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode::Real const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::LispCode::Kind>(m, "LispCodeKind", type_registry_guard);
  nanobind::enum_<org::sem::LispCode::Kind>(m, "LispCodeKind")
    .value("Call", org::sem::LispCode::Kind::Call)
    .value("List", org::sem::LispCode::Kind::List)
    .value("KeyValue", org::sem::LispCode::Kind::KeyValue)
    .value("Number", org::sem::LispCode::Kind::Number)
    .value("Text", org::sem::LispCode::Kind::Text)
    .value("Ident", org::sem::LispCode::Kind::Ident)
    .value("Boolean", org::sem::LispCode::Kind::Boolean)
    .value("Real", org::sem::LispCode::Kind::Real)
    .def("__iter__", [](org::sem::LispCode::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::LispCode::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::LispCode::Kind>();
                     })
    .def("__int__", [](org::sem::LispCode::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::LispCode::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::LispCode::Kind lhs, org::sem::LispCode::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::LispCode::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::LispCode>(m, "LispCode")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::LispCode* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LispCode();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::sem::LispCode::*)(org::sem::LispCode const&) const>(&org::sem::LispCode::operator==),
         nanobind::arg("other"))
    .def("isCall", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isCall))
    .def("getCall", static_cast<org::sem::LispCode::Call&(org::sem::LispCode::*)()>(&org::sem::LispCode::getCall))
    .def("isList", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isList))
    .def("getList", static_cast<org::sem::LispCode::List&(org::sem::LispCode::*)()>(&org::sem::LispCode::getList))
    .def("isKeyValue", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isKeyValue))
    .def("getKeyValue", static_cast<org::sem::LispCode::KeyValue&(org::sem::LispCode::*)()>(&org::sem::LispCode::getKeyValue))
    .def("isNumber", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isNumber))
    .def("getNumber", static_cast<org::sem::LispCode::Number&(org::sem::LispCode::*)()>(&org::sem::LispCode::getNumber))
    .def("isText", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isText))
    .def("getText", static_cast<org::sem::LispCode::Text&(org::sem::LispCode::*)()>(&org::sem::LispCode::getText))
    .def("isIdent", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isIdent))
    .def("getIdent", static_cast<org::sem::LispCode::Ident&(org::sem::LispCode::*)()>(&org::sem::LispCode::getIdent))
    .def("isBoolean", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isBoolean))
    .def("getBoolean", static_cast<org::sem::LispCode::Boolean&(org::sem::LispCode::*)()>(&org::sem::LispCode::getBoolean))
    .def("isReal", static_cast<bool(org::sem::LispCode::*)() const>(&org::sem::LispCode::isReal))
    .def("getReal", static_cast<org::sem::LispCode::Real&(org::sem::LispCode::*)()>(&org::sem::LispCode::getReal))
    .def_static("getKindStatic",
                static_cast<org::sem::LispCode::Kind(*)(org::sem::LispCode::Data const&)>(&org::sem::LispCode::getKind),
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::LispCode::Kind(org::sem::LispCode::*)() const>(&org::sem::LispCode::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::LispCode::*)() const>(&org::sem::LispCode::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::LispCode::Data const&(org::sem::LispCode::*)() const>(&org::sem::LispCode::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::LispCode::Kind(org::sem::LispCode::*)() const>(&org::sem::LispCode::sub_variant_get_kind))
    .def("__repr__", [](org::sem::LispCode const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LispCode const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::AxisRef::Position::Index>(m, "TblfmExprAxisRefPositionIndex")
    .def("__init__",
         [](org::sem::Tblfm::Expr::AxisRef::Position::Index* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Tblfm::Expr::AxisRef::Position::Index();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("index", &org::sem::Tblfm::Expr::AxisRef::Position::Index::index)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::Index::*)(org::sem::Tblfm::Expr::AxisRef::Position::Index const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::Index::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::AxisRef::Position::Index const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::AxisRef::Position::Index const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::AxisRef::Position::Name>(m, "TblfmExprAxisRefPositionName")
    .def("__init__",
         [](org::sem::Tblfm::Expr::AxisRef::Position::Name* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Tblfm::Expr::AxisRef::Position::Name();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::Tblfm::Expr::AxisRef::Position::Name::name)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::Name::*)(org::sem::Tblfm::Expr::AxisRef::Position::Name const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::Name::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::AxisRef::Position::Name const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::AxisRef::Position::Name const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::Tblfm::Expr::AxisRef::Position::Kind>(m, "TblfmExprAxisRefPositionKind", type_registry_guard);
  nanobind::enum_<org::sem::Tblfm::Expr::AxisRef::Position::Kind>(m, "TblfmExprAxisRefPositionKind")
    .value("Index", org::sem::Tblfm::Expr::AxisRef::Position::Kind::Index)
    .value("Name", org::sem::Tblfm::Expr::AxisRef::Position::Kind::Name)
    .def("__iter__", [](org::sem::Tblfm::Expr::AxisRef::Position::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::Tblfm::Expr::AxisRef::Position::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::Tblfm::Expr::AxisRef::Position::Kind>();
                     })
    .def("__int__", [](org::sem::Tblfm::Expr::AxisRef::Position::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::Tblfm::Expr::AxisRef::Position::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::Tblfm::Expr::AxisRef::Position::Kind lhs, org::sem::Tblfm::Expr::AxisRef::Position::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::Tblfm::Expr::AxisRef::Position::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::Tblfm::Expr::AxisRef::Position>(m, "TblfmExprAxisRefPosition")
    .def("__init__",
         [](org::sem::Tblfm::Expr::AxisRef::Position* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Tblfm::Expr::AxisRef::Position();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)(org::sem::Tblfm::Expr::AxisRef::Position const&) const>(&org::sem::Tblfm::Expr::AxisRef::Position::operator==),
         nanobind::arg("other"))
    .def("isIndex", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::isIndex))
    .def("getIndex", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Index&(org::sem::Tblfm::Expr::AxisRef::Position::*)()>(&org::sem::Tblfm::Expr::AxisRef::Position::getIndex))
    .def("isName", static_cast<bool(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::isName))
    .def("getName", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Name&(org::sem::Tblfm::Expr::AxisRef::Position::*)()>(&org::sem::Tblfm::Expr::AxisRef::Position::getName))
    .def_static("getKindStatic",
                static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(*)(org::sem::Tblfm::Expr::AxisRef::Position::Data const&)>(&org::sem::Tblfm::Expr::AxisRef::Position::getKind),
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Data const&(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::Tblfm::Expr::AxisRef::Position::Kind(org::sem::Tblfm::Expr::AxisRef::Position::*)() const>(&org::sem::Tblfm::Expr::AxisRef::Position::sub_variant_get_kind))
    .def("__repr__", [](org::sem::Tblfm::Expr::AxisRef::Position const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::AxisRef::Position const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::AxisRef>(m, "TblfmExprAxisRef")
    .def("__init__",
         [](org::sem::Tblfm::Expr::AxisRef* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Tblfm::Expr::AxisRef();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("col", &org::sem::Tblfm::Expr::AxisRef::col)
    .def_rw("row", &org::sem::Tblfm::Expr::AxisRef::row)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::AxisRef::*)(org::sem::Tblfm::Expr::AxisRef const&) const>(&org::sem::Tblfm::Expr::AxisRef::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::AxisRef const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::AxisRef const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::AxisName>(m, "TblfmExprAxisName")
    .def("__init__",
         [](org::sem::Tblfm::Expr::AxisName* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Tblfm::Expr::AxisName();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::Tblfm::Expr::AxisName::name)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::AxisName::*)(org::sem::Tblfm::Expr::AxisName const&) const>(&org::sem::Tblfm::Expr::AxisName::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::AxisName const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::AxisName const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::IntLiteral>(m, "TblfmExprIntLiteral")
    .def("__init__",
         [](org::sem::Tblfm::Expr::IntLiteral* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Tblfm::Expr::IntLiteral();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::Tblfm::Expr::IntLiteral::value)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::IntLiteral::*)(org::sem::Tblfm::Expr::IntLiteral const&) const>(&org::sem::Tblfm::Expr::IntLiteral::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::IntLiteral const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::IntLiteral const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::FloatLiteral>(m, "TblfmExprFloatLiteral")
    .def("__init__",
         [](org::sem::Tblfm::Expr::FloatLiteral* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Tblfm::Expr::FloatLiteral();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::Tblfm::Expr::FloatLiteral::value)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::FloatLiteral::*)(org::sem::Tblfm::Expr::FloatLiteral const&) const>(&org::sem::Tblfm::Expr::FloatLiteral::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::FloatLiteral const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::FloatLiteral const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::RangeRef>(m, "TblfmExprRangeRef")
    .def("__init__",
         [](org::sem::Tblfm::Expr::RangeRef* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Tblfm::Expr::RangeRef();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("first", &org::sem::Tblfm::Expr::RangeRef::first)
    .def_rw("last", &org::sem::Tblfm::Expr::RangeRef::last)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::RangeRef::*)(org::sem::Tblfm::Expr::RangeRef const&) const>(&org::sem::Tblfm::Expr::RangeRef::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::RangeRef const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::RangeRef const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::Call>(m, "TblfmExprCall")
    .def("__init__",
         [](org::sem::Tblfm::Expr::Call* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Tblfm::Expr::Call();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::Tblfm::Expr::Call::name)
    .def_rw("args", &org::sem::Tblfm::Expr::Call::args)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::Call::*)(org::sem::Tblfm::Expr::Call const&) const>(&org::sem::Tblfm::Expr::Call::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::Call const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::Call const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm::Expr::Elisp>(m, "TblfmExprElisp")
    .def("__init__",
         [](org::sem::Tblfm::Expr::Elisp* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Tblfm::Expr::Elisp();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::Tblfm::Expr::Elisp::value)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::Elisp::*)(org::sem::Tblfm::Expr::Elisp const&) const>(&org::sem::Tblfm::Expr::Elisp::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Expr::Elisp const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr::Elisp const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::Tblfm::Expr::Kind>(m, "TblfmExprKind", type_registry_guard);
  nanobind::enum_<org::sem::Tblfm::Expr::Kind>(m, "TblfmExprKind")
    .value("AxisRef", org::sem::Tblfm::Expr::Kind::AxisRef)
    .value("AxisName", org::sem::Tblfm::Expr::Kind::AxisName)
    .value("IntLiteral", org::sem::Tblfm::Expr::Kind::IntLiteral)
    .value("FloatLiteral", org::sem::Tblfm::Expr::Kind::FloatLiteral)
    .value("RangeRef", org::sem::Tblfm::Expr::Kind::RangeRef)
    .value("Call", org::sem::Tblfm::Expr::Kind::Call)
    .value("Elisp", org::sem::Tblfm::Expr::Kind::Elisp)
    .def("__iter__", [](org::sem::Tblfm::Expr::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::Tblfm::Expr::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::Tblfm::Expr::Kind>();
                     })
    .def("__int__", [](org::sem::Tblfm::Expr::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::Tblfm::Expr::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::Tblfm::Expr::Kind lhs, org::sem::Tblfm::Expr::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::Tblfm::Expr::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::Tblfm::Expr>(m, "TblfmExpr")
    .def("__init__",
         [](org::sem::Tblfm::Expr* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Tblfm::Expr();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Expr::*)(org::sem::Tblfm::Expr const&) const>(&org::sem::Tblfm::Expr::operator==),
         nanobind::arg("other"))
    .def("isAxisRef", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isAxisRef))
    .def("getAxisRef", static_cast<org::sem::Tblfm::Expr::AxisRef&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getAxisRef))
    .def("isAxisName", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isAxisName))
    .def("getAxisName", static_cast<org::sem::Tblfm::Expr::AxisName&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getAxisName))
    .def("isIntLiteral", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isIntLiteral))
    .def("getIntLiteral", static_cast<org::sem::Tblfm::Expr::IntLiteral&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getIntLiteral))
    .def("isFloatLiteral", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isFloatLiteral))
    .def("getFloatLiteral", static_cast<org::sem::Tblfm::Expr::FloatLiteral&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getFloatLiteral))
    .def("isRangeRef", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isRangeRef))
    .def("getRangeRef", static_cast<org::sem::Tblfm::Expr::RangeRef&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getRangeRef))
    .def("isCall", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isCall))
    .def("getCall", static_cast<org::sem::Tblfm::Expr::Call&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getCall))
    .def("isElisp", static_cast<bool(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::isElisp))
    .def("getElisp", static_cast<org::sem::Tblfm::Expr::Elisp&(org::sem::Tblfm::Expr::*)()>(&org::sem::Tblfm::Expr::getElisp))
    .def_static("getKindStatic",
                static_cast<org::sem::Tblfm::Expr::Kind(*)(org::sem::Tblfm::Expr::Data const&)>(&org::sem::Tblfm::Expr::getKind),
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::Tblfm::Expr::Kind(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::Tblfm::Expr::Data const&(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::Tblfm::Expr::Kind(org::sem::Tblfm::Expr::*)() const>(&org::sem::Tblfm::Expr::sub_variant_get_kind))
    .def("__repr__", [](org::sem::Tblfm::Expr const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Expr const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::Tblfm::Assign::Flag>(m, "TblfmAssignFlag", type_registry_guard);
  nanobind::enum_<org::sem::Tblfm::Assign::Flag>(m, "TblfmAssignFlag")
    .value("CellLeftAlign", org::sem::Tblfm::Assign::Flag::CellLeftAlign, R"RAW(Left-align the result)RAW")
    .value("CellRightAlign", org::sem::Tblfm::Assign::Flag::CellRightAlign, R"RAW(Right-align the result)RAW")
    .value("CellCenterAlign", org::sem::Tblfm::Assign::Flag::CellCenterAlign, R"RAW(Center-align the result)RAW")
    .value("CellNumber", org::sem::Tblfm::Assign::Flag::CellNumber, R"RAW(Convert result to number/currency format)RAW")
    .value("CellExponential", org::sem::Tblfm::Assign::Flag::CellExponential, R"RAW(Use exponential notation for numbers)RAW")
    .value("CellFloating", org::sem::Tblfm::Assign::Flag::CellFloating, R"RAW(Use floating point format)RAW")
    .value("CellUnformat", org::sem::Tblfm::Assign::Flag::CellUnformat, R"RAW(Unformat values before calculating)RAW")
    .value("CellText", org::sem::Tblfm::Assign::Flag::CellText, R"RAW(Convert result to text)RAW")
    .value("CellBool", org::sem::Tblfm::Assign::Flag::CellBool, R"RAW(Display boolean values as t/nil)RAW")
    .value("CellDecimal", org::sem::Tblfm::Assign::Flag::CellDecimal, R"RAW(Fixed format with specified decimal places (e.g., ;D2))RAW")
    .value("CellPercentage", org::sem::Tblfm::Assign::Flag::CellPercentage, R"RAW(Percentage format)RAW")
    .value("CellHours", org::sem::Tblfm::Assign::Flag::CellHours, R"RAW(Convert to hours/minutes (HH:MM))RAW")
    .value("CellZero", org::sem::Tblfm::Assign::Flag::CellZero, R"RAW(Display zero as empty cell)RAW")
    .value("CellMarkInvalid", org::sem::Tblfm::Assign::Flag::CellMarkInvalid, R"RAW(Mark field as invalid if conversion fails)RAW")
    .value("CellQuote", org::sem::Tblfm::Assign::Flag::CellQuote, R"RAW(Quote field contents)RAW")
    .def("__iter__", [](org::sem::Tblfm::Assign::Flag const& _self) -> org::bind::python::PyEnumIterator<org::sem::Tblfm::Assign::Flag> {
                     return org::bind::python::PyEnumIterator<org::sem::Tblfm::Assign::Flag>();
                     })
    .def("__int__", [](org::sem::Tblfm::Assign::Flag const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::Tblfm::Assign::Flag const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::Tblfm::Assign::Flag lhs, org::sem::Tblfm::Assign::Flag rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::Tblfm::Assign::Flag it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::Tblfm::Assign>(m, "TblfmAssign")
    .def("__init__",
         [](org::sem::Tblfm::Assign* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Tblfm::Assign();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("target", &org::sem::Tblfm::Assign::target)
    .def_rw("expr", &org::sem::Tblfm::Assign::expr)
    .def_rw("flags", &org::sem::Tblfm::Assign::flags)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::Assign::*)(org::sem::Tblfm::Assign const&) const>(&org::sem::Tblfm::Assign::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm::Assign const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm::Assign const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Tblfm>(m, "Tblfm")
    .def("__init__",
         [](org::sem::Tblfm* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Tblfm();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("exprs", &org::sem::Tblfm::exprs)
    .def("__eq__",
         static_cast<bool(org::sem::Tblfm::*)(org::sem::Tblfm const&) const>(&org::sem::Tblfm::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::Tblfm const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Tblfm const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::AttrValue::DimensionSpan>(m, "AttrValueDimensionSpan")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::AttrValue::DimensionSpan* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::AttrValue::DimensionSpan();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("first", &org::sem::AttrValue::DimensionSpan::first)
    .def_rw("last", &org::sem::AttrValue::DimensionSpan::last)
    .def("__eq__",
         static_cast<bool(org::sem::AttrValue::DimensionSpan::*)(org::sem::AttrValue::DimensionSpan const&) const>(&org::sem::AttrValue::DimensionSpan::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::AttrValue::DimensionSpan const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrValue::DimensionSpan const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::AttrValue::TextValue>(m, "AttrValueTextValue")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::AttrValue::TextValue* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::AttrValue::TextValue();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::AttrValue::TextValue::value)
    .def("__eq__",
         static_cast<bool(org::sem::AttrValue::TextValue::*)(org::sem::AttrValue::TextValue const&) const>(&org::sem::AttrValue::TextValue::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::AttrValue::TextValue const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrValue::TextValue const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::AttrValue::FileReference>(m, "AttrValueFileReference")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::AttrValue::FileReference* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::AttrValue::FileReference();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("file", &org::sem::AttrValue::FileReference::file)
    .def_rw("reference", &org::sem::AttrValue::FileReference::reference)
    .def("__eq__",
         static_cast<bool(org::sem::AttrValue::FileReference::*)(org::sem::AttrValue::FileReference const&) const>(&org::sem::AttrValue::FileReference::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::AttrValue::FileReference const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrValue::FileReference const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::AttrValue::LispValue>(m, "AttrValueLispValue")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::AttrValue::LispValue* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::AttrValue::LispValue();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("code", &org::sem::AttrValue::LispValue::code)
    .def("__eq__",
         static_cast<bool(org::sem::AttrValue::LispValue::*)(org::sem::AttrValue::LispValue const&) const>(&org::sem::AttrValue::LispValue::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::AttrValue::LispValue const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrValue::LispValue const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::AttrValue::Kind>(m, "AttrValueKind", type_registry_guard);
  nanobind::enum_<org::sem::AttrValue::Kind>(m, "AttrValueKind")
    .value("TextValue", org::sem::AttrValue::Kind::TextValue)
    .value("FileReference", org::sem::AttrValue::Kind::FileReference)
    .value("LispValue", org::sem::AttrValue::Kind::LispValue)
    .def("__iter__", [](org::sem::AttrValue::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::AttrValue::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::AttrValue::Kind>();
                     })
    .def("__int__", [](org::sem::AttrValue::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::AttrValue::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::AttrValue::Kind lhs, org::sem::AttrValue::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::AttrValue::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::AttrValue>(m, "AttrValue")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::AttrValue* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::AttrValue();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::AttrValue::name)
    .def_rw("varname", &org::sem::AttrValue::varname)
    .def_rw("span", &org::sem::AttrValue::span)
    .def_rw("isQuoted", &org::sem::AttrValue::isQuoted, R"RAW(If the original value was explicitly quoted in the org-mode code)RAW")
    .def("getBool", static_cast<hstd::Opt<bool>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getBool))
    .def("getInt", static_cast<hstd::Opt<int>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getInt))
    .def("getString", static_cast<hstd::Str(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getString))
    .def("getDouble", static_cast<hstd::Opt<double>(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getDouble))
    .def("__eq__",
         static_cast<bool(org::sem::AttrValue::*)(org::sem::AttrValue const&) const>(&org::sem::AttrValue::operator==),
         nanobind::arg("other"))
    .def("isTextValue", static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isTextValue))
    .def("getTextValue", static_cast<org::sem::AttrValue::TextValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getTextValue))
    .def("isFileReference", static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isFileReference))
    .def("getFileReference", static_cast<org::sem::AttrValue::FileReference&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getFileReference))
    .def("isLispValue", static_cast<bool(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::isLispValue))
    .def("getLispValue", static_cast<org::sem::AttrValue::LispValue&(org::sem::AttrValue::*)()>(&org::sem::AttrValue::getLispValue))
    .def_static("getKindStatic",
                static_cast<org::sem::AttrValue::Kind(*)(org::sem::AttrValue::DataVariant const&)>(&org::sem::AttrValue::getKind),
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::AttrValue::Kind(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::AttrValue::DataVariant const&(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::AttrValue::Kind(org::sem::AttrValue::*)() const>(&org::sem::AttrValue::sub_variant_get_kind))
    .def("__repr__", [](org::sem::AttrValue const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrValue const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::HashTagFlat>(m, "HashTagFlat")
    .def("__init__",
         [](org::sem::HashTagFlat* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::HashTagFlat();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("tags", &org::sem::HashTagFlat::tags)
    .def("__eq__",
         static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator==),
         nanobind::arg("other"))
    .def("__lt__",
         static_cast<bool(org::sem::HashTagFlat::*)(org::sem::HashTagFlat const&) const>(&org::sem::HashTagFlat::operator<),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::HashTagFlat const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::HashTagFlat const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::TodoKeyword::Transition>(m, "TodoKeywordTransition", type_registry_guard);
  nanobind::enum_<org::sem::TodoKeyword::Transition>(m, "TodoKeywordTransition")
    .value("None", org::sem::TodoKeyword::Transition::None)
    .value("NoteWithTimestamp", org::sem::TodoKeyword::Transition::NoteWithTimestamp)
    .value("Timestamp", org::sem::TodoKeyword::Transition::Timestamp)
    .def("__iter__", [](org::sem::TodoKeyword::Transition const& _self) -> org::bind::python::PyEnumIterator<org::sem::TodoKeyword::Transition> {
                     return org::bind::python::PyEnumIterator<org::sem::TodoKeyword::Transition>();
                     })
    .def("__int__", [](org::sem::TodoKeyword::Transition const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::TodoKeyword::Transition const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::TodoKeyword::Transition lhs, org::sem::TodoKeyword::Transition rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::TodoKeyword::Transition it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::TodoKeyword>(m, "TodoKeyword")
    .def("__init__",
         [](org::sem::TodoKeyword* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::TodoKeyword();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::TodoKeyword::name)
    .def_rw("shortcut", &org::sem::TodoKeyword::shortcut)
    .def_rw("onEnter", &org::sem::TodoKeyword::onEnter)
    .def_rw("onLeave", &org::sem::TodoKeyword::onLeave)
    .def("__eq__",
         static_cast<bool(org::sem::TodoKeyword::*)(org::sem::TodoKeyword const&) const>(&org::sem::TodoKeyword::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::TodoKeyword const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::TodoKeyword const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::HashTagText>(m, "HashTagText")
    .def("__init__",
         [](org::sem::HashTagText* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::HashTagText();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("head", &org::sem::HashTagText::head, R"RAW(Main part of the tag)RAW")
    .def_rw("subtags", &org::sem::HashTagText::subtags, R"RAW(List of nested tags)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::HashTagText::*)(org::sem::HashTagText const&) const>(&org::sem::HashTagText::operator==),
         nanobind::arg("other"))
    .def("prefixMatch",
         static_cast<bool(org::sem::HashTagText::*)(hstd::Vec<hstd::Str> const&) const>(&org::sem::HashTagText::prefixMatch),
         nanobind::arg("prefix"),
         R"RAW(Check if list of tag names is a prefix for either of the nested hash tags in this one)RAW")
    .def("getFlatHashes",
         static_cast<hstd::Vec<org::sem::HashTagFlat>(org::sem::HashTagText::*)(bool) const>(&org::sem::HashTagText::getFlatHashes),
         nanobind::arg("withIntermediate") = true,
         R"RAW(Get flat list of expanded hashtags)RAW")
    .def("__repr__", [](org::sem::HashTagText const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::HashTagText const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreePath>(m, "SubtreePath")
    .def("__init__",
         [](org::sem::SubtreePath* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::SubtreePath();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("path", &org::sem::SubtreePath::path)
    .def("__eq__",
         static_cast<bool(org::sem::SubtreePath::*)(org::sem::SubtreePath const&) const>(&org::sem::SubtreePath::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreePath const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreePath const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::Raw>(m, "LinkTargetRaw")
    .def("__init__",
         [](org::sem::LinkTarget::Raw* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LinkTarget::Raw();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::LinkTarget::Raw::text)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::Raw::*)(org::sem::LinkTarget::Raw const&) const>(&org::sem::LinkTarget::Raw::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Raw const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Raw const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::Id>(m, "LinkTargetId")
    .def("__init__",
         [](org::sem::LinkTarget::Id* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LinkTarget::Id();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::LinkTarget::Id::text)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::Id::*)(org::sem::LinkTarget::Id const&) const>(&org::sem::LinkTarget::Id::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Id const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Id const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::CustomId>(m, "LinkTargetCustomId")
    .def("__init__",
         [](org::sem::LinkTarget::CustomId* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LinkTarget::CustomId();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::LinkTarget::CustomId::text)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::CustomId::*)(org::sem::LinkTarget::CustomId const&) const>(&org::sem::LinkTarget::CustomId::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::CustomId const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::CustomId const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::SubtreeTitle>(m, "LinkTargetSubtreeTitle")
    .def("__init__",
         [](org::sem::LinkTarget::SubtreeTitle* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LinkTarget::SubtreeTitle();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("title", &org::sem::LinkTarget::SubtreeTitle::title)
    .def_rw("level", &org::sem::LinkTarget::SubtreeTitle::level)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::SubtreeTitle::*)(org::sem::LinkTarget::SubtreeTitle const&) const>(&org::sem::LinkTarget::SubtreeTitle::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::SubtreeTitle const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::SubtreeTitle const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::Person>(m, "LinkTargetPerson")
    .def("__init__",
         [](org::sem::LinkTarget::Person* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LinkTarget::Person();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::LinkTarget::Person::name)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::Person::*)(org::sem::LinkTarget::Person const&) const>(&org::sem::LinkTarget::Person::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Person const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Person const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::UserProtocol>(m, "LinkTargetUserProtocol")
    .def("__init__",
         [](org::sem::LinkTarget::UserProtocol* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LinkTarget::UserProtocol();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("protocol", &org::sem::LinkTarget::UserProtocol::protocol)
    .def_rw("target", &org::sem::LinkTarget::UserProtocol::target)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::UserProtocol::*)(org::sem::LinkTarget::UserProtocol const&) const>(&org::sem::LinkTarget::UserProtocol::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::UserProtocol const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::UserProtocol const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::Internal>(m, "LinkTargetInternal")
    .def("__init__",
         [](org::sem::LinkTarget::Internal* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LinkTarget::Internal();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("target", &org::sem::LinkTarget::Internal::target)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::Internal::*)(org::sem::LinkTarget::Internal const&) const>(&org::sem::LinkTarget::Internal::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Internal const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Internal const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::Footnote>(m, "LinkTargetFootnote")
    .def("__init__",
         [](org::sem::LinkTarget::Footnote* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LinkTarget::Footnote();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("target", &org::sem::LinkTarget::Footnote::target)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::Footnote::*)(org::sem::LinkTarget::Footnote const&) const>(&org::sem::LinkTarget::Footnote::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Footnote const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Footnote const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::File>(m, "LinkTargetFile")
    .def("__init__",
         [](org::sem::LinkTarget::File* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LinkTarget::File();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("file", &org::sem::LinkTarget::File::file)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::File::*)(org::sem::LinkTarget::File const&) const>(&org::sem::LinkTarget::File::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::File const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::File const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::LinkTarget::Attachment>(m, "LinkTargetAttachment")
    .def("__init__",
         [](org::sem::LinkTarget::Attachment* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LinkTarget::Attachment();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("file", &org::sem::LinkTarget::Attachment::file)
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::Attachment::*)(org::sem::LinkTarget::Attachment const&) const>(&org::sem::LinkTarget::Attachment::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::LinkTarget::Attachment const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget::Attachment const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::LinkTarget::Kind>(m, "LinkTargetKind", type_registry_guard);
  nanobind::enum_<org::sem::LinkTarget::Kind>(m, "LinkTargetKind")
    .value("Raw", org::sem::LinkTarget::Kind::Raw)
    .value("Id", org::sem::LinkTarget::Kind::Id)
    .value("CustomId", org::sem::LinkTarget::Kind::CustomId)
    .value("SubtreeTitle", org::sem::LinkTarget::Kind::SubtreeTitle)
    .value("Person", org::sem::LinkTarget::Kind::Person)
    .value("UserProtocol", org::sem::LinkTarget::Kind::UserProtocol)
    .value("Internal", org::sem::LinkTarget::Kind::Internal)
    .value("Footnote", org::sem::LinkTarget::Kind::Footnote)
    .value("File", org::sem::LinkTarget::Kind::File)
    .value("Attachment", org::sem::LinkTarget::Kind::Attachment)
    .def("__iter__", [](org::sem::LinkTarget::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::LinkTarget::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::LinkTarget::Kind>();
                     })
    .def("__int__", [](org::sem::LinkTarget::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::LinkTarget::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::LinkTarget::Kind lhs, org::sem::LinkTarget::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::LinkTarget::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::LinkTarget>(m, "LinkTarget")
    .def("__init__",
         [](org::sem::LinkTarget* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::LinkTarget();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::sem::LinkTarget::*)(org::sem::LinkTarget const&) const>(&org::sem::LinkTarget::operator==),
         nanobind::arg("other"))
    .def("isRaw", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isRaw))
    .def("getRaw", static_cast<org::sem::LinkTarget::Raw&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getRaw))
    .def("isId", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isId))
    .def("getId", static_cast<org::sem::LinkTarget::Id&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getId))
    .def("isCustomId", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isCustomId))
    .def("getCustomId", static_cast<org::sem::LinkTarget::CustomId&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getCustomId))
    .def("isSubtreeTitle", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isSubtreeTitle))
    .def("getSubtreeTitle", static_cast<org::sem::LinkTarget::SubtreeTitle&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getSubtreeTitle))
    .def("isPerson", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isPerson))
    .def("getPerson", static_cast<org::sem::LinkTarget::Person&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getPerson))
    .def("isUserProtocol", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isUserProtocol))
    .def("getUserProtocol", static_cast<org::sem::LinkTarget::UserProtocol&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getUserProtocol))
    .def("isInternal", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isInternal))
    .def("getInternal", static_cast<org::sem::LinkTarget::Internal&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getInternal))
    .def("isFootnote", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isFootnote))
    .def("getFootnote", static_cast<org::sem::LinkTarget::Footnote&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getFootnote))
    .def("isFile", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isFile))
    .def("getFile", static_cast<org::sem::LinkTarget::File&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getFile))
    .def("isAttachment", static_cast<bool(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::isAttachment))
    .def("getAttachment", static_cast<org::sem::LinkTarget::Attachment&(org::sem::LinkTarget::*)()>(&org::sem::LinkTarget::getAttachment))
    .def_static("getKindStatic",
                static_cast<org::sem::LinkTarget::Kind(*)(org::sem::LinkTarget::Data const&)>(&org::sem::LinkTarget::getKind),
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::LinkTarget::Kind(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::LinkTarget::Data const&(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::LinkTarget::Kind(org::sem::LinkTarget::*)() const>(&org::sem::LinkTarget::sub_variant_get_kind))
    .def("__repr__", [](org::sem::LinkTarget const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::LinkTarget const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::SubtreeLogHead::Priority::Action>(m, "SubtreeLogHeadPriorityAction", type_registry_guard);
  nanobind::enum_<org::sem::SubtreeLogHead::Priority::Action>(m, "SubtreeLogHeadPriorityAction")
    .value("Added", org::sem::SubtreeLogHead::Priority::Action::Added, R"RAW(`Priority B added on [timestamp]`)RAW")
    .value("Removed", org::sem::SubtreeLogHead::Priority::Action::Removed, R"RAW(`Priority C removed on [timestamp]`)RAW")
    .value("Changed", org::sem::SubtreeLogHead::Priority::Action::Changed, R"RAW(`Priority B changed from C on [timestamp]`)RAW")
    .def("__iter__", [](org::sem::SubtreeLogHead::Priority::Action const& _self) -> org::bind::python::PyEnumIterator<org::sem::SubtreeLogHead::Priority::Action> {
                     return org::bind::python::PyEnumIterator<org::sem::SubtreeLogHead::Priority::Action>();
                     })
    .def("__int__", [](org::sem::SubtreeLogHead::Priority::Action const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::SubtreeLogHead::Priority::Action const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::SubtreeLogHead::Priority::Action lhs, org::sem::SubtreeLogHead::Priority::Action rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::SubtreeLogHead::Priority::Action it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::SubtreeLogHead::Priority>(m, "SubtreeLogHeadPriority")
    .def("__init__",
         [](org::sem::SubtreeLogHead::Priority* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::SubtreeLogHead::Priority();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("oldPriority", &org::sem::SubtreeLogHead::Priority::oldPriority, R"RAW(Previous priority for change and removal)RAW")
    .def_rw("newPriority", &org::sem::SubtreeLogHead::Priority::newPriority, R"RAW(New priority for change and addition)RAW")
    .def_rw("on", &org::sem::SubtreeLogHead::Priority::on, R"RAW(When priority was changed)RAW")
    .def_rw("action", &org::sem::SubtreeLogHead::Priority::action, R"RAW(Which action taken)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::Priority::*)(org::sem::SubtreeLogHead::Priority const&) const>(&org::sem::SubtreeLogHead::Priority::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Priority const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Priority const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLogHead::Note>(m, "SubtreeLogHeadNote")
    .def("__init__",
         [](org::sem::SubtreeLogHead::Note* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::SubtreeLogHead::Note();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("on", &org::sem::SubtreeLogHead::Note::on, R"RAW(Where log was taken)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::Note::*)(org::sem::SubtreeLogHead::Note const&) const>(&org::sem::SubtreeLogHead::Note::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Note const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Note const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLogHead::Refile>(m, "SubtreeLogHeadRefile")
    .def("__init__",
         [](org::sem::SubtreeLogHead::Refile* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::SubtreeLogHead::Refile();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("on", &org::sem::SubtreeLogHead::Refile::on, R"RAW(When the refiling happened)RAW")
    .def_rw("from_", &org::sem::SubtreeLogHead::Refile::from, R"RAW(Link to the original subtree)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::Refile::*)(org::sem::SubtreeLogHead::Refile const&) const>(&org::sem::SubtreeLogHead::Refile::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Refile const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Refile const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLogHead::Clock>(m, "SubtreeLogHeadClock")
    .def("__init__",
         [](org::sem::SubtreeLogHead::Clock* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::SubtreeLogHead::Clock();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("from_", &org::sem::SubtreeLogHead::Clock::from, R"RAW(Clock start time)RAW")
    .def_rw("to", &org::sem::SubtreeLogHead::Clock::to, R"RAW(Optional end of the clock)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::Clock::*)(org::sem::SubtreeLogHead::Clock const&) const>(&org::sem::SubtreeLogHead::Clock::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Clock const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Clock const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLogHead::State>(m, "SubtreeLogHeadState")
    .def("__init__",
         [](org::sem::SubtreeLogHead::State* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::SubtreeLogHead::State();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("from_", &org::sem::SubtreeLogHead::State::from)
    .def_rw("to", &org::sem::SubtreeLogHead::State::to)
    .def_rw("on", &org::sem::SubtreeLogHead::State::on)
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::State::*)(org::sem::SubtreeLogHead::State const&) const>(&org::sem::SubtreeLogHead::State::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::State const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::State const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLogHead::Deadline>(m, "SubtreeLogHeadDeadline")
    .def("__init__",
         [](org::sem::SubtreeLogHead::Deadline* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::SubtreeLogHead::Deadline();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("from_", &org::sem::SubtreeLogHead::Deadline::from)
    .def_rw("to", &org::sem::SubtreeLogHead::Deadline::to)
    .def_rw("on", &org::sem::SubtreeLogHead::Deadline::on)
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::Deadline::*)(org::sem::SubtreeLogHead::Deadline const&) const>(&org::sem::SubtreeLogHead::Deadline::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Deadline const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Deadline const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLogHead::Schedule>(m, "SubtreeLogHeadSchedule")
    .def("__init__",
         [](org::sem::SubtreeLogHead::Schedule* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::SubtreeLogHead::Schedule();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("from_", &org::sem::SubtreeLogHead::Schedule::from)
    .def_rw("to", &org::sem::SubtreeLogHead::Schedule::to)
    .def_rw("on", &org::sem::SubtreeLogHead::Schedule::on)
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::Schedule::*)(org::sem::SubtreeLogHead::Schedule const&) const>(&org::sem::SubtreeLogHead::Schedule::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Schedule const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Schedule const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLogHead::Tag>(m, "SubtreeLogHeadTag")
    .def("__init__",
         [](org::sem::SubtreeLogHead::Tag* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::SubtreeLogHead::Tag();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("on", &org::sem::SubtreeLogHead::Tag::on, R"RAW(When the log was assigned)RAW")
    .def_rw("tag", &org::sem::SubtreeLogHead::Tag::tag, R"RAW(Tag in question)RAW")
    .def_rw("added", &org::sem::SubtreeLogHead::Tag::added, R"RAW(Added/removed?)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::Tag::*)(org::sem::SubtreeLogHead::Tag const&) const>(&org::sem::SubtreeLogHead::Tag::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Tag const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Tag const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLogHead::Unknown>(m, "SubtreeLogHeadUnknown")
    .def("__init__",
         [](org::sem::SubtreeLogHead::Unknown* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::SubtreeLogHead::Unknown();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::Unknown::*)(org::sem::SubtreeLogHead::Unknown const&) const>(&org::sem::SubtreeLogHead::Unknown::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeLogHead::Unknown const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead::Unknown const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::SubtreeLogHead::Kind>(m, "SubtreeLogHeadKind", type_registry_guard);
  nanobind::enum_<org::sem::SubtreeLogHead::Kind>(m, "SubtreeLogHeadKind")
    .value("Priority", org::sem::SubtreeLogHead::Kind::Priority)
    .value("Note", org::sem::SubtreeLogHead::Kind::Note)
    .value("Refile", org::sem::SubtreeLogHead::Kind::Refile)
    .value("Clock", org::sem::SubtreeLogHead::Kind::Clock)
    .value("State", org::sem::SubtreeLogHead::Kind::State)
    .value("Deadline", org::sem::SubtreeLogHead::Kind::Deadline)
    .value("Schedule", org::sem::SubtreeLogHead::Kind::Schedule)
    .value("Tag", org::sem::SubtreeLogHead::Kind::Tag)
    .value("Unknown", org::sem::SubtreeLogHead::Kind::Unknown)
    .def("__iter__", [](org::sem::SubtreeLogHead::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::SubtreeLogHead::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::SubtreeLogHead::Kind>();
                     })
    .def("__int__", [](org::sem::SubtreeLogHead::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::SubtreeLogHead::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::SubtreeLogHead::Kind lhs, org::sem::SubtreeLogHead::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::SubtreeLogHead::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::SubtreeLogHead>(m, "SubtreeLogHead")
    .def("__init__",
         [](org::sem::SubtreeLogHead* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::SubtreeLogHead();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeLogHead::*)(org::sem::SubtreeLogHead const&) const>(&org::sem::SubtreeLogHead::operator==),
         nanobind::arg("other"))
    .def("isPriority", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isPriority))
    .def("getPriority", static_cast<org::sem::SubtreeLogHead::Priority&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getPriority))
    .def("isNote", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isNote))
    .def("getNote", static_cast<org::sem::SubtreeLogHead::Note&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getNote))
    .def("isRefile", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isRefile))
    .def("getRefile", static_cast<org::sem::SubtreeLogHead::Refile&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getRefile))
    .def("isClock", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isClock))
    .def("getClock", static_cast<org::sem::SubtreeLogHead::Clock&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getClock))
    .def("isState", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isState))
    .def("getState", static_cast<org::sem::SubtreeLogHead::State&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getState))
    .def("isDeadline", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isDeadline))
    .def("getDeadline", static_cast<org::sem::SubtreeLogHead::Deadline&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getDeadline))
    .def("isSchedule", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isSchedule))
    .def("getSchedule", static_cast<org::sem::SubtreeLogHead::Schedule&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getSchedule))
    .def("isTag", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isTag))
    .def("getTag", static_cast<org::sem::SubtreeLogHead::Tag&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getTag))
    .def("isUnknown", static_cast<bool(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::isUnknown))
    .def("getUnknown", static_cast<org::sem::SubtreeLogHead::Unknown&(org::sem::SubtreeLogHead::*)()>(&org::sem::SubtreeLogHead::getUnknown))
    .def_static("getLogKindStatic",
                static_cast<org::sem::SubtreeLogHead::Kind(*)(org::sem::SubtreeLogHead::LogEntry const&)>(&org::sem::SubtreeLogHead::getLogKind),
                nanobind::arg("__input"))
    .def("getLogKind", static_cast<org::sem::SubtreeLogHead::Kind(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::getLogKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::SubtreeLogHead::LogEntry const&(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::SubtreeLogHead::Kind(org::sem::SubtreeLogHead::*)() const>(&org::sem::SubtreeLogHead::sub_variant_get_kind))
    .def("__repr__", [](org::sem::SubtreeLogHead const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLogHead const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeCompletion>(m, "SubtreeCompletion")
    .def("__init__",
         [](org::sem::SubtreeCompletion* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::SubtreeCompletion();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("done", &org::sem::SubtreeCompletion::done, R"RAW(Number of completed tasks)RAW")
    .def_rw("full", &org::sem::SubtreeCompletion::full, R"RAW(Full number of tasks)RAW")
    .def_rw("isPercent", &org::sem::SubtreeCompletion::isPercent, R"RAW(Use fraction or percent to display completion)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::SubtreeCompletion::*)(org::sem::SubtreeCompletion const&) const>(&org::sem::SubtreeCompletion::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreeCompletion const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeCompletion const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::AttrList>(m, "AttrList")
    .def("__init__",
         [](org::sem::AttrList* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::AttrList();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("items", &org::sem::AttrList::items)
    .def("__eq__",
         static_cast<bool(org::sem::AttrList::*)(org::sem::AttrList const&) const>(&org::sem::AttrList::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::AttrList const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrList const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::AttrGroup>(m, "AttrGroup")
    .def("__init__",
         [](org::sem::AttrGroup* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::AttrGroup();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("positional", &org::sem::AttrGroup::positional, R"RAW(Positional arguments with no keys)RAW")
    .def_rw("named", &org::sem::AttrGroup::named, R"RAW(Stored key-value mapping)RAW")
    .def("getFlatArgs", static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getFlatArgs))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::AttrGroup::getAttrs),
         nanobind::arg("key") = std::nullopt)
    .def("setNamedAttr",
         static_cast<void(org::sem::AttrGroup::*)(hstd::Str const&, hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setNamedAttr),
         nanobind::arg("key"),
         nanobind::arg("attrs"))
    .def("setPositionalAttr",
         static_cast<void(org::sem::AttrGroup::*)(hstd::Vec<org::sem::AttrValue> const&)>(&org::sem::AttrGroup::setPositionalAttr),
         nanobind::arg("items"))
    .def("getPositionalSize", static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getPositionalSize))
    .def("getNamedSize", static_cast<int(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getNamedSize))
    .def("isEmpty", static_cast<bool(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::isEmpty))
    .def("getAll", static_cast<org::sem::AttrList(org::sem::AttrGroup::*)() const>(&org::sem::AttrGroup::getAll))
    .def("atPositional",
         static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::atPositional),
         nanobind::arg("index"))
    .def("getPositional",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(int) const>(&org::sem::AttrGroup::getPositional),
         nanobind::arg("index"))
    .def("atNamed",
         static_cast<org::sem::AttrList const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atNamed),
         nanobind::arg("index"))
    .def("getNamed",
         static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getNamed),
         nanobind::arg("index"))
    .def("atFirstNamed",
         static_cast<org::sem::AttrValue const&(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstNamed),
         nanobind::arg("index"))
    .def("getFirstNamed",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstNamed),
         nanobind::arg("index"))
    .def("atVarNamed",
         static_cast<org::sem::AttrList(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atVarNamed),
         nanobind::arg("index"))
    .def("getVarNamed",
         static_cast<hstd::Opt<org::sem::AttrList>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getVarNamed),
         nanobind::arg("index"))
    .def("atFirstVarNamed",
         static_cast<org::sem::AttrValue(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::atFirstVarNamed),
         nanobind::arg("index"))
    .def("getFirstVarNamed",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::AttrGroup::*)(hstd::Str const&) const>(&org::sem::AttrGroup::getFirstVarNamed),
         nanobind::arg("index"))
    .def("__eq__",
         static_cast<bool(org::sem::AttrGroup::*)(org::sem::AttrGroup const&) const>(&org::sem::AttrGroup::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::AttrGroup const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AttrGroup const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::OrgCodeEvalInput::Var>(m, "OrgCodeEvalInputVar")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::OrgCodeEvalInput::Var* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::OrgCodeEvalInput::Var();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::OrgCodeEvalInput::Var::name)
    .def_rw("value", &org::sem::OrgCodeEvalInput::Var::value)
    .def("__eq__",
         static_cast<bool(org::sem::OrgCodeEvalInput::Var::*)(org::sem::OrgCodeEvalInput::Var const&) const>(&org::sem::OrgCodeEvalInput::Var::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::OrgCodeEvalInput::Var const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgCodeEvalInput::Var const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::OrgCodeEvalInput::ResultType>(m, "OrgCodeEvalInputResultType", type_registry_guard);
  nanobind::enum_<org::sem::OrgCodeEvalInput::ResultType>(m, "OrgCodeEvalInputResultType")
    .value("None", org::sem::OrgCodeEvalInput::ResultType::None)
    .value("Table", org::sem::OrgCodeEvalInput::ResultType::Table, R"RAW(Interpret the results as an Org table. If the result is a single value, create a table with one row and one column.)RAW")
    .value("List", org::sem::OrgCodeEvalInput::ResultType::List, R"RAW(Interpret the results as an Org list. If the result is a single value, create a list of one element.)RAW")
    .value("Scalar", org::sem::OrgCodeEvalInput::ResultType::Scalar, R"RAW(Interpret literally and insert as quoted text. Do not create a table.)RAW")
    .value("SaveFile", org::sem::OrgCodeEvalInput::ResultType::SaveFile, R"RAW(Interpret as a filename. Save the results of execution of the code block to that file, then insert a link to it.)RAW")
    .def("__iter__", [](org::sem::OrgCodeEvalInput::ResultType const& _self) -> org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultType> {
                     return org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultType>();
                     })
    .def("__int__", [](org::sem::OrgCodeEvalInput::ResultType const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::OrgCodeEvalInput::ResultType const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::OrgCodeEvalInput::ResultType lhs, org::sem::OrgCodeEvalInput::ResultType rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::OrgCodeEvalInput::ResultType it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org::sem::OrgCodeEvalInput::ResultFormat>(m, "OrgCodeEvalInputResultFormat", type_registry_guard);
  nanobind::enum_<org::sem::OrgCodeEvalInput::ResultFormat>(m, "OrgCodeEvalInputResultFormat")
    .value("None", org::sem::OrgCodeEvalInput::ResultFormat::None)
    .value("Raw", org::sem::OrgCodeEvalInput::ResultFormat::Raw, R"RAW(Interpreted as raw Org mode. Inserted directly into the buffer.)RAW")
    .value("Code", org::sem::OrgCodeEvalInput::ResultFormat::Code, R"RAW(Result enclosed in a code block.)RAW")
    .value("Drawer", org::sem::OrgCodeEvalInput::ResultFormat::Drawer, R"RAW(Results are added directly to the Org file as with ‘raw’, but are wrapped in a ‘RESULTS’ drawer or results macro (for inline code blocks), for later scripting and automated processing.)RAW")
    .value("ExportType", org::sem::OrgCodeEvalInput::ResultFormat::ExportType, R"RAW(Results enclosed in a ‘BEGIN_EXPORT’ block.)RAW")
    .value("Link", org::sem::OrgCodeEvalInput::ResultFormat::Link)
    .def("__iter__", [](org::sem::OrgCodeEvalInput::ResultFormat const& _self) -> org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultFormat> {
                     return org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultFormat>();
                     })
    .def("__int__", [](org::sem::OrgCodeEvalInput::ResultFormat const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::OrgCodeEvalInput::ResultFormat const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::OrgCodeEvalInput::ResultFormat lhs, org::sem::OrgCodeEvalInput::ResultFormat rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::OrgCodeEvalInput::ResultFormat it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org::sem::OrgCodeEvalInput::ResultHandling>(m, "OrgCodeEvalInputResultHandling", type_registry_guard);
  nanobind::enum_<org::sem::OrgCodeEvalInput::ResultHandling>(m, "OrgCodeEvalInputResultHandling")
    .value("None", org::sem::OrgCodeEvalInput::ResultHandling::None)
    .value("Replace", org::sem::OrgCodeEvalInput::ResultHandling::Replace)
    .value("Silent", org::sem::OrgCodeEvalInput::ResultHandling::Silent)
    .value("Discard", org::sem::OrgCodeEvalInput::ResultHandling::Discard)
    .value("Append", org::sem::OrgCodeEvalInput::ResultHandling::Append)
    .value("Prepend", org::sem::OrgCodeEvalInput::ResultHandling::Prepend)
    .def("__iter__", [](org::sem::OrgCodeEvalInput::ResultHandling const& _self) -> org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultHandling> {
                     return org::bind::python::PyEnumIterator<org::sem::OrgCodeEvalInput::ResultHandling>();
                     })
    .def("__int__", [](org::sem::OrgCodeEvalInput::ResultHandling const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::OrgCodeEvalInput::ResultHandling const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::OrgCodeEvalInput::ResultHandling lhs, org::sem::OrgCodeEvalInput::ResultHandling rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::OrgCodeEvalInput::ResultHandling it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::OrgCodeEvalInput>(m, "OrgCodeEvalInput")
    .def("__init__",
         [](org::sem::OrgCodeEvalInput* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::OrgCodeEvalInput();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("blockAttrs", &org::sem::OrgCodeEvalInput::blockAttrs)
    .def_rw("tangledCode", &org::sem::OrgCodeEvalInput::tangledCode)
    .def_rw("exportType", &org::sem::OrgCodeEvalInput::exportType)
    .def_rw("resultType", &org::sem::OrgCodeEvalInput::resultType)
    .def_rw("resultFormat", &org::sem::OrgCodeEvalInput::resultFormat)
    .def_rw("resultHandling", &org::sem::OrgCodeEvalInput::resultHandling)
    .def_rw("language", &org::sem::OrgCodeEvalInput::language)
    .def_rw("argList", &org::sem::OrgCodeEvalInput::argList)
    .def("__eq__",
         static_cast<bool(org::sem::OrgCodeEvalInput::*)(org::sem::OrgCodeEvalInput const&) const>(&org::sem::OrgCodeEvalInput::operator==),
         nanobind::arg("other"))
    .def("getVariable",
         static_cast<hstd::Opt<org::sem::OrgCodeEvalInput::Var>(org::sem::OrgCodeEvalInput::*)(hstd::Str const&) const>(&org::sem::OrgCodeEvalInput::getVariable),
         nanobind::arg("name"))
    .def("__repr__", [](org::sem::OrgCodeEvalInput const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgCodeEvalInput const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::OrgCodeEvalOutput>(m, "OrgCodeEvalOutput")
    .def("__init__",
         [](org::sem::OrgCodeEvalOutput* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::OrgCodeEvalOutput();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("stdoutText", &org::sem::OrgCodeEvalOutput::stdoutText)
    .def_rw("stderrText", &org::sem::OrgCodeEvalOutput::stderrText)
    .def_rw("code", &org::sem::OrgCodeEvalOutput::code)
    .def_rw("cmd", &org::sem::OrgCodeEvalOutput::cmd, R"RAW(Command evaluated, if none then eval output did not run CLI subprocess)RAW")
    .def_rw("args", &org::sem::OrgCodeEvalOutput::args, R"RAW(Command line arguments provided for execution)RAW")
    .def_rw("cwd", &org::sem::OrgCodeEvalOutput::cwd, R"RAW(Working directory where command was executed)RAW")
    .def_rw("appliedHeaderArg", &org::sem::OrgCodeEvalOutput::appliedHeaderArg, R"RAW(Final set of header arguments applied during evaluation)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::OrgCodeEvalOutput::*)(org::sem::OrgCodeEvalOutput const&) const>(&org::sem::OrgCodeEvalOutput::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::OrgCodeEvalOutput const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgCodeEvalOutput const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::ColumnView::Summary::CheckboxAggregate::Kind>(m, "ColumnViewSummaryCheckboxAggregateKind", type_registry_guard);
  nanobind::enum_<org::sem::ColumnView::Summary::CheckboxAggregate::Kind>(m, "ColumnViewSummaryCheckboxAggregateKind")
    .value("IfAllNested", org::sem::ColumnView::Summary::CheckboxAggregate::Kind::IfAllNested)
    .value("AggregateFractionRec", org::sem::ColumnView::Summary::CheckboxAggregate::Kind::AggregateFractionRec)
    .value("AggregatePercentRec", org::sem::ColumnView::Summary::CheckboxAggregate::Kind::AggregatePercentRec)
    .def("__iter__", [](org::sem::ColumnView::Summary::CheckboxAggregate::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::CheckboxAggregate::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::CheckboxAggregate::Kind>();
                     })
    .def("__int__", [](org::sem::ColumnView::Summary::CheckboxAggregate::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::ColumnView::Summary::CheckboxAggregate::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::ColumnView::Summary::CheckboxAggregate::Kind lhs, org::sem::ColumnView::Summary::CheckboxAggregate::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::ColumnView::Summary::CheckboxAggregate::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::ColumnView::Summary::CheckboxAggregate>(m, "ColumnViewSummaryCheckboxAggregate")
    .def("__init__",
         [](org::sem::ColumnView::Summary::CheckboxAggregate* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::ColumnView::Summary::CheckboxAggregate();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("kind", &org::sem::ColumnView::Summary::CheckboxAggregate::kind)
    .def("__eq__",
         static_cast<bool(org::sem::ColumnView::Summary::CheckboxAggregate::*)(org::sem::ColumnView::Summary::CheckboxAggregate const&) const>(&org::sem::ColumnView::Summary::CheckboxAggregate::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::ColumnView::Summary::CheckboxAggregate const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColumnView::Summary::CheckboxAggregate const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::ColumnView::Summary::MathAggregate::Kind>(m, "ColumnViewSummaryMathAggregateKind", type_registry_guard);
  nanobind::enum_<org::sem::ColumnView::Summary::MathAggregate::Kind>(m, "ColumnViewSummaryMathAggregateKind")
    .value("Min", org::sem::ColumnView::Summary::MathAggregate::Kind::Min)
    .value("Max", org::sem::ColumnView::Summary::MathAggregate::Kind::Max)
    .value("Mean", org::sem::ColumnView::Summary::MathAggregate::Kind::Mean)
    .value("Sum", org::sem::ColumnView::Summary::MathAggregate::Kind::Sum)
    .value("LowHighEst", org::sem::ColumnView::Summary::MathAggregate::Kind::LowHighEst)
    .def("__iter__", [](org::sem::ColumnView::Summary::MathAggregate::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::MathAggregate::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::MathAggregate::Kind>();
                     })
    .def("__int__", [](org::sem::ColumnView::Summary::MathAggregate::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::ColumnView::Summary::MathAggregate::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::ColumnView::Summary::MathAggregate::Kind lhs, org::sem::ColumnView::Summary::MathAggregate::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::ColumnView::Summary::MathAggregate::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::ColumnView::Summary::MathAggregate>(m, "ColumnViewSummaryMathAggregate")
    .def("__init__",
         [](org::sem::ColumnView::Summary::MathAggregate* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::ColumnView::Summary::MathAggregate();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("kind", &org::sem::ColumnView::Summary::MathAggregate::kind)
    .def_rw("formatDigits", &org::sem::ColumnView::Summary::MathAggregate::formatDigits)
    .def_rw("formatPrecision", &org::sem::ColumnView::Summary::MathAggregate::formatPrecision)
    .def("__eq__",
         static_cast<bool(org::sem::ColumnView::Summary::MathAggregate::*)(org::sem::ColumnView::Summary::MathAggregate const&) const>(&org::sem::ColumnView::Summary::MathAggregate::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::ColumnView::Summary::MathAggregate const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColumnView::Summary::MathAggregate const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::ColumnView::Summary::Kind>(m, "ColumnViewSummaryKind", type_registry_guard);
  nanobind::enum_<org::sem::ColumnView::Summary::Kind>(m, "ColumnViewSummaryKind")
    .value("CheckboxAggregate", org::sem::ColumnView::Summary::Kind::CheckboxAggregate)
    .value("MathAggregate", org::sem::ColumnView::Summary::Kind::MathAggregate)
    .def("__iter__", [](org::sem::ColumnView::Summary::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::ColumnView::Summary::Kind>();
                     })
    .def("__int__", [](org::sem::ColumnView::Summary::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::ColumnView::Summary::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::ColumnView::Summary::Kind lhs, org::sem::ColumnView::Summary::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::ColumnView::Summary::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::ColumnView::Summary>(m, "ColumnViewSummary")
    .def("__init__",
         [](org::sem::ColumnView::Summary* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::ColumnView::Summary();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::sem::ColumnView::Summary::*)(org::sem::ColumnView::Summary const&) const>(&org::sem::ColumnView::Summary::operator==),
         nanobind::arg("other"))
    .def("isCheckboxAggregate", static_cast<bool(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::isCheckboxAggregate))
    .def("getCheckboxAggregate", static_cast<org::sem::ColumnView::Summary::CheckboxAggregate&(org::sem::ColumnView::Summary::*)()>(&org::sem::ColumnView::Summary::getCheckboxAggregate))
    .def("isMathAggregate", static_cast<bool(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::isMathAggregate))
    .def("getMathAggregate", static_cast<org::sem::ColumnView::Summary::MathAggregate&(org::sem::ColumnView::Summary::*)()>(&org::sem::ColumnView::Summary::getMathAggregate))
    .def_static("getKindStatic",
                static_cast<org::sem::ColumnView::Summary::Kind(*)(org::sem::ColumnView::Summary::Data const&)>(&org::sem::ColumnView::Summary::getKind),
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::ColumnView::Summary::Kind(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::ColumnView::Summary::Data const&(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::ColumnView::Summary::Kind(org::sem::ColumnView::Summary::*)() const>(&org::sem::ColumnView::Summary::sub_variant_get_kind))
    .def("__repr__", [](org::sem::ColumnView::Summary const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColumnView::Summary const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::ColumnView::Column>(m, "ColumnViewColumn")
    .def("__init__",
         [](org::sem::ColumnView::Column* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::ColumnView::Column();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("summary", &org::sem::ColumnView::Column::summary)
    .def_rw("width", &org::sem::ColumnView::Column::width)
    .def_rw("property", &org::sem::ColumnView::Column::property)
    .def_rw("propertyTitle", &org::sem::ColumnView::Column::propertyTitle)
    .def("__eq__",
         static_cast<bool(org::sem::ColumnView::Column::*)(org::sem::ColumnView::Column const&) const>(&org::sem::ColumnView::Column::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::ColumnView::Column const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColumnView::Column const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::ColumnView>(m, "ColumnView")
    .def("__init__",
         [](org::sem::ColumnView* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::ColumnView();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("columns", &org::sem::ColumnView::columns)
    .def("__eq__",
         static_cast<bool(org::sem::ColumnView::*)(org::sem::ColumnView const&) const>(&org::sem::ColumnView::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::ColumnView const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColumnView const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockCodeLine::Part::Raw>(m, "BlockCodeLinePartRaw")
    .def("__init__",
         [](org::sem::BlockCodeLine::Part::Raw* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::BlockCodeLine::Part::Raw();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("code", &org::sem::BlockCodeLine::Part::Raw::code)
    .def("__eq__",
         static_cast<bool(org::sem::BlockCodeLine::Part::Raw::*)(org::sem::BlockCodeLine::Part::Raw const&) const>(&org::sem::BlockCodeLine::Part::Raw::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::BlockCodeLine::Part::Raw const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeLine::Part::Raw const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockCodeLine::Part::Callout>(m, "BlockCodeLinePartCallout")
    .def("__init__",
         [](org::sem::BlockCodeLine::Part::Callout* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::BlockCodeLine::Part::Callout();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::BlockCodeLine::Part::Callout::name)
    .def("__eq__",
         static_cast<bool(org::sem::BlockCodeLine::Part::Callout::*)(org::sem::BlockCodeLine::Part::Callout const&) const>(&org::sem::BlockCodeLine::Part::Callout::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::BlockCodeLine::Part::Callout const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeLine::Part::Callout const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockCodeLine::Part::Tangle>(m, "BlockCodeLinePartTangle")
    .def("__init__",
         [](org::sem::BlockCodeLine::Part::Tangle* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::BlockCodeLine::Part::Tangle();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("target", &org::sem::BlockCodeLine::Part::Tangle::target)
    .def("__eq__",
         static_cast<bool(org::sem::BlockCodeLine::Part::Tangle::*)(org::sem::BlockCodeLine::Part::Tangle const&) const>(&org::sem::BlockCodeLine::Part::Tangle::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::BlockCodeLine::Part::Tangle const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeLine::Part::Tangle const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::BlockCodeLine::Part::Kind>(m, "BlockCodeLinePartKind", type_registry_guard);
  nanobind::enum_<org::sem::BlockCodeLine::Part::Kind>(m, "BlockCodeLinePartKind")
    .value("Raw", org::sem::BlockCodeLine::Part::Kind::Raw)
    .value("Callout", org::sem::BlockCodeLine::Part::Kind::Callout)
    .value("Tangle", org::sem::BlockCodeLine::Part::Kind::Tangle)
    .def("__iter__", [](org::sem::BlockCodeLine::Part::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::BlockCodeLine::Part::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::BlockCodeLine::Part::Kind>();
                     })
    .def("__int__", [](org::sem::BlockCodeLine::Part::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::BlockCodeLine::Part::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::BlockCodeLine::Part::Kind lhs, org::sem::BlockCodeLine::Part::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::BlockCodeLine::Part::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::BlockCodeLine::Part>(m, "BlockCodeLinePart")
    .def("__init__",
         [](org::sem::BlockCodeLine::Part* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::BlockCodeLine::Part();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::sem::BlockCodeLine::Part::*)(org::sem::BlockCodeLine::Part const&) const>(&org::sem::BlockCodeLine::Part::operator==),
         nanobind::arg("other"))
    .def("isRaw", static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isRaw))
    .def("getRaw", static_cast<org::sem::BlockCodeLine::Part::Raw&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getRaw))
    .def("isCallout", static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isCallout))
    .def("getCallout", static_cast<org::sem::BlockCodeLine::Part::Callout&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getCallout))
    .def("isTangle", static_cast<bool(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::isTangle))
    .def("getTangle", static_cast<org::sem::BlockCodeLine::Part::Tangle&(org::sem::BlockCodeLine::Part::*)()>(&org::sem::BlockCodeLine::Part::getTangle))
    .def_static("getKindStatic",
                static_cast<org::sem::BlockCodeLine::Part::Kind(*)(org::sem::BlockCodeLine::Part::Data const&)>(&org::sem::BlockCodeLine::Part::getKind),
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::BlockCodeLine::Part::Kind(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::BlockCodeLine::Part::Data const&(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::BlockCodeLine::Part::Kind(org::sem::BlockCodeLine::Part::*)() const>(&org::sem::BlockCodeLine::Part::sub_variant_get_kind))
    .def("__repr__", [](org::sem::BlockCodeLine::Part const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeLine::Part const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockCodeLine>(m, "BlockCodeLine")
    .def("__init__",
         [](org::sem::BlockCodeLine* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::BlockCodeLine();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("parts", &org::sem::BlockCodeLine::parts, R"RAW(parts of the single line)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::BlockCodeLine::*)(org::sem::BlockCodeLine const&) const>(&org::sem::BlockCodeLine::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::BlockCodeLine const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeLine const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::DocumentExportConfig::TaskExport>(m, "DocumentExportConfigTaskExport")
    .def("__init__",
         [](org::sem::DocumentExportConfig::TaskExport* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::DocumentExportConfig::TaskExport();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("taskWhitelist", &org::sem::DocumentExportConfig::TaskExport::taskWhitelist)
    .def("__eq__",
         static_cast<bool(org::sem::DocumentExportConfig::TaskExport::*)(org::sem::DocumentExportConfig::TaskExport const&) const>(&org::sem::DocumentExportConfig::TaskExport::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::DocumentExportConfig::TaskExport const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentExportConfig::TaskExport const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::DocumentExportConfig::TagExport>(m, "DocumentExportConfigTagExport", type_registry_guard);
  nanobind::enum_<org::sem::DocumentExportConfig::TagExport>(m, "DocumentExportConfigTagExport")
    .value("None", org::sem::DocumentExportConfig::TagExport::None)
    .value("All", org::sem::DocumentExportConfig::TagExport::All)
    .value("NotInToc", org::sem::DocumentExportConfig::TagExport::NotInToc, R"RAW(Export tags in subtree titles but not in the table of content)RAW")
    .def("__iter__", [](org::sem::DocumentExportConfig::TagExport const& _self) -> org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TagExport> {
                     return org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TagExport>();
                     })
    .def("__int__", [](org::sem::DocumentExportConfig::TagExport const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::DocumentExportConfig::TagExport const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::DocumentExportConfig::TagExport lhs, org::sem::DocumentExportConfig::TagExport rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::DocumentExportConfig::TagExport it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org::sem::DocumentExportConfig::TaskFiltering>(m, "DocumentExportConfigTaskFiltering", type_registry_guard);
  nanobind::enum_<org::sem::DocumentExportConfig::TaskFiltering>(m, "DocumentExportConfigTaskFiltering")
    .value("Whitelist", org::sem::DocumentExportConfig::TaskFiltering::Whitelist, R"RAW(Include tasks from the whitelist)RAW")
    .value("Done", org::sem::DocumentExportConfig::TaskFiltering::Done, R"RAW(Include tasks marked as done)RAW")
    .value("None", org::sem::DocumentExportConfig::TaskFiltering::None, R"RAW(Exclude all task subtrees from export)RAW")
    .value("All", org::sem::DocumentExportConfig::TaskFiltering::All, R"RAW(Add all task subtrees to export)RAW")
    .def("__iter__", [](org::sem::DocumentExportConfig::TaskFiltering const& _self) -> org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TaskFiltering> {
                     return org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TaskFiltering>();
                     })
    .def("__int__", [](org::sem::DocumentExportConfig::TaskFiltering const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::DocumentExportConfig::TaskFiltering const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::DocumentExportConfig::TaskFiltering lhs, org::sem::DocumentExportConfig::TaskFiltering rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::DocumentExportConfig::TaskFiltering it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org::sem::DocumentExportConfig::BrokenLinks>(m, "DocumentExportConfigBrokenLinks", type_registry_guard);
  nanobind::enum_<org::sem::DocumentExportConfig::BrokenLinks>(m, "DocumentExportConfigBrokenLinks")
    .value("None", org::sem::DocumentExportConfig::BrokenLinks::None)
    .value("Mark", org::sem::DocumentExportConfig::BrokenLinks::Mark)
    .value("Raise", org::sem::DocumentExportConfig::BrokenLinks::Raise)
    .value("Ignore", org::sem::DocumentExportConfig::BrokenLinks::Ignore)
    .def("__iter__", [](org::sem::DocumentExportConfig::BrokenLinks const& _self) -> org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::BrokenLinks> {
                     return org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::BrokenLinks>();
                     })
    .def("__int__", [](org::sem::DocumentExportConfig::BrokenLinks const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::DocumentExportConfig::BrokenLinks const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::DocumentExportConfig::BrokenLinks lhs, org::sem::DocumentExportConfig::BrokenLinks rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::DocumentExportConfig::BrokenLinks it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org::sem::DocumentExportConfig::ArchivedTrees>(m, "DocumentExportConfigArchivedTrees", type_registry_guard);
  nanobind::enum_<org::sem::DocumentExportConfig::ArchivedTrees>(m, "DocumentExportConfigArchivedTrees")
    .value("Skip", org::sem::DocumentExportConfig::ArchivedTrees::Skip, R"RAW(Skip archived trees entirely)RAW")
    .value("Headline", org::sem::DocumentExportConfig::ArchivedTrees::Headline, R"RAW(Export only headlines of archived trees)RAW")
    .value("All", org::sem::DocumentExportConfig::ArchivedTrees::All, R"RAW(Export archived trees with full content)RAW")
    .def("__iter__", [](org::sem::DocumentExportConfig::ArchivedTrees const& _self) -> org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::ArchivedTrees> {
                     return org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::ArchivedTrees>();
                     })
    .def("__int__", [](org::sem::DocumentExportConfig::ArchivedTrees const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::DocumentExportConfig::ArchivedTrees const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::DocumentExportConfig::ArchivedTrees lhs, org::sem::DocumentExportConfig::ArchivedTrees rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::DocumentExportConfig::ArchivedTrees it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::DocumentExportConfig::DoExport>(m, "DocumentExportConfigDoExport")
    .def("__init__",
         [](org::sem::DocumentExportConfig::DoExport* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::DocumentExportConfig::DoExport();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("exportToc", &org::sem::DocumentExportConfig::DoExport::exportToc)
    .def("__eq__",
         static_cast<bool(org::sem::DocumentExportConfig::DoExport::*)(org::sem::DocumentExportConfig::DoExport const&) const>(&org::sem::DocumentExportConfig::DoExport::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::DocumentExportConfig::DoExport const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentExportConfig::DoExport const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::DocumentExportConfig::ExportFixed>(m, "DocumentExportConfigExportFixed")
    .def("__init__",
         [](org::sem::DocumentExportConfig::ExportFixed* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::DocumentExportConfig::ExportFixed();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("exportLevels", &org::sem::DocumentExportConfig::ExportFixed::exportLevels)
    .def("__eq__",
         static_cast<bool(org::sem::DocumentExportConfig::ExportFixed::*)(org::sem::DocumentExportConfig::ExportFixed const&) const>(&org::sem::DocumentExportConfig::ExportFixed::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::DocumentExportConfig::ExportFixed const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentExportConfig::ExportFixed const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::DocumentExportConfig::TocExportKind>(m, "DocumentExportConfigTocExportKind", type_registry_guard);
  nanobind::enum_<org::sem::DocumentExportConfig::TocExportKind>(m, "DocumentExportConfigTocExportKind")
    .value("DoExport", org::sem::DocumentExportConfig::TocExportKind::DoExport)
    .value("ExportFixed", org::sem::DocumentExportConfig::TocExportKind::ExportFixed)
    .def("__iter__", [](org::sem::DocumentExportConfig::TocExportKind const& _self) -> org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TocExportKind> {
                     return org::bind::python::PyEnumIterator<org::sem::DocumentExportConfig::TocExportKind>();
                     })
    .def("__int__", [](org::sem::DocumentExportConfig::TocExportKind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::DocumentExportConfig::TocExportKind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::DocumentExportConfig::TocExportKind lhs, org::sem::DocumentExportConfig::TocExportKind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::DocumentExportConfig::TocExportKind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::DocumentExportConfig>(m, "DocumentExportConfig")
    .def("__init__",
         [](org::sem::DocumentExportConfig* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::DocumentExportConfig();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("inlinetasks", &org::sem::DocumentExportConfig::inlinetasks, R"RAW(Toggle inclusion of inlinetasks)RAW")
    .def_rw("footnotes", &org::sem::DocumentExportConfig::footnotes, R"RAW(Toggle the inclusion of footnotes)RAW")
    .def_rw("clock", &org::sem::DocumentExportConfig::clock, R"RAW(Toggle inclusion of 'CLOCK' keywords)RAW")
    .def_rw("author", &org::sem::DocumentExportConfig::author, R"RAW(Toggle inclusion of author name into exported file)RAW")
    .def_rw("emphasis", &org::sem::DocumentExportConfig::emphasis, R"RAW(Toggle emphasized text)RAW")
    .def_rw("specialStrings", &org::sem::DocumentExportConfig::specialStrings, R"RAW(Toggle conversion of special strings)RAW")
    .def_rw("propertyDrawers", &org::sem::DocumentExportConfig::propertyDrawers, R"RAW(Toggle inclusion of property drawers)RAW")
    .def_rw("statisticsCookies", &org::sem::DocumentExportConfig::statisticsCookies, R"RAW(Toggle inclusion of statistics cookies)RAW")
    .def_rw("todoText", &org::sem::DocumentExportConfig::todoText, R"RAW(Toggle inclusion of TODO keywords into exported text)RAW")
    .def_rw("smartQuotes", &org::sem::DocumentExportConfig::smartQuotes, R"RAW(Toggle smart quotes)RAW")
    .def_rw("fixedWidth", &org::sem::DocumentExportConfig::fixedWidth, R"RAW(Toggle fixed-width sections)RAW")
    .def_rw("timestamps", &org::sem::DocumentExportConfig::timestamps, R"RAW(Toggle inclusion of time/date active/inactive stamps)RAW")
    .def_rw("preserveBreaks", &org::sem::DocumentExportConfig::preserveBreaks, R"RAW(Toggles whether to preserve line breaks)RAW")
    .def_rw("subSuperscripts", &org::sem::DocumentExportConfig::subSuperscripts, R"RAW(Toggle TeX-like syntax for sub- and superscripts)RAW")
    .def_rw("expandLinks", &org::sem::DocumentExportConfig::expandLinks, R"RAW(Toggle expansion of environment variables in file paths)RAW")
    .def_rw("creator", &org::sem::DocumentExportConfig::creator, R"RAW(Toggle inclusion of creator information in the exported file)RAW")
    .def_rw("drawers", &org::sem::DocumentExportConfig::drawers, R"RAW(Toggle inclusion of drawers)RAW")
    .def_rw("date", &org::sem::DocumentExportConfig::date, R"RAW(Toggle inclusion of a date into exported file)RAW")
    .def_rw("entities", &org::sem::DocumentExportConfig::entities, R"RAW(Toggle inclusion of entities)RAW")
    .def_rw("email", &org::sem::DocumentExportConfig::email, R"RAW(Toggle inclusion of the author's e-mail into exported file)RAW")
    .def_rw("sectionNumbers", &org::sem::DocumentExportConfig::sectionNumbers, R"RAW(Toggle section-numbers)RAW")
    .def_rw("planning", &org::sem::DocumentExportConfig::planning, R"RAW(Toggle export of planning information)RAW")
    .def_rw("priority", &org::sem::DocumentExportConfig::priority, R"RAW(Toggle inclusion of priority cookies)RAW")
    .def_rw("latex", &org::sem::DocumentExportConfig::latex, R"RAW(Toggle LaTeX export)RAW")
    .def_rw("timestamp", &org::sem::DocumentExportConfig::timestamp, R"RAW(Toggle inclusion of the creation time in the exported file)RAW")
    .def_rw("title", &org::sem::DocumentExportConfig::title, R"RAW(Toggle inclusion of title)RAW")
    .def_rw("tables", &org::sem::DocumentExportConfig::tables, R"RAW(Toggle inclusion of tables)RAW")
    .def_rw("headlineLevels", &org::sem::DocumentExportConfig::headlineLevels, R"RAW(Set the number of headline levels for export)RAW")
    .def_rw("brokenLinks", &org::sem::DocumentExportConfig::brokenLinks)
    .def_rw("tocExport", &org::sem::DocumentExportConfig::tocExport)
    .def_rw("tagExport", &org::sem::DocumentExportConfig::tagExport)
    .def_rw("taskFiltering", &org::sem::DocumentExportConfig::taskFiltering)
    .def_rw("archivedTrees", &org::sem::DocumentExportConfig::archivedTrees)
    .def("__eq__",
         static_cast<bool(org::sem::DocumentExportConfig::*)(org::sem::DocumentExportConfig const&) const>(&org::sem::DocumentExportConfig::operator==),
         nanobind::arg("other"))
    .def("isDoExport", static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isDoExport))
    .def("getDoExport", static_cast<org::sem::DocumentExportConfig::DoExport&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getDoExport))
    .def("isExportFixed", static_cast<bool(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::isExportFixed))
    .def("getExportFixed", static_cast<org::sem::DocumentExportConfig::ExportFixed&(org::sem::DocumentExportConfig::*)()>(&org::sem::DocumentExportConfig::getExportFixed))
    .def_static("getTocExportKindStatic",
                static_cast<org::sem::DocumentExportConfig::TocExportKind(*)(org::sem::DocumentExportConfig::TocExport const&)>(&org::sem::DocumentExportConfig::getTocExportKind),
                nanobind::arg("__input"))
    .def("getTocExportKind", static_cast<org::sem::DocumentExportConfig::TocExportKind(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::getTocExportKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::DocumentExportConfig::TocExport const&(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::DocumentExportConfig::TocExportKind(org::sem::DocumentExportConfig::*)() const>(&org::sem::DocumentExportConfig::sub_variant_get_kind))
    .def("__repr__", [](org::sem::DocumentExportConfig const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentExportConfig const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::SubtreePeriod::Kind>(m, "SubtreePeriodKind", type_registry_guard);
  nanobind::enum_<org::sem::SubtreePeriod::Kind>(m, "SubtreePeriodKind")
    .value("Clocked", org::sem::SubtreePeriod::Kind::Clocked, R"RAW(Time period of the task execution.)RAW")
    .value("Closed", org::sem::SubtreePeriod::Kind::Closed, R"RAW(Task marked as closed)RAW")
    .value("Scheduled", org::sem::SubtreePeriod::Kind::Scheduled, R"RAW(Date of task execution start plus it's estimated effort duration. If the latter one is missing then only a single time point is returned)RAW")
    .value("Titled", org::sem::SubtreePeriod::Kind::Titled, R"RAW(Single point or time range used in title. Single point can also be a simple time, such as `12:20`)RAW")
    .value("Deadline", org::sem::SubtreePeriod::Kind::Deadline, R"RAW(Date of task completion. Must be a single time point)RAW")
    .value("Created", org::sem::SubtreePeriod::Kind::Created, R"RAW(When the subtree was created)RAW")
    .value("Repeated", org::sem::SubtreePeriod::Kind::Repeated, R"RAW(Last repeat time of the recurring tasks)RAW")
    .def("__iter__", [](org::sem::SubtreePeriod::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::SubtreePeriod::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::SubtreePeriod::Kind>();
                     })
    .def("__int__", [](org::sem::SubtreePeriod::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::SubtreePeriod::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::SubtreePeriod::Kind lhs, org::sem::SubtreePeriod::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::SubtreePeriod::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::SubtreePeriod>(m, "SubtreePeriod")
    .def("__init__",
         [](org::sem::SubtreePeriod* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::SubtreePeriod();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("kind", &org::sem::SubtreePeriod::kind, R"RAW(Time period kind -- not associated with point/range distinction)RAW")
    .def_rw("from_", &org::sem::SubtreePeriod::from, R"RAW(Clock start time)RAW")
    .def_rw("to", &org::sem::SubtreePeriod::to, R"RAW(Optional end of the clock)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::SubtreePeriod::*)(org::sem::SubtreePeriod const&) const>(&org::sem::SubtreePeriod::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::SubtreePeriod const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreePeriod const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::Nonblocking>(m, "NamedPropertyNonblocking")
    .def("__init__",
         [](org::sem::NamedProperty::Nonblocking* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::Nonblocking();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("isBlocking", &org::sem::NamedProperty::Nonblocking::isBlocking)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::Nonblocking::*)(org::sem::NamedProperty::Nonblocking const&) const>(&org::sem::NamedProperty::Nonblocking::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Nonblocking const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Nonblocking const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ArchiveTime>(m, "NamedPropertyArchiveTime")
    .def("__init__",
         [](org::sem::NamedProperty::ArchiveTime* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::ArchiveTime();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("time", &org::sem::NamedProperty::ArchiveTime::time)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ArchiveTime::*)(org::sem::NamedProperty::ArchiveTime const&) const>(&org::sem::NamedProperty::ArchiveTime::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveTime const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveTime const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ArchiveFile>(m, "NamedPropertyArchiveFile")
    .def("__init__",
         [](org::sem::NamedProperty::ArchiveFile* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::ArchiveFile();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("file", &org::sem::NamedProperty::ArchiveFile::file)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ArchiveFile::*)(org::sem::NamedProperty::ArchiveFile const&) const>(&org::sem::NamedProperty::ArchiveFile::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveFile const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveFile const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ArchiveOlpath>(m, "NamedPropertyArchiveOlpath")
    .def("__init__",
         [](org::sem::NamedProperty::ArchiveOlpath* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::ArchiveOlpath();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("path", &org::sem::NamedProperty::ArchiveOlpath::path)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ArchiveOlpath::*)(org::sem::NamedProperty::ArchiveOlpath const&) const>(&org::sem::NamedProperty::ArchiveOlpath::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveOlpath const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveOlpath const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ArchiveTarget>(m, "NamedPropertyArchiveTarget")
    .def("__init__",
         [](org::sem::NamedProperty::ArchiveTarget* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::ArchiveTarget();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("path", &org::sem::NamedProperty::ArchiveTarget::path)
    .def_rw("pattern", &org::sem::NamedProperty::ArchiveTarget::pattern)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ArchiveTarget::*)(org::sem::NamedProperty::ArchiveTarget const&) const>(&org::sem::NamedProperty::ArchiveTarget::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveTarget const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveTarget const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ArchiveCategory>(m, "NamedPropertyArchiveCategory")
    .def("__init__",
         [](org::sem::NamedProperty::ArchiveCategory* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::ArchiveCategory();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("category", &org::sem::NamedProperty::ArchiveCategory::category)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ArchiveCategory::*)(org::sem::NamedProperty::ArchiveCategory const&) const>(&org::sem::NamedProperty::ArchiveCategory::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveCategory const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveCategory const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ArchiveTodo>(m, "NamedPropertyArchiveTodo")
    .def("__init__",
         [](org::sem::NamedProperty::ArchiveTodo* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::ArchiveTodo();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("todo", &org::sem::NamedProperty::ArchiveTodo::todo)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ArchiveTodo::*)(org::sem::NamedProperty::ArchiveTodo const&) const>(&org::sem::NamedProperty::ArchiveTodo::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ArchiveTodo const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ArchiveTodo const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::Trigger>(m, "NamedPropertyTrigger")
    .def("__init__",
         [](org::sem::NamedProperty::Trigger* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::Trigger();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::Trigger::*)(org::sem::NamedProperty::Trigger const&) const>(&org::sem::NamedProperty::Trigger::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Trigger const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Trigger const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ExportLatexClass>(m, "NamedPropertyExportLatexClass")
    .def("__init__",
         [](org::sem::NamedProperty::ExportLatexClass* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::ExportLatexClass();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("latexClass", &org::sem::NamedProperty::ExportLatexClass::latexClass)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ExportLatexClass::*)(org::sem::NamedProperty::ExportLatexClass const&) const>(&org::sem::NamedProperty::ExportLatexClass::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ExportLatexClass const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ExportLatexClass const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::CookieData>(m, "NamedPropertyCookieData")
    .def("__init__",
         [](org::sem::NamedProperty::CookieData* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::CookieData();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("isRecursive", &org::sem::NamedProperty::CookieData::isRecursive)
    .def_rw("source", &org::sem::NamedProperty::CookieData::source)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::CookieData::*)(org::sem::NamedProperty::CookieData const&) const>(&org::sem::NamedProperty::CookieData::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CookieData const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CookieData const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ExportLatexClassOptions>(m, "NamedPropertyExportLatexClassOptions")
    .def("__init__",
         [](org::sem::NamedProperty::ExportLatexClassOptions* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::ExportLatexClassOptions();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("options", &org::sem::NamedProperty::ExportLatexClassOptions::options)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ExportLatexClassOptions::*)(org::sem::NamedProperty::ExportLatexClassOptions const&) const>(&org::sem::NamedProperty::ExportLatexClassOptions::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ExportLatexClassOptions const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ExportLatexClassOptions const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ExportLatexHeader>(m, "NamedPropertyExportLatexHeader")
    .def("__init__",
         [](org::sem::NamedProperty::ExportLatexHeader* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::ExportLatexHeader();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("header", &org::sem::NamedProperty::ExportLatexHeader::header)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ExportLatexHeader::*)(org::sem::NamedProperty::ExportLatexHeader const&) const>(&org::sem::NamedProperty::ExportLatexHeader::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ExportLatexHeader const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ExportLatexHeader const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ExportLatexCompiler>(m, "NamedPropertyExportLatexCompiler")
    .def("__init__",
         [](org::sem::NamedProperty::ExportLatexCompiler* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::ExportLatexCompiler();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("compiler", &org::sem::NamedProperty::ExportLatexCompiler::compiler)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ExportLatexCompiler::*)(org::sem::NamedProperty::ExportLatexCompiler const&) const>(&org::sem::NamedProperty::ExportLatexCompiler::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ExportLatexCompiler const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ExportLatexCompiler const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::Ordered>(m, "NamedPropertyOrdered")
    .def("__init__",
         [](org::sem::NamedProperty::Ordered* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::Ordered();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("isOrdered", &org::sem::NamedProperty::Ordered::isOrdered)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::Ordered::*)(org::sem::NamedProperty::Ordered const&) const>(&org::sem::NamedProperty::Ordered::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Ordered const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Ordered const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::Effort>(m, "NamedPropertyEffort")
    .def("__init__",
         [](org::sem::NamedProperty::Effort* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::Effort();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("hours", &org::sem::NamedProperty::Effort::hours)
    .def_rw("minutes", &org::sem::NamedProperty::Effort::minutes)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::Effort::*)(org::sem::NamedProperty::Effort const&) const>(&org::sem::NamedProperty::Effort::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Effort const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Effort const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::NamedProperty::Visibility::Level>(m, "NamedPropertyVisibilityLevel", type_registry_guard);
  nanobind::enum_<org::sem::NamedProperty::Visibility::Level>(m, "NamedPropertyVisibilityLevel")
    .value("Folded", org::sem::NamedProperty::Visibility::Level::Folded)
    .value("Children", org::sem::NamedProperty::Visibility::Level::Children)
    .value("Content", org::sem::NamedProperty::Visibility::Level::Content)
    .value("All", org::sem::NamedProperty::Visibility::Level::All)
    .def("__iter__", [](org::sem::NamedProperty::Visibility::Level const& _self) -> org::bind::python::PyEnumIterator<org::sem::NamedProperty::Visibility::Level> {
                     return org::bind::python::PyEnumIterator<org::sem::NamedProperty::Visibility::Level>();
                     })
    .def("__int__", [](org::sem::NamedProperty::Visibility::Level const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::NamedProperty::Visibility::Level const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::NamedProperty::Visibility::Level lhs, org::sem::NamedProperty::Visibility::Level rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::NamedProperty::Visibility::Level it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::NamedProperty::Visibility>(m, "NamedPropertyVisibility")
    .def("__init__",
         [](org::sem::NamedProperty::Visibility* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::Visibility();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("level", &org::sem::NamedProperty::Visibility::level)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::Visibility::*)(org::sem::NamedProperty::Visibility const&) const>(&org::sem::NamedProperty::Visibility::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Visibility const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Visibility const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::ExportOptions>(m, "NamedPropertyExportOptions")
    .def("__init__",
         [](org::sem::NamedProperty::ExportOptions* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::ExportOptions();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("backend", &org::sem::NamedProperty::ExportOptions::backend)
    .def_rw("values", &org::sem::NamedProperty::ExportOptions::values)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::ExportOptions::*)(org::sem::NamedProperty::ExportOptions const&) const>(&org::sem::NamedProperty::ExportOptions::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::ExportOptions const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::ExportOptions const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::Blocker>(m, "NamedPropertyBlocker")
    .def("__init__",
         [](org::sem::NamedProperty::Blocker* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::Blocker();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("blockers", &org::sem::NamedProperty::Blocker::blockers)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::Blocker::*)(org::sem::NamedProperty::Blocker const&) const>(&org::sem::NamedProperty::Blocker::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Blocker const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Blocker const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::Unnumbered>(m, "NamedPropertyUnnumbered")
    .def("__init__",
         [](org::sem::NamedProperty::Unnumbered* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::Unnumbered();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::Unnumbered::*)(org::sem::NamedProperty::Unnumbered const&) const>(&org::sem::NamedProperty::Unnumbered::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Unnumbered const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Unnumbered const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::Created>(m, "NamedPropertyCreated")
    .def("__init__",
         [](org::sem::NamedProperty::Created* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::Created();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("time", &org::sem::NamedProperty::Created::time)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::Created::*)(org::sem::NamedProperty::Created const&) const>(&org::sem::NamedProperty::Created::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::Created const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::Created const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::RadioId>(m, "NamedPropertyRadioId")
    .def("__init__",
         [](org::sem::NamedProperty::RadioId* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::RadioId();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("words", &org::sem::NamedProperty::RadioId::words)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::RadioId::*)(org::sem::NamedProperty::RadioId const&) const>(&org::sem::NamedProperty::RadioId::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::RadioId const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::RadioId const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::HashtagDef>(m, "NamedPropertyHashtagDef")
    .def("__init__",
         [](org::sem::NamedProperty::HashtagDef* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::HashtagDef();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("hashtag", &org::sem::NamedProperty::HashtagDef::hashtag)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::HashtagDef::*)(org::sem::NamedProperty::HashtagDef const&) const>(&org::sem::NamedProperty::HashtagDef::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::HashtagDef const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::HashtagDef const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::CustomArgs>(m, "NamedPropertyCustomArgs")
    .def("__init__",
         [](org::sem::NamedProperty::CustomArgs* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::CustomArgs();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::NamedProperty::CustomArgs::name, R"RAW(Original name of the property)RAW")
    .def_rw("sub", &org::sem::NamedProperty::CustomArgs::sub, R"RAW(Property target specialization)RAW")
    .def_rw("attrs", &org::sem::NamedProperty::CustomArgs::attrs, R"RAW(Property parameters)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::CustomArgs::*)(org::sem::NamedProperty::CustomArgs const&) const>(&org::sem::NamedProperty::CustomArgs::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CustomArgs const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CustomArgs const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::CustomRaw>(m, "NamedPropertyCustomRaw")
    .def("__init__",
         [](org::sem::NamedProperty::CustomRaw* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::CustomRaw();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::NamedProperty::CustomRaw::name, R"RAW(Original name of the property)RAW")
    .def_rw("value", &org::sem::NamedProperty::CustomRaw::value, R"RAW(Property value)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::CustomRaw::*)(org::sem::NamedProperty::CustomRaw const&) const>(&org::sem::NamedProperty::CustomRaw::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CustomRaw const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CustomRaw const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::CustomId>(m, "NamedPropertyCustomId")
    .def("__init__",
         [](org::sem::NamedProperty::CustomId* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::CustomId();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("value", &org::sem::NamedProperty::CustomId::value, R"RAW(Property value)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::CustomId::*)(org::sem::NamedProperty::CustomId const&) const>(&org::sem::NamedProperty::CustomId::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CustomId const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CustomId const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::CustomSubtreeJson>(m, "NamedPropertyCustomSubtreeJson")
    .def("__init__",
         [](org::sem::NamedProperty::CustomSubtreeJson* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::CustomSubtreeJson();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::NamedProperty::CustomSubtreeJson::name)
    .def_rw("value", &org::sem::NamedProperty::CustomSubtreeJson::value)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::CustomSubtreeJson::*)(org::sem::NamedProperty::CustomSubtreeJson const&) const>(&org::sem::NamedProperty::CustomSubtreeJson::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CustomSubtreeJson const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CustomSubtreeJson const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::NamedProperty::CustomSubtreeFlags>(m, "NamedPropertyCustomSubtreeFlags")
    .def("__init__",
         [](org::sem::NamedProperty::CustomSubtreeFlags* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty::CustomSubtreeFlags();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::NamedProperty::CustomSubtreeFlags::name)
    .def_rw("value", &org::sem::NamedProperty::CustomSubtreeFlags::value)
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::CustomSubtreeFlags::*)(org::sem::NamedProperty::CustomSubtreeFlags const&) const>(&org::sem::NamedProperty::CustomSubtreeFlags::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::NamedProperty::CustomSubtreeFlags const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty::CustomSubtreeFlags const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::NamedProperty::Kind>(m, "NamedPropertyKind", type_registry_guard);
  nanobind::enum_<org::sem::NamedProperty::Kind>(m, "NamedPropertyKind")
    .value("Nonblocking", org::sem::NamedProperty::Kind::Nonblocking)
    .value("ArchiveTime", org::sem::NamedProperty::Kind::ArchiveTime)
    .value("ArchiveFile", org::sem::NamedProperty::Kind::ArchiveFile)
    .value("ArchiveOlpath", org::sem::NamedProperty::Kind::ArchiveOlpath)
    .value("ArchiveTarget", org::sem::NamedProperty::Kind::ArchiveTarget)
    .value("ArchiveCategory", org::sem::NamedProperty::Kind::ArchiveCategory)
    .value("ArchiveTodo", org::sem::NamedProperty::Kind::ArchiveTodo)
    .value("Trigger", org::sem::NamedProperty::Kind::Trigger)
    .value("ExportLatexClass", org::sem::NamedProperty::Kind::ExportLatexClass)
    .value("CookieData", org::sem::NamedProperty::Kind::CookieData)
    .value("ExportLatexClassOptions", org::sem::NamedProperty::Kind::ExportLatexClassOptions)
    .value("ExportLatexHeader", org::sem::NamedProperty::Kind::ExportLatexHeader)
    .value("ExportLatexCompiler", org::sem::NamedProperty::Kind::ExportLatexCompiler)
    .value("Ordered", org::sem::NamedProperty::Kind::Ordered)
    .value("Effort", org::sem::NamedProperty::Kind::Effort)
    .value("Visibility", org::sem::NamedProperty::Kind::Visibility)
    .value("ExportOptions", org::sem::NamedProperty::Kind::ExportOptions)
    .value("Blocker", org::sem::NamedProperty::Kind::Blocker)
    .value("Unnumbered", org::sem::NamedProperty::Kind::Unnumbered)
    .value("Created", org::sem::NamedProperty::Kind::Created)
    .value("RadioId", org::sem::NamedProperty::Kind::RadioId)
    .value("HashtagDef", org::sem::NamedProperty::Kind::HashtagDef)
    .value("CustomArgs", org::sem::NamedProperty::Kind::CustomArgs)
    .value("CustomRaw", org::sem::NamedProperty::Kind::CustomRaw)
    .value("CustomId", org::sem::NamedProperty::Kind::CustomId)
    .value("CustomSubtreeJson", org::sem::NamedProperty::Kind::CustomSubtreeJson)
    .value("CustomSubtreeFlags", org::sem::NamedProperty::Kind::CustomSubtreeFlags)
    .def("__iter__", [](org::sem::NamedProperty::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::NamedProperty::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::NamedProperty::Kind>();
                     })
    .def("__int__", [](org::sem::NamedProperty::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::NamedProperty::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::NamedProperty::Kind lhs, org::sem::NamedProperty::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::NamedProperty::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::NamedProperty>(m, "NamedProperty")
    .def("__init__",
         [](org::sem::NamedProperty* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NamedProperty();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("isMatching",
         static_cast<bool(org::sem::NamedProperty::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::NamedProperty::isMatching),
         nanobind::arg("kind"),
         nanobind::arg("subKind") = std::nullopt,
         R"RAW(Check if property matches specified kind and optional subkind. Built-in property checking is also done with this function -- 'created' etc.)RAW")
    .def("getName", static_cast<hstd::Str(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getName), R"RAW(Get non-normalized name of the property (for built-in and user))RAW")
    .def("getSubKind", static_cast<hstd::Opt<hstd::Str>(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getSubKind), R"RAW(Get non-normalized sub-kind for the property.)RAW")
    .def("__eq__",
         static_cast<bool(org::sem::NamedProperty::*)(org::sem::NamedProperty const&) const>(&org::sem::NamedProperty::operator==),
         nanobind::arg("other"))
    .def("isNonblocking", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isNonblocking))
    .def("getNonblocking", static_cast<org::sem::NamedProperty::Nonblocking&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getNonblocking))
    .def("isArchiveTime", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTime))
    .def("getArchiveTime", static_cast<org::sem::NamedProperty::ArchiveTime&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTime))
    .def("isArchiveFile", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveFile))
    .def("getArchiveFile", static_cast<org::sem::NamedProperty::ArchiveFile&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveFile))
    .def("isArchiveOlpath", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveOlpath))
    .def("getArchiveOlpath", static_cast<org::sem::NamedProperty::ArchiveOlpath&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveOlpath))
    .def("isArchiveTarget", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTarget))
    .def("getArchiveTarget", static_cast<org::sem::NamedProperty::ArchiveTarget&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTarget))
    .def("isArchiveCategory", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveCategory))
    .def("getArchiveCategory", static_cast<org::sem::NamedProperty::ArchiveCategory&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveCategory))
    .def("isArchiveTodo", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isArchiveTodo))
    .def("getArchiveTodo", static_cast<org::sem::NamedProperty::ArchiveTodo&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getArchiveTodo))
    .def("isTrigger", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isTrigger))
    .def("getTrigger", static_cast<org::sem::NamedProperty::Trigger&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getTrigger))
    .def("isExportLatexClass", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexClass))
    .def("getExportLatexClass", static_cast<org::sem::NamedProperty::ExportLatexClass&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexClass))
    .def("isCookieData", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCookieData))
    .def("getCookieData", static_cast<org::sem::NamedProperty::CookieData&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCookieData))
    .def("isExportLatexClassOptions", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexClassOptions))
    .def("getExportLatexClassOptions", static_cast<org::sem::NamedProperty::ExportLatexClassOptions&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexClassOptions))
    .def("isExportLatexHeader", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexHeader))
    .def("getExportLatexHeader", static_cast<org::sem::NamedProperty::ExportLatexHeader&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexHeader))
    .def("isExportLatexCompiler", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportLatexCompiler))
    .def("getExportLatexCompiler", static_cast<org::sem::NamedProperty::ExportLatexCompiler&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportLatexCompiler))
    .def("isOrdered", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isOrdered))
    .def("getOrdered", static_cast<org::sem::NamedProperty::Ordered&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getOrdered))
    .def("isEffort", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isEffort))
    .def("getEffort", static_cast<org::sem::NamedProperty::Effort&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getEffort))
    .def("isVisibility", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isVisibility))
    .def("getVisibility", static_cast<org::sem::NamedProperty::Visibility&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getVisibility))
    .def("isExportOptions", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isExportOptions))
    .def("getExportOptions", static_cast<org::sem::NamedProperty::ExportOptions&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getExportOptions))
    .def("isBlocker", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isBlocker))
    .def("getBlocker", static_cast<org::sem::NamedProperty::Blocker&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getBlocker))
    .def("isUnnumbered", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isUnnumbered))
    .def("getUnnumbered", static_cast<org::sem::NamedProperty::Unnumbered&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getUnnumbered))
    .def("isCreated", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCreated))
    .def("getCreated", static_cast<org::sem::NamedProperty::Created&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCreated))
    .def("isRadioId", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isRadioId))
    .def("getRadioId", static_cast<org::sem::NamedProperty::RadioId&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getRadioId))
    .def("isHashtagDef", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isHashtagDef))
    .def("getHashtagDef", static_cast<org::sem::NamedProperty::HashtagDef&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getHashtagDef))
    .def("isCustomArgs", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomArgs))
    .def("getCustomArgs", static_cast<org::sem::NamedProperty::CustomArgs&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomArgs))
    .def("isCustomRaw", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomRaw))
    .def("getCustomRaw", static_cast<org::sem::NamedProperty::CustomRaw&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomRaw))
    .def("isCustomId", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomId))
    .def("getCustomId", static_cast<org::sem::NamedProperty::CustomId&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomId))
    .def("isCustomSubtreeJson", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeJson))
    .def("getCustomSubtreeJson", static_cast<org::sem::NamedProperty::CustomSubtreeJson&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeJson))
    .def("isCustomSubtreeFlags", static_cast<bool(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::isCustomSubtreeFlags))
    .def("getCustomSubtreeFlags", static_cast<org::sem::NamedProperty::CustomSubtreeFlags&(org::sem::NamedProperty::*)()>(&org::sem::NamedProperty::getCustomSubtreeFlags))
    .def_static("getKindStatic",
                static_cast<org::sem::NamedProperty::Kind(*)(org::sem::NamedProperty::Data const&)>(&org::sem::NamedProperty::getKind),
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::NamedProperty::Kind(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::NamedProperty::Data const&(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::NamedProperty::Kind(org::sem::NamedProperty::*)() const>(&org::sem::NamedProperty::sub_variant_get_kind))
    .def("__repr__", [](org::sem::NamedProperty const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NamedProperty const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::OrgDiagnostics::ParseTokenError>(m, "OrgDiagnosticsParseTokenError")
    .def("__init__",
         [](org::sem::OrgDiagnostics::ParseTokenError* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::OrgDiagnostics::ParseTokenError();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("brief", &org::sem::OrgDiagnostics::ParseTokenError::brief)
    .def_rw("detail", &org::sem::OrgDiagnostics::ParseTokenError::detail)
    .def_rw("parserFunction", &org::sem::OrgDiagnostics::ParseTokenError::parserFunction)
    .def_rw("parserLine", &org::sem::OrgDiagnostics::ParseTokenError::parserLine)
    .def_rw("tokenKind", &org::sem::OrgDiagnostics::ParseTokenError::tokenKind)
    .def_rw("tokenText", &org::sem::OrgDiagnostics::ParseTokenError::tokenText)
    .def_rw("loc", &org::sem::OrgDiagnostics::ParseTokenError::loc)
    .def_rw("errName", &org::sem::OrgDiagnostics::ParseTokenError::errName)
    .def_rw("errCode", &org::sem::OrgDiagnostics::ParseTokenError::errCode)
    .def("__eq__",
         static_cast<bool(org::sem::OrgDiagnostics::ParseTokenError::*)(org::sem::OrgDiagnostics::ParseTokenError const&) const>(&org::sem::OrgDiagnostics::ParseTokenError::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::OrgDiagnostics::ParseTokenError const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgDiagnostics::ParseTokenError const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::OrgDiagnostics::ParseError>(m, "OrgDiagnosticsParseError")
    .def("__init__",
         [](org::sem::OrgDiagnostics::ParseError* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::OrgDiagnostics::ParseError();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("brief", &org::sem::OrgDiagnostics::ParseError::brief)
    .def_rw("detail", &org::sem::OrgDiagnostics::ParseError::detail)
    .def_rw("parserFunction", &org::sem::OrgDiagnostics::ParseError::parserFunction)
    .def_rw("parserLine", &org::sem::OrgDiagnostics::ParseError::parserLine)
    .def_rw("errName", &org::sem::OrgDiagnostics::ParseError::errName)
    .def_rw("errCode", &org::sem::OrgDiagnostics::ParseError::errCode)
    .def_rw("loc", &org::sem::OrgDiagnostics::ParseError::loc)
    .def("__eq__",
         static_cast<bool(org::sem::OrgDiagnostics::ParseError::*)(org::sem::OrgDiagnostics::ParseError const&) const>(&org::sem::OrgDiagnostics::ParseError::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::OrgDiagnostics::ParseError const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgDiagnostics::ParseError const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::OrgDiagnostics::IncludeError>(m, "OrgDiagnosticsIncludeError")
    .def("__init__",
         [](org::sem::OrgDiagnostics::IncludeError* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::OrgDiagnostics::IncludeError();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("brief", &org::sem::OrgDiagnostics::IncludeError::brief)
    .def_rw("targetPath", &org::sem::OrgDiagnostics::IncludeError::targetPath)
    .def_rw("workingFile", &org::sem::OrgDiagnostics::IncludeError::workingFile)
    .def("__eq__",
         static_cast<bool(org::sem::OrgDiagnostics::IncludeError::*)(org::sem::OrgDiagnostics::IncludeError const&) const>(&org::sem::OrgDiagnostics::IncludeError::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::OrgDiagnostics::IncludeError const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgDiagnostics::IncludeError const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::OrgDiagnostics::ConvertError>(m, "OrgDiagnosticsConvertError")
    .def("__init__",
         [](org::sem::OrgDiagnostics::ConvertError* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::OrgDiagnostics::ConvertError();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("brief", &org::sem::OrgDiagnostics::ConvertError::brief)
    .def_rw("detail", &org::sem::OrgDiagnostics::ConvertError::detail)
    .def_rw("convertFunction", &org::sem::OrgDiagnostics::ConvertError::convertFunction)
    .def_rw("convertLine", &org::sem::OrgDiagnostics::ConvertError::convertLine)
    .def_rw("convertFile", &org::sem::OrgDiagnostics::ConvertError::convertFile)
    .def_rw("errName", &org::sem::OrgDiagnostics::ConvertError::errName)
    .def_rw("errCode", &org::sem::OrgDiagnostics::ConvertError::errCode)
    .def_rw("loc", &org::sem::OrgDiagnostics::ConvertError::loc)
    .def("__eq__",
         static_cast<bool(org::sem::OrgDiagnostics::ConvertError::*)(org::sem::OrgDiagnostics::ConvertError const&) const>(&org::sem::OrgDiagnostics::ConvertError::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::OrgDiagnostics::ConvertError const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgDiagnostics::ConvertError const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::OrgDiagnostics::InternalError>(m, "OrgDiagnosticsInternalError")
    .def("__init__",
         [](org::sem::OrgDiagnostics::InternalError* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::OrgDiagnostics::InternalError();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("message", &org::sem::OrgDiagnostics::InternalError::message)
    .def_rw("function", &org::sem::OrgDiagnostics::InternalError::function)
    .def_rw("line", &org::sem::OrgDiagnostics::InternalError::line)
    .def_rw("file", &org::sem::OrgDiagnostics::InternalError::file)
    .def_rw("loc", &org::sem::OrgDiagnostics::InternalError::loc)
    .def("__eq__",
         static_cast<bool(org::sem::OrgDiagnostics::InternalError::*)(org::sem::OrgDiagnostics::InternalError const&) const>(&org::sem::OrgDiagnostics::InternalError::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::sem::OrgDiagnostics::InternalError const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgDiagnostics::InternalError const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::OrgDiagnostics::Kind>(m, "OrgDiagnosticsKind", type_registry_guard);
  nanobind::enum_<org::sem::OrgDiagnostics::Kind>(m, "OrgDiagnosticsKind")
    .value("ParseTokenError", org::sem::OrgDiagnostics::Kind::ParseTokenError)
    .value("ParseError", org::sem::OrgDiagnostics::Kind::ParseError)
    .value("IncludeError", org::sem::OrgDiagnostics::Kind::IncludeError)
    .value("ConvertError", org::sem::OrgDiagnostics::Kind::ConvertError)
    .value("InternalError", org::sem::OrgDiagnostics::Kind::InternalError)
    .def("__iter__", [](org::sem::OrgDiagnostics::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::OrgDiagnostics::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::OrgDiagnostics::Kind>();
                     })
    .def("__int__", [](org::sem::OrgDiagnostics::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::OrgDiagnostics::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::OrgDiagnostics::Kind lhs, org::sem::OrgDiagnostics::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::OrgDiagnostics::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::OrgDiagnostics>(m, "OrgDiagnostics")
    .def("__init__",
         [](org::sem::OrgDiagnostics* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::OrgDiagnostics();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::sem::OrgDiagnostics::*)(org::sem::OrgDiagnostics const&) const>(&org::sem::OrgDiagnostics::operator==),
         nanobind::arg("other"))
    .def("isParseTokenError", static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isParseTokenError))
    .def("getParseTokenError", static_cast<org::sem::OrgDiagnostics::ParseTokenError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getParseTokenError))
    .def("isParseError", static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isParseError))
    .def("getParseError", static_cast<org::sem::OrgDiagnostics::ParseError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getParseError))
    .def("isIncludeError", static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isIncludeError))
    .def("getIncludeError", static_cast<org::sem::OrgDiagnostics::IncludeError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getIncludeError))
    .def("isConvertError", static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isConvertError))
    .def("getConvertError", static_cast<org::sem::OrgDiagnostics::ConvertError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getConvertError))
    .def("isInternalError", static_cast<bool(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::isInternalError))
    .def("getInternalError", static_cast<org::sem::OrgDiagnostics::InternalError&(org::sem::OrgDiagnostics::*)()>(&org::sem::OrgDiagnostics::getInternalError))
    .def_static("getKindStatic",
                static_cast<org::sem::OrgDiagnostics::Kind(*)(org::sem::OrgDiagnostics::Data const&)>(&org::sem::OrgDiagnostics::getKind),
                nanobind::arg("__input"))
    .def("getKind", static_cast<org::sem::OrgDiagnostics::Kind(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::getKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::OrgDiagnostics::Data const&(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::OrgDiagnostics::Kind(org::sem::OrgDiagnostics::*)() const>(&org::sem::OrgDiagnostics::sub_variant_get_kind))
    .def("__repr__", [](org::sem::OrgDiagnostics const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::OrgDiagnostics const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmNoNode>>(m, "ImmAdapterNoNodeBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmErrorItem>>(m, "ImmAdapterErrorItemBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmErrorGroup>>(m, "ImmAdapterErrorGroupBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmStmt>>(m, "ImmAdapterStmtBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmInline>>(m, "ImmAdapterInlineBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmStmtList>>(m, "ImmAdapterStmtListBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmEmpty>>(m, "ImmAdapterEmptyBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmd>>(m, "ImmAdapterCmdBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlock>>(m, "ImmAdapterBlockBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmLineCommand>>(m, "ImmAdapterLineCommandBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmAttached>>(m, "ImmAdapterAttachedBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmLeaf>>(m, "ImmAdapterLeafBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdCaption>>(m, "ImmAdapterCmdCaptionBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdCreator>>(m, "ImmAdapterCmdCreatorBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdAuthor>>(m, "ImmAdapterCmdAuthorBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdEmail>>(m, "ImmAdapterCmdEmailBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdLanguage>>(m, "ImmAdapterCmdLanguageBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdColumns>>(m, "ImmAdapterCmdColumnsBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdName>>(m, "ImmAdapterCmdNameBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomArgs>>(m, "ImmAdapterCmdCustomArgsBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomRaw>>(m, "ImmAdapterCmdCustomRawBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomText>>(m, "ImmAdapterCmdCustomTextBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdCall>>(m, "ImmAdapterCmdCallBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdTblfm>>(m, "ImmAdapterCmdTblfmBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmHashTag>>(m, "ImmAdapterHashTagBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmInlineFootnote>>(m, "ImmAdapterInlineFootnoteBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmInlineExport>>(m, "ImmAdapterInlineExportBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmTime>>(m, "ImmAdapterTimeBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmTimeRange>>(m, "ImmAdapterTimeRangeBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmMacro>>(m, "ImmAdapterMacroBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmSymbol>>(m, "ImmAdapterSymbolBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmEscaped>>(m, "ImmAdapterEscapedBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmNewline>>(m, "ImmAdapterNewlineBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmSpace>>(m, "ImmAdapterSpaceBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmWord>>(m, "ImmAdapterWordBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmAtMention>>(m, "ImmAdapterAtMentionBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmRawText>>(m, "ImmAdapterRawTextBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmPunctuation>>(m, "ImmAdapterPunctuationBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmPlaceholder>>(m, "ImmAdapterPlaceholderBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBigIdent>>(m, "ImmAdapterBigIdentBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmTextTarget>>(m, "ImmAdapterTextTargetBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmErrorSkipToken>>(m, "ImmAdapterErrorSkipTokenBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmErrorSkipGroup>>(m, "ImmAdapterErrorSkipGroupBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmMarkup>>(m, "ImmAdapterMarkupBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBold>>(m, "ImmAdapterBoldBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmUnderline>>(m, "ImmAdapterUnderlineBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmMonospace>>(m, "ImmAdapterMonospaceBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmMarkQuote>>(m, "ImmAdapterMarkQuoteBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmVerbatim>>(m, "ImmAdapterVerbatimBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmItalic>>(m, "ImmAdapterItalicBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmStrike>>(m, "ImmAdapterStrikeBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmPar>>(m, "ImmAdapterParBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmRadioTarget>>(m, "ImmAdapterRadioTargetBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmLatex>>(m, "ImmAdapterLatexBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmLink>>(m, "ImmAdapterLinkBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockCenter>>(m, "ImmAdapterBlockCenterBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockQuote>>(m, "ImmAdapterBlockQuoteBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockComment>>(m, "ImmAdapterBlockCommentBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockVerse>>(m, "ImmAdapterBlockVerseBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockDynamicFallback>>(m, "ImmAdapterBlockDynamicFallbackBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockExample>>(m, "ImmAdapterBlockExampleBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockExport>>(m, "ImmAdapterBlockExportBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockAdmonition>>(m, "ImmAdapterBlockAdmonitionBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockCodeEvalResult>>(m, "ImmAdapterBlockCodeEvalResultBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmBlockCode>>(m, "ImmAdapterBlockCodeBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmSubtreeLog>>(m, "ImmAdapterSubtreeLogBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmSubtree>>(m, "ImmAdapterSubtreeBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCell>>(m, "ImmAdapterCellBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmRow>>(m, "ImmAdapterRowBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmTable>>(m, "ImmAdapterTableBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmParagraph>>(m, "ImmAdapterParagraphBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmColonExample>>(m, "ImmAdapterColonExampleBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdAttr>>(m, "ImmAdapterCmdAttrBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdExport>>(m, "ImmAdapterCmdExportBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCall>>(m, "ImmAdapterCallBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmList>>(m, "ImmAdapterListBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmListItem>>(m, "ImmAdapterListItemBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmDocumentOptions>>(m, "ImmAdapterDocumentOptionsBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmDocumentFragment>>(m, "ImmAdapterDocumentFragmentBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCriticMarkup>>(m, "ImmAdapterCriticMarkupBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmDocument>>(m, "ImmAdapterDocumentBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmFileTarget>>(m, "ImmAdapterFileTargetBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmTextSeparator>>(m, "ImmAdapterTextSeparatorBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmDocumentGroup>>(m, "ImmAdapterDocumentGroupBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmFile>>(m, "ImmAdapterFileBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmDirectory>>(m, "ImmAdapterDirectoryBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmSymlink>>(m, "ImmAdapterSymlinkBase")
    ;
  nanobind::class_<org::imm::ImmAdapterTBase<org::imm::ImmCmdInclude>>(m, "ImmAdapterCmdIncludeBase")
    ;
  nanobind::class_<org::sem::NoNode /* d_org */, org::sem::Org>(m, "NoNode")
    .def("__init__",
         [](org::sem::NoNode* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::NoNode /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::NoNode const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::NoNode const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::ErrorItem /* d_org */, org::sem::Org>(m, "ErrorItem")
    .def("__init__",
         [](org::sem::ErrorItem* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::ErrorItem /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("diag", &org::sem::ErrorItem /* d_org */::diag)
    .def("__repr__", [](org::sem::ErrorItem const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ErrorItem const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::ErrorGroup /* d_org */, org::sem::Org>(m, "ErrorGroup")
    .def("__init__",
         [](org::sem::ErrorGroup* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::ErrorGroup /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("diagnostics", &org::sem::ErrorGroup /* d_org */::diagnostics)
    .def("__repr__", [](org::sem::ErrorGroup const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ErrorGroup const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Stmt /* d_org */, org::sem::Org>(m, "Stmt")
    .def_rw("attached", &org::sem::Stmt /* d_org */::attached)
    .def("getAttached",
         static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt /* d_org */::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt /* d_org */::getAttached),
         nanobind::arg("kind") = std::nullopt,
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Stmt /* d_org */::*)() const>(&org::sem::Stmt /* d_org */::getCaption))
    .def("getName", static_cast<hstd::Vec<hstd::Str>(org::sem::Stmt /* d_org */::*)() const>(&org::sem::Stmt /* d_org */::getName))
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Stmt /* d_org */::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Stmt /* d_org */::getAttrs),
         nanobind::arg("kind") = std::nullopt,
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Stmt /* d_org */::*)(hstd::Str const&) const>(&org::sem::Stmt /* d_org */::getFirstAttr),
         nanobind::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("getFirstAttrString",
         static_cast<hstd::Opt<hstd::Str>(org::sem::Stmt /* d_org */::*)(hstd::Str const&) const>(&org::sem::Stmt /* d_org */::getFirstAttrString),
         nanobind::arg("kind"))
    .def("getFirstAttrInt",
         static_cast<hstd::Opt<int>(org::sem::Stmt /* d_org */::*)(hstd::Str const&) const>(&org::sem::Stmt /* d_org */::getFirstAttrInt),
         nanobind::arg("kind"))
    .def("getFirstAttrBool",
         static_cast<hstd::Opt<bool>(org::sem::Stmt /* d_org */::*)(hstd::Str const&) const>(&org::sem::Stmt /* d_org */::getFirstAttrBool),
         nanobind::arg("kind"))
    .def("getFirstAttrDouble",
         static_cast<hstd::Opt<double>(org::sem::Stmt /* d_org */::*)(hstd::Str const&) const>(&org::sem::Stmt /* d_org */::getFirstAttrDouble),
         nanobind::arg("kind"))
    .def("getFirstAttrLisp",
         static_cast<hstd::Opt<org::sem::AttrValue::LispValue>(org::sem::Stmt /* d_org */::*)(hstd::Str const&) const>(&org::sem::Stmt /* d_org */::getFirstAttrLisp),
         nanobind::arg("kind"))
    .def("getFirstAttrKind",
         static_cast<hstd::Opt<org::sem::AttrValue::Kind>(org::sem::Stmt /* d_org */::*)(hstd::Str const&) const>(&org::sem::Stmt /* d_org */::getFirstAttrKind),
         nanobind::arg("kind"))
    ;
  nanobind::class_<org::sem::Inline /* d_org */, org::sem::Org>(m, "Inline")
    ;
  nanobind::class_<org::sem::StmtList /* d_org */, org::sem::Org>(m, "StmtList")
    .def("__init__",
         [](org::sem::StmtList* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::StmtList /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::StmtList const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::StmtList const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Empty /* d_org */, org::sem::Org>(m, "Empty")
    .def("__init__",
         [](org::sem::Empty* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Empty /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Empty const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Empty const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Leaf /* d_org */, org::sem::Org>(m, "Leaf")
    .def_rw("text", &org::sem::Leaf /* d_org */::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<hstd::Str(org::sem::Leaf /* d_org */::*)() const>(&org::sem::Leaf /* d_org */::getText))
    ;
  bind_enum_iterator<org::sem::Time::Repeat::Mode>(m, "TimeRepeatMode", type_registry_guard);
  nanobind::enum_<org::sem::Time::Repeat::Mode>(m, "TimeRepeatMode")
    .value("None", org::sem::Time::Repeat::Mode::None, R"RAW(Do not repeat task on completion)RAW")
    .value("Exact", org::sem::Time::Repeat::Mode::Exact, R"RAW(?)RAW")
    .value("FirstMatch", org::sem::Time::Repeat::Mode::FirstMatch, R"RAW(Repeat on the first matching day in the future)RAW")
    .value("SameDay", org::sem::Time::Repeat::Mode::SameDay, R"RAW(Repeat task on the same day next week/month/year)RAW")
    .def("__iter__", [](org::sem::Time::Repeat::Mode const& _self) -> org::bind::python::PyEnumIterator<org::sem::Time::Repeat::Mode> {
                     return org::bind::python::PyEnumIterator<org::sem::Time::Repeat::Mode>();
                     })
    .def("__int__", [](org::sem::Time::Repeat::Mode const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::Time::Repeat::Mode const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::Time::Repeat::Mode lhs, org::sem::Time::Repeat::Mode rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::Time::Repeat::Mode it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org::sem::Time::Repeat::Period>(m, "TimeRepeatPeriod", type_registry_guard);
  nanobind::enum_<org::sem::Time::Repeat::Period>(m, "TimeRepeatPeriod")
    .value("Year", org::sem::Time::Repeat::Period::Year)
    .value("Month", org::sem::Time::Repeat::Period::Month)
    .value("Week", org::sem::Time::Repeat::Period::Week)
    .value("Day", org::sem::Time::Repeat::Period::Day)
    .value("Hour", org::sem::Time::Repeat::Period::Hour)
    .value("Minute", org::sem::Time::Repeat::Period::Minute)
    .def("__iter__", [](org::sem::Time::Repeat::Period const& _self) -> org::bind::python::PyEnumIterator<org::sem::Time::Repeat::Period> {
                     return org::bind::python::PyEnumIterator<org::sem::Time::Repeat::Period>();
                     })
    .def("__int__", [](org::sem::Time::Repeat::Period const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::Time::Repeat::Period const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::Time::Repeat::Period lhs, org::sem::Time::Repeat::Period rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::Time::Repeat::Period it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::Time::Repeat>(m, "TimeRepeat")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::Time::Repeat* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Time::Repeat();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("mode", &org::sem::Time::Repeat::mode, R"RAW(mode)RAW")
    .def_rw("period", &org::sem::Time::Repeat::period, R"RAW(period)RAW")
    .def_rw("count", &org::sem::Time::Repeat::count, R"RAW(count)RAW")
    .def("__repr__", [](org::sem::Time::Repeat const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Time::Repeat const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Time::Static>(m, "TimeStatic")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::Time::Static* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Time::Static();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("repeat", &org::sem::Time::Static::repeat)
    .def_rw("warn", &org::sem::Time::Static::warn)
    .def_rw("time", &org::sem::Time::Static::time)
    .def("__repr__", [](org::sem::Time::Static const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Time::Static const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Time::Dynamic>(m, "TimeDynamic")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::Time::Dynamic* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Time::Dynamic();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("expr", &org::sem::Time::Dynamic::expr)
    .def("__repr__", [](org::sem::Time::Dynamic const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Time::Dynamic const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::Time::TimeKind>(m, "TimeTimeKind", type_registry_guard);
  nanobind::enum_<org::sem::Time::TimeKind>(m, "TimeTimeKind")
    .value("Static", org::sem::Time::TimeKind::Static)
    .value("Dynamic", org::sem::Time::TimeKind::Dynamic)
    .def("__iter__", [](org::sem::Time::TimeKind const& _self) -> org::bind::python::PyEnumIterator<org::sem::Time::TimeKind> {
                     return org::bind::python::PyEnumIterator<org::sem::Time::TimeKind>();
                     })
    .def("__int__", [](org::sem::Time::TimeKind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::Time::TimeKind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::Time::TimeKind lhs, org::sem::Time::TimeKind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::Time::TimeKind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::Time /* d_org */, org::sem::Org>(m, "Time")
    .def("__init__",
         [](org::sem::Time* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Time /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("isActive", &org::sem::Time /* d_org */::isActive, R"RAW(<active> vs [inactive])RAW")
    .def("getYear", static_cast<hstd::Opt<int>(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getYear))
    .def("getMonth", static_cast<hstd::Opt<int>(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getMonth))
    .def("getDay", static_cast<hstd::Opt<int>(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getDay))
    .def("getHour", static_cast<hstd::Opt<int>(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getHour))
    .def("getMinute", static_cast<hstd::Opt<int>(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getMinute))
    .def("getSecond", static_cast<hstd::Opt<int>(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getSecond))
    .def("getStaticTime", static_cast<hstd::UserTime(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getStaticTime))
    .def("isStatic", static_cast<bool(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::isStatic))
    .def("getStatic", static_cast<org::sem::Time::Static&(org::sem::Time /* d_org */::*)()>(&org::sem::Time /* d_org */::getStatic))
    .def("isDynamic", static_cast<bool(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::isDynamic))
    .def("getDynamic", static_cast<org::sem::Time::Dynamic&(org::sem::Time /* d_org */::*)()>(&org::sem::Time /* d_org */::getDynamic))
    .def_static("getTimeKindStatic",
                static_cast<org::sem::Time::TimeKind(*)(org::sem::Time::TimeVariant const&)>(&org::sem::Time /* d_org */::getTimeKind),
                nanobind::arg("__input"))
    .def("getTimeKind", static_cast<org::sem::Time::TimeKind(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::getTimeKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::Time::TimeVariant const&(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::Time::TimeKind(org::sem::Time /* d_org */::*)() const>(&org::sem::Time /* d_org */::sub_variant_get_kind))
    .def("__repr__", [](org::sem::Time const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Time const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::TimeRange /* d_org */, org::sem::Org>(m, "TimeRange")
    .def("__init__",
         [](org::sem::TimeRange* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::TimeRange /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("from_", &org::sem::TimeRange /* d_org */::from, R"RAW(Starting time)RAW")
    .def_rw("to", &org::sem::TimeRange /* d_org */::to, R"RAW(Finishing time)RAW")
    .def("getClockedTimeSeconds", static_cast<hstd::Opt<int64_t>(org::sem::TimeRange /* d_org */::*)() const>(&org::sem::TimeRange /* d_org */::getClockedTimeSeconds))
    .def("__repr__", [](org::sem::TimeRange const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::TimeRange const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Macro /* d_org */, org::sem::Org>(m, "Macro")
    .def("__init__",
         [](org::sem::Macro* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Macro /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::Macro /* d_org */::name, R"RAW(Macro name)RAW")
    .def_rw("attrs", &org::sem::Macro /* d_org */::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def("__repr__", [](org::sem::Macro const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Macro const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Symbol::Param>(m, "SymbolParam")
    .def("__init__",
         [](org::sem::Symbol::Param* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Symbol::Param();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("key", &org::sem::Symbol::Param::key, R"RAW(Key -- for non-positional)RAW")
    .def_rw("value", &org::sem::Symbol::Param::value, R"RAW(Uninterpreted value)RAW")
    .def("__repr__", [](org::sem::Symbol::Param const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Symbol::Param const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Symbol /* d_org */, org::sem::Org>(m, "Symbol")
    .def("__init__",
         [](org::sem::Symbol* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Symbol /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::Symbol /* d_org */::name, R"RAW(Name of the symbol)RAW")
    .def_rw("parameters", &org::sem::Symbol /* d_org */::parameters, R"RAW(Optional list of parameters)RAW")
    .def_rw("positional", &org::sem::Symbol /* d_org */::positional, R"RAW(Positional parameters)RAW")
    .def("__repr__", [](org::sem::Symbol const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Symbol const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::ErrorSkipGroup /* d_org */, org::sem::Org>(m, "ErrorSkipGroup")
    .def("__init__",
         [](org::sem::ErrorSkipGroup* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::ErrorSkipGroup /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("skipped", &org::sem::ErrorSkipGroup /* d_org */::skipped)
    .def("__repr__", [](org::sem::ErrorSkipGroup const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ErrorSkipGroup const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Markup /* d_org */, org::sem::Org>(m, "Markup")
    ;
  nanobind::class_<org::sem::RadioTarget /* d_org */, org::sem::Org>(m, "RadioTarget")
    .def("__init__",
         [](org::sem::RadioTarget* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::RadioTarget /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("words", &org::sem::RadioTarget /* d_org */::words)
    .def("__repr__", [](org::sem::RadioTarget const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::RadioTarget const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Latex /* d_org */, org::sem::Org>(m, "Latex")
    .def("__init__",
         [](org::sem::Latex* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Latex /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Latex const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Latex const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::SubtreeLog /* d_org */, org::sem::Org>(m, "SubtreeLog")
    .def("__init__",
         [](org::sem::SubtreeLog* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::SubtreeLog /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("head", &org::sem::SubtreeLog /* d_org */::head)
    .def_rw("desc", &org::sem::SubtreeLog /* d_org */::desc, R"RAW(Optional description of the log entry)RAW")
    .def("setDescription",
         static_cast<void(org::sem::SubtreeLog /* d_org */::*)(org::sem::SemId<org::sem::StmtList>)>(&org::sem::SubtreeLog /* d_org */::setDescription),
         nanobind::arg("desc"))
    .def("__repr__", [](org::sem::SubtreeLog const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::SubtreeLog const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Subtree /* d_org */, org::sem::Org>(m, "Subtree")
    .def("__init__",
         [](org::sem::Subtree* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Subtree /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("level", &org::sem::Subtree /* d_org */::level, R"RAW(Subtree level)RAW")
    .def_rw("treeId", &org::sem::Subtree /* d_org */::treeId, R"RAW(:ID: property)RAW")
    .def_rw("todo", &org::sem::Subtree /* d_org */::todo, R"RAW(Todo state of the tree)RAW")
    .def_rw("completion", &org::sem::Subtree /* d_org */::completion, R"RAW(Task completion state)RAW")
    .def_rw("description", &org::sem::Subtree /* d_org */::description)
    .def_rw("tags", &org::sem::Subtree /* d_org */::tags, R"RAW(Trailing tags)RAW")
    .def_rw("title", &org::sem::Subtree /* d_org */::title, R"RAW(Main title)RAW")
    .def_rw("logbook", &org::sem::Subtree /* d_org */::logbook, R"RAW(Associated subtree log)RAW")
    .def_rw("properties", &org::sem::Subtree /* d_org */::properties, R"RAW(Immediate properties)RAW")
    .def_rw("closed", &org::sem::Subtree /* d_org */::closed, R"RAW(When subtree was marked as closed)RAW")
    .def_rw("deadline", &org::sem::Subtree /* d_org */::deadline, R"RAW(When is the deadline)RAW")
    .def_rw("scheduled", &org::sem::Subtree /* d_org */::scheduled, R"RAW(When the event is scheduled)RAW")
    .def_rw("isComment", &org::sem::Subtree /* d_org */::isComment, R"RAW(Subtree is annotated with the COMMENT keyword)RAW")
    .def_rw("isArchived", &org::sem::Subtree /* d_org */::isArchived, R"RAW(Subtree is tagged with `:ARCHIVE:` tag)RAW")
    .def_rw("priority", &org::sem::Subtree /* d_org */::priority)
    .def("getTimePeriods",
         static_cast<hstd::Vec<org::sem::SubtreePeriod>(org::sem::Subtree /* d_org */::*)(hstd::IntSet<org::sem::SubtreePeriod::Kind>) const>(&org::sem::Subtree /* d_org */::getTimePeriods),
         nanobind::arg("kinds"))
    .def("getProperties",
         static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Subtree /* d_org */::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree /* d_org */::getProperties),
         nanobind::arg("kind"),
         nanobind::arg("subkind") = std::nullopt)
    .def("getProperty",
         static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Subtree /* d_org */::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Subtree /* d_org */::getProperty),
         nanobind::arg("kind"),
         nanobind::arg("subkind") = std::nullopt)
    .def("removeProperty",
         static_cast<void(org::sem::Subtree /* d_org */::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree /* d_org */::removeProperty),
         nanobind::arg("kind"),
         nanobind::arg("subkind") = std::nullopt,
         R"RAW(Remove all instances of the property with matching kind/subkind from the property list)RAW")
    .def("setProperty",
         static_cast<void(org::sem::Subtree /* d_org */::*)(org::sem::NamedProperty const&)>(&org::sem::Subtree /* d_org */::setProperty),
         nanobind::arg("value"),
         R"RAW(Create or override existing property value in the subtree property list)RAW")
    .def("setPropertyStrValue",
         static_cast<void(org::sem::Subtree /* d_org */::*)(hstd::Str const&, hstd::Str const&, hstd::Opt<hstd::Str> const&)>(&org::sem::Subtree /* d_org */::setPropertyStrValue),
         nanobind::arg("value"),
         nanobind::arg("kind"),
         nanobind::arg("subkind") = std::nullopt,
         R"RAW(Assign a raw string literal to a property.)RAW")
    .def("getCleanTitle", static_cast<hstd::Str(org::sem::Subtree /* d_org */::*)() const>(&org::sem::Subtree /* d_org */::getCleanTitle), R"RAW(Get subtree title as a flat string, without markup nodes, but with all left strings)RAW")
    .def("getTodoKeyword", static_cast<hstd::Opt<hstd::Str>(org::sem::Subtree /* d_org */::*)() const>(&org::sem::Subtree /* d_org */::getTodoKeyword))
    .def("__repr__", [](org::sem::Subtree const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Subtree const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::ColonExample /* d_org */, org::sem::Org>(m, "ColonExample")
    .def("__init__",
         [](org::sem::ColonExample* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::ColonExample /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::ColonExample const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ColonExample const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Call /* d_org */, org::sem::Org>(m, "Call")
    .def("__init__",
         [](org::sem::Call* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Call /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::Call /* d_org */::name, R"RAW(Call target name)RAW")
    .def_rw("attrs", &org::sem::Call /* d_org */::attrs, R"RAW(Additional parameters aside from 'exporter')RAW")
    .def_rw("isCommand", &org::sem::Call /* d_org */::isCommand)
    .def("__repr__", [](org::sem::Call const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Call const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::ListItem /* d_org */, org::sem::Org>(m, "ListItem")
    .def("__init__",
         [](org::sem::ListItem* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::ListItem /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("checkbox", &org::sem::ListItem /* d_org */::checkbox)
    .def_rw("header", &org::sem::ListItem /* d_org */::header, R"RAW(Description list item header)RAW")
    .def_rw("bullet", &org::sem::ListItem /* d_org */::bullet, R"RAW(Full text of the numbered list item, e.g. `a)`, `a.`)RAW")
    .def("isDescriptionItem", static_cast<bool(org::sem::ListItem /* d_org */::*)() const>(&org::sem::ListItem /* d_org */::isDescriptionItem))
    .def("getCleanHeader", static_cast<hstd::Opt<hstd::Str>(org::sem::ListItem /* d_org */::*)() const>(&org::sem::ListItem /* d_org */::getCleanHeader), R"RAW(Return flat text for the description list header)RAW")
    .def("__repr__", [](org::sem::ListItem const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ListItem const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::DocumentOptions /* d_org */, org::sem::Org>(m, "DocumentOptions")
    .def("__init__",
         [](org::sem::DocumentOptions* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::DocumentOptions /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("initialVisibility", &org::sem::DocumentOptions /* d_org */::initialVisibility)
    .def_rw("properties", &org::sem::DocumentOptions /* d_org */::properties)
    .def_rw("exportConfig", &org::sem::DocumentOptions /* d_org */::exportConfig)
    .def_rw("fixedWidthSections", &org::sem::DocumentOptions /* d_org */::fixedWidthSections)
    .def_rw("startupIndented", &org::sem::DocumentOptions /* d_org */::startupIndented)
    .def_rw("category", &org::sem::DocumentOptions /* d_org */::category)
    .def_rw("setupfile", &org::sem::DocumentOptions /* d_org */::setupfile)
    .def_rw("maxSubtreeLevelExport", &org::sem::DocumentOptions /* d_org */::maxSubtreeLevelExport)
    .def_rw("columns", &org::sem::DocumentOptions /* d_org */::columns)
    .def_rw("todoKeywords", &org::sem::DocumentOptions /* d_org */::todoKeywords)
    .def_rw("doneKeywords", &org::sem::DocumentOptions /* d_org */::doneKeywords)
    .def("getProperties",
         static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::DocumentOptions /* d_org */::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions /* d_org */::getProperties),
         nanobind::arg("kind"),
         nanobind::arg("subKind") = std::nullopt)
    .def("getProperty",
         static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::DocumentOptions /* d_org */::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::DocumentOptions /* d_org */::getProperty),
         nanobind::arg("kind"),
         nanobind::arg("subKind") = std::nullopt)
    .def("__repr__", [](org::sem::DocumentOptions const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentOptions const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::DocumentFragment /* d_org */, org::sem::Org>(m, "DocumentFragment")
    .def("__init__",
         [](org::sem::DocumentFragment* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::DocumentFragment /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("baseLine", &org::sem::DocumentFragment /* d_org */::baseLine)
    .def_rw("baseCol", &org::sem::DocumentFragment /* d_org */::baseCol)
    .def("__repr__", [](org::sem::DocumentFragment const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentFragment const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::CriticMarkup::Kind>(m, "CriticMarkupKind", type_registry_guard);
  nanobind::enum_<org::sem::CriticMarkup::Kind>(m, "CriticMarkupKind")
    .value("Deletion", org::sem::CriticMarkup::Kind::Deletion)
    .value("Addition", org::sem::CriticMarkup::Kind::Addition)
    .value("Substitution", org::sem::CriticMarkup::Kind::Substitution)
    .value("Highlighting", org::sem::CriticMarkup::Kind::Highlighting)
    .value("Comment", org::sem::CriticMarkup::Kind::Comment)
    .def("__iter__", [](org::sem::CriticMarkup::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::CriticMarkup::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::CriticMarkup::Kind>();
                     })
    .def("__int__", [](org::sem::CriticMarkup::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::CriticMarkup::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::CriticMarkup::Kind lhs, org::sem::CriticMarkup::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::CriticMarkup::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::CriticMarkup /* d_org */, org::sem::Org>(m, "CriticMarkup")
    .def("__init__",
         [](org::sem::CriticMarkup* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CriticMarkup /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("kind", &org::sem::CriticMarkup /* d_org */::kind)
    .def("__repr__", [](org::sem::CriticMarkup const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CriticMarkup const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Document /* d_org */, org::sem::Org>(m, "Document")
    .def("__init__",
         [](org::sem::Document* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Document /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("title", &org::sem::Document /* d_org */::title)
    .def_rw("author", &org::sem::Document /* d_org */::author)
    .def_rw("creator", &org::sem::Document /* d_org */::creator)
    .def_rw("filetags", &org::sem::Document /* d_org */::filetags)
    .def_rw("email", &org::sem::Document /* d_org */::email)
    .def_rw("language", &org::sem::Document /* d_org */::language)
    .def_rw("options", &org::sem::Document /* d_org */::options)
    .def_rw("exportFileName", &org::sem::Document /* d_org */::exportFileName)
    .def("getProperties",
         static_cast<hstd::Vec<org::sem::NamedProperty>(org::sem::Document /* d_org */::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document /* d_org */::getProperties),
         nanobind::arg("kind"),
         nanobind::arg("subKind") = std::nullopt)
    .def("getProperty",
         static_cast<hstd::Opt<org::sem::NamedProperty>(org::sem::Document /* d_org */::*)(hstd::Str const&, hstd::Opt<hstd::Str> const&) const>(&org::sem::Document /* d_org */::getProperty),
         nanobind::arg("kind"),
         nanobind::arg("subKind") = std::nullopt)
    .def("__repr__", [](org::sem::Document const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Document const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::FileTarget /* d_org */, org::sem::Org>(m, "FileTarget")
    .def("__init__",
         [](org::sem::FileTarget* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::FileTarget /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("path", &org::sem::FileTarget /* d_org */::path)
    .def_rw("line", &org::sem::FileTarget /* d_org */::line)
    .def_rw("searchTarget", &org::sem::FileTarget /* d_org */::searchTarget)
    .def_rw("restrictToHeadlines", &org::sem::FileTarget /* d_org */::restrictToHeadlines)
    .def_rw("targetId", &org::sem::FileTarget /* d_org */::targetId)
    .def_rw("regexp", &org::sem::FileTarget /* d_org */::regexp)
    .def("__repr__", [](org::sem::FileTarget const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::FileTarget const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::TextSeparator /* d_org */, org::sem::Org>(m, "TextSeparator")
    .def("__init__",
         [](org::sem::TextSeparator* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::TextSeparator /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::TextSeparator const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::TextSeparator const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::DocumentGroup /* d_org */, org::sem::Org>(m, "DocumentGroup")
    .def("__init__",
         [](org::sem::DocumentGroup* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::DocumentGroup /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::DocumentGroup const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::DocumentGroup const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::File::Document>(m, "FileDocument")
    .def("__init__",
         [](org::sem::File::Document* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::File::Document();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::File::Document const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::File::Document const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::File::Attachment>(m, "FileAttachment")
    .def("__init__",
         [](org::sem::File::Attachment* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::File::Attachment();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::File::Attachment const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::File::Attachment const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::File::Source>(m, "FileSource")
    .def("__init__",
         [](org::sem::File::Source* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::File::Source();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::File::Source const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::File::Source const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::File::Kind>(m, "FileKind", type_registry_guard);
  nanobind::enum_<org::sem::File::Kind>(m, "FileKind")
    .value("Document", org::sem::File::Kind::Document)
    .value("Attachment", org::sem::File::Kind::Attachment)
    .value("Source", org::sem::File::Kind::Source)
    .def("__iter__", [](org::sem::File::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::File::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::File::Kind>();
                     })
    .def("__int__", [](org::sem::File::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::File::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::File::Kind lhs, org::sem::File::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::File::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::File /* d_org */, org::sem::Org>(m, "File")
    .def("__init__",
         [](org::sem::File* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::File /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("relPath", &org::sem::File /* d_org */::relPath, R"RAW(Relative path from the root directory)RAW")
    .def_rw("absPath", &org::sem::File /* d_org */::absPath, R"RAW(Absolute resolved path to physical file)RAW")
    .def("isDocument", static_cast<bool(org::sem::File /* d_org */::*)() const>(&org::sem::File /* d_org */::isDocument))
    .def("getDocument", static_cast<org::sem::File::Document&(org::sem::File /* d_org */::*)()>(&org::sem::File /* d_org */::getDocument))
    .def("isAttachment", static_cast<bool(org::sem::File /* d_org */::*)() const>(&org::sem::File /* d_org */::isAttachment))
    .def("getAttachment", static_cast<org::sem::File::Attachment&(org::sem::File /* d_org */::*)()>(&org::sem::File /* d_org */::getAttachment))
    .def("isSource", static_cast<bool(org::sem::File /* d_org */::*)() const>(&org::sem::File /* d_org */::isSource))
    .def("getSource", static_cast<org::sem::File::Source&(org::sem::File /* d_org */::*)()>(&org::sem::File /* d_org */::getSource))
    .def_static("getFileKindStatic",
                static_cast<org::sem::File::Kind(*)(org::sem::File::Data const&)>(&org::sem::File /* d_org */::getFileKind),
                nanobind::arg("__input"))
    .def("getFileKind", static_cast<org::sem::File::Kind(org::sem::File /* d_org */::*)() const>(&org::sem::File /* d_org */::getFileKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::File /* d_org */::*)() const>(&org::sem::File /* d_org */::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::File::Data const&(org::sem::File /* d_org */::*)() const>(&org::sem::File /* d_org */::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::File::Kind(org::sem::File /* d_org */::*)() const>(&org::sem::File /* d_org */::sub_variant_get_kind))
    .def("__repr__", [](org::sem::File const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::File const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Directory /* d_org */, org::sem::Org>(m, "Directory")
    .def("__init__",
         [](org::sem::Directory* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Directory /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("relPath", &org::sem::Directory /* d_org */::relPath, R"RAW(Relative path from the root directory, empty if this is the root directory)RAW")
    .def_rw("absPath", &org::sem::Directory /* d_org */::absPath, R"RAW(Absolute resolved path to physical directory)RAW")
    .def("__repr__", [](org::sem::Directory const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Directory const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Symlink /* d_org */, org::sem::Org>(m, "Symlink")
    .def("__init__",
         [](org::sem::Symlink* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Symlink /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("isDirectory", &org::sem::Symlink /* d_org */::isDirectory)
    .def_rw("absPath", &org::sem::Symlink /* d_org */::absPath, R"RAW(Absolute path to the symlinked target directory. All relative paths under symlink node use its absolute path as a root.)RAW")
    .def("__repr__", [](org::sem::Symlink const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Symlink const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeIncludeBase")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::CmdInclude::IncludeBase* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdInclude::IncludeBase();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::CmdInclude::IncludeBase const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::IncludeBase const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdInclude::Example, org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeExample")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::CmdInclude::Example* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdInclude::Example();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::CmdInclude::Example const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::Example const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdInclude::Export, org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeExport")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::CmdInclude::Export* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdInclude::Export();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("language", &org::sem::CmdInclude::Export::language, R"RAW(Source code language for export)RAW")
    .def("__repr__", [](org::sem::CmdInclude::Export const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::Export const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdInclude::Custom, org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeCustom")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::CmdInclude::Custom* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdInclude::Custom();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("blockName", &org::sem::CmdInclude::Custom::blockName, R"RAW(Block name not covered by the default values)RAW")
    .def("__repr__", [](org::sem::CmdInclude::Custom const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::Custom const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdInclude::Src, org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeSrc")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::CmdInclude::Src* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdInclude::Src();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("language", &org::sem::CmdInclude::Src::language, R"RAW(Source code language for code block)RAW")
    .def("__repr__", [](org::sem::CmdInclude::Src const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::Src const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdInclude::OrgDocument, org::sem::CmdInclude::IncludeBase>(m, "CmdIncludeOrgDocument")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::sem::CmdInclude::OrgDocument* result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdInclude::OrgDocument();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("onlyContent", &org::sem::CmdInclude::OrgDocument::onlyContent, R"RAW(omits any planning lines or property drawers)RAW")
    .def_rw("subtreePath", &org::sem::CmdInclude::OrgDocument::subtreePath, R"RAW(Include first subtree matching path with `file.org::* tree`)RAW")
    .def_rw("minLevel", &org::sem::CmdInclude::OrgDocument::minLevel, R"RAW(The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.)RAW")
    .def_rw("customIdTarget", &org::sem::CmdInclude::OrgDocument::customIdTarget, R"RAW(Include target subtree content with `file.org::#custom`)RAW")
    .def("__repr__", [](org::sem::CmdInclude::OrgDocument const& _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude::OrgDocument const& _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::sem::CmdInclude::Kind>(m, "CmdIncludeKind", type_registry_guard);
  nanobind::enum_<org::sem::CmdInclude::Kind>(m, "CmdIncludeKind")
    .value("Example", org::sem::CmdInclude::Kind::Example)
    .value("Export", org::sem::CmdInclude::Kind::Export)
    .value("Custom", org::sem::CmdInclude::Kind::Custom)
    .value("Src", org::sem::CmdInclude::Kind::Src)
    .value("OrgDocument", org::sem::CmdInclude::Kind::OrgDocument)
    .def("__iter__", [](org::sem::CmdInclude::Kind const& _self) -> org::bind::python::PyEnumIterator<org::sem::CmdInclude::Kind> {
                     return org::bind::python::PyEnumIterator<org::sem::CmdInclude::Kind>();
                     })
    .def("__int__", [](org::sem::CmdInclude::Kind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::sem::CmdInclude::Kind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::sem::CmdInclude::Kind lhs, org::sem::CmdInclude::Kind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::sem::CmdInclude::Kind it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::sem::CmdInclude /* d_org */, org::sem::Org>(m, "CmdInclude")
    .def("__init__",
         [](org::sem::CmdInclude* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdInclude /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("path", &org::sem::CmdInclude /* d_org */::path, R"RAW(Path to include)RAW")
    .def_rw("firstLine", &org::sem::CmdInclude /* d_org */::firstLine, R"RAW(0-based index of the first line to include. NOTE: Org-mode syntax uses 1-based half-open range in the text)RAW")
    .def_rw("lastLine", &org::sem::CmdInclude /* d_org */::lastLine, R"RAW(0-based index of the last line to include)RAW")
    .def("isExample", static_cast<bool(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::isExample))
    .def("getExample", static_cast<org::sem::CmdInclude::Example&(org::sem::CmdInclude /* d_org */::*)()>(&org::sem::CmdInclude /* d_org */::getExample))
    .def("isExport", static_cast<bool(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::isExport))
    .def("getExport", static_cast<org::sem::CmdInclude::Export&(org::sem::CmdInclude /* d_org */::*)()>(&org::sem::CmdInclude /* d_org */::getExport))
    .def("isCustom", static_cast<bool(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::isCustom))
    .def("getCustom", static_cast<org::sem::CmdInclude::Custom&(org::sem::CmdInclude /* d_org */::*)()>(&org::sem::CmdInclude /* d_org */::getCustom))
    .def("isSrc", static_cast<bool(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::isSrc))
    .def("getSrc", static_cast<org::sem::CmdInclude::Src&(org::sem::CmdInclude /* d_org */::*)()>(&org::sem::CmdInclude /* d_org */::getSrc))
    .def("isOrgDocument", static_cast<bool(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::isOrgDocument))
    .def("getOrgDocument", static_cast<org::sem::CmdInclude::OrgDocument&(org::sem::CmdInclude /* d_org */::*)()>(&org::sem::CmdInclude /* d_org */::getOrgDocument))
    .def_static("getIncludeKindStatic",
                static_cast<org::sem::CmdInclude::Kind(*)(org::sem::CmdInclude::Data const&)>(&org::sem::CmdInclude /* d_org */::getIncludeKind),
                nanobind::arg("__input"))
    .def("getIncludeKind", static_cast<org::sem::CmdInclude::Kind(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::getIncludeKind))
    .def("sub_variant_get_name", static_cast<char const*(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::sub_variant_get_name))
    .def("sub_variant_get_data", static_cast<org::sem::CmdInclude::Data const&(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::sub_variant_get_data))
    .def("sub_variant_get_kind", static_cast<org::sem::CmdInclude::Kind(org::sem::CmdInclude /* d_org */::*)() const>(&org::sem::CmdInclude /* d_org */::sub_variant_get_kind))
    .def("__repr__", [](org::sem::CmdInclude const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdInclude const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmNoNode /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTNoNode")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmErrorItem /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTErrorItem")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmErrorGroup /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTErrorGroup")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmStmt /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTStmt")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmInline /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTInline")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmStmtList /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTStmtList")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmEmpty /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTEmpty")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmd /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCmd")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlock /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTBlock")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmLineCommand /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTLineCommand")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmAttached /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTAttached")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmLeaf /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTLeaf")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdCaption /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCmdCaption")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdCreator /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCmdCreator")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdAuthor /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCmdAuthor")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdEmail /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCmdEmail")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdLanguage /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCmdLanguage")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdColumns /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCmdColumns")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdName /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCmdName")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdCustomArgs /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCmdCustomArgs")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdCustomRaw /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCmdCustomRaw")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdCustomText /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCmdCustomText")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdCall /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCmdCall")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdTblfm /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCmdTblfm")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmHashTag /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTHashTag")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmInlineFootnote /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTInlineFootnote")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmInlineExport /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTInlineExport")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmTime /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTTime")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmTimeRange /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTTimeRange")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmMacro /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTMacro")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmSymbol /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTSymbol")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmEscaped /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTEscaped")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmNewline /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTNewline")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmSpace /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTSpace")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmWord /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTWord")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmAtMention /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTAtMention")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmRawText /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTRawText")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmPunctuation /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTPunctuation")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmPlaceholder /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTPlaceholder")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBigIdent /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTBigIdent")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmTextTarget /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTTextTarget")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmErrorSkipToken /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTErrorSkipToken")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmErrorSkipGroup /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTErrorSkipGroup")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmMarkup /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTMarkup")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBold /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTBold")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmUnderline /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTUnderline")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmMonospace /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTMonospace")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmMarkQuote /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTMarkQuote")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmVerbatim /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTVerbatim")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmItalic /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTItalic")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmStrike /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTStrike")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmPar /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTPar")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmRadioTarget /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTRadioTarget")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmLatex /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTLatex")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmLink /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTLink")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockCenter /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTBlockCenter")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockQuote /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTBlockQuote")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockComment /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTBlockComment")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockVerse /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTBlockVerse")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockDynamicFallback /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTBlockDynamicFallback")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockExample /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTBlockExample")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockExport /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTBlockExport")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockAdmonition /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTBlockAdmonition")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTBlockCodeEvalResult")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmBlockCode /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTBlockCode")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmSubtreeLog /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTSubtreeLog")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmSubtree /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTSubtree")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCell /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCell")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmRow /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTRow")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmTable /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTTable")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmParagraph /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTParagraph")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmColonExample /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTColonExample")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdAttr /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCmdAttr")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdExport /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCmdExport")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCall /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCall")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmList /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTList")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmListItem /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTListItem")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmDocumentOptions /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTDocumentOptions")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmDocumentFragment /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTDocumentFragment")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCriticMarkup /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCriticMarkup")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmDocument /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTDocument")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmFileTarget /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTFileTarget")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmTextSeparator /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTTextSeparator")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmDocumentGroup /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTDocumentGroup")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmFile /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTFile")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmDirectory /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTDirectory")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmSymlink /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTSymlink")
    ;
  nanobind::class_<org::imm::ImmIdT<org::imm::ImmCmdInclude /* d_orgimm_write */>, org::imm::ImmId>(m, "ImmIdTCmdInclude")
    ;
  nanobind::class_<org::imm::ImmTime::Repeat /* imm_write */>(m, "ImmTimeRepeat")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::imm::ImmTime::Repeat* /* imm_write */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::imm::ImmTime::Repeat /* imm_write */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("mode", &org::imm::ImmTime::Repeat /* imm_write */::mode, R"RAW(mode)RAW")
    .def_rw("period", &org::imm::ImmTime::Repeat /* imm_write */::period, R"RAW(period)RAW")
    .def_rw("count", &org::imm::ImmTime::Repeat /* imm_write */::count, R"RAW(count)RAW")
    .def("__eq__",
         static_cast<bool(org::imm::ImmTime::Repeat /* imm_write */::*)(org::imm::ImmTime::Repeat const& /* imm_write */) const>(&org::imm::ImmTime::Repeat /* imm_write */::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmTime::Repeat const& /* imm_write */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmTime::Repeat const& /* imm_write */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmTime::Static /* imm_write */>(m, "ImmTimeStatic")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::imm::ImmTime::Static* /* imm_write */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::imm::ImmTime::Static /* imm_write */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("repeat", &org::imm::ImmTime::Static /* imm_write */::repeat)
    .def_rw("warn", &org::imm::ImmTime::Static /* imm_write */::warn)
    .def_rw("time", &org::imm::ImmTime::Static /* imm_write */::time)
    .def("__eq__",
         static_cast<bool(org::imm::ImmTime::Static /* imm_write */::*)(org::imm::ImmTime::Static const& /* imm_write */) const>(&org::imm::ImmTime::Static /* imm_write */::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmTime::Static const& /* imm_write */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmTime::Static const& /* imm_write */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmTime::Dynamic /* imm_write */>(m, "ImmTimeDynamic")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::imm::ImmTime::Dynamic* /* imm_write */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::imm::ImmTime::Dynamic /* imm_write */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("expr", &org::imm::ImmTime::Dynamic /* imm_write */::expr)
    .def("__eq__",
         static_cast<bool(org::imm::ImmTime::Dynamic /* imm_write */::*)(org::imm::ImmTime::Dynamic const& /* imm_write */) const>(&org::imm::ImmTime::Dynamic /* imm_write */::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmTime::Dynamic const& /* imm_write */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmTime::Dynamic const& /* imm_write */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::imm::ImmTime::TimeKind /* imm_write */>(m, "ImmTimeTimeKind", type_registry_guard);
  nanobind::enum_<org::imm::ImmTime::TimeKind /* imm_write */>(m, "ImmTimeTimeKind")
    .value("Static", org::imm::ImmTime::TimeKind /* imm_write */::Static)
    .value("Dynamic", org::imm::ImmTime::TimeKind /* imm_write */::Dynamic)
    .def("__iter__", [](org::imm::ImmTime::TimeKind const& /* imm_write */ _self) -> org::bind::python::PyEnumIterator<org::imm::ImmTime::TimeKind /* imm_write */> {
                     return org::bind::python::PyEnumIterator<org::imm::ImmTime::TimeKind /* imm_write */>();
                     })
    .def("__int__", [](org::imm::ImmTime::TimeKind const& /* imm_write */ _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::imm::ImmTime::TimeKind const& /* imm_write */ _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::imm::ImmTime::TimeKind /* imm_write */ lhs, org::imm::ImmTime::TimeKind /* imm_write */ rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::imm::ImmTime::TimeKind /* imm_write */ it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::imm::ImmSymbol::Param /* imm_write */>(m, "ImmSymbolParam")
    .def("__init__",
         [](org::imm::ImmSymbol::Param* /* imm_write */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::imm::ImmSymbol::Param /* imm_write */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("key", &org::imm::ImmSymbol::Param /* imm_write */::key, R"RAW(Key -- for non-positional)RAW")
    .def_rw("value", &org::imm::ImmSymbol::Param /* imm_write */::value, R"RAW(Uninterpreted value)RAW")
    .def("__eq__",
         static_cast<bool(org::imm::ImmSymbol::Param /* imm_write */::*)(org::imm::ImmSymbol::Param const& /* imm_write */) const>(&org::imm::ImmSymbol::Param /* imm_write */::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmSymbol::Param const& /* imm_write */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmSymbol::Param const& /* imm_write */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmFile::Document /* imm_write */>(m, "ImmFileDocument")
    .def("__init__",
         [](org::imm::ImmFile::Document* /* imm_write */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::imm::ImmFile::Document /* imm_write */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::imm::ImmFile::Document /* imm_write */::*)(org::imm::ImmFile::Document const& /* imm_write */) const>(&org::imm::ImmFile::Document /* imm_write */::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmFile::Document const& /* imm_write */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmFile::Document const& /* imm_write */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmFile::Attachment /* imm_write */>(m, "ImmFileAttachment")
    .def("__init__",
         [](org::imm::ImmFile::Attachment* /* imm_write */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::imm::ImmFile::Attachment /* imm_write */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::imm::ImmFile::Attachment /* imm_write */::*)(org::imm::ImmFile::Attachment const& /* imm_write */) const>(&org::imm::ImmFile::Attachment /* imm_write */::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmFile::Attachment const& /* imm_write */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmFile::Attachment const& /* imm_write */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmFile::Source /* imm_write */>(m, "ImmFileSource")
    .def("__init__",
         [](org::imm::ImmFile::Source* /* imm_write */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::imm::ImmFile::Source /* imm_write */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::imm::ImmFile::Source /* imm_write */::*)(org::imm::ImmFile::Source const& /* imm_write */) const>(&org::imm::ImmFile::Source /* imm_write */::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmFile::Source const& /* imm_write */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmFile::Source const& /* imm_write */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::imm::ImmFile::Kind /* imm_write */>(m, "ImmFileKind", type_registry_guard);
  nanobind::enum_<org::imm::ImmFile::Kind /* imm_write */>(m, "ImmFileKind")
    .value("Document", org::imm::ImmFile::Kind /* imm_write */::Document)
    .value("Attachment", org::imm::ImmFile::Kind /* imm_write */::Attachment)
    .value("Source", org::imm::ImmFile::Kind /* imm_write */::Source)
    .def("__iter__", [](org::imm::ImmFile::Kind const& /* imm_write */ _self) -> org::bind::python::PyEnumIterator<org::imm::ImmFile::Kind /* imm_write */> {
                     return org::bind::python::PyEnumIterator<org::imm::ImmFile::Kind /* imm_write */>();
                     })
    .def("__int__", [](org::imm::ImmFile::Kind const& /* imm_write */ _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::imm::ImmFile::Kind const& /* imm_write */ _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::imm::ImmFile::Kind /* imm_write */ lhs, org::imm::ImmFile::Kind /* imm_write */ rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::imm::ImmFile::Kind /* imm_write */ it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org::imm::ImmCmdInclude::IncludeBase /* imm_write */>(m, "ImmCmdIncludeIncludeBase")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::imm::ImmCmdInclude::IncludeBase* /* imm_write */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::imm::ImmCmdInclude::IncludeBase /* imm_write */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::imm::ImmCmdInclude::IncludeBase /* imm_write */::*)(org::imm::ImmCmdInclude::IncludeBase const& /* imm_write */) const>(&org::imm::ImmCmdInclude::IncludeBase /* imm_write */::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmCmdInclude::IncludeBase const& /* imm_write */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmCmdInclude::IncludeBase const& /* imm_write */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmCmdInclude::Example /* imm_write */, org::imm::ImmCmdInclude::IncludeBase /* imm_write */>(m, "ImmCmdIncludeExample")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::imm::ImmCmdInclude::Example* /* imm_write */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::imm::ImmCmdInclude::Example /* imm_write */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__eq__",
         static_cast<bool(org::imm::ImmCmdInclude::Example /* imm_write */::*)(org::imm::ImmCmdInclude::Example const& /* imm_write */) const>(&org::imm::ImmCmdInclude::Example /* imm_write */::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmCmdInclude::Example const& /* imm_write */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmCmdInclude::Example const& /* imm_write */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmCmdInclude::Export /* imm_write */, org::imm::ImmCmdInclude::IncludeBase /* imm_write */>(m, "ImmCmdIncludeExport")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::imm::ImmCmdInclude::Export* /* imm_write */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::imm::ImmCmdInclude::Export /* imm_write */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("language", &org::imm::ImmCmdInclude::Export /* imm_write */::language, R"RAW(Source code language for export)RAW")
    .def("__eq__",
         static_cast<bool(org::imm::ImmCmdInclude::Export /* imm_write */::*)(org::imm::ImmCmdInclude::Export const& /* imm_write */) const>(&org::imm::ImmCmdInclude::Export /* imm_write */::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmCmdInclude::Export const& /* imm_write */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmCmdInclude::Export const& /* imm_write */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmCmdInclude::Custom /* imm_write */, org::imm::ImmCmdInclude::IncludeBase /* imm_write */>(m, "ImmCmdIncludeCustom")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::imm::ImmCmdInclude::Custom* /* imm_write */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::imm::ImmCmdInclude::Custom /* imm_write */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("blockName", &org::imm::ImmCmdInclude::Custom /* imm_write */::blockName, R"RAW(Block name not covered by the default values)RAW")
    .def("__eq__",
         static_cast<bool(org::imm::ImmCmdInclude::Custom /* imm_write */::*)(org::imm::ImmCmdInclude::Custom const& /* imm_write */) const>(&org::imm::ImmCmdInclude::Custom /* imm_write */::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmCmdInclude::Custom const& /* imm_write */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmCmdInclude::Custom const& /* imm_write */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmCmdInclude::Src /* imm_write */, org::imm::ImmCmdInclude::IncludeBase /* imm_write */>(m, "ImmCmdIncludeSrc")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::imm::ImmCmdInclude::Src* /* imm_write */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::imm::ImmCmdInclude::Src /* imm_write */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("language", &org::imm::ImmCmdInclude::Src /* imm_write */::language, R"RAW(Source code language for code block)RAW")
    .def("__eq__",
         static_cast<bool(org::imm::ImmCmdInclude::Src /* imm_write */::*)(org::imm::ImmCmdInclude::Src const& /* imm_write */) const>(&org::imm::ImmCmdInclude::Src /* imm_write */::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmCmdInclude::Src const& /* imm_write */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmCmdInclude::Src const& /* imm_write */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::imm::ImmCmdInclude::OrgDocument /* imm_write */, org::imm::ImmCmdInclude::IncludeBase /* imm_write */>(m, "ImmCmdIncludeOrgDocument")
    .def(nanobind::init<>())
    .def("__init__",
         [](org::imm::ImmCmdInclude::OrgDocument* /* imm_write */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::imm::ImmCmdInclude::OrgDocument /* imm_write */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("onlyContent", &org::imm::ImmCmdInclude::OrgDocument /* imm_write */::onlyContent, R"RAW(omits any planning lines or property drawers)RAW")
    .def_rw("subtreePath", &org::imm::ImmCmdInclude::OrgDocument /* imm_write */::subtreePath, R"RAW(Include first subtree matching path with `file.org::* tree`)RAW")
    .def_rw("minLevel", &org::imm::ImmCmdInclude::OrgDocument /* imm_write */::minLevel, R"RAW(The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.)RAW")
    .def_rw("customIdTarget", &org::imm::ImmCmdInclude::OrgDocument /* imm_write */::customIdTarget, R"RAW(Include target subtree content with `file.org::#custom`)RAW")
    .def("__eq__",
         static_cast<bool(org::imm::ImmCmdInclude::OrgDocument /* imm_write */::*)(org::imm::ImmCmdInclude::OrgDocument const& /* imm_write */) const>(&org::imm::ImmCmdInclude::OrgDocument /* imm_write */::operator==),
         nanobind::arg("other"))
    .def("__repr__", [](org::imm::ImmCmdInclude::OrgDocument const& /* imm_write */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::imm::ImmCmdInclude::OrgDocument const& /* imm_write */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  bind_enum_iterator<org::imm::ImmCmdInclude::Kind /* imm_write */>(m, "ImmCmdIncludeKind", type_registry_guard);
  nanobind::enum_<org::imm::ImmCmdInclude::Kind /* imm_write */>(m, "ImmCmdIncludeKind")
    .value("Example", org::imm::ImmCmdInclude::Kind /* imm_write */::Example)
    .value("Export", org::imm::ImmCmdInclude::Kind /* imm_write */::Export)
    .value("Custom", org::imm::ImmCmdInclude::Kind /* imm_write */::Custom)
    .value("Src", org::imm::ImmCmdInclude::Kind /* imm_write */::Src)
    .value("OrgDocument", org::imm::ImmCmdInclude::Kind /* imm_write */::OrgDocument)
    .def("__iter__", [](org::imm::ImmCmdInclude::Kind const& /* imm_write */ _self) -> org::bind::python::PyEnumIterator<org::imm::ImmCmdInclude::Kind /* imm_write */> {
                     return org::bind::python::PyEnumIterator<org::imm::ImmCmdInclude::Kind /* imm_write */>();
                     })
    .def("__int__", [](org::imm::ImmCmdInclude::Kind const& /* imm_write */ _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org::imm::ImmCmdInclude::Kind const& /* imm_write */ _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org::imm::ImmCmdInclude::Kind /* imm_write */ lhs, org::imm::ImmCmdInclude::Kind /* imm_write */ rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org::imm::ImmCmdInclude::Kind /* imm_write */ it) -> int {
         return static_cast<int>(it);
         })
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1343:17( [780] >record 'ImmAdapterOrgAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterVirtualBase /*  [905]imm/ImmOrg.hpp:1343:17( [780] >record 'ImmAdapterVirtualBase'<>) */>(m, "ImmAdapterOrgAPI")
    ;
  nanobind::class_<org::sem::Cmd /* d_org */, org::sem::Stmt>(m, "Cmd")
    .def_rw("attrs", &org::sem::Cmd /* d_org */::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def("getAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::Cmd /* d_org */::*)(hstd::Opt<hstd::Str> const&) const>(&org::sem::Cmd /* d_org */::getAttrs),
         nanobind::arg("key") = std::nullopt,
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::Cmd /* d_org */::*)(hstd::Str const&) const>(&org::sem::Cmd /* d_org */::getFirstAttr),
         nanobind::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    ;
  nanobind::class_<org::sem::CmdCustomRaw /* d_org */, org::sem::Stmt>(m, "CmdCustomRaw")
    .def("__init__",
         [](org::sem::CmdCustomRaw* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdCustomRaw /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::CmdCustomRaw /* d_org */::name)
    .def_rw("isAttached", &org::sem::CmdCustomRaw /* d_org */::isAttached)
    .def_rw("text", &org::sem::CmdCustomRaw /* d_org */::text)
    .def("__repr__", [](org::sem::CmdCustomRaw const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCustomRaw const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdCustomText /* d_org */, org::sem::Stmt>(m, "CmdCustomText")
    .def("__init__",
         [](org::sem::CmdCustomText* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdCustomText /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::CmdCustomText /* d_org */::name)
    .def_rw("isAttached", &org::sem::CmdCustomText /* d_org */::isAttached)
    .def_rw("text", &org::sem::CmdCustomText /* d_org */::text)
    .def("__repr__", [](org::sem::CmdCustomText const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCustomText const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Link /* d_org */, org::sem::Stmt>(m, "Link")
    .def("__init__",
         [](org::sem::Link* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Link /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("description", &org::sem::Link /* d_org */::description)
    .def_rw("target", &org::sem::Link /* d_org */::target)
    .def("__repr__", [](org::sem::Link const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Link const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockComment /* d_org */, org::sem::Stmt>(m, "BlockComment")
    .def("__init__",
         [](org::sem::BlockComment* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::BlockComment /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::BlockComment const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockComment const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Paragraph /* d_org */, org::sem::Stmt>(m, "Paragraph")
    .def("__init__",
         [](org::sem::Paragraph* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Paragraph /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("isFootnoteDefinition", static_cast<bool(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::isFootnoteDefinition))
    .def("getFootnoteName", static_cast<hstd::Opt<hstd::Str>(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::getFootnoteName))
    .def("hasAdmonition", static_cast<bool(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::hasAdmonition))
    .def("getAdmonitions", static_cast<hstd::Vec<hstd::Str>(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::getAdmonitions))
    .def("getAdmonitionNodes", static_cast<hstd::Vec<org::sem::SemId<org::sem::BigIdent>>(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::getAdmonitionNodes))
    .def("hasTimestamp", static_cast<bool(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::hasTimestamp))
    .def("getTimestamps", static_cast<hstd::Vec<hstd::UserTime>(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::getTimestamps))
    .def("getTimestampNodes", static_cast<hstd::Vec<org::sem::SemId<org::sem::Time>>(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::getTimestampNodes))
    .def("hasLeadHashtags", static_cast<bool(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::hasLeadHashtags))
    .def("getLeadHashtags", static_cast<hstd::Vec<org::sem::SemId<org::sem::HashTag>>(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::getLeadHashtags))
    .def("getBody", static_cast<hstd::Vec<org::sem::SemId<org::sem::Org>>(org::sem::Paragraph /* d_org */::*)() const>(&org::sem::Paragraph /* d_org */::getBody), R"RAW(Return content of the paragraph, without prefix idents, hashtags, footnotes etc. )RAW")
    .def("__repr__", [](org::sem::Paragraph const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Paragraph const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::List /* d_org */, org::sem::Stmt>(m, "List")
    .def("__init__",
         [](org::sem::List* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::List /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("getListAttrs",
         static_cast<hstd::Vec<org::sem::AttrValue>(org::sem::List /* d_org */::*)(hstd::Str const&) const>(&org::sem::List /* d_org */::getListAttrs),
         nanobind::arg("key"))
    .def("getListFormattingMode", static_cast<ListFormattingMode(org::sem::List /* d_org */::*)() const>(&org::sem::List /* d_org */::getListFormattingMode))
    .def("isDescriptionList", static_cast<bool(org::sem::List /* d_org */::*)() const>(&org::sem::List /* d_org */::isDescriptionList), R"RAW(List is marked as description if any list item has a header)RAW")
    .def("isNumberedList", static_cast<bool(org::sem::List /* d_org */::*)() const>(&org::sem::List /* d_org */::isNumberedList), R"RAW(List is marked as numbered if any list item has bullet text set)RAW")
    .def("__repr__", [](org::sem::List const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::List const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::HashTag /* d_org */, org::sem::Inline>(m, "HashTag")
    .def("__init__",
         [](org::sem::HashTag* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::HashTag /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::HashTag /* d_org */::text)
    .def("__repr__", [](org::sem::HashTag const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::HashTag const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::InlineFootnote /* d_org */, org::sem::Inline>(m, "InlineFootnote")
    .def("__init__",
         [](org::sem::InlineFootnote* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::InlineFootnote /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("tag", &org::sem::InlineFootnote /* d_org */::tag, R"RAW(Footnote text target name)RAW")
    .def_rw("definition", &org::sem::InlineFootnote /* d_org */::definition, R"RAW(Link to possibly resolved definition)RAW")
    .def("__repr__", [](org::sem::InlineFootnote const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::InlineFootnote const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::InlineExport /* d_org */, org::sem::Inline>(m, "InlineExport")
    .def("__init__",
         [](org::sem::InlineExport* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::InlineExport /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("exporter", &org::sem::InlineExport /* d_org */::exporter)
    .def_rw("content", &org::sem::InlineExport /* d_org */::content)
    .def("__repr__", [](org::sem::InlineExport const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::InlineExport const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Escaped /* d_org */, org::sem::Leaf>(m, "Escaped")
    .def("__init__",
         [](org::sem::Escaped* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Escaped /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Escaped const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Escaped const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Newline /* d_org */, org::sem::Leaf>(m, "Newline")
    .def("__init__",
         [](org::sem::Newline* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Newline /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Newline const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Newline const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Space /* d_org */, org::sem::Leaf>(m, "Space")
    .def("__init__",
         [](org::sem::Space* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Space /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Space const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Space const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Word /* d_org */, org::sem::Leaf>(m, "Word")
    .def("__init__",
         [](org::sem::Word* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Word /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Word const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Word const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::AtMention /* d_org */, org::sem::Leaf>(m, "AtMention")
    .def("__init__",
         [](org::sem::AtMention* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::AtMention /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::AtMention const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::AtMention const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::RawText /* d_org */, org::sem::Leaf>(m, "RawText")
    .def("__init__",
         [](org::sem::RawText* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::RawText /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::RawText const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::RawText const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Punctuation /* d_org */, org::sem::Leaf>(m, "Punctuation")
    .def("__init__",
         [](org::sem::Punctuation* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Punctuation /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Punctuation const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Punctuation const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Placeholder /* d_org */, org::sem::Leaf>(m, "Placeholder")
    .def("__init__",
         [](org::sem::Placeholder* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Placeholder /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Placeholder const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Placeholder const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BigIdent /* d_org */, org::sem::Leaf>(m, "BigIdent")
    .def("__init__",
         [](org::sem::BigIdent* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::BigIdent /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::BigIdent const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BigIdent const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::TextTarget /* d_org */, org::sem::Leaf>(m, "TextTarget")
    .def("__init__",
         [](org::sem::TextTarget* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::TextTarget /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::TextTarget const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::TextTarget const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::ErrorSkipToken /* d_org */, org::sem::Leaf>(m, "ErrorSkipToken")
    .def("__init__",
         [](org::sem::ErrorSkipToken* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::ErrorSkipToken /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::ErrorSkipToken const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::ErrorSkipToken const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Bold /* d_org */, org::sem::Markup>(m, "Bold")
    .def("__init__",
         [](org::sem::Bold* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Bold /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Bold const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Bold const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Underline /* d_org */, org::sem::Markup>(m, "Underline")
    .def("__init__",
         [](org::sem::Underline* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Underline /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Underline const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Underline const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Monospace /* d_org */, org::sem::Markup>(m, "Monospace")
    .def("__init__",
         [](org::sem::Monospace* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Monospace /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Monospace const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Monospace const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::MarkQuote /* d_org */, org::sem::Markup>(m, "MarkQuote")
    .def("__init__",
         [](org::sem::MarkQuote* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::MarkQuote /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::MarkQuote const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::MarkQuote const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Verbatim /* d_org */, org::sem::Markup>(m, "Verbatim")
    .def("__init__",
         [](org::sem::Verbatim* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Verbatim /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Verbatim const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Verbatim const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Italic /* d_org */, org::sem::Markup>(m, "Italic")
    .def("__init__",
         [](org::sem::Italic* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Italic /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Italic const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Italic const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Strike /* d_org */, org::sem::Markup>(m, "Strike")
    .def("__init__",
         [](org::sem::Strike* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Strike /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Strike const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Strike const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Par /* d_org */, org::sem::Markup>(m, "Par")
    .def("__init__",
         [](org::sem::Par* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Par /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::Par const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Par const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtAPI /*  [905]imm/ImmOrg.hpp:1345:17( [780] >record 'ImmAdapterStmtAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1345:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterStmtAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterSubtreeAPI /*  [905]imm/ImmOrg.hpp:1365:17( [780] >record 'ImmAdapterSubtreeAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1365:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterSubtreeAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterNoNodeAPI /*  [905]imm/ImmOrg.hpp:1384:17( [780] >record 'ImmAdapterNoNodeAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1384:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterNoNodeAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttrAPI /*  [905]imm/ImmOrg.hpp:1385:17( [780] >record 'ImmAdapterAttrAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1385:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterAttrAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttrListAPI /*  [905]imm/ImmOrg.hpp:1386:17( [780] >record 'ImmAdapterAttrListAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1386:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterAttrListAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttrsAPI /*  [905]imm/ImmOrg.hpp:1387:17( [780] >record 'ImmAdapterAttrsAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1387:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterAttrsAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterErrorItemAPI /*  [905]imm/ImmOrg.hpp:1388:17( [780] >record 'ImmAdapterErrorItemAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1388:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterErrorItemAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterErrorGroupAPI /*  [905]imm/ImmOrg.hpp:1389:17( [780] >record 'ImmAdapterErrorGroupAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1389:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterErrorGroupAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterErrorSkipGroupAPI /*  [905]imm/ImmOrg.hpp:1390:17( [780] >record 'ImmAdapterErrorSkipGroupAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1390:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterErrorSkipGroupAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterErrorSkipTokenAPI /*  [905]imm/ImmOrg.hpp:1391:17( [780] >record 'ImmAdapterErrorSkipTokenAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1391:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterErrorSkipTokenAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtListAPI /*  [905]imm/ImmOrg.hpp:1392:17( [780] >record 'ImmAdapterStmtListAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1392:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterStmtListAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterEmptyAPI /*  [905]imm/ImmOrg.hpp:1393:17( [780] >record 'ImmAdapterEmptyAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1393:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterEmptyAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterInlineAPI /*  [905]imm/ImmOrg.hpp:1411:17( [780] >record 'ImmAdapterInlineAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1411:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterInlineAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterTimeAPI /*  [905]imm/ImmOrg.hpp:1414:17( [780] >record 'ImmAdapterTimeAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1414:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterTimeAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterTimeRangeAPI /*  [905]imm/ImmOrg.hpp:1423:17( [780] >record 'ImmAdapterTimeRangeAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1423:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterTimeRangeAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMacroAPI /*  [905]imm/ImmOrg.hpp:1424:17( [780] >record 'ImmAdapterMacroAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1424:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterMacroAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterSymbolAPI /*  [905]imm/ImmOrg.hpp:1425:17( [780] >record 'ImmAdapterSymbolAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1425:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterSymbolAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1426:17( [780] >record 'ImmAdapterLeafAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1426:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterLeafAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1439:17( [780] >record 'ImmAdapterMarkupAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1439:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterMarkupAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLatexAPI /*  [905]imm/ImmOrg.hpp:1449:17( [780] >record 'ImmAdapterLatexAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1449:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterLatexAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterSubtreeLogAPI /*  [905]imm/ImmOrg.hpp:1466:17( [780] >record 'ImmAdapterSubtreeLogAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1466:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterSubtreeLogAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterColonExampleAPI /*  [905]imm/ImmOrg.hpp:1485:17( [780] >record 'ImmAdapterColonExampleAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1485:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterColonExampleAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCallAPI /*  [905]imm/ImmOrg.hpp:1487:17( [780] >record 'ImmAdapterCallAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1487:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterCallAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterFileAPI /*  [905]imm/ImmOrg.hpp:1488:17( [780] >record 'ImmAdapterFileAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1488:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterFileAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterDirectoryAPI /*  [905]imm/ImmOrg.hpp:1489:17( [780] >record 'ImmAdapterDirectoryAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1489:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterDirectoryAPI")
    .def("getFsSubnode",
         static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::optional<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapter /*  [640]Type parameter [905]imm/ImmOrg.hpp:1490:46( [780] >record 'ImmAdapter'<>) */> /*  [905]imm/ImmOrg.hpp:1490:46( [780] >record 'optional'< [657] templates: template-specialization-type>) */(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterDirectoryAPI /*  [905]imm/ImmOrg.hpp:1489:17( [780] >record 'ImmAdapterDirectoryAPI'<>) */::*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Str const& /*  [905]imm/ImmOrg.hpp:1491:26( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Str'<>)<>) */, bool /*  [905]imm/ImmOrg.hpp:1492:26( [755] >bool<>) */) const>(&org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterDirectoryAPI /*  [905]imm/ImmOrg.hpp:1489:17( [780] >record 'ImmAdapterDirectoryAPI'<>) */::getFsSubnode),
         nanobind::arg("name"),
         nanobind::arg("withPath") = true)
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterSymlinkAPI /*  [905]imm/ImmOrg.hpp:1494:17( [780] >record 'ImmAdapterSymlinkAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1494:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterSymlinkAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterDocumentFragmentAPI /*  [905]imm/ImmOrg.hpp:1495:17( [780] >record 'ImmAdapterDocumentFragmentAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1495:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterDocumentFragmentAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCriticMarkupAPI /*  [905]imm/ImmOrg.hpp:1496:17( [780] >record 'ImmAdapterCriticMarkupAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1496:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterCriticMarkupAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterListItemAPI /*  [905]imm/ImmOrg.hpp:1505:17( [780] >record 'ImmAdapterListItemAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1505:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterListItemAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterDocumentOptionsAPI /*  [905]imm/ImmOrg.hpp:1513:17( [780] >record 'ImmAdapterDocumentOptionsAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1513:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterDocumentOptionsAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterDocumentAPI /*  [905]imm/ImmOrg.hpp:1525:17( [780] >record 'ImmAdapterDocumentAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1525:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterDocumentAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterFileTargetAPI /*  [905]imm/ImmOrg.hpp:1534:17( [780] >record 'ImmAdapterFileTargetAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1534:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterFileTargetAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterTextSeparatorAPI /*  [905]imm/ImmOrg.hpp:1535:17( [780] >record 'ImmAdapterTextSeparatorAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1535:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterTextSeparatorAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdIncludeAPI /*  [905]imm/ImmOrg.hpp:1536:17( [780] >record 'ImmAdapterCmdIncludeAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1536:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterCmdIncludeAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterDocumentGroupAPI /*  [905]imm/ImmOrg.hpp:1537:17( [780] >record 'ImmAdapterDocumentGroupAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterOrgAPI /*  [905]imm/ImmOrg.hpp:1537:17( [780] >record 'ImmAdapterOrgAPI'<>) */>(m, "ImmAdapterDocumentGroupAPI")
    ;
  nanobind::class_<org::sem::Block /* d_org */, org::sem::Cmd>(m, "Block")
    ;
  nanobind::class_<org::sem::LineCommand /* d_org */, org::sem::Cmd>(m, "LineCommand")
    ;
  nanobind::class_<org::sem::CmdCreator /* d_org */, org::sem::Cmd>(m, "CmdCreator")
    .def("__init__",
         [](org::sem::CmdCreator* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdCreator /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::CmdCreator /* d_org */::text, R"RAW(Creator name text)RAW")
    .def("__repr__", [](org::sem::CmdCreator const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCreator const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdAuthor /* d_org */, org::sem::Cmd>(m, "CmdAuthor")
    .def("__init__",
         [](org::sem::CmdAuthor* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdAuthor /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::CmdAuthor /* d_org */::text, R"RAW(Author name text)RAW")
    .def("__repr__", [](org::sem::CmdAuthor const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdAuthor const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdEmail /* d_org */, org::sem::Cmd>(m, "CmdEmail")
    .def("__init__",
         [](org::sem::CmdEmail* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdEmail /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::CmdEmail /* d_org */::text)
    .def("__repr__", [](org::sem::CmdEmail const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdEmail const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdLanguage /* d_org */, org::sem::Cmd>(m, "CmdLanguage")
    .def("__init__",
         [](org::sem::CmdLanguage* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdLanguage /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::CmdLanguage /* d_org */::text)
    .def("__repr__", [](org::sem::CmdLanguage const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdLanguage const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdCustomArgs /* d_org */, org::sem::Cmd>(m, "CmdCustomArgs")
    .def("__init__",
         [](org::sem::CmdCustomArgs* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdCustomArgs /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::CmdCustomArgs /* d_org */::name)
    .def_rw("isAttached", &org::sem::CmdCustomArgs /* d_org */::isAttached)
    .def("__repr__", [](org::sem::CmdCustomArgs const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCustomArgs const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdTblfm /* d_org */, org::sem::Cmd>(m, "CmdTblfm")
    .def("__init__",
         [](org::sem::CmdTblfm* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdTblfm /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("expr", &org::sem::CmdTblfm /* d_org */::expr)
    .def("__repr__", [](org::sem::CmdTblfm const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdTblfm const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Cell /* d_org */, org::sem::Cmd>(m, "Cell")
    .def("__init__",
         [](org::sem::Cell* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Cell /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("isBlock", &org::sem::Cell /* d_org */::isBlock, R"RAW(Single-line pipe cell or `#+cell:` command)RAW")
    .def("__repr__", [](org::sem::Cell const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Cell const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Row /* d_org */, org::sem::Cmd>(m, "Row")
    .def("__init__",
         [](org::sem::Row* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Row /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("cells", &org::sem::Row /* d_org */::cells, R"RAW(List of cells on the row)RAW")
    .def_rw("isBlock", &org::sem::Row /* d_org */::isBlock, R"RAW(Single-line pipe cell or `#+cell:` command)RAW")
    .def("__repr__", [](org::sem::Row const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Row const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1357:17( [780] >record 'ImmAdapterCmdAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtAPI /*  [905]imm/ImmOrg.hpp:1357:17( [780] >record 'ImmAdapterStmtAPI'<>) */>(m, "ImmAdapterCmdAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdCustomRawAPI /*  [905]imm/ImmOrg.hpp:1407:17( [780] >record 'ImmAdapterCmdCustomRawAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtAPI /*  [905]imm/ImmOrg.hpp:1407:17( [780] >record 'ImmAdapterStmtAPI'<>) */>(m, "ImmAdapterCmdCustomRawAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdCustomTextAPI /*  [905]imm/ImmOrg.hpp:1408:17( [780] >record 'ImmAdapterCmdCustomTextAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtAPI /*  [905]imm/ImmOrg.hpp:1408:17( [780] >record 'ImmAdapterStmtAPI'<>) */>(m, "ImmAdapterCmdCustomTextAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLinkAPI /*  [905]imm/ImmOrg.hpp:1450:17( [780] >record 'ImmAdapterLinkAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtAPI /*  [905]imm/ImmOrg.hpp:1450:17( [780] >record 'ImmAdapterStmtAPI'<>) */>(m, "ImmAdapterLinkAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockCommentAPI /*  [905]imm/ImmOrg.hpp:1454:17( [780] >record 'ImmAdapterBlockCommentAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtAPI /*  [905]imm/ImmOrg.hpp:1454:17( [780] >record 'ImmAdapterStmtAPI'<>) */>(m, "ImmAdapterBlockCommentAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterParagraphAPI /*  [905]imm/ImmOrg.hpp:1471:17( [780] >record 'ImmAdapterParagraphAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtAPI /*  [905]imm/ImmOrg.hpp:1471:17( [780] >record 'ImmAdapterStmtAPI'<>) */>(m, "ImmAdapterParagraphAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterListAPI /*  [905]imm/ImmOrg.hpp:1498:17( [780] >record 'ImmAdapterListAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStmtAPI /*  [905]imm/ImmOrg.hpp:1498:17( [780] >record 'ImmAdapterStmtAPI'<>) */>(m, "ImmAdapterListAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmStmt>, org::imm::ImmAdapterStmtAPI>(m, "ImmStmtAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getAttached", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmStmt>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmStmt>::getAttached))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmSubtree>, org::imm::ImmAdapterSubtreeAPI>(m, "ImmSubtreeAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getLevel", static_cast<int /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getLevel))
    .def("getTreeId", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTreeId))
    .def("getTodo", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTodo))
    .def("getCompletion", static_cast<hstd::Opt<org::sem::SubtreeCompletion> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getCompletion))
    .def("getDescription", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getDescription))
    .def("getTags", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTags))
    .def("getTitle", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getTitle))
    .def("getLogbook", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getLogbook))
    .def("getProperties", static_cast<hstd::ext::ImmVec<org::sem::NamedProperty> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getProperties))
    .def("getClosed", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getClosed))
    .def("getDeadline", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getDeadline))
    .def("getScheduled", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getScheduled))
    .def("getIsComment", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getIsComment))
    .def("getIsArchived", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getIsArchived))
    .def("getPriority", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmSubtree>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtree>::getPriority))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmNoNode>, org::imm::ImmAdapterNoNodeAPI>(m, "ImmNoNodeAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmErrorItem>, org::imm::ImmAdapterErrorItemAPI>(m, "ImmErrorItemAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getDiag", static_cast<org::sem::OrgDiagnostics(org::imm::ImmAdapterT<org::imm::ImmErrorItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorItem>::getDiag))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmErrorGroup>, org::imm::ImmAdapterErrorGroupAPI>(m, "ImmErrorGroupAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getDiagnostics", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorGroup>::getDiagnostics))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>, org::imm::ImmAdapterErrorSkipGroupAPI>(m, "ImmErrorSkipGroupAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getSkipped", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorSkipToken /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup>::getSkipped))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken>, org::imm::ImmAdapterErrorSkipTokenAPI>(m, "ImmErrorSkipTokenAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmStmtList>, org::imm::ImmAdapterStmtListAPI>(m, "ImmStmtListAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmEmpty>, org::imm::ImmAdapterEmptyAPI>(m, "ImmEmptyAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterHashTagAPI /*  [905]imm/ImmOrg.hpp:1412:17( [780] >record 'ImmAdapterHashTagAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterInlineAPI /*  [905]imm/ImmOrg.hpp:1412:17( [780] >record 'ImmAdapterInlineAPI'<>) */>(m, "ImmAdapterHashTagAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterInlineFootnoteAPI /*  [905]imm/ImmOrg.hpp:1413:17( [780] >record 'ImmAdapterInlineFootnoteAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterInlineAPI /*  [905]imm/ImmOrg.hpp:1413:17( [780] >record 'ImmAdapterInlineAPI'<>) */>(m, "ImmAdapterInlineFootnoteAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterSubtreeCompletionAPI /*  [905]imm/ImmOrg.hpp:1467:17( [780] >record 'ImmAdapterSubtreeCompletionAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterInlineAPI /*  [905]imm/ImmOrg.hpp:1467:17( [780] >record 'ImmAdapterInlineAPI'<>) */>(m, "ImmAdapterSubtreeCompletionAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmInline>, org::imm::ImmAdapterInlineAPI>(m, "ImmInlineAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmTime>, org::imm::ImmAdapterTimeAPI>(m, "ImmTimeAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getIsActive", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmTime>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTime>::getIsActive))
    .def("getTime", static_cast<org::imm::ImmTime::TimeVariant /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmTime>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTime>::getTime))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmTimeRange>, org::imm::ImmAdapterTimeRangeAPI>(m, "ImmTimeRangeAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getFrom", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmTimeRange>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTimeRange>::getFrom))
    .def("getTo", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmTimeRange>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTimeRange>::getTo))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmMacro>, org::imm::ImmAdapterMacroAPI>(m, "ImmMacroAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmMacro>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMacro>::getName))
    .def("getAttrs", static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmMacro>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmMacro>::getAttrs))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmSymbol>, org::imm::ImmAdapterSymbolAPI>(m, "ImmSymbolAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getName))
    .def("getParameters", static_cast<hstd::ext::ImmVec<org::imm::ImmSymbol::Param /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getParameters))
    .def("getPositional", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSymbol>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymbol>::getPositional))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterEscapedAPI /*  [905]imm/ImmOrg.hpp:1429:17( [780] >record 'ImmAdapterEscapedAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1429:17( [780] >record 'ImmAdapterLeafAPI'<>) */>(m, "ImmAdapterEscapedAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterNewlineAPI /*  [905]imm/ImmOrg.hpp:1430:17( [780] >record 'ImmAdapterNewlineAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1430:17( [780] >record 'ImmAdapterLeafAPI'<>) */>(m, "ImmAdapterNewlineAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterSpaceAPI /*  [905]imm/ImmOrg.hpp:1431:17( [780] >record 'ImmAdapterSpaceAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1431:17( [780] >record 'ImmAdapterLeafAPI'<>) */>(m, "ImmAdapterSpaceAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterWordAPI /*  [905]imm/ImmOrg.hpp:1432:17( [780] >record 'ImmAdapterWordAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1432:17( [780] >record 'ImmAdapterLeafAPI'<>) */>(m, "ImmAdapterWordAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAtMentionAPI /*  [905]imm/ImmOrg.hpp:1433:17( [780] >record 'ImmAdapterAtMentionAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1433:17( [780] >record 'ImmAdapterLeafAPI'<>) */>(m, "ImmAdapterAtMentionAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterRawTextAPI /*  [905]imm/ImmOrg.hpp:1434:17( [780] >record 'ImmAdapterRawTextAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1434:17( [780] >record 'ImmAdapterLeafAPI'<>) */>(m, "ImmAdapterRawTextAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterPunctuationAPI /*  [905]imm/ImmOrg.hpp:1435:17( [780] >record 'ImmAdapterPunctuationAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1435:17( [780] >record 'ImmAdapterLeafAPI'<>) */>(m, "ImmAdapterPunctuationAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterPlaceholderAPI /*  [905]imm/ImmOrg.hpp:1436:17( [780] >record 'ImmAdapterPlaceholderAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1436:17( [780] >record 'ImmAdapterLeafAPI'<>) */>(m, "ImmAdapterPlaceholderAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBigIdentAPI /*  [905]imm/ImmOrg.hpp:1437:17( [780] >record 'ImmAdapterBigIdentAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1437:17( [780] >record 'ImmAdapterLeafAPI'<>) */>(m, "ImmAdapterBigIdentAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterTextTargetAPI /*  [905]imm/ImmOrg.hpp:1438:17( [780] >record 'ImmAdapterTextTargetAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLeafAPI /*  [905]imm/ImmOrg.hpp:1438:17( [780] >record 'ImmAdapterLeafAPI'<>) */>(m, "ImmAdapterTextTargetAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmLeaf>, org::imm::ImmAdapterLeafAPI>(m, "ImmLeafAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getText", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmLeaf>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLeaf>::getText))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBoldAPI /*  [905]imm/ImmOrg.hpp:1440:17( [780] >record 'ImmAdapterBoldAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1440:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>(m, "ImmAdapterBoldAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterUnderlineAPI /*  [905]imm/ImmOrg.hpp:1441:17( [780] >record 'ImmAdapterUnderlineAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1441:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>(m, "ImmAdapterUnderlineAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMonospaceAPI /*  [905]imm/ImmOrg.hpp:1442:17( [780] >record 'ImmAdapterMonospaceAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1442:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>(m, "ImmAdapterMonospaceAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkQuoteAPI /*  [905]imm/ImmOrg.hpp:1443:17( [780] >record 'ImmAdapterMarkQuoteAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1443:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>(m, "ImmAdapterMarkQuoteAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterRadioTargetAPI /*  [905]imm/ImmOrg.hpp:1444:17( [780] >record 'ImmAdapterRadioTargetAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1444:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>(m, "ImmAdapterRadioTargetAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterVerbatimAPI /*  [905]imm/ImmOrg.hpp:1445:17( [780] >record 'ImmAdapterVerbatimAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1445:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>(m, "ImmAdapterVerbatimAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterItalicAPI /*  [905]imm/ImmOrg.hpp:1446:17( [780] >record 'ImmAdapterItalicAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1446:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>(m, "ImmAdapterItalicAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterStrikeAPI /*  [905]imm/ImmOrg.hpp:1447:17( [780] >record 'ImmAdapterStrikeAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1447:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>(m, "ImmAdapterStrikeAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterParAPI /*  [905]imm/ImmOrg.hpp:1448:17( [780] >record 'ImmAdapterParAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterMarkupAPI /*  [905]imm/ImmOrg.hpp:1448:17( [780] >record 'ImmAdapterMarkupAPI'<>) */>(m, "ImmAdapterParAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmMarkup>, org::imm::ImmAdapterMarkupAPI>(m, "ImmMarkupAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmLatex>, org::imm::ImmAdapterLatexAPI>(m, "ImmLatexAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>, org::imm::ImmAdapterSubtreeLogAPI>(m, "ImmSubtreeLogAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getHead", static_cast<org::sem::SubtreeLogHead(org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::getHead))
    .def("getDesc", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmStmtList /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSubtreeLog>::getDesc))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmColonExample>, org::imm::ImmAdapterColonExampleAPI>(m, "ImmColonExampleAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCall>, org::imm::ImmAdapterCallAPI>(m, "ImmCallAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getName))
    .def("getAttrs", static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getAttrs))
    .def("getIsCommand", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCall>::getIsCommand))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmFile>, org::imm::ImmAdapterFileAPI>(m, "ImmFileAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getRelPath", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmFile>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFile>::getRelPath))
    .def("getAbsPath", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmFile>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFile>::getAbsPath))
    .def("getData", static_cast<org::imm::ImmFile::Data /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmFile>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFile>::getData))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmDirectory>, org::imm::ImmAdapterDirectoryAPI>(m, "ImmDirectoryAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getRelPath", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmDirectory>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDirectory>::getRelPath))
    .def("getAbsPath", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmDirectory>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDirectory>::getAbsPath))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmSymlink>, org::imm::ImmAdapterSymlinkAPI>(m, "ImmSymlinkAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getIsDirectory", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmSymlink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymlink>::getIsDirectory))
    .def("getAbsPath", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmSymlink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmSymlink>::getAbsPath))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>, org::imm::ImmAdapterDocumentFragmentAPI>(m, "ImmDocumentFragmentAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getBaseLine", static_cast<int /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::getBaseLine))
    .def("getBaseCol", static_cast<int /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentFragment>::getBaseCol))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>, org::imm::ImmAdapterCriticMarkupAPI>(m, "ImmCriticMarkupAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getKind", static_cast<org::imm::ImmCriticMarkup::Kind /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCriticMarkup>::getKind))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmListItem>, org::imm::ImmAdapterListItemAPI>(m, "ImmListItemAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getCheckbox", static_cast<CheckboxState /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getCheckbox))
    .def("getHeader", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getHeader))
    .def("getBullet", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmListItem>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmListItem>::getBullet))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>, org::imm::ImmAdapterDocumentOptionsAPI>(m, "ImmDocumentOptionsAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getInitialVisibility", static_cast<InitialSubtreeVisibility /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getInitialVisibility))
    .def("getProperties", static_cast<hstd::ext::ImmVec<org::sem::NamedProperty> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getProperties))
    .def("getExportConfig", static_cast<org::sem::DocumentExportConfig(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getExportConfig))
    .def("getFixedWidthSections", static_cast<hstd::Opt<bool /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getFixedWidthSections))
    .def("getStartupIndented", static_cast<hstd::Opt<bool /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getStartupIndented))
    .def("getCategory", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getCategory))
    .def("getSetupfile", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getSetupfile))
    .def("getMaxSubtreeLevelExport", static_cast<hstd::Opt<int /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getMaxSubtreeLevelExport))
    .def("getColumns", static_cast<hstd::Opt<org::sem::ColumnView> const&(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getColumns))
    .def("getTodoKeywords", static_cast<hstd::ext::ImmVec<org::sem::TodoKeyword> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getTodoKeywords))
    .def("getDoneKeywords", static_cast<hstd::ext::ImmVec<org::sem::TodoKeyword> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocumentOptions>::getDoneKeywords))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmDocument>, org::imm::ImmAdapterDocumentAPI>(m, "ImmDocumentAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getTitle", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getTitle))
    .def("getAuthor", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getAuthor))
    .def("getCreator", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getCreator))
    .def("getFiletags", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getFiletags))
    .def("getEmail", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmRawText /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getEmail))
    .def("getLanguage", static_cast<hstd::ext::ImmVec<hstd /* imm_write */::Str /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getLanguage))
    .def("getOptions", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getOptions))
    .def("getExportFileName", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmDocument>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmDocument>::getExportFileName))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmFileTarget>, org::imm::ImmAdapterFileTargetAPI>(m, "ImmFileTargetAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getPath", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getPath))
    .def("getLine", static_cast<hstd::Opt<int /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getLine))
    .def("getSearchTarget", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getSearchTarget))
    .def("getRestrictToHeadlines", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getRestrictToHeadlines))
    .def("getTargetId", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getTargetId))
    .def("getRegexp", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmFileTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmFileTarget>::getRegexp))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmTextSeparator>, org::imm::ImmAdapterTextSeparatorAPI>(m, "ImmTextSeparatorAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdInclude>, org::imm::ImmAdapterCmdIncludeAPI>(m, "ImmCmdIncludeAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getPath", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getPath))
    .def("getFirstLine", static_cast<hstd::Opt<int /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getFirstLine))
    .def("getLastLine", static_cast<hstd::Opt<int /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getLastLine))
    .def("getData", static_cast<org::imm::ImmCmdInclude::Data /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdInclude>::getData))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmDocumentGroup>, org::imm::ImmAdapterDocumentGroupAPI>(m, "ImmDocumentGroupAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::sem::BlockCenter /* d_org */, org::sem::Block>(m, "BlockCenter")
    .def("__init__",
         [](org::sem::BlockCenter* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::BlockCenter /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::BlockCenter const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCenter const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockQuote /* d_org */, org::sem::Block>(m, "BlockQuote")
    .def("__init__",
         [](org::sem::BlockQuote* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::BlockQuote /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::BlockQuote const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockQuote const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockVerse /* d_org */, org::sem::Block>(m, "BlockVerse")
    .def("__init__",
         [](org::sem::BlockVerse* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::BlockVerse /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::BlockVerse const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockVerse const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockDynamicFallback /* d_org */, org::sem::Block>(m, "BlockDynamicFallback")
    .def("__init__",
         [](org::sem::BlockDynamicFallback* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::BlockDynamicFallback /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::BlockDynamicFallback /* d_org */::name)
    .def("__repr__", [](org::sem::BlockDynamicFallback const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockDynamicFallback const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockExample /* d_org */, org::sem::Block>(m, "BlockExample")
    .def("__init__",
         [](org::sem::BlockExample* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::BlockExample /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::BlockExample const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockExample const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockExport /* d_org */, org::sem::Block>(m, "BlockExport")
    .def("__init__",
         [](org::sem::BlockExport* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::BlockExport /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("exporter", &org::sem::BlockExport /* d_org */::exporter)
    .def_rw("content", &org::sem::BlockExport /* d_org */::content)
    .def("getPlacement", static_cast<hstd::Opt<hstd::Str>(org::sem::BlockExport /* d_org */::*)() const>(&org::sem::BlockExport /* d_org */::getPlacement), R"RAW(Return value of the :placement attribute if present)RAW")
    .def("__repr__", [](org::sem::BlockExport const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockExport const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockAdmonition /* d_org */, org::sem::Block>(m, "BlockAdmonition")
    .def("__init__",
         [](org::sem::BlockAdmonition* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::BlockAdmonition /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def("__repr__", [](org::sem::BlockAdmonition const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockAdmonition const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockCodeEvalResult /* d_org */, org::sem::Block>(m, "BlockCodeEvalResult")
    .def("__init__",
         [](org::sem::BlockCodeEvalResult* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::BlockCodeEvalResult /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("raw", &org::sem::BlockCodeEvalResult /* d_org */::raw)
    .def_rw("node", &org::sem::BlockCodeEvalResult /* d_org */::node)
    .def("__repr__", [](org::sem::BlockCodeEvalResult const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCodeEvalResult const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::BlockCode /* d_org */, org::sem::Block>(m, "BlockCode")
    .def("__init__",
         [](org::sem::BlockCode* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::BlockCode /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("lang", &org::sem::BlockCode /* d_org */::lang, R"RAW(Code block language name)RAW")
    .def_rw("result", &org::sem::BlockCode /* d_org */::result, R"RAW(Code evaluation results)RAW")
    .def_rw("lines", &org::sem::BlockCode /* d_org */::lines, R"RAW(Collected code lines)RAW")
    .def_rw("switches", &org::sem::BlockCode /* d_org */::switches, R"RAW(Dash-based switches for code block execution)RAW")
    .def("getVariable",
         static_cast<hstd::Opt<org::sem::AttrValue>(org::sem::BlockCode /* d_org */::*)(hstd::Str const&) const>(&org::sem::BlockCode /* d_org */::getVariable),
         nanobind::arg("varname"))
    .def("__repr__", [](org::sem::BlockCode const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::BlockCode const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Table /* d_org */, org::sem::Block>(m, "Table")
    .def("__init__",
         [](org::sem::Table* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::Table /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("rows", &org::sem::Table /* d_org */::rows, R"RAW(List of rows for the table)RAW")
    .def_rw("isBlock", &org::sem::Table /* d_org */::isBlock, R"RAW(Single-line pipe cell or `#+cell:` command)RAW")
    .def("__repr__", [](org::sem::Table const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::Table const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::Attached /* d_org */, org::sem::LineCommand>(m, "Attached")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLineCommandAPI /*  [905]imm/ImmOrg.hpp:1394:17( [780] >record 'ImmAdapterLineCommandAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1394:17( [780] >record 'ImmAdapterCmdAPI'<>) */>(m, "ImmAdapterLineCommandAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdCustomArgsAPI /*  [905]imm/ImmOrg.hpp:1402:17( [780] >record 'ImmAdapterCmdCustomArgsAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1402:17( [780] >record 'ImmAdapterCmdAPI'<>) */>(m, "ImmAdapterCmdCustomArgsAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdCreatorAPI /*  [905]imm/ImmOrg.hpp:1403:17( [780] >record 'ImmAdapterCmdCreatorAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1403:17( [780] >record 'ImmAdapterCmdAPI'<>) */>(m, "ImmAdapterCmdCreatorAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAuthorAPI /*  [905]imm/ImmOrg.hpp:1404:17( [780] >record 'ImmAdapterCmdAuthorAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1404:17( [780] >record 'ImmAdapterCmdAPI'<>) */>(m, "ImmAdapterCmdAuthorAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdEmailAPI /*  [905]imm/ImmOrg.hpp:1405:17( [780] >record 'ImmAdapterCmdEmailAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1405:17( [780] >record 'ImmAdapterCmdAPI'<>) */>(m, "ImmAdapterCmdEmailAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdLanguageAPI /*  [905]imm/ImmOrg.hpp:1406:17( [780] >record 'ImmAdapterCmdLanguageAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1406:17( [780] >record 'ImmAdapterCmdAPI'<>) */>(m, "ImmAdapterCmdLanguageAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdTblfmAPI /*  [905]imm/ImmOrg.hpp:1410:17( [780] >record 'ImmAdapterCmdTblfmAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1410:17( [780] >record 'ImmAdapterCmdAPI'<>) */>(m, "ImmAdapterCmdTblfmAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1451:17( [780] >record 'ImmAdapterBlockAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1451:17( [780] >record 'ImmAdapterCmdAPI'<>) */>(m, "ImmAdapterBlockAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCellAPI /*  [905]imm/ImmOrg.hpp:1468:17( [780] >record 'ImmAdapterCellAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1468:17( [780] >record 'ImmAdapterCmdAPI'<>) */>(m, "ImmAdapterCellAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterRowAPI /*  [905]imm/ImmOrg.hpp:1469:17( [780] >record 'ImmAdapterRowAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAPI /*  [905]imm/ImmOrg.hpp:1469:17( [780] >record 'ImmAdapterCmdAPI'<>) */>(m, "ImmAdapterRowAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmd>, org::imm::ImmAdapterCmdAPI>(m, "ImmCmdAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getAttrs", static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmd>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmd>::getAttrs))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>, org::imm::ImmAdapterCmdCustomRawAPI>(m, "ImmCmdCustomRawAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getName))
    .def("getIsAttached", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getIsAttached))
    .def("getText", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw>::getText))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>, org::imm::ImmAdapterCmdCustomTextAPI>(m, "ImmCmdCustomTextAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getName))
    .def("getIsAttached", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getIsAttached))
    .def("getText", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomText>::getText))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmLink>, org::imm::ImmAdapterLinkAPI>(m, "ImmLinkAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getDescription", static_cast<hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph /* imm_write */>>(org::imm::ImmAdapterT<org::imm::ImmLink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLink>::getDescription))
    .def("getTarget", static_cast<org::sem::LinkTarget(org::imm::ImmAdapterT<org::imm::ImmLink>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmLink>::getTarget))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockComment>, org::imm::ImmAdapterBlockCommentAPI>(m, "ImmBlockCommentAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmParagraph>, org::imm::ImmAdapterParagraphAPI>(m, "ImmParagraphAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmList>, org::imm::ImmAdapterListAPI>(m, "ImmListAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmHashTag>, org::imm::ImmAdapterHashTagAPI>(m, "ImmHashTagAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getText", static_cast<org::sem::HashTagText(org::imm::ImmAdapterT<org::imm::ImmHashTag>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmHashTag>::getText))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>, org::imm::ImmAdapterInlineFootnoteAPI>(m, "ImmInlineFootnoteAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getTag", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::getTag))
    .def("getDefinition", static_cast<hstd::Opt<org::imm::ImmAdapter>(org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineFootnote>::getDefinition))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmEscaped>, org::imm::ImmAdapterEscapedAPI>(m, "ImmEscapedAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmNewline>, org::imm::ImmAdapterNewlineAPI>(m, "ImmNewlineAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmSpace>, org::imm::ImmAdapterSpaceAPI>(m, "ImmSpaceAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmWord>, org::imm::ImmAdapterWordAPI>(m, "ImmWordAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmAtMention>, org::imm::ImmAdapterAtMentionAPI>(m, "ImmAtMentionAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmRawText>, org::imm::ImmAdapterRawTextAPI>(m, "ImmRawTextAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmPunctuation>, org::imm::ImmAdapterPunctuationAPI>(m, "ImmPunctuationAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmPlaceholder>, org::imm::ImmAdapterPlaceholderAPI>(m, "ImmPlaceholderAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBigIdent>, org::imm::ImmAdapterBigIdentAPI>(m, "ImmBigIdentAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmTextTarget>, org::imm::ImmAdapterTextTargetAPI>(m, "ImmTextTargetAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBold>, org::imm::ImmAdapterBoldAPI>(m, "ImmBoldAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmUnderline>, org::imm::ImmAdapterUnderlineAPI>(m, "ImmUnderlineAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmMonospace>, org::imm::ImmAdapterMonospaceAPI>(m, "ImmMonospaceAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmMarkQuote>, org::imm::ImmAdapterMarkQuoteAPI>(m, "ImmMarkQuoteAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmRadioTarget>, org::imm::ImmAdapterRadioTargetAPI>(m, "ImmRadioTargetAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getWords", static_cast<hstd::ext::ImmVec<hstd /* imm_write */::Str /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRadioTarget>::getWords))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmVerbatim>, org::imm::ImmAdapterVerbatimAPI>(m, "ImmVerbatimAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmItalic>, org::imm::ImmAdapterItalicAPI>(m, "ImmItalicAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmStrike>, org::imm::ImmAdapterStrikeAPI>(m, "ImmStrikeAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmPar>, org::imm::ImmAdapterParAPI>(m, "ImmParAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::sem::CmdCaption /* d_org */, org::sem::Attached>(m, "CmdCaption")
    .def("__init__",
         [](org::sem::CmdCaption* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdCaption /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("text", &org::sem::CmdCaption /* d_org */::text, R"RAW(Content description)RAW")
    .def("__repr__", [](org::sem::CmdCaption const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCaption const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdColumns /* d_org */, org::sem::Attached>(m, "CmdColumns")
    .def("__init__",
         [](org::sem::CmdColumns* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdColumns /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("view", &org::sem::CmdColumns /* d_org */::view)
    .def("__repr__", [](org::sem::CmdColumns const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdColumns const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdName /* d_org */, org::sem::Attached>(m, "CmdName")
    .def("__init__",
         [](org::sem::CmdName* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdName /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::CmdName /* d_org */::name)
    .def("__repr__", [](org::sem::CmdName const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdName const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdCall /* d_org */, org::sem::Attached>(m, "CmdCall")
    .def("__init__",
         [](org::sem::CmdCall* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdCall /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("name", &org::sem::CmdCall /* d_org */::name, R"RAW(Code block call name)RAW")
    .def_rw("fileName", &org::sem::CmdCall /* d_org */::fileName, R"RAW(Which file code block should come from)RAW")
    .def_rw("insideHeaderAttrs", &org::sem::CmdCall /* d_org */::insideHeaderAttrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_rw("callAttrs", &org::sem::CmdCall /* d_org */::callAttrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_rw("endHeaderAttrs", &org::sem::CmdCall /* d_org */::endHeaderAttrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_rw("result", &org::sem::CmdCall /* d_org */::result, R"RAW(Code evaluation results)RAW")
    .def("__repr__", [](org::sem::CmdCall const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdCall const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdAttr /* d_org */, org::sem::Attached>(m, "CmdAttr")
    .def("__init__",
         [](org::sem::CmdAttr* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdAttr /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("target", &org::sem::CmdAttr /* d_org */::target)
    .def("__repr__", [](org::sem::CmdAttr const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdAttr const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org::sem::CmdExport /* d_org */, org::sem::Attached>(m, "CmdExport")
    .def("__init__",
         [](org::sem::CmdExport* /* d_org */ result, nanobind::kwargs const& kwargs) -> void {
         new(result) org::sem::CmdExport /* d_org */();
         org::bind::python::init_fields_from_kwargs(*result, kwargs);
         },
         nanobind::arg("result"))
    .def_rw("exporter", &org::sem::CmdExport /* d_org */::exporter)
    .def_rw("content", &org::sem::CmdExport /* d_org */::content)
    .def("__repr__", [](org::sem::CmdExport const& /* d_org */ _self) -> std::string {
                     return org::bind::python::py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](org::sem::CmdExport const& /* d_org */ _self, std::string const& name) -> nanobind::object {
         return org::bind::python::py_getattr_impl(_self, name);
         },
         nanobind::arg("name"))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttachedAPI /*  [905]imm/ImmOrg.hpp:1395:17( [780] >record 'ImmAdapterAttachedAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterLineCommandAPI /*  [905]imm/ImmOrg.hpp:1395:17( [780] >record 'ImmAdapterLineCommandAPI'<>) */>(m, "ImmAdapterAttachedAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmLineCommand>, org::imm::ImmAdapterLineCommandAPI>(m, "ImmLineCommandAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>, org::imm::ImmAdapterCmdCustomArgsAPI>(m, "ImmCmdCustomArgsAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::getName))
    .def("getIsAttached", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs>::getIsAttached))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCreator>, org::imm::ImmAdapterCmdCreatorAPI>(m, "ImmCmdCreatorAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getText", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdCreator>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCreator>::getText))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>, org::imm::ImmAdapterCmdAuthorAPI>(m, "ImmCmdAuthorAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getText", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdAuthor>::getText))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdEmail>, org::imm::ImmAdapterCmdEmailAPI>(m, "ImmCmdEmailAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getText", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdEmail>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdEmail>::getText))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>, org::imm::ImmAdapterCmdLanguageAPI>(m, "ImmCmdLanguageAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getText", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdLanguage>::getText))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>, org::imm::ImmAdapterCmdTblfmAPI>(m, "ImmCmdTblfmAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getExpr", static_cast<org::sem::Tblfm(org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdTblfm>::getExpr))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockCenterAPI /*  [905]imm/ImmOrg.hpp:1452:17( [780] >record 'ImmAdapterBlockCenterAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1452:17( [780] >record 'ImmAdapterBlockAPI'<>) */>(m, "ImmAdapterBlockCenterAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockQuoteAPI /*  [905]imm/ImmOrg.hpp:1453:17( [780] >record 'ImmAdapterBlockQuoteAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1453:17( [780] >record 'ImmAdapterBlockAPI'<>) */>(m, "ImmAdapterBlockQuoteAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockVerseAPI /*  [905]imm/ImmOrg.hpp:1455:17( [780] >record 'ImmAdapterBlockVerseAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1455:17( [780] >record 'ImmAdapterBlockAPI'<>) */>(m, "ImmAdapterBlockVerseAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockExampleAPI /*  [905]imm/ImmOrg.hpp:1456:17( [780] >record 'ImmAdapterBlockExampleAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1456:17( [780] >record 'ImmAdapterBlockAPI'<>) */>(m, "ImmAdapterBlockExampleAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterInlineExportAPI /*  [905]imm/ImmOrg.hpp:1457:17( [780] >record 'ImmAdapterInlineExportAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1457:17( [780] >record 'ImmAdapterBlockAPI'<>) */>(m, "ImmAdapterInlineExportAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdExportAPI /*  [905]imm/ImmOrg.hpp:1458:17( [780] >record 'ImmAdapterCmdExportAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1458:17( [780] >record 'ImmAdapterBlockAPI'<>) */>(m, "ImmAdapterCmdExportAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockExportAPI /*  [905]imm/ImmOrg.hpp:1459:17( [780] >record 'ImmAdapterBlockExportAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1459:17( [780] >record 'ImmAdapterBlockAPI'<>) */>(m, "ImmAdapterBlockExportAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockDynamicFallbackAPI /*  [905]imm/ImmOrg.hpp:1462:17( [780] >record 'ImmAdapterBlockDynamicFallbackAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1462:17( [780] >record 'ImmAdapterBlockAPI'<>) */>(m, "ImmAdapterBlockDynamicFallbackAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAdmonitionAPI /*  [905]imm/ImmOrg.hpp:1463:17( [780] >record 'ImmAdapterBlockAdmonitionAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1463:17( [780] >record 'ImmAdapterBlockAPI'<>) */>(m, "ImmAdapterBlockAdmonitionAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockCodeEvalResultAPI /*  [905]imm/ImmOrg.hpp:1464:17( [780] >record 'ImmAdapterBlockCodeEvalResultAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1464:17( [780] >record 'ImmAdapterBlockAPI'<>) */>(m, "ImmAdapterBlockCodeEvalResultAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockCodeAPI /*  [905]imm/ImmOrg.hpp:1465:17( [780] >record 'ImmAdapterBlockCodeAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1465:17( [780] >record 'ImmAdapterBlockAPI'<>) */>(m, "ImmAdapterBlockCodeAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterTableAPI /*  [905]imm/ImmOrg.hpp:1470:17( [780] >record 'ImmAdapterTableAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterBlockAPI /*  [905]imm/ImmOrg.hpp:1470:17( [780] >record 'ImmAdapterBlockAPI'<>) */>(m, "ImmAdapterTableAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlock>, org::imm::ImmAdapterBlockAPI>(m, "ImmBlockAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCell>, org::imm::ImmAdapterCellAPI>(m, "ImmCellAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getIsBlock", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmCell>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCell>::getIsBlock))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmRow>, org::imm::ImmAdapterRowAPI>(m, "ImmRowAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getCells", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmRow>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRow>::getCells))
    .def("getIsBlock", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmRow>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmRow>::getIsBlock))
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdCaptionAPI /*  [905]imm/ImmOrg.hpp:1396:17( [780] >record 'ImmAdapterCmdCaptionAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttachedAPI /*  [905]imm/ImmOrg.hpp:1396:17( [780] >record 'ImmAdapterAttachedAPI'<>) */>(m, "ImmAdapterCmdCaptionAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdColumnsAPI /*  [905]imm/ImmOrg.hpp:1399:17( [780] >record 'ImmAdapterCmdColumnsAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttachedAPI /*  [905]imm/ImmOrg.hpp:1399:17( [780] >record 'ImmAdapterAttachedAPI'<>) */>(m, "ImmAdapterCmdColumnsAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdNameAPI /*  [905]imm/ImmOrg.hpp:1400:17( [780] >record 'ImmAdapterCmdNameAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttachedAPI /*  [905]imm/ImmOrg.hpp:1400:17( [780] >record 'ImmAdapterAttachedAPI'<>) */>(m, "ImmAdapterCmdNameAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdCallAPI /*  [905]imm/ImmOrg.hpp:1401:17( [780] >record 'ImmAdapterCmdCallAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttachedAPI /*  [905]imm/ImmOrg.hpp:1401:17( [780] >record 'ImmAdapterAttachedAPI'<>) */>(m, "ImmAdapterCmdCallAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdResultsAPI /*  [905]imm/ImmOrg.hpp:1409:17( [780] >record 'ImmAdapterCmdResultsAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttachedAPI /*  [905]imm/ImmOrg.hpp:1409:17( [780] >record 'ImmAdapterAttachedAPI'<>) */>(m, "ImmAdapterCmdResultsAPI")
    ;
  nanobind::class_<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterCmdAttrAPI /*  [905]imm/ImmOrg.hpp:1486:17( [780] >record 'ImmAdapterCmdAttrAPI'<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAdapterAttachedAPI /*  [905]imm/ImmOrg.hpp:1486:17( [780] >record 'ImmAdapterAttachedAPI'<>) */>(m, "ImmAdapterCmdAttrAPI")
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmAttached>, org::imm::ImmAdapterAttachedAPI>(m, "ImmAttachedAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockCenter>, org::imm::ImmAdapterBlockCenterAPI>(m, "ImmBlockCenterAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockQuote>, org::imm::ImmAdapterBlockQuoteAPI>(m, "ImmBlockQuoteAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockVerse>, org::imm::ImmAdapterBlockVerseAPI>(m, "ImmBlockVerseAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockExample>, org::imm::ImmAdapterBlockExampleAPI>(m, "ImmBlockExampleAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmInlineExport>, org::imm::ImmAdapterInlineExportAPI>(m, "ImmInlineExportAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getExporter", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmInlineExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineExport>::getExporter))
    .def("getContent", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmInlineExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmInlineExport>::getContent))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdExport>, org::imm::ImmAdapterCmdExportAPI>(m, "ImmCmdExportAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getExporter", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdExport>::getExporter))
    .def("getContent", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdExport>::getContent))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockExport>, org::imm::ImmAdapterBlockExportAPI>(m, "ImmBlockExportAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getExporter", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmBlockExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockExport>::getExporter))
    .def("getContent", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmBlockExport>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockExport>::getContent))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>, org::imm::ImmAdapterBlockDynamicFallbackAPI>(m, "ImmBlockDynamicFallbackAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback>::getName))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition>, org::imm::ImmAdapterBlockAdmonitionAPI>(m, "ImmBlockAdmonitionAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>, org::imm::ImmAdapterBlockCodeEvalResultAPI>(m, "ImmBlockCodeEvalResultAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getRaw", static_cast<hstd::ext::ImmVec<org::sem::OrgCodeEvalOutput> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::getRaw))
    .def("getNode", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult>::getNode))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmBlockCode>, org::imm::ImmAdapterBlockCodeAPI>(m, "ImmBlockCodeAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getLang", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getLang))
    .def("getResult", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getResult))
    .def("getLines", static_cast<hstd::ext::ImmVec<org::sem::BlockCodeLine> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getLines))
    .def("getSwitches", static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmBlockCode>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmBlockCode>::getSwitches))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmTable>, org::imm::ImmAdapterTableAPI>(m, "ImmTableAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getRows", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmTable>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTable>::getRows))
    .def("getIsBlock", static_cast<bool /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmTable>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmTable>::getIsBlock))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCaption>, org::imm::ImmAdapterCmdCaptionAPI>(m, "ImmCmdCaptionAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getText", static_cast<org::imm::ImmAdapter(org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCaption>::getText))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdColumns>, org::imm::ImmAdapterCmdColumnsAPI>(m, "ImmCmdColumnsAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getView", static_cast<org::sem::ColumnView(org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdColumns>::getView))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdName>, org::imm::ImmAdapterCmdNameAPI>(m, "ImmCmdNameAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdName>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdName>::getName))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdCall>, org::imm::ImmAdapterCmdCallAPI>(m, "ImmCmdCallAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getName", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getName))
    .def("getFileName", static_cast<hstd::Opt<hstd /* imm_write */::Str /* imm_write */> const&(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getFileName))
    .def("getInsideHeaderAttrs", static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getInsideHeaderAttrs))
    .def("getCallAttrs", static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getCallAttrs))
    .def("getEndHeaderAttrs", static_cast<org::sem::AttrGroup(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getEndHeaderAttrs))
    .def("getResult", static_cast<hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult /* imm_write */> /* imm_write */> /* imm_write */(org::imm::ImmAdapterT<org::imm::ImmCmdCall>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdCall>::getResult))
    ;
  nanobind::class_<org::imm::ImmAdapterT<org::imm::ImmCmdAttr>, org::imm::ImmAdapterCmdAttrAPI>(m, "ImmCmdAttrAdapter")
    .def(nanobind::init<org::imm::ImmAdapter const&>())
    .def("getTarget", static_cast<hstd::Str const&(org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::*)() const>(&org::imm::ImmAdapterT<org::imm::ImmCmdAttr>::getTarget))
    ;
  bind_enum_iterator<CheckboxState>(m, "CheckboxState", type_registry_guard);
  nanobind::enum_<CheckboxState>(m, "CheckboxState")
    .value("None", CheckboxState::None)
    .value("Done", CheckboxState::Done)
    .value("Empty", CheckboxState::Empty)
    .value("Partial", CheckboxState::Partial)
    .def("__iter__", [](CheckboxState const& _self) -> org::bind::python::PyEnumIterator<CheckboxState> {
                     return org::bind::python::PyEnumIterator<CheckboxState>();
                     })
    .def("__int__", [](CheckboxState const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](CheckboxState const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](CheckboxState lhs, CheckboxState rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](CheckboxState it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<SubtreeTodoSource>(m, "SubtreeTodoSource", type_registry_guard);
  nanobind::enum_<SubtreeTodoSource>(m, "SubtreeTodoSource")
    .value("Checkbox", SubtreeTodoSource::Checkbox, R"RAW(Only count checkbox subnodes as a progress completion)RAW")
    .value("Todo", SubtreeTodoSource::Todo, R"RAW(Use subtrees with todo keywords)RAW")
    .value("Both", SubtreeTodoSource::Both, R"RAW(Use both subtrees and todo keywords)RAW")
    .def("__iter__", [](SubtreeTodoSource const& _self) -> org::bind::python::PyEnumIterator<SubtreeTodoSource> {
                     return org::bind::python::PyEnumIterator<SubtreeTodoSource>();
                     })
    .def("__int__", [](SubtreeTodoSource const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](SubtreeTodoSource const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](SubtreeTodoSource lhs, SubtreeTodoSource rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](SubtreeTodoSource it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<ListFormattingMode>(m, "ListFormattingMode", type_registry_guard);
  nanobind::enum_<ListFormattingMode>(m, "ListFormattingMode")
    .value("None", ListFormattingMode::None, R"RAW(Default, no custom formatting)RAW")
    .value("Table1D1Col", ListFormattingMode::Table1D1Col, R"RAW(one column, each table item is an individual row)RAW")
    .value("Table1D2Col", ListFormattingMode::Table1D2Col, R"RAW(for description lists, treat header row as an individual column)RAW")
    .value("Table2DColFirst", ListFormattingMode::Table2DColFirst, R"RAW(for tables tables with arbitrary column count, treat the first level of items as column names, treat all nested elements in these columns as row values)RAW")
    .value("Table2DRowFirst", ListFormattingMode::Table2DRowFirst, R"RAW(for tables with arbitrary column count, each top-level list item is an individual row, then each item in the nested list is a cell on this row.)RAW")
    .def("__iter__", [](ListFormattingMode const& _self) -> org::bind::python::PyEnumIterator<ListFormattingMode> {
                     return org::bind::python::PyEnumIterator<ListFormattingMode>();
                     })
    .def("__int__", [](ListFormattingMode const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](ListFormattingMode const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](ListFormattingMode lhs, ListFormattingMode rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](ListFormattingMode it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<InitialSubtreeVisibility>(m, "InitialSubtreeVisibility", type_registry_guard);
  nanobind::enum_<InitialSubtreeVisibility>(m, "InitialSubtreeVisibility")
    .value("Overview", InitialSubtreeVisibility::Overview)
    .value("Content", InitialSubtreeVisibility::Content)
    .value("ShowAll", InitialSubtreeVisibility::ShowAll)
    .value("Show2Levels", InitialSubtreeVisibility::Show2Levels)
    .value("Show3Levels", InitialSubtreeVisibility::Show3Levels)
    .value("Show4Levels", InitialSubtreeVisibility::Show4Levels)
    .value("Show5Levels", InitialSubtreeVisibility::Show5Levels)
    .value("ShowEverything", InitialSubtreeVisibility::ShowEverything)
    .def("__iter__", [](InitialSubtreeVisibility const& _self) -> org::bind::python::PyEnumIterator<InitialSubtreeVisibility> {
                     return org::bind::python::PyEnumIterator<InitialSubtreeVisibility>();
                     })
    .def("__int__", [](InitialSubtreeVisibility const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](InitialSubtreeVisibility const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](InitialSubtreeVisibility lhs, InitialSubtreeVisibility rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](InitialSubtreeVisibility it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<OrgSpecName>(m, "OrgSpecName", type_registry_guard);
  nanobind::enum_<OrgSpecName>(m, "OrgSpecName")
    .value("Unnamed", OrgSpecName::Unnamed)
    .value("Result", OrgSpecName::Result)
    .value("Year", OrgSpecName::Year)
    .value("Day", OrgSpecName::Day)
    .value("Clock", OrgSpecName::Clock)
    .value("Repeater", OrgSpecName::Repeater)
    .value("Warn", OrgSpecName::Warn)
    .value("Zone", OrgSpecName::Zone)
    .value("Link", OrgSpecName::Link)
    .value("Tags", OrgSpecName::Tags)
    .value("Tag", OrgSpecName::Tag)
    .value("State", OrgSpecName::State)
    .value("Protocol", OrgSpecName::Protocol)
    .value("Desc", OrgSpecName::Desc)
    .value("Times", OrgSpecName::Times)
    .value("Drawer", OrgSpecName::Drawer)
    .value("Args", OrgSpecName::Args)
    .value("Name", OrgSpecName::Name)
    .value("Definition", OrgSpecName::Definition)
    .value("Body", OrgSpecName::Body)
    .value("HeaderArgs", OrgSpecName::HeaderArgs)
    .value("File", OrgSpecName::File)
    .value("Kind", OrgSpecName::Kind)
    .value("Lang", OrgSpecName::Lang)
    .value("Prefix", OrgSpecName::Prefix)
    .value("Text", OrgSpecName::Text)
    .value("Todo", OrgSpecName::Todo)
    .value("Importance", OrgSpecName::Importance)
    .value("Title", OrgSpecName::Title)
    .value("Completion", OrgSpecName::Completion)
    .value("Head", OrgSpecName::Head)
    .value("Subnodes", OrgSpecName::Subnodes)
    .value("Properties", OrgSpecName::Properties)
    .value("Logbook", OrgSpecName::Logbook)
    .value("Description", OrgSpecName::Description)
    .value("Logs", OrgSpecName::Logs)
    .value("Newstate", OrgSpecName::Newstate)
    .value("Oldstate", OrgSpecName::Oldstate)
    .value("Time", OrgSpecName::Time)
    .value("From", OrgSpecName::From)
    .value("EndArgs", OrgSpecName::EndArgs)
    .value("Flags", OrgSpecName::Flags)
    .value("Value", OrgSpecName::Value)
    .value("Assoc", OrgSpecName::Assoc)
    .value("Main", OrgSpecName::Main)
    .value("Hash", OrgSpecName::Hash)
    .value("Bullet", OrgSpecName::Bullet)
    .value("Counter", OrgSpecName::Counter)
    .value("Checkbox", OrgSpecName::Checkbox)
    .value("Header", OrgSpecName::Header)
    .value("To", OrgSpecName::To)
    .value("Diff", OrgSpecName::Diff)
    .value("Property", OrgSpecName::Property)
    .value("Subname", OrgSpecName::Subname)
    .value("Values", OrgSpecName::Values)
    .value("Cells", OrgSpecName::Cells)
    .value("Rows", OrgSpecName::Rows)
    .value("Lines", OrgSpecName::Lines)
    .value("Chunks", OrgSpecName::Chunks)
    .def("__iter__", [](OrgSpecName const& _self) -> org::bind::python::PyEnumIterator<OrgSpecName> {
                     return org::bind::python::PyEnumIterator<OrgSpecName>();
                     })
    .def("__int__", [](OrgSpecName const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](OrgSpecName const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](OrgSpecName lhs, OrgSpecName rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](OrgSpecName it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<OrgNodeKind>(m, "OrgNodeKind", type_registry_guard);
  nanobind::enum_<OrgNodeKind>(m, "OrgNodeKind")
    .value("None", OrgNodeKind::None, R"RAW(Default valye for node - invalid state)RAW")
    .value("Document", OrgNodeKind::Document, R"RAW(Toplevel part of the ast, not created by parser, and only used in `semorg` stage)RAW")
    .value("Empty", OrgNodeKind::Empty, R"RAW(Empty node - valid state that does not contain any value)RAW")
    .value("InlineStmtList", OrgNodeKind::InlineStmtList)
    .value("StmtList", OrgNodeKind::StmtList, R"RAW(List of statements, possibly recursive. Used as toplevel part of the document, in recursive parsing of subtrees, or as regular list, in cases where multiple subnodes have to be grouped together.)RAW")
    .value("Checkbox", OrgNodeKind::Checkbox, R"RAW(Single checkbox item like `[X]` or `[-]`)RAW")
    .value("List", OrgNodeKind::List)
    .value("Bullet", OrgNodeKind::Bullet, R"RAW(List item prefix)RAW")
    .value("ListItem", OrgNodeKind::ListItem)
    .value("ListTag", OrgNodeKind::ListTag, R"RAW(Auxilliary wrapper for the paragraph placed at the start of the description list.)RAW")
    .value("Counter", OrgNodeKind::Counter)
    .value("File", OrgNodeKind::File)
    .value("ColonExample", OrgNodeKind::ColonExample, R"RAW(Colon example block)RAW")
    .value("TextSeparator", OrgNodeKind::TextSeparator, R"RAW(Long horizontal line `----`)RAW")
    .value("Paragraph", OrgNodeKind::Paragraph, R"RAW(Single 'paragraph' of text. Used as generic container for any place in AST where unordered sentence might be encountered (e.g. caption, link description) - not limited to actual paragraph)RAW")
    .value("TableRow", OrgNodeKind::TableRow, R"RAW(Horizontal table row)RAW")
    .value("TableCell", OrgNodeKind::TableCell, R"RAW(Single cell in row. Might contain anyting, including other tables, simple text paragraph etc.)RAW")
    .value("Table", OrgNodeKind::Table, R"RAW(Org-mode table)RAW")
    .value("InlineFootnote", OrgNodeKind::InlineFootnote, R"RAW(Inline footnote with text placed directly in the node body.)RAW")
    .value("Footnote", OrgNodeKind::Footnote, R"RAW(Footnote entry. Just as regular links - internal content is not parsed, and instead just cut out verbatim into target AST node.)RAW")
    .value("Cmd", OrgNodeKind::Cmd, R"RAW(Undefined single-line command -- most likely custom user-provided oe)RAW")
    .value("Attrs", OrgNodeKind::Attrs, R"RAW(Arguments for the command block)RAW")
    .value("AttrValue", OrgNodeKind::AttrValue, R"RAW(:key name=value syntax)RAW")
    .value("AttrLisp", OrgNodeKind::AttrLisp, R"RAW(S-expression as an attribute value value)RAW")
    .value("CmdTitle", OrgNodeKind::CmdTitle, R"RAW(`#+title:` - full document title)RAW")
    .value("CmdAuthor", OrgNodeKind::CmdAuthor, R"RAW(`#+author:` Document author)RAW")
    .value("CmdCreator", OrgNodeKind::CmdCreator, R"RAW(`#+creator:` Document creator)RAW")
    .value("CmdInclude", OrgNodeKind::CmdInclude, R"RAW(`#+include:` - include other org-mode document (or subsection of it), source code or backend-specific chunk.)RAW")
    .value("CmdLanguage", OrgNodeKind::CmdLanguage, R"RAW(`#+language:`)RAW")
    .value("CmdEmail", OrgNodeKind::CmdEmail, R"RAW(`#+email:`)RAW")
    .value("CmdAttr", OrgNodeKind::CmdAttr, R"RAW(`#+attr_html:`, `#+attr_image` etc.)RAW")
    .value("CmdStartup", OrgNodeKind::CmdStartup, R"RAW(`#+startup:`)RAW")
    .value("CmdName", OrgNodeKind::CmdName, R"RAW(`#+name:` - name of the associated entry)RAW")
    .value("CmdCustomTextCommand", OrgNodeKind::CmdCustomTextCommand, R"RAW(Line command with parsed text value)RAW")
    .value("CmdCustomArgsCommand", OrgNodeKind::CmdCustomArgsCommand, R"RAW(Line command with parsed argument list)RAW")
    .value("CmdCustomRawCommand", OrgNodeKind::CmdCustomRawCommand, R"RAW(Line command with raw text argument)RAW")
    .value("CmdResults", OrgNodeKind::CmdResults, R"RAW(`#+results:` - source code block evaluation results)RAW")
    .value("CmdHeader", OrgNodeKind::CmdHeader, R"RAW(`#+header:` - extended list of parameters passed to associated block)RAW")
    .value("CmdOptions", OrgNodeKind::CmdOptions, R"RAW(`#+options:` - document-wide formatting options)RAW")
    .value("CmdTblfm", OrgNodeKind::CmdTblfm)
    .value("CmdCaption", OrgNodeKind::CmdCaption, R"RAW(`#+caption:` command)RAW")
    .value("CmdResult", OrgNodeKind::CmdResult, R"RAW(Command evaluation result)RAW")
    .value("CmdCallCode", OrgNodeKind::CmdCallCode, R"RAW(Call to named source code block.)RAW")
    .value("CmdFlag", OrgNodeKind::CmdFlag, R"RAW(Flag for source code block. For example `-n`, which is used to to make source code block export with lines)RAW")
    .value("CmdLatexClass", OrgNodeKind::CmdLatexClass)
    .value("CmdLatexHeader", OrgNodeKind::CmdLatexHeader)
    .value("CmdLatexCompiler", OrgNodeKind::CmdLatexCompiler)
    .value("CmdLatexClassOptions", OrgNodeKind::CmdLatexClassOptions)
    .value("CmdHtmlHead", OrgNodeKind::CmdHtmlHead)
    .value("CmdColumns", OrgNodeKind::CmdColumns, R"RAW(`#+columns:` line command for specifying formatting of the org-mode clock table visualization on per-file basis.)RAW")
    .value("CmdPropertyArgs", OrgNodeKind::CmdPropertyArgs, R"RAW(`#+property:` command)RAW")
    .value("CmdPropertyText", OrgNodeKind::CmdPropertyText, R"RAW(`#+property:` command)RAW")
    .value("CmdPropertyRaw", OrgNodeKind::CmdPropertyRaw, R"RAW(`#+property:` command)RAW")
    .value("CmdFiletags", OrgNodeKind::CmdFiletags, R"RAW(`#+filetags:` line command)RAW")
    .value("CmdKeywords", OrgNodeKind::CmdKeywords)
    .value("BlockVerbatimMultiline", OrgNodeKind::BlockVerbatimMultiline, R"RAW(Verbatim mulitiline block that *might* be a part of `orgMultilineCommand` (in case of `#+begin-src`), but not necessarily. Can also be a part of =quote= and =example= multiline blocks.)RAW")
    .value("CodeLine", OrgNodeKind::CodeLine, R"RAW(Single line of source code)RAW")
    .value("CodeText", OrgNodeKind::CodeText, R"RAW(Block of source code text)RAW")
    .value("CodeTangle", OrgNodeKind::CodeTangle, R"RAW(Single tangle target in the code block)RAW")
    .value("CodeCallout", OrgNodeKind::CodeCallout, R"RAW(`(refs:` callout in the source code)RAW")
    .value("BlockCode", OrgNodeKind::BlockCode)
    .value("BlockQuote", OrgNodeKind::BlockQuote, R"RAW(`#+begin_quote:` block in code)RAW")
    .value("BlockComment", OrgNodeKind::BlockComment, R"RAW(`#+begin_comment:` block in code)RAW")
    .value("BlockCenter", OrgNodeKind::BlockCenter)
    .value("BlockVerse", OrgNodeKind::BlockVerse)
    .value("BlockExample", OrgNodeKind::BlockExample, R"RAW(Verbatim example text block)RAW")
    .value("BlockExport", OrgNodeKind::BlockExport)
    .value("BlockDetails", OrgNodeKind::BlockDetails, R"RAW(`#+begin_details`  section)RAW")
    .value("BlockSummary", OrgNodeKind::BlockSummary, R"RAW(`#+begin_summary` section)RAW")
    .value("BlockDynamicFallback", OrgNodeKind::BlockDynamicFallback, R"RAW(#+begin_<any> section)RAW")
    .value("BigIdent", OrgNodeKind::BigIdent, R"RAW(full-uppsercase identifier such as `MUST` or `TODO`)RAW")
    .value("Bold", OrgNodeKind::Bold, R"RAW(Region of text with formatting, which contains standalone words -
     can itself contain subnodes, which allows to represent nested
     formatting regions, such as `*bold /italic/*` text. Particular type
     of identifier is stored in string form in `str` field for `OrgNode`
     -- bold is represented as `"*"`, italic as `/` and so on. In case
     of explicit open/close pairs only opening one is stored.

     NOTE: when structured sentences are enabled, regular punctuation
     elements like `some text (notes)` are also represented as `Word,
     Word, Markup(str: "(", [Word])` - e.g. structure is not fully flat.)RAW")
    .value("ErrorInfoToken", OrgNodeKind::ErrorInfoToken, R"RAW(Error leaf node inserted into the parse tree on failure)RAW")
    .value("ErrorSkipGroup", OrgNodeKind::ErrorSkipGroup, R"RAW(Parent node for one or more tokens skipped during error recovery)RAW")
    .value("ErrorSkipToken", OrgNodeKind::ErrorSkipToken, R"RAW(Single token node skipped while the parser searched for recovery point)RAW")
    .value("Italic", OrgNodeKind::Italic)
    .value("Verbatim", OrgNodeKind::Verbatim)
    .value("Backtick", OrgNodeKind::Backtick)
    .value("Underline", OrgNodeKind::Underline)
    .value("Strike", OrgNodeKind::Strike)
    .value("Quote", OrgNodeKind::Quote)
    .value("Angle", OrgNodeKind::Angle)
    .value("Monospace", OrgNodeKind::Monospace)
    .value("Par", OrgNodeKind::Par)
    .value("CriticMarkStructure", OrgNodeKind::CriticMarkStructure)
    .value("InlineMath", OrgNodeKind::InlineMath, R"RAW(Inline latex math. Contains latex math body - either from `$dollar-wrapped$` or `\(paren-wrapped\)` inline text.)RAW")
    .value("DisplayMath", OrgNodeKind::DisplayMath, R"RAW(Inline display latex math from `$$double-dollar$$` or `\[bracket-wrapped\]` code.)RAW")
    .value("Space", OrgNodeKind::Space, R"RAW(Space or tab character in regular text)RAW")
    .value("Punctuation", OrgNodeKind::Punctuation)
    .value("Colon", OrgNodeKind::Colon)
    .value("Word", OrgNodeKind::Word, R"RAW(Regular word - technically not different from `orgIdent`, but defined separately to disiguish between places where special syntax is required and free-form text.)RAW")
    .value("Escaped", OrgNodeKind::Escaped, R"RAW(Escaped formatting character in the text)RAW")
    .value("Newline", OrgNodeKind::Newline)
    .value("RawLink", OrgNodeKind::RawLink, R"RAW(Raw unwrapped link that was pasted in text)RAW")
    .value("Link", OrgNodeKind::Link, R"RAW(External or internal link. Consists of one or two elements - target
     (url, file location etc.) and description (`orgParagraph` of text).
     Description might be empty, and represented as empty node in this
     case. For external links particular formatting of the address is
     not handled by parser and instead contains raw string from input
     text.)RAW")
    .value("Macro", OrgNodeKind::Macro, R"RAW(Org-mode macro replacement - during export each macro is expanded
     and evaluated according to it's environment. Body of the macro is
     not parsed fully during org-mode evaluation, but is checked for
     correct parenthesis balance (as macro might contain elisp code))RAW")
    .value("Symbol", OrgNodeKind::Symbol, R"RAW(Special symbol that should be exported differently to various backends - greek letters (`lpha`), mathematical notations and so on.)RAW")
    .value("StaticActiveTime", OrgNodeKind::StaticActiveTime)
    .value("StaticInactiveTime", OrgNodeKind::StaticInactiveTime)
    .value("DynamicActiveTime", OrgNodeKind::DynamicActiveTime)
    .value("DynamicInactiveTime", OrgNodeKind::DynamicInactiveTime, R"RAW(Single date and time entry (active or inactive),, possibly with repeater interval. Is not parsed directly, and instead contains `orgRawText` that can be parsed later)RAW")
    .value("TimeRange", OrgNodeKind::TimeRange, R"RAW(Date and time range format - two `orgDateTime` entries)RAW")
    .value("SimpleTime", OrgNodeKind::SimpleTime, R"RAW(Result of the time range evaluation or trailing annotation a subtree)RAW")
    .value("HashTag", OrgNodeKind::HashTag)
    .value("MetaSymbol", OrgNodeKind::MetaSymbol, R"RAW(`\sym{}` with explicit arguments)RAW")
    .value("AtMention", OrgNodeKind::AtMention, R"RAW(`@user`)RAW")
    .value("Placeholder", OrgNodeKind::Placeholder, R"RAW(Placeholder entry in text, usually writte like `<text to replace>`)RAW")
    .value("RadioTarget", OrgNodeKind::RadioTarget, R"RAW(`<<<RADIO>>>`)RAW")
    .value("Target", OrgNodeKind::Target, R"RAW(`<<TARGET>>`)RAW")
    .value("SrcInlineCode", OrgNodeKind::SrcInlineCode, R"RAW(inline piece of code (such as `src_nim`),. Latter is different from regular monospaced text inside of `~~` pair as it contains additional internal structure, optional parameter for code evaluation etc.)RAW")
    .value("InlineCallCode", OrgNodeKind::InlineCallCode, R"RAW(Call to named source code block.)RAW")
    .value("InlineExport", OrgNodeKind::InlineExport, R"RAW(Passthrough block. Inline, multiline, or single-line. Syntax is `@@<backend-name>:<any-body>@@`. Has line and block syntax respectively)RAW")
    .value("InlineComment", OrgNodeKind::InlineComment)
    .value("RawText", OrgNodeKind::RawText, R"RAW(Raw string of text from input buffer. Things like particular syntax details of every single command, link formats are not handled in parser, deferring formatting to future processing layers )RAW")
    .value("SubtreeDescription", OrgNodeKind::SubtreeDescription, R"RAW(`:description:` entry)RAW")
    .value("SubtreeUrgency", OrgNodeKind::SubtreeUrgency)
    .value("DrawerLogbook", OrgNodeKind::DrawerLogbook, R"RAW(`:logbook:` entry storing note information)RAW")
    .value("Drawer", OrgNodeKind::Drawer, R"RAW(Single enclosed drawer like `:properties: ... :end:` or `:logbook: ... :end:`)RAW")
    .value("DrawerPropertyList", OrgNodeKind::DrawerPropertyList)
    .value("DrawerProperty", OrgNodeKind::DrawerProperty, R"RAW(`:property:` drawer)RAW")
    .value("Subtree", OrgNodeKind::Subtree, R"RAW(Section subtree)RAW")
    .value("SubtreeTimes", OrgNodeKind::SubtreeTimes, R"RAW(Time? associated with subtree entry)RAW")
    .value("SubtreeStars", OrgNodeKind::SubtreeStars)
    .value("SubtreeCompletion", OrgNodeKind::SubtreeCompletion, R"RAW(Task compleation cookie, indicated either in percents of completion, or as `<done>/<todo>` ratio.)RAW")
    .value("SubtreeImportance", OrgNodeKind::SubtreeImportance, R"RAW(Subtree importance level, such as `[#A]` or `[#B]`. Default org-mode only allows single character for contents inside of `[]`, but this parser makes it possible to use any regular identifier, such as `[#urgent]`.)RAW")
    .def("__iter__", [](OrgNodeKind const& _self) -> org::bind::python::PyEnumIterator<OrgNodeKind> {
                     return org::bind::python::PyEnumIterator<OrgNodeKind>();
                     })
    .def("__int__", [](OrgNodeKind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](OrgNodeKind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](OrgNodeKind lhs, OrgNodeKind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](OrgNodeKind it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<OrgTokenKind>(m, "OrgTokenKind", type_registry_guard);
  nanobind::enum_<OrgTokenKind>(m, "OrgTokenKind")
    .value("Ampersand", OrgTokenKind::Ampersand)
    .value("AngleBegin", OrgTokenKind::AngleBegin)
    .value("AngleEnd", OrgTokenKind::AngleEnd)
    .value("AnyPunct", OrgTokenKind::AnyPunct)
    .value("Asterisk", OrgTokenKind::Asterisk)
    .value("At", OrgTokenKind::At)
    .value("Backtick", OrgTokenKind::Backtick)
    .value("BigIdent", OrgTokenKind::BigIdent)
    .value("BoldBegin", OrgTokenKind::BoldBegin)
    .value("BoldEnd", OrgTokenKind::BoldEnd)
    .value("BoldUnknown", OrgTokenKind::BoldUnknown)
    .value("BraceBegin", OrgTokenKind::BraceBegin)
    .value("BraceEnd", OrgTokenKind::BraceEnd)
    .value("Checkbox", OrgTokenKind::Checkbox)
    .value("Circumflex", OrgTokenKind::Circumflex)
    .value("CmdAdmonitionEnd", OrgTokenKind::CmdAdmonitionEnd)
    .value("CmdAttr", OrgTokenKind::CmdAttr)
    .value("CmdAuthor", OrgTokenKind::CmdAuthor)
    .value("CmdBindRaw", OrgTokenKind::CmdBindRaw)
    .value("CmdCall", OrgTokenKind::CmdCall)
    .value("CmdCaption", OrgTokenKind::CmdCaption)
    .value("CmdCategoryRaw", OrgTokenKind::CmdCategoryRaw)
    .value("CmdCell", OrgTokenKind::CmdCell)
    .value("CmdCellBegin", OrgTokenKind::CmdCellBegin)
    .value("CmdCellEnd", OrgTokenKind::CmdCellEnd)
    .value("CmdCenterBegin", OrgTokenKind::CmdCenterBegin)
    .value("CmdCenterEnd", OrgTokenKind::CmdCenterEnd)
    .value("CmdColonIdent", OrgTokenKind::CmdColonIdent)
    .value("CmdColumns", OrgTokenKind::CmdColumns)
    .value("CmdCommentBegin", OrgTokenKind::CmdCommentBegin)
    .value("CmdCommentEnd", OrgTokenKind::CmdCommentEnd)
    .value("CmdConstants", OrgTokenKind::CmdConstants)
    .value("CmdContentBegin", OrgTokenKind::CmdContentBegin)
    .value("CmdContentEnd", OrgTokenKind::CmdContentEnd)
    .value("CmdCreator", OrgTokenKind::CmdCreator)
    .value("CmdCustomRaw", OrgTokenKind::CmdCustomRaw)
    .value("CmdDateRaw", OrgTokenKind::CmdDateRaw)
    .value("CmdDescription", OrgTokenKind::CmdDescription)
    .value("CmdDrawersRaw", OrgTokenKind::CmdDrawersRaw)
    .value("CmdDynamicBegin", OrgTokenKind::CmdDynamicBegin)
    .value("CmdDynamicBlockBegin", OrgTokenKind::CmdDynamicBlockBegin)
    .value("CmdDynamicBlockEnd", OrgTokenKind::CmdDynamicBlockEnd)
    .value("CmdDynamicEnd", OrgTokenKind::CmdDynamicEnd)
    .value("CmdEmailRaw", OrgTokenKind::CmdEmailRaw)
    .value("CmdExampleBegin", OrgTokenKind::CmdExampleBegin)
    .value("CmdExampleEnd", OrgTokenKind::CmdExampleEnd)
    .value("CmdExampleLine", OrgTokenKind::CmdExampleLine)
    .value("CmdExcludeTagsRaw", OrgTokenKind::CmdExcludeTagsRaw)
    .value("CmdExportBegin", OrgTokenKind::CmdExportBegin)
    .value("CmdExportEnd", OrgTokenKind::CmdExportEnd)
    .value("CmdExportLine", OrgTokenKind::CmdExportLine)
    .value("CmdFiletags", OrgTokenKind::CmdFiletags)
    .value("CmdFlag", OrgTokenKind::CmdFlag)
    .value("CmdHeader", OrgTokenKind::CmdHeader)
    .value("CmdHtmlHeadRaw", OrgTokenKind::CmdHtmlHeadRaw)
    .value("CmdInclude", OrgTokenKind::CmdInclude)
    .value("CmdLanguage", OrgTokenKind::CmdLanguage)
    .value("CmdLatexClass", OrgTokenKind::CmdLatexClass)
    .value("CmdLatexClassOptions", OrgTokenKind::CmdLatexClassOptions)
    .value("CmdLatexCompiler", OrgTokenKind::CmdLatexCompiler)
    .value("CmdLatexHeader", OrgTokenKind::CmdLatexHeader)
    .value("CmdLatexHeaderExtraRaw", OrgTokenKind::CmdLatexHeaderExtraRaw)
    .value("CmdLinkRaw", OrgTokenKind::CmdLinkRaw)
    .value("CmdMacroRaw", OrgTokenKind::CmdMacroRaw)
    .value("CmdName", OrgTokenKind::CmdName)
    .value("CmdOptions", OrgTokenKind::CmdOptions)
    .value("CmdPrefix", OrgTokenKind::CmdPrefix)
    .value("CmdPrioritiesRaw", OrgTokenKind::CmdPrioritiesRaw)
    .value("CmdPropertyArgs", OrgTokenKind::CmdPropertyArgs)
    .value("CmdPropertyRaw", OrgTokenKind::CmdPropertyRaw)
    .value("CmdPropertyText", OrgTokenKind::CmdPropertyText)
    .value("CmdQuoteBegin", OrgTokenKind::CmdQuoteBegin)
    .value("CmdQuoteEnd", OrgTokenKind::CmdQuoteEnd)
    .value("CmdRawArg", OrgTokenKind::CmdRawArg)
    .value("CmdResults", OrgTokenKind::CmdResults)
    .value("CmdRow", OrgTokenKind::CmdRow)
    .value("CmdRowBegin", OrgTokenKind::CmdRowBegin)
    .value("CmdRowEnd", OrgTokenKind::CmdRowEnd)
    .value("CmdSelectTagsRaw", OrgTokenKind::CmdSelectTagsRaw)
    .value("CmdSeqTodoRaw", OrgTokenKind::CmdSeqTodoRaw)
    .value("CmdKeywordsRaw", OrgTokenKind::CmdKeywordsRaw)
    .value("CmdSetupfileRaw", OrgTokenKind::CmdSetupfileRaw)
    .value("CmdSrcBegin", OrgTokenKind::CmdSrcBegin)
    .value("CmdSrcEnd", OrgTokenKind::CmdSrcEnd)
    .value("CmdStartup", OrgTokenKind::CmdStartup)
    .value("CmdTableBegin", OrgTokenKind::CmdTableBegin)
    .value("CmdTableEnd", OrgTokenKind::CmdTableEnd)
    .value("CmdTagsRaw", OrgTokenKind::CmdTagsRaw)
    .value("CmdTblfm", OrgTokenKind::CmdTblfm)
    .value("CmdTitle", OrgTokenKind::CmdTitle)
    .value("CmdVerseBegin", OrgTokenKind::CmdVerseBegin)
    .value("CmdVerseEnd", OrgTokenKind::CmdVerseEnd)
    .value("Colon", OrgTokenKind::Colon)
    .value("ColonArgumentsProperty", OrgTokenKind::ColonArgumentsProperty)
    .value("ColonEnd", OrgTokenKind::ColonEnd)
    .value("ColonExampleLine", OrgTokenKind::ColonExampleLine)
    .value("ColonLiteralProperty", OrgTokenKind::ColonLiteralProperty)
    .value("ColonLogbook", OrgTokenKind::ColonLogbook)
    .value("ColonProperties", OrgTokenKind::ColonProperties)
    .value("ColonPropertyText", OrgTokenKind::ColonPropertyText)
    .value("Comma", OrgTokenKind::Comma)
    .value("Comment", OrgTokenKind::Comment)
    .value("CriticAddBegin", OrgTokenKind::CriticAddBegin)
    .value("CriticAddEnd", OrgTokenKind::CriticAddEnd)
    .value("CriticCommentBegin", OrgTokenKind::CriticCommentBegin)
    .value("CriticCommentEnd", OrgTokenKind::CriticCommentEnd)
    .value("CriticDeleteBegin", OrgTokenKind::CriticDeleteBegin)
    .value("CriticDeleteEnd", OrgTokenKind::CriticDeleteEnd)
    .value("CriticHighlightBegin", OrgTokenKind::CriticHighlightBegin)
    .value("CriticHighlightEnd", OrgTokenKind::CriticHighlightEnd)
    .value("CriticReplaceBegin", OrgTokenKind::CriticReplaceBegin)
    .value("CriticReplaceEnd", OrgTokenKind::CriticReplaceEnd)
    .value("CriticReplaceMiddle", OrgTokenKind::CriticReplaceMiddle)
    .value("CurlyBegin", OrgTokenKind::CurlyBegin)
    .value("CurlyEnd", OrgTokenKind::CurlyEnd)
    .value("Date", OrgTokenKind::Date)
    .value("Dedent", OrgTokenKind::Dedent)
    .value("Dollar", OrgTokenKind::Dollar)
    .value("DoubleAngleBegin", OrgTokenKind::DoubleAngleBegin)
    .value("DoubleAngleEnd", OrgTokenKind::DoubleAngleEnd)
    .value("DoubleColon", OrgTokenKind::DoubleColon)
    .value("DoubleDash", OrgTokenKind::DoubleDash)
    .value("DoubleHash", OrgTokenKind::DoubleHash)
    .value("DoubleQuote", OrgTokenKind::DoubleQuote)
    .value("DoubleSlash", OrgTokenKind::DoubleSlash)
    .value("ActiveDynamicTimeContent", OrgTokenKind::ActiveDynamicTimeContent)
    .value("InactiveDynamicTimeContent", OrgTokenKind::InactiveDynamicTimeContent)
    .value("EndOfFile", OrgTokenKind::EndOfFile)
    .value("Equals", OrgTokenKind::Equals)
    .value("Escaped", OrgTokenKind::Escaped)
    .value("Exclamation", OrgTokenKind::Exclamation)
    .value("FootnoteInlineBegin", OrgTokenKind::FootnoteInlineBegin)
    .value("FootnoteLinked", OrgTokenKind::FootnoteLinked)
    .value("ForwardSlash", OrgTokenKind::ForwardSlash)
    .value("HashIdent", OrgTokenKind::HashIdent)
    .value("HashTagBegin", OrgTokenKind::HashTagBegin)
    .value("Indent", OrgTokenKind::Indent)
    .value("InlineExportBackend", OrgTokenKind::InlineExportBackend)
    .value("InlineExportContent", OrgTokenKind::InlineExportContent)
    .value("ItalicBegin", OrgTokenKind::ItalicBegin)
    .value("ItalicEnd", OrgTokenKind::ItalicEnd)
    .value("ItalicUnknown", OrgTokenKind::ItalicUnknown)
    .value("LatexInlineRaw", OrgTokenKind::LatexInlineRaw)
    .value("LatexParBegin", OrgTokenKind::LatexParBegin)
    .value("LatexParEnd", OrgTokenKind::LatexParEnd)
    .value("LeadingMinus", OrgTokenKind::LeadingMinus)
    .value("LeadingNumber", OrgTokenKind::LeadingNumber)
    .value("LeadingPipe", OrgTokenKind::LeadingPipe)
    .value("LeadingPlus", OrgTokenKind::LeadingPlus)
    .value("LeadingSpace", OrgTokenKind::LeadingSpace)
    .value("LineCommand", OrgTokenKind::LineCommand)
    .value("LinkBegin", OrgTokenKind::LinkBegin)
    .value("LinkDescriptionBegin", OrgTokenKind::LinkDescriptionBegin)
    .value("LinkDescriptionEnd", OrgTokenKind::LinkDescriptionEnd)
    .value("LinkEnd", OrgTokenKind::LinkEnd)
    .value("LinkFull", OrgTokenKind::LinkFull)
    .value("LinkProtocol", OrgTokenKind::LinkProtocol)
    .value("LinkProtocolAttachment", OrgTokenKind::LinkProtocolAttachment)
    .value("LinkProtocolCustomId", OrgTokenKind::LinkProtocolCustomId)
    .value("LinkProtocolFile", OrgTokenKind::LinkProtocolFile)
    .value("LinkProtocolHttp", OrgTokenKind::LinkProtocolHttp)
    .value("LinkProtocolId", OrgTokenKind::LinkProtocolId)
    .value("LinkProtocolInternal", OrgTokenKind::LinkProtocolInternal)
    .value("LinkProtocolTitle", OrgTokenKind::LinkProtocolTitle)
    .value("LinkSplit", OrgTokenKind::LinkSplit)
    .value("LinkTarget", OrgTokenKind::LinkTarget)
    .value("LinkTargetBegin", OrgTokenKind::LinkTargetBegin)
    .value("LinkTargetEnd", OrgTokenKind::LinkTargetEnd)
    .value("LinkTargetFile", OrgTokenKind::LinkTargetFile)
    .value("ListBegin", OrgTokenKind::ListBegin)
    .value("ListEnd", OrgTokenKind::ListEnd)
    .value("ListItemBegin", OrgTokenKind::ListItemBegin)
    .value("ListItemEnd", OrgTokenKind::ListItemEnd)
    .value("LongNewline", OrgTokenKind::LongNewline)
    .value("MediumNewline", OrgTokenKind::MediumNewline)
    .value("Minus", OrgTokenKind::Minus)
    .value("MiscUnicode", OrgTokenKind::MiscUnicode)
    .value("MonospaceBegin", OrgTokenKind::MonospaceBegin)
    .value("MonospaceEnd", OrgTokenKind::MonospaceEnd)
    .value("MonospaceUnknown", OrgTokenKind::MonospaceUnknown)
    .value("Newline", OrgTokenKind::Newline)
    .value("Number", OrgTokenKind::Number)
    .value("ParBegin", OrgTokenKind::ParBegin)
    .value("ParEnd", OrgTokenKind::ParEnd)
    .value("Percent", OrgTokenKind::Percent)
    .value("Pipe", OrgTokenKind::Pipe)
    .value("Placeholder", OrgTokenKind::Placeholder)
    .value("Plus", OrgTokenKind::Plus)
    .value("Punctuation", OrgTokenKind::Punctuation)
    .value("RawText", OrgTokenKind::RawText)
    .value("SameIndent", OrgTokenKind::SameIndent)
    .value("Semicolon", OrgTokenKind::Semicolon)
    .value("SingleQuote", OrgTokenKind::SingleQuote)
    .value("SrcContent", OrgTokenKind::SrcContent)
    .value("StmtListBegin", OrgTokenKind::StmtListBegin)
    .value("StmtListEnd", OrgTokenKind::StmtListEnd)
    .value("StrikeBegin", OrgTokenKind::StrikeBegin)
    .value("StrikeEnd", OrgTokenKind::StrikeEnd)
    .value("StrikeUnknown", OrgTokenKind::StrikeUnknown)
    .value("SubtreeCompletion", OrgTokenKind::SubtreeCompletion)
    .value("SubtreePriority", OrgTokenKind::SubtreePriority)
    .value("SubtreeStars", OrgTokenKind::SubtreeStars)
    .value("Symbol", OrgTokenKind::Symbol)
    .value("TableSeparator", OrgTokenKind::TableSeparator)
    .value("TextSeparator", OrgTokenKind::TextSeparator)
    .value("TextSrcBegin", OrgTokenKind::TextSrcBegin)
    .value("Tilda", OrgTokenKind::Tilda)
    .value("Time", OrgTokenKind::Time)
    .value("TimeArrow", OrgTokenKind::TimeArrow)
    .value("TimeRepeaterDuration", OrgTokenKind::TimeRepeaterDuration)
    .value("TimeRepeaterSpec", OrgTokenKind::TimeRepeaterSpec)
    .value("TimeWarnPeriod", OrgTokenKind::TimeWarnPeriod)
    .value("TrailingPipe", OrgTokenKind::TrailingPipe)
    .value("TreeClock", OrgTokenKind::TreeClock)
    .value("TreeTime", OrgTokenKind::TreeTime)
    .value("TripleAngleBegin", OrgTokenKind::TripleAngleBegin)
    .value("TripleAngleEnd", OrgTokenKind::TripleAngleEnd)
    .value("Underline", OrgTokenKind::Underline)
    .value("UnderlineBegin", OrgTokenKind::UnderlineBegin)
    .value("UnderlineEnd", OrgTokenKind::UnderlineEnd)
    .value("UnderlineUnknown", OrgTokenKind::UnderlineUnknown)
    .value("Unknown", OrgTokenKind::Unknown)
    .value("VerbatimBegin", OrgTokenKind::VerbatimBegin)
    .value("VerbatimEnd", OrgTokenKind::VerbatimEnd)
    .value("VerbatimUnknown", OrgTokenKind::VerbatimUnknown)
    .value("Whitespace", OrgTokenKind::Whitespace)
    .value("Word", OrgTokenKind::Word)
    .def("__iter__", [](OrgTokenKind const& _self) -> org::bind::python::PyEnumIterator<OrgTokenKind> {
                     return org::bind::python::PyEnumIterator<OrgTokenKind>();
                     })
    .def("__int__", [](OrgTokenKind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](OrgTokenKind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](OrgTokenKind lhs, OrgTokenKind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](OrgTokenKind it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<OrgJsonKind>(m, "OrgJsonKind", type_registry_guard);
  nanobind::enum_<OrgJsonKind>(m, "OrgJsonKind")
    .value("Null", OrgJsonKind::Null)
    .value("Object", OrgJsonKind::Object)
    .value("Array", OrgJsonKind::Array)
    .value("String", OrgJsonKind::String)
    .value("Boolean", OrgJsonKind::Boolean)
    .value("Int", OrgJsonKind::Int)
    .value("Float", OrgJsonKind::Float)
    .def("__iter__", [](OrgJsonKind const& _self) -> org::bind::python::PyEnumIterator<OrgJsonKind> {
                     return org::bind::python::PyEnumIterator<OrgJsonKind>();
                     })
    .def("__int__", [](OrgJsonKind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](OrgJsonKind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](OrgJsonKind lhs, OrgJsonKind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](OrgJsonKind it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<OrgSemKind>(m, "OrgSemKind", type_registry_guard);
  nanobind::enum_<OrgSemKind>(m, "OrgSemKind")
    .value("NoNode", OrgSemKind::NoNode)
    .value("ErrorItem", OrgSemKind::ErrorItem)
    .value("ErrorGroup", OrgSemKind::ErrorGroup)
    .value("StmtList", OrgSemKind::StmtList)
    .value("Empty", OrgSemKind::Empty)
    .value("CmdCaption", OrgSemKind::CmdCaption)
    .value("CmdCreator", OrgSemKind::CmdCreator)
    .value("CmdAuthor", OrgSemKind::CmdAuthor)
    .value("CmdEmail", OrgSemKind::CmdEmail)
    .value("CmdLanguage", OrgSemKind::CmdLanguage)
    .value("CmdColumns", OrgSemKind::CmdColumns)
    .value("CmdName", OrgSemKind::CmdName)
    .value("CmdCustomArgs", OrgSemKind::CmdCustomArgs)
    .value("CmdCustomRaw", OrgSemKind::CmdCustomRaw)
    .value("CmdCustomText", OrgSemKind::CmdCustomText)
    .value("CmdCall", OrgSemKind::CmdCall)
    .value("CmdTblfm", OrgSemKind::CmdTblfm)
    .value("HashTag", OrgSemKind::HashTag)
    .value("InlineFootnote", OrgSemKind::InlineFootnote)
    .value("InlineExport", OrgSemKind::InlineExport)
    .value("Time", OrgSemKind::Time)
    .value("TimeRange", OrgSemKind::TimeRange)
    .value("Macro", OrgSemKind::Macro)
    .value("Symbol", OrgSemKind::Symbol)
    .value("Escaped", OrgSemKind::Escaped)
    .value("Newline", OrgSemKind::Newline)
    .value("Space", OrgSemKind::Space)
    .value("Word", OrgSemKind::Word)
    .value("AtMention", OrgSemKind::AtMention)
    .value("RawText", OrgSemKind::RawText)
    .value("Punctuation", OrgSemKind::Punctuation)
    .value("Placeholder", OrgSemKind::Placeholder)
    .value("BigIdent", OrgSemKind::BigIdent)
    .value("TextTarget", OrgSemKind::TextTarget)
    .value("ErrorSkipToken", OrgSemKind::ErrorSkipToken)
    .value("ErrorSkipGroup", OrgSemKind::ErrorSkipGroup)
    .value("Bold", OrgSemKind::Bold)
    .value("Underline", OrgSemKind::Underline)
    .value("Monospace", OrgSemKind::Monospace)
    .value("MarkQuote", OrgSemKind::MarkQuote)
    .value("Verbatim", OrgSemKind::Verbatim)
    .value("Italic", OrgSemKind::Italic)
    .value("Strike", OrgSemKind::Strike)
    .value("Par", OrgSemKind::Par)
    .value("RadioTarget", OrgSemKind::RadioTarget)
    .value("Latex", OrgSemKind::Latex)
    .value("Link", OrgSemKind::Link)
    .value("BlockCenter", OrgSemKind::BlockCenter)
    .value("BlockQuote", OrgSemKind::BlockQuote)
    .value("BlockComment", OrgSemKind::BlockComment)
    .value("BlockVerse", OrgSemKind::BlockVerse)
    .value("BlockDynamicFallback", OrgSemKind::BlockDynamicFallback)
    .value("BlockExample", OrgSemKind::BlockExample)
    .value("BlockExport", OrgSemKind::BlockExport)
    .value("BlockAdmonition", OrgSemKind::BlockAdmonition)
    .value("BlockCodeEvalResult", OrgSemKind::BlockCodeEvalResult)
    .value("BlockCode", OrgSemKind::BlockCode)
    .value("SubtreeLog", OrgSemKind::SubtreeLog)
    .value("Subtree", OrgSemKind::Subtree)
    .value("Cell", OrgSemKind::Cell)
    .value("Row", OrgSemKind::Row)
    .value("Table", OrgSemKind::Table)
    .value("Paragraph", OrgSemKind::Paragraph)
    .value("ColonExample", OrgSemKind::ColonExample)
    .value("CmdAttr", OrgSemKind::CmdAttr)
    .value("CmdExport", OrgSemKind::CmdExport)
    .value("Call", OrgSemKind::Call)
    .value("List", OrgSemKind::List)
    .value("ListItem", OrgSemKind::ListItem)
    .value("DocumentOptions", OrgSemKind::DocumentOptions)
    .value("DocumentFragment", OrgSemKind::DocumentFragment)
    .value("CriticMarkup", OrgSemKind::CriticMarkup)
    .value("Document", OrgSemKind::Document)
    .value("FileTarget", OrgSemKind::FileTarget)
    .value("TextSeparator", OrgSemKind::TextSeparator)
    .value("DocumentGroup", OrgSemKind::DocumentGroup)
    .value("File", OrgSemKind::File)
    .value("Directory", OrgSemKind::Directory)
    .value("Symlink", OrgSemKind::Symlink)
    .value("CmdInclude", OrgSemKind::CmdInclude)
    .def("__iter__", [](OrgSemKind const& _self) -> org::bind::python::PyEnumIterator<OrgSemKind> {
                     return org::bind::python::PyEnumIterator<OrgSemKind>();
                     })
    .def("__int__", [](OrgSemKind const& _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](OrgSemKind const& _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](OrgSemKind lhs, OrgSemKind rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](OrgSemKind it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct api/SemBaseApi.hpp:162:25 */>(m, "AstTrackingGroupKind", type_registry_guard);
  nanobind::enum_<org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct api/SemBaseApi.hpp:162:25 */>(m, "AstTrackingGroupKind")
    .value("RadioTarget", org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct api/SemBaseApi.hpp:162:25 */::RadioTarget)
    .value("Single", org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct api/SemBaseApi.hpp:162:25 */::Single)
    .value("TrackedHashtag", org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct api/SemBaseApi.hpp:162:25 */::TrackedHashtag)
    .def("__iter__", [](org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind const& /*  [1513]enum direct api/SemBaseApi.hpp:162:25 */ _self) -> org::bind::python::PyEnumIterator<org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct api/SemBaseApi.hpp:162:25 */> {
                     return org::bind::python::PyEnumIterator<org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct api/SemBaseApi.hpp:162:25 */>();
                     })
    .def("__int__", [](org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind const& /*  [1513]enum direct api/SemBaseApi.hpp:162:25 */ _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind const& /*  [1513]enum direct api/SemBaseApi.hpp:162:25 */ _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct api/SemBaseApi.hpp:162:25 */ lhs, org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct api/SemBaseApi.hpp:162:25 */ rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::AstTrackingGroup /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct api/SemBaseApi.hpp:162:25 */ it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct imm/ImmOrgGraph.hpp:36:5 */>(m, "GraphMapLinkKind", type_registry_guard);
  nanobind::enum_<org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct imm/ImmOrgGraph.hpp:36:5 */>(m, "GraphMapLinkKind")
    .value("Radio", org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct imm/ImmOrgGraph.hpp:36:5 */::Radio)
    .value("Link", org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct imm/ImmOrgGraph.hpp:36:5 */::Link)
    .def("__iter__", [](org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind const& /*  [1513]enum direct imm/ImmOrgGraph.hpp:36:5 */ _self) -> org::bind::python::PyEnumIterator<org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct imm/ImmOrgGraph.hpp:36:5 */> {
                     return org::bind::python::PyEnumIterator<org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct imm/ImmOrgGraph.hpp:36:5 */>();
                     })
    .def("__int__", [](org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind const& /*  [1513]enum direct imm/ImmOrgGraph.hpp:36:5 */ _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind const& /*  [1513]enum direct imm/ImmOrgGraph.hpp:36:5 */ _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct imm/ImmOrgGraph.hpp:36:5 */ lhs, org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct imm/ImmOrgGraph.hpp:36:5 */ rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::graph /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::MapLink /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [550]type namespace @[0]' */::Kind /*  [1513]enum direct imm/ImmOrgGraph.hpp:36:5 */ it) -> int {
         return static_cast<int>(it);
         })
    ;
  bind_enum_iterator<org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */>(m, "LeafFieldType", type_registry_guard);
  nanobind::enum_<org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */>(m, "LeafFieldType")
    .value("Int", org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */::Int)
    .value("UserTimeKind", org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */::UserTimeKind)
    .value("QDate", org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */::QDate)
    .value("Bool", org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */::Bool)
    .value("FixedIdVec", org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */::FixedIdVec)
    .value("TopIdVec", org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */::TopIdVec)
    .value("QDateTime", org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */::QDateTime)
    .value("Str", org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */::Str)
    .value("Any", org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */::Any)
    .def("__iter__", [](org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType const& /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */ _self) -> org::bind::python::PyEnumIterator<org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */> {
                     return org::bind::python::PyEnumIterator<org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */>();
                     })
    .def("__int__", [](org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType const& /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */ _self) -> int {
                    return static_cast<int>(_self);
                    })
    .def("__index__", [](org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType const& /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */ _self) -> int {
                      return static_cast<int>(_self);
                      })
    .def("__eq__",
         [](org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */ lhs, org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */ rhs) -> bool {
         return lhs == rhs;
         },
         nanobind::arg("rhs"))
    .def("__hash__",
         [](org /*  [485]Apply namespace @[0] from 1517:VisitEnumDecl ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 1517:VisitEnumDecl ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 1517:VisitEnumDecl ' [539]regular type namespaces @[0]' */::LeafFieldType /*  [1513]enum direct pyhaxorg/pyhaxorg_manual_impl.hpp:228:58 */ it) -> int {
         return static_cast<int>(it);
         })
    ;
  m.def("newSemTimeStatic",
        static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Time /*  [640]Type parameter [905]api/SemBaseApi.hpp:12:32( [780] >record 'Time'<>) */> /*  [905]api/SemBaseApi.hpp:12:32( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::UserTimeBreakdown const& /*  [905]api/SemBaseApi.hpp:13:36( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'UserTimeBreakdown'<>)<>) */, bool /*  [905]api/SemBaseApi.hpp:14:36( [755] >bool<>) */)>(&org::newSemTimeStatic),
        nanobind::arg("breakdown"),
        nanobind::arg("isActive") = false);
  m.def("initImmutableAstContext", static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]api/SemBaseApi.hpp:16:46( [780] >record 'ImmAstContext'<>) */> /*  [905]api/SemBaseApi.hpp:16:46( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */(*)()>(&org::initImmutableAstContext));
  m.def("asOneNode",
        static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:25:31( [780] >record 'Org'<>) */> /*  [905]api/SemBaseApi.hpp:25:31( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:26:43( [780] >record 'Org'<>) */> const& /*  [905]api/SemBaseApi.hpp:26:43( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */)>(&org::asOneNode),
        nanobind::arg("arg"));
  m.def("formatToString",
        static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]api/SemBaseApi.hpp:28:22( [735] typedef type bits/stringfwd.h:79:33) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:28:58( [780] >record 'Org'<>) */> /*  [905]api/SemBaseApi.hpp:28:58( [780] >record 'SemId'< [657] templates: template-specialization-type>) */)>(&org::formatToString),
        nanobind::arg("arg"));
  m.def("exportToYamlString",
        static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]api/SemBaseApi.hpp:49:22( [735] typedef type bits/stringfwd.h:79:33) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:50:33( [780] >record 'Org'<>) */> const& /*  [905]api/SemBaseApi.hpp:50:33( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts const& /*  [905]api/SemBaseApi.hpp:51:33( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'OrgYamlExportOpts'<>)<>) */)>(&org::exportToYamlString),
        nanobind::arg("node"),
        nanobind::arg("opts"));
  m.def("exportToYamlFile",
        static_cast<void /*  [905]api/SemBaseApi.hpp:52:15(<>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:53:33( [780] >record 'Org'<>) */> const& /*  [905]api/SemBaseApi.hpp:53:33( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]api/SemBaseApi.hpp:54:33( [735] typedef type bits/stringfwd.h:79:33) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgYamlExportOpts const& /*  [905]api/SemBaseApi.hpp:55:33( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'OrgYamlExportOpts'<>)<>) */)>(&org::exportToYamlFile),
        nanobind::arg("node"),
        nanobind::arg("path"),
        nanobind::arg("opts"));
  m.def("exportToJsonString",
        static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]api/SemBaseApi.hpp:57:22( [735] typedef type bits/stringfwd.h:79:33) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:57:69( [780] >record 'Org'<>) */> const& /*  [905]api/SemBaseApi.hpp:57:69( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */)>(&org::exportToJsonString),
        nanobind::arg("node"));
  m.def("exportToJsonFile",
        static_cast<void /*  [905]api/SemBaseApi.hpp:58:22(<>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:59:40( [780] >record 'Org'<>) */> const& /*  [905]api/SemBaseApi.hpp:59:40( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]api/SemBaseApi.hpp:60:40( [735] typedef type bits/stringfwd.h:79:33) */)>(&org::exportToJsonFile),
        nanobind::arg("node"),
        nanobind::arg("path"));
  m.def("readProtobufFile",
        static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Document /*  [640]Type parameter [905]api/SemBaseApi.hpp:62:36( [780] >record 'Document'<>) */> /*  [905]api/SemBaseApi.hpp:62:36( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/SemBaseApi.hpp:63:24( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */)>(&org::readProtobufFile),
        nanobind::arg("file"));
  m.def("exportToProtobufFile",
        static_cast<void /*  [905]api/SemBaseApi.hpp:65:15(<>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Document /*  [640]Type parameter [905]api/SemBaseApi.hpp:66:31( [780] >record 'Document'<>) */> /*  [905]api/SemBaseApi.hpp:66:31( [780] >record 'SemId'< [657] templates: template-specialization-type>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]api/SemBaseApi.hpp:67:31( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */)>(&org::exportToProtobufFile),
        nanobind::arg("doc"),
        nanobind::arg("file"));
  m.def("exportToTreeString",
        static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]api/SemBaseApi.hpp:92:22( [735] typedef type bits/stringfwd.h:79:33) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:93:33( [780] >record 'Org'<>) */> const& /*  [905]api/SemBaseApi.hpp:93:33( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts const& /*  [905]api/SemBaseApi.hpp:94:33( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'OrgTreeExportOpts'<>)<>) */)>(&org::exportToTreeString),
        nanobind::arg("node"),
        nanobind::arg("opts"));
  m.def("exportToTreeFile",
        static_cast<void /*  [905]api/SemBaseApi.hpp:96:15(<>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:97:33( [780] >record 'Org'<>) */> const& /*  [905]api/SemBaseApi.hpp:97:33( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'SemId'< [657] templates: template-specialization-type>)<>) */, std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]api/SemBaseApi.hpp:98:33( [735] typedef type bits/stringfwd.h:79:33) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgTreeExportOpts const& /*  [905]api/SemBaseApi.hpp:99:33( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'OrgTreeExportOpts'<>)<>) */)>(&org::exportToTreeFile),
        nanobind::arg("node"),
        nanobind::arg("path"),
        nanobind::arg("opts"));
  m.def("getAstTrackingMap",
        static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap /*  [905]api/SemBaseApi.hpp:265:25( [780] >record 'AstTrackingMap'<>) */(*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:266:44( [780] >record 'Org'<>) */> /*  [640]Type parameter [905]api/SemBaseApi.hpp:266:44( [780] >record 'SemId'< [657] templates: template-specialization-type>) */> const& /*  [905]api/SemBaseApi.hpp:266:44( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Vec'< [657] templates: template-specialization-type>)<>) */)>(&org::getAstTrackingMap),
        nanobind::arg("nodes"));
  m.def("getSubnodeGroups",
        static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingGroup /*  [640]Type parameter [905]api/SemBaseApi.hpp:268:38( [780] >record 'AstTrackingGroup'<>) */> /*  [905]api/SemBaseApi.hpp:268:38( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]api/SemBaseApi.hpp:269:27( [780] >record 'Org'<>) */> /*  [905]api/SemBaseApi.hpp:269:27( [780] >record 'SemId'< [657] templates: template-specialization-type>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::AstTrackingMap const& /*  [905]api/SemBaseApi.hpp:270:27( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'AstTrackingMap'<>)<>) */)>(&org::getSubnodeGroups),
        nanobind::arg("node"),
        nanobind::arg("map"));
  m.def("annotateSequence",
        static_cast<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceAnnotation /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:93:34( [780] >record 'SequenceAnnotation'<>) */> /*  [905]stdlib/RangeSegmentation.hpp:93:34( [780] >record 'Vec'< [657] templates: template-specialization-type>) */(*)(hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Vec<hstd /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SequenceSegmentGroup /*  [640]Type parameter [905]stdlib/RangeSegmentation.hpp:94:38( [780] >record 'SequenceSegmentGroup'<>) */> const& /*  [905]stdlib/RangeSegmentation.hpp:94:38( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'Vec'< [657] templates: template-specialization-type>)<>) */, int /*  [905]stdlib/RangeSegmentation.hpp:95:38( [766] >builtin/unqual<>) */, int /*  [905]stdlib/RangeSegmentation.hpp:96:38( [766] >builtin/unqual<>) */)>(&hstd::annotateSequence),
        nanobind::arg("groups"),
        nanobind::arg("first"),
        nanobind::arg("last"));
  m.def("initMapGraphState",
        static_cast<std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraphState /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:441:41( [780] >record 'MapGraphState'<>) */> /*  [905]imm/ImmOrgGraph.hpp:441:41( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */(*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]imm/ImmOrgGraph.hpp:442:46( [780] >record 'ImmAstContext'<>) */> /*  [905]imm/ImmOrgGraph.hpp:442:46( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */)>(&org /*  [539]regular type namespaces @[1] */::graph::initMapGraphState),
        nanobind::arg("ast"));
  m.def("serializeToText",
        static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]serde/SemOrgCereal.hpp:7:73( [735] typedef type bits/stringfwd.h:79:33) */(*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]serde/SemOrgCereal.hpp:8:43( [780] >record 'ImmAstContext'<>) */> const& /*  [905]serde/SemOrgCereal.hpp:8:43( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[1] */::imm::serializeToText),
        nanobind::arg("store"));
  m.def("serializeFromText",
        static_cast<void /*  [905]serde/SemOrgCereal.hpp:9:68(<>) */(*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]serde/SemOrgCereal.hpp:10:43( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]serde/SemOrgCereal.hpp:11:43( [780] >record 'ImmAstContext'<>) */> const& /*  [905]serde/SemOrgCereal.hpp:11:43( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[1] */::imm::serializeFromText),
        nanobind::arg("binary"),
        nanobind::arg("store"));
  m.def("serializeToText",
        static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]serde/SemOrgCereal.hpp:13:71( [735] typedef type bits/stringfwd.h:79:33) */(*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstReplaceEpoch /*  [640]Type parameter [905]serde/SemOrgCereal.hpp:14:48( [780] >record 'ImmAstReplaceEpoch'<>) */> const& /*  [905]serde/SemOrgCereal.hpp:14:48( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[1] */::imm::serializeToText),
        nanobind::arg("store"));
  m.def("serializeFromText",
        static_cast<void /*  [905]serde/SemOrgCereal.hpp:15:66(<>) */(*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]serde/SemOrgCereal.hpp:16:48( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstReplaceEpoch /*  [640]Type parameter [905]serde/SemOrgCereal.hpp:17:48( [780] >record 'ImmAstReplaceEpoch'<>) */> const& /*  [905]serde/SemOrgCereal.hpp:17:48( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[1] */::imm::serializeFromText),
        nanobind::arg("binary"),
        nanobind::arg("store"));
  m.def("serializeToText",
        static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]serde/SemOrgCereal.hpp:19:71( [735] typedef type bits/stringfwd.h:79:33) */(*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [640]Type parameter [905]serde/SemOrgCereal.hpp:20:50( [780] >record 'MapGraph'<>) */> const& /*  [905]serde/SemOrgCereal.hpp:20:50( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[1] */::imm::serializeToText),
        nanobind::arg("store"));
  m.def("serializeFromText",
        static_cast<void /*  [905]serde/SemOrgCereal.hpp:21:66(<>) */(*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]serde/SemOrgCereal.hpp:22:50( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [640]Type parameter [905]serde/SemOrgCereal.hpp:23:50( [780] >record 'MapGraph'<>) */> const& /*  [905]serde/SemOrgCereal.hpp:23:50( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[1] */::imm::serializeFromText),
        nanobind::arg("binary"),
        nanobind::arg("store"));
  m.def("serializeFromTextToTreeDump",
        static_cast<std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string /*  [905]serde/SemOrgCereal.hpp:27:22( [735] typedef type bits/stringfwd.h:79:33) */(*)(std /*  [485]Apply namespace @[0] from 741:fillTypeRec ' [539]regular type namespaces @[0]' */::string const& /*  [905]serde/SemOrgCereal.hpp:28:24( [745] T-reference [752] >ref/ptr( [707] T-const [735] typedef type bits/stringfwd.h:79:33)<>) */)>(&org /*  [539]regular type namespaces @[1] */::imm::serializeFromTextToTreeDump),
        nanobind::arg("binary"));
  m.def("eachSubnodeRec",
        static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:123:66(<>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]pyhaxorg/pyhaxorg_manual_impl.hpp:124:36( [780] >record 'Org'<>) */> /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:124:36( [780] >record 'SemId'< [657] templates: template-specialization-type>) */, nanobind /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::callable /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:125:36( [780] >record 'callable'<>) */)>(&org /*  [539]regular type namespaces @[2] */::bind /*  [539]regular type namespaces @[1] */::python::eachSubnodeRec),
        nanobind::arg("node"),
        nanobind::arg("callback"));
  m.def("eachSubnodeRecSimplePath",
        static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:127:66(<>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]pyhaxorg/pyhaxorg_manual_impl.hpp:128:36( [780] >record 'Org'<>) */> /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:128:36( [780] >record 'SemId'< [657] templates: template-specialization-type>) */, nanobind /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::callable /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:129:36( [780] >record 'callable'<>) */)>(&org /*  [539]regular type namespaces @[2] */::bind /*  [539]regular type namespaces @[1] */::python::eachSubnodeRecSimplePath),
        nanobind::arg("node"),
        nanobind::arg("callback"));
  m.def("setShouldProcessPath",
        static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:144:66(<>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgDirectoryParseParameters* /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:145:46( [712] T-pointer [752] >ref/ptr( [780] >record 'OrgDirectoryParseParameters'<>)<>) */, nanobind /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::callable /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:146:46( [780] >record 'callable'<>) */)>(&org /*  [539]regular type namespaces @[2] */::bind /*  [539]regular type namespaces @[1] */::python::setShouldProcessPath),
        nanobind::arg("parameters"),
        nanobind::arg("callback"));
  m.def("serializeAstContextToText",
        static_cast<nanobind /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::bytes /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:156:5( [780] >record 'bytes'<>) */(*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]pyhaxorg/pyhaxorg_manual_impl.hpp:157:52( [780] >record 'ImmAstContext'<>) */> const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:157:52( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[2] */::bind /*  [539]regular type namespaces @[1] */::python::serializeAstContextToText),
        nanobind::arg("store"));
  m.def("serializeAstContextFromText",
        static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:167:5(<>) */(*)(nanobind /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::bytes const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:168:52( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'bytes'<>)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstContext /*  [640]Type parameter [905]pyhaxorg/pyhaxorg_manual_impl.hpp:169:52( [780] >record 'ImmAstContext'<>) */> const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:169:52( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[2] */::bind /*  [539]regular type namespaces @[1] */::python::serializeAstContextFromText),
        nanobind::arg("binary"),
        nanobind::arg("store"));
  m.def("serializeAstReplaceEpochToText",
        static_cast<nanobind /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::bytes /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:179:5( [780] >record 'bytes'<>) */(*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstReplaceEpoch /*  [640]Type parameter [905]pyhaxorg/pyhaxorg_manual_impl.hpp:180:57( [780] >record 'ImmAstReplaceEpoch'<>) */> const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:180:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[2] */::bind /*  [539]regular type namespaces @[1] */::python::serializeAstReplaceEpochToText),
        nanobind::arg("store"));
  m.def("serializeAstReplaceEpochFromText",
        static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:190:5(<>) */(*)(nanobind /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::bytes const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:191:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'bytes'<>)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::imm /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ImmAstReplaceEpoch /*  [640]Type parameter [905]pyhaxorg/pyhaxorg_manual_impl.hpp:192:57( [780] >record 'ImmAstReplaceEpoch'<>) */> const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:192:57( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[2] */::bind /*  [539]regular type namespaces @[1] */::python::serializeAstReplaceEpochFromText),
        nanobind::arg("binary"),
        nanobind::arg("store"));
  m.def("serializeMapGraphFromText",
        static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:202:5(<>) */(*)(nanobind /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::bytes const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:203:54( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'bytes'<>)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [640]Type parameter [905]pyhaxorg/pyhaxorg_manual_impl.hpp:204:54( [780] >record 'MapGraph'<>) */> const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:204:54( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[2] */::bind /*  [539]regular type namespaces @[1] */::python::serializeMapGraphFromText),
        nanobind::arg("binary"),
        nanobind::arg("store"));
  m.def("serializeMapGraphToText",
        static_cast<nanobind /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::bytes /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:214:5( [780] >record 'bytes'<>) */(*)(std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::graph /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::MapGraph /*  [640]Type parameter [905]pyhaxorg/pyhaxorg_manual_impl.hpp:215:54( [780] >record 'MapGraph'<>) */> const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:215:54( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'shared_ptr'< [657] templates: template-specialization-type>)<>) */)>(&org /*  [539]regular type namespaces @[2] */::bind /*  [539]regular type namespaces @[1] */::python::serializeMapGraphToText),
        nanobind::arg("store"));
  m.def("setGetParsedNode",
        static_cast<void /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:218:66(<>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::OrgDirectoryParseParameters* /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:219:41( [712] T-pointer [752] >ref/ptr( [780] >record 'OrgDirectoryParseParameters'<>)<>) */, nanobind /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::callable /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:220:41( [780] >record 'callable'<>) */)>(&org /*  [539]regular type namespaces @[2] */::bind /*  [539]regular type namespaces @[1] */::python::setGetParsedNode),
        nanobind::arg("params"),
        nanobind::arg("callback"));
  m.def("evaluateCodeBlocks",
        static_cast<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]pyhaxorg/pyhaxorg_manual_impl.hpp:222:87( [780] >record 'Org'<>) */> /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:222:87( [780] >record 'SemId'< [657] templates: template-specialization-type>) */(*)(org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::SemId<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::sem /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::Org /*  [640]Type parameter [905]pyhaxorg/pyhaxorg_manual_impl.hpp:223:47( [780] >record 'Org'<>) */> /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:223:47( [780] >record 'SemId'< [657] templates: template-specialization-type>) */, org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[2]' */::bind /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::python /*  [485]Apply namespace @[2] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::PyCodeEvalParameters const& /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:224:47( [745] T-reference [752] >ref/ptr( [707] T-const [780] >record 'PyCodeEvalParameters'<>)<>) */, std /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::shared_ptr<org /*  [485]Apply namespace @[0] from 776:fillTypeRec ' [539]regular type namespaces @[1]' */::parse /*  [485]Apply namespace @[1] from 776:fillTypeRec ' [539]regular type namespaces @[0]' */::ParseContext /*  [640]Type parameter [905]pyhaxorg/pyhaxorg_manual_impl.hpp:225:47( [780] >record 'ParseContext'<>) */> /*  [905]pyhaxorg/pyhaxorg_manual_impl.hpp:225:47( [780] >record 'shared_ptr'< [657] templates: template-specialization-type>) */)>(&org /*  [539]regular type namespaces @[2] */::bind /*  [539]regular type namespaces @[1] */::python::evaluateCodeBlocks),
        nanobind::arg("node"),
        nanobind::arg("conf"),
        nanobind::arg("parse_context"));
  nanobind::set_leak_warnings(false);
}
/* clang-format on */