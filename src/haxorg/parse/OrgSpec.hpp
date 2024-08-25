#pragma once

#include <haxorg/lexbase/AstSpec.hpp>
#include <haxorg/parse/OrgTypes.hpp>


using OrgSpec = astspec::AstSpec<OrgAdapter, OrgNodeKind, OrgSpecName>;

std::unique_ptr<OrgSpec> getOrgSpec();
