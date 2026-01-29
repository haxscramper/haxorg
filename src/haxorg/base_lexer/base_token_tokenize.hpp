#pragma once

#include <haxorg/base_lexer/base_token.hpp>
#include <haxorg/lexbase/TokenStore.hpp>

namespace org::parse {
using OrgTokenGroup = TokenGroup<OrgTokenKind, OrgFill>;

struct LexerParams : hstd::OperationsTracer {};


OrgTokenGroup tokenize(
    std::string const&              text,
    LexerParams const&              params,
    org::parse::SourceFileId const& file_id);


} // namespace org::parse
