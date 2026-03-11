#include "pyhaxorg_manual_impl.hpp"
#include <haxorg/serde/SemOrgSerde.hpp>

#include <haxorg/sem/SemOrgFormat.hpp>
#include <haxorg/imm/ImmOrg.hpp>
#include <haxorg/imm/ImmOrgGraph.hpp>
#include <haxorg/exporters/ExporterJson.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/RangeSegmentation.hpp>
#include <haxorg/exporters/exporteryaml.hpp>
#include <haxorg/exporters/exportertree.hpp>
#include <datetime.h>
#include <fstream>

#include <memory>

#include <haxorg/exporters/Exporter.cpp>
#include <haxorg/sem/perfetto_org.hpp>
#include <haxorg/serde/SemOrgCereal.hpp>

#ifdef HAXORG_IMM_ORG_ADAPTER_GENERATED_INCLUDED
#error HAXORG_IMM_ORG_ADAPTER_GENERATED_INCLUDED -- auto-generated adapter file is included in the reflection processing. This causes cyclic dependency loop -- inspect all the headers to ensure that `#include <haxorg/imm/ImmOrgAdapter.hpp>` is not used in this translation unit, directly or transitively.
#endif
