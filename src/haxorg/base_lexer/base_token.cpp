#include "base_token.hpp"

#include <reflex/abslexer.h>
#include <reflex/matcher.h>

using namespace hstd;
using namespace org::parse;

#include "base_token_state.tcc"
#include <haxorg/lexbase/TraceStructured.hpp>

using namespace org::report;

namespace {
EntryLexer::View viewStruct(OrgLexerImpl* lex) {
    EntryLexer::View res;

    res.line   = lex->impl->lineno();
    res.column = lex->impl->columno();
    res.state  = lex->state_name(lex->impl->start());

    for (OrgLexerImpl::PushInfo const& state : lex->states) {
        res.states.push_back(EntryLexer::State{
            .column  = state.column,
            .line    = state.line,
            .rule    = state.rule,
            .matched = state.matched,
            .name    = lex->state_name(state.stateId),
        });
    }

    return res;
}

std::string view(OrgLexerImpl* lex) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    std::string    text      = lex->impl->matcher().str();
    std::u32string utf32_str = conv.from_bytes(text);
    char32_t       codepoint = utf32_str[0];
    std::string    states;
    std::string    line = lex->impl->matcher().line();

    for (OrgLexerImpl::PushInfo const& state : lex->states) {
        states += std::format(
            " <{}:{}:{}:{}:RULE{}>",
            escape_for_write(state.matched),
            lex->state_name(state.stateId),
            state.line,
            state.column,
            state.rule);
    }

    return std::format(
        "{}:{} (orig:{}) {} (ST:{}) {} (INT:{}) {} {}",
        lex->impl->lineno(),
        lex->impl->columno(),
        lex->p.sub_locations | rv::transform([](auto it) {
            return fmt("{}:{}", it.line, it.col);
        }) | rs::to<std::vector>(),
        lex->state_name(lex->impl->start()),
        lex->impl->start(),
        escape_for_write(text).toBase(),
        (uint32_t)codepoint,
        escape_for_write(
            line.substr(lex->impl->columno(), line.length() - 1)),
        states);
}
} // namespace

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
        if (p.traceStructured) {
            ValueToken val{
                .index = id.getIntIndex(),
                .value = impl->matcher().str(),
            };

            (*p.traceStream) << to_json_eval(EntryLexer{EntryLexer::Add{
                .indent = p.indentation,
                .token  = val,
            }}) << std::endl;
        } else {
            (*p.traceStream) << std::format(
                "{}   {:0>4}] = {} {}",
                get_print_indent(),
                id.getIndex(),
                token,
                escape_for_write(impl->matcher().str()))
                             << std::endl;
        }
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
            view(this));
    }

    impl->pop_state();

    CHECK(impl->start() == next) << std::format(
        "After popping {} expected next state to be {} line:{} but got "
        "{} '{}'",
        state_name(current),
        state_name(next),
        line,
        state_name(impl->start()),
        view(this));

    states.pop_back();
    if (!states.empty()) { CHECK(states.back().stateId == next); }

    if (p.traceStream) {
        if (p.traceStructured) {
            (*p.traceStream) << to_json_eval(EntryLexer{EntryLexer::Pop{
                .indent       = p.indentation,
                .currentState = state_name(current),
                .nextState    = state_name(next),
                .yamlLine     = line,
                .view         = viewStruct(this),
            }}) << std::endl;
        } else {
            (*p.traceStream) << std::format(
                "{}         - {} -> {} at {} with {}",
                get_print_indent(),
                state_name(current),
                state_name(next),
                line,
                view(this)) << std::endl;
        }
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
        view(this));
    impl->push_state(next);
    states.push_back(PushInfo{
        .stateId = next,
        .line    = static_cast<int>(impl->lineno()),
        .column  = static_cast<int>(impl->columno()),
        .matched = impl->str(),
        .rule    = line,
    });

    if (p.traceStream) {
        if (p.traceStructured) {
            (*p.traceStream) << to_json_eval(EntryLexer{EntryLexer::Push{
                .view         = viewStruct(this),
                .indent       = p.indentation,
                .currentState = state_name(current),
                .nextState    = state_name(next),
                .yamlLine     = line,
            }}) << std::endl;
        } else {
            (*p.traceStream) << std::format(
                "{}         + {} -> {} at {} with {}",
                get_print_indent(),
                state_name(current),
                state_name(next),
                line,
                view(this)) << std::endl;
        }
    }
}

void OrgLexerImpl::before(
    int               line,
    Opt<OrgTokenKind> kind,
    const char*       pattern) {
    if (p.traceStream) {
        if (p.traceStructured) {
            (*p.traceStream)
                << to_json_eval(EntryLexer{EntryLexer::PreToken{
                       .tokenRegex = pattern,
                       .yamlLine   = line,
                       .indent     = p.indentation,
                       .view       = viewStruct(this),
                   }})
                << std::endl;
        } else {
            (*p.traceStream) << std::format(
                "{}>  {:0>4}]   {} {}",
                get_print_indent(),
                line,
                escape_for_write(pattern),
                view(this)) << std::endl;
        }
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


void OrgLexerImpl::unknown() {
    if (p.traceStream) {
        if (p.traceStructured) {
            (*p.traceStream)
                << to_json_eval(EntryLexer{EntryLexer::Unknown{
                       .view   = viewStruct(this),
                       .indent = p.indentation,
                   }})
                << std::endl;
        } else {
            (*p.traceStream) << get_print_indent() << "  X unknown "
                             << view(this) << std::endl;
        }
    } else {
        // LOG(ERROR) << "Unknown " << view(this);
    }

    CHECK(++p.visitedUnknown < p.maxUnknown) << std::format(
        "Max {} visited {}", p.maxUnknown, p.visitedUnknown);
}

std::string OrgLexerImpl::get_print_indent() const {
    return std::string(p.indentation * 3, ' ');
}
