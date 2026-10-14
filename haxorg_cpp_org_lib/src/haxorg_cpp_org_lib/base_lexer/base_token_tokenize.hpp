#pragma once

#include <haxorg_cpp_org_lib/base_lexer/base_token.hpp>
#include <haxorg_cpp_org_lib/lexbase/TokenStore.hpp>
#include <hstd_cpp_lib/logger/TraceBase.hpp>

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
