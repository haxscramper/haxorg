#pragma once

#include "OrgTokenizer.hpp"

#include <hstd/stdlib/algorithms.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/wrappers/perfetto_aux.hpp>

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#include "OrgTokenizerMacros.hpp"


using ock = OrgCommandKind;
using otk = OrgTokenKind;
using obt = BaseTokenKind;

void OrgTokenizer::rewriteIndents(BaseLexer& lex) {
    while (lex.hasNext()) {
        lex.next();
    }
}


DECL_DESCRIBED_ENUM_STANDALONE(State, None, Paragraph);
DECL_DESCRIBED_ENUM_STANDALONE(
    MarkKind,
    Bold,
    Italic,
    Markup,
    Parens,
    Curly,
    Quotes);


OrgFill fill(BaseLexer& lex) { return OrgFill{.base = lex.tok().value}; }

namespace {

struct RecombineState {
    OrgTokenizer* d;
    struct Mark {
        MarkKind   kind;
        OrgTokenId set;
    };

    Vec<Mark>  mark;
    Vec<State> state;
    BaseLexer& lex;


    RecombineState(OrgTokenizer* d, BaseLexer& lex) : d(d), lex(lex) {}

    auto prev_token() -> Opt<BaseToken> {
        if (lex.hasNext(-1)) {
            return lex.tok(-1);
        } else {
            return std::nullopt;
        }
    };

    auto next_token() -> Opt<BaseToken> {
        if (lex.hasNext(1)) {
            return lex.tok(1);
        } else {
            return std::nullopt;
        }
    };


    void state_push(State value) { state.push_back(value); };

    State state_top() {
        return state.empty() ? State::None : state.back();
    };

    State state_pop() {
        return state.empty() ? State::None : state.pop_back_v();
    };

    // Push new markup token from the current lexer position and
    // remember the opening location in the stack.
    void mark_push(MarkKind value, OrgTokenKind __to) {
        OrgTokenId added = add_as(__to);
        mark.push_back(Mark{.kind = value, .set = added});
        lex.next();
    };

    // Get top known markup token from the stack of markup openings
    Opt<Mark> mark_top() {
        return mark.empty() ? std::nullopt : Opt<Mark>(mark.back());
    };

    // Finalize the markup token pair
    Opt<Mark> mark_pop(MarkKind value, OrgTokenKind __to) {
        OrgTokenId added = add_as(__to);
        lex.next();
        CHECK(!mark.empty())
            << "Expected the markup stack to not be empty";
        CHECK(mark.back().kind == value)
            << fmt("Expected markup stack to have value {} but top is {}. "
                   "Pushed from {}",
                   fmt1(value),
                   mark.back().kind,
                   mark.back().set);

        return mark.empty() ? std::nullopt : Opt<Mark>(mark.pop_back_v());
    };

    void mark_toggle(MarkKind value, OrgTokenKind to) {
        // Check if there has already been an opening markup token
        // somewhere in the stack.
        if (std::any_of(mark.begin(), mark.end(), [&value](Mark const& m) {
                return m.kind == value;
            })) {
            if (mark.back().kind == value) {
                // If it is the last one, then close it properly
                mark_pop(value, to);
            } else {
                // If it is something internal, it means there is an
                // unbalanced content, like `{[}` -- opening `[` will add
                // something to the stack, but surrounding `{}` would not
                // allow the proper tree to be formed.
                CHECK(false) << "TODO FAIL";
            }
        } else {
            mark_push(value, to);
        }
    }

    OrgTokenId add_as(OrgTokenKind __to) {
        return d->out->add(OrgToken{__to, fill(lex)});
    }

    void pop_as(OrgTokenKind __to) {
        add_as(__to);
        lex.next();
    }

    OrgTokenId add_fake(OrgTokenKind __to) {
        return d->out->add(OrgToken{__to});
    }

    void recombine_markup() {
        // TODO Check if we are in the paragraph element or some other place.
        auto prev = prev_token();
        auto next = next_token();
        switch (lex.kind()) {
            case obt::Asterisk: {
                if (prev && next) {
                    LOG(INFO) << fmt("prev={} next={}", prev, next);
                    if (prev->kind == obt::Whitespace
                        && next->kind == obt::Word) {
                        mark_toggle(MarkKind::Bold, otk::BoldOpen);
                    }

                } else if (!prev) {
                    mark_push(MarkKind::Bold, otk::BoldOpen);
                }

                break;
            }
            default: {
                CHECK(false) << fmt(
                    "Unexpected kind of the markup recombine input {}",
                    lex.kind());
            }
        }
    }

    void recombine_impl() {

#define direct(__from, __to)                                              \
    case __from: {                                                        \
        pop_as(__to);                                                     \
        break;                                                            \
    }


        while (lex.hasNext(0)) {
            BaseTokenId        start = lex.pos;
            BaseToken const&   tok   = lex.tok();
            BaseFill const&    val   = tok.value;
            std::string const& str   = tok.value.text;


            switch (lex.kind()) {
                direct(obt::Ampersand, otk::Punctuation);
                direct(obt::Whitespace, otk::Space);
                direct(obt::AnyPunct, otk::Punctuation);
                direct(obt::Newline, otk::Newline);
                direct(obt::Comment, otk::Comment);
                direct(obt::HashIdent, otk::HashTag);

                case obt::Asterisk: {
                    recombine_markup();
                    break;
                }

                case obt::EndOfFile: {
                    while (!state.empty()) {
                        switch (state_top()) {
                            case State::Paragraph: {
                                add_fake(otk::ParagraphEnd);
                                break;
                            }
                        }
                        state_pop();
                    }
                    lex.next();
                    break;
                }

                case obt::Word: {
                    if (state_top() == State::None) {
                        add_fake(otk::ParagraphStart);
                        state_push(State::Paragraph);
                    }

                    pop_as(otk::Word);
                    break;
                }

                case obt::MediumNewline: {
                    if (state_top() == State::Paragraph) {
                        add_fake(otk::ParagraphEnd);
                        state_pop();
                    }

                    pop_as(otk::SkipNewline);
                    break;
                }
                case obt::BraceOpen: {
                    if (lex.hasNext(-1)) {
                        switch (lex.tok(-1).kind) {
                            case obt::HashIdent:
                                pop_as(otk::HashTagOpen);
                                break;
                            default: pop_as(otk::Punctuation);
                        }
                    } else {
                        pop_as(otk::Punctuation);
                    }
                }
                default: {
                    DLOG(ERROR) << std::format(
                        "Unhanled kind for token conversion, got {}:{} {} "
                        "\"{}\"",
                        val.line,
                        val.col,
                        lex.kind(),
                        val.text);
                    lex.next();
                }
            }

            CHECK((lex.pos != start)) << std::format(
                "Non-terminating token conversion case, got kind {} "
                "text {} "
                "at id {} with no movement",
                lex.kind(),
                val.text,
                lex.pos.format());
        }
    }
};

} // namespace

void OrgTokenizer::recombine(BaseLexer& lex) {
    RecombineState state{this, lex};
    state.recombine_impl();
}

void OrgTokenizer::convert(BaseTokenGroup& input) {
    Lexer<BaseTokenKind, BaseFill> lex(&input);
    return convert(lex);
}

void OrgTokenizer::convert(BaseLexer& lex) {
    rewriteIndents(lex);
    lex.pos = TokenId<BaseTokenKind, BaseFill>::FromValue(1);
    recombine(lex);
}
