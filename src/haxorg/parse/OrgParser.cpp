#include <haxorg/parse/OrgParser.hpp>
#pragma clang diagnostic ignored "-Wunused-result"
#pragma clang diagnostic ignored "-Wformat-security"
#include <absl/log/log.h>
#include <absl/log/check.h>
#include <haxorg/sem/perfetto_org.hpp>
#include <boost/algorithm/string/replace.hpp>


using otk = OrgTokenKind;
using onk = OrgNodeKind;

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


#define subParse(__kind, __lex)                                           \
    this->subParseImpl(                                                   \
        &OrgParser::parse##__kind, __lex, __LINE__, __func__)

void OrgParser::space(OrgLexer& lex, int line, char const* function) {
    while (lex.at(OrgTokSet{otk::Whitespace, otk::LeadingSpace})) {
        skip(lex, std::nullopt, line, function);
    }
}

void OrgParser::newline(OrgLexer& lex, int line, char const* function) {
    while (lex.at(Newline)) { skip(lex, std::nullopt, line, function); }
}

SubLexer<OrgTokenKind, OrgFill> subToEol(
    OrgLexer& lex,
    OrgTokSet Terminator = ParagraphTerminator) {
    SubLexer sub{lex};
    while (lex.can_search(Terminator)) { sub.add(lex.pop()); }
    if (!sub.tokens.empty()) { sub.start(); }
    return sub;
}

void OrgParser::parseCSVArguments(OrgLexer& lex) {
    __perf_trace("parsing", "parseCSVArguments");
    auto __trace = trace(lex);
    token(onk::Word, pop(lex, OrgTokSet{otk::Word}));

    if (lex.at(otk::ParBegin)) {
        skip(lex, otk::ParBegin);
        while (lex.at(otk::RawText)) {
            token(onk::RawText, pop(lex, otk::RawText));
            if (lex.at(otk::Comma)) { skip(lex); }
        }
        skip(lex, otk::ParEnd);
    }
}

OrgId OrgParser::subParseImpl(
    OrgId (OrgParser::*func)(OrgLexer&),
    OrgLexer&   lex,
    int         line,
    char const* function) {
    auto tok = lex.get();
    return (this->*func)(lex);
}


OrgId OrgParser::parseMacro(OrgLexer& lex) {
    __perf_trace("parsing", "parseMacro");
    auto __trace = trace(lex);
    start(onk::Macro);
    skip(lex, otk::CurlyBegin);
    skip(lex, otk::CurlyBegin);
    skip(lex, otk::CurlyBegin);
    token(onk::Word, pop(lex, OrgTokSet{otk::Word}));

    parseCallArguments(lex);

    skip(lex, otk::CurlyEnd);
    skip(lex, otk::CurlyEnd);
    skip(lex, otk::CurlyEnd);
    return end();
}

void OrgParser::parseCallArguments(OrgLexer& lex) {
    if (lex.at(otk::ParBegin)) {
        skip(lex, otk::ParBegin);
        space(lex);
        if (lex.at(otk::ParEnd)) {
            empty();
            skip(lex, otk::ParEnd);
            return;
        }

        bool isVerbatimWrap = lex.at(otk::VerbatimBegin);
        if (isVerbatimWrap) { skip(lex, otk::VerbatimBegin); }

        auto argEnd   = isVerbatimWrap ? Vec{otk::VerbatimEnd, otk::ParEnd}
                                       : Vec{otk::ParEnd};
        auto macroEnd = Vec{
            otk::CurlyEnd,
            otk::CurlyEnd,
            otk::CurlyEnd,
        };

        while (lex.can_search(macroEnd) && lex.can_search(argEnd)) {
            start(onk::InlineStmtList);
            while (lex.can_search(otk::Comma) && lex.can_search(argEnd)) {
                token(onk::RawText, pop(lex));
            }
            end();
            if (lex.at(otk::Comma)) { skip(lex); }
            space(lex);
        }

        if (isVerbatimWrap) { skip(lex, otk::VerbatimEnd); }
        skip(lex, otk::ParEnd);
    } else {
        empty();
    }
}


OrgId OrgParser::parsePlaceholder(OrgLexer& lex) {
    __perf_trace("parsing", "parsePlaceholder");
    auto __trace = trace(lex);
    if (lex.at(otk::Placeholder)) {
        auto tok = token(onk::Placeholder, pop(lex, otk::Placeholder));
        return tok;
    } else {
        return token(onk::Punctuation, pop(lex, lex.kind()));
    }
}


OrgId OrgParser::parseLatex(OrgLexer& lex) {
    __perf_trace("parsing", "parseLatex");
    auto __trace = trace(lex);
    skip(lex, otk::LatexParBegin);
    auto tok = token(onk::InlineMath, pop(lex, otk::LatexInlineRaw));
    skip(lex, otk::LatexParEnd);
    return tok;
}


void OrgParser::textFold(OrgLexer& lex) {
    // Text fold method will consume all tokens in the lexer, folding into
    // series of tree nodes.
    __perf_trace("parsing", "textFold");
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
                    token(onk::Escaped, pop(lex, otk::Escaped));
                    break;
                }
                case otk::RawText: {
                    token(onk::RawText, pop(lex, otk::RawText));
                    break;
                }
                case otk::Newline: {
                    token(onk::Newline, pop(lex, otk::Newline));
                    break;
                }
                case otk::Word: {
                    token(onk::Word, pop(lex, otk::Word));
                    break;
                }
                case otk::BigIdent: {
                    token(onk::BigIdent, pop(lex, otk::BigIdent));
                    break;
                }
                case otk::Punctuation: {
                    token(onk::Punctuation, pop(lex, otk::Punctuation));
                    break;
                }
                case otk::Colon: {
                    token(onk::Colon, pop(lex, otk::Colon));
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

                case otk::Whitespace:
                    token(onk::Space, pop(lex, lex.kind()));
                    break;
                case otk::CurlyBegin: {
                    if (lex.at(
                            Vec{otk::CurlyBegin,
                                otk::CurlyBegin,
                                otk::CurlyBegin})) {
                        subParse(Macro, lex);
                    } else {
                        token(onk::Punctuation, pop(lex));
                    }
                    break;
                }

                case otk::AngleEnd: {
                    token(onk::Punctuation, pop(lex, lex.kind()));
                    break;
                }

                case otk::MiscUnicode:
                case otk::WeekdayName:
                case otk::Time:
                case otk::Date:
                case otk::SubtreePriority:
                case otk::Number: {
                    token(onk::Word, pop(lex, lex.kind()));
                    break;
                }

                case otk::Placeholder: {
                    parsePlaceholder(lex);
                    break;
                }

                case otk::AngleBegin: {
                    if (lex.at(otk::Date, +1)) {
                        subParse(TimeStamp, lex);
                    } else {
                        subParse(Placeholder, lex);
                    }
                    break;
                }

                case otk::TextSrcBegin: subParse(SrcInline, lex); break;
                case otk::HashIdent: subParse(HashTag, lex); break;
                case otk::LinkProtocolHttp:
                case otk::LinkProtocol:
                case otk::LinkBegin: subParse(Link, lex); break;
                case otk::FootnoteInlineBegin:
                case otk::FootnoteLinked: subParse(Footnote, lex); break;
                case otk::Symbol: subParse(Symbol, lex); break;

                case otk::BraceBegin: {
                    if (lex.at(otk::Date, +1)) {
                        subParse(TimeRange, lex);
                    } else {
                        token(onk::Punctuation, pop(lex, lex.kind()));
                    }
                    break;
                }

                case otk::At: {
                    token(onk::AtMention, pop(lex, otk::At));
                    break;
                }

                case otk::VerbatimBegin:
                case otk::MonospaceBegin: {
                    parseVerbatimOrMonospace(lex);
                    break;
                }

                    // case otk::DoubleAngleBegin: {
                    //     if (lex.ahead(
                    //             OrgTokSet{
                    //                 otk::Whitespace,
                    //                 otk::Word,
                    //                 otk::DoubleAngleBegin},
                    //             otk::DoubleAngleEnd)) {
                    //         skip(lex, otk::DoubleAngleBegin);
                    //         start(onk::Target);
                    //         while (lex.can_search(otk::DoubleAngleEnd))
                    //         {
                    //             token(
                    //                 onk::Target, pop(lex,
                    //                 AngleTargetContent));
                    //         }
                    //         end();
                    //         skip(lex, otk::DoubleAngleEnd);
                    //     } else {
                    //         token(onk::Punctuation, pop(lex,
                    //         lex.kind()));
                    //     }

                    //     break;
                    // }

                case otk::DoubleAngleBegin:
                case otk::TripleAngleBegin: {
                    parseAngleTarget(lex);
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
                        token(onk::Punctuation, pop(lex, lex.kind()));
                    }
                    break;
                }

                default: {
                    token(onk::Punctuation, pop(lex, lex.kind()));
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
    __perf_trace("parsing", "parseText");
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


OrgId OrgParser::parseLink(OrgLexer& lex) {
    __perf_trace("parsing", "parseLink");
    auto __trace = trace(lex);
    if (lex.at(otk::LinkProtocolHttp)) {
        start(onk::Link);
        token(onk::Word, pop(lex, otk::LinkProtocolHttp));
        token(onk::RawText, pop(lex, otk::LinkTarget));
        empty();
        return end();
    } else {
        start(onk::Link);
        skip(lex, otk::LinkBegin);
        // LOG(INFO) << fmt1(lex.tok()->line);
        switch (lex.kind()) {
            case otk::LinkProtocolHttp: {
                token(onk::Word, pop(lex, otk::LinkProtocolHttp));
                token(onk::RawText, pop(lex, otk::LinkTarget));
                break;
            }
            case otk::LinkProtocolId: {
                token(onk::Word, pop(lex, otk::LinkProtocolId));
                token(onk::RawText, pop(lex, otk::LinkTarget));
                break;
            }
            case otk::LinkProtocolTitle: {
                empty();
                token(onk::RawText, pop(lex, otk::LinkProtocolTitle));
                break;
            }
            case otk::LinkProtocolCustomId: {
                token(onk::Word, pop(lex, otk::LinkProtocolCustomId));
                token(onk::RawText, pop(lex, otk::LinkProtocolInternal));
                break;
            }
            case otk::LinkProtocolAttachment: {
                token(onk::Word, pop(lex, otk::LinkProtocolAttachment));
                token(onk::RawText, pop(lex, otk::LinkTarget));
                break;
            }
            case otk::LinkProtocolFile: {
                token(onk::Word, pop(lex, otk::LinkProtocolFile));
                token(onk::RawText, pop(lex, otk::LinkTarget));
                break;
            }
            case otk::LinkTargetFile: {
                empty();
                token(onk::RawText, pop(lex, otk::LinkTargetFile));
                break;
            }
            case otk::LinkProtocolInternal: {
                empty();
                token(onk::RawText, pop(lex, otk::LinkProtocolInternal));
                break;
            }
            default:
                token(onk::Word, pop(lex, otk::LinkProtocol));
                SubLexer sub{lex};
                while (!lex.at(OrgTokSet{otk::LinkSplit, otk::LinkEnd})) {
                    sub.add(pop(lex));
                }
                if (sub.empty()) {
                    empty();
                } else {
                    sub.start();
                    parseParagraph(sub);
                }
        }

        if (lex.at(otk::LinkSplit)) {
            skip(lex, otk::LinkSplit);
            SubLexer sub{lex};
            while (lex.can_search(otk::LinkEnd)) { sub.add(pop(lex)); }
            if (sub.empty()) {
                empty();
            } else {
                sub.start();
                parseParagraph(sub);
            }
        } else {
            empty();
        }


        skip(lex, otk::LinkEnd);
        return end();
    }
}


OrgId OrgParser::parseInlineMath(OrgLexer& lex) {
    __perf_trace("parsing", "parseInlineMath");
    auto __trace = trace(lex);

    start(onk::InlineMath);


    return end();
}


OrgId OrgParser::parseSymbol(OrgLexer& lex) {
    __perf_trace("parsing", "parseSymbol");
    auto __trace = trace(lex);
    start(onk::Symbol);
    token(onk::Word, pop(lex, otk::Symbol));

    start(onk::InlineStmtList);
    while (lex.at(otk::BraceBegin)) {
        skip(lex, otk::BraceBegin);
        token(onk::RawText, pop(lex));
        skip(lex, otk::BraceEnd);
    }
    end();

    start(onk::InlineStmtList);
    while (lex.at(otk::CurlyBegin)) {
        if (lex.at(Vec{otk::CurlyBegin, otk::CurlyEnd})) {
            empty();
            skip(lex, otk::CurlyBegin);
            skip(lex, otk::CurlyEnd);
        } else {
            auto sub = SubLexer(
                lex.in, lex.getInside({otk::CurlyBegin}, {otk::CurlyEnd}));
            start(onk::Paragraph);
            parseText(sub);
            end();
        }
    }
    end();

    return end();
}


OrgId OrgParser::parseHashTag(OrgLexer& lex) {
    __perf_trace("parsing", "parseHashTag");
    auto __trace = trace(lex);

    struct HashState {
        OrgId result;
        bool  doubleSkip;
    };

    Func<HashState(OrgLexer & lex)> aux;


    aux = [&](OrgLexer& lex) -> HashState {
        auto __trace = trace(lex, "aux", __LINE__, "aux");
        start(onk::HashTag);
        space(lex);
        if (lex.at(otk::At)) {
            // Org-mode suppors tags like '@work' etc.
            token(onk::RawText, pop(lex, otk::At));
        } else {
            token(
                onk::RawText,
                pop(lex,
                    OrgTokSet{otk::HashIdent, otk::Word, otk::BigIdent}));
        }

        bool doubleSkip = false;

        if (lex.at(otk::DoubleHash)) {
            skip(lex, otk::DoubleHash);
            if (lex.at(
                    OrgTokSet{otk::HashIdent, otk::Word, otk::BigIdent})) {
                auto sub = aux(lex);
                if (sub.doubleSkip) {
                    print("double skip");
                    return HashState{.result = end()};
                }

            } else {
                skip(lex, otk::BraceBegin);
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
                    skip(lex, otk::LinkEnd);
                } else {
                    skip(lex, otk::BraceEnd);
                }
            }
        }

        return HashState{
            .result     = end(),
            .doubleSkip = doubleSkip,
        };
    };

    return aux(lex).result;
}


OrgId OrgParser::parseTimeStamp(OrgLexer& lex) {
    __perf_trace("parsing", "parseTimeStamp");
    auto __trace   = trace(lex);
    auto start_tok = lex.tok();
    expect(lex, OrgTokSet{otk::BraceBegin, otk::AngleBegin});
    bool active = lex.at(otk::AngleBegin);
    if (lex.at(otk::DynamicTimeContent)) {
        if (active) {
            start(onk::DynamicActiveTime);
        } else {
            start(onk::DynamicInactiveTime);
        }

        token(onk::RawText, pop(lex, otk::DynamicTimeContent));

        end();
    } else {
        if (active) {
            start(onk::StaticActiveTime);
            skip(lex, otk::AngleBegin);
        } else {
            start(onk::StaticInactiveTime);
            skip(lex, otk::BraceBegin);
        }

        // Date part is usually used, but I think supporting *time* stamps
        // also makes sense
        if (lex.at(otk::Date)) {
            token(onk::RawText, pop(lex, otk::Date));
            space(lex);
        } else {
            empty();
        }

        // Day can sometimes be added to the timestamp
        if (lex.at(otk::WeekdayName)) {
            skip(lex);
            space(lex);
        }

        if (lex.at(otk::Time)) {
            token(onk::RawText, pop(lex, otk::Time));
            space(lex);
        } else {
            empty();
        }


        // timezone
        if (lex.at(otk::StrikeBegin) && lex.at(otk::Number, +1)) {
            skip(lex);
            token(onk::RawText, pop(lex, otk::Number));
            space(lex);
        } else {
            empty();
        }


        if (lex.at(otk::TimeRepeaterSpec)) {
            token(onk::RawText, pop(lex, otk::TimeRepeaterSpec));
            start(onk::InlineStmtList);
            while (lex.at(otk::TimeRepeaterDuration)) {
                token(onk::RawText, pop(lex));
            }
            end();
            space(lex);
        } else {
            empty();
        }

        if (lex.at(otk::TimeWarnPeriod)) {
            token(onk::RawText, pop(lex, otk::TimeWarnPeriod));
        } else {
            empty();
        }


        end();
    }

    skip(lex, active ? otk::AngleEnd : otk::BraceEnd);
    return back();
}


OrgId OrgParser::parseTimeRange(OrgLexer& lex) {
    __perf_trace("parsing", "parseTimeRange");
    auto            __trace  = trace(lex);
    bool            isActive = lex.at(otk::AngleBegin);
    const OrgTokSet times{
        otk::BraceBegin,
        otk::BraceEnd,
        otk::AngleBegin,
        otk::AngleEnd,
        otk::DynamicTimeContent,
        otk::Date,
        otk::WeekdayName,
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
        if (tmp.at(Vec{
                isActive ? otk::AngleEnd : otk::BraceEnd,
                otk::DoubleDash,
                isActive ? otk::AngleBegin : otk::BraceBegin,
            })) {
            isTimeRange = true;
            break;
        } else {
            tmp.next();
        }
    }

    if (isTimeRange) {
        start(onk::TimeRange);
        subParse(TimeStamp, lex);
        skip(lex, otk::DoubleDash);
        subParse(TimeStamp, lex);
        if (lex.ahead({otk::Whitespace}, {otk::TimeArrow})) {
            space(lex);
            skip(lex, otk::TimeArrow);
            space(lex);
            token(onk::SimpleTime, pop(lex, otk::Time));
        } else {
            empty();
        }

        return end();
    } else {
        return subParse(TimeStamp, lex);
    }
}


OrgId OrgParser::parseFootnote(OrgLexer& lex) {
    __perf_trace("parsing", "parseFootnote");
    auto __trace = trace(lex);
    if (lex.at(otk::FootnoteLinked)) {
        start(onk::Footnote);
        empty();
        token(onk::RawText, pop(lex));
        return end();
    } else {
        start(onk::InlineFootnote);
        skip(lex, otk::FootnoteInlineBegin);
        SubLexer sub{lex};
        while (!lex.finished() && !lex.at(otk::BraceEnd)) {
            sub.add(pop(lex));
        }
        sub.start();
        parseParagraph(sub);
        skip(lex, otk::BraceEnd);
        return end();
    }
}


OrgId OrgParser::parseSrcInline(OrgLexer& lex) {
    __perf_trace("parsing", "parseSrcInline");
    auto __trace = trace(lex);
    start(onk::SrcInlineCode);
    {
        token(onk::Word, pop(lex, otk::TextSrcBegin)); // lang

        { // header args
            empty();
        }
        start(onk::CodeLine); // body
        {
            int balance = 1;
            skip(lex, otk::CurlyBegin);
            while (!lex.finished() && 0 < balance) {
                if (lex.at(otk::CurlyEnd)) {
                    if (balance == 1) {
                        skip(lex, otk::CurlyEnd);
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
    return end();
}

OrgId OrgParser::parseVerbatimOrMonospace(OrgLexer& lex) {
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
                    token(onk::RawText, pop(lex, lex.kind()));
                }

                break;
            }
            case otk::Newline: {
                if (2 < newlineCount) {
                    foundEnd = true;
                } else {
                    ++newlineCount;
                    token(onk::RawText, pop(lex, lex.kind()));
                }
                break;
            }

            case otk::Placeholder: {
                subParse(Placeholder, lex);
                break;
            }
            default: {
                token(onk::RawText, pop(lex, lex.kind()));
            }
        }
    }

    if (lex.at(m ? otk::MonospaceEnd : otk::VerbatimEnd)) {
        skip(lex);
        return end();
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
        return token(onk::Punctuation, pop(lex));
    }
}

OrgId OrgParser::parseAngleTarget(OrgLexer& lex) {
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
        skip(lex, begin);
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
        skip(lex, end);
        return this->end();
    } else {
        return token(onk::Punctuation, pop(lex, lex.kind()));
    }
}


OrgId OrgParser::parseTable(OrgLexer& lex) {
    __perf_trace("parsing", "parseTable");
    auto __trace = trace(lex);
    start(onk::Table);


    auto parse_pipe_row = [&]() {
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
            while (!lex.at(CellEnd)) {
                if (lex.at(otk::Whitespace)
                    && (lex.at(CellEnd, +1) || lex.at(CellStart, -1))) {
                    lex.next();
                } else {
                    sub.add(pop(lex, lex.kind()));
                }
            }
            if (sub.empty()) {
                start(onk::Paragraph);
                end();
            } else {
                sub.start();
                parseParagraph(sub);
            }

            end();
            end();
        }
        skip(lex, otk::TrailingPipe);
        if (lex.at(Newline)) { skip(lex, Newline); }

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
        skip(lex, otk::CmdPrefix);
        skip(lex, otk::CmdTableBegin);
        parseCommandArguments(lex);
        newline(lex);

        while (lex.can_search(TableEnd)) {
            switch (lex.kind()) {
                case otk::LeadingPipe: {
                    parse_pipe_row();
                    break;
                }
                case otk::CmdPrefix: {
                    skip(lex, otk::CmdPrefix);
                    skip(lex, otk::CmdRow);
                    start(onk::TableRow);
                    parseCommandArguments(lex);
                    empty();
                    newline(lex);

                    start(onk::StmtList);
                    if (lex.at(otk::LeadingPipe)) {
                        while (lex.at(otk::LeadingPipe)) {
                            skip(lex, otk::LeadingPipe);
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
                                        parseParagraph(sub);
                                    }
                                }
                                end();
                            }
                            end();
                            newline(lex);
                        }
                    } else {
                        while (lex.at(Vec{otk::CmdPrefix, otk::CmdCell})) {
                            skip(lex, otk::CmdPrefix);
                            skip(lex, otk::CmdCell);
                            start(onk::TableCell);
                            {
                                parseCommandArguments(lex);
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
                                        parseStmtListItem(lex);
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


        skip(lex, otk::CmdPrefix);
        skip(lex, otk::CmdTableEnd);
    }


    return end();
}


OrgId OrgParser::parseParagraph(OrgLexer& lex) {
    start(onk::Paragraph);
    parseText(lex);
    end();
    return back();
}

OrgId OrgParser::parseCommandArguments(OrgLexer& lex) {
    __perf_trace("parsing", "parseCommandArguments");
    auto __trace = trace(lex);
    space(lex);
    start(onk::InlineStmtList);
    while (lex.at(OrgTokSet{otk::CmdRawArg, otk::CmdColonIdent})) {
        if (lex.at(otk::CmdColonIdent)) {
            start(onk::CmdValue);
            {
                token(onk::Word, pop(lex, otk::CmdColonIdent));
                space(lex);
                if (lex.at(otk::CmdRawArg)) {
                    token(onk::RawText, pop(lex, otk::CmdRawArg));
                } else {
                    empty();
                }
            }
            end();
        } else {
            start(onk::CmdValue);
            {
                empty();
                space(lex);
                token(onk::RawText, pop(lex, otk::CmdRawArg));
            }
            end();
        }
        space(lex);
    }

    return end();
}


OrgId OrgParser::parseSrcArguments(OrgLexer& lex) {
    __perf_trace("parsing", "parseSrcArguments");
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(Newline)) {
        empty();
        return empty();
    } else {
        start(onk::Attrs);
        start(onk::InlineStmtList);
        {
            while (lex.at(otk::CmdFlag)) {
                token(onk::CmdFlag, pop(lex, otk::CmdFlag));
            }
        }
        end();
        subParse(CommandArguments, lex);
        return end();
    }
}


OrgId OrgParser::parseTextWrapCommand(OrgLexer& lex) {
    __perf_trace("parsing", "parseTextWrapCommand");
    skip(lex, otk::CmdPrefix);
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
        subParse(CommandArguments, lex);
        space(lex);
    }

    skip(lex, Newline);

    if (isDynamic) {
        boost::replace_all(tmp, "begin", "end");
        Str endName = normalize(tmp);
        print(fmt("Dynamic block, name {}", endName));
        while (lex.can_search(Vec<otk>{otk::CmdPrefix, endTok})
               && lex.hasNext(2)
               && normalize(lex.val(1).text) != endName) {
            subParse(StmtListItem, lex);
            if (lex.at(BlockTerminator)) {
                print(fmt("block terminator {}", lex));
                break;
            }
        }
    } else {
        while (lex.can_search(Vec<otk>{otk::CmdPrefix, endTok})) {
            subParse(StmtListItem, lex);
            if (lex.at(BlockTerminator)) {
                print(fmt("block terminator {}", lex));
                break;
            }
        }
    }

    skip(lex, otk::CmdPrefix);
    skip(lex, endTok);
    return end();
}


OrgId OrgParser::parseBlockExport(OrgLexer& lex) {
    __perf_trace("parsing", "parseExample");
    auto __trace = trace(lex);
    start(onk::BlockExport);

    skip(lex, otk::CmdPrefix);
    skip(lex, otk::CmdExportBegin);

    // command arguments
    space(lex);
    token(onk::Word, pop(lex, otk::CmdRawArg));
    space(lex);
    subParse(CommandArguments, lex);
    newline(lex);

    // command content
    start(onk::StmtList);
    while (lex.at(OrgTokSet{otk::CmdExportLine, otk::Newline})) {
        token(onk::RawText, pop(lex, lex.kind()));
    }
    end();

    skip(lex, otk::CmdPrefix);
    skip(lex, otk::CmdExportEnd);

    return end();
}


OrgId OrgParser::parseColonExample(OrgLexer& lex) {
    __perf_trace("parsing", "parseColonExample");

    auto __trace = trace(lex);


    start(onk::ColonExample);
    while (lex.at(OrgTokSet{otk::ColonExampleLine, otk::Colon})) {
        if (lex.at(otk::ColonExampleLine)) {
            token(onk::RawText, pop(lex, lex.kind()));
        } else {
            empty();
            skip(lex, otk::Colon);
        }

        if (lex.at(otk::Newline)) { skip(lex, otk::Newline); }
    }

    return end();
}

OrgId OrgParser::parseExample(OrgLexer& lex) {
    __perf_trace("parsing", "parseExample");
    auto __trace = trace(lex);
    start(onk::BlockExample);

    skip(lex, otk::CmdPrefix);
    skip(lex, otk::CmdExampleBegin);

    { // command arguments
        subParse(CommandArguments, lex);
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

    skip(lex, otk::CmdPrefix);
    skip(lex, otk::CmdExampleEnd);

    return end();
}


OrgId OrgParser::parseSrc(OrgLexer& lex) {
    __perf_trace("parsing", "parseSrc");
    auto __trace = trace(lex);
    start(onk::BlockCode);
    skip(lex, otk::CmdPrefix);
    skip(lex, otk::CmdSrcBegin);
    // header_args_lang
    {
        space(lex);
        if (lex.at(otk::CmdRawArg)) {
            if (lex.val().text.empty()) {
                empty();
            } else {
                token(onk::Word, pop(lex, otk::CmdRawArg));
            }
        } else {
            empty();
        }

        space(lex);

        subParse(SrcArguments, lex);
    };
    // body
    {

        start(onk::StmtList);
        skip(lex, otk::CmdContentBegin);
        while (lex.can_search(Vec{otk::CmdPrefix, otk::CmdSrcEnd})) {
            start(onk::CodeLine);
            while (lex.can_search(
                OrgTokSet{otk::CmdContentEnd, otk::Newline})) {
                switch (lex.kind()) {
                    case otk::SrcContent: {
                        token(onk::CodeText, pop(lex, otk::SrcContent));
                        break;
                    }
                    case otk::ParBegin: {
                        skip(lex, otk::ParBegin);
                        skip(lex, otk::Word);
                        skip(lex, otk::Colon);
                        start(onk::CodeCallout);
                        token(onk::Word, pop(lex, otk::Word));
                        end();
                        skip(lex, otk::ParEnd);
                        break;
                    }
                    case otk::DoubleAngleBegin: {
                        skip(lex, otk::DoubleAngleBegin);
                        start(onk::CodeTangle);
                        parseCSVArguments(lex);
                        end();
                        skip(lex, otk::DoubleAngleEnd);
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

    skip(lex, otk::CmdPrefix);
    skip(lex, otk::CmdSrcEnd);


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
        skip(lex, otk::CmdPrefix);
        skip(lex, otk::CmdResults);
        start(onk::CmdResults);
        space(lex);
        parseCommandArguments(lex);
        newline(lex);
        parseStmtListItem(lex);
        end();
    } else {
        empty();
    }

    return end();
}


OrgId OrgParser::parseListItem(OrgLexer& lex) {
    __perf_trace("parsing", "parseListItem");
    auto __trace = trace(lex);
    start(onk::ListItem);
    // prefix, 0
    { token(onk::RawText, pop(lex, ListStarts)); }
    space(lex);
    // counter, 1
    {
        empty(); // TODO parse counter
    }
    // checkbox 2
    {
        if (lex.at(otk::Checkbox)) {
            token(onk::Checkbox, pop(lex, otk::Checkbox));
            space(lex);
        } else {
            empty();
        }
    }
    // tag, 3
    {
        // Search ahead for the description list tag
        Lexer<OrgTokenKind, OrgFill> tmp{lex.in};
        tmp.pos = lex.pos;
        while (tmp.can_search(otk::DoubleColon)) {
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

        if (tmp.at(otk::DoubleColon)) {
            SubLexer sub{lex};

            while (lex.can_search(otk::DoubleColon)) {
                sub.add(lex.pop());
            }

            if (sub.empty()) {
                empty();
            } else {
                sub.start();
                subParse(Paragraph, sub);
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
            subParse(StmtListItem, lex);
        }
    }

    if (lex.at(otk::ListItemEnd)) { skip(lex); }

    end();
    return end();
}


OrgId OrgParser::parseList(OrgLexer& lex) {
    __perf_trace("parsing", "parseList");
    auto __trace = trace(lex);
    start(onk::List);

    print(fmt("{}", lex.tok()));

    while (lex.at(ListStarts)
           || (lex.at(otk::LeadingSpace) && lex.at(ListStarts, +1))) {
        subParse(ListItem, lex);
        if (lex.at(otk::SameIndent)) { skip(lex); }
    }

    return end();
}


OrgId OrgParser::parseSubtreeLogbook(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtreeLogbook");
    auto __trace = trace(lex);
    start(onk::DrawerLogbook);
    skip(lex, otk::ColonLogbook);
    newline(lex);

    space(lex);

    skip(lex, otk::Indent);
    subParse(List, lex);
    if (lex.at(otk::StmtListEnd)) {
        skip(lex, otk::StmtListEnd);
        skip(lex, otk::ListItemEnd);
    }
    skip(lex, otk::Dedent);

    space(lex);
    skip(lex, otk::ColonEnd);
    return end();
}


OrgId OrgParser::parseSubtreeProperties(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtreeProperties");
    auto __trace = trace(lex);
    skip(lex, otk::ColonProperties);
    skip(lex, otk::Newline);
    start(onk::DrawerPropertyList);
    while (lex.can_search(otk::ColonEnd)) {
        trace(lex, "Parse single subtree property");
        start(onk::DrawerProperty);
        auto head = lex.kind();
        token(onk::RawText, pop(lex, head));
        switch (head) {
            case otk::ColonLiteralProperty: {
                token(onk::RawText, pop(lex, otk::RawText));
                break;
            }

            case otk::ColonArgumentsProperty: {
                subParse(CommandArguments, lex);
                break;
            }

            case otk::ColonPropertyText: {
                space(lex);
                SubLexer sub{lex};
                while (lex.can_search(Newline)) { sub.add(lex.pop()); }
                sub.start();
                parseParagraph(sub);
                break;
            }
            default: {
                throw fatalError(
                    lex, fmt("Unhandled property kind parse {}", head));
            }
        }
        skip(lex, otk::Newline);
        end();
    }

    skip(lex, otk::ColonEnd);
    return end();
}


OrgId OrgParser::parseSubtreeDrawer(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtreeDrawer");
    auto __trace = trace(lex);
    start(onk::Drawer);

    while (lex.at(OrgTokSet{otk::ColonProperties, otk::ColonLogbook})) {
        switch (lex.tok().kind) {
            case otk::ColonProperties:
                subParse(SubtreeProperties, lex);
                break;
            case otk::ColonLogbook: subParse(SubtreeLogbook, lex); break;
            default:
        }

        newline(lex);
        space(lex);
    }

    return end();
}

void tokenFormat(ColStream& os, OrgToken const& t) { os << t->text; }

OrgId OrgParser::parseSubtreeCompletion(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtreeCompletion");
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(otk::SubtreeCompletion)) {
        return token(
            onk::SubtreeCompletion, pop(lex, otk::SubtreeCompletion));
    } else {
        return empty();
    }
}


OrgId OrgParser::parseSubtreeTodo(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtreeTodo");
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(otk::BigIdent)) {
        return token(onk::BigIdent, pop(lex, otk::BigIdent));
    } else {
        return empty();
    }
}


OrgId OrgParser::parseSubtreeUrgency(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtreeUrgency");
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(otk::SubtreePriority)) {
        return token(onk::SubtreeUrgency, pop(lex, otk::SubtreePriority));
    } else {
        return empty();
    }
}


OrgId OrgParser::parseSubtreeTitle(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtreeTitle");
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
        sub.add(pop(lex, lex.kind()));
    }

    if (sub.empty()) {
        return empty();
    } else {
        sub.start();
        return parseParagraph(sub);
    }
}


OrgId OrgParser::parseSubtreeTags(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtreeTags");
    auto __trace = trace(lex);
    if (lex.at(otk::Colon)) {
        start(onk::InlineStmtList);
        while (
            lex.at(otk::Colon)
            && lex.at(OrgTokSet{otk::Word, otk::At, otk::BigIdent}, +1)) {
            skip(lex, otk::Colon);
            subParse(HashTag, lex);
        }
        skip(lex, OrgTokSet{otk::Colon} + Newline);
        return end();
    } else {
        return empty();
    }
}


OrgId OrgParser::parseSubtreeTimes(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtreeTimes");
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
            subParse(TimeRange, lex);
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
                subParse(TimeRange, lex);
                space(lex);
                end();
            }

        not_a_timestamp:
        }

        return end();
    } else {
        return empty();
    }
}


OrgId OrgParser::parseSubtree(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtree");
    auto __trace = trace(lex);
    start(onk::Subtree);
    // prefix

    token(onk::RawText, pop(lex, otk::SubtreeStars)); // 0
    subParse(SubtreeTodo, lex);                       // 1
    subParse(SubtreeUrgency, lex);                    // 2
    space(lex);                                       //
    subParse(SubtreeTitle, lex);                      // 3
    subParse(SubtreeCompletion, lex);                 // 4
    subParse(SubtreeTags, lex);                       // 5

    if (lex.at(otk::Newline)) { newline(lex); }
    subParse(SubtreeTimes, lex); // 6


    if (lex.at(otk::Newline)) { newline(lex); }

    if (lex.at(OrgTokSet{otk::ColonProperties, otk::ColonLogbook})) { // 7
        subParse(SubtreeDrawer, lex);
    } else {
        empty();
    }

    newline(lex);

    start(onk::StmtList); // 8
    end();
    return end();
}


OrgId OrgParser::parseOrgFile(OrgLexer& lex) {
    __perf_trace("parsing", "parseOrgFile");
    auto __trace = trace(lex);
    start(onk::File);
    LOG(FATAL);
    return end();
}


OrgId OrgParser::parseLineCommand(OrgLexer& lex) {
    __perf_trace("parsing", "parseLineCommand");
    auto __trace  = trace(lex);
    auto cmd_kind = lex.kind(+1);
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
            skip(lex, otk::CmdPrefix);
            token(onk::RawText, pop(lex));
            while (lex.at(otk::RawText)) {
                token(onk::RawText, pop(lex, otk::RawText));
                if (lex.at(otk::Whitespace)) { space(lex); }
            }
            break;
        }

        case otk::CmdDateRaw:
        case otk::CmdDescription: {
            skip(lex, otk::CmdPrefix);
            start(onk::CmdCustomTextCommand);
            token(onk::RawText, pop(lex));
            start(onk::Attrs);
            auto sub = subToEol(
                lex, ParagraphTerminator + OrgTokSet{otk::Newline});
            if (sub.empty()) {
                empty();
            } else {
                parseParagraph(sub);
            }
            end();
            break;
        }

        case otk::CmdHtmlHeadRaw: {
            skip(lex, otk::CmdPrefix);
            start(onk::CmdCustomArgsCommand);
            token(onk::RawText, pop(lex));
            parseCommandArguments(lex);
            break;
        }

        case otk::CmdCall: {
            start(onk::CmdCallCode);
            skip(lex, otk::CmdPrefix);
            skip(lex, otk::CmdCall);
            token(onk::Word, pop(lex, otk::Word));
            parseCallArguments(lex);
            break;
        }

        case otk::CmdTitle:
        case otk::CmdCaption: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
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
                parseParagraph(sub);
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

            skip(lex, otk::CmdPrefix);
            skip(lex);
            while (lex.at(OrgTokSet{otk::RawText, otk::CmdRawArg})) {
                token(onk::RawText, pop(lex));
                space(lex);
            }
            break;
        }

        case otk::CmdFiletags: {
            skip(lex, otk::CmdPrefix);
            skip(lex, otk::CmdFiletags);
            start(onk::CmdFiletags);
            while (lex.at(OrgTokSet{otk::Word, otk::BigIdent}, +1)) {
                if (lex.at(otk::Colon)) {
                    skip(lex);
                } else {
                    space(lex);
                }
                subParse(HashTag, lex);
                space(lex);
            }
            if (lex.at(otk::Colon)) { skip(lex); }
            break;
        }


        case otk::CmdLatexClass:
        case otk::CmdLatexCompiler: {
            skip(lex, otk::CmdPrefix);
            switch (cmd_kind) {
                case otk::CmdLatexCompiler:
                    start(onk::CmdLatexCompiler);
                    skip(lex, otk::CmdLatexCompiler);
                    break;
                case otk::CmdLatexClass:
                    start(onk::CmdLatexClass);
                    skip(lex, otk::CmdLatexClass);
                    break;
                default:
            }

            token(onk::Word, pop(lex, otk::CmdRawArg));
            break;
        }


        case otk::CmdLatexClassOptions: {
            skip(lex, otk::CmdPrefix);
            skip(lex, otk::CmdLatexClassOptions);
            start(onk::CmdLatexClassOptions);
            token(onk::RawText, pop(lex, otk::CmdRawArg));
            break;
        }

        case otk::CmdPropertyRaw: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            start(onk::CmdPropertyRaw);
            token(onk::RawText, pop(lex, otk::RawText));
            break;
        }

        case otk::CmdPropertyText: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            start(onk::CmdPropertyArgs);
            token(onk::RawText, pop(lex, otk::CmdRawArg));
            subParse(CommandArguments, lex);
            subParse(Paragraph, lex);
            break;
        }

        case otk::CmdInclude: {
            start(onk::CmdInclude);
            skip(lex);
            skip(lex, otk::CmdInclude);
            subParse(CommandArguments, lex);
            break;
        }

        case otk::CmdAttr: {
            start(onk::CmdAttr);
            skip(lex, otk::CmdPrefix);
            token(onk::Word, pop(lex, otk::CmdAttr));
            subParse(CommandArguments, lex);
            break;
        }

        case otk::CmdName:
        case otk::CmdResults:
        case otk::CmdHeader: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            switch (cmd_kind) {
                case otk::CmdHeader: start(onk::CmdHeader); break;
                case otk::CmdName: start(onk::CmdName); break;
                case otk::CmdResults: start(onk::CmdResults); break;
                default:
            }


            subParse(CommandArguments, lex);
            break;
        }


        case otk::CmdPropertyArgs: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            start(onk::CmdPropertyArgs);
            token(onk::RawText, pop(lex, otk::CmdRawArg));
            subParse(CommandArguments, lex);
            break;
        }

        case otk::CmdOptions: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            start(onk::CmdOptions);
            token(onk::RawText, pop(lex, otk::RawText));
            break;
        }

        case otk::CmdTblfm:
        case otk::CmdColumns: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            switch (cmd_kind) {
                case otk::CmdTblfm: start(onk::CmdTblfm); break;
                case otk::CmdColumns: start(onk::CmdColumns); break;
                default: throw fatalError(lex, "asdf");
            }
            token(onk::RawText, pop(lex, otk::RawText));
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
    return back();
}


OrgId OrgParser::parseStmtListItem(OrgLexer& lex) {
    __perf_trace("parsing", "parseStmtListItem");
    auto __trace = trace(lex);
    switch (lex.kind()) {
        case otk::SubtreeStars: return subParse(Subtree, lex);
        case otk::Indent: {
            skip(lex, otk::Indent);
            auto result = subParse(List, lex);
            skip(lex, otk::Dedent);
            return result;
        }

        case otk::Whitespace:
            return token(onk::Space, pop(lex, otk::Whitespace));

        case otk::MediumNewline:
        case otk::LongNewline:
        case otk::Newline:
            return token(onk::Newline, pop(lex, lex.kind()));
        case otk::TextSeparator:
            return token(onk::TextSeparator, pop(lex, otk::TextSeparator));

        case otk::TableSeparator:
        case otk::LeadingPipe: return subParse(Table, lex);
        case otk::ColonExampleLine: return subParse(ColonExample, lex);


        case otk::CmdPrefix: {
            switch (lex.kind(+1)) {
                case otk::CmdSrcBegin: return subParse(Src, lex);
                case otk::CmdExampleBegin: return subParse(Example, lex);
                case otk::CmdExportBegin:
                    return subParse(BlockExport, lex);
                case otk::CmdVerseBegin:
                case otk::CmdCenterBegin:
                case otk::CmdCommentBegin:
                case otk::CmdDynamicBlockBegin:
                case otk::CmdQuoteBegin:
                    return subParse(TextWrapCommand, lex);
                case otk::CmdTableBegin: return subParse(Table, lex);
                default: return subParse(LineCommand, lex);
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


OrgId OrgParser::parseTop(OrgLexer& lex) {
    __perf_trace("parsing", "parseTop");
    auto __trace = trace(lex);
    start(onk::StmtList);
    while (!lex.finished()) {
        if (lex.at(otk::Comment)) {
            skip(lex);
        } else {
            subParse(StmtListItem, lex);
        };
    }
    return end();
}


OrgId OrgParser::parseFull(OrgLexer& lex) {
    __perf_trace("parsing", "parseFull");
    auto __trace = trace(lex);
    auto id      = subParse(Top, lex);
    extendSubtreeTrails(OrgId(0));
    return id;
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
        CHECK(g.nodes.contains(top));
        auto fmt_id = [&](CR<Id> id) {
            return fmt("{} {}", id.format(), g.at(id).kind);
        };
        if (g.at(top).isTerminal() || g.at(top).isMono()) { return; }

        CHECK(g.at(top).kind != onk::Empty);

        Id start = top + 1;
        Id id    = start;

        if (Opt<Slice<Id>> extentOpt = g.allSubnodesOf(top)) {
            Slice<Id> extent = extentOpt.value();
            CHECK(g.nodes.contains(extent.first));
            CHECK(g.nodes.contains(extent.last));

            int     index = 0;
            Vec<Id> visited;
            while (extent.contains(id)) {
                CHECK(g.nodes.contains(id));
                aux(id);
                visited.push_back(id);

                id = id + g.at(id).getExtent();
                CHECK(g.nodes.contains(id))
                    << "next subnode"
                    << std::format(
                           "Step over the subnode of {} with extent {} "
                           "yielded id {} which is outsize of the group "
                           "range (index is {}, group size is {}), "
                           "subnode index is {}, size overflow is {}",
                           fmt_id(start),
                           extent,
                           id.getUnmasked(),
                           id.getIndex(),
                           g.size(),
                           index,
                           id - g.nodes.back());


                id = id + 1;
                ++index;
            }

            CHECK(extent.last + 1 == id) << fmt(
                "range end Iteration over subnode ranges for {} did not "
                "end at the {} -- combined subnode extent strides summed "
                "up to {}. Total subnode count is {}, full extent is {} "
                "visited subnodes {}",
                top.getUnmasked(),
                (extent.last + 1).getUnmasked(),
                id.getUnmasked(),
                index,
                extent,
                visited | rv::transform(fmt_id) | rs::to<Vec>());
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
            parser->print(
                "Found subtree on the lower level " + id.format());
            OrgId const tree = id;
            if (g.size(tree) == 0) { LOG(INFO) << g.treeRepr(tree); }

            OrgId subId = g.subnode(tree, 0);
            int   sub   = g.val(subId).text.size();
            if (level < sub) {
                OrgId stmt = g.subnode(tree, 8);
                CHECK(g.at(stmt).kind == onk::StmtList);
                id = extendSubtreeTrailsImpl(parser, stmt + 1, sub);
                CHECK(stmt + 1 <= id);
                // AUX returns next position to start looping from, so
                // the tree size is 'end - start - 1' to account for
                // the offset.

                // Extend the tree itself and nested statement list
                int stmt_extend = (id - stmt) - 1;
                int tree_extend = (id - tree) - 1;
                g.at(stmt).extend(stmt_extend);
                g.at(tree).extend(tree_extend);

                parser->print(
                    fmt("Found nested subtree tree={} stmt={} "
                        "tree-extend={} stmt-extend={}",
                        tree.format(),
                        stmt.format(),
                        tree_extend,
                        stmt_extend));

                auto treeSlice = g.allSubnodesOf(tree).value();
                auto stmtSlice = g.allSubnodesOf(tree).value();

                // Structural correctness checks -- mostly for
                // debugging of the implementation, malformed incoming
                // data is not expected.
                assertValidStructure(parser->group, tree);
                CHECK(treeSlice.last <= g.nodes.back());
                CHECK(stmtSlice.last <= g.nodes.back());
                CHECK(treeSlice.last == stmtSlice.last)
                    << "extend tree"
                    << "$# -- $#" % to_string_vec(treeSlice, stmtSlice);
                CHECK(treeSlice.contains(stmtSlice))
                    << "statement containment"
                    << "$# -- $#" % to_string_vec(treeSlice, stmtSlice);


            } else {
                parser->print(
                    "Found subtree on the same level or above "
                    + id.format());
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
