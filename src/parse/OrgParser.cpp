#include <parse/OrgParser.hpp>
#pragma clang diagnostic ignored "-Wunused-result"
#pragma clang diagnostic ignored "-Wformat-security"
#include <absl/log/log.h>
#include <absl/log/check.h>
#include <hstd/wrappers/perfetto_aux.hpp>

#ifdef ORG_USE_PERFETTO
#    define __perf_trace(name) TRACE_EVENT("parsing", name)
#else
#    define __perf_trace(...)
#endif


using otk = OrgTokenKind;
using org = OrgNodeKind;

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
};

const OrgTokSet BlockTerminator{
    otk::SubtreeStars,
};
} // namespace

void OrgParser::space(OrgLexer& lex, int line, char const* function) {
    while (lex.at(OrgTokSet{otk::Whitespace, otk::LeadingSpace})) {
        skip(lex, std::nullopt, line, function);
    }
}

void OrgParser::newline(OrgLexer& lex, int line, char const* function) {
    while (lex.at(Newline)) { skip(lex, std::nullopt, line, function); }
}

SubLexer<OrgTokenKind, OrgFill> subToEol(OrgLexer& lex) {
    SubLexer sub{lex};
    while (lex.can_search(Newline)) { sub.add(lex.pop()); }
    if (!sub.tokens.empty()) { sub.start(); }
    return sub;
}

Vec<OrgTokenId> strip(
    OrgLexer&                   lex,
    const Vec<OrgTokenId>&      tokens,
    const IntSet<OrgTokenKind>& leading,
    const IntSet<OrgTokenKind>& trailing,
    const IntSet<OrgTokenKind>& skipLeading,
    const IntSet<OrgTokenKind>& skipTrailing) {
    Vec<OrgTokenId> result;

    auto leftmost  = 0;
    auto rightmost = tokens.high();
    while (leftmost <= rightmost
           && (skipLeading + leading)
                  .contains(lex.in->at(tokens[leftmost]).kind)) {
        ++leftmost;
    }

    while (leftmost <= rightmost
           && (skipTrailing + trailing)
                  .contains(lex.in->at(tokens[rightmost]).kind)) {
        --rightmost;
    }

    for (const auto [idx, token] : enumerate(tokens)) {
        if (idx < leftmost) {
            if ((skipLeading.contains(lex.in->at(token).kind))) {
                result.push_back(token);
            }
        } else if (rightmost < idx) {
            if (skipTrailing.contains(lex.in->at(token).kind)) {
                result.push_back(token);
            }
        } else {
            result.push_back(token);
        }
    }
    return result;
}


void OrgParser::parseCSVArguments(OrgLexer& lex) {
    __perf_trace("parseCSVArguments");
    auto __trace = trace(lex);
    auto tok     = token(org::Ident, pop(lex, OrgTokSet{otk::Word}));

    if (lex.at(otk::ParBegin)) {
        skip(lex, otk::ParBegin);
        while (lex.at(otk::RawText)) {
            token(org::RawText, pop(lex, otk::RawText));
            if (lex.at(otk::Comma)) { skip(lex); }
        }
        skip(lex, otk::ParEnd);
    }
}


OrgId OrgParser::parseMacro(OrgLexer& lex) {
    __perf_trace("parseMacro");
    auto __trace = trace(lex);
    start(org::Macro);
    skip(lex, otk::CurlyBegin);
    skip(lex, otk::CurlyBegin);
    skip(lex, otk::CurlyBegin);
    parseCSVArguments(lex);
    skip(lex, otk::CurlyEnd);
    skip(lex, otk::CurlyEnd);
    skip(lex, otk::CurlyEnd);
    return end();
}


OrgId OrgParser::parseRawUrl(OrgLexer& lex) {
    __perf_trace("parseRawUrl");
    auto __trace = trace(lex);
    auto tok     = token(org::RawLink, pop(lex, otk::RawText));
    return tok;
}


OrgId OrgParser::parsePlaceholder(OrgLexer& lex) {
    __perf_trace("parsePlaceholder");
    auto __trace = trace(lex);
    if (lex.at(otk::RawText, 1)) {
        skip(lex, otk::AngleBegin);
        auto tok = token(org::Placeholder, pop(lex, otk::RawText));
        skip(lex, otk::AngleEnd);
        return tok;
    } else {
        return token(org::Punctuation, pop(lex, lex.kind()));
    }
}


OrgId OrgParser::parseTarget(OrgLexer& lex) {
    __perf_trace("parseTarget");
    auto __trace = trace(lex);
    skip(lex, otk::DoubleAngleBegin);
    auto tok = token(org::Target, pop(lex, otk::RawText));
    skip(lex, otk::DoubleAngleEnd);
    return tok;
}


OrgId OrgParser::parseLatex(OrgLexer& lex) {
    __perf_trace("parseLatex");
    auto __trace = trace(lex);
    skip(lex, otk::LatexParBegin);
    auto tok = token(org::InlineMath, pop(lex, otk::LatexInlineRaw));
    skip(lex, otk::LatexParEnd);
    return tok;
}


void OrgParser::textFold(OrgLexer& lex) {
    __perf_trace("textFold");
    auto __trace = trace(lex);
#define CASE_MARKUP(Kind)                                                 \
    case otk::Kind##Begin: {                                              \
        start(org::Kind);                                                 \
        skip(lex);                                                        \
        textFold(lex);                                                    \
        break;                                                            \
    }                                                                     \
                                                                          \
    case otk::Kind##End: {                                                \
        if (pending().kind == org::Kind) {                                \
            end();                                                        \
            skip(lex);                                                    \
        } else {                                                          \
            token(org::Punctuation, pop(lex));                            \
        }                                                                 \
        break;                                                            \
    }

#define CASE_SINGLE(Kind)                                                 \
    case otk::Kind: {                                                     \
        token(org::Kind, pop(lex, otk::Kind));                            \
        break;                                                            \
    }


    while (!lex.finished()) {
        switch (lex.kind()) {
            CASE_MARKUP(Bold);
            CASE_MARKUP(Italic);
            CASE_MARKUP(Underline);
            CASE_MARKUP(Strike);

            CASE_SINGLE(Escaped);
            CASE_SINGLE(RawText);
            CASE_SINGLE(Newline);
            CASE_SINGLE(Word);
            CASE_SINGLE(BigIdent);
            CASE_SINGLE(Punctuation);
            CASE_SINGLE(Colon);

            case otk::Whitespace:
                token(org::Space, pop(lex, lex.kind()));
                break;
            case otk::BraceEnd:
            case otk::ParEnd:
            case otk::ParBegin:
            case otk::DoubleSlash:
            case otk::Comma:
            case otk::AnyPunct:
            case otk::DoubleDash:
            case otk::Minus:
            case otk::SingleQuote:
            case otk::Ampersand:
            case otk::DoubleQuote:
            case otk::Percent:
            case otk::Semicolon:
            case otk::DoubleColon:
            case otk::CurlyEnd:
            case otk::Exclamation:
            case otk::Dollar:
            case otk::Backtick:
            case otk::Pipe:
            case otk::VerbatimEnd:
            case otk::TrailingPipe:
            case otk::MonospaceEnd:
            case otk::Circumflex: {
                token(org::Punctuation, pop(lex, lex.kind()));
                break;
            }
            case otk::CurlyBegin: {
                if (lex.at(
                        Vec{otk::CurlyBegin,
                            otk::CurlyBegin,
                            otk::CurlyBegin})) {
                    parseMacro(lex);
                } else {
                    token(org::Punctuation, pop(lex));
                }
                break;
            }

            case otk::AngleEnd: {
                token(org::Punctuation, pop(lex, lex.kind()));
                break;
            }

            case otk::MiscUnicode:
            case otk::WeekdayName:
            case otk::Time:
            case otk::Date:
            case otk::ColonPropertyName:
            case otk::SubtreePriority:
            case otk::Number: {
                token(org::Word, pop(lex, lex.kind()));
                break;
            }

            case otk::AngleBegin: parsePlaceholder(lex); break;
            case otk::TextSrcBegin: parseSrcInline(lex); break;
            case otk::HashIdent: parseHashTag(lex); break;
            case otk::RawLink:
            case otk::LinkBegin: parseLink(lex); break;
            case otk::FootnoteInlineBegin:
            case otk::FootnoteLinked: parseFootnote(lex); break;
            case otk::Symbol: parseSymbol(lex); break;

            case otk::BraceBegin: {
                if (lex.at(otk::Date, +1)) {
                    parseTimeRange(lex);
                } else {
                    token(org::Punctuation, pop(lex, lex.kind()));
                }
                break;
            }

            case otk::At: {
                token(org::AtMention, pop(lex, otk::At));
                break;
            }

            case otk::MonospaceBegin: {
                start(org::Monospace);
                skip(lex, otk::MonospaceBegin);
                while (!lex.finished() && !lex.at(otk::MonospaceEnd)) {
                    token(org::RawText, pop(lex, lex.kind()));
                }
                if (!lex.finished()) { skip(lex, otk::MonospaceEnd); }
                end();
                break;
            }

            case otk::VerbatimBegin: {
                start(org::Verbatim);
                skip(lex, otk::VerbatimBegin);
                while (!lex.finished() && !lex.at(otk::VerbatimEnd)) {
                    token(org::RawText, pop(lex, lex.kind()));
                }
                if (!lex.finished()) { skip(lex, otk::VerbatimEnd); }
                end();
                break;
            }


            case otk::DoubleAngleBegin: {
                skip(lex, otk::DoubleAngleBegin);
                SubLexer sub{lex};
                while (lex.can_search(otk::DoubleAngleEnd)) {
                    sub.add(lex.pop());
                }
                sub.start();
                parseParagraph(sub);
                skip(lex, otk::DoubleAngleEnd);
                break;
            }

            case otk::TripleAngleBegin: {
                skip(lex, otk::TripleAngleBegin);
                token(org::RadioTarget, pop(lex, otk::RawText));
                skip(lex, otk::TripleAngleEnd);
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
                    token(org::Punctuation, pop(lex, lex.kind()));
                }
                break;
            }

            default: {
                fatalError(lex, "unhandled token");
            }
        }
    }

#undef CASE_MARKUP
#undef CASE_SINGLE
#undef CASE_INLINE
}


Slice<OrgId> OrgParser::parseText(OrgLexer& lex) {
    __perf_trace("parseText");
    auto        __trace   = trace(lex);
    OrgId       first     = back();
    std::string forMsg    = getLocMsg(lex);
    int         treeStart = treeDepth();
    textFold(lex);
    int treeEnd = treeDepth();
    print(
        "Trace levels after text fold start:$#, end:$#"
        % to_string_vec(treeStart, treeEnd));

    CHECK(treeStart <= treeEnd)
        << "parseText"
        << ("Text fold created unbalanced tree - starting with depth $# "
            "ended up on depth $# on position $# (starting from $#)"
            % to_string_vec(treeStart, treeEnd, getLocMsg(lex), forMsg));

    while (treeStart < treeDepth()) {
        print("Warn, force closing content on " + getLocMsg(lex));
        end();
    }

    OrgId last = back();
    return slice(first, last);
}


OrgId OrgParser::parseLink(OrgLexer& lex) {
    __perf_trace("parseLink");
    auto __trace = trace(lex);
    if (lex.at(otk::RawLink)) {
        return token(org::RawLink, pop(lex));
    } else {
        start(org::Link);
        skip(lex, otk::LinkBegin);
        skip(lex, otk::LinkTargetBegin);
        if (lex.at(otk::LinkInternal)) {
            empty();
            token(org::RawText, pop(lex, otk::LinkInternal));
        } else if (lex.at(otk::LinkFull)) {
            empty();
            token(org::RawText, pop(lex, otk::LinkFull));
        } else {
            token(org::Ident, pop(lex, otk::LinkProtocol));
            if (lex.at(otk::RawText)) {
                token(org::RawText, pop(lex));
            } else {
                SubLexer sub{lex};
                while (
                    !lex.at(OrgTokSet{otk::LinkTargetEnd, otk::LinkEnd})) {
                    sub.add(pop(lex));
                }
                sub.start();
                parseParagraph(sub);
            }
        }

        if (lex.at(otk::LinkTargetEnd)) {
            skip(lex, otk::LinkTargetEnd);
            SubLexer sub{lex};
            while (lex.can_search(otk::LinkEnd)) { sub.add(pop(lex)); }
            if (sub.empty()) {
                LOG(FATAL) << lex.printToString(
                    [](ColStream& os, OrgToken const& t) {
                        os << os.yellow() << escape_for_write(t.value.text)
                           << os.end() << fmt1(t.value);
                    });
            }
            sub.start();
            parseParagraph(sub);
        } else {
            empty();
        }


        skip(lex, otk::LinkEnd);
        return end();
    }
}


OrgId OrgParser::parseInlineMath(OrgLexer& lex) {
    __perf_trace("parseInlineMath");
    auto __trace = trace(lex);

    start(org::InlineMath);


    return end();
}


OrgId OrgParser::parseSymbol(OrgLexer& lex) {
    __perf_trace("parseSymbol");
    auto __trace = trace(lex);
    start(org::Symbol);
    token(org::Ident, pop(lex, otk::Symbol));

    start(org::InlineStmtList);
    while (lex.at(otk::BraceBegin)) {
        skip(lex, otk::BraceBegin);
        token(org::RawText, pop(lex, otk::RawText));
        skip(lex, otk::BraceEnd);
    }
    end();

    start(org::InlineStmtList);
    while (lex.at(otk::CurlyBegin)) {
        if (lex.at(Vec{otk::CurlyBegin, otk::CurlyEnd})) {
            empty();
            skip(lex, otk::CurlyBegin);
            skip(lex, otk::CurlyEnd);
        } else {
            auto sub = SubLexer(
                lex.in, lex.getInside({otk::CurlyBegin}, {otk::CurlyEnd}));
            start(org::Paragraph);
            parseText(sub);
            end();
        }
    }
    end();

    return end();
}


OrgId OrgParser::parseHashTag(OrgLexer& lex) {
    __perf_trace("parseHashTag");
    auto __trace = trace(lex);
    start(org::HashTag);
    space(lex);
    if (lex.at(otk::At)) {
        // Org-mode suppors tags like '@work' etc.
        token(org::RawText, pop(lex, otk::At));
    } else {
        token(
            org::RawText,
            pop(lex, OrgTokSet{otk::HashIdent, otk::Word, otk::BigIdent}));
    }

    if (lex.at(otk::DoubleHash)) {
        skip(lex, otk::DoubleHash);
        if (lex.at(OrgTokSet{otk::HashIdent, otk::Word, otk::BigIdent})) {
            parseHashTag(lex);

        } else {
            skip(lex, otk::BraceBegin);
            while (!lex.finished() && !lex.at(otk::BraceEnd)) {
                parseHashTag(lex);
                if (lex.at(otk::Comma)) { skip(lex); }
                space(lex);
            }
            skip(lex, otk::BraceEnd);
        }
    }
    return end();
}


OrgId OrgParser::parseTimeStamp(OrgLexer& lex) {
    __perf_trace("parseTimeStamp");
    auto __trace = trace(lex);
    expect(lex, OrgTokSet{otk::BraceBegin, otk::AngleBegin});
    bool active = lex.at(otk::AngleBegin);
    skip(lex, active ? otk::AngleBegin : otk::BraceBegin);
    if (lex.at(otk::DynamicTimeContent)) {
        if (active) {
            start(org::DynamicActiveTime);
        } else {
            start(org::DynamicInactiveTime);
        }

        auto sub = token(org::RawText, pop(lex, otk::DynamicTimeContent));

        end();
    } else {
        if (active) {
            start(org::StaticActiveTime);
        } else {
            start(org::StaticInactiveTime);
        }

        // Date part is usually used, but I think supporting *time* stamps
        // also makes sense
        if (lex.at(otk::Date)) {
            token(org::RawText, pop(lex, otk::Date));
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
            token(org::RawText, pop(lex, otk::Time));
            space(lex);
        } else {
            empty();
        }

        if (lex.at(Vec{otk::StrikeBegin, otk::Number})) {
            skip(lex);
            token(org::RawText, pop(lex, otk::Number));
            space(lex);
        } else {
            empty();
        }

        if (lex.at(otk::TimeRepeater)) {
            token(org::RawText, pop(lex, otk::TimeRepeater));
            space(lex);
        } else {
            empty();
        }


        end();
    }

    skip(lex, active ? otk::AngleEnd : otk::BraceEnd);
    return back();
}


OrgId OrgParser::parseTimeRange(OrgLexer& lex) {
    __perf_trace("parseTimeRange");
    auto            __trace = trace(lex);
    const OrgTokSet times{
        otk::BraceBegin,
        otk::BraceEnd,
        otk::AngleBegin,
        otk::AngleEnd,
        otk::DynamicTimeContent,
        otk::Date,
        otk::WeekdayName,
        otk::Time,
        otk::TimeRepeater,
        otk::Number,
        otk::StrikeBegin,
        otk::Whitespace,
    };


    if (lex.ahead(times, OrgTokSet{otk::DoubleDash})) {
        start(org::TimeRange);
        parseTimeStamp(lex);
        skip(lex, otk::DoubleDash);
        parseTimeStamp(lex);
        print("???");
        space(lex);
        if (lex.at(otk::TimeArrow)) {
            skip(lex, otk::TimeArrow);
            space(lex);
            token(org::SimpleTime, pop(lex, otk::Time));
        } else {
            empty();
        }

        return end();
    } else {
        return parseTimeStamp(lex);
    }
}


OrgId OrgParser::parseFootnote(OrgLexer& lex) {
    __perf_trace("parseFootnote");
    auto __trace = trace(lex);
    if (lex.at(otk::FootnoteLinked)) {
        start(org::Footnote);
        empty();
        token(org::RawText, pop(lex));
        return end();
    } else {
        start(org::InlineFootnote);
        skip(lex, otk::FootnoteInlineBegin);
        SubLexer sub{lex};
        while (!lex.finished() && !lex.at(otk::BraceEnd)) {
            sub.add(pop(lex));
        }
        parseParagraph(sub);
        skip(lex, otk::BraceEnd);
        return end();
    }
}


OrgId OrgParser::parseIdent(OrgLexer& lex) {
    __perf_trace("parseIdent");
    auto __trace = trace(lex);
    auto tok     = token(org::Ident, pop(lex, otk::Word));
    return tok;
}


OrgId OrgParser::parseSrcInline(OrgLexer& lex) {
    __perf_trace("parseSrcInline");
    auto __trace = trace(lex);
    start(org::SrcInlineCode);
    {
        token(org::Ident, pop(lex, otk::TextSrcBegin)); // lang

        { // header args
            empty();
        }
        start(org::CodeLine); // body
        {
            int balance = 1;
            skip(lex, otk::CurlyBegin);
            while (!lex.finished() && 0 < balance) {
                if (lex.at(otk::CurlyEnd)) {
                    if (balance == 1) {
                        skip(lex, otk::CurlyEnd);
                    } else {
                        token(org::CodeText, pop(lex));
                    }
                    --balance;
                } else {
                    token(org::CodeText, pop(lex));
                }
            }
        }
        end();
    }
    return end();
}


OrgId OrgParser::parseTable(OrgLexer& lex) {
    __perf_trace("parseTable");
    auto __trace = trace(lex);
    start(org::Table);

    while (lex.at(OrgTokSet{otk::LeadingPipe, otk::TableSeparator})) {
        switch (lex.kind()) {
            case otk::LeadingPipe: {
                start(org::TableRow);
                while (lex.at(OrgTokSet{otk::LeadingPipe, otk::Pipe})) {
                    start(org::TableCell);
                    SubLexer sub{lex};
                    skip(lex);
                    while (
                        !lex.at(OrgTokSet{otk::Pipe, otk::TrailingPipe})) {
                        sub.add(pop(lex, lex.kind()));
                    }
                    sub.start();
                    parseParagraph(sub);
                    end();
                }
                skip(lex, otk::TrailingPipe);
                skip(lex, Newline);
                end();
                break;
            }
            case otk::TableSeparator: {
                lex.next();
                break;
            }
            default: {
            }
        }
    }

    return end();
}


OrgId OrgParser::parseParagraph(OrgLexer& lex) {
    start(org::Paragraph);
    auto nodes = parseText(lex);
    end();
    return back();
}


OrgId OrgParser::parseInlineParagraph(OrgLexer& lex) {
    __perf_trace("parseInlineParagraph");
    auto __trace = trace(lex);
    return parseParagraph(lex);
}


OrgId OrgParser::parseTopParagraph(OrgLexer& lex) {
    __perf_trace("parseTopParagraph");
    auto __trace = trace(lex);
    return parseParagraph(lex);
}


OrgId OrgParser::parseCommandArguments(OrgLexer& lex) {
    __perf_trace("parseCommandArguments");
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(Newline)) {
        return empty();
    } else {
        start(org::InlineStmtList);
        while (lex.at(OrgTokSet{otk::CmdRawArg, otk::CmdColonIdent})) {
            if (lex.at(otk::CmdColonIdent)) {
                start(org::CmdValue);
                {
                    token(org::Ident, pop(lex, otk::CmdColonIdent));
                    space(lex);
                    token(org::RawText, pop(lex, otk::CmdRawArg));
                }
                end();
            } else {
                start(org::CmdValue);
                {
                    empty();
                    space(lex);
                    token(org::RawText, pop(lex, otk::CmdRawArg));
                }
                end();
            }
            space(lex);
        }

        return end();
    }
}


OrgId OrgParser::parseSrcArguments(OrgLexer& lex) {
    __perf_trace("parseSrcArguments");
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(Newline)) {
        empty();
        return empty();
    } else {
        start(org::CmdArguments);
        start(org::InlineStmtList);
        {
            while (lex.at(otk::CmdFlag)) {
                token(org::CmdFlag, pop(lex, otk::CmdFlag));
            }
        }
        end();
        parseCommandArguments(lex);
        return end();
    }
}


OrgId OrgParser::parseTextWrapCommand(OrgLexer& lex) {
    __perf_trace("parseTextWrapCommand");
    skip(lex, otk::CmdPrefix);
    auto __trace = trace(lex);

    OrgTokenKind endTok;
    switch (lex.kind()) {
        case otk::CmdVerseBegin:
            start(org::VerseBlock);
            endTok = otk::CmdVerseEnd;
            break;
        case otk::CmdCenterBegin:
            start(org::CenterBlock);
            endTok = otk::CmdCenterEnd;
            break;
        case otk::CmdQuoteBegin:
            start(org::QuoteBlock);
            endTok = otk::CmdQuoteEnd;
            break;
        case otk::CmdAdmonitionBegin:
            start(org::AdmonitionBlock);
            endTok = otk::CmdAdmonitionEnd;
            break;
        default: fatalError(lex, "unhandled token");
    }

    skip(lex);

    if (lex.at(Newline)) {
        empty();
    } else {
        space(lex);
        parseCommandArguments(lex);
        space(lex);
    }

    skip(lex, Newline);


    while (lex.can_search(Vec<otk>{otk::CmdPrefix, endTok})) {
        parseStmtListItem(lex);
        if (lex.at(BlockTerminator)) { break; }
    }

    skip(lex, otk::CmdPrefix);
    skip(lex, endTok);
    return end();
}


OrgId OrgParser::parseBlockExport(OrgLexer& lex) {
    __perf_trace("parseExample");
    auto __trace = trace(lex);
    start(org::BlockExport);

    skip(lex, otk::CmdPrefix);
    skip(lex, otk::CmdExportBegin);

    // command arguments
    space(lex);
    token(org::Ident, pop(lex, otk::CmdRawArg));
    space(lex);
    parseSrcArguments(lex);
    newline(lex);

    // command content
    while (lex.at(OrgTokSet{otk::SrcContent, otk::Newline})) {
        token(org::RawText, pop(lex, lex.kind()));
    }

    skip(lex, otk::CmdPrefix);
    skip(lex, otk::CmdExportEnd);

    return end();
}


OrgId OrgParser::parseExample(OrgLexer& lex) {
    __perf_trace("parseExample");
    auto __trace = trace(lex);
    start(org::Example);

    skip(lex, otk::CmdPrefix);
    skip(lex, otk::CmdExampleBegin);

    { // command arguments
        parseCommandArguments(lex);
        newline(lex);
    }

    { // command content
        while (lex.at(OrgTokSet{otk::CmdExampleLine, otk::Newline})) {
            token(org::RawText, pop(lex));
        }
    }

    skip(lex, otk::CmdPrefix);
    skip(lex, otk::CmdExampleEnd);

    return end();
}


OrgId OrgParser::parseSrc(OrgLexer& lex) {
    __perf_trace("parseSrc");
    auto __trace = trace(lex);
    start(org::SrcCode);
    skip(lex, otk::CmdPrefix);
    skip(lex, otk::CmdSrcBegin);
    // header_args_lang
    {
        space(lex);
        if (lex.at(otk::CmdRawArg)) {
            const auto lang = pop(lex, otk::CmdRawArg);
            if (lex.val().text.empty()) {
                empty();
            } else {
                token(org::Ident, lang);
            }
        } else {
            empty();
        }

        space(lex);

        parseSrcArguments(lex);
    };
    // body
    {

        start(org::StmtList);
        skip(lex, otk::CmdContentBegin);
        while (lex.can_search(Vec{otk::CmdPrefix, otk::CmdSrcEnd})) {
            start(org::CodeLine);
            while (lex.can_search(
                OrgTokSet{otk::CmdContentEnd, otk::Newline})) {
                switch (lex.kind()) {
                    case otk::SrcContent: {
                        token(org::CodeText, pop(lex, otk::SrcContent));
                        break;
                    }
                    case otk::ParBegin: {
                        skip(lex, otk::ParBegin);
                        skip(lex, otk::Word);
                        skip(lex, otk::Colon);
                        start(org::CodeCallout);
                        token(org::Ident, pop(lex, otk::Word));
                        end();
                        skip(lex, otk::ParEnd);
                        break;
                    }
                    case otk::DoubleAngleBegin: {
                        skip(lex, otk::DoubleAngleBegin);
                        start(org::CodeTangle);
                        parseCSVArguments(lex);
                        end();
                        skip(lex, otk::DoubleAngleEnd);
                        break;
                    }
                    default: {
                        fatalError(
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
    // eval_result
    { empty(); };
    skip(lex, otk::CmdPrefix);
    skip(lex, otk::CmdSrcEnd);
    return end();
}


OrgId OrgParser::parseListItem(OrgLexer& lex) {
    __perf_trace("parseListItem");
    auto __trace = trace(lex);
    start(org::ListItem);
    // prefix, 0
    {
        token(
            org::RawText,
            pop(lex,
                OrgTokSet{
                    otk::LeadingNumber,
                    otk::TreeClock,
                    otk::LeadingMinus}));
    }
    space(lex);
    skip(lex, otk::StmtListBegin);
    // counter, 1
    {
        empty(); // TODO parse counter
    }
    // checkbox 2
    {
        if (lex.at(otk::Checkbox)) {
            token(org::Checkbox, pop(lex, otk::Checkbox));
        } else {
            empty();
        }
    }
    // tag, 3
    bool isAnnotatedParagraph = false;
    { empty(); }
    // completion, 4
    { empty(); }
    // body, 5
    start(org::StmtList);
    {
        while (lex.can_search(otk::StmtListEnd)) {
            parseStmtListItem(lex);
        }
        skip(lex, otk::StmtListEnd);
        skip(lex, otk::ListItemEnd);
        if (lex.at(otk::Indent)) { parseStmtListItem(lex); }
    }
    end();
    return end();
}


OrgId OrgParser::parseList(OrgLexer& lex) {
    __perf_trace("parseList");
    auto __trace = trace(lex);
    start(org::List);
    while (lex.at(OrgTokSet{
        otk::LeadingMinus, otk::LeadingNumber, otk::TreeClock})) {
        parseListItem(lex);
        if (lex.at(otk::SameIndent)) { skip(lex); }
    }

    return end();
}


OrgId OrgParser::parseSubtreeLogbook(OrgLexer& lex) {
    __perf_trace("parseSubtreeLogbook");
    auto __trace = trace(lex);
    start(org::Logbook);
    skip(lex, otk::ColonLogbook);
    newline(lex);

    space(lex);

    skip(lex, otk::ListBegin);
    auto result = parseList(lex);
    if (lex.at(otk::StmtListEnd)) {
        skip(lex, otk::StmtListEnd);
        skip(lex, otk::ListItemEnd);
    }
    skip(lex, otk::ListEnd);

    space(lex);
    skip(lex, otk::ColonEnd);
    return end();
}


OrgId OrgParser::parseSubtreeProperties(OrgLexer& lex) {
    __perf_trace("parseSubtreeProperties");
    auto __trace = trace(lex);
    skip(lex, otk::ColonProperties);
    skip(lex, otk::Newline);
    start(org::PropertyList);
    while (lex.can_search(otk::ColonEnd)) {
        trace(lex, "Parse single subtree property");
        start(org::Property);
        auto head = lex.kind();
        auto name = token(org::RawText, pop(lex, head));
        switch (head) {
            case otk::ColonLiteralProperty: {
                token(org::RawText, pop(lex, otk::RawText));
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
                LOG(FATAL)
                    << fmt("Unhandled property kind parse {}", head);
            }
        }
        skip(lex, otk::Newline);
        end();
    }

    skip(lex, otk::ColonEnd);
    return end();
}


OrgId OrgParser::parseSubtreeDrawer(OrgLexer& lex) {
    __perf_trace("parseSubtreeDrawer");
    auto __trace = trace(lex);
    start(org::Drawer);

    while (lex.at(OrgTokSet{otk::ColonProperties, otk::ColonLogbook})) {
        switch (lex.tok().kind) {
            case otk::ColonProperties: parseSubtreeProperties(lex); break;
            case otk::ColonLogbook: parseSubtreeLogbook(lex); break;
            default:
        }

        newline(lex);
        space(lex);
    }

    return end();
}

void tokenFormat(ColStream& os, OrgToken const& t) { os << t->text; }

OrgId OrgParser::parseSubtreeCompletion(OrgLexer& lex) {
    __perf_trace("parseSubtreeCompletion");
    auto __trace = trace(lex);
    if (lex.at(Newline) || lex.at(otk::Colon)) {
        return empty();

    } else {
        start(org::Completion);
        return end();
    }
}


OrgId OrgParser::parseSubtreeTodo(OrgLexer& lex) {
    __perf_trace("parseSubtreeTodo");
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(otk::BigIdent)) {
        return token(org::BigIdent, pop(lex, otk::BigIdent));
    } else {
        return empty();
    }
}


OrgId OrgParser::parseSubtreeUrgency(OrgLexer& lex) {
    __perf_trace("parseSubtreeUrgency");
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(otk::SubtreePriority)) {
        return token(org::SubtreeUrgency, pop(lex, otk::SubtreePriority));
    } else {
        return empty();
    }
}


OrgId OrgParser::parseSubtreeTitle(OrgLexer& lex) {
    __perf_trace("parseSubtreeTitle");
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

        return Newline.contains((lex.begin() + ahead.size())->kind);
    };

    while (lex.can_search(Newline) && !is_at_subtree_tags(lex)) {
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
    __perf_trace("parseSubtreeTags");
    auto __trace = trace(lex);
    if (lex.at(otk::Colon)) {
        start(org::InlineStmtList);
        while (
            lex.at(otk::Colon)
            && lex.at(OrgTokSet{otk::Word, otk::At, otk::BigIdent}, +1)) {
            skip(lex, otk::Colon);
            parseHashTag(lex);
        }
        skip(lex, otk::Colon);
        return end();
    } else {
        return empty();
    }
}


OrgId OrgParser::parseSubtreeTimes(OrgLexer& lex) {
    __perf_trace("parseSubtreeTimes");
    auto __trace = trace(lex);
    if (lex.at(otk::LeadingSpace) && lex.at(otk::TreeTime, +1)) {
        space(lex);
        start(org::StmtList);
        while (lex.at(otk::TreeTime)) {
            start(org::InlineStmtList);
            token(org::Word, pop(lex));
            space(lex);
            parseTimeStamp(lex);
            space(lex);
            end();
        }

        return end();
    } else {
        return empty();
    }
}


OrgId OrgParser::parseSubtree(OrgLexer& lex) {
    __perf_trace("parseSubtree");
    auto __trace = trace(lex);
    start(org::Subtree);
    // prefix

    token(org::RawText, pop(lex, otk::SubtreeStars)); // 0
    parseSubtreeTodo(lex);                            // 1
    parseSubtreeUrgency(lex);                         // 2
    space(lex);                                       //
    parseSubtreeTitle(lex);                           // 3
    parseSubtreeCompletion(lex);                      // 4
    parseSubtreeTags(lex);                            // 5

    if (lex.at(otk::Newline)) { newline(lex); }
    parseSubtreeTimes(lex); // 6


    if (lex.at(otk::Newline)) { newline(lex); }

    if (lex.at(OrgTokSet{otk::ColonProperties, otk::ColonLogbook})) { // 7
        parseSubtreeDrawer(lex);
    } else {
        empty();
    }


    start(org::StmtList); // 8
    end();
    return end();
}


OrgId OrgParser::parseOrgFile(OrgLexer& lex) {
    __perf_trace("parseOrgFile");
    auto __trace = trace(lex);
    start(org::File);
    LOG(FATAL);
    return end();
}


OrgId OrgParser::parseLineCommand(OrgLexer& lex) {
    __perf_trace("parseLineCommand");
    auto __trace  = trace(lex);
    auto cmd_kind = lex.kind(+1);
    switch (cmd_kind) {
        case otk::CmdTitle: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            start(org::CommandTitle);
            parseParagraph(lex);
            break;
        }

        case otk::CmdCaption: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            start(org::CommandCaption);
            start(org::CommandArguments);
            auto sub = subToEol(lex);
            if (sub.empty()) {
                parseParagraph(sub);
            } else {
                empty();
            }
            end();
            break;
        }

        case otk::CmdCreator:
        case otk::CmdAuthor:
        case otk::CmdLatexHeader:
        case otk::CmdLanguage: {
            switch (cmd_kind) {
                case otk::CmdCreator: start(org::CommandCreator); break;
                case otk::CmdLanguage: start(org::CommandLanguage); break;
                case otk::CmdAuthor: start(org::CommandAuthor); break;
                case otk::CmdOptions: start(org::CommandOptions); break;
                case otk::CmdLatexHeader: start(org::LatexHeader); break;
                case otk::CmdColumns: start(org::Columns); break;
                default:
            }

            skip(lex, otk::CmdPrefix);
            skip(lex);
            while (lex.at(otk::RawText)) {
                token(org::RawText, pop(lex, otk::RawText));
                if (lex.at(otk::Whitespace)) { space(lex); }
            }
            break;
        }

        case otk::CmdFiletags: {
            skip(lex, otk::CmdPrefix);
            skip(lex, otk::CmdFiletags);
            start(org::Filetags);
            while (lex.at(otk::Colon) && lex.at(otk::Word, +1)) {
                parseHashTag(lex);
            }
            skip(lex, otk::Colon);
            break;
        }

#if false
        case otk::CmdAttrHtml: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            start(org::CommandAttrHtml);
            parseSrcArguments(lex);
            break;
        }

        case otk::CmdHtmlHead: {
            skip(lex, otk::CmdPrefix);
            skip(lex, otk::CmdHtmlHead);
            start(org::HtmlHead);
            token(org::RawText, pop(lex, otk::RawText));
            break;
        }

        case otk::CmdLatexClassOptions: {
            skip(lex, otk::CmdPrefix);
            skip(lex, otk::CmdLatexClassOptions);
            start(org::LatexClassOptions);
            token(org::RawText, pop(lex, otk::RawText));
            break;
        }

        case otk::CmdLatexClass:
        case otk::CmdLatexCompiler: {
            skip(lex, otk::CmdPrefix);
            switch (cmd_kind) {
                case otk::CmdLatexCompiler:
                    start(org::LatexCompiler);
                    skip(lex, otk::CmdLatexCompiler);
                    break;
                case otk::CmdLatexClass:
                    start(org::LatexClass);
                    skip(lex, otk::CmdLatexClass);
                    break;
                default:
            }

            token(org::Ident, pop(lex, otk::Word));
            break;
        }
#endif

        case otk::CmdPropertyRaw: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            start(org::CmdPropertyRaw);
            token(org::RawText, pop(lex, otk::RawText));
            break;
        }

        case otk::CmdPropertyText: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            start(org::CmdPropertyArgs);
            token(org::RawText, pop(lex, otk::CmdRawArg));
            parseCommandArguments(lex);
            parseParagraph(lex);
            break;
        }

        case otk::CmdPropertyArgs: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            start(org::CmdPropertyArgs);
            token(org::RawText, pop(lex, otk::CmdRawArg));
            parseCommandArguments(lex);
            break;
        }

        case otk::CmdOptions: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            start(org::CommandOptions);
            token(org::RawText, pop(lex, otk::RawText));
            break;
        }

        case otk::CmdTblfm:
        case otk::CmdColumns: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            switch (cmd_kind) {
                case otk::CmdTblfm: start(org::CommandTblfm); break;
                case otk::CmdColumns: start(org::Columns); break;
                default: LOG(FATAL);
            }
            token(org::RawText, pop(lex, otk::RawText));
            break;
        }


        default: {
            LOG(FATAL) << fmt(
                "Unhandled token kind {} {}", lex.kind(+1), lex);
        }
    }

    // Placeholder statement list that might be extended in a latter pass
    start(org::StmtList);
    end();
    // End main tree that was started in the case statement
    end();

    return back();
}


OrgId OrgParser::parseStmtListItem(OrgLexer& lex) {
    __perf_trace("parseStmtListItem");
    auto __trace = trace(lex);
    switch (lex.kind()) {
        case otk::SubtreeStars: return parseSubtree(lex);
        case otk::ListBegin: {
            skip(lex, otk::ListBegin);
            auto result = parseList(lex);
            if (lex.at(otk::StmtListEnd)) {
                skip(lex, otk::StmtListEnd);
                skip(lex, otk::ListItemEnd);
            }
            skip(lex, otk::ListEnd);
            return result;
        }

        case otk::Indent: {
            lex.next();
            auto result = parseList(lex);
            if (lex.at(otk::StmtListEnd)) {
                skip(lex, otk::StmtListEnd);
                skip(lex, otk::ListItemEnd);
            }
            skip(lex, otk::Dedent);
            return result;
        }

        case otk::Whitespace:
            return token(org::Space, pop(lex, otk::Whitespace));

        case otk::MediumNewline:
        case otk::LongNewline:
        case otk::Newline:
            return token(org::Newline, pop(lex, lex.kind()));
        case otk::TextSeparator:
            return token(org::TextSeparator, pop(lex, otk::TextSeparator));

        case otk::TableSeparator:
        case otk::LeadingPipe: return parseTable(lex);

        case otk::CmdPrefix: {
            switch (lex.kind(+1)) {
                case otk::CmdSrcBegin: return parseSrc(lex);
                case otk::CmdExampleBegin: return parseExample(lex);
                case otk::CmdExportBegin: return parseBlockExport(lex);
                case otk::CmdVerseBegin:
                case otk::CmdCenterBegin:
                case otk::CmdQuoteBegin: return parseTextWrapCommand(lex);
                default: return parseLineCommand(lex);
            }
        }
        default: {
            SubLexer sub{lex};
            while (lex.hasNext() && !lex.at(ParagraphTerminator)) {
                sub.add(lex.pop());
            }

            sub.start();
            return parseParagraph(sub);
        }
    }
}


OrgId OrgParser::parseTop(OrgLexer& lex) {
    __perf_trace("parseTop");
    auto __trace = trace(lex);
    start(org::StmtList);
    while (lex.hasNext()) {
        if (lex.at(otk::Comment)) {
            skip(lex);
        } else {
            parseStmtListItem(lex);
        };
    }
    return end();
}


OrgId OrgParser::parseFull(OrgLexer& lex) {
    __perf_trace("parseFull");
    auto __trace = trace(lex);
    auto id      = parseTop(lex);
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
        if (g.at(top).isTerminal() || g.at(top).isMono()) { return; }

        CHECK(g.at(top).kind != org::Empty);

        Id start = top + 1;
        Id id    = start;

        if (Opt<Slice<Id>> extentOpt = g.allSubnodesOf(top)) {
            Slice<Id> extent = extentOpt.value();
            CHECK(g.nodes.contains(extent.first));
            CHECK(g.nodes.contains(extent.last));

            int index = 0;
            while (extent.contains(id)) {
                CHECK(g.nodes.contains(id));
                aux(id);

                id = id + g.at(id).getExtent();
                CHECK(g.nodes.contains(id))
                    << "next subnode"
                    << std::format(
                           "Step over the subnode of $# with extent $# "
                           "yielded id $# which is outsize of the group "
                           "range (index is $#, group size is $#), "
                           "subnode index is $#, size overflow is $#",
                           start.getUnmasked(),
                           extent,
                           id.getUnmasked(),
                           id.getIndex(),
                           g.size(),
                           index,
                           id - g.nodes.back());


                id = id + 1;
                ++index;
            }

            CHECK(extent.last + 1 == id)
                << "range end"
                << "Iteration over subnode ranges for $# did not end at "
                   "the $# -- combined subnode extent strides summed up "
                   "to "
                   "$#. Total subnode count is $#, full extent is $#"
                       % to_string_vec(
                           top.getUnmasked(),
                           (extent.last + 1).getUnmasked(),
                           id.getUnmasked(),
                           index,
                           extent);
        }
    };

    aux(id);
}


void OrgParser::extendSubtreeTrails(OrgId position) {
    __perf_trace("extendSubtreeTrails");
    Func<OrgId(OrgId, int)> aux;
    aux = [&](OrgId id, int level) -> OrgId {
        OrgId const start = id;
        // Iterate over all nodes until the end of the group or until exit
        // condition is met. This assumes non-restructured tree that has
        // subnodes positioned flatlyl on the top level
        auto& g = *group;
        while (id <= g.nodes.back()) {
            // NOTE: 'back' returns the last node, not one-past-last
            OrgNode node = g.at(id);
            if (node.kind == org::Subtree) {
                print("Found subtree on the lower level " + id.format());
                OrgId const tree  = id;
                OrgId       subId = g.subnode(tree, 0);
                int         sub   = g.val(subId).text.size();
                if (level < sub) {
                    OrgId stmt = g.subnode(tree, 8);
                    CHECK(g.at(stmt).kind == org::StmtList);
                    id = aux(stmt + 1, sub);
                    CHECK(stmt + 1 <= id);
                    // AUX returns next position to start looping from, so
                    // the tree size is 'end - start - 1' to account for
                    // the offset.

                    // Extend the tree itself and nested statement list
                    g.at(stmt).extend((id - stmt) - 1);

                    g.at(tree).extend((id - tree) - 1);

                    auto treeSlice = g.allSubnodesOf(tree).value();
                    auto stmtSlice = g.allSubnodesOf(tree).value();

                    // Structural correctness checks -- mostly for
                    // debugging of the implementation, malformed incoming
                    // data is not expected.
                    assertValidStructure(group, tree);
                    CHECK(treeSlice.last <= g.nodes.back());
                    CHECK(stmtSlice.last <= g.nodes.back());
                    CHECK(treeSlice.last == stmtSlice.last)
                        << "extend tree"
                        << "$# -- $#"
                               % to_string_vec(treeSlice, stmtSlice);
                    CHECK(treeSlice.contains(stmtSlice))
                        << "statement containment"
                        << "$# -- $#"
                               % to_string_vec(treeSlice, stmtSlice);


                } else {
                    print(
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
    };

    aux(position, 0);
    assertValidStructure(group, position);
}
