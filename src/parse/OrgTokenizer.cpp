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

OrgFill fill(BaseLexer& lex) { return OrgFill{.base = lex.tok().value}; }

void OrgTokenizer::recombine(BaseLexer& lex) {
#define add_as(__to) out->add(OrgToken{__to, fill(lex)});
#define pop_as(__to)                                                      \
    {                                                                     \
        add_as(__to);                                                     \
        lex.next();                                                       \
    }

#define add_fake(__to) out->add(OrgToken{__to});

#define direct(__from, __to)                                              \
    case __from: {                                                        \
        pop_as(__to);                                                     \
        break;                                                            \
    }


    enum class State
    {
        None,
        Paragraph
    };
    Vec<State> state;

    auto push = [&state](State value) -> void { state.push_back(value); };

    auto top = [&state]() -> State {
        return state.empty() ? State::None : state.back();
    };

    auto pop = [&state]() -> State {
        return state.empty() ? State::None : state.pop_back_v();
    };


    while (lex.hasNext(0)) {
        auto               start = lex.pos;
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

            case obt::EndOfFile: {
                while (!state.empty()) {
                    switch (top()) {
                        case State::Paragraph: {
                            add_fake(otk::ParagraphEnd);
                            break;
                        }
                    }
                    pop();
                }
                lex.next();
                break;
            }

            case obt::Word: {
                if (top() == State::None) {
                    add_fake(otk::ParagraphStart);
                    push(State::Paragraph);
                }

                pop_as(otk::Word);
                break;
            }

            case obt::MediumNewline: {
                if (top() == State::Paragraph) {
                    add_fake(otk::ParagraphEnd);
                    pop();
                }

                pop_as(otk::Newline);
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

void OrgTokenizer::assignMarkupDirections() {}

void OrgTokenizer::convert(BaseTokenGroup& input) {
    Lexer<BaseTokenKind, BaseFill> lex(&input);
    return convert(lex);
}

void OrgTokenizer::convert(BaseLexer& lex) {
    rewriteIndents(lex);
    lex.pos = TokenId<BaseTokenKind, BaseFill>::FromValue(1);
    recombine(lex);
    assignMarkupDirections();
}
