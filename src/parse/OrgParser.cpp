#include "OrgParser.hpp"

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <hstd/stdlib/Debug.hpp>

#pragma clang diagnostic push
// #pragma clang diagnostic error "-Wswitch-enum"
// #pragma clang diagnostic error "-Wswitch-enum"


#define __INIT_REPORT(__subname, __lex)                                   \
    (Report{                                                              \
        .line     = __LINE__,                                             \
        .location = __CURRENT_FILE_PATH__,                                \
        .lex      = &__lex,                                               \
        .subname  = __subname,                                            \
    })

#define __trace2(__subname, __lex)                                        \
    {                                                                     \
        Report rep = __INIT_REPORT(__subname, __lex);                     \
        rep.kind   = ReportKind::EnterParse;                              \
        rep.name   = __func__;                                            \
        report(rep);                                                      \
    }                                                                     \
                                                                          \
    finally CONCAT(close, __COUNTER__) = finally::init<Str>(              \
        ([&](CR<Str> name) {                                              \
            Report rep = __INIT_REPORT(__subname, __lex);                 \
            rep.kind   = ReportKind::LeaveParse;                          \
            rep.name   = name;                                            \
            report(rep);                                                  \
        }),                                                               \
        Str(__func__));


#define __trace1(__subname) __trace2(__subname, lex)
#define __trace0() __trace2(std::nullopt, lex)

#define __trace(...)                                                      \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__trace, __VA_ARGS__)(__VA_ARGS__),             \
        BOOST_PP_EMPTY())


#define __end2(__subname, __lex)                                          \
    OrgId CONCAT(tmpNode, __LINE__) = end();                              \
    {                                                                     \
        Report rep = __INIT_REPORT(__subname, __lex);                     \
        rep.kind   = ReportKind::EndNode;                                 \
        rep.node   = CONCAT(tmpNode, __LINE__);                           \
        report(rep);                                                      \
    }


#define __end1(__subname) __end2(__subname, lex)
#define __end0() __end2(std::nullopt, lex);

#define __end(...)                                                        \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__end, __VA_ARGS__)(__VA_ARGS__),               \
        BOOST_PP_EMPTY())

#define __start3(__node, __subname, __lex)                                \
    OrgId CONCAT(tmpNode, __LINE__) = start(__node);                      \
    {                                                                     \
        Report rep = __INIT_REPORT(__subname, __lex);                     \
        rep.kind   = ReportKind::StartNode;                               \
        rep.node   = CONCAT(tmpNode, __LINE__);                           \
        report(rep);                                                      \
    }


#define __start2(__node, __subname) __start3(__node, __subname, lex)
#define __start1(__node) __start3(__node, std::nullopt, lex);

#define __start(...)                                                      \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__start, __VA_ARGS__)(__VA_ARGS__),             \
        BOOST_PP_EMPTY())


#define __token3(__node, __subname, __lex)                                \
    {                                                                     \
        Report rep = __INIT_REPORT(__subname, __lex);                     \
        rep.kind   = ReportKind::AddToken;                                \
        rep.node   = __node;                                              \
        report(rep);                                                      \
    }

#define __token2(__node, __subname) __token3(__node, __subname, lex)
#define __token1(__node) __token3(__node, std::nullopt, lex);

#define __token(...)                                                      \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__token, __VA_ARGS__)(__VA_ARGS__),             \
        BOOST_PP_EMPTY())

using otk = OrgTokenKind;
using org = OrgNodeKind;
using ock = OrgCommandKind;
using Err = OrgParser::Errors;

void space(OrgLexer& lex) {
    while (lex.at(otk::Space) || lex.at(otk::SkipSpace)) {
        lex.next();
    }
}


void skipSpace(OrgLexer& lex) {
    while (lex.at(otk::SkipSpace)) {
        lex.next();
    }
}


void newline(OrgLexer& lex) {
    while (lex.at(otk::Newline) || lex.at(otk::SkipNewline)) {
        lex.next();
    }
}


OrgId OrgParser::parseCSVArguments(OrgLexer& lex) {
    __trace();
    start(org::Ident);
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
    return end();
}

OrgId OrgParser::parseMacro(OrgLexer& lex) {
    __trace();
    start(org::Macro);
    skip(lex, otk::MacroOpen);
    parseCSVArguments(lex);
    skip(lex, otk::MacroClose);
    return end();
}

OrgId OrgParser::parseRawUrl(OrgLexer& lex) {
    __trace();
    token(org::RawLink, pop(lex, otk::RawUrl));
}

void OrgParser::textFold(OrgLexer& lex) {
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

    while (!lex.finished()) {
        // qDebug() << lex;
        switch (lex.kind()) {
            CASE_MARKUP(Bold);
            CASE_MARKUP(Italic);
            CASE_MARKUP(Underline);
            CASE_MARKUP(Strike);
            CASE_MARKUP(Verbatim);
            CASE_MARKUP(Angle);
            CASE_MARKUP(Quote);
            CASE_MARKUP(Par);

            case otk::Space: {
                auto t = token(org::Space, pop(lex, otk::Space));
                __token(t);
                break;
            }

            case otk::Escaped: {
                auto t = token(org::Escaped, pop(lex, otk::Escaped));
                __token(t);
                break;
            }

            case otk::RawText: {
                auto t = token(org::RawText, pop(lex, otk::RawText));
                __token(t);
                break;
            }

            case otk::Newline: {
                auto t = token(org::Newline, pop(lex, otk::Newline));
                __token(t);
                break;
            }

            case otk::Word: {
                auto t = token(org::Word, pop(lex, otk::Word));
                __token(t);
                break;
            }

            case otk::BigIdent: {
                auto t = token(org::BigIdent, pop(lex, otk::BigIdent));
                __token(t);
                break;
            }

            case otk::SrcOpen: parseTime(lex); break;
            case otk::AngleTime: parseTime(lex); break;
            case otk::BracketTime: parseTime(lex); break;
            case otk::HashTag: parseHashTag(lex); break;
            case otk::LinkOpen: parseLink(lex); break;
            case otk::MacroOpen: parseMacro(lex); break;
            case otk::RawUrl: parseRawUrl(lex); break;
            case otk::FootnoteStart: parseFootnote(lex); break;

            case otk::DollarOpen:
            case otk::LatexParOpen:
            case otk::DoubleDollarOpen:
            case otk::LatexBraceOpen: parseInlineMath(lex); break;


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
            case otk::StrikeInline:
                assert(
                    "Non-directional inline markup token incountered "
                    "during text parsing");

            default: {
                std::cout << "unhandled token kind "
                          << to_string(lex.kind()) << std::endl;
                assert(false);
            }
        }
    }

#undef CASE_MARKUP
}

Slice<OrgId> OrgParser::parseText(OrgLexer& lex) {
    __trace();
    OrgId first = back();
    textFold(lex);
    OrgId last = back();
    return slice(first, last);
}

OrgId OrgParser::parseLink(OrgLexer& lex) {
    __trace();
    __start(org::Link);
    skip(lex, otk::LinkOpen);
    skip(lex, otk::LinkTargetOpen);
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
    skip(lex, otk::LinkTargetClose);
    if (lex.at(otk::LinkDescriptionOpen)) {
        auto sub = SubLexer(
            lex.in,
            lex.getInside(
                {otk::LinkDescriptionOpen}, {otk::LinkDescriptionClose}));
        start(org::Paragraph);
        parseText(sub);
        end();

    } else {
        empty();
    }
    skip(lex, otk::LinkClose);
    __end();
    return back();
}

OrgId OrgParser::parseInlineMath(OrgLexer& lex) {
    __trace();
    const auto startKind = lex.tok().kind;
    const auto regular   = OrgTokSet{otk::DollarOpen, otk::LatexParOpen};
    const auto display   = OrgTokSet{
        otk::DoubleDollarOpen, otk::LatexBraceOpen};

    skip(lex, regular + display);
    start(
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

    return end();
}

OrgId OrgParser::parseSymbol(OrgLexer& lex) {
    __trace();
    skip(lex, otk::SymbolStart);
    start(org::Symbol);
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

    return end();
}

OrgId OrgParser::parseHashTag(OrgLexer& lex) {
    __trace();
    start(org::HashTag);
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
        };
    };
    return end();
}

OrgId OrgParser::parseTime(OrgLexer& lex) {
    __trace();
    const OrgTokSet times{otk::BracketTime, otk::AngleTime};
    if (lex.ahead(times, OrgTokSet{otk::TimeDash})) {
        start(org::TimeRange);
        // IMPLEMENT check for identical start/end bracket categories:
        // `[]--[]` or `<>--<>` but not `<>--[]`
        token(org::TimeStamp, pop(lex, times));
        skip(lex, otk::TimeDash);
        token(org::TimeStamp, pop(lex, times));
        if (lex.at(otk::TimeArrow)) {
            skip(lex, otk::TimeArrow);
            token(org::SimpleTime, pop(lex, otk::TimeDuration));
        } else {
            empty();
        }
        return end();
    } else {
        return token(org::TimeStamp, pop(lex, times));
    }
}

OrgId OrgParser::parseFootnote(OrgLexer& lex) {
    __trace();
    // TODO replace 'footnote start' + '::' with a 'inline footnote start'
    // / 'footnote start nodes'
    skip(lex, otk::FootnoteStart);
    if (lex.at(otk::Colon)) {
        start(org::Footnote);
        skip(lex, otk::Colon);
        parseIdent(lex);
    } else {
        start(org::InlineFootnote);
        skip(lex, otk::DoubleColon);
        parseInlineParagraph(lex);
    }
    skip(lex, otk::FootnoteEnd);
    return end();
}

OrgId OrgParser::parseIdent(OrgLexer& lex) {
    __trace();
    token(org::Ident, pop(lex, otk::Ident));
}

OrgId OrgParser::parseSrcInline(OrgLexer& lex) {
    __trace();
    start(org::SrcInlineCode);
    {
        parseIdent(lex);
        token(org::Ident, pop(lex, otk::SrcName));
        start(org::CodeLine);
        token(org::CodeText, pop(lex, otk::SrcBody));
    }
    end();
    skip(lex, otk::SrcClose);
    return end();
}

OrgId OrgParser::parseTable(OrgLexer& lex) {
    __trace();
    start(org::Table);
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
                start(org::TableRow);
                empty();
                empty();

                skip(lex, otk::PipeOpen);
                start(org::TableCell);
                {
                    empty();
                    parseContent(lex);
                }
                end();

                while (lex.at(otk::PipeSeparator)) {
                    skip(lex, otk::PipeSeparator);
                    start(org::TableCell);
                    {
                        empty();
                        parseContent(lex);
                    }
                    end();
                }

                skip(lex, otk::PipeClose);
                end();
                break;
            }
            case otk::PipeCellOpen: {
                start(org::TableRow);
                empty();
                empty();

                skip(lex, otk::PipeCellOpen);
                start(org::TableCell);
                {

                    empty();
                    parseContent(lex);
                }
                end();

                while (lex.at(otk::PipeCellOpen)) {
                    skip(lex, otk::PipeCellOpen);
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
            case otk::RowSpec: {
                start(org::TableRow);
                empty();
                skip(lex, otk::RowSpec);
                skip(lex, otk::CmdArguments);
                empty();
                start(org::TableCell);
                {
                    empty();
                    parseContent(lex);
                }
                end();
                while (lex.at(otk::CellSpec)) {
                    skip(lex, otk::CellSpec);
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
            case otk::TableEnd: {
                break;
            }
            default: {
                assert(false);
            }
        };
    };
    skip(lex, otk::TableEnd);
    return end();
}

OrgId OrgParser::parseParagraph(OrgLexer& lex, bool onToplevel) {
    __trace();
    lex.expect(otk::ParagraphStart);
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

OrgId OrgParser::parseInlineParagraph(OrgLexer& lex) {
    __trace();
    return parseParagraph(lex, false);
}


OrgId OrgParser::parseTopParagraph(OrgLexer& lex) {
    __trace();
    return parseParagraph(lex, false);
}


OrgId OrgParser::parseCommandArguments(OrgLexer& lex) {
    __trace();
    start(org::InlineStmtList);
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

    return end();
}

OrgId OrgParser::parseSrcArguments(OrgLexer& lex) {
    __trace();
    start(org::CmdArguments);
    start(org::InlineStmtList);

    while (lex.at(otk::CommandFlag)) {
        token(org::CmdFlag, pop(lex, otk::CommandFlag));
    }
    end();
    parseCommandArguments(lex);
    return end();
}

OrgId OrgParser::parseTextWrapCommand(OrgLexer& lex, OrgCommandKind kind) {
    __trace();
    switch (kind) {
        case ock::BeginCenter: {
            start(org::CenterBlock);
            break;
        }
        case ock::BeginQuote: {
            start(org::QuoteBlock);
            break;
        }
        case ock::BeginAdmonition: {
            start(org::AdmonitionBlock);
            break;
        }
        default: {
            assert(false);
        }
    }
    skip(lex, otk::CommandPrefix);
    skip(lex, otk::CommandBegin);
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
    return end();
}

OrgId OrgParser::parseSrc(OrgLexer& lex) {
    __trace();
    start(org::SrcCode);
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

        start(org::StmtList);
        skip(lex, otk::CommandContentStart);
        skip(lex, otk::CodeContentBegin);
        while (!lex.at(
            OrgTokSet{otk::CommandContentEnd, otk::CodeContentEnd})) {
            start(org::CodeLine);
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
                        start(org::CodeCallout);
                        token(org::Ident, pop(lex, otk::Ident));
                        end();
                        skip(lex, otk::ParClose);
                        break;
                    }
                    case otk::CodeContentEnd: {
                        break;
                        break;
                    }
                    case otk::DoubleAngleOpen: {
                        skip(lex, otk::DoubleAngleOpen);
                        start(org::CodeTangle);
                        parseCSVArguments(lex);
                        end();
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
            end(); // finish code line
        }

        skip(lex, otk::CodeContentEnd);
        skip(lex, otk::CommandContentEnd);
        end(); // finish statement
    };
    // eval_result
    { empty(); };
    skip(lex, otk::CommandPrefix);
    skip(lex, otk::CommandEnd);
    return end();
}

OrgId OrgParser::parseListItemBody(OrgLexer& lex) {
    __trace();
    start(org::StmtList);
    while (!lex.at(otk::StmtListClose)) {
        if (lex.at(Vec<OrgTokenKind>{otk::Indent, otk::ListItemStart})) {
            lex.next();
            parseNestedList(lex);
            skip(lex, otk::Dedent);
        } else {
            parseToplevelItem(lex);
        }
    }
    return end();
}

OrgId OrgParser::parseListItem(OrgLexer& lex) {
    __trace();
    start(org::ListItem);
    // prefix
    { token(org::RawText, pop(lex, otk::ListItemStart)); }
    skipSpace(lex);
    // counter
    {
        empty(); // TODO parse counter
    }
    // checkbox
    {
        if (lex.at(otk::Checkbox)) {
            token(org::Checkbox, pop(lex, otk::Checkbox));
        } else {
            empty();
        }
    }
    // tag
    bool isAnnotatedParagraph = false;
    {
        if (lex.at(otk::ListDescOpen)) {
            isAnnotatedParagraph = true;
            skip(lex, otk::ListDescOpen);
            start(org::AnnotatedParagraph);
            start(org::ListTag);
            parseParagraph(lex, false);
            end();
            skip(lex, otk::ListDescClose);
            skip(lex, otk::DoubleColon);
            end();
        } else {
            empty();
        }
    }
    // completion
    {
        skip(lex, otk::StmtListOpen);
        parseListItemBody(lex);
        skip(lex, otk::StmtListClose);
    }
    skip(lex, otk::ListItemEnd);
    return end();
}

OrgId OrgParser::parseNestedList(OrgLexer& lex) {
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
            return end();
        } else if (lex.at(otk::Indent)) {
            nextLevel(lex);
        } else if (lex.at(otk::ListEnd)) {
            return end();
        } else {
            assert(false);
        }
    }
    __end();
    return back();
}

OrgId OrgParser::parseList(OrgLexer& lex) {
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

OrgId OrgParser::parseLogbookClockEntry(OrgLexer& lex) {
    __trace();
    start(org::LogbookClock);
    // CLOCK:
    skip(lex, otk::ListClock);
    skip(lex, otk::ParagraphStart);
    space(lex);
    skip(lex, otk::BigIdent);
    skip(lex, otk::Colon);
    space(lex);

    parseTime(lex);

    space(lex);
    skip(lex, otk::ParagraphEnd);
    skip(lex, otk::ListItemEnd);
    return end();
}

OrgId OrgParser::parseLogbookListEntry(OrgLexer& lex) {
    __trace();
    skip(lex, otk::ListItemStart);
    const auto pos = lex.find(
        OrgTokSet{otk::DoubleSlash}, OrgTokSet{otk::ListItemEnd});

    const auto head = lex.pop(
        pos == -1 ? lex.find(otk::ListItemEnd) - 1 : pos);
    // head_parser
    {
        auto sub = SubLexer(lex.in, head);
        sub.skip(otk::StmtListOpen);
        sub.skip(otk::ParagraphStart);
        if (sub.at(otk::Word) && sub.strVal() == "State") {
            start(org::LogbookStateChange);
            sub.skip(otk::Word);
            sub.trySkip(otk::Space);
            sub.skip(otk::QuoteOpen);
            token(org::BigIdent, sub.pop(otk::BigIdent));
            sub.skip(otk::QuoteClose);
            sub.trySkip(otk::Space);
            if (sub.at(otk::QuoteOpen)) {
                sub.skip(otk::QuoteOpen);
                token(org::BigIdent, sub.pop(otk::BigIdent));
                sub.skip(otk::QuoteClose);
                sub.trySkip(otk::Space);
            };
            parseTime(lex);
            end();
        } else if (lex.at(otk::Word) && lex.strVal() == "Refiled") {
            start(org::LogbookRefile);
            skip(lex, TokenWithValue{otk::Word, "Refiled"});
            space(lex);
            skip(lex, TokenWithValue{otk::Word, "on"});
            space(lex);
            parseTime(lex);
            space(lex);
            skip(lex, TokenWithValue{otk::Word, "from"});
            space(lex);
            parseLink(lex);
            end();
        } else if (lex.at(otk::Word) && lex.strVal() == "Note") {
            start(org::LogbookNote);
            skip(lex, TokenWithValue{otk::Word, "Note"});
            space(lex);
            skip(lex, TokenWithValue{otk::Word, "taken"});
            space(lex);
            skip(lex, TokenWithValue{otk::Word, "on"});
            space(lex);
            parseTime(lex);
            space(lex);
            if (lex.at(otk::DoubleSlash)) {
                skip(lex, otk::DoubleSlash);
            };
            end();
        } else {
            assert(false);
        }
    }
    // body_parser
    {
        if (pos == -1) {
            empty();
            skip(lex, otk::ListItemEnd);
        } else {
            Vec<OrgTokenId> tokens;
            tokens.push_back(lex.in->add(OrgToken(otk::ParagraphStart)));
            tokens.append(lex.pop(lex.find(otk::ListItemEnd)));

            tokens = strip(
                lex,
                tokens,
                {otk::Newline, otk::Space},
                {otk::Newline, otk::Space},
                {otk::StmtListOpen, otk::ParagraphStart},
                {otk::StmtListClose, otk::ParagraphEnd, otk::ListItemEnd});

            auto sub = SubLexer(lex.in, tokens);
            parseListItemBody(sub);
        }
    }
    return end();
}

OrgId OrgParser::parseLogbook(OrgLexer& lex) {
    __trace();
    start(org::Logbook);
    skip(lex, otk::ColonLogbook);
    skip(lex, otk::LogbookStart);
    skip(lex, otk::ListStart);

    const auto indented = lex.at(otk::Indent);
    if (indented) {
        skip(lex, otk::Indent);
    }
    while (!lex.at(indented ? otk::Dedent : otk::ListEnd)) {
        switch (lex.tok().kind) {
            case otk::ListItemStart: {
                parseLogbookListEntry(lex);
                break;
            }
            case otk::ListClock: {
                parseLogbookClockEntry(lex);
                break;
            }
            case otk::SameIndent: {
                skip(lex, otk::SameIndent);
                break;
            }
            default: {
                assert(false);
            }
        }
    }

    if (indented) {
        skip(lex, otk::Dedent);
    }

    skip(lex, otk::ListEnd);
    skip(lex, otk::LogbookEnd);
    skip(lex, otk::ColonEnd);
    return end();
}

OrgId OrgParser::parseDrawer(OrgLexer& lex) {
    __trace();
    start(org::Drawer);
    while (lex.at(OrgTokSet{
        otk::ColonProperties, otk::ColonLogbook, otk::ColonDescription})) {
        switch (lex.tok().kind) {
            case otk::ColonProperties: {
                skip(lex, otk::ColonProperties);
                start(org::PropertyList);
                while (lex.at(
                    OrgTokSet{otk::ColonIdent, otk::ColonAddIdent})) {
                    start(
                        lex.at(otk::ColonIdent) ? org::Property
                                                : org::PropertyAdd);

                    token(
                        org::RawText,
                        pop(lex,
                            OrgTokSet{
                                otk::ColonIdent, otk::ColonAddIdent}));

                    if (lex.at(otk::Ident)) {
                        token(org::Ident, pop(lex, otk::Ident));
                    }

                    token(org::RawText, pop(lex, otk::RawProperty));
                    end();
                }
                skip(lex, otk::ColonEnd);
                end();
                break;
            }
            case otk::ColonLogbook: {
                parseLogbook(lex);
                break;
            }
            case otk::ColonDescription: {
                skip(lex, otk::ColonDescription);
                start(org::SubtreeDescription);
                parseParagraph(lex, false);
                skip(lex, otk::ColonEnd);
                end();
                break;
            }
        }
    }
    return end();
}

OrgId OrgParser::parseSubtree(OrgLexer& lex) {
    __trace();
    start(org::Subtree);
    // prefix

    { token(org::RawText, pop(lex, otk::SubtreeStars)); };
    // todo_status
    {
        skipSpace(lex);
        if (lex.at(otk::SubtreeTodoState)) {
            token(org::BigIdent, pop(lex, otk::SubtreeTodoState));
        } else {
            empty();
        };
    }
    // urgency
    {
        skipSpace(lex);
        empty();
    }
    // subtree_title
    {
        skipSpace(lex);
        parseParagraph(lex, false);
    }
    // subtree_completion
    { empty(); }
    // tree_tags
    {
        if (lex.at(otk::SubtreeTag)) {
            start(org::InlineStmtList);
            while (lex.at(otk::SubtreeTag)) {
                token(org::OrgTag, pop(lex, otk::SubtreeTag));
            }
            end();
        } else {
            empty();
        }
    }
    // subtree_time
    {

        start(org::StmtList);
        while (lex.at(otk::SubtreeTime) || lex.at(otk::BracketTime)) {
            start(org::TimeAssoc);
            if (lex.at(otk::SubtreeTime)) {
                token(org::BigIdent, pop(lex, otk::SubtreeTime));
            } else {
                empty();
            }
            token(org::TimeStamp, pop(lex, otk::BracketTime));
            end();
        }

        end();
    };
    // tree_drawer
    { parseDrawer(lex); };
    newline(lex);
    skip(lex, otk::SubtreeEnd);
    return end();
}

void OrgParser::skipLineCommand(OrgLexer& lex) {
    __trace();
    skip(lex, otk::CommandPrefix);
    skip(lex, otk::LineCommand);
    skip(lex, otk::Colon);
}

OrgId OrgParser::parseOrgFile(OrgLexer& lex) {
    __trace();
    start(org::File);
    if (lex.at(otk::QuoteOpen)) {
        lex.next();
        token(org::RawText, pop(lex, otk::RawText));
        skip(lex, otk::QuoteClose);
    } else {
        token(org::RawText, pop(lex, otk::RawText));
    }
    return end();
}

OrgId OrgParser::parseLineCommand(OrgLexer& lex) {
    __trace();
    const auto kind           = classifyCommand(lex.strVal(+1));
    auto       skipLineComand = [this](OrgLexer& lex) {
        skip(lex, otk::CommandPrefix);
        skip(lex, otk::LineCommand);
        skip(lex, otk::Colon);
    };

    switch (kind) {
        case ock::Include: {
            skipLineCommand(lex);
            skip(lex, otk::CommandArgumentsBegin);
            start(org::CommandInclude);
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
            start(org::CommandAttrHtml);
            parseSrcArguments(lex);
            end();
            skip(lex, otk::CommandArgumentsEnd);
            break;
        }

        case ock::Title: {
            skipLineCommand(lex);
            start(org::CommandTitle);
            parseParagraph(lex, false);
            end();
            break;
        }

        case ock::Caption: {
            skipLineCommand(lex);
            start(org::CommandCaption);
            parseParagraph(lex, false);
            end();
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
            skipLineCommand(lex);
            start(newk);
            skipSpace(lex);
            token(org::RawText, pop(lex, otk::RawText));
            end();
            break;
        }

        case ock::Filetags: {
            skipLineCommand(lex);
            start(org::Filetags);
            token(org::OrgTag, pop(lex, otk::SubtreeTag));
            end();
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
            start(newk);
            token(org::Ident, pop(lex, otk::RawText));
            end();
            break;
        }

        case ock::Property: {
            skipLineCommand(lex);
            start(org::Property);
            token(org::RawText, pop(lex, otk::Ident));
            empty();
            token(org::RawText, pop(lex, otk::RawProperty));
            end();
            break;
        }
        default: {
            assert(false && "TODO");
        }
    }
    return end();
}

OrgId OrgParser::parseToplevelItem(OrgLexer& lex) {
    __trace();
    switch (lex.kind()) {
        case otk::ParagraphStart: return parseParagraph(lex, true);
        case otk::TableBegin: return parseTable(lex);
        case otk::SubtreeStars: return parseSubtree(lex);
        case otk::ListStart: return parseList(lex);
        case otk::SkipNewline:
            return token(org::SkipNewline, pop(lex, otk::SkipNewline));
        case otk::TextSeparator:
            return token(org::TextSeparator, pop(lex, otk::TextSeparator));

        case otk::CommandPrefix: {
            const auto kind = classifyCommand(lex.strVal(1));
            switch (kind) {
                case ock::BeginSrc: return parseSrc(lex);
                case ock::BeginQuote:
                case ock::BeginCenter:
                case ock::BeginAdmonition: {
                    return parseTextWrapCommand(lex, kind);
                }
                default: {
                    return parseLineCommand(lex);
                }
            }
            break;
        }
        default: {
            throw wrapError(Err::UnhandledToken(lex), lex);
        }
    }
}

OrgId OrgParser::parseTop(OrgLexer& lex) {
    __trace();
    start(org::StmtList);
    while (lex.hasNext()) {
        if (lex.at(otk::Comment)) {
            lex.next();
        } else {
            parseToplevelItem(lex);
        };
    }
    return end();
}

#pragma clang diagnostic pop
