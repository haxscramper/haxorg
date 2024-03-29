#include "base_token.hpp"

#include <reflex/abslexer.h>
#include <reflex/matcher.h>

#include "base_token_state.tcc"

void OrgLexerImpl::add(OrgTokenKind token) {
    using Loc   = LexerParams::Loc;
    Loc sub_loc = rs::fold_left(
        p.sub_locations, Loc{}, [](CR<Loc> l, CR<Loc> r) -> Loc {
            return {l.line + r.line, l.col + r.col};
        });

    auto id = tokens->add(OrgToken{
        token,
        OrgFill{
            impl->matcher().str(),
            static_cast<int>(impl->lineno() + sub_loc.line),
            static_cast<int>(impl->columno() + sub_loc.col),
        }});

    if (p.traceStream) {
        (*p.traceStream) << std::format(
            "{}   {:0>4}] = {} {}",
            get_print_indent(),
            id.getIndex(),
            token,
            escape_for_write(impl->matcher().str()))
                         << std::endl;
    }
}

void OrgLexerImpl::maybe_pop_expect_impl(int current, int next, int line) {
    if (impl->start() == current) { pop_expect_impl(current, next, line); }
}

void OrgLexerImpl::pop_expect_impl(int current, int next, int line) {
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

    if (p.traceStream) {
        (*p.traceStream) << std::format(
            "{}         - {} -> {} at {} with {}",
            get_print_indent(),
            state_name(current),
            state_name(next),
            line,
            view()) << std::endl;
    }
}

void OrgLexerImpl::push_expect_impl(int current, int next, int line) {
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

    if (p.traceStream) {
        (*p.traceStream) << std::format(
            "{}         + {} -> {} at {} with {}",
            get_print_indent(),
            state_name(current),
            state_name(next),
            line,
            view()) << std::endl;
    }
}

void OrgLexerImpl::before(
    int               line,
    Opt<OrgTokenKind> kind,
    const char*       pattern) {
    if (p.traceStream) {
        (*p.traceStream) << std::format(
            "{}>  {:0>4}]   {} {}",
            get_print_indent(),
            line,
            escape_for_write(pattern),
            view()) << std::endl;
    }
}

void OrgLexerImpl::after(int line) {
    // if (traceStream) {
    //     (*traceStream) << std::format(
    //         "< {} state {}", line, state_name(impl->start()))
    //                    << std::endl;
    // }
}

std::pair<const char*, size_t> OrgLexerImpl::get_capture(
    const char* name) {
    std::pair<size_t, const char*> id = impl->matcher().group_id();
    while (id.first != 0
           && (id.second == NULL || strcmp(id.second, name) != 0)) {
        id = impl->matcher().group_next_id();
    }

    if (id.first != 0) {
        return impl->matcher()[id.first];
    } else {
        LOG(FATAL) << "??? " << name;
    }
}

std::string OrgLexerImpl::view() {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    std::string    text      = impl->matcher().str();
    std::u32string utf32_str = conv.from_bytes(text);
    char32_t       codepoint = utf32_str[0];
    std::string    states;
    std::string    line = impl->matcher().line();

    for (PushInfo const& state : this->states) {
        states += std::format(
            " <{}:{}:{}:{}:RULE{}>",
            escape_for_write(state.matched),
            state_name(state.stateId),
            state.line,
            state.column,
            state.rule);
    }

    return std::format(
        "{}:{} (orig:{}) {} (ST:{}) {} (INT:{}) {} {}",
        impl->lineno(),
        impl->columno(),
        p.sub_locations | rv::transform([](auto it) {
            return fmt("{}:{}", it.line, it.col);
        }) | rs::to<std::vector>(),
        state_name(impl->start()),
        impl->start(),
        escape_for_write(text).toBase(),
        (uint32_t)codepoint,
        escape_for_write(line.substr(impl->columno(), line.length() - 1)),
        states);
}

void OrgLexerImpl::unknown() {
    if (p.traceStream) {
        (*p.traceStream) << get_print_indent() << "  X unknown " << view()
                         << std::endl;
    } else {
        LOG(ERROR) << "Unknown " << view();
    }

    CHECK(++p.visitedUnknown < p.maxUnknown) << std::format(
        "Max {} visited {}", p.maxUnknown, p.visitedUnknown);
}

std::string OrgLexerImpl::get_print_indent() const {
    return std::string(p.indentation * 3, ' ');
}
