#include "base_token.hpp"

#include <reflex/abslexer.h>
#include <reflex/matcher.h>

#include "base_token_state.tcc"

void BaseLexerImpl::add(BaseTokenKind token) {
    tokens.emplace_back(BaseToken{
        token,
        BaseFill{
            impl->matcher().text(), impl->lineno(), impl->columno()}});
}


void BaseLexerImpl::pop_expect_impl(int current, int next, int line) {
    CHECK(impl->start() == current) << std::format(
        "Expected current state to be {} at {} but got {} '{}'",
        state_name(current),
        line,
        state_name(impl->start()),
        view());

    impl->pop_state();
    CHECK(impl->start() == next) << std::format(
        "After popping {} expected next state to be {} at {} but got "
        "{} '{}'",
        state_name(current),
        state_name(next),
        line,
        state_name(impl->start()),
        view());
}

std::string BaseLexerImpl::view() {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    std::u32string utf32_str = conv.from_bytes(impl->matcher().text());
    char32_t       codepoint = utf32_str[0];
    return std::format(
        "{}:{} in state {} ({}) >{}< (code {}) span: '{}'",
        impl->lineno(),
        impl->columno(),
        state_name(impl->top_state()),
        impl->top_state(),
        impl->matcher().text(),
        (uint32_t)codepoint,
        impl->matcher().span());
}

void BaseLexerImpl::unknown() { std::cerr << view() << "\n"; }

