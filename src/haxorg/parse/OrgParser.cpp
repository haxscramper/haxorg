#include <haxorg/parse/OrgParser.hpp>
#pragma clang diagnostic ignored "-Wunused-result"
#pragma clang diagnostic ignored "-Wformat-security"
#include <haxorg/sem/perfetto_org.hpp>

#pragma clang diagnostic error "-Wunused-result"


using otk = OrgTokenKind;
using onk = OrgNodeKind;

using namespace org::parse;
using namespace hstd;

namespace {
const OrgTokSet Newline{
    otk::Newline,
    otk::LongNewline,
    otk::MediumNewline,
};

const OrgTokSet ParagraphTerminator{
    otk::MediumNewline,
    otk::LongNewline,
    otk::SubtreeStars,
    otk::ListBegin,
    otk::ListItemBegin,
    otk::CmdSrcBegin,
    otk::CmdSrcEnd,
    otk::CmdQuoteEnd,
    otk::CmdQuoteBegin,
    otk::StmtListEnd,
    otk::CmdPrefix,
    otk::StmtListEnd,
    otk::LeadingPipe,
    otk::ListItemEnd,
    otk::Indent,
    otk::Dedent,
    otk::SameIndent,
};

OrgTokSet ListStarts{
    otk::LeadingMinus,
    otk::LeadingNumber,
    otk::LeadingPlus,
    otk::TreeClock,
};

const OrgTokSet BlockTerminator{
    otk::SubtreeStars,
};
} // namespace


#define SUB_PARSE(__kind, __lex, __on_failure)                            \
    BOOST_OUTCOME_TRY(maybe_recursive_error_end(                          \
        this->subParseImpl(                                               \
            &OrgParser::parse##__kind, __lex, __LINE__, __func__),        \
        __on_failure,                                                     \
        __lex))

#define SUB_PARSEX(__kind, __lex, __on_failure)                           \
    BOOST_OUTCOME_TRYX(maybe_recursive_error_end(                         \
        this->subParseImpl(                                               \
            &OrgParser::parse##__kind, __lex, __LINE__, __func__),        \
        __on_failure,                                                     \
        __lex))

#define TRY_SKIP(__lex, __expected)                                       \
    BOOST_OUTCOME_TRY(skip(__lex, __expected))

#define TRY_POPX(__lex, __expression)                                     \
    BOOST_OUTCOME_TRYX(pop(__lex, __expression))

void OrgParser::space(OrgLexer& lex, int line, char const* function) {
    while (lex.at(OrgTokSet{otk::Whitespace, otk::LeadingSpace})) {
        std::ignore = skip(lex, std::nullopt, line, function);
    }
}

void OrgParser::newline(OrgLexer& lex, int line, char const* function) {
    while (lex.at(Newline)) {
        std::ignore = skip(lex, std::nullopt, line, function);
    }
}

SubLexer<OrgTokenKind, OrgFill> subToEol(
    OrgLexer& lex,
    OrgTokSet Terminator = ParagraphTerminator) {
    SubLexer sub{lex};
    while (lex.can_search(Terminator)) { sub.add(lex.pop()); }
    if (!sub.tokens.empty()) { sub.start(); }
    return sub;
}

OrgParser::ParseResult OrgParser::parseCSVArguments(OrgLexer& lex) {
    __perf_trace("parsing", "parseCSVArguments");
    auto __trace = trace(lex);
    token(
        onk::Word,
        TRY_POPX(
            lex,
            (OrgTokSet{
                otk::Word,
                otk::SrcContent,
            })));

    if (lex.at(otk::ParBegin)) {
        TRY_SKIP(lex, otk::ParBegin);
        while (lex.at(otk::RawText)) {
            token(onk::RawText, TRY_POPX(lex, otk::RawText));
            if (lex.at(otk::Comma)) { skip(lex); }
        }
        TRY_SKIP(lex, otk::ParEnd);
    }

    return ParseOk{};
}

OrgParser::ParseResult OrgParser::subParseImpl(
    OrgParser::ParseResult (OrgParser::*func)(OrgLexer&),
    OrgLexer&   lex,
    int         line,
    char const* function) {
    auto tok = lex.get();
    return (this->*func)(lex);
}


OrgParser::ParseResult OrgParser::parseMacro(OrgLexer& lex) {
    __perf_trace("parsing", "parseMacro");
    auto __trace = trace(lex);

    int closingOffset = 0;
    while (lex.hasNext(closingOffset)
           && !lex.at(otk::CurlyEnd, closingOffset)) {
        ++closingOffset;
    }

    bool hasClose = lex.at(otk::CurlyEnd, closingOffset)
                 && lex.at(otk::CurlyEnd, closingOffset + 1)
                 && lex.at(otk::CurlyEnd, closingOffset + 2);

    start(onk::Macro);
    TRY_SKIP(lex, otk::CurlyBegin);
    TRY_SKIP(lex, otk::CurlyBegin);
    TRY_SKIP(lex, otk::CurlyBegin);
    token(onk::Word, TRY_POPX(lex, OrgTokSet{otk::Word}));

    SUB_PARSE(CallArguments, lex, "Failed to parse call arguments");

    for (int i = 0; i <= 2; ++i) {
        if (lex.at(otk::CurlyEnd)) {
            std::ignore = skip(lex, otk::CurlyEnd);
        } else {
            LOGIC_ASSERTION_CHECK(!hasClose, "");
            return error_end(
                "macro is missing closing triple curly brace", lex);
        }
    }

    LOGIC_ASSERTION_CHECK(hasClose, "");
    return ParseOk{};
}

OrgParser::ParseResult OrgParser::parseCallArguments(OrgLexer& lex) {
    __perf_trace("parsing", "parseCallArguments");
    auto __trace = trace(lex);
    start(onk::InlineStmtList);
    if (lex.at(otk::ParBegin)) {
        TRY_SKIP(lex, otk::ParBegin);
        while (lex.can_search(otk::ParEnd)) {
            SUB_PARSE(
                AttrValue,
                lex,
                "Failed to parse attribute value in call arguments");
            space(lex);
            if (lex.at(otk::Comma)) {
                std::ignore = skip(lex, otk::Comma);
                space(lex);
            }
        }


        TRY_SKIP(lex, otk::ParEnd);
    }

    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseAttrValue(OrgLexer& lex) {
    __perf_trace("parsing", "parseAttrColonKeyValue");
    auto __trace = trace(lex);
    start(onk::AttrValue);

    if (lex.at(IntSet<OrgTokenKind>{
            otk::CmdColonIdent,
            otk::CmdRawArg,
            otk::ParBegin,
        })) {
        print("Attribute value was lexed with explicit argument tokens");
        if (lex.at(otk::CmdColonIdent)) {
            // `:ident`
            token(onk::Word, TRY_POPX(lex, otk::CmdColonIdent));
            space(lex);
        } else {
            empty();
        }

        IntSet<OrgTokenKind> eqTokens{
            otk::Equals,
            otk::VerbatimBegin,
            otk::VerbatimEnd,
            otk::VerbatimUnknown};

        if (lex.at(otk::CmdRawArg) && lex.at(eqTokens, +1)) {
            // `key=`
            token(onk::RawText, TRY_POPX(lex, otk::CmdRawArg));
            TRY_SKIP(lex, eqTokens);
            space(lex);
        } else {
            empty();
        }

        if (lex.at(otk::ParBegin)) {
            SUB_PARSE(
                AttrLisp,
                lex,
                "Failed to parse attribute value as lisp expression.");
        } else if (lex.at(otk::CmdRawArg)) {
            token(onk::RawText, TRY_POPX(lex, otk::CmdRawArg));
        } else {
            empty();
        }

        if (lex.at(otk::BraceBegin)) {
            start(onk::InlineStmtList);
            TRY_SKIP(lex, otk::BraceBegin);
            while (lex.at(otk::CmdRawArg) || lex.at(otk::Comma)) {
                if (lex.at(otk::Comma)) {
                    empty();
                    std::ignore = skip(lex, otk::Comma);
                    space(lex);
                } else {
                    token(onk::RawText, TRY_POPX(lex, otk::CmdRawArg));
                    space(lex);
                    if (lex.at(otk::Comma)) {
                        std::ignore = skip(lex, otk::Comma);
                        space(lex);
                    }
                }
            }

            TRY_SKIP(lex, otk::BraceEnd);
            end();
        } else {
            empty();
        }
    } else {
        // `{{{macro(with some parameter that looks like actual text)}}}}`
        // is lexed as a part of the text, so tokens in the argument list
        // are not 'correct'.
        print("Argument value was lexed using random tokens");
        empty();

        if (lex.at(OrgTokSet{otk::Word, otk::RawText})
            && lex.at(
                OrgTokSet{
                    otk::Equals,
                    otk::VerbatimBegin,
                    otk::VerbatimEnd,
                    otk::VerbatimUnknown,
                },
                +1)) {
            token(onk::RawText, pop(lex));
            skip(lex);
        } else {
            empty();
        }

        start(onk::InlineStmtList);
        while (lex.can_search(OrgTokSet{otk::ParEnd, otk::Comma})) {
            token(onk::RawText, pop(lex));
        }
        end();
        empty();
    }


    return ParseOk{};
}

OrgParser::ParseResult OrgParser::parseAttrLisp(OrgLexer& lex) {
    __perf_trace("parsing", "parseAttrLisp");
    auto __trace = trace(lex);
    start(onk::AttrLisp);
    if (lex.at(otk::ParBegin)) {
        start(onk::InlineStmtList);
        TRY_SKIP(lex, otk::ParBegin);
        space(lex);
        while (lex.can_search(otk::ParEnd)) {
            SUB_PARSE(
                AttrLisp,
                lex,
                "Failed to parse lisp attribute sub-expression.");
            space(lex);
        }
        TRY_SKIP(lex, otk::ParEnd);
        end();
    } else {
        token(onk::RawText, pop(lex));
    }

    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parsePlaceholder(OrgLexer& lex) {
    __perf_trace("parsing", "parsePlaceholder");
    auto __trace = trace(lex);
    if (lex.at(otk::Placeholder)) {
        token(onk::Placeholder, TRY_POPX(lex, otk::Placeholder));
    } else {
        token(onk::Punctuation, pop(lex));
    }

    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseLatex(OrgLexer& lex) {
    __perf_trace("parsing", "parseLatex");
    auto __trace = trace(lex);
    TRY_SKIP(lex, otk::LatexParBegin);
    token(onk::InlineMath, TRY_POPX(lex, otk::LatexInlineRaw));
    TRY_SKIP(lex, otk::LatexParEnd);
    return ParseOk{};
}


void OrgParser::textFold(OrgLexer& lex) {
    // Text fold method will consume all tokens in the lexer, folding into
    // series of tree nodes.
    auto __trace = trace(lex);

    Func<void()> aux;
    auto         _begin = [&](onk Kind) {
        print(fmt("begin {}", Kind));
        int        startDepth = treeDepth();
        OrgTokenId startToken = pop(lex);
        start(Kind);
        aux();
        print(
            fmt("Started on {} exited on {} tok {}",
                startDepth,
                treeDepth(),
                startToken));
        // If the function returned earlier because the input has ended
        // before the markup opening was terminated it means there is no
        // correct markup in the text and it must be converted to the
        // punctuation.
        //
        // `*bold` -> `aux(*)` -- after pushing `bold` as a workd and
        // returning, the `aux(*)` will convert `Bold` into
        // `Punctuation(*)`
        if (startDepth < treeDepth()) {
            print(fmt(
                "Folding unclosed with token {}", lex.in->at(startToken)));
            auto unclosed = group->pendingTrees.back();
            group->nodes.at(unclosed).kind  = onk::Punctuation;
            group->nodes.at(unclosed).value = startToken;
            group->pendingTrees.pop_back();
        }
    };

    auto _end = [&](onk Kind) {
        print(fmt("end {}", Kind));
        if (pending().kind == Kind) {
            end();
            skip(lex);
        } else {
            token(onk::Punctuation, pop(lex));
        }
    };

    auto _unknown = [&](onk Kind) {
        print(fmt("unknown {}", Kind));
        if (pending().kind == Kind) {
            _end(Kind);
        } else {
            _begin(Kind);
        }
    };


    aux = [&]() {
        auto __trace = trace(lex, std::nullopt, __LINE__, "aux");

        while (!lex.finished()) {
            switch (lex.kind()) {
                case otk::Escaped: {
                    token(onk::Escaped, TRY_POPX(lex, otk::Escaped));
                    break;
                }
                case otk::RawText: {
                    token(onk::RawText, TRY_POPX(lex, otk::RawText));
                    break;
                }
                case otk::Newline: {
                    token(onk::Newline, TRY_POPX(lex, otk::Newline));
                    break;
                }
                case otk::Word: {
                    token(onk::Word, TRY_POPX(lex, otk::Word));
                    break;
                }
                case otk::BigIdent: {
                    token(onk::BigIdent, TRY_POPX(lex, otk::BigIdent));
                    break;
                }
                case otk::Punctuation: {
                    token(
                        onk::Punctuation, TRY_POPX(lex, otk::Punctuation));
                    break;
                }
                case otk::Colon: {
                    token(onk::Colon, TRY_POPX(lex, otk::Colon));
                    break;
                }


                case otk::BoldBegin: _begin(onk::Bold); break;
                case otk::BoldEnd: _end(onk::Bold); break;
                case otk::BoldUnknown: _unknown(onk::Bold); break;
                case otk::ItalicBegin: _begin(onk::Italic); break;
                case otk::ItalicEnd: _end(onk::Italic); break;
                case otk::ItalicUnknown: _unknown(onk::Italic); break;
                case otk::UnderlineBegin: _begin(onk::Underline); break;
                case otk::UnderlineEnd: _end(onk::Underline); break;
                case otk::UnderlineUnknown:
                    _unknown(onk::Underline);
                    break;
                case otk::StrikeBegin: _begin(onk::Strike); break;
                case otk::StrikeEnd: _end(onk::Strike); break;
                case otk::StrikeUnknown: _unknown(onk::Strike); break;

                case otk::Whitespace: token(onk::Space, pop(lex)); break;
                case otk::CurlyBegin: {
                    if (lex.at(
                            Vec{otk::CurlyBegin,
                                otk::CurlyBegin,
                                otk::CurlyBegin})) {
                        SUB_PARSE(
                            Macro,
                            lex,
                            "Failed to parse inline macro call.");
                    } else {
                        token(onk::Punctuation, pop(lex));
                    }
                    break;
                }

                case otk::AngleEnd: {
                    token(onk::Punctuation, pop(lex));
                    break;
                }

                case otk::MiscUnicode:
                case otk::Time:
                case otk::Date:
                case otk::SubtreePriority:
                case otk::Number: {
                    token(onk::Word, pop(lex));
                    break;
                }

                case otk::CriticAddBegin:
                case otk::CriticDeleteBegin:
                case otk::CriticReplaceBegin:
                case otk::CriticCommentBegin:
                case otk::CriticHighlightBegin: {
                    SUB_PARSE(
                        CriticMarkup,
                        lex,
                        "Failed to parse inline critic markup in text.");
                    break;
                }

                case otk::Placeholder: {
                    parsePlaceholder(
                        lex, "Failed to parse inline placeholder text.");
                    break;
                }

                case otk::ActiveDynamicTimeContent:
                case otk::InactiveDynamicTimeContent: {
                    SUB_PARSE(
                        TimeRange,
                        lex,
                        "Failed to parse inline timestamp/time-range.");
                    break;
                }

                case otk::AngleBegin: {
                    if (lex.at(otk::Date, +1)) {
                        SUB_PARSE(
                            TimeRange,
                            lex,
                            "Failed to parse inline active time range.");
                    } else {
                        SUB_PARSE(
                            Placeholder,
                            lex,
                            "Failed to parse placeholder.");
                    }
                    break;
                }

                case otk::InlineExportBackend: {
                    SUB_PARSE(
                        InlineExport,
                        lex,
                        "Failed to parse inline export backend. ");
                    break;
                }

                case otk::TextSrcBegin:
                    SUB_PARSE(
                        SrcInline, lex, "Failed to parse inline source.");
                    break;
                case otk::HashIdent:
                    SUB_PARSE(
                        HashTag, lex, "Failed to parse inline hashtag");
                    break;
                case otk::LinkProtocolHttp:
                case otk::LinkProtocol:
                case otk::LinkBegin:
                    SUB_PARSE(Link, lex, "Failed to parse inline link.");
                    break;
                case otk::FootnoteInlineBegin:
                case otk::FootnoteLinked:
                    SUB_PARSE(
                        Footnote, lex, "Failed to parse inline footnote.");
                    break;
                case otk::Symbol:
                    SUB_PARSE(
                        Symbol, lex, "Failed to parse inline symbol.");
                    break;

                case otk::BraceBegin: {
                    if (lex.at(otk::Date, +1)) {
                        SUB_PARSE(
                            TimeRange,
                            lex,
                            "Failed to parse inline time range.");
                    } else {
                        token(onk::Punctuation, pop(lex));
                    }
                    break;
                }

                case otk::At: {
                    token(onk::AtMention, TRY_POPX(lex, otk::At));
                    break;
                }

                case otk::VerbatimBegin:
                case otk::MonospaceBegin: {
                    SUB_PARSE(
                        VerbatimOrMonospace,
                        lex,
                        "Failed to parse inline verbatim/monospace.");
                    break;
                }

                case otk::DoubleAngleBegin:
                case otk::TripleAngleBegin: {
                    SUB_PARSE(
                        AngleTarget,
                        lex,
                        "Failed to parse inline angle target.");
                    break;
                }

                case otk::Comment:
                case otk::LeadingSpace: {
                    skip(lex);
                    break;
                }

                case otk::LinkEnd:
                case otk::LinkDescriptionBegin:
                case otk::LinkTargetEnd: {
                    if (lex.tok()->text.empty()) {
                        skip(lex);
                    } else {
                        token(onk::Punctuation, pop(lex));
                    }
                    break;
                }

                default: {
                    token(onk::Punctuation, pop(lex));
                    break;
                }
            }
        }

#undef CASE_MARKUP
#undef CASE_SINGLE
#undef CASE_INLINE
    };

    aux();
}


Slice<OrgId> OrgParser::parseText(OrgLexer& lex) {
    auto        __trace   = trace(lex);
    OrgId       first     = back();
    std::string forMsg    = getLocMsg(lex);
    int         treeStart = treeDepth();
    textFold(lex);
    int treeEnd = treeDepth();
    print(
        "Trace levels after text fold start:$#, end:$#"
        % to_string_vec(treeStart, treeEnd));

    if (treeStart != treeEnd) {
        auto msg = fmt(
            "Text fold created unbalanced tree - starting with depth {} "
            "ended up on depth {} on position {} (starting from {})",
            treeStart,
            treeEnd,
            getLocMsg(lex),
            forMsg);

        throw fatalError(lex, msg);
    }

    OrgId last = back();
    return slice(first, last);
}


OrgParser::ParseResult OrgParser::parseLink(OrgLexer& lex) {
    __perf_trace("parsing", "parseLink");
    auto __trace = trace(lex);
    if (lex.at(otk::LinkProtocolHttp)) {
        start(onk::Link);
        token(onk::Word, TRY_POPX(lex, otk::LinkProtocolHttp));
        token(onk::RawText, TRY_POPX(lex, otk::LinkTarget));
        empty();
        return ParseOk{};
    } else {
        start(onk::Link);
        TRY_SKIP(lex, otk::LinkBegin);
        // LOG(INFO) << fmt1(lex.tok()->line);
        switch (lex.kind()) {
            case otk::LinkProtocolHttp: {
                token(onk::Word, TRY_POPX(lex, otk::LinkProtocolHttp));
                token(onk::RawText, TRY_POPX(lex, otk::LinkTarget));
                break;
            }
            case otk::LinkProtocolId: {
                token(onk::Word, TRY_POPX(lex, otk::LinkProtocolId));
                token(onk::RawText, TRY_POPX(lex, otk::LinkTarget));
                break;
            }
            case otk::LinkProtocolTitle: {
                empty();
                token(onk::RawText, TRY_POPX(lex, otk::LinkProtocolTitle));
                break;
            }
            case otk::LinkProtocolCustomId: {
                token(onk::Word, TRY_POPX(lex, otk::LinkProtocolCustomId));
                token(onk::RawText, TRY_POPX(lex, otk::LinkTarget));
                break;
            }
            case otk::LinkProtocolAttachment: {
                token(
                    onk::Word, TRY_POPX(lex, otk::LinkProtocolAttachment));
                token(onk::RawText, TRY_POPX(lex, otk::LinkTarget));
                break;
            }
            case otk::LinkProtocolFile: {
                token(onk::Word, TRY_POPX(lex, otk::LinkProtocolFile));
                token(onk::RawText, TRY_POPX(lex, otk::LinkTarget));
                break;
            }
            case otk::LinkTargetFile: {
                empty();
                token(onk::RawText, TRY_POPX(lex, otk::LinkTargetFile));
                break;
            }
            case otk::LinkProtocolInternal: {
                empty();
                token(
                    onk::RawText,
                    TRY_POPX(lex, otk::LinkProtocolInternal));
                break;
            }
            default:
                token(onk::Word, TRY_POPX(lex, otk::LinkProtocol));
                SubLexer sub{lex};
                while (!lex.at(OrgTokSet{otk::LinkSplit, otk::LinkEnd})) {
                    sub.add(pop(lex));
                }
                if (sub.empty()) {
                    empty();
                } else {
                    sub.start();
                    SUB_PARSE(
                        Paragraph,
                        sub,
                        "Failed to parse link free-form target "
                        "paragraph.");
                }
        }

        if (lex.at(otk::LinkSplit)) {
            TRY_SKIP(lex, otk::LinkSplit);
            SubLexer sub{lex};
            while (lex.can_search(otk::LinkEnd)) { sub.add(pop(lex)); }
            if (sub.empty()) {
                empty();
            } else {
                sub.start();
                SUB_PARSE(
                    Paragraph,
                    sub,
                    "Failed to parse link description paragraph");
            }
        } else {
            empty();
        }


        TRY_SKIP(lex, otk::LinkEnd);
        return ParseOk{};
    }
}


OrgParser::ParseResult OrgParser::parseInlineMath(OrgLexer& lex) {
    __perf_trace("parsing", "parseInlineMath");
    auto __trace = trace(lex);

    start(onk::InlineMath);


    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseSymbol(OrgLexer& lex) {
    __perf_trace("parsing", "parseSymbol");
    auto __trace = trace(lex);
    start(onk::Symbol);
    token(onk::Word, TRY_POPX(lex, otk::Symbol));

    start(onk::InlineStmtList);
    while (lex.at(otk::BraceBegin)) {
        TRY_SKIP(lex, otk::BraceBegin);
        token(onk::RawText, pop(lex));
        TRY_SKIP(lex, otk::BraceEnd);
    }
    end();

    start(onk::InlineStmtList);
    while (lex.at(otk::CurlyBegin)) {
        if (lex.at(Vec{otk::CurlyBegin, otk::CurlyEnd})) {
            empty();
            TRY_SKIP(lex, otk::CurlyBegin);
            TRY_SKIP(lex, otk::CurlyEnd);
        } else {
            auto sub = SubLexer(
                lex.in, lex.getInside({otk::CurlyBegin}, {otk::CurlyEnd}));
            start(onk::Paragraph);
            parseText(sub);
            end();
        }
    }
    end();

    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseHashTag(OrgLexer& lex) {
    auto __trace = trace(lex);

    struct HashState {
        OrgId result;
        bool  doubleSkip;
    };

    Func<HashState(OrgLexer & lex)> aux;

    using HashResult = hstd::Outcome<HashState, ParseFail>;

    aux = [&](OrgLexer& lex) -> HashResult {
        auto __trace = trace(lex, "aux", __LINE__, "aux");
        start(onk::HashTag);
        space(lex);
        if (lex.at(otk::At)) {
            // Org-mode suppors tags like '@work' etc.
            token(onk::RawText, TRY_POPX(lex, otk::At));
        } else {
            token(
                onk::RawText,
                pop(lex,
                    OrgTokSet{otk::HashIdent, otk::Word, otk::BigIdent}));
        }

        bool doubleSkip = false;

        if (lex.at(otk::DoubleHash)) {
            TRY_SKIP(lex, otk::DoubleHash);
            if (lex.at(
                    OrgTokSet{otk::HashIdent, otk::Word, otk::BigIdent})) {
                auto sub = aux(lex);
                if (sub) {
                    if (sub.assume_value().doubleSkip) {
                        print("double skip");
                        return HashState{.result = end()};
                    }
                } else {
                    return sub.assume_error();
                }

            } else {
                TRY_SKIP(lex, otk::BraceBegin);
                while (
                    !lex.finished()
                    && !lex.at(OrgTokSet{otk::BraceEnd, otk::LinkEnd})) {
                    auto result = aux(lex);
                    if (result.doubleSkip) {
                        print("double skip");
                        return HashState{.result = end()};
                    }
                    if (lex.at(otk::Comma)) { skip(lex); }
                    space(lex);
                }

                if (lex.at(otk::LinkEnd)) {
                    doubleSkip = true;
                    TRY_SKIP(lex, otk::LinkEnd);
                } else {
                    TRY_SKIP(lex, otk::BraceEnd);
                }
            }
        }

        return HashState{
            .result     = end(),
            .doubleSkip = doubleSkip,
        };
    };

    return BOOST_OUTCOME_TRYX(aux(lex)).result;
}


OrgParser::ParseResult OrgParser::parseTimeStamp(OrgLexer& lex) {
    auto __trace   = trace(lex);
    auto start_tok = lex.tok();
    BOOST_OUTCOME_TRY(expect(
        lex,
        OrgTokSet{
            otk::BraceBegin,
            otk::AngleBegin,
            otk::InactiveDynamicTimeContent,
            otk::ActiveDynamicTimeContent,
        }));

    bool active = lex.at(OrgTokSet{
        otk::AngleBegin,
        otk::ActiveDynamicTimeContent,
    });

    if (lex.at(OrgTokSet{
            otk::InactiveDynamicTimeContent,
            otk::ActiveDynamicTimeContent})) {
        if (active) {
            start(onk::DynamicActiveTime);
            TRY_SKIP(lex, otk::ActiveDynamicTimeContent);
        } else {
            start(onk::DynamicInactiveTime);
            TRY_SKIP(lex, otk::InactiveDynamicTimeContent);
        }

        std::function<void()> aux;
        aux = [&]() {
            if (lex.at(otk::ParBegin)) {
                start(onk::InlineStmtList);
                TRY_SKIP(lex, otk::ParBegin);
                space(lex);
                while (lex.can_search(otk::ParEnd)) {
                    SUB_PARSE(
                        AttrLisp,
                        lex,
                        "Failed to parse dynamic timestamp lisp "
                        "expression.");
                    space(lex);
                }
                TRY_SKIP(lex, otk::ParEnd);
                end();
            } else {
                token(onk::RawText, pop(lex));
            }
        };


        aux();

        end();
    } else {
        if (active) {
            start(onk::StaticActiveTime);
            TRY_SKIP(lex, otk::AngleBegin);
        } else {
            start(onk::StaticInactiveTime);
            TRY_SKIP(lex, otk::BraceBegin);
        }

        // Date part is usually used, but I think supporting *time* stamps
        // also makes sense
        if (lex.at(otk::Date)) {
            token(onk::RawText, TRY_POPX(lex, otk::Date));
            space(lex);
        } else {
            empty();
        }

        // Day can sometimes be added to the timestamp
        if (lex.at(otk::Word)) {
            skip(lex);
            space(lex);
        }

        if (lex.at(otk::Time)) {
            token(onk::RawText, TRY_POPX(lex, otk::Time));
            space(lex);
        } else {
            empty();
        }


        // timezone
        if (lex.at(otk::StrikeBegin) && lex.at(otk::Number, +1)) {
            skip(lex);
            token(onk::RawText, TRY_POPX(lex, otk::Number));
            space(lex);
        } else {
            empty();
        }


        if (lex.at(otk::TimeRepeaterSpec)) {
            start(onk::InlineStmtList);
            while (lex.at(otk::TimeRepeaterSpec)) {
                start(onk::InlineStmtList);
                token(onk::RawText, TRY_POPX(lex, otk::TimeRepeaterSpec));
                while (lex.at(otk::TimeRepeaterDuration)) {
                    token(onk::RawText, pop(lex));
                }
                end();
                space(lex);
            }
            end();
        } else {
            empty();
        }

        if (lex.at(otk::TimeWarnPeriod)) {
            token(onk::RawText, TRY_POPX(lex, otk::TimeWarnPeriod));
        } else {
            empty();
        }


        end();
    }

    TRY_SKIP(lex, active ? otk::AngleEnd : otk::BraceEnd);
    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseTimeRange(OrgLexer& lex) {
    auto            __trace = trace(lex);
    const OrgTokSet times{
        otk::BraceBegin,
        otk::BraceEnd,
        otk::AngleBegin,
        otk::AngleEnd,
        otk::InactiveDynamicTimeContent,
        otk::ActiveDynamicTimeContent,
        otk::Date,
        otk::Word,
        otk::Time,
        otk::Number,
        otk::StrikeBegin,
        otk::Whitespace,
        otk::TimeRepeaterSpec,
        otk::TimeWarnPeriod,
        otk::TimeRepeaterDuration,
    };

    Lexer tmp{lex.in};
    tmp.pos          = lex.pos;
    bool isTimeRange = false;
    while (!tmp.finished() && tmp.at(times)) {
        message(printLexerToString(tmp));
        if (tmp.at(otk::AngleEnd) && tmp.at(otk::DoubleDash, +1)
            && tmp.at(
                OrgTokSet{otk::AngleBegin, otk::ActiveDynamicTimeContent},
                +2)) {
            isTimeRange = true;
            break;
        } else if (
            tmp.at(otk::BraceEnd) && tmp.at(otk::DoubleDash, +1)
            && tmp.at(
                OrgTokSet{
                    otk::BraceBegin, otk::InactiveDynamicTimeContent},
                +2)) {
            isTimeRange = true;
            break;
        } else {
            tmp.next();
        }
    }

    if (isTimeRange) {
        message("correct time range found");
        start(onk::TimeRange);
        SUB_PARSE(TimeStamp, lex, "Failed to parse time-range start.");
        TRY_SKIP(lex, otk::DoubleDash);
        SUB_PARSE(TimeStamp, lex, "Failed to parse time-range end");
        if (lex.ahead({otk::Whitespace}, {otk::TimeArrow})) {
            space(lex);
            TRY_SKIP(lex, otk::TimeArrow);
            space(lex);
            token(onk::SimpleTime, TRY_POPX(lex, otk::Time));
        } else {
            empty();
        }

        return ParseOk{};
    } else {
        return SUB_PARSE(TimeStamp, lex, "Failed to parse timestamp");
    }
}


OrgParser::ParseResult OrgParser::parseFootnote(OrgLexer& lex) {
    __perf_trace("parsing", "parseFootnote");
    auto __trace = trace(lex);
    if (lex.at(otk::FootnoteLinked)) {
        start(onk::Footnote);
        empty();
        token(onk::RawText, pop(lex));
        return ParseOk{};
    } else {
        start(onk::InlineFootnote);
        TRY_SKIP(lex, otk::FootnoteInlineBegin);
        SubLexer sub{lex};
        while (!lex.finished() && !lex.at(otk::BraceEnd)) {
            sub.add(pop(lex));
        }
        sub.start();
        SUB_PARSE(
            Paragraph, sub, "Failed to parse inline footnote description");
        TRY_SKIP(lex, otk::BraceEnd);
        return ParseOk{};
    }
}


OrgParser::ParseResult OrgParser::parseSrcInline(OrgLexer& lex) {
    __perf_trace("parsing", "parseSrcInline");
    auto __trace = trace(lex);
    start(onk::SrcInlineCode);
    {
        token(onk::Word, TRY_POPX(lex, otk::TextSrcBegin)); // lang

        { // header args
            empty();
        }
        start(onk::CodeLine); // body
        {
            int balance = 1;
            TRY_SKIP(lex, otk::CurlyBegin);
            while (!lex.finished() && 0 < balance) {
                if (lex.at(otk::CurlyEnd)) {
                    if (balance == 1) {
                        TRY_SKIP(lex, otk::CurlyEnd);
                    } else {
                        token(onk::CodeText, pop(lex));
                    }
                    --balance;
                } else {
                    token(onk::CodeText, pop(lex));
                }
            }
        }
        end();
    }
    empty(); // TODO Parse result call
    return ParseOk{};
}

OrgParser::ParseResult OrgParser::parseVerbatimOrMonospace(OrgLexer& lex) {
    __perf_trace("parsing", "parseVerbatimOrMonospace");
    auto __trace = trace(lex);
    bool m       = lex.kind() == otk::MonospaceBegin;

    auto postBeginLex = lex.getPos();
    auto start_node   = start(m ? onk::Monospace : onk::Verbatim);
    auto begin_token  = pop(
        lex, m ? otk::MonospaceBegin : otk::VerbatimBegin);

    int  newlineCount = 0;
    bool foundEnd     = false;

    while (!lex.finished() && !foundEnd) {
        switch (lex.kind()) {
            case otk::VerbatimEnd:
            case otk::MonospaceEnd: {
                if (lex.at(m ? otk::MonospaceEnd : otk::VerbatimEnd)) {
                    foundEnd = true;
                } else {
                    token(onk::RawText, pop(lex));
                }

                break;
            }
            case otk::Newline: {
                if (2 < newlineCount) {
                    foundEnd = true;
                } else {
                    ++newlineCount;
                    token(onk::RawText, pop(lex));
                }
                break;
            }

            case otk::Placeholder: {
                SUB_PARSE(Placeholder, lex, "Failed to parse placeholder");
                break;
            }
            default: {
                token(onk::RawText, pop(lex));
            }
        }
    }

    if (lex.at(m ? otk::MonospaceEnd : otk::VerbatimEnd)) {
        skip(lex);
        return ParseOk{};
    } else {
        if (TraceState) {
            print(
                fmt("Reset monospace parse position. Removing tail at {}, "
                    "moving lexer from {} to {}",
                    start_node,
                    lex.getPos(),
                    postBeginLex));
        }

        end();
        group->removeTail(start_node);
        lex.setPos(postBeginLex);
        token(onk::Punctuation, pop(lex));
        return ParseOk{};
    }
}

OrgParser::ParseResult OrgParser::parseAngleTarget(OrgLexer& lex) {
    bool            radio = lex.kind() == otk::TripleAngleBegin;
    const OrgTokSet AngleTargetContent{
        otk::RawText,
        otk::Whitespace,
        otk::Word,
        otk::BigIdent,
    };

    auto end   = radio ? otk::TripleAngleEnd : otk::DoubleAngleEnd;
    auto begin = radio ? otk::TripleAngleBegin : otk::DoubleAngleBegin;

    if (lex.ahead(OrgTokSet{otk::Whitespace, otk::Word, begin}, end)) {
        TRY_SKIP(lex, begin);
        start(onk::RadioTarget);
        while (lex.can_search(end)) {
            switch (lex.kind()) {
                case otk::RawText: token(onk::RawText, pop(lex)); break;
                case otk::Whitespace: token(onk::Space, pop(lex)); break;
                case otk::Word: token(onk::Word, pop(lex)); break;
                case otk::BigIdent: token(onk::BigIdent, pop(lex)); break;
                default:
            }
        }
        TRY_SKIP(lex, end);
        return this->end();
    } else {
        return token(onk::Punctuation, pop(lex));
    }
}


OrgParser::ParseResult OrgParser::parseTable(OrgLexer& lex) {
    __perf_trace("parsing", "parseTable");
    auto __trace = trace(lex);
    start(onk::Table);


    auto parse_pipe_row = [&]() -> ParseResult {
        start(onk::TableRow);
        empty();              // no row parameters
        empty();              // no row-level text
        start(onk::StmtList); // List of rows

        while (lex.at(OrgTokSet{otk::LeadingPipe, otk::Pipe})) {
            start(onk::TableCell);
            empty();              // No cell parameters
            start(onk::StmtList); // Cell content
            SubLexer sub{lex};
            skip(lex);
            OrgTokSet CellEnd{otk::Pipe, otk::TrailingPipe};
            OrgTokSet CellStart{otk::Pipe, otk::LeadingPipe};
            while (lex.can_search(CellEnd)) {
                if (lex.at(otk::Whitespace)
                    && (lex.at(CellEnd, +1) || lex.at(CellStart, -1))) {
                    lex.next();
                } else {
                    sub.add(pop(lex));
                }
            }
            if (sub.empty()) {
                start(onk::Paragraph);
                end();
            } else {
                sub.start();
                SUB_PARSE(
                    Paragraph, sub, "Failed to parse table cell content.");
            }

            end();
            end();
        }
        BOOST_OUTCOME_TRY(
            skip(lex, otk::TrailingPipe, __LINE__, "parse_pipe_row"));
        if (lex.at(Newline)) { skip(lex); }

        end();
        end();
    };

    Vec<otk> TableEnd{otk::CmdPrefix, otk::CmdTableEnd};

    if (lex.at(OrgTokSet{otk::LeadingPipe, otk::TableSeparator})) {
        empty(); // No table command arguments for a pipe table
        while (lex.at(OrgTokSet{otk::LeadingPipe, otk::TableSeparator})) {
            switch (lex.kind()) {
                case otk::LeadingPipe: {
                    parse_pipe_row();
                    break;
                }
                case otk::TableSeparator: {
                    lex.next();
                    newline(lex);
                    break;
                }
                default: {
                }
            }
        }
    } else {
        TRY_SKIP(lex, otk::CmdPrefix);
        TRY_SKIP(lex, otk::CmdTableBegin);
        SUB_PARSE(
            CommandArguments,
            lex,
            "Failed to parse command arguments for table block.");
        newline(lex);

        while (lex.can_search(TableEnd)) {
            switch (lex.kind()) {
                case otk::LeadingPipe: {
                    parse_pipe_row();
                    break;
                }
                case otk::CmdPrefix: {
                    TRY_SKIP(lex, otk::CmdPrefix);
                    TRY_SKIP(lex, otk::CmdRow);
                    start(onk::TableRow);
                    SUB_PARSE(
                        CommandArguments,
                        lex,
                        "Failed to parse command arguments for table row");
                    empty();
                    newline(lex);

                    start(onk::StmtList);
                    if (lex.at(otk::LeadingPipe)) {
                        while (lex.at(otk::LeadingPipe)) {
                            TRY_SKIP(lex, otk::LeadingPipe);
                            space(lex);
                            start(onk::TableCell);
                            {
                                empty();
                                start(onk::StmtList);
                                {
                                    auto sub = subToEol(lex);
                                    if (sub.empty()) {
                                        empty();
                                    } else {
                                        SUB_PARSE(
                                            Paragraph,
                                            sub,
                                            "Failed to parse command "
                                            "arguments for table cell");
                                    }
                                }
                                end();
                            }
                            end();
                            newline(lex);
                        }
                    } else {
                        while (lex.at(Vec{otk::CmdPrefix, otk::CmdCell})) {
                            TRY_SKIP(lex, otk::CmdPrefix);
                            TRY_SKIP(lex, otk::CmdCell);
                            start(onk::TableCell);
                            {
                                SUB_PARSE(
                                    CommandArguments,
                                    lex,
                                    "Failed to parse command arguments "
                                    "for table cell");
                                start(onk::StmtList);
                                {
                                    while (
                                        !(lex.at(otk::CmdPrefix)
                                          && lex.at(
                                              OrgTokSet{
                                                  otk::CmdCell,
                                                  otk::CmdRow,
                                                  otk::CmdTableEnd},
                                              +1))) {
                                        SUB_PARSE(
                                            StmtListItem,
                                            lex,
                                            "Failed to parse cell item in "
                                            "table block");
                                    }
                                }
                                end();
                            }
                            end();
                        }
                    }

                    end();
                    end();

                    break;
                }
                default: {
                    throw fatalError(
                        lex,
                        "Expected cmd row or leading pipe in the block "
                        "table");
                }
            }
        }


        TRY_SKIP(lex, otk::CmdPrefix);
        TRY_SKIP(lex, otk::CmdTableEnd);
    }


    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseParagraph(OrgLexer& lex) {
    start(onk::Paragraph);
    parseText(lex);
    end();
    return ParseOk{};
}

OrgParser::ParseResult OrgParser::parseInlineExport(OrgLexer& lex) {
    start(onk::InlineExport);
    token(onk::RawText, TRY_POPX(lex, otk::InlineExportBackend));
    token(onk::RawText, TRY_POPX(lex, otk::InlineExportContent));
    return ParseOk{};
}

OrgParser::ParseResult OrgParser::parseCriticMarkup(OrgLexer& lex) {
    __perf_trace("parsing", "parseCriticMarkup");
    auto __trace = trace(lex);
    otk  e;
    switch (lex.kind()) {
        case otk::CriticDeleteBegin: e = otk::CriticDeleteEnd; break;
        case otk::CriticAddBegin: e = otk::CriticAddEnd; break;
        case otk::CriticCommentBegin: e = otk::CriticCommentEnd; break;
        case otk::CriticReplaceBegin: e = otk::CriticReplaceEnd; break;
        case otk::CriticHighlightBegin: e = otk::CriticHighlightEnd; break;
        default: {
        }
    }

    start(onk::CriticMarkStructure);
    token(onk::RawText, pop(lex));
    if (e == otk::CriticReplaceEnd) {
        SubLexer sub{lex};
        while (lex.can_search(otk::CriticReplaceMiddle)) {
            sub.add(lex.pop());
        }

        if (sub.empty()) {
            empty();
        } else {
            sub.start();
            SUB_PARSE(
                Paragraph, sub, "Failed to parse critic markup body");
        }
        TRY_SKIP(lex, otk::CriticReplaceMiddle);
    } else {
        empty();
    }

    SubLexer sub{lex};
    while (lex.can_search(e)) { sub.add(lex.pop()); }

    sub.start();
    SUB_PARSE(Paragraph, sub, "Failed to parse critic markup body");
    TRY_SKIP(lex, e);
    return ParseOk{};
}

OrgParser::ParseResult OrgParser::parseCommandArguments(OrgLexer& lex) {
    __perf_trace("parsing", "parseCommandArguments");
    auto __trace = trace(lex);
    space(lex);
    start(onk::InlineStmtList);
    while (lex.at(OrgTokSet{otk::CmdRawArg, otk::CmdColonIdent})) {
        SUB_PARSE(AttrValue, lex, "Failed to parse command arguments");
        space(lex);
    }

    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseSrcArguments(OrgLexer& lex) {
    __perf_trace("parsing", "parseSrcArguments");
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(Newline)) {
        empty();
        empty();
        return ParseOk{};
    } else {
        start(onk::Attrs);
        start(onk::InlineStmtList);
        {
            while (lex.at(otk::CmdFlag)) {
                token(onk::CmdFlag, TRY_POPX(lex, otk::CmdFlag));
            }
        }
        end();
        SUB_PARSE(CommandArguments, lex, "Failed to parse SRC arguments");
        return ParseOk{};
    }
}


OrgParser::ParseResult OrgParser::parseTextWrapCommand(OrgLexer& lex) {
    __perf_trace("parsing", "parseTextWrapCommand");
    TRY_SKIP(lex, otk::CmdPrefix);
    auto __trace = trace(lex);

    bool isDynamic = lex.kind() == otk::CmdDynamicBlockBegin;

    OrgTokenKind endTok;
    switch (lex.kind()) {
        case otk::CmdVerseBegin:
            start(onk::BlockVerse);
            endTok = otk::CmdVerseEnd;
            break;
        case otk::CmdCenterBegin:
            start(onk::BlockCenter);
            endTok = otk::CmdCenterEnd;
            break;
        case otk::CmdQuoteBegin:
            start(onk::BlockQuote);
            endTok = otk::CmdQuoteEnd;
            break;
        case otk::CmdCommentBegin:
            start(onk::BlockComment);
            endTok = otk::CmdCommentEnd;
            break;
        case otk::CmdDynamicBlockBegin:
            start(onk::BlockDynamicFallback);
            token(onk::Word, lex.get());
            endTok = otk::CmdDynamicBlockEnd;
            break;
        default: throw fatalError(lex, "unhandled token");
    }

    std::string tmp = lex.val().text;
    skip(lex);

    if (lex.at(Newline)) {
        empty();
    } else {
        space(lex);
        SUB_PARSE(
            CommandArguments,
            lex,
            "Failed to parse text wrap command arguments");
        space(lex);
    }

    TRY_SKIP(lex, Newline);

    if (isDynamic) {
        hstd::replace_all(tmp, "begin", "end");
        Str endName = normalize(tmp);
        print(fmt("Dynamic block, name {}", endName));
        while (lex.can_search(Vec<otk>{otk::CmdPrefix, endTok})
               && lex.hasNext(2)
               && normalize(lex.val(1).text) != endName) {
            SUB_PARSE(
                StmtListItem,
                lex,
                "Failed to parse dynamic block arguments");
            if (lex.at(BlockTerminator)) {
                print(fmt("block terminator {}", lex));
                break;
            }
        }
    } else {
        while (lex.can_search(Vec<otk>{otk::CmdPrefix, endTok})) {
            SUB_PARSE(
                StmtListItem,
                lex,
                "Failed to parse statement in the text block body");
            if (lex.at(BlockTerminator)) {
                print(fmt("block terminator {}", lex));
                break;
            }
        }
    }

    TRY_SKIP(lex, otk::CmdPrefix);
    TRY_SKIP(lex, endTok);
    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseBlockExport(OrgLexer& lex) {
    __perf_trace("parsing", "parseExample");
    auto __trace = trace(lex);
    start(onk::BlockExport);

    TRY_SKIP(lex, otk::CmdPrefix);
    TRY_SKIP(lex, otk::CmdExportBegin);

    // command arguments
    space(lex);
    token(onk::Word, TRY_POPX(lex, otk::CmdRawArg));
    space(lex);
    SUB_PARSE(
        CommandArguments,
        lex,
        "Failed to parse command arguments for export block");
    newline(lex);

    // command content
    start(onk::StmtList);
    while (lex.at(OrgTokSet{otk::CmdExportLine, otk::Newline})) {
        token(onk::RawText, pop(lex));
    }
    end();

    TRY_SKIP(lex, otk::CmdPrefix);
    TRY_SKIP(lex, otk::CmdExportEnd);

    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseColonExample(OrgLexer& lex) {
    __perf_trace("parsing", "parseColonExample");

    auto __trace = trace(lex);


    start(onk::ColonExample);
    while (lex.at(OrgTokSet{otk::ColonExampleLine, otk::Colon})) {
        if (lex.at(otk::ColonExampleLine)) {
            token(onk::RawText, pop(lex));
        } else {
            empty();
            TRY_SKIP(lex, otk::Colon);
        }

        if (lex.at(otk::Newline)) { skip(lex); }
    }

    return ParseOk{};
}

OrgParser::ParseResult OrgParser::parseExample(OrgLexer& lex) {
    __perf_trace("parsing", "parseExample");
    auto __trace = trace(lex);
    start(onk::BlockExample);

    TRY_SKIP(lex, otk::CmdPrefix);
    TRY_SKIP(lex, otk::CmdExampleBegin);

    { // command arguments
        SUB_PARSE(
            CommandArguments,
            lex,
            "Failed to parse command arguments for example command");
        newline(lex);
    }

    { // command content
        while (lex.at(OrgTokSet{otk::CmdExampleLine, otk::Newline})) {
            if (lex.at(Vec{otk::Newline, otk::CmdPrefix})) {
                skip(lex);
            } else {
                token(onk::RawText, pop(lex));
            }
        }
    }

    TRY_SKIP(lex, otk::CmdPrefix);
    TRY_SKIP(lex, otk::CmdExampleEnd);

    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseSrc(OrgLexer& lex) {
    __perf_trace("parsing", "parseSrc");
    auto __trace = trace(lex);
    start(onk::BlockCode);
    TRY_SKIP(lex, otk::CmdPrefix);
    TRY_SKIP(lex, otk::CmdSrcBegin);
    // header_args_lang
    {
        space(lex);
        if (lex.at(otk::CmdRawArg)) {
            if (lex.val().text.empty()) {
                empty();
            } else {
                token(onk::Word, TRY_POPX(lex, otk::CmdRawArg));
            }
        } else {
            empty();
        }

        space(lex);

        SUB_PARSE(
            SrcArguments,
            lex,
            "Failed to parse command arguments for source block");
    };
    // body
    {

        start(onk::StmtList);
        TRY_SKIP(lex, otk::CmdContentBegin);
        while (lex.can_search(Vec{otk::CmdPrefix, otk::CmdSrcEnd})) {
            start(onk::CodeLine);
            while (lex.can_search(
                OrgTokSet{otk::CmdContentEnd, otk::Newline})) {
                switch (lex.kind()) {
                    case otk::SrcContent: {
                        token(
                            onk::CodeText, TRY_POPX(lex, otk::SrcContent));
                        break;
                    }
                    case otk::ParBegin: {
                        TRY_SKIP(lex, otk::ParBegin);
                        TRY_SKIP(lex, otk::Word);
                        TRY_SKIP(lex, otk::Colon);
                        start(onk::CodeCallout);
                        token(onk::Word, TRY_POPX(lex, otk::Word));
                        end();
                        TRY_SKIP(lex, otk::ParEnd);
                        break;
                    }
                    case otk::DoubleAngleBegin: {
                        bool hasClose = false;
                        for (int offset = 0; lex.hasNext(offset);
                             ++offset) {
                            if (lex.at(otk::DoubleAngleEnd, offset)) {
                                hasClose = true;
                                break;
                            } else if (lex.at(otk::Newline, offset)) {
                                break;
                            }
                        }
                        if (hasClose) {
                            TRY_SKIP(lex, otk::DoubleAngleBegin);
                            start(onk::CodeTangle);
                            SUB_PARSE(
                                CSVArguments,
                                lex,
                                "Failed to parse arguments for source "
                                "code block tangle.");
                            end();
                            TRY_SKIP(lex, otk::DoubleAngleEnd);
                        } else {
                            token(
                                onk::CodeText,
                                TRY_POPX(lex, otk::DoubleAngleBegin));
                        }
                        break;
                    }
                    case otk::DoubleAngleEnd: {
                        token(
                            onk::CodeText,
                            TRY_POPX(lex, otk::DoubleAngleEnd));
                        break;
                    }
                    default: {
                        throw fatalError(
                            lex,
                            fmt("Unhandled code parse token {}",
                                lex.tok()));
                    }
                }
            }
            if (lex.at(otk::Newline)) { skip(lex); }
            end(); // finish code line
        }

        end(); // finish statement
    };

    TRY_SKIP(lex, otk::CmdPrefix);
    TRY_SKIP(lex, otk::CmdSrcEnd);


    // eval_result
    if (lex.ahead(
            Newline + OrgTokSet{otk::Whitespace},
            Vec<OrgTokenKind>{
                otk::CmdPrefix,
                otk::CmdResults,
            })) {
        while (!lex.at(otk::CmdPrefix)) {
            space(lex);
            newline(lex);
        }
        TRY_SKIP(lex, otk::CmdPrefix);
        TRY_SKIP(lex, otk::CmdResults);
        start(onk::CmdResults);
        space(lex);
        SUB_PARSE(
            CommandArguments,
            lex,
            "Failed to parse arguments for source code block result "
            "spec");
        newline(lex);
        if (!lex.at(otk::SubtreeStars)) {
            SUB_PARSE(
                StmtListItem,
                lex,
                "Failed to parse subtree block result statment");
        } else {
            empty();
        }
        end();
    } else {
        empty();
    }

    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseListItem(OrgLexer& lex) {
    __perf_trace("parsing", "parseListItem");
    auto __trace = trace(lex);
    start(onk::ListItem);
    // prefix, 0
    { token(onk::RawText, TRY_POPX(lex, ListStarts)); }
    space(lex);
    // counter, 1
    {
        empty(); // TODO parse counter
    }
    // checkbox 2
    {
        if (lex.at(otk::Checkbox)) {
            token(onk::Checkbox, TRY_POPX(lex, otk::Checkbox));
            space(lex);
        } else {
            empty();
        }
    }
    // tag, 3
    {
        // Search ahead for the description list tag
        Lexer<OrgTokenKind, OrgFill> tmp{lex.in};
        tmp.pos                  = lex.pos;
        auto const colon_pattern = Vec<otk>{
            otk::Whitespace,
            otk::DoubleColon,
            otk::Whitespace,
        };

        while (tmp.can_search(colon_pattern)) {
            if (tmp.at(Newline)) { break; }
            tmp.next();
        }

        if (tmp.finished()) {
            print("Sub-lexer reached end without header");
        } else {
            print(fmt(
                "Searched for double colon to {} tmp-pos {} lex-pos {}",
                tmp.tok(),
                tmp.pos,
                lex.pos));
        }

        if (tmp.at(colon_pattern)) {
            SubLexer sub{lex};

            while (lex.can_search(colon_pattern)) { sub.add(lex.pop()); }

            if (sub.empty()) {
                empty();
            } else {
                sub.start();
                SUB_PARSE(Paragraph, sub, "Failed to parse list item");
                lex.skip(otk::Whitespace);
                lex.skip(otk::DoubleColon);
                space(lex);
            }
        } else {
            empty();
        }
    }
    // body, 5
    start(onk::StmtList);
    {
        while (lex.can_search(
            OrgTokSet{otk::Dedent, otk::SameIndent, otk::ListItemEnd})) {
            SUB_PARSE(
                StmtListItem,
                lex,
                "Failed to parse statement in the list body");
        }
    }

    if (lex.at(otk::ListItemEnd)) { skip(lex); }

    end();
    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseList(OrgLexer& lex) {
    __perf_trace("parsing", "parseList");
    auto __trace = trace(lex);
    start(onk::List);

    print(fmt("{}", lex.tok()));

    while (lex.at(ListStarts)
           || (lex.at(otk::LeadingSpace) && lex.at(ListStarts, +1))) {
        SUB_PARSE(ListItem, lex, "Failed to parse list item in the list");
        if (lex.at(otk::SameIndent)) { skip(lex); }
    }

    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseSubtreeLogbook(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtreeLogbook");
    auto __trace = trace(lex);
    start(onk::DrawerLogbook);
    TRY_SKIP(lex, otk::ColonLogbook);
    newline(lex);

    space(lex);

    TRY_SKIP(lex, otk::Indent);
    SUB_PARSE(List, lex, "Failed to parse subtree logbook");
    if (lex.at(otk::StmtListEnd)) {
        TRY_SKIP(lex, otk::StmtListEnd);
        TRY_SKIP(lex, otk::ListItemEnd);
    }
    TRY_SKIP(lex, otk::Dedent);

    space(lex);
    TRY_SKIP(lex, otk::ColonEnd);
    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseSubtreeProperties(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtreeProperties");
    auto __trace = trace(lex);
    TRY_SKIP(lex, otk::ColonProperties);
    TRY_SKIP(lex, otk::Newline);
    start(onk::DrawerPropertyList);
    while (lex.can_search(otk::ColonEnd)) {
        trace(lex, "Parse single subtree property");
        start(onk::DrawerProperty);
        auto head = lex.kind();
        token(onk::RawText, TRY_POPX(lex, head));
        switch (head) {
            case otk::ColonLiteralProperty: {
                token(onk::RawText, TRY_POPX(lex, otk::RawText));
                break;
            }

            case otk::ColonArgumentsProperty: {
                SUB_PARSE(
                    CommandArguments,
                    lex,
                    "Failed to parse arguments for subtree property");
                break;
            }

            case otk::ColonPropertyText: {
                space(lex);
                SubLexer sub{lex};
                while (lex.can_search(Newline)) { sub.add(lex.pop()); }
                sub.start();
                SUB_PARSE(
                    Paragraph,
                    sub,
                    "Failed to parse text for subtree property");
                break;
            }
            default: {
                throw fatalError(
                    lex, fmt("Unhandled property kind parse {}", head));
            }
        }
        TRY_SKIP(lex, otk::Newline);
        end();
    }

    TRY_SKIP(lex, otk::ColonEnd);
    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseSubtreeDrawer(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtreeDrawer");
    auto __trace = trace(lex);
    start(onk::Drawer);

    while (lex.at(OrgTokSet{otk::ColonProperties, otk::ColonLogbook})) {
        switch (lex.tok().kind) {
            case otk::ColonProperties:
                SUB_PARSE(
                    SubtreeProperties,
                    lex,
                    "Failed to parse subtree properties");
                break;
            case otk::ColonLogbook:
                SUB_PARSE(
                    SubtreeLogbook,
                    lex,
                    "Failed to parse subtree logbook");
                break;
            default:
        }

        newline(lex);
        space(lex);
    }

    return ParseOk{};
}

void tokenFormat(ColStream& os, OrgToken const& t) { os << t->text; }

OrgParser::ParseResult OrgParser::parseSubtreeCompletion(OrgLexer& lex) {
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(otk::SubtreeCompletion)) {
        token(
            onk::SubtreeCompletion, TRY_POPX(lex, otk::SubtreeCompletion));
    } else {
        empty();
    }

    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseSubtreeTodo(OrgLexer& lex) {
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(
            Vec{otk::BigIdent, otk::Whitespace, otk::SubtreePriority})) {
        token(onk::BigIdent, TRY_POPX(lex, otk::BigIdent));
    } else {
        empty();
    }

    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseSubtreeUrgency(OrgLexer& lex) {
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(otk::SubtreePriority)) {
        token(onk::SubtreeUrgency, TRY_POPX(lex, otk::SubtreePriority));
    } else {
        empty();
    }

    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseSubtreeTitle(OrgLexer& lex) {
    auto __trace = trace(lex);
    space(lex);
    SubLexer sub{lex};


    auto is_at_subtree_tags = [](OrgLexer& lex) {
        const IntSet<OrgTokenKind> tree_tags{
            otk::Colon,
            otk::Word,
            otk::DoubleHash,
            otk::At,
            otk::BigIdent,
        };

        if (!lex.at(otk::Colon)) { return false; }

        auto ahead = lex.whole_fixed().range_current()
                   | rv::take_while([&](OrgToken const& t) -> bool {
                         return tree_tags.contains(t.kind);
                     })
                   | rs::to<std::vector>;

        auto tag_end = lex.begin() + ahead.size();
        return tag_end == lex.whole_fixed().end()
            || Newline.contains(tag_end->kind);
    };

    while (lex.can_search(Newline)     //
           && !is_at_subtree_tags(lex) //
           && !lex.at(otk::SubtreeCompletion)) {
        sub.add(pop(lex));
    }

    if (sub.empty()) {
        empty();
    } else {
        sub.start();
        SUB_PARSE(Paragraph, sub, "Failed to parse subtree title");
    }

    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseSubtreeTags(OrgLexer& lex) {
    auto __trace = trace(lex);
    if (lex.at(otk::Colon)) {
        start(onk::InlineStmtList);
        while (
            lex.at(otk::Colon)
            && lex.at(OrgTokSet{otk::Word, otk::At, otk::BigIdent}, +1)) {
            TRY_SKIP(lex, otk::Colon);
            SUB_PARSE(HashTag, lex, "Failed to parse subtree tags");
        }
        TRY_SKIP(lex, OrgTokSet{otk::Colon} + Newline);
        return ParseOk{};
    } else {
        empty();
        return ParseOk{};
    }
}


OrgParser::ParseResult OrgParser::parseSubtreeTimes(OrgLexer& lex) {
    auto __trace = trace(lex);
    if ((lex.at(otk::LeadingSpace) && lex.at(otk::TreeTime, +1))
        || lex.at(otk::TreeTime)) {
        space(lex);
        start(onk::StmtList);
        while (lex.at(otk::TreeTime)
               || (lex.at(otk::Newline) && lex.at(otk::TreeTime, +1))) {
            newline(lex);
            start(onk::InlineStmtList);
            token(onk::Word, pop(lex));
            space(lex);
            SUB_PARSE(TimeRange, lex, "Failed to parse subtree times");
            space(lex);
            end();
        }

        // Optional standalone timestamp or time range right after the
        // subtree. The check is for token sequence
        // <newline> <space>? <angle/brace> <date>
        auto [it, lex_end] = lex.whole_fixed().range_current();
        if (it != lex_end && it->kind == otk::Newline) {
            ++it;
            if (it == lex_end) { goto not_a_timestamp; }
            if (it->kind == otk::LeadingSpace) { ++it; }
            if (it == lex_end) { goto not_a_timestamp; }
            if (it->kind != otk::AngleBegin
                && it->kind != otk::BraceBegin) {
                goto not_a_timestamp;
            }

            ++it;

            if (it == lex_end) { goto not_a_timestamp; }
            if (it->kind == otk::Date) {
                lex.skip(otk::Newline);
                space(lex);
                start(onk::InlineStmtList);
                empty();
                SUB_PARSE(
                    TimeRange, lex, "Failed to parse subtree time range");
                space(lex);
                end();
            }

        not_a_timestamp:
        }

    } else {
        empty();
    }
    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseSubtree(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtree");
    auto __trace = trace(lex);
    start(onk::Subtree);
    // prefix

    token(onk::RawText, TRY_POPX(lex, otk::SubtreeStars));             // 0
    SUB_PARSE(SubtreeTodo, lex, "Failed to parse subtree todo");       // 1
    SUB_PARSE(SubtreeUrgency, lex, 'Failed to parse subtree urgency'); // 2
    space(lex);                                                        //
    SUB_PARSE(SubtreeTitle, lex, "Failed to parse subtree title");     // 3
    SUB_PARSE(
        SubtreeCompletion, lex, "Failed to parse subtree completion"); // 4
    space(lex);
    SUB_PARSE(SubtreeTags, lex, "Failed to parse subtree tags"); // 5

    if (lex.at(otk::Newline)) { newline(lex); }
    SUB_PARSE(SubtreeTimes, lex, "Failed to parse subtree times"); // 6


    if (lex.at(otk::Newline)) { newline(lex); }

    if (lex.at(OrgTokSet{otk::ColonProperties, otk::ColonLogbook})) { // 7
        SUB_PARSE(SubtreeDrawer, lex, "Failed to parse subtree drawer");
    } else {
        empty();
    }

    newline(lex);

    start(onk::StmtList); // 8
    end();
    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseOrgFile(OrgLexer& lex) {
    __perf_trace("parsing", "parseOrgFile");
    auto __trace = trace(lex);
    start(onk::File);
    logic_todo_impl();
    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseLineCommand(OrgLexer& lex) {
    __perf_trace("parsing", "parseLineCommand");
    auto __trace  = trace(lex);
    auto cmd_kind = lex.kind(+1);

    OrgTokSet raw_arg_cmd_value{
        otk::CmdRawArg,
        otk::BraceBegin,
        otk::BraceEnd,
        otk::Comma,
        otk::Equals,
        otk::RawText,
    };

    auto get_cmd_arguments = [&]() -> ParseResult {
        start(onk::InlineStmtList);
        while (lex.at(raw_arg_cmd_value)) {
            token(onk::RawText, TRY_POPX(lex, raw_arg_cmd_value));
        }
        end();
    };

    switch (cmd_kind) {
        case otk::CmdEmailRaw:
        case otk::CmdBindRaw:
        case otk::CmdCategoryRaw:
        case otk::CmdSetupfileRaw:
        case otk::CmdPrioritiesRaw:
        case otk::CmdSeqTodoRaw:
        case otk::CmdTagsRaw:
        case otk::CmdMacroRaw:
        case otk::CmdLinkRaw:
        case otk::CmdLatexHeaderExtraRaw:
        case otk::CmdExcludeTagsRaw:
        case otk::CmdSelectTagsRaw:
        case otk::CmdDrawersRaw:
        case otk::CmdConstants:
        case otk::CmdCustomRaw: {
            start(onk::CmdCustomRawCommand);
            TRY_SKIP(lex, otk::CmdPrefix);
            token(onk::RawText, TRY_POPX(lex, cmd_kind));
            space(lex);
            while (lex.at(otk::RawText)) {
                token(onk::RawText, TRY_POPX(lex, otk::RawText));
                if (lex.at(otk::Whitespace)) { space(lex); }
            }
            break;
        }

        case otk::CmdDateRaw:
        case otk::CmdDescription: {
            TRY_SKIP(lex, otk::CmdPrefix);
            start(onk::CmdCustomTextCommand);
            token(onk::RawText, TRY_POPX(lex, cmd_kind));
            space(lex);
            start(onk::Attrs);
            auto sub = subToEol(
                lex, ParagraphTerminator + OrgTokSet{otk::Newline});
            if (sub.empty()) {
                empty();
            } else {
                SUB_PARSE(
                    Paragraph,
                    sub,
                    "Failed to parse description paragraph");
            }
            end();
            break;
        }

        case otk::CmdHtmlHeadRaw: {
            TRY_SKIP(lex, otk::CmdPrefix);
            start(onk::CmdCustomArgsCommand);
            token(onk::RawText, TRY_POPX(lex, cmd_kind));
            space(lex);
            SUB_PARSE(
                CommandArguments,
                lex,
                "Failed to parse HTML header for the document.");
            break;
        }

        case otk::CmdCall: {
            start(onk::CmdCallCode);
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, otk::CmdCall);
            space(lex);
            // Name
            token(onk::Word, TRY_POPX(lex, otk::CmdRawArg));
            space(lex);

            // HeaderArgs
            if (lex.at(otk::BraceBegin)) {
                TRY_SKIP(lex, otk::BraceBegin);
                SUB_PARSE(
                    CommandArguments,
                    lex,
                    "Failed to parse CALL command header args.");
                TRY_SKIP(lex, otk::BraceEnd);
            } else {
                empty();
            }

            space(lex);

            // Args
            if (lex.at(otk::ParBegin)) {
                SUB_PARSE(
                    CallArguments,
                    lex,
                    "Failed to parse CALL command arguments.");
            } else {
                empty();
            }

            space(lex);

            // EndArgs
            SUB_PARSE(
                CommandArguments,
                lex,
                "Failed to parse CALL command end arguments.");

            break;
        }

        case otk::CmdTitle:
        case otk::CmdCaption: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, cmd_kind);
            space(lex);
            if (cmd_kind == otk::CmdTitle) {
                start(onk::CmdTitle);
            } else {
                start(onk::CmdCaption);
            }
            start(onk::Attrs);
            auto sub = subToEol(
                lex, ParagraphTerminator + OrgTokSet{otk::Newline});
            if (sub.empty()) {
                empty();
            } else {
                SUB_PARSE(
                    Paragraph, sub, "Failed to parse title/caption text.");
            }
            end();
            break;
        }

        case otk::CmdCreator:
        case otk::CmdAuthor:
        case otk::CmdLatexHeader:
        case otk::CmdStartup:
        case otk::CmdLanguage: {
            switch (cmd_kind) {
                case otk::CmdCreator: start(onk::CmdCreator); break;
                case otk::CmdLanguage: start(onk::CmdLanguage); break;
                case otk::CmdAuthor: start(onk::CmdAuthor); break;
                case otk::CmdOptions: start(onk::CmdOptions); break;
                case otk::CmdLatexHeader:
                    start(onk::CmdLatexHeader);
                    break;
                case otk::CmdInclude: start(onk::CmdInclude); break;
                case otk::CmdColumns: start(onk::CmdColumns); break;
                case otk::CmdStartup: start(onk::CmdStartup); break;
                default: throw fatalError(lex, "");
            }

            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, cmd_kind);
            space(lex);
            while (lex.at(OrgTokSet{otk::RawText, otk::CmdRawArg})) {
                token(onk::RawText, pop(lex));
                space(lex);
            }
            break;
        }

        case otk::CmdFiletags: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, otk::CmdFiletags);
            space(lex);
            start(onk::CmdFiletags);
            while (lex.at(OrgTokSet{otk::Word, otk::BigIdent}, +1)) {
                if (lex.at(otk::Colon)) {
                    skip(lex);
                } else {
                    space(lex);
                }
                SUB_PARSE(
                    HashTag,
                    lex,
                    "Failed to parse hashtag in the FILETAGS command");
                space(lex);
            }
            if (lex.at(otk::Colon)) { skip(lex); }
            break;
        }


        case otk::CmdLatexClass:
        case otk::CmdLatexCompiler: {
            TRY_SKIP(lex, otk::CmdPrefix);
            switch (cmd_kind) {
                case otk::CmdLatexCompiler: {
                    start(onk::CmdLatexCompiler);
                    TRY_SKIP(lex, otk::CmdLatexCompiler);
                    break;
                }
                case otk::CmdLatexClass: {
                    start(onk::CmdLatexClass);
                    TRY_SKIP(lex, otk::CmdLatexClass);
                    break;
                }
                default:
            }

            space(lex);
            token(onk::Word, TRY_POPX(lex, otk::CmdRawArg));
            break;
        }


        case otk::CmdLatexClassOptions: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, otk::CmdLatexClassOptions);
            space(lex);
            start(onk::CmdLatexClassOptions);
            get_cmd_arguments();
            break;
        }

        case otk::CmdPropertyRaw: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, cmd_kind);
            space(lex);
            start(onk::CmdPropertyRaw);
            token(onk::RawText, TRY_POPX(lex, otk::RawText));
            break;
        }

        case otk::CmdPropertyText: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, cmd_kind);
            space(lex);
            start(onk::CmdPropertyArgs);
            token(onk::RawText, TRY_POPX(lex, otk::CmdRawArg));
            SUB_PARSE(CommandArguments, lex);
            SUB_PARSE(Paragraph, lex);
            break;
        }

        case otk::CmdInclude: {
            start(onk::CmdInclude);
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, otk::CmdInclude);
            space(lex);
            SUB_PARSE(CommandArguments, lex);
            break;
        }

        case otk::CmdAttr: {
            start(onk::CmdAttr);
            TRY_SKIP(lex, otk::CmdPrefix);
            token(onk::Word, TRY_POPX(lex, otk::CmdAttr));
            space(lex);
            SUB_PARSE(
                CommandArguments,
                lex,
                "Failed to parse arguments for the ATTR command.");
            break;
        }

        case otk::CmdName:
        case otk::CmdResults:
        case otk::CmdHeader: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, cmd_kind);
            switch (cmd_kind) {
                case otk::CmdHeader: start(onk::CmdHeader); break;
                case otk::CmdName: start(onk::CmdName); break;
                case otk::CmdResults: start(onk::CmdResults); break;
                default:
            }


            space(lex);
            SUB_PARSE(
                CommandArguments,
                lex,
                "Failed to parse arguments for the NAME/RESULTS/HEADER "
                "command");
            break;
        }


        case otk::CmdPropertyArgs: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, cmd_kind);
            space(lex);
            start(onk::CmdPropertyArgs);
            token(onk::RawText, TRY_POPX(lex, otk::CmdRawArg));
            SUB_PARSE(
                CommandArguments,
                lex,
                "Failed to parse arguments for the PROPERTY_ARGS "
                "command.");
            break;
        }

        case otk::CmdOptions: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, cmd_kind);
            space(lex);
            start(onk::CmdOptions);
            BOOST_OUTCOME_TRY(get_cmd_arguments());
            break;
        }

        case otk::CmdKeywordsRaw:
        case otk::CmdTblfm:
        case otk::CmdColumns: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, cmd_kind);
            space(lex);
            switch (cmd_kind) {
                case otk::CmdTblfm: start(onk::CmdTblfm); break;
                case otk::CmdColumns: start(onk::CmdColumns); break;
                case otk::CmdKeywordsRaw: start(onk::CmdKeywords); break;
                default: throw fatalError(lex, "asdf");
            }
            BOOST_OUTCOME_TRY(get_cmd_arguments());
            break;
        }


        default: {
            throw fatalError(
                lex, fmt("Unhandled command kind {}", lex.kind(+1)));
        }
    }

    newline(lex);

    // End main tree that was started in the case statement
    end();
    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseStmtListItem(OrgLexer& lex) {
    auto __trace = trace(lex);
    switch (lex.kind()) {
        case otk::SubtreeStars:
            return SUB_PARSEX(
                Subtree,
                lex,
                "Failed to parse subtree in the statement list.");
        case otk::Indent: {
            TRY_SKIP(lex, otk::Indent);
            auto result = SUB_PARSEX(
                List,
                lex,
                "Failed to parse top-level list in the statement list.");
            TRY_SKIP(lex, otk::Dedent);
            return result;
        }

        case otk::Whitespace:
            return token(onk::Space, TRY_POPX(lex, otk::Whitespace));

        case otk::MediumNewline:
        case otk::LongNewline:
        case otk::Newline: return token(onk::Newline, pop(lex));
        case otk::TextSeparator:
            return token(
                onk::TextSeparator, TRY_POPX(lex, otk::TextSeparator));

        case otk::TableSeparator:
        case otk::LeadingPipe: return SUB_PARSE(Table, lex);
        case otk::ColonExampleLine: return SUB_PARSE(ColonExample, lex);


        case otk::CmdPrefix: {
            switch (lex.kind(+1)) {
                case otk::CmdSrcBegin: return SUB_PARSE(Src, lex);
                case otk::CmdExampleBegin: return SUB_PARSE(Example, lex);
                case otk::CmdExportBegin:
                    return SUB_PARSE(BlockExport, lex);
                case otk::CmdVerseBegin:
                case otk::CmdCenterBegin:
                case otk::CmdCommentBegin:
                case otk::CmdDynamicBlockBegin:
                case otk::CmdQuoteBegin:
                    return SUB_PARSE(TextWrapCommand, lex);
                case otk::CmdTableBegin: return SUB_PARSE(Table, lex);
                default: return SUB_PARSE(LineCommand, lex);
            }
        }
        default: {
            SubLexer sub{lex};
            while (lex.can_search(ParagraphTerminator)) {
                sub.add(lex.pop());
            }

            sub.start();
            return parseParagraph(sub);
        }
    }
}


OrgParser::ParseResult OrgParser::parseTop(OrgLexer& lex) {
    __perf_trace("parsing", "parseTop");
    auto __trace = trace(lex);
    start(onk::StmtList);
    while (!lex.finished()) {
        if (lex.at(otk::Comment)) {
            skip(lex);
        } else {
            SUB_PARSE(
                StmtListItem,
                lex,
                "Failed to parse statement list item on the document "
                "top.");
        };
    }
    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseFull(OrgLexer& lex) {
    __perf_trace("parsing", "parseFull");
    auto __trace = trace(lex);
    SUB_PARSE(Top, lex, "Failed to parse top");
    extendSubtreeTrails(OrgId(0));
    return ParseOk{};
}


bool OrgParser::at(CR<OrgLexer> lex, CR<OrgExpectable> item) {
    if (item.index() == 0 && lex.at(std::get<0>(item))) {
        return true;
    } else if (item.index() == 1 && lex.at(std::get<1>(item))) {
        return true;
    } else if (item.index() == 2) {
        auto const& tokens = std::get<Vec<OrgTokenKind>>(item);
        for (int i = 0; i < tokens.size(); ++i) {
            if (!lex.at(tokens.at(i), i)) { return false; }
        }

        return true;
    } else {
        return false;
    }
}


void assertValidStructure(OrgNodeGroup* group, OrgId id) {
    using Id = OrgNodeGroup::Id;

    Func<void(Id)> aux;
    aux = [&](Id top) {
        auto& g = *group;
        LOGIC_ASSERTION_CHECK(g.nodes.contains(top), "");
        auto fmt_id = [&](CR<Id> id) {
            return fmt("{} {}", id.format(), g.at(id).kind);
        };
        if (g.at(top).isTerminal() || g.at(top).isMono()) { return; }

        LOGIC_ASSERTION_CHECK(g.at(top).kind != onk::Empty, "");

        Id start = top + 1;
        Id id    = start;


        if (Opt<Slice<Id>> extentOpt = g.allSubnodesOf(top)) {
            Slice<Id> extent = extentOpt.value();
            LOGIC_ASSERTION_CHECK(g.nodes.contains(extent.first), "");
            LOGIC_ASSERTION_CHECK(g.nodes.contains(extent.last), "");

            Opt<OrgToken> first_token;
            for (auto const& id : extent) {
                if (g.at(id).isTerminal()) {
                    first_token = g.tokens->at(g.at(id).getToken());
                }
            }

            int     index = 0;
            Vec<Id> visited;
            while (extent.contains(id)) {
                LOGIC_ASSERTION_CHECK(g.nodes.contains(id), "");
                aux(id);
                visited.push_back(id);

                id = id + g.at(id).getExtent();
                LOGIC_ASSERTION_CHECK(
                    g.nodes.contains(id),
                    "next subnode"
                    "Step over the subnode of {} with extent {} "
                    "yielded id {} which is outsize of the group "
                    "range (index is {}, group size is {}), "
                    "subnode index is {}, size overflow is {}. First "
                    "token is {}",
                    fmt_id(start),
                    extent,
                    id.getUnmasked(),
                    id.getIndex(),
                    g.size(),
                    index,
                    id - g.nodes.back(),
                    first_token);


                id = id + 1;
                ++index;
            }

            LOGIC_ASSERTION_CHECK(
                extent.last + 1 == id,
                "range end Iteration over subnode ranges for {} did not "
                "end at the {} -- combined subnode extent strides summed "
                "up to {}. Total subnode count is {}, full extent is {} "
                "visited subnodes {}. First token is {}",
                top.getUnmasked(),
                (extent.last + 1).getUnmasked(),
                id.getUnmasked(),
                index,
                extent,
                visited | rv::transform(fmt_id) | rs::to<Vec>(),
                first_token);
        }
    };

    aux(id);
}


namespace {
OrgId extendSubtreeTrailsImpl(OrgParser* parser, OrgId id, int level) {
    OrgId const start = id;
    // Iterate over all nodes until the end of the group or until exit
    // condition is met. This assumes non-restructured tree that has
    // subnodes positioned flatlyl on the top level
    auto& g = *parser->group;
    while (id <= g.nodes.back()) {
        // NOTE: 'back' returns the last node, not one-past-last
        OrgNode node = g.at(id);
        if (node.kind == onk::Subtree) {
            if (parser->TraceState) {
                parser->print(
                    "Found subtree on the lower level " + id.format());
            }
            OrgId const tree = id;
            if (g.size(tree) == 0 && parser->TraceState) {
                parser->message(g.treeRepr(tree));
            }

            OrgId subId = g.subnode(tree, 0);
            int   sub   = g.val(subId).text.size();
            if (level < sub) {
                OrgId stmt = g.subnode(tree, 8);
                LOGIC_ASSERTION_CHECK(
                    g.at(stmt).kind == onk::StmtList, "");
                id = extendSubtreeTrailsImpl(parser, stmt + 1, sub);
                LOGIC_ASSERTION_CHECK(stmt + 1 <= id, "");
                // AUX returns next position to start looping from, so
                // the tree size is 'end - start - 1' to account for
                // the offset.

                // Extend the tree itself and nested statement list
                int stmt_extend = (id - stmt) - 1;
                int tree_extend = (id - tree) - 1;
                g.at(stmt).extend(stmt_extend);
                g.at(tree).extend(tree_extend);

                if (parser->TraceState) {
                    parser->print(
                        fmt("Found nested subtree tree={} stmt={} "
                            "tree-extend={} stmt-extend={}",
                            tree.format(),
                            stmt.format(),
                            tree_extend,
                            stmt_extend));
                }

                auto treeSlice = g.allSubnodesOf(tree).value();
                auto stmtSlice = g.allSubnodesOf(tree).value();

                // Structural correctness checks -- mostly for
                // debugging of the implementation, malformed incoming
                // data is not expected.
                assertValidStructure(parser->group, tree);
                LOGIC_ASSERTION_CHECK(
                    treeSlice.last <= g.nodes.back(), "");
                LOGIC_ASSERTION_CHECK(
                    stmtSlice.last <= g.nodes.back(), "");
                LOGIC_ASSERTION_CHECK(
                    treeSlice.last == stmtSlice.last,
                    "extend tree {} -- {}",
                    treeSlice,
                    stmtSlice);
                LOGIC_ASSERTION_CHECK(
                    treeSlice.contains(stmtSlice),
                    "statement containment {} -- {}",
                    treeSlice,
                    stmtSlice);


            } else {
                if (parser->TraceState) {
                    parser->print(
                        "Found subtree on the same level or above "
                        + id.format());
                }
                // Found subtree on the same level or above
                break;
            }
        } else {
            // Node is not a subtree, skipping.
            ++id;
        }
    }

    // Return next starting position for the caller start
    return id;
}
} // namespace

void OrgParser::extendSubtreeTrails(OrgId position) {
    __perf_trace("parsing", "extendSubtreeTrails");
    extendSubtreeTrailsImpl(this, position, 0);
    assertValidStructure(group, position);
}
