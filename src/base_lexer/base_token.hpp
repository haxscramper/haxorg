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
struct enum_serde<BaseTokenKind> {
    static std::string to_string(BaseTokenKind const& value);
};


struct BaseFill {
    std::string text;
    int         line;
    int         col;
};

using BaseToken = Token<BaseTokenKind, BaseFill>;

std::vector<BaseToken> tokenize(const char* input, int size);


struct BaseLexerImpl {
    reflex::AbstractLexer<reflex::Matcher>* impl;
    int                                     maxUnknown     = 20;
    int                                     visitedUnknown = 0;

    std::vector<BaseToken> tokens;
    void                   add(BaseTokenKind token);
    std::string            state_name(int name);
    std::string            view();
    void                   unknown();

    void pop_expect_impl(int current, int next, int line);
    void push_expect_impl(int current, int next, int line);
    void before(int line);
    void after(int line);
};
