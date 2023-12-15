#include "base_token.hpp"

#include <reflex/abslexer.h>
#include <reflex/matcher.h>

#include "base_token_state.tcc"

void BaseLexerImpl::add(BaseTokenKind token) {
    (void)tokens.add(BaseToken{
        token,
        BaseFill{
            impl->matcher().str(),
            static_cast<int>(impl->lineno()),
            static_cast<int>(impl->columno()),
        }});
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
    states.pop_back();
    if (!states.empty()) {
        CHECK(states.back().stateId == next);
    }

    //    std::cout << std::format(
    //        "Move {} -> {} at {} with {}",
    //        state_name(current),
    //        state_name(next),
    //        line,
    //        view())
    //              << std::endl;
}

void BaseLexerImpl::push_expect_impl(int current, int next, int line) {
    CHECK(impl->start() == current) << std::format(
        "Expected current state to be {} at {} but got {} when "
        "transitioning to {} at '{}'",
        state_name(current),
        line,
        state_name(impl->start()),
        state_name(next),
        view());
    impl->push_state(next);
    states.push_back(PushInfo{
        .stateId = next,
        .line    = static_cast<int>(impl->lineno()),
        .column  = static_cast<int>(impl->columno()),
        .matched = impl->str(),
    });

    //    std::cout << std::format(
    //        "Move {} -> {} at {} with {}",
    //        state_name(current),
    //        state_name(next),
    //        line,
    //        view())
    //              << std::endl;
}

void BaseLexerImpl::before(int line) {
    //    std::cout << "Trigger line " << line << " -- " << view() << "\n";
}

void BaseLexerImpl::after(int line) {
    //    std::cout << std::format(
    //        "End line trigger {} in state {}\n",
    //        line,
    //        state_name(impl->start()));
}

std::string BaseLexerImpl::view() {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    std::string    text      = impl->matcher().str();
    std::u32string utf32_str = conv.from_bytes(text);
    char32_t       codepoint = utf32_str[0];
    std::string    span      = std::string(impl->matcher().span());
    std::string    states;

    for (PushInfo const& state : this->states) {
        states += std::format(
            " <'{}':{}:{}:{}>",
            state.matched,
            state_name(state.stateId),
            state.line,
            state.column);
    }

    return "";
#warning FIXME FIX TOKEN
    // return std::format(
    //     "{}:{} in state {} ({}) >{}< (code {}) span: '{}', states:{}",
    //     impl->lineno(),
    //     impl->columno(),
    //     state_name(impl->start()),
    //     impl->start(),
    //     escape_for_write(text),
    //     (uint32_t)codepoint,
    //     escape_for_write(
    //         span.substr(impl->columno(), span.length() - 1), false),
    //     states);
}

void BaseLexerImpl::unknown() {
    std::cerr << "Unknown " << view() << std::endl;
    CHECK(++visitedUnknown < maxUnknown)
        << std::format("Max {} visited {}", maxUnknown, visitedUnknown);
}
