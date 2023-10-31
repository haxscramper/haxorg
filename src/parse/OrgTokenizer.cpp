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
#define direct(__from, __to)                                              \
    case __from: {                                                        \
        add_as(__to);                                                     \
        lex.next();                                                       \
        break;                                                            \
    }

    while (lex.hasNext()) {
        BaseToken const&   tok = lex.tok();
        BaseFill const&    val = tok.value;
        std::string const& str = tok.value.text;
        switch (lex.kind()) {
            direct(obt::Ampersand, otk::Punctuation);
            direct(obt::Whitespace, otk::Space);
            direct(obt::Word, otk::Word);
            direct(obt::AnyPunct, otk::Punctuation);
            direct(obt::Newline, otk::Newline);
            direct(obt::Comment, otk::Comment);
            direct(obt::HashIdent, otk::HashTag);
            case obt::BraceOpen: {
                switch (lex.tok(-1).kind) {
                    case obt::HashIdent: add_as(otk::HashTagOpen); break;
                    default: add_as(otk::Punctuation);
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
