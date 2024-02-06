#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <lexbase/Token.hpp>
#include <hstd/system/reflection.hpp>


#include "base_token_kind.hpp"

namespace reflex {
class Matcher;
template <typename T>
class AbstractLexer;
}; // namespace reflex

template <>
struct enum_serde<OrgTokenKind> {
    static std::string       to_string(OrgTokenKind const& value);
    static Opt<OrgTokenKind> from_string(std::string const& value);
};


template <>
struct std::formatter<OrgTokenKind> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        OrgTokenKind const& p,
        FormatContext&      ctx) const {
        std::formatter<std::string> fmt;
        return fmt.format(enum_serde<OrgTokenKind>::to_string(p), ctx);
    }
};

struct OrgFill {
    Str  text;
    int  line = -1;
    int  col  = -1;
    bool isFake() const { return line == -1 && col == -1; }
};

using OrgToken      = Token<OrgTokenKind, OrgFill>;
using OrgTokenGroup = TokenGroup<OrgTokenKind, OrgFill>;
using OrgTokenId    = TokenId<OrgTokenKind, OrgFill>;

template <>
struct value_domain<OrgTokenKind>
    : public value_domain_ungapped<
          OrgTokenKind,
          OrgTokenKind::Ampersand,
          OrgTokenKind::Word> {};

template <>
struct std::formatter<OrgFill> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(OrgFill const& p, FormatContext& ctx)
        const {
        std::formatter<std::string>{}.format("<", ctx);
        fmt_ctx(escape_for_write(p.text), ctx);
        std::formatter<std::string>{}.format(">:", ctx);
        fmt_ctx(p.line, ctx);
        std::formatter<std::string>{}.format(":", ctx);
        fmt_ctx(p.col, ctx);
        return ctx.out();
    }
};

struct LexerParams {
    int           maxUnknown     = 100;
    int           visitedUnknown = 0;
    std::ostream* traceStream    = nullptr;
    int           indentation    = 0;
};


OrgTokenGroup tokenize(const char* input, int size, LexerParams const& p);


struct OrgLexerImpl {
    reflex::AbstractLexer<reflex::Matcher>* impl;
    LexerParams                             p;

    struct PushInfo {
        int         stateId; /// Name of the state pushed into stack
        int         line;    /// Line in the source where state triggered
        int         column;  /// code column
        int         rule;    /// Line in the rule file
        std::string matched; /// matched text content
    };

    Vec<PushInfo> states;

    OrgTokenGroup* tokens;
    void           add(OrgTokenKind token);
    std::string    state_name(int name);
    std::string    view();
    void           unknown();

    void maybe_pop_expect_impl(int current, int next, int line);
    void pop_expect_impl(int current, int next, int line);
    void push_expect_impl(int current, int next, int line);
    void before(int line, OrgTokenKind kind, char const* pattern);
    void after(int line);
};
