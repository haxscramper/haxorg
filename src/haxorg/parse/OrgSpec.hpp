#pragma once

#include <haxorg/lexbase/AstSpec.hpp>
#include <haxorg/parse/OrgTypes.hpp>
#include <haxorg/parse/OrgParserTypes.hpp>


using OrgSpec = org::parse::
    AstSpec<org::parse::OrgAdapter, OrgNodeKind, OrgSpecName>;

std::unique_ptr<OrgSpec> getOrgSpec();
