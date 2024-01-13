#include <parse/OrgParser.hpp>
#pragma clang diagnostic ignored "-Wunused-result"
#pragma clang diagnostic ignored "-Wformat-security"
#include <absl/log/log.h>
#include <absl/log/check.h>


using otk = OrgTokenKind;
using org = OrgNodeKind;
using ock = OrgCommandKind;

#include "OrgParserMacros.hpp"


void space(OrgLexer& lex) {
    while (lex.at(otk::Space) || lex.at(otk::SkipSpace)) { lex.next(); }
}


void skipSpace(OrgLexer& lex) {
    while (lex.at(otk::SkipSpace) || lex.at(otk::Space)) { lex.next(); }
}


void newline(OrgLexer& lex) {
    while (lex.at(otk::Newline) || lex.at(otk::SkipNewline)) {
        lex.next();
    }
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
    __trace();
    auto tok = token(org::Ident, pop(lex, otk::Ident));
    __token(tok);

    if (lex.at(otk::ParBegin)) {
        __skip(lex, otk::ParBegin);
        while (lex.at(otk::RawText)) {
            token(org::RawText, pop(lex, otk::RawText));
            if (lex.at(otk::Comma)) { lex.next(); }
        }
        __skip(lex, otk::ParEnd);
    }
}


OrgId OrgParser::parseMacro(OrgLexer& lex) {
    __perf_trace("parseMacro");
    __trace();
    __start(org::Macro);
    __skip(lex, otk::MacroBegin);
    parseCSVArguments(lex);
    __skip(lex, otk::MacroEnd);
    __end_return();
}


OrgId OrgParser::parseRawUrl(OrgLexer& lex) {
    __perf_trace("parseRawUrl");
    __trace();
    auto tok = token(org::RawLink, pop(lex, otk::RawUrl));
    __token(tok);
    return tok;
}


OrgId OrgParser::parsePlaceholder(OrgLexer& lex) {
    __perf_trace("parsePlaceholder");
    __trace();
    __skip(lex, otk::GroupBegin);
    __skip(lex, otk::AngleBegin);
    auto tok = token(org::Placeholder, pop(lex, otk::RawText));
    __token(tok);
    __skip(lex, otk::AngleEnd);
    __skip(lex, otk::GroupEnd);

    return tok;
}


OrgId OrgParser::parseTarget(OrgLexer& lex) {
    __perf_trace("parseTarget");
    __trace();
    __skip(lex, otk::GroupBegin);
    __skip(lex, otk::DoubleAngleBegin);
    auto tok = token(org::Target, pop(lex, otk::RawText));
    __token(tok);
    __skip(lex, otk::DoubleAngleEnd);
    __skip(lex, otk::GroupEnd);

    return tok;
}


OrgId OrgParser::parseLatex(OrgLexer& lex) {
    __perf_trace("parseLatex");
    __trace();
    __skip(lex, otk::GroupBegin);
    __skip(lex, otk::LatexParBegin);
    auto tok = token(org::InlineMath, pop(lex, otk::LatexInlineRaw));
    __token(tok);
    __skip(lex, otk::LatexParEnd);
    __skip(lex, otk::GroupEnd);
    return tok;
}


void OrgParser::textFold(OrgLexer& lex) {
    __perf_trace("textFold");
    __trace();
#define CASE_MARKUP(Kind)                                                 \
    case otk::Kind##Begin: {                                              \
        __start(org::Kind);                                               \
        lex.next();                                                       \
        textFold(lex);                                                    \
        break;                                                            \
    }                                                                     \
                                                                          \
    case otk::Kind##End: {                                                \
        if (pending().kind == org::Kind) {                                \
            __end();                                                      \
            lex.next();                                                   \
        } else {                                                          \
            auto msg                                                      \
                = "Mismatched kind Beginings pending tree was '$#', but " \
                  "found '$#' at $# parser $#"                            \
                % to_string_vec(                                          \
                      pending().kind,                                     \
                      org::Kind,                                          \
                      getLocMsg(lex),                                     \
                      __LINE__);                                          \
            __print(msg);                                                 \
            LOG(FATAL) << msg;                                          \
            fail(pop(lex, otk::Kind##End));                               \
        }                                                                 \
        break;                                                            \
    }

#define CASE_SINGLE(Kind)                                                 \
    case otk::Kind: {                                                     \
        auto t = token(org::Kind, pop(lex, otk::Kind));                   \
        __token(t);                                                       \
        break;                                                            \
    }

#define CASE_INLINE(Kind)                                                 \
    case otk::Kind##InlineBegin: {                                        \
        __start(org::Kind);                                               \
        lex.next();                                                       \
        textFold(lex);                                                    \
        break;                                                            \
    }                                                                     \
                                                                          \
    case otk::Kind##InlineEnd: {                                          \
        if (pending().kind == org::Kind) {                                \
            __end();                                                      \
            lex.next();                                                   \
        } else {                                                          \
            fail(pop(lex, otk::Kind##InlineEnd));                         \
        }                                                                 \
        break;                                                            \
    }


    while (!lex.finished()) {
        switch (lex.kind()) {
            CASE_MARKUP(Bold);
            CASE_MARKUP(Italic);
            CASE_MARKUP(Underline);
            CASE_MARKUP(Strike);
            CASE_MARKUP(Verbatim);
            CASE_MARKUP(Angle);
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

            CASE_INLINE(Bold);
            CASE_INLINE(Italic);
            CASE_INLINE(Backtick);

            case otk::Circumflex: {
                auto sub = token(
                    org::Punctuation, pop(lex, otk::Circumflex));
                __token(sub);
                break;
            }

            case otk::DoubleSlash: {
                auto sub = token(
                    org::Punctuation, pop(lex, otk::DoubleSlash));
                __token(sub);
                break;
            }

            case otk::MaybeWord: {
                auto sub = token(
                    org::Punctuation, pop(lex, otk::MaybeWord));
                __token(sub);
                break;
            }

                // CASE_MARKUP(Quote);
            case otk::QuoteBegin: {
                auto sub = token(
                    org::Punctuation, pop(lex, otk::QuoteBegin));
                __token(sub);
                break;
            }

            case otk::QuoteEnd: {
                auto sub = token(
                    org::Punctuation, pop(lex, otk::QuoteEnd));
                __token(sub);
                break;
            }

                // CASE_MARKUP(Par);
            case otk::ParBegin: {
                auto sub = token(
                    org::Punctuation, pop(lex, otk::ParBegin));
                __token(sub);
                break;
            }

            case otk::ParEnd: {
                auto sub = token(org::Punctuation, pop(lex, otk::ParEnd));
                __token(sub);
                break;
            }

            case otk::SrcBegin: parseSrcInline(lex); break;
            case otk::ActiveTimeBegin:
            case otk::InactiveTimeBegin: parseTimeRange(lex); break;
            case otk::HashTag: parseHashTag(lex); break;
            case otk::LinkBegin: parseLink(lex); break;
            case otk::MacroBegin: parseMacro(lex); break;
            case otk::RawUrl: parseRawUrl(lex); break;
            case otk::FootnoteBegin: parseFootnote(lex); break;

            case otk::DollarBegin:
            case otk::LatexParBegin:
            case otk::DoubleDollarBegin:
            case otk::LatexBraceBegin: parseInlineMath(lex); break;

            case otk::SkipAny: {
                auto any = token(org::SkipAny, pop(lex, otk::SkipAny));
                __token(any);
                break;
            }

            case otk::AtMention: {
                auto any = token(org::AtMention, pop(lex, otk::AtMention));
                __token(any);
                break;
            }

            case otk::DoubleAngleBegin: {
                __skip(lex, otk::DoubleAngleBegin);
                auto tmp = token(org::Target, pop(lex, otk::RawText));
                __token(tmp);
                __skip(lex, otk::DoubleAngleEnd);
                break;
            }

            case otk::TripleAngleBegin: {
                __skip(lex, otk::TripleAngleBegin);
                auto target = token(
                    org::RadioTarget, pop(lex, otk::RawText));
                __token(target);
                __skip(lex, otk::TripleAngleEnd);
                break;
            }

            case otk::BoldInline:
            case otk::ItalicInline:
            case otk::VerbatimInline:
            case otk::MonospaceInline:
            case otk::BacktickInline:
            case otk::UnderlineInline:
            case otk::StrikeInline: {
                throw UnhandledToken(
                    lex,
                    "Non-directional inline markup token incountered "
                    "during text parsing");
            }

            case otk::GroupBegin: {
                switch (lex.kind(+1)) {
                    case otk::LinkBegin: {
                        (void)parseLink(lex);
                        break;
                    }
                    case otk::FootnoteBegin: {
                        (void)parseFootnote(lex);
                        break;
                    }
                    case otk::AngleBegin: {
                        (void)parsePlaceholder(lex);
                        break;
                    }
                    case otk::LatexParBegin: {
                        (void)parseLatex(lex);
                        break;
                    }
                    case otk::SymbolBegin: {
                        (void)parseSymbol(lex);
                        break;
                    }
                    case otk::DoubleAngleBegin: {
                        (void)parseTarget(lex);
                        break;
                    }
                    default: throw UnhandledToken(lex);
                }
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
    __trace();
    OrgId       first     = back();
    std::string forMsg    = getLocMsg(lex);
    int         treeStart = treeDepth();
    textFold(lex);
    int treeEnd = treeDepth();
    __print(
        "Trace levels after text fold start:$#, end:$#"
        % to_string_vec(treeStart, treeEnd));

    CHECK(treeStart <= treeEnd)
        << "parseText"
        << ("Text fold created unbalanced tree - starting with depth $# "
            "ended up on depth $# on position $# (starting from $#)"
            % to_string_vec(treeStart, treeEnd, getLocMsg(lex), forMsg));

    while (treeStart < treeDepth()) {
        __print("Warn, force closing content on " + getLocMsg(lex));
        __end();
    }

    OrgId last = back();
    return slice(first, last);
}


OrgId OrgParser::parseLink(OrgLexer& lex) {
    __perf_trace("parseLink");
    __trace();
    __start(org::Link);
    __skip(lex, otk::GroupBegin);
    __skip(lex, otk::LinkBegin);
    __skip(lex, otk::LinkTargetBegin);
    if (lex.at(otk::LinkInternal)) {
        empty();
        auto inter = token(org::RawText, pop(lex, otk::LinkInternal));
        __token(inter);
    } else if (lex.at(otk::LinkFull)) {
        empty();
        auto full = token(org::RawText, pop(lex, otk::LinkFull));
        __token(full);
    } else {
        auto prot = token(org::Ident, pop(lex, otk::LinkProtocol));
        __token(prot);
        auto target = token(org::RawText, pop(lex, otk::LinkTarget));
        __token(target);
    }
    __skip(lex, otk::LinkTargetEnd);
    if (lex.at(otk::LinkDescriptionBegin)) {
        auto sub = SubLexer(
            lex.in,
            lex.getInside(
                {otk::LinkDescriptionBegin}, {otk::LinkDescriptionEnd}));
        __start(org::Paragraph);
        parseText(sub);
        __end();

    } else {
        empty();
    }

    __skip(lex, otk::LinkEnd);
    __skip(lex, otk::GroupEnd);
    __end_return();
}


OrgId OrgParser::parseInlineMath(OrgLexer& lex) {
    __perf_trace("parseInlineMath");
    __trace();
    const auto startKind = lex.tok().kind;
    const auto regular   = OrgTokSet{otk::DollarBegin, otk::LatexParBegin};
    const auto display   = OrgTokSet{
        otk::DoubleDollarBegin, otk::LatexBraceBegin};

    __skip(lex, regular + display);
    __start(
        regular.contains(startKind) ? org::InlineMath : org::DisplayMath);

    OrgTokenKind End;
    switch (startKind) {
        case otk::DollarBegin: {
            __skip(lex, otk::DollarEnd);
            break;
        }
        case otk::DoubleDollarBegin: {
            __skip(lex, otk::DoubleDollarEnd);
            break;
        }
        case otk::LatexParBegin: {
            __skip(lex, otk::LatexParEnd);
            break;
        }
        case otk::LatexBraceBegin: {
            __skip(lex, otk::LatexBraceEnd);
            break;
        }
        default: {
            assert(false);
        }
    }

    __end_return();
}


OrgId OrgParser::parseSymbol(OrgLexer& lex) {
    __perf_trace("parseSymbol");
    __trace();
    __skip(lex, otk::GroupBegin);
    __skip(lex, otk::SymbolBegin);
    __start(org::Symbol);
    token(org::Ident, pop(lex, otk::Ident));

    while (lex.at(otk::MetaBraceBegin)) {
        __skip(lex, otk::MetaBraceBegin);
        token(org::RawText, pop(lex, otk::MetaBraceBody));
        __skip(lex, otk::MetaBraceEnd);
    }

    while (lex.at(otk::MetaArgsBegin)) {
        __skip(lex, otk::MetaArgsBegin);
        parseParagraph(lex, false);
        __skip(lex, otk::MetaArgsEnd);
    }

    __skip(lex, otk::GroupEnd);

    __end_return();
}


OrgId OrgParser::parseHashTag(OrgLexer& lex) {
    __perf_trace("parseHashTag");
    __trace();
    __start(org::HashTag);
    space(lex);
    if (lex.at(otk::AtMention)) {
        // Org-mode suppors tags like '@work' etc.
        token(org::RawText, pop(lex, otk::AtMention));
    } else {
        token(org::RawText, pop(lex, otk::HashTag));
    }

    if (lex.at(otk::HashTagSub)) {
        __skip(lex, otk::HashTagSub);
        if (lex.at(otk::HashTag)) {
            parseHashTag(lex);

        } else {
            __skip(lex, otk::HashTagBegin);
            while (!lex.finished() && !lex.at(otk::HashTagEnd)) {
                parseHashTag(lex);
                if (lex.at(otk::Comma)) { lex.next(); }
            }
            __skip(lex, otk::HashTagEnd);
        }
    }
    __end_return();
}


OrgId OrgParser::parseTimeStamp(OrgLexer& lex) {
    __perf_trace("parseTimeStamp");
    __trace();
    expect(lex, OrgTokSet{otk::InactiveTimeBegin, otk::ActiveTimeBegin});
    bool active = lex.at(otk::ActiveTimeBegin);
    __skip(lex, active ? otk::ActiveTimeBegin : otk::InactiveTimeBegin);
    if (!lex.at(otk::DynamicTimeContent)) {
        if (active) {
            __start(org::StaticActiveTime);
        } else {
            __start(org::StaticInactiveTime);
        }

        // Date part is usually used, but I think supporting *time* stamps
        // also makes sense
        if (lex.at(otk::StaticTimeDatePart)) {
            auto year = token(
                org::RawText, pop(lex, otk::StaticTimeDatePart));
            __token(year);
            skipSpace(lex);
        } else {
            empty();
        }

        // Day can sometimes be added to the timestamp
        if (lex.at(otk::StaticTimeDayPart)) {
            auto day = token(
                org::RawText, pop(lex, otk::StaticTimeDayPart));
            __token(day);

            skipSpace(lex);
        } else {
            empty();
        }

        if (lex.at(otk::StaticTimeClockPart)) {
            auto clock = token(
                org::RawText, pop(lex, otk::StaticTimeClockPart));
            __token(clock);
            skipSpace(lex);
        } else {
            empty();
        }

        if (lex.at(otk::StaticTimeRepeater)) {
            auto repeater = token(
                org::RawText, pop(lex, otk::StaticTimeRepeater));
            __token(repeater);
            skipSpace(lex);
        } else {
            empty();
        }


        __end();

    } else {
        if (active) {
            __start(org::DynamicActiveTime);
        } else {
            __start(org::DynamicInactiveTime);
        }

        auto sub = token(org::RawText, pop(lex, otk::DynamicTimeContent));

        __end();
    }

    __skip(lex, active ? otk::ActiveTimeEnd : otk::InactiveTimeEnd);
    return back();
}


OrgId OrgParser::parseTimeRange(OrgLexer& lex) {
    __perf_trace("parseTimeRange");
    __trace();
    const OrgTokSet times{
        otk::SkipSpace,
        otk::InactiveTimeBegin,
        otk::InactiveTimeEnd,
        otk::ActiveTimeBegin,
        otk::ActiveTimeEnd,
        otk::DynamicTimeContent,
        otk::StaticTimeDatePart,
        otk::StaticTimeDayPart,
        otk::StaticTimeClockPart,
        otk::StaticTimeRepeater,
    };


    if (lex.ahead(times, OrgTokSet{otk::TimeDash})) {
        __start(org::TimeRange);
        parseTimeStamp(lex);
        __skip(lex, otk::TimeDash);
        parseTimeStamp(lex);
        skipSpace(lex);
        if (lex.at(otk::TimeArrow)) {
            __skip(lex, otk::TimeArrow);
            skipSpace(lex);
            token(org::SimpleTime, pop(lex, otk::TimeDuration));
        } else {
            empty();
        }

        __end_return();
    } else {
        return parseTimeStamp(lex);
    }


    // __end_return();

    // if (lex.ahead(times, OrgTokSet{otk::TimeDash})) {
    //     __start(org::TimeRange);
    //     // IMPLEMENT check for identical start/end bracket categories:
    //     // `[]--[]` or `<>--<>` but not `<>--[]`
    //     token(org::Time, pop(lex, times));
    //     __skip(lex, otk::TimeDash);
    //     token(org::Time, pop(lex, times));

    //     if (lex.ahead(otk::SkipSpace, otk::TimeArrow)) {
    //         space(lex);
    //         __skip(lex, otk::TimeArrow);
    //         space(lex);
    //         token(org::SimpleTime, pop(lex, otk::TimeDuration));
    //     } else {
    //         empty();
    //     }

    //     __end_return();
    // } else {
    //     return token(org::Time, pop(lex, times));
    // }
}


OrgId OrgParser::parseFootnote(OrgLexer& lex) {
    __perf_trace("parseFootnote");
    __trace();
    __skip(lex, otk::GroupBegin);
    // TODO replace 'footnote start' + '::' with a 'inline footnote start'
    // / 'footnote start nodes'
    __skip(lex, otk::FootnoteBegin);
    if (lex.at(otk::Colon)) {
        __start(org::Footnote);
        __skip(lex, otk::Colon);
        parseIdent(lex);
    } else {
        __start(org::InlineFootnote);
        __skip(lex, otk::DoubleColon);
        parseInlineParagraph(lex);
    }

    __skip(lex, otk::FootnoteEnd);
    __skip(lex, otk::GroupEnd);

    __end_return();
}


OrgId OrgParser::parseIdent(OrgLexer& lex) {
    __perf_trace("parseIdent");
    __trace();
    auto tok = token(org::Ident, pop(lex, otk::Ident));
    __token(tok);
    return tok;
}


OrgId OrgParser::parseSrcInline(OrgLexer& lex) {
    __perf_trace("parseSrcInline");
    __trace();
    __start(org::SrcInlineCode);
    __skip(lex, otk::SrcBegin);
    {
        token(org::Ident, pop(lex, otk::SrcName));
        __start(org::CodeLine);
        token(org::CodeText, pop(lex, otk::SrcBody));
        __end();
    }
    __skip(lex, otk::SrcEnd);
    __end_return();
}


OrgId OrgParser::parseTable(OrgLexer& lex) {
    __perf_trace("parseTable");
    __trace();
    __start(org::Table);
    __skip(lex, otk::TblBegin);
    __skip(lex, otk::CmdArguments);
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
                __start(org::TableRow);
                empty();
                empty();

                __skip(lex, otk::TblPipeBegin);
                __start(org::TableCell);
                {
                    empty();
                    parseContent(lex);
                }
                __end();

                while (lex.at(otk::TblPipeSeparator)) {
                    __skip(lex, otk::TblPipeSeparator);
                    __start(org::TableCell);
                    {
                        empty();
                        parseContent(lex);
                    }
                    __end();
                }

                __skip(lex, otk::TblPipeEnd);
                __end();
                break;
            }
            case otk::TblPipeCellBegin: {
                __start(org::TableRow);
                empty();
                empty();

                __skip(lex, otk::TblPipeCellBegin);
                __start(org::TableCell);
                {

                    empty();
                    parseContent(lex);
                }
                __end();

                while (lex.at(otk::TblPipeCellBegin)) {
                    __skip(lex, otk::TblPipeCellBegin);
                    __start(org::TableCell);
                    {
                        empty();
                        parseContent(lex);
                    }
                    __end();
                }

                __end();
                break;
            }
            case otk::TblRowSpec: {
                __start(org::TableRow);
                empty();
                __skip(lex, otk::TblRowSpec);
                __skip(lex, otk::CmdArguments);
                empty();
                __start(org::TableCell);
                {
                    empty();
                    parseContent(lex);
                }
                __end();
                while (lex.at(otk::TblCellSpec)) {
                    __skip(lex, otk::TblCellSpec);
                    __skip(lex, otk::CmdArguments);
                    __start(org::TableCell);
                    {
                        empty();
                        parseContent(lex);
                    }
                    __end();
                }

                __end();
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
    __skip(lex, otk::TblEnd);
    __end_return();
}


OrgId OrgParser::parseParagraph(OrgLexer& lex, bool onToplevel) {
    __perf_trace("parseParagraph");
    __trace();
    expect(lex, otk::ParagraphBegin);
    const auto& paragraphTokens = lex.getInside(
        IntSet<OrgTokenKind>{otk::ParagraphBegin},
        IntSet<OrgTokenKind>{otk::ParagraphEnd});

    if (paragraphTokens.empty()) {
        __start(org::Paragraph);
        __end();
        return back();
    }

    SubLexer<OrgTokenKind, OrgFill> sub = SubLexer<OrgTokenKind, OrgFill>(
        lex.in, paragraphTokens);

    UnorderedMap<OrgTokenKind, bool> lastClosing({
        {otk::BoldInline, true},
        {otk::ItalicInline, true},
        {otk::VerbatimInline, true},
        {otk::MonospaceInline, true},
        {otk::BacktickInline, true},
        {otk::UnderlineInline, true},
        {otk::StrikeInline, true},
    });

    for (const auto& tok : sub.tokens) {
        auto kind = sub.tok(tok).kind;
        if (lastClosing.contains(kind)) {
            if (lastClosing.at(kind)) {
                switch (kind) {
#define MarkupBegin(Kind)                                                 \
    case otk::Kind##Inline:                                               \
        sub.tok(tok).kind = otk::Kind##InlineBegin;                       \
        break;

                    MarkupBegin(Bold);
                    MarkupBegin(Italic);
                    MarkupBegin(Verbatim);
                    MarkupBegin(Monospace);
                    MarkupBegin(Backtick);
                    MarkupBegin(Underline);
                    MarkupBegin(Strike);

#undef MarkupBegin
                    default: {
                    }
                }
            } else {
                switch (kind) {
#define MarkupEnd(Kind)                                                   \
    case otk::Kind##Inline:                                               \
        sub.tok(tok).kind = otk::Kind##InlineEnd;                         \
        break;

                    MarkupEnd(Bold);
                    MarkupEnd(Italic);
                    MarkupEnd(Verbatim);
                    MarkupEnd(Monospace);
                    MarkupEnd(Backtick);
                    MarkupEnd(Underline);
                    MarkupEnd(Strike);

#undef MarkupEnd
                    default: {
                    }
                }
            }
        }
    }


    __start(org::Paragraph);
    auto nodes = parseText(sub);
    __end();
    return back();
}


OrgId OrgParser::parseInlineParagraph(OrgLexer& lex) {
    __perf_trace("parseInlineParagraph");
    __trace();
    return parseParagraph(lex, false);
}


OrgId OrgParser::parseTopParagraph(OrgLexer& lex) {
    __perf_trace("parseTopParagraph");
    __trace();
    return parseParagraph(lex, false);
}


OrgId OrgParser::parseCommandArguments(OrgLexer& lex) {
    __perf_trace("parseCommandArguments");
    __trace();
    __start(org::InlineStmtList);
    while (lex.at(OrgTokSet{otk::CmdValue, otk::CmdKey})) {
        if (lex.at(otk::CmdKey)) {
            __start(org::CmdValue);
            {
                auto ident = token(org::Ident, pop(lex, otk::CmdKey));
                __token(ident);
                space(lex);
                auto raw = token(org::RawText, pop(lex, otk::CmdValue));
                __token(raw);
            }
            __end();
        } else {
            __start(org::CmdValue);
            {
                auto em = empty();
                __token(em);
                space(lex);
                auto raw = token(org::RawText, pop(lex, otk::CmdValue));
                __token(raw);
            }
            __end();
        }
    }

    __end_return();
}


OrgId OrgParser::parseSrcArguments(OrgLexer& lex) {
    __perf_trace("parseSrcArguments");
    __trace();
    __start(org::CmdArguments);
    __start(org::InlineStmtList);

    while (lex.at(otk::CmdFlag)) {
        token(org::CmdFlag, pop(lex, otk::CmdFlag));
    }
    __end();
    parseCommandArguments(lex);
    __end_return();
}


OrgId OrgParser::parseTextWrapCommand(OrgLexer& lex, OrgCommandKind kind) {
    __perf_trace("parseTextWrapCommand");
    __trace();
    switch (kind) {
        case ock::BeginCenter: __start(org::CenterBlock); break;
        case ock::BeginQuote: __start(org::QuoteBlock); break;
        case ock::BeginAdmonition: __start(org::AdmonitionBlock); break;
        default: throw UnhandledToken(lex);
    }

    __skip(lex, otk::CmdPrefix);
    __skip(lex, otk::CmdBegin);
    space(lex);
    __skip(lex, otk::CmdArgumentsBegin);
    if (lex.at(otk::RawText)) {
        lex.next();
    } else if (lex.at(otk::Ident)) {
        lex.next();
    };
    __skip(lex, otk::CmdArgumentsEnd);
    __skip(lex, otk::CmdContentBegin);
    parseParagraph(lex, true);
    __skip(lex, otk::CmdContentEnd);
    __skip(lex, otk::CmdPrefix);
    __skip(lex, otk::CmdEnd);
    __end_return();
}


OrgId OrgParser::parseBlockExport(OrgLexer& lex) {
    __perf_trace("parseExample");
    __trace();
    __start(org::BlockExport);

    __skip(lex, otk::CmdPrefix);
    __skip(lex, otk::CmdBegin);

    // command arguments
    space(lex);
    __skip(lex, otk::CmdArgumentsBegin);
    auto args = token(org::Ident, pop(lex, otk::Ident));
    __token(args);
    space(lex);
    parseSrcArguments(lex);
    __skip(lex, otk::CmdArgumentsEnd);

    // command content
    __skip(lex, otk::CmdContentBegin);
    auto body = token(org::RawText, pop(lex, otk::RawText));
    __token(body);
    __skip(lex, otk::CmdContentEnd);

    __skip(lex, otk::CmdPrefix);
    __skip(lex, otk::CmdEnd);

    __end_return();
}


OrgId OrgParser::parseExample(OrgLexer& lex) {
    __perf_trace("parseExample");
    __trace();
    __start(org::Example);

    __skip(lex, otk::CmdPrefix);
    __skip(lex, otk::CmdBegin);

    { // command arguments
        __skip(lex, otk::CmdArgumentsBegin);
        auto args = token(org::RawText, pop(lex, otk::RawText));
        __token(args);
        __skip(lex, otk::CmdArgumentsEnd);
    }

    { // command content
        __skip(lex, otk::CmdContentBegin);
        auto body = token(org::RawText, pop(lex, otk::RawText));
        __token(body);
        __skip(lex, otk::CmdContentEnd);
    }

    __skip(lex, otk::CmdPrefix);
    __skip(lex, otk::CmdEnd);

    __end_return();
}


OrgId OrgParser::parseSrc(OrgLexer& lex) {
    __perf_trace("parseSrc");
    __trace();
    __start(org::SrcCode);
    __skip(lex, otk::CmdPrefix);
    __skip(lex, otk::CmdBegin);
    // header_args_lang
    {
        skipSpace(lex);
        __skip(lex, otk::CmdArgumentsBegin);

        const auto lang = pop(lex, otk::Word);
        if (lex.val().getText().empty()) {
            empty();
        } else {
            token(org::Ident, lang);
        }

        parseSrcArguments(lex);
        __skip(lex, otk::CmdArgumentsEnd);
    };
    // body
    {

        __start(org::StmtList);
        __skip(lex, otk::CmdContentBegin);
        while (!lex.at(otk::CmdContentEnd)) {
            __start(org::CodeLine);
            while (!lex.at(OrgTokSet{otk::CmdContentEnd, otk::Newline})) {
                switch (lex.kind()) {
                    case otk::CodeText: {
                        token(org::CodeText, pop(lex, otk::CodeText));
                        break;
                    }
                    case otk::ParBegin: {
                        __skip(lex, otk::ParBegin);
                        __skip(lex, otk::Ident);
                        __skip(lex, otk::Colon);
                        __start(org::CodeCallout);
                        token(org::Ident, pop(lex, otk::Ident));
                        __end();
                        __skip(lex, otk::ParEnd);
                        break;
                    }
                    case otk::CmdContentEnd: {
                        break;
                        break;
                    }
                    case otk::DoubleAngleBegin: {
                        __skip(lex, otk::DoubleAngleBegin);
                        __start(org::CodeTangle);
                        parseCSVArguments(lex);
                        __end();
                        __skip(lex, otk::DoubleAngleEnd);
                        break;
                    }
                    default: {
                        assert(false);
                    }
                }
            }
            if (lex.at(otk::Newline)) { lex.next(); }
            __end(); // finish code line
        }

        __skip(lex, otk::CmdContentEnd);
        __end(); // finish statement
    };
    // eval_result
    { empty(); };
    __skip(lex, otk::CmdPrefix);
    __skip(lex, otk::CmdEnd);
    __end_return();
}


OrgId OrgParser::parseListItemBody(OrgLexer& lex) {
    __perf_trace("parseListItemBody");
    __trace();
    __start(org::StmtList);
    while (!lex.at(otk::StmtListEnd)) {
        if (lex.at(Vec<OrgTokenKind>{otk::Indent, otk::ListItemBegin})) {
            lex.next();
            parseNestedList(lex);
            __skip(lex, otk::Dedent);
        } else {
            parseToplevelItem(lex);
        }
    }
    __end_return();
}


OrgId OrgParser::parseListItem(OrgLexer& lex) {
    __perf_trace("parseListItem");
    __trace();
    __start(org::ListItem);
    // prefix, 0
    { token(org::RawText, pop(lex, otk::ListItemBegin)); }
    skipSpace(lex);
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
            __skip(lex, otk::ListDescBegin);
            __start(org::AnnotatedParagraph);
            __start(org::ListTag);
            parseParagraph(lex, false);
            __end();
            __skip(lex, otk::DoubleColon);
            __skip(lex, otk::ListDescEnd);
            __end();
        } else {
            empty();
        }
    }
    // completion, 4
    { empty(); }
    // body, 5
    {
        __skip(lex, otk::StmtListBegin);
        parseListItemBody(lex);
        __skip(lex, otk::StmtListEnd);
    }
    __skip(lex, otk::ListItemEnd);
    __end_return();
}


OrgId OrgParser::parseNestedList(OrgLexer& lex) {
    __perf_trace("parseNestedList");
    __trace();
    ParseCb nextLevel = [this](OrgLexer& lex) {
        __skip(lex, otk::Indent);
        auto result = parseNestedList(lex);
        __skip(lex, otk::Dedent);
        return result;
    };

    __start(org::List);
    while (lex.at(otk::ListItemBegin)) {
        parseListItem(lex);
        if (lex.at(otk::SameIndent)) {
            lex.next();
        } else if (lex.at(otk::Dedent)) {
            __end_return();
        } else if (lex.at(otk::Indent)) {
            nextLevel(lex);
        } else if (lex.at(otk::ListEnd)) {
            __end_return();
        } else {
            assert(false);
        }
    }
    __end();
    return back();
}


OrgId OrgParser::parseList(OrgLexer& lex) {
    __perf_trace("parseList");
    __trace();
    __skip(lex, otk::ListBegin);
    const auto nested = lex.at(otk::Indent);
    if (nested) { __skip(lex, otk::Indent); }
    auto result = parseNestedList(lex);
    if (nested) { __skip(lex, otk::Dedent); }
    __skip(lex, otk::ListEnd);
    return result;
}


OrgId OrgParser::parseSubtreeLogbookClockEntry(OrgLexer& lex) {
    __perf_trace("parseSubtreeLogbookClockEntry");
    __trace();
    __start(org::LogbookClock);
    // CLOCK:
    __skip(lex, otk::ListClock);
    __skip(lex, otk::ParagraphBegin);
    space(lex);
    __skip(lex, otk::BigIdent);
    __skip(lex, otk::Colon);
    space(lex);

    parseTimeRange(lex);

    space(lex);
    __skip(lex, otk::ParagraphEnd);
    newline(lex);
    __end_return();
}


OrgId OrgParser::parseSubtreeLogbookListEntry(OrgLexer& lex) {
    __perf_trace("parseSubtreeLogbookListEntry");
    __trace();
    __start(org::LogbookEntry);
    using V = TokenWithValue;

    __skip(lex, otk::ListItemBegin);
    skipSpace(lex);
    __skip(lex, otk::StmtListBegin);
    __skip(lex, otk::ParagraphBegin);
    if (lex.at(otk::Word) && lex.val().getText() == "State") {
        // - State "WIP" from "TODO" [2023-01-01 Sun 23:32:22]
        __start(org::LogbookStateChange);
        {
            CHECK(lex.val().getText() == "State");
            __skip(lex, otk::Word);
            space(lex);
            __skip(lex, otk::QuoteBegin);
            token(org::BigIdent, pop(lex, otk::BigIdent));
            __skip(lex, otk::QuoteEnd);
            space(lex);
            CHECK(lex.val().getText() == "from");
            __skip(lex, otk::Word);
            space(lex);
            if (lex.at(otk::QuoteBegin)) {
                __skip(lex, otk::QuoteBegin);
                token(org::BigIdent, pop(lex, otk::BigIdent));
                __skip(lex, otk::QuoteEnd);
            } else {
                empty();
            }

            space(lex);
            parseTimeStamp(lex);
        }
        __end();
    } else if (lex.at(otk::Word) && lex.val().getText() == "Refiled") {
        __start(org::LogbookRefile);
        {
            CHECK(lex.val().getText() == "Refiled");
            __skip(lex, otk::Word);
            space(lex);
            CHECK(lex.val().getText() == "on");
            __skip(lex, otk::Word);
            space(lex);
            parseTimeStamp(lex);
            space(lex);
            CHECK(lex.val().getText() == "from");
            __skip(lex, otk::Word);
            space(lex);
            parseLink(lex);
        }
        __end();
    } else if (lex.at(otk::Word) && lex.val().getText() == "Note") {
        __start(org::LogbookNote);
        {
            CHECK(lex.val().getText() == "Note");
            __skip(lex, otk::Word);
            space(lex);
            CHECK(lex.val().getText() == "taken");
            __skip(lex, otk::Word);
            space(lex);
            CHECK(lex.val().getText() == "on");
            __skip(lex, otk::Word);
            space(lex);
            parseTimeStamp(lex);
            space(lex);
        }
        __end();
    } else if (lex.at(otk::Word) && lex.val().getText() == "Priority") {
        __start(org::LogbookPriority);
        {
            CHECK(lex.val().getText() == "Priority");
            __skip(lex, otk::Word);
            space(lex);
            __skip(lex, otk::QuoteBegin);
            auto first = token(org::Word, pop(lex, lex.kind()));
            __token(first);
            __skip(lex, otk::QuoteEnd);
            space(lex);
            auto str    = lex.val().getText();
            auto change = token(
                org::LogbookPriorityChangeAction, pop(lex, otk::Word));
            __token(change);
            space(lex);

            if (str == "Removed") {
                empty();
                CHECK(lex.val().getText() == "on");
                __skip(lex, otk::Word);
            } else if (str == "Changed") {
                CHECK(lex.val().getText() == "From");
                __skip(lex, otk::Word);
                space(lex);
                __skip(lex, otk::QuoteBegin);
                auto second = token(org::Word, pop(lex, lex.kind()));
                __token(second);
                __skip(lex, otk::QuoteEnd);
                space(lex);
                CHECK(lex.val().getText() == "at");
                __skip(lex, otk::Word);
            } else if (str == "Added") {
                empty();
                CHECK(lex.val().getText() == "at");
                __skip(lex, otk::Word);
            } else {
                throw UnhandledToken(
                    lex, "Unexpected priority action " + str);
            }

            space(lex);
            parseTimeStamp(lex);
        }
        __end();
    } else if (lex.at(otk::Word) && lex.val().getText() == "Rescheduled") {
        __start(org::LogbookReschedule);
        {
            CHECK(lex.val().getText() == "Rescheduled");
            __skip(lex, otk::Word);
            space(lex);
            CHECK(lex.val().getText() == "from");
            __skip(lex, otk::Word);
            space(lex);
            __skip(lex, otk::QuoteBegin);
            parseTimeStamp(lex);
            __skip(lex, otk::QuoteEnd);
            space(lex);
            CHECK(lex.val().getText() == "on");
            __skip(lex, otk::Word);
            space(lex);
            parseTimeStamp(lex);
            space(lex);
        }
        __end();
    } else if (lex.at(otk::Word) && lex.val().getText() == "Tag") {
        __start(org::LogbookTagChange);
        {
            CHECK(lex.val().getText() == "Tag");
            __skip(lex, otk::Word);
            space(lex);
            __skip(lex, otk::QuoteBegin);
            parseHashTag(lex);
            __skip(lex, otk::QuoteEnd);
            space(lex);
            auto sub = token(
                org::LogbookTagChangeAction, pop(lex, otk::Word));
            __token(sub);
            space(lex);
            CHECK(lex.val().getText() == "on");
            __skip(lex, otk::Word);
            space(lex);
            parseTimeStamp(lex);
            space(lex);
        }
        __end();
    }

    newline(lex);
    space(lex);
    if (lex.at(otk::DoubleSlash)) {
        __start(org::StmtList);
        __skip(lex, otk::DoubleSlash);
        __skip(lex, otk::Newline);

        Vec<OrgTokenId> firstParagraph;
        while (!lex.at(otk::ParagraphEnd)) {
            firstParagraph.push_back(lex.pop());
        }

        auto sub = SubLexer(lex.in, firstParagraph);

        __skip(lex, otk::ParagraphEnd);

        while (!lex.at(otk::StmtListEnd)) { parseToplevelItem(lex); }

        __skip(lex, otk::StmtListEnd);
        __skip(lex, otk::ListItemEnd);
        __end();

    } else {
        __skip(lex, otk::ParagraphEnd);
        __skip(lex, otk::StmtListEnd);
        __skip(lex, otk::ListItemEnd);
        empty();
    }


    // TODO handle optional logbook entry description or note
    __end_return();
}


OrgId OrgParser::parseSubtreeLogbook(OrgLexer& lex) {
    __perf_trace("parseSubtreeLogbook");
    __trace();
    __start(org::Logbook);
    __skip(lex, otk::ColonLogbook);
    newline(lex);
    __skip(lex, otk::GroupBegin);
    __skip(lex, otk::LogbookBegin);

    skipSpace(lex);
    while (lex.at(otk::ListBegin) || lex.at(otk::ListClock)) {
        switch (lex.tok().kind) {
            case otk::ListBegin: {
                __skip(lex, otk::ListBegin);
                __skip(lex, otk::Indent);
                while (lex.at(otk::ListItemBegin)) {
                    parseSubtreeLogbookListEntry(lex);
                    if (lex.at(otk::SameIndent)) { lex.next(); }
                }
                __skip(lex, otk::Dedent);
                __skip(lex, otk::ListEnd);
                space(lex);
                break;
            }
            case otk::ListClock: {
                parseSubtreeLogbookClockEntry(lex);
                space(lex);
                break;
            }
            default: {
                throw UnhandledToken(lex);
            }
        }
    }

    space(lex);
    __skip(lex, otk::LogbookEnd);
    __skip(lex, otk::ColonEnd);
    __end_return();
}


OrgId OrgParser::parseSubtreeProperties(OrgLexer& lex) {
    __perf_trace("parseSubtreeProperties");
    __trace();
    __skip(lex, otk::ColonProperties);
    __skip(lex, otk::SkipNewline);
    __skip(lex, otk::GroupBegin);
    __skip(lex, otk::SkipSpace);
    __start(org::PropertyList);
    while (lex.at(otk::ColonIdent) || lex.at(otk::Punctuation)) {
        __trace("Parse single subtree property");
        __start(org::Property);
        // Optional exclusion rule description
        if (lex.at(otk::Punctuation)) {
            auto sub = token(org::Punctuation, pop(lex, otk::Punctuation));
            __token(sub);
        } else {
            empty();
        }

        // First ident
        auto name = token(org::RawText, pop(lex, otk::ColonIdent));
        __token(name);

        // Set rule for main property specification
        if (lex.at(otk::Punctuation)) {
            auto sub = token(org::Punctuation, pop(lex, otk::Punctuation));
            __token(sub);
        } else {
            empty();
        }

        // Optional sub-ident for the property name, like
        // `:header-args:cpp:`
        if (lex.at(otk::ColonIdent)) {
            auto sub = token(org::Ident, pop(lex, otk::ColonIdent));
            __token(sub);
        } else {
            empty();
        }

        // Set rule for sub-property specification
        if (lex.at(otk::Punctuation)) {
            auto sub = token(org::Punctuation, pop(lex, otk::Punctuation));
            __token(sub);
        } else {
            empty();
        }

        __skip(lex, otk::SkipSpace);

        std::string strName = normalize(group->val(name).getText());

        if (strName == "created") {
            parseTimeStamp(lex);
        } else {
            token(org::RawText, pop(lex, otk::RawProperty));
        }


        __skip(lex, otk::SkipNewline);
        __skip(lex, otk::SkipSpace);
        __end();
    }
    __skip(lex, otk::ColonEnd);
    __skip(lex, otk::GroupEnd);
    __end_return();
}


OrgId OrgParser::parseSubtreeDrawer(OrgLexer& lex) {
    __perf_trace("parseSubtreeDrawer");
    __trace();
    __skip(lex, otk::GroupBegin);
    __skip(lex, otk::SkipSpace);
    __start(org::Drawer);

    while (lex.at(OrgTokSet{
        otk::ColonProperties, otk::ColonLogbook, otk::ColonDescription})) {
        switch (lex.tok().kind) {
            case otk::ColonProperties: parseSubtreeProperties(lex); break;
            case otk::ColonLogbook: parseSubtreeLogbook(lex); break;
            case otk::ColonDescription: {
                __skip(lex, otk::ColonDescription);
                __start(org::SubtreeDescription);
                newline(lex);
                {
                    parseParagraph(lex, false);
                    __skip(lex, otk::ColonEnd);
                }
                __end();
                break;
            }
            default: {
            }
        }

        newline(lex);
        space(lex);
    }

    __skip(lex, otk::GroupEnd);
    __end_return();
}

void tokenFormat(ColStream& os, OrgToken const& t) { os << t->getText(); }

OrgId OrgParser::parseSubtreeCompletion(OrgLexer& lex) {
    __perf_trace("parseSubtreeCompletion");
    __trace();
    if (lex.at(otk::SkipNewline) || lex.at(otk::SubtreeTagSeparator)
        || lex.at(otk::SubtreeEnd)) {
        return empty();

    } else {
        __start(org::Completion);
        LOG(INFO) << "Parse subtree completion ["
                  << lex.printToString(tokenFormat) << "]";
        __end_return();
    }
}


OrgId OrgParser::parseSubtreeTodo(OrgLexer& lex) {
    __perf_trace("parseSubtreeTodo");
    __trace();
    skipSpace(lex);
    if (lex.at(otk::SubtreeTodoState)) {
        auto tmp = token(org::BigIdent, pop(lex, otk::SubtreeTodoState));
        __token(tmp);
        return tmp;
    } else {
        return empty();
    }
}


OrgId OrgParser::parseSubtreeUrgency(OrgLexer& lex) {
    __perf_trace("parseSubtreeUrgency");
    __trace();
    skipSpace(lex);
    if (lex.at(otk::SubtreeUrgency)) {
        return token(org::SubtreeUrgency, pop(lex, otk::SubtreeUrgency));
    } else {
        return empty();
    }
}


OrgId OrgParser::parseSubtreeTitle(OrgLexer& lex) {
    __perf_trace("parseSubtreeTitle");
    __trace();
    skipSpace(lex);
    return parseParagraph(lex, false);
}


OrgId OrgParser::parseSubtreeTags(OrgLexer& lex) {
    __perf_trace("parseSubtreeTags");
    __trace();
    if (lex.at(otk::SubtreeTagSeparator)) {
        __start(org::InlineStmtList);
        while (lex.at(otk::SubtreeTagSeparator)
               && lex.at(otk::HashTag, +1)) {
            __skip(lex, otk::SubtreeTagSeparator);
            parseHashTag(lex);
        }
        __skip(lex, otk::SubtreeTagSeparator);
        __end_return();
    } else {
        return empty();
    }
}


OrgId OrgParser::parseSubtreeTimes(OrgLexer& lex) {
    __perf_trace("parseSubtreeTimes");
    __trace();
    __start(org::StmtList);
    if (lex.ahead(
            OrgTokSet{otk::SkipSpace, otk::GroupBegin},
            OrgTokSet{otk::SubtreeTime})) {
        __skip(lex, otk::GroupBegin);
        __skip(lex, otk::SkipSpace);

        while (lex.at(otk::SubtreeTime)) {
            __start(org::TimeAssoc);
            if (lex.at(otk::SubtreeTime)) {
                token(org::BigIdent, pop(lex, otk::SubtreeTime));
            } else {
                empty();
            }
            space(lex);
            parseTimeStamp(lex);
            space(lex);
            __end();
        }

        newline(lex);
        __skip(lex, otk::GroupEnd);
    } else {
        __print("No subtree time");
    }

    __end_return();
}


OrgId OrgParser::parseSubtree(OrgLexer& lex) {
    __perf_trace("parseSubtree");
    __trace();
    __start(org::Subtree);
    // prefix

    token(org::RawText, pop(lex, otk::SubtreeStars)); // 0
    parseSubtreeTodo(lex);                            // 1
    parseSubtreeUrgency(lex);                         // 2
    space(lex);                                       //
    parseSubtreeTitle(lex);                           // 3
    parseSubtreeCompletion(lex);                      // 4
    parseSubtreeTags(lex);                            // 5

    if (!lex.at(otk::SubtreeEnd)) { // 6
        __skip(lex, otk::SkipNewline);
        parseSubtreeTimes(lex);
        newline(lex);
    } else {
        empty();
    }

    if (!lex.at(otk::SubtreeEnd)) { // 7
        parseSubtreeDrawer(lex);
        newline(lex);
    } else {
        empty();
    }

    start(org::StmtList); // 8
    end();

    __skip(lex, otk::SubtreeEnd);
    __end_return();
}


OrgId OrgParser::parseOrgFile(OrgLexer& lex) {
    __perf_trace("parseOrgFile");
    __trace();
    __start(org::File);
    if (lex.at(otk::QuoteBegin)) {
        lex.next();
        token(org::RawText, pop(lex, otk::RawText));
        __skip(lex, otk::QuoteEnd);
    } else {
        token(org::RawText, pop(lex, otk::RawText));
    }
    __end_return();
}


OrgId OrgParser::parseLineCommand(OrgLexer& lex) {
    __perf_trace("parseLineCommand");
    __trace();
    LOG(FATAL) << "TODO implement line command parse";
#if false // TODO
    const auto kind = classifyCommand(lex.strVal(+1));
    switch (kind) {
        case ock::Include: {
            skipLineCommand(lex);
            __skip(lex, otk::CmdArgumentsBegin);
            __start(org::CommandInclude);
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
            __skip(lex, otk::CmdArgumentsEnd);
            break;
        }

        case ock::AttrHtml: {
            skipLineCommand(lex);
            __skip(lex, otk::CmdArgumentsBegin);
            __start(org::CommandAttrHtml);
            parseSrcArguments(lex);
            __skip(lex, otk::CmdArgumentsEnd);
            break;
        }

        case ock::Title: {
            skipLineCommand(lex);
            __start(org::CommandTitle);
            parseParagraph(lex, false);
            break;
        }

        case ock::Caption: {
            skipLineCommand(lex);
            __start(org::CommandCaption);
            __start(org::CommandArguments);
            parseParagraph(lex, false);
            __end();
            break;
        }

        case ock::Creator:
        case ock::Options:
        case ock::Columns:
        case ock::Author:
        case ock::LatexHeader:
        case ock::Language: {
            OrgNodeKind newk;
            switch (kind) {
                case ock::Creator: newk = org::CommandCreator; break;
                case ock::Language: newk = org::CommandLanguage; break;
                case ock::Author: newk = org::CommandAuthor; break;
                case ock::Options: newk = org::CommandOptions; break;
                case ock::LatexHeader: newk = org::LatexHeader; break;
                case ock::Columns: newk = org::Columns; break;
                default: {
                }
            }

            __start(newk);
            {
                skipLineCommand(lex);
                __skip(lex, otk::CmdArgumentsBegin);
                while (lex.at(otk::RawText)) {
                    token(org::RawText, pop(lex, otk::RawText));
                    if (lex.at(otk::SkipSpace)) {
                        skipSpace(lex);
                    }
                }
                __skip(lex, otk::CmdArgumentsEnd);
            }

            break;
        }

        case ock::Filetags: {
            skipLineCommand(lex);
            __start(org::Filetags);
            while (lex.at(otk::SubtreeTagSeparator)
                   && lex.at(otk::HashTag, +1)) {
                parseHashTag(lex);
            }
            __skip(lex, otk::SubtreeTagSeparator);
            break;
        }

        case ock::HtmlHead: {
            skipLineCommand(lex);
            __skip(lex, otk::CmdArgumentsBegin);
            __start(org::HtmlHead);
            token(org::RawText, pop(lex, otk::RawText));
            __skip(lex, otk::CmdArgumentsEnd);
            break;
        }

        case ock::LatexClassOptions: {
            skipLineCommand(lex);
            __skip(lex, otk::CmdArgumentsBegin);
            __start(org::LatexClassOptions);
            token(org::RawText, pop(lex, otk::RawText));
            __skip(lex, otk::CmdArgumentsEnd);
            break;
        }

        case ock::LatexClass:
        case ock::LatexCompiler: {
            OrgNodeKind newk = org::Empty;
            switch (kind) {
                case ock::LatexCompiler: newk = org::LatexCompiler; break;
                case ock::LatexClass: newk = org::LatexClass; break;
                default: {
                }
            }
            skipLineCommand(lex);
            __skip(lex, otk::CmdArgumentsBegin);
            __start(newk);
            token(org::Ident, pop(lex, otk::Ident));
            __skip(lex, otk::CmdArgumentsEnd);
            break;
        }


        case ock::Property: {
            skipLineCommand(lex);
            __start(org::Property);
            token(org::RawText, pop(lex, otk::Ident));
            empty();
            token(org::RawText, pop(lex, otk::RawProperty));
            break;
        }

        case ock::TableFormula: {
            skipLineCommand(lex);
            __start(org::CommandTblfm);
            __skip(lex, otk::CmdArgumentsBegin);
            token(org::RawText, pop(lex, otk::RawText));
            __skip(lex, otk::CmdArgumentsEnd);
            break;
        }

        default: {
            throw wrapError(
                UnhandledToken(lex, to_string(kind)), lex);
        }
    }

    // Placeholder statement list that might be extended in a latter pass
    __start(org::StmtList);
    __end();
    // End main tree that was started in the case statement
    __end();
#endif

    return back();
}


OrgId OrgParser::parseToplevelItem(OrgLexer& lex) {
    __perf_trace("parseToplevelItem");
    __trace();
    switch (lex.kind()) {
        case otk::ParagraphBegin: return parseParagraph(lex, true);
        case otk::TblBegin: return parseTable(lex);
        case otk::SubtreeStars: return parseSubtree(lex);
        case otk::ListBegin: return parseList(lex);
        case otk::SkipAny:
            return token(org::SkipAny, pop(lex, otk::SkipAny));
        case otk::SkipSpace:
            return token(org::SkipSpace, pop(lex, otk::SkipSpace));
        case otk::SkipNewline:
            return token(org::SkipNewline, pop(lex, otk::SkipNewline));
        case otk::Newline:
            return token(org::Newline, pop(lex, otk::Newline));
        case otk::TextSeparator:
            return token(org::TextSeparator, pop(lex, otk::TextSeparator));

        case otk::CmdPrefix: {
            auto const& kind = lex.tok(1)->getText();
            if (kind == "begin_src") {
                return parseSrc(lex);
            } else if (kind == "begin_example") {
                return parseExample(lex);
            } else if (kind == "begin_export") {
                parseBlockExport(lex);
            } else if (kind == "begin_quote") {
                return parseTextWrapCommand(lex, ock::BeginQuote);
            } else if (kind == "begin_center") {
                return parseTextWrapCommand(lex, ock::BeginCenter);
            } else if (kind == "begin_admonition") {
                return parseTextWrapCommand(lex, ock::BeginAdmonition);
            } else {
                return parseLineCommand(lex);
            }
        }
        default: {
            throw UnhandledToken(lex);
        }
    }
}


OrgId OrgParser::parseTop(OrgLexer& lex) {
    __perf_trace("parseTop");
    __trace();
    __start(org::StmtList);
    while (lex.hasNext()) {
        if (lex.at(otk::Comment)) {
            lex.next();
        } else {
            parseToplevelItem(lex);
        };
    }
    __end_return();
}


OrgId OrgParser::parseFull(OrgLexer& lex) {
    __perf_trace("parseFull");
    __trace();
    auto id = parseTop(lex);
    extendSubtreeTrails(OrgId(0));
    extendAttachedTrails(OrgId(0));
    return id;
}


// namespace

void OrgParser::skipLineCommand(OrgLexer& lex) {
    skip(lex, otk::CmdPrefix);
    skip(lex, otk::CmdLine);
    skip(lex, otk::Colon);
    while (lex.at(otk::SkipSpace)) { lex.next(); }
}

bool OrgParser::at(CR<OrgLexer> lex, CR<OrgExpectable> item) {
    if (item.index() == 0 && lex.at(std::get<0>(item))) {
        return true;
    } else if (item.index() == 1 && lex.at(std::get<1>(item))) {
        return true;
    } else if (
        item.index() == 2 //
        && lex.at(std::get<2>(item).kind)
        && lex.tok()->getText() == std::get<2>(item).value) {
        return true;
    } else {
        return false;
    }
}

void OrgParser::expect(CR<OrgLexer> lex, CR<OrgExpectable> item) {
    if (!(at(lex, item))) { throw UnexpectedToken(lex, {item}); }
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
                __print(
                    "Found subtree on the lower level " + id.format(),
                    nullptr);
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
                    __print(
                        "Found subtree on the same level or above "
                            + id.format(),
                        nullptr);
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
            CHECK(g.at(stmt + 1).kind == org::SkipNewline);
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
