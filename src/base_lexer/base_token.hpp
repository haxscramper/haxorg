#pragma once

import std;
import std;
import std;
import org.lexbase.Token;
import std.system.reflection;


#include "base_token_kind.hpp"

namespace reflex {
class Matcher;
template <typename T>
class AbstractLexer;
}; // namespace reflex

template <>
struct enum_serde<BaseTokenKind> {
    static std::string to_string(BaseTokenKind const& value);
};


template <>
struct std::formatter<BaseTokenKind> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        BaseTokenKind const& p,
        FormatContext&       ctx) const {
        std::formatter<std::string> fmt;
        return fmt.format(enum_serde<BaseTokenKind>::to_string(p), ctx);
    }
};

struct BaseFill {
    Str text;
    int line;
    int col;
};

using BaseToken      = Token<BaseTokenKind, BaseFill>;
using BaseTokenGroup = TokenGroup<BaseTokenKind, BaseFill>;
using BaseTokenId    = TokenId<BaseTokenKind, BaseFill>;

template <>
struct value_domain<BaseTokenKind>
    : public value_domain_ungapped<
          BaseTokenKind,
          BaseTokenKind::Ampersand,
          BaseTokenKind::Word> {};

template <>
struct std::formatter<BaseFill> : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(BaseFill const& p, FormatContext& ctx)
        const {
        fmt_ctx("<", ctx);
        fmt_ctx(escape_for_write(p.text), ctx);
        fmt_ctx(">:", ctx);
        fmt_ctx(p.line, ctx);
        fmt_ctx(":", ctx);
        fmt_ctx(p.col, ctx);
        return ctx.out();
    }
};


BaseTokenGroup tokenize(const char* input, int size);


struct BaseLexerImpl {
    reflex::AbstractLexer<reflex::Matcher>* impl;
    int                                     maxUnknown     = 20;
    int                                     visitedUnknown = 0;
    struct PushInfo {
        int         stateId;
        int         line;
        int         column;
        std::string matched;
    };

    Vec<PushInfo> states;

    BaseTokenGroup tokens;
    void           add(BaseTokenKind token);
    std::string    state_name(int name);
    std::string    view();
    void           unknown();

    void pop_expect_impl(int current, int next, int line);
    void push_expect_impl(int current, int next, int line);
    void before(int line);
    void after(int line);
};
