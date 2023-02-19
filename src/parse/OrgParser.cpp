#include "OrgParser.hpp"

#pragma clang diagnostic push
// #pragma clang diagnostic error "-Wswitch-enum"
// #pragma clang diagnostic error "-Wswitch-enum"

using otk = OrgTokenKind;
using org = OrgNodeKind;
using ock = OrgCommandKind;

OrgId OrgParser::parseCSVArguments(OrgLexer& lex) {
    start(org::Ident);
    lex.skip(otk::Ident);

    if (lex.at(otk::ParOpen)) {
        lex.skip(otk::ParOpen);
        while (lex.at(otk::RawText)) {
            token(org::RawText, lex.pop(otk::RawText));
            if (lex.at(otk::Comma)) {
                lex.next();
            }
        }
        lex.skip(otk::ParClose);
    }
    return end();
}

OrgId OrgParser::parseMacro(OrgLexer& lex) {
    start(org::Macro);
    lex.skip(otk::MacroOpen);
    parseCSVArguments(lex);
    lex.skip(otk::MacroClose);
    return end();
}

OrgId OrgParser::parseRawUrl(OrgLexer& lex) {
    token(org::RawLink, lex.pop(otk::RawUrl));
}

void OrgParser::textFold(OrgLexer& lex) {
#define CASE_MARKUP(Kind)                                                 \
    case otk::Kind##Open: {                                               \
        start(org::Kind, lex);                                            \
        textFold(lex);                                                    \
        break;                                                            \
    }                                                                     \
                                                                          \
    case otk::Kind##Close: {                                              \
        if (pending().kind == org::Kind) {                                \
            end(lex);                                                     \
        } else {                                                          \
            fail(lex.pop());                                              \
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

            case otk::Space: token(org::Space, lex.pop()); break;
            case otk::Escaped: token(org::Escaped, lex.pop()); break;
            case otk::RawText: token(org::RawText, lex.pop()); break;
            case otk::Newline: token(org::Newline, lex.pop()); break;
            case otk::Word: token(org::Word, lex.pop()); break;

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
                lex.skip(otk::DoubleAngleOpen);
                token(org::Target, lex.pop(otk::RawText));
                lex.skip(otk::DoubleAngleClose);
                break;
            }

            case otk::TripleAngleOpen: {
                lex.skip(otk::TripleAngleOpen);
                token(org::RadioTarget, lex.pop(otk::RawText));
                lex.skip(otk::TripleAngleClose);
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

                // default: {
                //     std::cout << "unhandled token kind "
                //               << to_string(lex.kind()) << std::endl;
                //     assert(false);
                // }
        }
    }

#undef CASE_MARKUP
}

Slice<OrgId> OrgParser::parseText(OrgLexer& lex) {
    OrgId first = back();
    textFold(lex);
    OrgId last = back();
    return slice(first, last);
}

OrgId OrgParser::parseLink(OrgLexer& lex) {
    start(org::Link);
    lex.skip(otk::LinkOpen);
    lex.skip(otk::LinkTargetOpen);
    if (lex.at(otk::LinkInternal)) {
        empty();
        token(org::RawText, lex.pop(otk::LinkInternal));
    } else if (lex.at(otk::LinkFull)) {
        empty();
        token(org::RawText, lex.pop(otk::LinkFull));
    } else {
        token(org::Ident, lex.pop(otk::LinkProtocol));
        token(org::RawText, lex.pop(otk::LinkTarget));
    }
    lex.skip(otk::LinkTargetClose);
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
    lex.skip(otk::LinkClose);
    return end();
}

OrgId OrgParser::parseInlineMath(OrgLexer& lex) {
    const auto startKind = lex.tok().kind;
    const auto regular   = OrgTokSet{otk::DollarOpen, otk::LatexParOpen};
    const auto display   = OrgTokSet{
        otk::DoubleDollarOpen, otk::LatexBraceOpen};

    lex.skip(regular + display);
    start(
        regular.contains(startKind) ? org::InlineMath : org::DisplayMath);

    OrgTokenKind close;
    switch (startKind) {
        case otk::DollarOpen: {
            lex.skip(otk::DollarClose);
            break;
        }
        case otk::DoubleDollarOpen: {
            lex.skip(otk::DoubleDollarClose);
            break;
        }
        case otk::LatexParOpen: {
            lex.skip(otk::LatexParClose);
            break;
        }
        case otk::LatexBraceOpen: {
            lex.skip(otk::LatexBraceClose);
            break;
        }
        default: {
            assert(false);
        }
    }

    return end();
}

OrgId OrgParser::parseSymbol(OrgLexer& lex) {
    lex.skip(otk::SymbolStart);
    start(org::Symbol);
    token(org::Ident, lex.pop(otk::Ident));

    if (lex.at(otk::MetaBraceOpen)) {
        assert(false);
    } else {
        empty();
    }

    while (lex.at(otk::MetaArgsOpen)) {
        lex.skip(otk::MetaArgsOpen);
        lex.skip(otk::MetaArgsBody);
        lex.skip(otk::MetaArgsClose);
    }

    return end();
}

OrgId OrgParser::parseHashTag(OrgLexer& lex) {
    start(org::HashTag);
    token(org::RawText, lex.pop(otk::HashTag));

    if (lex.at(otk::HashTagSub)) {
        lex.skip(otk::HashTagSub);
        if (lex.at(otk::HashTag)) {
            parseHashTag(lex);

        } else {
            lex.skip(otk::HashTagOpen);
            while (!lex.finished() && !lex.at(otk::HashTagClose)) {
                parseHashTag(lex);
                if (lex.at(otk::Comma)) {
                    lex.next();
                };
            }
            lex.skip(otk::HashTagClose);
        };
    };
    return end();
}

OrgId OrgParser::parseTime(OrgLexer& lex) {
    const OrgTokSet times{otk::BracketTime, otk::AngleTime};
    if (lex.ahead(times, OrgTokSet{otk::TimeDash})) {
        start(org::TimeRange);
        // IMPLEMENT check for identical start/end bracket categories:
        // `[]--[]` or `<>--<>` but not `<>--[]`
        token(org::TimeStamp, lex.pop(times));
        lex.skip(otk::TimeDash);
        token(org::TimeStamp, lex.pop(times));
        if (lex.at(otk::TimeArrow)) {
            lex.skip(otk::TimeArrow);
            token(org::SimpleTime, lex.pop(otk::TimeDuration));
        } else {
            empty();
        }
        return end();
    } else {
        return token(org::TimeStamp, lex.pop(times));
    }
}

OrgId OrgParser::parseFootnote(OrgLexer& lex) {
    // TODO replace 'footnote start' + '::' with a 'inline footnote start'
    // / 'footnote start nodes'
    lex.skip(otk::FootnoteStart);
    if (lex.at(otk::Colon)) {
        start(org::Footnote);
        lex.skip(otk::Colon);
        parseIdent(lex);
    } else {
        start(org::InlineFootnote);
        lex.skip(otk::DoubleColon);
        parseInlineParagraph(lex);
    }
    lex.skip(otk::FootnoteEnd);
    return end();
}

OrgId OrgParser::parseIdent(OrgLexer& lex) {
    token(org::Ident, lex.pop(otk::Ident));
}

OrgId OrgParser::parseSrcInline(OrgLexer& lex) {
    start(org::SrcInlineCode);
    {
        parseIdent(lex);
        token(org::Ident, lex.pop(otk::SrcName));
        start(org::CodeLine);
        token(org::CodeText, lex.pop(otk::SrcBody));
    }
    end();
    lex.skip(otk::SrcClose);
    return end();
}

OrgId OrgParser::parseTable(OrgLexer& lex) {
    start(org::Table);
    lex.skip(otk::TableBegin);
    lex.skip(otk::CmdArguments);
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

                lex.skip(otk::PipeOpen);
                start(org::TableCell);
                {
                    empty();
                    parseContent(lex);
                }
                end();

                while (lex.at(otk::PipeSeparator)) {
                    lex.skip(otk::PipeSeparator);
                    start(org::TableCell);
                    {
                        empty();
                        parseContent(lex);
                    }
                    end();
                }

                lex.skip(otk::PipeClose);
                end();
                break;
            }
            case otk::PipeCellOpen: {
                start(org::TableRow);
                empty();
                empty();

                lex.skip(otk::PipeCellOpen);
                start(org::TableCell);
                {

                    empty();
                    parseContent(lex);
                }
                end();

                while (lex.at(otk::PipeCellOpen)) {
                    lex.skip(otk::PipeCellOpen);
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
                lex.skip(otk::RowSpec);
                lex.skip(otk::CmdArguments);
                empty();
                start(org::TableCell);
                {
                    empty();
                    parseContent(lex);
                }
                end();
                while (lex.at(otk::CellSpec)) {
                    lex.skip(otk::CellSpec);
                    lex.skip(otk::CmdArguments);
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
    lex.skip(otk::TableEnd);
    return end();
}

OrgId OrgParser::parseParagraph(OrgLexer& lex, bool onToplevel) {
    std::cout << "pos " << lex.pos << std::endl;
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


    start(org::Paragraph);
    auto nodes = parseText(sub);
    return end();
}

OrgId OrgParser::parseInlineParagraph(OrgLexer& lex) {
    return parseParagraph(lex, false);
}


OrgId OrgParser::parseTopParagraph(OrgLexer& lex) {
    return parseParagraph(lex, false);
}


OrgId OrgParser::parseCommandArguments(OrgLexer& lex) {
    start(org::InlineStmtList);
    while (lex.at(OrgTokSet{otk::CommandValue, otk::CommandKey})) {
        if (lex.at(otk::CommandKey)) {
            start(org::CmdValue);
            {
                token(org::Ident, lex.pop(otk::CommandKey));
                token(org::RawText, lex.pop(otk::CommandValue));
            }
            end();
        } else {
            start(org::CmdValue);
            {
                empty();
                token(org::RawText, lex.pop(otk::CommandValue));
            }
            end();
        }
    }

    return end();
}

OrgId OrgParser::parseSrcArguments(OrgLexer& lex) {
    start(org::CmdArguments);
    start(org::InlineStmtList);

    while (lex.at(otk::CommandFlag)) {
        token(org::CmdFlag, lex.pop());
    }
    end();
    parseCommandArguments(lex);
    return end();
}

OrgId OrgParser::parseTextWrapCommand(OrgLexer& lex, OrgCommandKind kind) {
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
    lex.skip(otk::CommandPrefix);
    lex.skip(otk::CommandBegin);
    lex.skip(otk::CommandArgumentsBegin);
    if (lex.at(otk::RawText)) {
        lex.next();
    } else if (lex.at(otk::Ident)) {
        lex.next();
    };
    lex.skip(otk::CommandArgumentsEnd);
    lex.skip(otk::CommandContentStart);
    parseParagraph(lex, true);
    lex.skip(otk::CommandContentEnd);
    lex.skip(otk::CommandPrefix);
    lex.skip(otk::CommandEnd);
    return end();
}

OrgId OrgParser::parseSrc(OrgLexer& lex) {
    start(org::SrcCode);
    lex.skip(otk::CommandPrefix);
    lex.skip(otk::CommandBegin);
    // header_args_lang
    {
        lex.skip(otk::CommandArgumentsBegin);

        const auto lang = lex.pop(otk::Word);
        if (lex.strVal().empty()) {
            empty();
        } else {
            token(org::Ident, lang);
        }

        parseSrcArguments(lex);
        lex.skip(otk::CommandArgumentsEnd);
    };
    // body
    {

        start(org::StmtList);
        lex.skip(otk::CommandContentStart);
        lex.skip(otk::CodeContentBegin);
        while (!lex.at(
            OrgTokSet{otk::CommandContentEnd, otk::CodeContentEnd})) {
            start(org::CodeLine);
            while (!lex.at(OrgTokSet{
                otk::CommandContentEnd,
                otk::Newline,
                otk::CodeContentEnd})) {
                switch (lex.kind()) {
                    case otk::CodeText: {
                        token(org::CodeText, lex.pop(otk::CodeText));
                        break;
                    }
                    case otk::ParOpen: {
                        lex.skip(otk::ParOpen);
                        lex.skip(otk::Ident);
                        lex.skip(otk::Colon);
                        start(org::CodeCallout);
                        token(org::Ident, lex.pop(otk::Ident));
                        end();
                        lex.skip(otk::ParClose);
                        break;
                    }
                    case otk::CodeContentEnd: {
                        break;
                        break;
                    }
                    case otk::DoubleAngleOpen: {
                        lex.skip(otk::DoubleAngleOpen);
                        start(org::CodeTangle);
                        parseCSVArguments(lex);
                        end();
                        lex.skip(otk::DoubleAngleClose);
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

        lex.skip(otk::CodeContentEnd);
        lex.skip(otk::CommandContentEnd);
        end(); // finish statement
    };
    // eval_result
    { empty(); };
    lex.skip(otk::CommandPrefix);
    lex.skip(otk::CommandEnd);
    return end();
}

OrgId OrgParser::parseListItemBody(OrgLexer& lex) {
    start(org::StmtList);
    while ((!(lex.at(otk::StmtListClose)))) {
        if (lex.at(Vec<OrgTokenKind>{otk::Indent, otk::ListDash})) {
            lex.next();
            parseNestedList(lex);
            lex.skip(otk::Dedent);
        } else {
            parseToplevelItem(lex);
        }
    }
    return end();
}

OrgId OrgParser::parseListItem(OrgLexer& lex) {
    start(org::ListItem);
    // prefix
    { token(org::RawText, lex.pop(otk::ListDash)); }
    // counter
    {
        empty(); // TODO parse counter
    }
    // checkbox
    {
        if (lex.at(otk::Checkbox)) {
            token(org::Checkbox, lex.pop());
        } else {
            empty();
        }
    }
    // tag
    bool isAnnotatedParagraph = false;
    {
        if (lex.at(otk::ListDescOpen)) {
            isAnnotatedParagraph = true;
            lex.skip(otk::ListDescOpen);
            start(org::AnnotatedParagraph);
            start(org::ListTag);
            parseParagraph(lex, false);
            end();
            lex.skip(otk::ListDescClose);
            lex.skip(otk::DoubleColon);
            end();
        } else {
            empty();
        }
    }
    // completion
    {
        assert(false && "TODO"); //
    }
    lex.skip(otk::ListItemEnd);
    return end();
}

OrgId OrgParser::parseNestedList(OrgLexer& lex) {
    ParseCb nextLevel = [this](OrgLexer& lex) {
        lex.skip(otk::Indent);
        auto result = parseNestedList(lex);
        lex.skip(otk::Dedent);
        return result;
    };

    start(org::List);
    while (lex.at(otk::ListDash)) {
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
    return end();
}

OrgId OrgParser::parseList(OrgLexer& lex) {

    lex.skip(otk::ListStart);
    const auto nested = lex.at(otk::Indent);
    if (nested) {
        lex.skip(otk::Indent);
    }
    auto result = parseNestedList(lex);
    if (nested) {
        lex.skip(otk::Dedent);
    }
    lex.skip(otk::ListEnd);
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
    start(org::LogbookClock);
    // CLOCK:
    lex.skip(otk::ListClock);
    lex.skip(otk::ParagraphStart);
    lex.trySkip(otk::Space);
    lex.skip(otk::BigIdent);
    lex.skip(otk::Colon);
    lex.trySkip(otk::Space);

    parseTime(lex);

    lex.trySkip(otk::Space);
    lex.skip(otk::ParagraphEnd);
    lex.skip(otk::ListItemEnd);
    return end();
}

OrgId OrgParser::parseLogbookListEntry(OrgLexer& lex) {
    lex.skip(otk::ListDash);
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
            lex.skip(otk::Word, "Refiled");
            lex.trySkip(otk::Space);
            lex.skip(otk::Word, "on");
            lex.trySkip(otk::Space);
            parseTime(lex);
            lex.trySkip(otk::Space);
            lex.skip(otk::Word, "from");
            lex.trySkip(otk::Space);
            parseLink(lex);
            end();
        } else if (lex.at(otk::Word) && lex.strVal() == "Note") {
            start(org::LogbookNote);
            lex.skip(otk::Word, "Note");
            lex.trySkip(otk::Space);
            lex.skip(otk::Word, "taken");
            lex.trySkip(otk::Space);
            lex.skip(otk::Word, "on");
            lex.trySkip(otk::Space);
            parseTime(lex);
            lex.trySkip(otk::Space);
            if (lex.at(otk::DoubleSlash)) {
                lex.skip(otk::DoubleSlash);
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
            lex.skip(otk::ListItemEnd);
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
    start(org::Logbook);
    lex.skip(otk::ColonLogbook);
    lex.skip(otk::LogbookStart);
    lex.skip(otk::ListStart);

    const auto indented = lex.at(otk::Indent);
    if (indented) {
        lex.skip(otk::Indent);
    }
    while (!lex.at(indented ? otk::Dedent : otk::ListEnd)) {
        switch (lex.tok().kind) {
            case otk::ListDash: {
                parseLogbookListEntry(lex);
                break;
            }
            case otk::ListClock: {
                parseLogbookClockEntry(lex);
                break;
            }
            case otk::SameIndent: {
                lex.skip(otk::SameIndent);
                break;
            }
            default: {
                assert(false);
            }
        }
    }

    if (indented) {
        lex.skip(otk::Dedent);
    }

    lex.skip(otk::ListEnd);
    lex.skip(otk::LogbookEnd);
    lex.skip(otk::ColonEnd);
    return end();
}

OrgId OrgParser::parseDrawer(OrgLexer& lex) {
    start(org::Drawer);
    while (lex.at(OrgTokSet{
        otk::ColonProperties, otk::ColonLogbook, otk::ColonDescription})) {
        switch (lex.tok().kind) {
            case otk::ColonProperties: {
                lex.skip(otk::ColonProperties);
                start(org::PropertyList);
                while (lex.at(
                    OrgTokSet{otk::ColonIdent, otk::ColonAddIdent})) {
                    start(
                        lex.at(otk::ColonIdent) ? org::Property
                                                : org::PropertyAdd);

                    token(
                        org::RawText,
                        lex.pop(OrgTokSet{
                            otk::ColonIdent, otk::ColonAddIdent}));

                    if (lex.at(otk::Ident)) {
                        token(org::Ident, lex.pop(otk::Ident));
                    }

                    token(org::RawText, lex.pop(otk::RawProperty));
                    end();
                }
                lex.skip(otk::ColonEnd);
                end();
                break;
            }
            case otk::ColonLogbook: {
                parseLogbook(lex);
                break;
            }
            case otk::ColonDescription: {
                lex.skip(otk::ColonDescription);
                start(org::SubtreeDescription);
                parseParagraph(lex, false);
                lex.skip(otk::ColonEnd);
                end();
                break;
            }
        }
    }
    return end();
}

OrgId OrgParser::parseSubtree(OrgLexer& lex) {
    start(org::Subtree);
    // prefix
    { token(org::RawText, lex.pop(otk::SubtreeStars)); };
    // todo_status
    {
        if (lex.at(otk::SubtreeTodoState)) {
            token(org::BigIdent, lex.pop(otk::SubtreeTodoState));
        } else {
            empty();
        };
    }
    // urgency
    { empty(); }
    // subtree_title
    { parseParagraph(lex, false); }
    // subtree_completion
    { empty(); }
    // tree_tags
    {
        if (lex.at(otk::SubtreeTag)) {
            start(org::InlineStmtList);
            while (lex.at(otk::SubtreeTag)) {
                token(org::OrgTag, lex.pop(otk::SubtreeTag));
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
                token(org::BigIdent, lex.pop(otk::SubtreeTime));
            } else {
                empty();
            }
            token(org::TimeStamp, lex.pop(otk::BracketTime));
            end();
        }

        end();
    };
    // tree_drawer
    { parseDrawer(lex); };
    lex.skip(otk::SubtreeEnd);
    return end();
}

void OrgParser::skipLineCommand(OrgLexer& lex) {
    lex.skip(otk::CommandPrefix);
    lex.skip(otk::LineCommand);
    lex.skip(otk::Colon);
}

OrgId OrgParser::parseOrgFile(OrgLexer& lex) {
    start(org::File);
    if (lex.at(otk::QuoteOpen)) {
        lex.next();
        token(org::RawText, lex.pop(otk::RawText));
        lex.skip(otk::QuoteClose);
    } else {
        token(org::RawText, lex.pop(otk::RawText));
    }
    return end();
}

OrgId OrgParser::parseLineCommand(OrgLexer& lex) {
    const auto kind           = classifyCommand(lex.strVal(+1));
    auto       skipLineComand = [](OrgLexer& lex) {
        lex.skip(otk::CommandPrefix);
        lex.skip(otk::LineCommand);
        lex.skip(otk::Colon);
    };

    switch (kind) {
        case ock::Include: {
            skipLineCommand(lex);
            lex.skip(otk::CommandArgumentsBegin);
            start(org::CommandInclude);
            parseOrgFile(lex);

            if (lex.at(otk::CommandValue)) {
                token(org::Ident, lex.pop(otk::CommandValue));
            } else {
                empty();
            }

            if (lex.at(otk::CommandValue)) {
                token(org::Ident, lex.pop(otk::CommandValue));
            } else {
                empty();
            }

            parseSrcArguments(lex);
            lex.skip(otk::CommandArgumentsEnd);
            break;
        }
        case ock::AttrHtml: {
            skipLineCommand(lex);
            lex.skip(otk::CommandArgumentsBegin);
            start(org::CommandAttrHtml);
            parseSrcArguments(lex);
            end();
            lex.skip(otk::CommandArgumentsEnd);
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
            token(org::RawText, lex.pop());
            end();
            break;
        }

        case ock::Filetags: {
            skipLineCommand(lex);
            start(org::Filetags);
            token(org::OrgTag, lex.pop(otk::SubtreeTag));
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
            token(org::Ident, lex.pop());
            end();
        }

        case ock::Property: {
            skipLineCommand(lex);
            start(org::Property);
            token(org::RawText, lex.pop(otk::Ident));
            empty();
            token(org::RawText, lex.pop(otk::RawProperty));
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
    switch (lex.kind()) {
        case otk::ParagraphStart: return parseParagraph(lex, true);
        case otk::TableBegin: return parseTable(lex);
        case otk::SubtreeStars: return parseSubtree(lex);
        case otk::ListStart: return parseList(lex);
        case otk::TextSeparator: {
            return token(org::TextSeparator, lex.pop());
        }
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
            assert(false && "TODO");
        }
    }
}

OrgId OrgParser::parseTop(OrgLexer& lex) {
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
