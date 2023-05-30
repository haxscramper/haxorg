#include "OrgParser.hpp"

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <hstd/stdlib/Debug.hpp>

#ifndef TRACE_STATE
#    define TRACE_STATE true
#endif


#pragma clang diagnostic push
// #pragma clang diagnostic error "-Wswitch-enum"
// #pragma clang diagnostic error "-Wswitch-enum"

#if TRACE_STATE

#    define __INIT_REPORT(__subname, __lex)                               \
        (Report{                                                          \
            .line     = __LINE__,                                         \
            .location = __CURRENT_FILE_PATH__,                            \
            .lex      = &__lex,                                           \
            .subname  = __subname,                                        \
        })

#    define __trace2(__subname, __lex)                                    \
        {                                                                 \
            Report rep = __INIT_REPORT(__subname, __lex);                 \
            rep.kind   = ReportKind::EnterParse;                          \
            rep.name   = __func__;                                        \
            report(rep);                                                  \
        }                                                                 \
                                                                          \
        finally CONCAT(close, __COUNTER__) = finally::init<Str>(          \
            ([&](CR<Str> name) {                                          \
                Report rep = __INIT_REPORT(__subname, __lex);             \
                rep.kind   = ReportKind::LeaveParse;                      \
                rep.name   = name;                                        \
                report(rep);                                              \
            }),                                                           \
            Str(__func__));


#    define __trace1(__subname) __trace2(__subname, lex)
#    define __trace0() __trace2(std::nullopt, lex)

#    define __trace(...)                                                  \
        BOOST_PP_CAT(                                                     \
            BOOST_PP_OVERLOAD(__trace, __VA_ARGS__)(__VA_ARGS__),         \
            BOOST_PP_EMPTY())


#    define __print2(__text, __lex)                                       \
        report(Report{                                                    \
            .line     = __LINE__,                                         \
            .location = __CURRENT_FILE_PATH__,                            \
            .kind     = ReportKind::Print,                                \
            .lex      = __lex,                                            \
            .subname  = __text});

#    define __print1(__text) __print2(__text, &lex)

#    define __print(...)                                                  \
        BOOST_PP_CAT(                                                     \
            BOOST_PP_OVERLOAD(__print, __VA_ARGS__)(__VA_ARGS__),         \
            BOOST_PP_EMPTY())


#    define __end2(__subname, __lex)                                      \
        OrgId CONCAT(tmpNode, __LINE__) = end();                          \
        {                                                                 \
            Report rep = __INIT_REPORT(__subname, __lex);                 \
            rep.kind   = ReportKind::EndNode;                             \
            rep.node   = CONCAT(tmpNode, __LINE__);                       \
            report(rep);                                                  \
        }


#    define __end1(__subname) __end2(__subname, lex)
#    define __end0() __end2(std::nullopt, lex);

#    define __end(...)                                                    \
        BOOST_PP_CAT(                                                     \
            BOOST_PP_OVERLOAD(__end, __VA_ARGS__)(__VA_ARGS__),           \
            BOOST_PP_EMPTY())

#    define __end_return(...)                                             \
        __end(__VA_ARGS__);                                               \
        return back();

#    define __start3(__node, __subname, __lex)                            \
        {                                                                 \
            OrgId  CONCAT(tmpNode, __LINE__) = start(__node);             \
            Report rep = __INIT_REPORT(__subname, __lex);                 \
            rep.kind   = ReportKind::StartNode;                           \
            rep.node   = CONCAT(tmpNode, __LINE__);                       \
            report(rep);                                                  \
        }


#    define __start2(__node, __subname) __start3(__node, __subname, lex)
#    define __start1(__node) __start3(__node, std::nullopt, lex);

#    define __start(...)                                                  \
        BOOST_PP_CAT(                                                     \
            BOOST_PP_OVERLOAD(__start, __VA_ARGS__)(__VA_ARGS__),         \
            BOOST_PP_EMPTY())


#    define __token3(__node, __subname, __lex)                            \
        {                                                                 \
            Report rep = __INIT_REPORT(__subname, __lex);                 \
            rep.kind   = ReportKind::AddToken;                            \
            rep.node   = __node;                                          \
            report(rep);                                                  \
        }

#    define __token2(__node, __subname) __token3(__node, __subname, lex)
#    define __token1(__node) __token3(__node, std::nullopt, lex);

#    define __token(...)                                                  \
        BOOST_PP_CAT(                                                     \
            BOOST_PP_OVERLOAD(__token, __VA_ARGS__)(__VA_ARGS__),         \
            BOOST_PP_EMPTY())

#else
#    define __token(...)
#    define __start(__node, ...) start(__node);
#    define __end(...) end();
#    define __print(...)
#    define __trace(...)
#endif


template <>
OrgId OrgParserImpl<TRACE_STATE>::parseCSVArguments(OrgLexer& lex) {
    __perf_trace("parseCSVArguments");
    __trace();
    __start(org::Ident);
    skip(lex, otk::Ident);

    if (lex.at(otk::ParOpen)) {
        skip(lex, otk::ParOpen);
        while (lex.at(otk::RawText)) {
            token(org::RawText, pop(lex, otk::RawText));
            if (lex.at(otk::Comma)) {
                lex.next();
            }
        }
        skip(lex, otk::ParClose);
    }
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseMacro(OrgLexer& lex) {
    __perf_trace("parseMacro");
    __trace();
    __start(org::Macro);
    skip(lex, otk::MacroOpen);
    parseCSVArguments(lex);
    skip(lex, otk::MacroClose);
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseRawUrl(OrgLexer& lex) {
    __perf_trace("parseRawUrl");
    __trace();
    auto tok = token(org::RawLink, pop(lex, otk::RawUrl));
    __token(tok);
    return tok;
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parsePlaceholder(OrgLexer& lex) {
    __perf_trace("parsePlaceholder");
    __trace();
    skip(lex, otk::GroupStart);
    skip(lex, otk::AngleOpen);
    auto tok = token(org::Placeholder, pop(lex, otk::RawText));
    __token(tok);
    skip(lex, otk::AngleClose);
    skip(lex, otk::GroupEnd);

    return tok;
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseLatex(OrgLexer& lex) {
    __perf_trace("parseLatex");
    __trace();
    skip(lex, otk::GroupStart);
    skip(lex, otk::LatexParOpen);
    auto tok = token(org::InlineMath, pop(lex, otk::LatexInlineRaw));
    __token(tok);
    skip(lex, otk::LatexParClose);
    skip(lex, otk::GroupEnd);
    return tok;
}

template <>
void OrgParserImpl<TRACE_STATE>::textFold(OrgLexer& lex) {
    __perf_trace("textFold");
    __trace();
#define CASE_MARKUP(Kind)                                                 \
    case otk::Kind##Open: {                                               \
        __start(org::Kind);                                               \
        lex.next();                                                       \
        textFold(lex);                                                    \
        break;                                                            \
    }                                                                     \
                                                                          \
    case otk::Kind##Close: {                                              \
        if (pending().kind == org::Kind) {                                \
            __end();                                                      \
            lex.next();                                                   \
        } else {                                                          \
            fail(pop(lex, otk::Kind##Close));                             \
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
    case otk::Kind##InlineOpen: {                                         \
        __start(org::Kind);                                               \
        lex.next();                                                       \
        textFold(lex);                                                    \
        break;                                                            \
    }                                                                     \
                                                                          \
    case otk::Kind##InlineClose: {                                        \
        if (pending().kind == org::Kind) {                                \
            __end();                                                      \
            lex.next();                                                   \
        } else {                                                          \
            fail(pop(lex, otk::Kind##InlineClose));                       \
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
            CASE_MARKUP(Quote);
            CASE_MARKUP(Par);
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

            case otk::SrcOpen: parseSrcInline(lex); break;
            case otk::ActiveTimeBegin:
            case otk::InactiveTimeBegin: parseTimeRange(lex); break;
            case otk::HashTag: parseHashTag(lex); break;
            case otk::LinkOpen: parseLink(lex); break;
            case otk::MacroOpen: parseMacro(lex); break;
            case otk::RawUrl: parseRawUrl(lex); break;
            case otk::FootnoteStart: parseFootnote(lex); break;

            case otk::DollarOpen:
            case otk::LatexParOpen:
            case otk::DoubleDollarOpen:
            case otk::LatexBraceOpen: parseInlineMath(lex); break;

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

            case otk::DoubleAngleOpen: {
                skip(lex, otk::DoubleAngleOpen);
                auto tmp = token(org::Target, pop(lex, otk::RawText));
                __token(tmp);
                skip(lex, otk::DoubleAngleClose);
                break;
            }

            case otk::TripleAngleOpen: {
                skip(lex, otk::TripleAngleOpen);
                auto target = token(
                    org::RadioTarget, pop(lex, otk::RawText));
                __token(target);
                skip(lex, otk::TripleAngleClose);
                break;
            }

            case otk::BoldInline:
            case otk::ItalicInline:
            case otk::VerbatimInline:
            case otk::MonospaceInline:
            case otk::BacktickInline:
            case otk::UnderlineInline:
            case otk::StrikeInline: {
                throw wrapError(
                    Err::UnhandledToken(
                        lex,
                        "Non-directional inline markup token incountered "
                        "during text parsing"),
                    lex);
            }

            case otk::GroupStart: {
                switch (lex.kind(+1)) {
                    case otk::LinkOpen: parseLink(lex); break;
                    case otk::FootnoteStart: parseFootnote(lex); break;
                    case otk::AngleOpen: parsePlaceholder(lex); break;
                    case otk::LatexParOpen: parseLatex(lex); break;
                    default:
                        throw wrapError(Err::UnhandledToken(lex), lex);
                }
                break;
            }

            default: {
                throw wrapError(Err::UnhandledToken(lex), lex);
            }
        }
    }

#undef CASE_MARKUP
#undef CASE_SINGLE
#undef CASE_INLINE
}

template <>
Slice<OrgId> OrgParserImpl<TRACE_STATE>::parseText(OrgLexer& lex) {
    __perf_trace("parseText");
    __trace();
    OrgId   first     = back();
    QString forMsg    = getLocMsg(lex);
    int     treeStart = treeDepth();
    textFold(lex);
    int treeEnd = treeDepth();
    Q_ASSERT_X(
        treeStart <= treeEnd,
        "parseText",
        ("Text fold created unbalanced tree - starting with depth $# "
         "ended up on depth $# on position $# (starting from $#)"
         % to_string_vec(treeStart, treeEnd, getLocMsg(lex), forMsg)));

    while (treeStart < treeDepth()) {
        __print("Warn, force closing content on " + getLocMsg(lex));
        __end();
    }

    OrgId last = back();
    return slice(first, last);
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseLink(OrgLexer& lex) {
    __perf_trace("parseLink");
    __trace();
    __start(org::Link);
    skip(lex, otk::GroupStart);
    skip(lex, otk::LinkOpen);
    skip(lex, otk::LinkTargetOpen);
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
    skip(lex, otk::LinkTargetClose);
    if (lex.at(otk::LinkDescriptionOpen)) {
        auto sub = SubLexer(
            lex.in,
            lex.getInside(
                {otk::LinkDescriptionOpen}, {otk::LinkDescriptionClose}));
        __start(org::Paragraph);
        parseText(sub);
        __end();

    } else {
        empty();
    }

    skip(lex, otk::LinkClose);
    skip(lex, otk::GroupEnd);
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseInlineMath(OrgLexer& lex) {
    __perf_trace("parseInlineMath");
    __trace();
    const auto startKind = lex.tok().kind;
    const auto regular   = OrgTokSet{otk::DollarOpen, otk::LatexParOpen};
    const auto display   = OrgTokSet{
        otk::DoubleDollarOpen, otk::LatexBraceOpen};

    skip(lex, regular + display);
    __start(
        regular.contains(startKind) ? org::InlineMath : org::DisplayMath);

    OrgTokenKind close;
    switch (startKind) {
        case otk::DollarOpen: {
            skip(lex, otk::DollarClose);
            break;
        }
        case otk::DoubleDollarOpen: {
            skip(lex, otk::DoubleDollarClose);
            break;
        }
        case otk::LatexParOpen: {
            skip(lex, otk::LatexParClose);
            break;
        }
        case otk::LatexBraceOpen: {
            skip(lex, otk::LatexBraceClose);
            break;
        }
        default: {
            assert(false);
        }
    }

    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseSymbol(OrgLexer& lex) {
    __perf_trace("parseSymbol");
    __trace();
    skip(lex, otk::SymbolStart);
    __start(org::Symbol);
    token(org::Ident, pop(lex, otk::Ident));

    if (lex.at(otk::MetaBraceOpen)) {
        assert(false);
    } else {
        empty();
    }

    while (lex.at(otk::MetaArgsOpen)) {
        skip(lex, otk::MetaArgsOpen);
        skip(lex, otk::MetaArgsBody);
        skip(lex, otk::MetaArgsClose);
    }

    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseHashTag(OrgLexer& lex) {
    __perf_trace("parseHashTag");
    __trace();
    __start(org::HashTag);
    space(lex);
    token(org::RawText, pop(lex, otk::HashTag));

    if (lex.at(otk::HashTagSub)) {
        skip(lex, otk::HashTagSub);
        if (lex.at(otk::HashTag)) {
            parseHashTag(lex);

        } else {
            skip(lex, otk::HashTagOpen);
            while (!lex.finished() && !lex.at(otk::HashTagClose)) {
                parseHashTag(lex);
                if (lex.at(otk::Comma)) {
                    lex.next();
                }
            }
            skip(lex, otk::HashTagClose);
        }
    }
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseTimeStamp(OrgLexer& lex) {
    __perf_trace("parseTimeStamp");
    __trace();
    expect(lex, OrgTokSet{otk::InactiveTimeBegin, otk::ActiveTimeBegin});
    bool active = lex.at(otk::ActiveTimeBegin);
    skip(lex, active ? otk::ActiveTimeBegin : otk::InactiveTimeBegin);
    if (!lex.at(otk::DynamicTimeContent)) {
        if (active) {
            __start(org::StaticActiveTime);
        } else {
            __start(org::StaticInactiveTime);
        }

        // Year part of the timestamp is not optional
        auto year = token(org::RawText, pop(lex, otk::StaticTimeDatePart));
        __token(year);
        skipSpace(lex);

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

    skip(lex, active ? otk::ActiveTimeEnd : otk::InactiveTimeEnd);
    return back();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseTimeRange(OrgLexer& lex) {
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
        skip(lex, otk::TimeDash);
        parseTimeStamp(lex);
        skipSpace(lex);
        if (lex.at(otk::TimeArrow)) {
            skip(lex, otk::TimeArrow);
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
    //     skip(lex, otk::TimeDash);
    //     token(org::Time, pop(lex, times));

    //     if (lex.ahead(otk::SkipSpace, otk::TimeArrow)) {
    //         space(lex);
    //         skip(lex, otk::TimeArrow);
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

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseFootnote(OrgLexer& lex) {
    __perf_trace("parseFootnote");
    __trace();
    skip(lex, otk::GroupStart);
    // TODO replace 'footnote start' + '::' with a 'inline footnote start'
    // / 'footnote start nodes'
    skip(lex, otk::FootnoteStart);
    if (lex.at(otk::Colon)) {
        __start(org::Footnote);
        skip(lex, otk::Colon);
        parseIdent(lex);
    } else {
        __start(org::InlineFootnote);
        skip(lex, otk::DoubleColon);
        parseInlineParagraph(lex);
    }

    skip(lex, otk::FootnoteEnd);
    skip(lex, otk::GroupEnd);

    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseIdent(OrgLexer& lex) {
    __perf_trace("parseIdent");
    __trace();
    auto tok = token(org::Ident, pop(lex, otk::Ident));
    __token(tok);
    return tok;
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseSrcInline(OrgLexer& lex) {
    __perf_trace("parseSrcInline");
    __trace();
    __start(org::SrcInlineCode);
    skip(lex, otk::SrcOpen);
    {
        token(org::Ident, pop(lex, otk::SrcName));
        __start(org::CodeLine);
        token(org::CodeText, pop(lex, otk::SrcBody));
        __end();
    }
    skip(lex, otk::SrcClose);
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseTable(OrgLexer& lex) {
    __perf_trace("parseTable");
    __trace();
    __start(org::Table);
    skip(lex, otk::TableBegin);
    skip(lex, otk::CmdArguments);
    empty();

    ParseCb parseContent = [this](OrgLexer& lex) {
        auto sub = SubLexer(
            lex.in, lex.getInside({otk::ContentStart}, {otk::ContentEnd}));

        return parseTop(sub);
    };

    while (!lex.at(otk::TableEnd)) {
        switch (lex.kind()) {
            case otk::PipeOpen: {
                __start(org::TableRow);
                empty();
                empty();

                skip(lex, otk::PipeOpen);
                __start(org::TableCell);
                {
                    empty();
                    parseContent(lex);
                }
                __end();

                while (lex.at(otk::PipeSeparator)) {
                    skip(lex, otk::PipeSeparator);
                    __start(org::TableCell);
                    {
                        empty();
                        parseContent(lex);
                    }
                    __end();
                }

                skip(lex, otk::PipeClose);
                __end();
                break;
            }
            case otk::PipeCellOpen: {
                __start(org::TableRow);
                empty();
                empty();

                skip(lex, otk::PipeCellOpen);
                __start(org::TableCell);
                {

                    empty();
                    parseContent(lex);
                }
                __end();

                while (lex.at(otk::PipeCellOpen)) {
                    skip(lex, otk::PipeCellOpen);
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
            case otk::RowSpec: {
                __start(org::TableRow);
                empty();
                skip(lex, otk::RowSpec);
                skip(lex, otk::CmdArguments);
                empty();
                __start(org::TableCell);
                {
                    empty();
                    parseContent(lex);
                }
                __end();
                while (lex.at(otk::CellSpec)) {
                    skip(lex, otk::CellSpec);
                    skip(lex, otk::CmdArguments);
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
            case otk::TableEnd: {
                break;
            }
            default: {
                assert(false);
            }
        };
    };
    skip(lex, otk::TableEnd);
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseParagraph(
    OrgLexer& lex,
    bool      onToplevel) {
    __perf_trace("parseParagraph");
    __trace();
    expect(lex, otk::ParagraphStart);
    const auto& paragraphTokens = lex.getInside(
        IntSet<OrgTokenKind>{otk::ParagraphStart},
        IntSet<OrgTokenKind>{otk::ParagraphEnd});

    SubLexer<OrgTokenKind> sub = SubLexer<OrgTokenKind>(
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
#define MarkupOpen(Kind)                                                  \
    case otk::Kind##Inline:                                               \
        sub.tok(tok).kind = otk::Kind##InlineOpen;                        \
        break;

                    MarkupOpen(Bold);
                    MarkupOpen(Italic);
                    MarkupOpen(Verbatim);
                    MarkupOpen(Monospace);
                    MarkupOpen(Backtick);
                    MarkupOpen(Underline);
                    MarkupOpen(Strike);

#undef MarkupOpen
                }
            } else {
                switch (kind) {
#define MarkupClose(Kind)                                                 \
    case otk::Kind##Inline:                                               \
        sub.tok(tok).kind = otk::Kind##InlineClose;                       \
        break;

                    MarkupClose(Bold);
                    MarkupClose(Italic);
                    MarkupClose(Verbatim);
                    MarkupClose(Monospace);
                    MarkupClose(Backtick);
                    MarkupClose(Underline);
                    MarkupClose(Strike);

#undef MarkupClose
                }
            }
        }
    }


    __start(org::Paragraph);
    auto nodes = parseText(sub);
    __end();
    return back();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseInlineParagraph(OrgLexer& lex) {
    __perf_trace("parseInlineParagraph");
    __trace();
    return parseParagraph(lex, false);
}


template <>
OrgId OrgParserImpl<TRACE_STATE>::parseTopParagraph(OrgLexer& lex) {
    __perf_trace("parseTopParagraph");
    __trace();
    return parseParagraph(lex, false);
}


template <>
OrgId OrgParserImpl<TRACE_STATE>::parseCommandArguments(OrgLexer& lex) {
    __perf_trace("parseCommandArguments");
    __trace();
    __start(org::InlineStmtList);
    while (lex.at(OrgTokSet{otk::CommandValue, otk::CommandKey})) {
        if (lex.at(otk::CommandKey)) {
            __start(org::CmdValue);
            {
                auto ident = token(org::Ident, pop(lex, otk::CommandKey));
                __token(ident);
                auto raw = token(
                    org::RawText, pop(lex, otk::CommandValue));
                __token(raw);
            }
            __end();
        } else {
            __start(org::CmdValue);
            {
                auto em = empty();
                __token(em);
                auto raw = token(
                    org::RawText, pop(lex, otk::CommandValue));
                __token(raw);
            }
            __end();
        }
    }

    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseSrcArguments(OrgLexer& lex) {
    __perf_trace("parseSrcArguments");
    __trace();
    __start(org::CmdArguments);
    __start(org::InlineStmtList);

    while (lex.at(otk::CommandFlag)) {
        token(org::CmdFlag, pop(lex, otk::CommandFlag));
    }
    __end();
    parseCommandArguments(lex);
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseTextWrapCommand(
    OrgLexer&      lex,
    OrgCommandKind kind) {
    __perf_trace("parseTextWrapCommand");
    __trace();
    switch (kind) {
        case ock::BeginCenter: __start(org::CenterBlock); break;
        case ock::BeginQuote: __start(org::QuoteBlock); break;
        case ock::BeginAdmonition: __start(org::AdmonitionBlock); break;
        default: wrapError(Err::UnhandledToken(lex), lex);
    }

    skip(lex, otk::CommandPrefix);
    skip(lex, otk::CommandBegin);
    space(lex);
    skip(lex, otk::CommandArgumentsBegin);
    if (lex.at(otk::RawText)) {
        lex.next();
    } else if (lex.at(otk::Ident)) {
        lex.next();
    };
    skip(lex, otk::CommandArgumentsEnd);
    skip(lex, otk::CommandContentStart);
    parseParagraph(lex, true);
    skip(lex, otk::CommandContentEnd);
    skip(lex, otk::CommandPrefix);
    skip(lex, otk::CommandEnd);
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseExample(OrgLexer& lex) {
    __perf_trace("parseExample");
    __trace();
    __start(org::Example);

    skip(lex, otk::CommandPrefix);
    skip(lex, otk::CommandBegin);

    { // command arguments
        skip(lex, otk::CommandArgumentsBegin);
        auto args = token(org::RawText, pop(lex, otk::RawText));
        __token(args);
        skip(lex, otk::CommandArgumentsEnd);
    }

    { // command content
        skip(lex, otk::CommandContentStart);
        auto body = token(org::RawText, pop(lex, otk::RawText));
        __token(body);
        skip(lex, otk::CommandContentEnd);
    }

    skip(lex, otk::CommandPrefix);
    skip(lex, otk::CommandEnd);

    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseSrc(OrgLexer& lex) {
    __perf_trace("parseSrc");
    __trace();
    __start(org::SrcCode);
    skip(lex, otk::CommandPrefix);
    skip(lex, otk::CommandBegin);
    // header_args_lang
    {
        skipSpace(lex);
        skip(lex, otk::CommandArgumentsBegin);

        const auto lang = pop(lex, otk::Word);
        if (lex.strVal().empty()) {
            empty();
        } else {
            token(org::Ident, lang);
        }

        parseSrcArguments(lex);
        skip(lex, otk::CommandArgumentsEnd);
    };
    // body
    {

        __start(org::StmtList);
        skip(lex, otk::CommandContentStart);
        skip(lex, otk::CodeContentBegin);
        while (!lex.at(
            OrgTokSet{otk::CommandContentEnd, otk::CodeContentEnd})) {
            __start(org::CodeLine);
            while (!lex.at(OrgTokSet{
                otk::CommandContentEnd,
                otk::Newline,
                otk::CodeContentEnd})) {
                switch (lex.kind()) {
                    case otk::CodeText: {
                        token(org::CodeText, pop(lex, otk::CodeText));
                        break;
                    }
                    case otk::ParOpen: {
                        skip(lex, otk::ParOpen);
                        skip(lex, otk::Ident);
                        skip(lex, otk::Colon);
                        __start(org::CodeCallout);
                        token(org::Ident, pop(lex, otk::Ident));
                        __end();
                        skip(lex, otk::ParClose);
                        break;
                    }
                    case otk::CodeContentEnd: {
                        break;
                        break;
                    }
                    case otk::DoubleAngleOpen: {
                        skip(lex, otk::DoubleAngleOpen);
                        __start(org::CodeTangle);
                        parseCSVArguments(lex);
                        __end();
                        skip(lex, otk::DoubleAngleClose);
                        break;
                    }
                    default: {
                        assert(false);
                    }
                }
            }
            if (lex.at(otk::Newline)) {
                lex.next();
            }
            __end(); // finish code line
        }

        skip(lex, otk::CodeContentEnd);
        skip(lex, otk::CommandContentEnd);
        __end(); // finish statement
    };
    // eval_result
    { empty(); };
    skip(lex, otk::CommandPrefix);
    skip(lex, otk::CommandEnd);
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseListItemBody(OrgLexer& lex) {
    __perf_trace("parseListItemBody");
    __trace();
    __start(org::StmtList);
    while (!lex.at(otk::StmtListClose)) {
        if (lex.at(Vec<OrgTokenKind>{otk::Indent, otk::ListItemStart})) {
            lex.next();
            parseNestedList(lex);
            skip(lex, otk::Dedent);
        } else {
            parseToplevelItem(lex);
        }
    }
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseListItem(OrgLexer& lex) {
    __perf_trace("parseListItem");
    __trace();
    __start(org::ListItem);
    // prefix, 0
    { token(org::RawText, pop(lex, otk::ListItemStart)); }
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
        if (lex.at(otk::ListDescOpen)) {
            isAnnotatedParagraph = true;
            skip(lex, otk::ListDescOpen);
            __start(org::AnnotatedParagraph);
            __start(org::ListTag);
            parseParagraph(lex, false);
            __end();
            skip(lex, otk::DoubleColon);
            skip(lex, otk::ListDescClose);
            __end();
        } else {
            empty();
        }
    }
    // completion, 4
    { empty(); }
    // body, 5
    {
        skip(lex, otk::StmtListOpen);
        parseListItemBody(lex);
        skip(lex, otk::StmtListClose);
    }
    skip(lex, otk::ListItemEnd);
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseNestedList(OrgLexer& lex) {
    __perf_trace("parseNestedList");
    __trace();
    ParseCb nextLevel = [this](OrgLexer& lex) {
        skip(lex, otk::Indent);
        auto result = parseNestedList(lex);
        skip(lex, otk::Dedent);
        return result;
    };

    __start(org::List);
    while (lex.at(otk::ListItemStart)) {
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

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseList(OrgLexer& lex) {
    __perf_trace("parseList");
    __trace();
    skip(lex, otk::ListStart);
    const auto nested = lex.at(otk::Indent);
    if (nested) {
        skip(lex, otk::Indent);
    }
    auto result = parseNestedList(lex);
    if (nested) {
        skip(lex, otk::Dedent);
    }
    skip(lex, otk::ListEnd);
    return result;
}


template <>
OrgId OrgParserImpl<TRACE_STATE>::parseSubtreeLogbookClockEntry(
    OrgLexer& lex) {
    __perf_trace("parseSubtreeLogbookClockEntry");
    __trace();
    __start(org::LogbookClock);
    // CLOCK:
    skip(lex, otk::ListClock);
    skip(lex, otk::ParagraphStart);
    space(lex);
    skip(lex, otk::BigIdent);
    skip(lex, otk::Colon);
    space(lex);

    parseTimeRange(lex);

    space(lex);
    skip(lex, otk::ParagraphEnd);
    newline(lex);
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseSubtreeLogbookListEntry(
    OrgLexer& lex) {
    __perf_trace("parseSubtreeLogbookListEntry");
    __trace();
    __start(org::LogbookEntry);
    using V = TokenWithValue;

    skip(lex, otk::ListItemStart);
    skipSpace(lex);
    skip(lex, otk::StmtListOpen);
    skip(lex, otk::ParagraphStart);
    if (lex.at(otk::Word) && lex.strVal() == "State") {
        // - State "WIP" from "TODO" [2023-01-01 Sun 23:32:22]
        __start(org::LogbookStateChange);
        {

            skip(lex, V{otk::Word, "State"});
            space(lex);
            skip(lex, otk::QuoteOpen);
            token(org::BigIdent, pop(lex, otk::BigIdent));
            skip(lex, otk::QuoteClose);
            space(lex);
            skip(lex, V{otk::Word, "from"});
            space(lex);
            skip(lex, otk::QuoteOpen);
            token(org::BigIdent, pop(lex, otk::BigIdent));
            skip(lex, otk::QuoteClose);
            space(lex);
            parseTimeStamp(lex);
        }
        __end();
    } else if (lex.at(otk::Word) && lex.strVal() == "Refiled") {
        __start(org::LogbookRefile);
        {
            skip(lex, V{otk::Word, "Refiled"});
            space(lex);
            skip(lex, V{otk::Word, "on"});
            space(lex);
            parseTimeStamp(lex);
            space(lex);
            skip(lex, V{otk::Word, "from"});
            space(lex);
            parseLink(lex);
        }
        __end();
    } else if (lex.at(otk::Word) && lex.strVal() == "Note") {
        __start(org::LogbookNote);
        {
            skip(lex, V{otk::Word, "Note"});
            space(lex);
            skip(lex, V{otk::Word, "taken"});
            space(lex);
            skip(lex, V{otk::Word, "on"});
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
        skip(lex, otk::DoubleSlash);
        skip(lex, otk::Newline);

        Vec<OrgTokenId> firstParagraph;
        while (!lex.at(otk::ParagraphEnd)) {
            firstParagraph.push_back(lex.pop());
        }

        auto sub = SubLexer(lex.in, firstParagraph);

        skip(lex, otk::ParagraphEnd);

        while (!lex.at(otk::StmtListClose)) {
            parseToplevelItem(lex);
        }

        skip(lex, otk::StmtListClose);
        skip(lex, otk::ListItemEnd);
        __end();

    } else {
        skip(lex, otk::ParagraphEnd);
        skip(lex, otk::StmtListClose);
        skip(lex, otk::ListItemEnd);
        empty();
    }


    // TODO handle optional logbook entry description or note
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseSubtreeLogbook(OrgLexer& lex) {
    __perf_trace("parseSubtreeLogbook");
    __trace();
    __start(org::Logbook);
    skip(lex, otk::ColonLogbook);
    newline(lex);
    skip(lex, otk::GroupStart);
    skip(lex, otk::LogbookStart);

    skipSpace(lex);
    while (lex.at(otk::ListStart) || lex.at(otk::ListClock)) {
        switch (lex.tok().kind) {
            case otk::ListStart: {
                skip(lex, otk::ListStart);
                skip(lex, otk::Indent);
                while (lex.at(otk::ListItemStart)) {
                    parseSubtreeLogbookListEntry(lex);
                    if (lex.at(otk::SameIndent)) {
                        lex.next();
                    }
                }
                skip(lex, otk::Dedent);
                skip(lex, otk::ListEnd);
                space(lex);
                break;
            }
            case otk::ListClock: {
                parseSubtreeLogbookClockEntry(lex);
                break;
            }
            default: {
                throw wrapError(Err::UnhandledToken(lex), lex);
            }
        }
    }

    space(lex);
    skip(lex, otk::LogbookEnd);
    skip(lex, otk::ColonEnd);
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseSubtreeProperties(OrgLexer& lex) {
    __perf_trace("parseSubtreeProperties");
    __trace();
    skip(lex, otk::ColonProperties);
    skip(lex, otk::SkipNewline);
    skip(lex, otk::GroupStart);
    skip(lex, otk::SkipSpace);
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
        auto add = token(org::RawText, pop(lex, otk::ColonIdent));
        __token(add);

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

        skip(lex, otk::SkipSpace);

        token(org::RawText, pop(lex, otk::RawProperty));
        skip(lex, otk::SkipNewline);
        skip(lex, otk::SkipSpace);
        __end();
    }
    skip(lex, otk::ColonEnd);
    skip(lex, otk::GroupEnd);
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseSubtreeDrawer(OrgLexer& lex) {
    __perf_trace("parseSubtreeDrawer");
    __trace();
    skip(lex, otk::GroupStart);
    skip(lex, otk::SkipSpace);
    __start(org::Drawer);

    while (lex.at(OrgTokSet{
        otk::ColonProperties, otk::ColonLogbook, otk::ColonDescription})) {
        switch (lex.tok().kind) {
            case otk::ColonProperties: parseSubtreeProperties(lex); break;
            case otk::ColonLogbook: parseSubtreeLogbook(lex); break;
            case otk::ColonDescription: {
                skip(lex, otk::ColonDescription);
                __start(org::SubtreeDescription);
                newline(lex);
                {
                    parseParagraph(lex, false);
                    skip(lex, otk::ColonEnd);
                }
                __end();
                break;
            }
        }

        newline(lex);
        space(lex);
    }

    skip(lex, otk::GroupEnd);
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseSubtreeCompletion(OrgLexer& lex) {
    __perf_trace("parseSubtreeCompletion");
    __trace();
    if (lex.at(otk::SkipNewline) || lex.at(otk::SubtreeTagSeparator)) {
        return empty();

    } else {
        __start(org::Completion);
        qDebug() << "Parse subtree completion" << lex;
        __end_return();
    }
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseSubtreeTodo(OrgLexer& lex) {
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

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseSubtreeUrgency(OrgLexer& lex) {
    __perf_trace("parseSubtreeUrgency");
    __trace();
    skipSpace(lex);
    return empty();
}


template <>
OrgId OrgParserImpl<TRACE_STATE>::parseSubtreeTitle(OrgLexer& lex) {
    __perf_trace("parseSubtreeTitle");
    __trace();
    skipSpace(lex);
    return parseParagraph(lex, false);
}


template <>
OrgId OrgParserImpl<TRACE_STATE>::parseSubtreeTags(OrgLexer& lex) {
    __perf_trace("parseSubtreeTags");
    __trace();
    if (lex.at(otk::SubtreeTagSeparator)) {
        __start(org::InlineStmtList);
        while (lex.at(otk::SubtreeTagSeparator)
               && lex.at(otk::HashTag, +1)) {
            skip(lex, otk::SubtreeTagSeparator);
            parseHashTag(lex);
        }
        skip(lex, otk::SubtreeTagSeparator);
        __end_return();
    } else {
        return empty();
    }
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseSubtreeTimes(OrgLexer& lex) {
    __perf_trace("parseSubtreeTimes");
    __trace();
    __start(org::StmtList);
    if (lex.ahead(
            OrgTokSet{otk::SkipSpace, otk::GroupStart},
            OrgTokSet{otk::SubtreeTime})) {
        skip(lex, otk::GroupStart);
        skip(lex, otk::SkipSpace);

        while (lex.at(otk::SubtreeTime)) {
            __start(org::TimeAssoc);
            if (lex.at(otk::SubtreeTime)) {
                token(org::BigIdent, pop(lex, otk::SubtreeTime));
            } else {
                empty();
            }
            space(lex);
            parseTimeStamp(lex);
            __end();
        }

        newline(lex);
        skip(lex, otk::GroupEnd);
    } else {
        __print("No subtree time");
    }

    __end_return();
}


template <>
OrgId OrgParserImpl<TRACE_STATE>::parseSubtree(OrgLexer& lex) {
    __perf_trace("parseSubtree");
    __trace();
    __start(org::Subtree);
    // prefix

    token(org::RawText, pop(lex, otk::SubtreeStars)); // 0
    parseSubtreeTodo(lex);                            // 1
    parseSubtreeUrgency(lex);                         // 2
    parseSubtreeTitle(lex);                           // 3
    parseSubtreeCompletion(lex);                      // 4
    parseSubtreeTags(lex);                            // 5

    if (!lex.at(otk::SubtreeEnd)) {                   // 6
        skip(lex, otk::SkipNewline);
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

    skip(lex, otk::SubtreeEnd);
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseOrgFile(OrgLexer& lex) {
    __perf_trace("parseOrgFile");
    __trace();
    __start(org::File);
    if (lex.at(otk::QuoteOpen)) {
        lex.next();
        token(org::RawText, pop(lex, otk::RawText));
        skip(lex, otk::QuoteClose);
    } else {
        token(org::RawText, pop(lex, otk::RawText));
    }
    __end_return();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseLineCommand(OrgLexer& lex) {
    __perf_trace("parseLineCommand");
    __trace();
    const auto kind = classifyCommand(lex.strVal(+1));
    switch (kind) {
        case ock::Include: {
            skipLineCommand(lex);
            skip(lex, otk::CommandArgumentsBegin);
            __start(org::CommandInclude);
            parseOrgFile(lex);

            if (lex.at(otk::CommandValue)) {
                token(org::Ident, pop(lex, otk::CommandValue));
            } else {
                empty();
            }

            if (lex.at(otk::CommandValue)) {
                token(org::Ident, pop(lex, otk::CommandValue));
            } else {
                empty();
            }

            parseSrcArguments(lex);
            skip(lex, otk::CommandArgumentsEnd);
            break;
        }

        case ock::AttrHtml: {
            skipLineCommand(lex);
            skip(lex, otk::CommandArgumentsBegin);
            __start(org::CommandAttrHtml);
            parseSrcArguments(lex);
            skip(lex, otk::CommandArgumentsEnd);
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
            }

            __start(newk);
            {
                skipLineCommand(lex);
                skip(lex, otk::CommandArgumentsBegin);
                while (lex.at(otk::RawText)) {
                    token(org::RawText, pop(lex, otk::RawText));
                    if (lex.at(otk::SkipSpace)) {
                        skipSpace(lex);
                    }
                }
                skip(lex, otk::CommandArgumentsEnd);
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
            skip(lex, otk::SubtreeTagSeparator);
            break;
        }
        case ock::LatexClass:
        case ock::LatexCompiler: {
            OrgNodeKind newk = org::Empty;
            switch (kind) {
                case ock::LatexCompiler: newk = org::LatexCompiler; break;
                case ock::LatexClass: newk = org::LatexClass; break;
            }
            skipLineCommand(lex);
            skip(lex, otk::CommandArgumentsBegin);
            __start(newk);
            token(org::Ident, pop(lex, otk::Ident));
            skip(lex, otk::CommandArgumentsEnd);
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
        default: {
            throw wrapError(
                Err::UnhandledToken(lex, to_string(kind)), lex);
        }
    }

    // Placeholder statement list that might be extended in a latter pass
    __start(org::StmtList);
    __end();
    // End main tree that was started in the case statement
    __end();


    return back();
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseToplevelItem(OrgLexer& lex) {
    __perf_trace("parseToplevelItem");
    __trace();
    switch (lex.kind()) {
        case otk::ParagraphStart: return parseParagraph(lex, true);
        case otk::TableBegin: return parseTable(lex);
        case otk::SubtreeStars: return parseSubtree(lex);
        case otk::ListStart: return parseList(lex);
        case otk::SkipAny:
            return token(org::SkipAny, pop(lex, otk::SkipAny));
        case otk::SkipSpace:
            return token(org::SkipSpace, pop(lex, otk::SkipSpace));
        case otk::SkipNewline:
            return token(org::SkipNewline, pop(lex, otk::SkipNewline));
        case otk::TextSeparator:
            return token(org::TextSeparator, pop(lex, otk::TextSeparator));

        case otk::CommandPrefix: {
            const auto kind = classifyCommand(lex.strVal(1));
            switch (kind) {
                case ock::BeginSrc: return parseSrc(lex);
                case ock::BeginExample: return parseExample(lex);
                case ock::BeginQuote:
                case ock::BeginCenter:
                case ock::BeginAdmonition:
                    return parseTextWrapCommand(lex, kind);

                default: return parseLineCommand(lex);
            }
            break;
        }
        default: {
            throw wrapError(Err::UnhandledToken(lex), lex);
        }
    }
}

template <>
OrgId OrgParserImpl<TRACE_STATE>::parseTop(OrgLexer& lex) {
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


#pragma clang diagnostic pop
