#pragma once

#include <hstd/stdlib/dod_base.hpp>

#include <lexbase/Token.hpp>
#include <lexbase/TokenGroup.hpp>
#include <types/enums.hpp>
#include <types/enum_repr.hpp>

using OrgToken      = Token<OrgTokenKind>;
using OrgTokenId    = TokenId<OrgTokenKind>;
using OrgTokenStore = TokenStore<OrgTokenKind>;
using OrgTokenGroup = TokenGroup<OrgTokenKind>;
