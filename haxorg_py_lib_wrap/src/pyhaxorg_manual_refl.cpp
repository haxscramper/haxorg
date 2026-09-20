#include "pyhaxorg_manual_impl.hpp"
#include <haxorg_cpp_org_lib/serde/SemOrgSerde.hpp>

#include <datetime.h>
#include <fstream>
#include <haxorg_cpp_org_lib/exporters/ExporterJson.hpp>
#include <haxorg_cpp_org_lib/exporters/exportertree.hpp>
#include <haxorg_cpp_org_lib/exporters/exporteryaml.hpp>
#include <haxorg_cpp_org_lib/imm/ImmOrg.hpp>
#include <haxorg_cpp_org_lib/imm/ImmOrgGraph.hpp>
#include <haxorg_cpp_org_lib/sem/SemOrgFormat.hpp>
#include <hstd_cpp_lib/stdlib/Filesystem.hpp>
#include <hstd_cpp_lib/stdlib/RangeSegmentation.hpp>

#include <memory>

#include <haxorg_cpp_org_lib/exporters/Exporter.cpp>
#include <haxorg_cpp_org_lib/sem/perfetto_org.hpp>

// #ifdef HAXORG_IMM_ORG_ADAPTER_GENERATED_INCLUDED
// #error HAXORG_IMM_ORG_ADAPTER_GENERATED_INCLUDED -- auto-generated adapter file is included in the reflection processing. This causes cyclic dependency loop -- inspect all the headers to ensure that `#include <haxorg_cpp_org_lib/imm/ImmOrgAdapter.hpp>` is not used in this translation unit, directly or transitively.
// #endif
