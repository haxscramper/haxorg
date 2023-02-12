#pragma once

#include <sem/SemOrg.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <parse/OrgParser.hpp>

UPtr<sem::Table>   convertTable(sem::Org* parent, OrgAdapter adapter);
UPtr<sem::HashTag> convertHashTag(sem::Org* parent, OrgAdapter adapter);
