#include "base_token.hpp"

#include <reflex/abslexer.h>
#include <reflex/matcher.h>

#include "base_token_state.tcc"

void BaseLexerImpl::add(BaseTokenKind token) {
    auto id = tokens.add(BaseToken{
        token,
        BaseFill{
            impl->matcher().str(),
            static_cast<int>(impl->lineno()),
            static_cast<int>(impl->columno()),
        }});

    if (traceStream) {
        (*traceStream) << std::format(
            "  [{:0>4}] = {} {}",
            id.getIndex(),
            token,
            escape_for_write(impl->matcher().str()))
                       << std::endl;
    }
}


void BaseLexerImpl::pop_expect_impl(int current, int next, int line) {
    if (current != -1) {
        CHECK(impl->start() == current) << std::format(
            "Expected current state to be {} line:{} but got {} '{}'",
            state_name(current),
            line,
            state_name(impl->start()),
            view());
    }

    impl->pop_state();

    CHECK(impl->start() == next) << std::format(
        "After popping {} expected next state to be {} line:{} but got "
        "{} '{}'",
        state_name(current),
        state_name(next),
        line,
        state_name(impl->start()),
        view());

    states.pop_back();
    if (!states.empty()) { CHECK(states.back().stateId == next); }

    if (traceStream) {

        (*traceStream) << std::format(
            "  - {} -> {} at {} with {}",
            state_name(current),
            state_name(next),
            line,
            view()) << std::endl;
    }
}

void BaseLexerImpl::push_expect_impl(int current, int next, int line) {
    CHECK(impl->start() == current) << std::format(
        "Expected current state to be {} line:{} but got {} when "
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
        .rule    = line,
    });

    if (traceStream) {
        (*traceStream) << std::format(
            "  + {} -> {} at {} with {}",
            state_name(current),
            state_name(next),
            line,
            view()) << std::endl;
    }
}

void BaseLexerImpl::before(
    int           line,
    BaseTokenKind kind,
    const char*   pattern) {
    if (traceStream) {
        (*traceStream) << std::format(
            "> {:>4}   {} {}", line, escape_for_write(pattern), view())
                       << std::endl;
    }
}

void BaseLexerImpl::after(int line) {
    // if (traceStream) {
    //     (*traceStream) << std::format(
    //         "< {} state {}", line, state_name(impl->start()))
    //                    << std::endl;
    // }
}

std::string BaseLexerImpl::view() {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    std::string    text      = impl->matcher().str();
    std::u32string utf32_str = conv.from_bytes(text);
    char32_t       codepoint = utf32_str[0];
    std::string    states;
    std::string    line = impl->matcher().line();

    for (PushInfo const& state : this->states) {
        states += std::format(
            " <'{}':{}:{}:{}:RULE{}>",
            state.matched,
            state_name(state.stateId),
            state.line,
            state.column,
            state.rule);
    }

    return std::format(
        "{}:{} {} ({}) {} (INT:{}) {} {}",
        impl->lineno(),
        impl->columno(),
        state_name(impl->start()),
        impl->start(),
        escape_for_write(text).toBase(),
        (uint32_t)codepoint,
        escape_for_write(line.substr(impl->columno(), line.length() - 1)),
        states);
}

void BaseLexerImpl::unknown() {
    if (traceStream) {
        (*traceStream) << "  X unknown " << view() << std::endl;
    } else {
        LOG(ERROR) << "Unknown " << view();
    }

    CHECK(++visitedUnknown < maxUnknown)
        << std::format("Max {} visited {}", maxUnknown, visitedUnknown);
}
