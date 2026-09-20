#pragma once

#include <haxorg/base_lexer/base_token.hpp>
#include <haxorg/lexbase/TokenStore.hpp>
#include <hstd/logger/TraceBase.hpp>

namespace org::parse {
using OrgTokenGroup = TokenGroup<OrgTokenKind, OrgFill>;

struct LexerParams : hstd::OperationsTracer {
    bool validateTokens = false;
};


OrgTokenGroup tokenize(
    std::string const&              text [[clang::lifetimebound]],
    LexerParams const&              params,
    org::parse::SourceFileId const& file_id);


} // namespace org::parse
