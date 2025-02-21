#pragma once

#include <haxorg/lexbase/AstSpec.hpp>
#include <haxorg/parse/OrgTypes.hpp>


using OrgSpec = hstd::ext::astspec::
    AstSpec<org::parse::OrgAdapter, OrgNodeKind, OrgSpecName>;

std::unique_ptr<OrgSpec> getOrgSpec();
