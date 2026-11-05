#pragma once

#include <haxorg_cpp_org_lib/lexbase/AstSpec.hpp>
#include <haxorg_cpp_org_lib/parse/OrgParserTypes.hpp>
#include <haxorg_cpp_org_lib/parse/OrgTypes.hpp>


using OrgSpec = org::parse::
    AstSpec<org::parse::OrgAdapter, org::sem::OrgNodeKind, org::sem::OrgSpecName>;

std::unique_ptr<OrgSpec> getOrgSpec();
