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
#define direct(__from, __to)                                              \
    case __from: {                                                        \
        out->add(OrgToken{__to, fill(lex)});                              \
        break;                                                            \
    }

    while (lex.hasNext()) {
        switch (lex.kind()) {
            direct(obt::Ampersand, otk::Punctuation);
            default: {
                CHECK(false) << std::format(
                    "Unhanled kind for token conversion, got {}",
                    lex.kind());
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
