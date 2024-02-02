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
};
} // namespace

void OrgParser::space(OrgLexer& lex, int line, char const* function) {
    while (lex.at(otk::Space)) { skip(lex, std::nullopt, line, function); }
}

void OrgParser::newline(OrgLexer& lex, int line, char const* function) {
    while (lex.at(Newline)) { skip(lex, std::nullopt, line, function); }
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
    skip(lex, otk::MacroBegin);
    parseCSVArguments(lex);
    skip(lex, otk::MacroEnd);
    return end();
}


OrgId OrgParser::parseRawUrl(OrgLexer& lex) {
    __perf_trace("parseRawUrl");
    auto __trace = trace(lex);
    auto tok     = token(org::RawLink, pop(lex, otk::RawUrl));
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
            auto msg                                                      \
                = "Mismatched kind Beginings pending tree was '$#', but " \
                  "found '$#' at $# parser $#"                            \
                % to_string_vec(                                          \
                      pending().kind,                                     \
                      org::Kind,                                          \
                      getLocMsg(lex),                                     \
                      __LINE__);                                          \
            print(msg);                                                   \
            LOG(FATAL) << msg;                                            \
            fail(pop(lex, otk::Kind##End));                               \
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
            CASE_MARKUP(Verbatim);
            CASE_MARKUP(Monospace);
            CASE_MARKUP(Backtick);

            CASE_SINGLE(Space);
            CASE_SINGLE(Escaped);
            CASE_SINGLE(RawText);
            CASE_SINGLE(Newline);
            CASE_SINGLE(Word);
            CASE_SINGLE(BigIdent);
            CASE_SINGLE(Punctuation);
            CASE_SINGLE(Colon);

            case otk::BraceEnd:
            case otk::ParEnd:
            case otk::ParBegin:
            case otk::QuoteEnd:
            case otk::QuoteBegin:
            case otk::MaybeWord:
            case otk::DoubleSlash:
            case otk::Comma:
            case otk::Circumflex: {
                token(org::Punctuation, pop(lex, lex.kind()));
                break;
            }

            case otk::AngleEnd: {
                token(org::Punctuation, pop(lex, lex.kind()));
                break;
            }

            case otk::AngleBegin: parsePlaceholder(lex); break;
            case otk::SrcBegin: parseSrcInline(lex); break;
            case otk::HashTag: parseHashTag(lex); break;
            case otk::LinkBegin: parseLink(lex); break;
            case otk::MacroBegin: parseMacro(lex); break;
            case otk::RawUrl: parseRawUrl(lex); break;
            case otk::FootnoteBegin: parseFootnote(lex); break;
            case otk::SymbolBegin: parseSymbol(lex); break;

            case otk::DollarBegin:
            case otk::LatexParBegin:
            case otk::DoubleDollarBegin:
            case otk::LatexBraceBegin: parseInlineMath(lex); break;

            case otk::BraceBegin: {
                if (lex.at(otk::StaticTimeDatePart, +1)) {
                    parseTimeRange(lex);
                } else {
                    token(org::Punctuation, pop(lex, lex.kind()));
                }
                break;
            }

            case otk::AtMention: {
                token(org::AtMention, pop(lex, otk::AtMention));
                break;
            }

            case otk::DoubleAngleBegin: {
                skip(lex, otk::DoubleAngleBegin);
                token(org::Target, pop(lex, otk::RawText));
                skip(lex, otk::DoubleAngleEnd);
                break;
            }

            case otk::TripleAngleBegin: {
                skip(lex, otk::TripleAngleBegin);
                token(org::RadioTarget, pop(lex, otk::RawText));
                skip(lex, otk::TripleAngleEnd);
                break;
            }

            default: {
                throw UnhandledToken(lex);
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
        token(org::RawText, pop(lex, otk::LinkTarget));
    }
    skip(lex, otk::LinkTargetEnd);
    if (lex.at(otk::LinkDescriptionBegin)) {
        auto sub = SubLexer(
            lex.in,
            lex.getInside(
                {otk::LinkDescriptionBegin}, {otk::LinkDescriptionEnd}));
        start(org::Paragraph);
        parseText(sub);
        end();

    } else {
        empty();
    }

    skip(lex, otk::LinkEnd);
    return end();
}


OrgId OrgParser::parseInlineMath(OrgLexer& lex) {
    __perf_trace("parseInlineMath");
    auto       __trace   = trace(lex);
    const auto startKind = lex.tok().kind;
    const auto regular   = OrgTokSet{otk::DollarBegin, otk::LatexParBegin};
    const auto display   = OrgTokSet{
        otk::DoubleDollarBegin, otk::LatexBraceBegin};

    skip(lex, regular + display);
    start(
        regular.contains(startKind) ? org::InlineMath : org::DisplayMath);

    OrgTokenKind End;
    switch (startKind) {
        case otk::DollarBegin: {
            skip(lex, otk::DollarEnd);
            break;
        }
        case otk::DoubleDollarBegin: {
            skip(lex, otk::DoubleDollarEnd);
            break;
        }
        case otk::LatexParBegin: {
            skip(lex, otk::LatexParEnd);
            break;
        }
        case otk::LatexBraceBegin: {
            skip(lex, otk::LatexBraceEnd);
            break;
        }
        default: {
            assert(false);
        }
    }

    return end();
}


OrgId OrgParser::parseSymbol(OrgLexer& lex) {
    __perf_trace("parseSymbol");
    auto __trace = trace(lex);
    start(org::Symbol);
    token(org::Ident, pop(lex, otk::SymbolBegin));

    start(org::InlineStmtList);
    while (lex.at(otk::BraceBegin)) {
        skip(lex, otk::BraceBegin);
        token(org::RawText, pop(lex, otk::RawText));
        skip(lex, otk::BraceEnd);
    }
    end();

    start(org::InlineStmtList);
    while (lex.at(otk::CurlyStart)) {
        if (lex.at(Vec{otk::CurlyStart, otk::CurlyEnd})) {
            empty();
            skip(lex, otk::CurlyStart);
            skip(lex, otk::CurlyEnd);
        } else {
            auto sub = SubLexer(
                lex.in, lex.getInside({otk::CurlyStart}, {otk::CurlyEnd}));
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
    if (lex.at(otk::AtMention)) {
        // Org-mode suppors tags like '@work' etc.
        token(org::RawText, pop(lex, otk::AtMention));
    } else {
        token(org::RawText, pop(lex, OrgTokSet{otk::HashTag, otk::Word}));
    }

    if (lex.at(otk::HashTagSub)) {
        skip(lex, otk::HashTagSub);
        if (lex.at(OrgTokSet{otk::HashTag, otk::Word})) {
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
        if (lex.at(otk::StaticTimeDatePart)) {
            token(org::RawText, pop(lex, otk::StaticTimeDatePart));
            space(lex);
        } else {
            empty();
        }

        // Day can sometimes be added to the timestamp
        if (lex.at(otk::StaticTimeDayPart)) {
            token(org::RawText, pop(lex, otk::StaticTimeDayPart));
            space(lex);
        } else {
            empty();
        }

        if (lex.at(otk::StaticTimeClockPart)) {
            token(org::RawText, pop(lex, otk::StaticTimeClockPart));
            space(lex);
        } else {
            empty();
        }

        if (lex.at(otk::Number)) {
            token(org::RawText, pop(lex, otk::Number));
            space(lex);
        } else {
            empty();
        }

        if (lex.at(otk::StaticTimeRepeater)) {
            token(org::RawText, pop(lex, otk::StaticTimeRepeater));
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
        otk::StaticTimeDatePart,
        otk::StaticTimeDayPart,
        otk::StaticTimeClockPart,
        otk::StaticTimeRepeater,
        otk::Number,
    };


    if (lex.ahead(times, OrgTokSet{otk::TimeDash})) {
        start(org::TimeRange);
        parseTimeStamp(lex);
        skip(lex, otk::TimeDash);
        parseTimeStamp(lex);
        space(lex);
        if (lex.at(otk::TimeArrow)) {
            skip(lex, otk::TimeArrow);
            space(lex);
            token(org::SimpleTime, pop(lex, otk::TimeDuration));
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
    // TODO replace 'footnote start' + '::' with a 'inline footnote start'
    // / 'footnote start nodes'
    skip(lex, otk::FootnoteBegin);
    if (lex.at(otk::Colon)) {
        start(org::InlineFootnote);
        skip(lex, otk::Colon);
        Vec<OrgTokenId> sub;
        while (!lex.at(otk::BraceEnd)) { sub.push_back(lex.pop()); }
        SubLexer subLexer{lex.in, sub};
        start(org::Paragraph);
        parseText(subLexer);
        end();
    } else {
        start(org::Footnote);
        parseIdent(lex);
    }

    skip(lex, otk::BraceEnd);

    return end();
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
    skip(lex, otk::SrcBegin);
    {
        token(org::Ident, pop(lex, otk::SrcName));
        start(org::CodeLine);
        token(org::CodeText, pop(lex, otk::SrcBody));
        end();
    }
    skip(lex, otk::SrcEnd);
    return end();
}


OrgId OrgParser::parseTable(OrgLexer& lex) {
    __perf_trace("parseTable");
    auto __trace = trace(lex);
    start(org::Table);
    skip(lex, otk::TblBegin);
    skip(lex, otk::CmdArguments);
    empty();

    ParseCb parseContent = [this](OrgLexer& lex) {
        auto sub = SubLexer(
            lex.in,
            lex.getInside({otk::CmdContentBegin}, {otk::CmdContentEnd}));

        return parseTop(sub);
    };

    while (!lex.at(otk::TblEnd)) {
        switch (lex.kind()) {
            case otk::TblPipeBegin: {
                start(org::TableRow);
                empty();
                empty();

                skip(lex, otk::TblPipeBegin);
                start(org::TableCell);
                {
                    empty();
                    parseContent(lex);
                }
                end();

                while (lex.at(otk::TblPipeSeparator)) {
                    skip(lex, otk::TblPipeSeparator);
                    start(org::TableCell);
                    {
                        empty();
                        parseContent(lex);
                    }
                    end();
                }

                skip(lex, otk::TblPipeEnd);
                end();
                break;
            }
            case otk::TblPipeCellBegin: {
                start(org::TableRow);
                empty();
                empty();

                skip(lex, otk::TblPipeCellBegin);
                start(org::TableCell);
                {

                    empty();
                    parseContent(lex);
                }
                end();

                while (lex.at(otk::TblPipeCellBegin)) {
                    skip(lex, otk::TblPipeCellBegin);
                    start(org::TableCell);
                    {
                        empty();
                        parseContent(lex);
                    }
                    end();
                }

                end();
                break;
            }
            case otk::TblRowSpec: {
                start(org::TableRow);
                empty();
                skip(lex, otk::TblRowSpec);
                skip(lex, otk::CmdArguments);
                empty();
                start(org::TableCell);
                {
                    empty();
                    parseContent(lex);
                }
                end();
                while (lex.at(otk::TblCellSpec)) {
                    skip(lex, otk::TblCellSpec);
                    skip(lex, otk::CmdArguments);
                    start(org::TableCell);
                    {
                        empty();
                        parseContent(lex);
                    }
                    end();
                }

                end();
                break;
            }
            case otk::TblEnd: {
                break;
            }
            default: {
                assert(false);
            }
        };
    };
    skip(lex, otk::TblEnd);
    return end();
}


OrgId OrgParser::parseParagraph(OrgLexer& lex, bool onToplevel) {
    start(org::Paragraph);
    auto nodes = parseText(lex);
    end();
    return back();
}


OrgId OrgParser::parseInlineParagraph(OrgLexer& lex) {
    __perf_trace("parseInlineParagraph");
    auto __trace = trace(lex);
    return parseParagraph(lex, false);
}


OrgId OrgParser::parseTopParagraph(OrgLexer& lex) {
    __perf_trace("parseTopParagraph");
    auto __trace = trace(lex);
    return parseParagraph(lex, false);
}


OrgId OrgParser::parseCommandArguments(OrgLexer& lex) {
    __perf_trace("parseCommandArguments");
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(Newline)) {
        return empty();
    } else {
        start(org::InlineStmtList);
        while (lex.at(OrgTokSet{otk::CmdValue, otk::CmdKey})) {
            if (lex.at(otk::CmdKey)) {
                start(org::CmdValue);
                {
                    token(org::Ident, pop(lex, otk::CmdKey));
                    space(lex);
                    token(org::RawText, pop(lex, otk::CmdValue));
                }
                end();
            } else {
                start(org::CmdValue);
                {
                    empty();
                    space(lex);
                    token(org::RawText, pop(lex, otk::CmdValue));
                }
                end();
            }
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
        default: throw UnhandledToken(lex);
    }

    skip(lex);

    if (lex.at(otk::Newline)) {
        empty();
    } else {
        if (lex.at(otk::RawText)) {
            skip(lex);
        } else if (lex.at(otk::Word)) {
            skip(lex);
        };
    }

    skip(lex, otk::Newline);

    while (!lex.at(Vec<otk>{otk::CmdPrefix, endTok})) {
        parseStmtListItem(lex);
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
    token(org::Ident, pop(lex, otk::CmdValue));
    space(lex);
    parseSrcArguments(lex);
    newline(lex);

    // command content
    while (lex.at(OrgTokSet{otk::CodeText, otk::Newline})) {
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
        while (lex.at(OrgTokSet{otk::RawText, otk::Newline})) {
            token(org::RawText, pop(lex, lex.kind()));
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
        const auto lang = pop(lex, otk::CmdValue);
        if (lex.val().getText().empty()) {
            empty();
        } else {
            token(org::Ident, lang);
        }
        space(lex);

        parseSrcArguments(lex);
    };
    // body
    {

        start(org::StmtList);
        skip(lex, otk::CmdContentBegin);
        while (!lex.at(otk::CmdContentEnd)) {
            start(org::CodeLine);
            while (!lex.at(OrgTokSet{otk::CmdContentEnd, otk::Newline})) {
                switch (lex.kind()) {
                    case otk::CodeText: {
                        token(org::CodeText, pop(lex, otk::CodeText));
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
                    case otk::CmdContentEnd: {
                        break;
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
                        LOG(FATAL) << fmt(
                            "Unhandled code parse token {}", lex.tok());
                    }
                }
            }
            if (lex.at(otk::Newline)) { skip(lex); }
            end(); // finish code line
        }

        skip(lex, otk::CmdContentEnd);
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
            pop(lex, OrgTokSet{otk::ListItemBegin, otk::ListClock}));
    }
    space(lex);
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
    {
        if (lex.at(otk::ListDescBegin)) {
            isAnnotatedParagraph = true;
            skip(lex, otk::ListDescBegin);
            start(org::AnnotatedParagraph);
            start(org::ListTag);
            parseParagraph(lex, false);
            end();
            skip(lex, otk::DoubleColon);
            skip(lex, otk::ListDescEnd);
            end();
        } else {
            empty();
        }
    }
    // completion, 4
    { empty(); }
    // body, 5
    start(org::StmtList);
    {
        skip(lex, otk::StmtListBegin);
        while (!lex.at(otk::StmtListEnd)) { parseStmtListItem(lex); }
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
    while (lex.at(OrgTokSet{otk::ListItemBegin, otk::ListClock})) {
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
    while (!lex.at(otk::ColonEnd)) {
        trace(lex, "Parse single subtree property");
        start(org::Property);
        auto head = lex.kind();
        auto name = token(org::RawText, pop(lex, head));
        switch (head) {
            case otk::PropRawKey: {
                token(org::RawText, pop(lex, otk::RawText));
                break;
            }
            case otk::PropTextKey: {
                space(lex);
                parseParagraph(lex, false);
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

    while (lex.at(OrgTokSet{
        otk::ColonProperties, otk::ColonLogbook, otk::ColonDescription})) {
        switch (lex.tok().kind) {
            case otk::ColonProperties: parseSubtreeProperties(lex); break;
            case otk::ColonLogbook: parseSubtreeLogbook(lex); break;
            case otk::ColonDescription: {
                skip(lex, otk::ColonDescription);
                start(org::SubtreeDescription);
                newline(lex);
                {
                    parseParagraph(lex, false);
                    skip(lex, otk::ColonEnd);
                }
                end();
                break;
            }
            default:
        }

        newline(lex);
        space(lex);
    }

    return end();
}

void tokenFormat(ColStream& os, OrgToken const& t) { os << t->getText(); }

OrgId OrgParser::parseSubtreeCompletion(OrgLexer& lex) {
    __perf_trace("parseSubtreeCompletion");
    auto __trace = trace(lex);
    if (lex.at(otk::Newline) || lex.at(otk::SubtreeTagSeparator)
        || lex.at(otk::SubtreeEnd)) {
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
    if (lex.at(otk::SubtreeTodoState)) {
        return token(org::BigIdent, pop(lex, otk::SubtreeTodoState));
    } else {
        return empty();
    }
}


OrgId OrgParser::parseSubtreeUrgency(OrgLexer& lex) {
    __perf_trace("parseSubtreeUrgency");
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(otk::SubtreeUrgency)) {
        return token(org::SubtreeUrgency, pop(lex, otk::SubtreeUrgency));
    } else {
        return empty();
    }
}


OrgId OrgParser::parseSubtreeTitle(OrgLexer& lex) {
    __perf_trace("parseSubtreeTitle");
    auto __trace = trace(lex);
    space(lex);
    return parseParagraph(lex, false);
}


OrgId OrgParser::parseSubtreeTags(OrgLexer& lex) {
    __perf_trace("parseSubtreeTags");
    auto __trace = trace(lex);
    if (lex.at(otk::SubtreeTagSeparator)) {
        start(org::InlineStmtList);
        while (lex.at(otk::SubtreeTagSeparator)
               && lex.at(otk::HashTag, +1)) {
            skip(lex, otk::SubtreeTagSeparator);
            parseHashTag(lex);
        }
        skip(lex, otk::SubtreeTagSeparator);
        return end();
    } else {
        return empty();
    }
}


OrgId OrgParser::parseSubtreeTimes(OrgLexer& lex) {
    __perf_trace("parseSubtreeTimes");
    auto __trace = trace(lex);
    start(org::StmtList);
    if (lex.ahead(OrgTokSet{otk::Space}, OrgTokSet{otk::SubtreeTime})) {
        skip(lex, otk::Space);

        while (lex.at(otk::SubtreeTime)) {
            start(org::TimeAssoc);
            if (lex.at(otk::SubtreeTime)) {
                token(org::BigIdent, pop(lex, otk::SubtreeTime));
            } else {
                empty();
            }
            space(lex);
            parseTimeStamp(lex);
            space(lex);
            end();
        }

        newline(lex);
    } else {
        print("No subtree time");
    }

    return end();
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
    if (false) { // 6 TODO
        skip(lex, otk::Newline);
        parseSubtreeTimes(lex);
        newline(lex);
    } else {
        empty();
    }

    if (lex.at(otk::Newline)) { newline(lex); }

    if (lex.at(otk::ColonProperties)) { // 7
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
    if (lex.at(otk::QuoteBegin)) {
        skip(lex);
        token(org::RawText, pop(lex, otk::RawText));
        skip(lex, otk::QuoteEnd);
    } else {
        token(org::RawText, pop(lex, otk::RawText));
    }
    return end();
}


OrgId OrgParser::parseLineCommand(OrgLexer& lex) {
    __perf_trace("parseLineCommand");
    auto __trace  = trace(lex);
    auto cmd_kind = lex.kind(+1);
    switch (cmd_kind) {
        case otk::CmdInclude: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            start(org::CommandInclude);
            parseOrgFile(lex);

            if (lex.at(otk::CmdValue)) {
                token(org::Ident, pop(lex, otk::CmdValue));
            } else {
                empty();
            }

            if (lex.at(otk::CmdValue)) {
                token(org::Ident, pop(lex, otk::CmdValue));
            } else {
                empty();
            }

            parseSrcArguments(lex);
            break;
        }

        case otk::CmdAttrHtml: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            start(org::CommandAttrHtml);
            parseSrcArguments(lex);
            break;
        }

        case otk::CmdTitle: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            start(org::CommandTitle);
            parseParagraph(lex, false);
            break;
        }

        case otk::CmdCaption: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            start(org::CommandCaption);
            start(org::CommandArguments);
            parseParagraph(lex, false);
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
                if (lex.at(otk::Space)) { space(lex); }
            }
            break;
        }

        case otk::CmdFiletags: {
            skip(lex, otk::CmdPrefix);
            skip(lex, otk::CmdFiletags);
            start(org::Filetags);
            while (lex.at(otk::SubtreeTagSeparator)
                   && lex.at(otk::HashTag, +1)) {
                parseHashTag(lex);
            }
            skip(lex, otk::SubtreeTagSeparator);
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
            token(org::RawText, pop(lex, otk::CmdValue));
            parseCommandArguments(lex);
            parseParagraph(lex, false);
            break;
        }

        case otk::CmdPropertyArgs: {
            skip(lex, otk::CmdPrefix);
            skip(lex);
            start(org::CmdPropertyArgs);
            token(org::RawText, pop(lex, otk::CmdValue));
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
            start(org::CommandTblfm);
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
        case otk::TblBegin: return parseTable(lex);
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

        case otk::Word: {
            SubLexer sub{lex.in, {}};
            while (lex.hasNext() && lex.at(ParagraphTerminator)) {
                sub.add(lex.pop());
            }

            return parseParagraph(sub, true);
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

        case otk::Space: return token(org::Space, pop(lex, otk::Space));
        case otk::Newline:
            return token(org::Newline, pop(lex, otk::Newline));
        case otk::TextSeparator:
            return token(org::TextSeparator, pop(lex, otk::TextSeparator));

        case otk::CmdPrefix: {
            switch (lex.kind(+1)) {
                case otk::CmdSrcBegin: return parseSrc(lex);
                case otk::CmdExampleBegin: return parseExample(lex);
                case otk::CmdExportBegin: return parseBlockExport(lex);
                case otk::CmdCenterBegin:
                case otk::CmdAdmonitionBegin:
                case otk::CmdQuoteBegin: return parseTextWrapCommand(lex);
                default: return parseLineCommand(lex);
            }
        }
        default: {
            throw UnhandledToken(lex);
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
    extendAttachedTrails(OrgId(0));
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
                int         sub   = g.val(subId).getText().size();
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


void OrgParser::extendAttachedTrails(OrgId position) {
    __perf_trace("extendAttachedTrails");
    Func<OrgId(OrgId)> aux;
    aux = [&](OrgId id) -> OrgId {
        auto& g = *group;

        OrgNode node = g.at(id);
        if (OrgAttachableCommands.contains(node.kind)) {
            OrgId const annotation = id;
            // Get ID of the nested statement list
            OrgId const stmt = g.subnode(annotation, 1);
            CHECK(g.at(stmt).kind == org::StmtList);
            // Next element after command block is the non-optional newline
            // to separate them.
            CHECK(g.at(stmt + 1).kind == org::Newline);
            OrgId   nextId = stmt + 2;
            OrgNode next   = g.at(nextId);

            // DLOG(INFO) << "Next element from" << annotation << "has
            // kind"
            //          << next.kind << "at" << nextId;

            if (OrgAttachableCommands.contains(next.kind)) {
                // Nested annotations are recursively placed inside
                // each other by extending the trail
                id = aux(nextId);
                g.at(annotation).extend((id - annotation) - 1);
                g.at(stmt).extend((id - stmt) - 1);

            } else if (OrgTrailableCommands.contains(next.kind)) {
                // Element that can be put as the final part of the
                // trailable statement
                if (auto nextSub = g.allSubnodesOf(nextId)) {
                    OrgId const end = nextSub->last;
                    g.at(annotation).extend(end - annotation);
                    g.at(stmt).extend(end - stmt);
                    id = end + 1;
                } else {
                    LOG(WARNING) << "No subnodes found in the next node"
                                 << nextId.format();
                    ++id;
                }

            } else {
                // Next element after line command is neither trailable
                // nor another command. Switching the subnode kind to
                // empty.
                g.at(stmt) = getEmpty();
                ++id;
            }
        } else {
            ++id;
        }

        return id;
    };

    while (position < group->nodes.back()) { position = aux(position); }
}
