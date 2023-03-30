#pragma once

#include <lexbase/AstSpec.hpp>
#include <parse/OrgTypes.hpp>

using OrgSpec = astspec::AstSpec<OrgAdapter, OrgNodeKind, Str>;

extern OrgSpec spec;
