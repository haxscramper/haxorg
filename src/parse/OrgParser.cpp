#include "OrgParser.hpp"


OrgId OrgParser::parseCSVArguments(OrgLexer& lex) {
    start(orgIdent);
    lex.skip(OTkIdent);

    if (lex.at(OTkParOpen)) {
        lex.skip(OTkParOpen);
        while (lex.at(OTkRawText)) {
            token(orgRawText, lex.pop(OTkRawText));
            if (lex.at(OTkComma)) {
                lex.next();
            }
        }
        lex.skip(OTkParClose);
    }
    return end();
}

OrgId OrgParser::parseMacro(OrgLexer& lex) {
    start(orgMacro);
    lex.skip(OTkMacroOpen);
    parseCSVArguments(lex);
    lex.skip(OTkMacroClose);
    return end();
}

OrgId OrgParser::parseRawUrl(OrgLexer& lex) {
    token(orgRawLink, lex.pop(OTkRawUrl));
}

OrgId OrgParser::parseText(OrgLexer& lex) { assert(false && "TODO"); }

OrgId OrgParser::parseLink(OrgLexer& lex) {
    start(orgLink);
    lex.skip(OTkLinkOpen);
    lex.skip(OTkLinkTargetOpen);
    if (lex.at(OTkLinkInternal)) {
        empty();
        token(orgRawText, lex.pop(OTkLinkInternal));
    } else if (lex.at(OTkLinkFull)) {
        empty();
        token(orgRawText, lex.pop(OTkLinkFull));
    } else {
        token(orgIdent, lex.pop(OTkLinkProtocol));
        token(orgRawText, lex.pop(OTkLinkTarget));
    }
    lex.skip(OTkLinkTargetClose);
    if (lex.at(OTkLinkDescriptionOpen)) {
        auto sub = splinter(
            lex,
            lex.getInside(
                {OTkLinkDescriptionOpen}, {OTkLinkDescriptionClose}));
        start(orgParagraph);
        parseText(sub);
        end();

    } else {
        empty();
    }
    lex.skip(OTkLinkClose);
    return end();
}

OrgId OrgParser::parseInlineMath(OrgLexer& lex) {
    const auto startKind = lex.tok().kind;
    const auto regular   = OrgTokSet{OTkDollarOpen, OTkLatexParOpen};
    const auto display = OrgTokSet{OTkDoubleDollarOpen, OTkLatexBraceOpen};

    lex.skip(regular + display);
    start(regular.contains(startKind) ? orgInlineMath : orgDisplayMath);

    OrgTokenKind close;
    switch (startKind) {
        case OTkDollarOpen: {
            lex.skip(OTkDollarClose);
            break;
        }
        case OTkDoubleDollarOpen: {
            lex.skip(OTkDoubleDollarClose);
            break;
        }
        case OTkLatexParOpen: {
            lex.skip(OTkLatexParClose);
            break;
        }
        case OTkLatexBraceOpen: {
            lex.skip(OTkLatexBraceClose);
            break;
        }
        default: {
            assert(false);
        }
    }

    return end();
}

OrgId OrgParser::parseSymbol(OrgLexer& lex) {
    lex.skip(OTkSymbolStart);
    start(orgSymbol);
    token(orgIdent, lex.pop(OTkIdent));

    if (lex.at(OTkMetaBraceOpen)) {
        assert(false);
    } else {
        empty();
    }

    while (lex.at(OTkMetaArgsOpen)) {
        lex.skip(OTkMetaArgsOpen);
        lex.skip(OTkMetaArgsBody);
        lex.skip(OTkMetaArgsClose);
    }

    return end();
}

OrgId OrgParser::parseHashTag(OrgLexer& lex) {
    start(orgHashTag);
    token(orgRawText, lex.pop(OTkHashTag));

    if (lex.at(OTkHashTagSub)) {
        lex.skip(OTkHashTagSub);
        if (lex.at(OTkHashTag)) {
            parseHashTag(lex);

        } else {
            lex.skip(OTkHashTagOpen);
            while (!lex.finished() && !lex.at(OTkHashTagClose)) {
                parseHashTag(lex);
                if (lex.at(OTkComma)) {
                    lex.next();
                };
            }
            lex.skip(OTkHashTagClose);
        };
    };
    return end();
}

OrgId OrgParser::parseTime(OrgLexer& lex) {
    const OrgTokSet times{OTkBracketTime, OTkAngleTime};
    if (lex.ahead(times, OrgTokSet{OTkTimeDash})) {
        start(orgTimeRange);
        token(orgTimeStamp, lex.pop(times));
        lex.skip(OTkTimeDash);
        token(orgTimeStamp, lex.pop(times));
        if (lex.at(OTkTimeArrow)) {
            lex.skip(OTkTimeArrow);
            token(orgSimpleTime, lex.pop(OTkTimeDuration));
        }
        return end();
    } else {
        return token(orgTimeStamp, lex.pop(times));
    }
}

void OrgParser::parseIdent(OrgLexer& lex) {}

OrgId OrgParser::parseSrcInline(OrgLexer& lex) {
    start(orgSrcInlineCode);
    {
        parseIdent(lex);
        token(orgIdent, lex.pop(OTkSrcName));
        start(orgCodeLine);
        token(orgCodeText, lex.pop(OTkSrcBody));
    }
    end();
    lex.skip(OTkSrcClose);
    return end();
}

OrgId OrgParser::parseTable(OrgLexer& lex) {
    start(orgTable);
    lex.skip(OTkTableBegin);
    lex.skip(OTkCmdArguments);
    empty();

    ParseCb parseContent = [this](OrgLexer& lex) {
        auto sub = splinter(
            lex, lex.getInside({OTkContentStart}, {OTkContentEnd}));
        return parseTop(sub);
    };

    while (!lex.at(OTkTableEnd)) {
        switch (lex.kind()) {
            case OTkPipeOpen: {
                start(orgTableRow);
                empty();
                empty();

                lex.skip(OTkPipeOpen);
                start(orgTableCell);
                {
                    empty();
                    parseContent(lex);
                }
                end();

                while (lex.at(OTkPipeSeparator)) {
                    lex.skip(OTkPipeSeparator);
                    start(orgTableCell);
                    {
                        empty();
                        parseContent(lex);
                    }
                    end();
                }

                lex.skip(OTkPipeClose);
                end();
                break;
            }
            case OTkPipeCellOpen: {
                start(orgTableRow);
                empty();
                empty();

                lex.skip(OTkPipeCellOpen);
                start(orgTableCell);
                {

                    empty();
                    parseContent(lex);
                }
                end();

                while (lex.at(OTkPipeCellOpen)) {
                    lex.skip(OTkPipeCellOpen);
                    start(orgTableCell);
                    {
                        empty();
                        parseContent(lex);
                    }
                    end();
                }

                end();
                break;
            }
            case OTkRowSpec: {
                start(orgTableRow);
                empty();
                lex.skip(OTkRowSpec);
                lex.skip(OTkCmdArguments);
                empty();
                start(orgTableCell);
                {
                    empty();
                    parseContent(lex);
                }
                end();
                while (lex.at(OTkCellSpec)) {
                    lex.skip(OTkCellSpec);
                    lex.skip(OTkCmdArguments);
                    start(orgTableCell);
                    {
                        empty();
                        parseContent(lex);
                    }
                    end();
                }

                end();
                break;
            }
            case OTkTableEnd: {
                break;
            }
            default: {
                assert(false);
            }
        };
    };
    lex.skip(OTkTableEnd);
    return end();
}

OrgId OrgParser::parseParagraph(OrgLexer& lex, bool onToplevel) {
    assert(false && "TODO");
}

OrgId OrgParser::parseCommandArguments(OrgLexer& lex) {
    start(orgInlineStmtList);
    while (lex.at(OrgTokSet{OTkCommandValue, OTkCommandKey})) {
        if (lex.at(OTkCommandKey)) {
            start(orgCmdValue);
            {
                token(orgIdent, lex.pop(OTkCommandKey));
                token(orgRawText, lex.pop(OTkCommandValue));
            }
            end();
        } else {
            start(orgCmdValue);
            {
                empty();
                token(orgRawText, lex.pop(OTkCommandValue));
            }
            end();
        }
    }

    return end();
}

OrgId OrgParser::parseSrcArguments(OrgLexer& lex) {
    start(orgCmdArguments);
    start(orgInlineStmtList);

    while (lex.at(OTkCommandFlag)) {
        token(orgCmdFlag, lex.pop());
    }
    end();
    parseCommandArguments(lex);
    return end();
}

OrgId OrgParser::parseTextWrapCommand(OrgLexer& lex, OrgCommandKind kind) {
    switch (kind) {
        case ockBeginCenter: {
            start(orgCenterBlock);
            break;
        }
        case ockBeginQuote: {
            start(orgQuoteBlock);
            break;
        }
        case ockBeginAdmonition: {
            start(orgAdmonitionBlock);
            break;
        }
        default: {
            assert(false);
        }
    }
    lex.skip(OTkCommandPrefix);
    lex.skip(OTkCommandBegin);
    lex.skip(OTkCommandArgumentsBegin);
    if (lex.at(OTkRawText)) {
        lex.next();
    } else if (lex.at(OTkIdent)) {
        lex.next();
    };
    lex.skip(OTkCommandArgumentsEnd);
    lex.skip(OTkCommandContentStart);
    parseParagraph(lex, true);
    lex.skip(OTkCommandContentEnd);
    lex.skip(OTkCommandPrefix);
    lex.skip(OTkCommandEnd);
    return end();
}

OrgId OrgParser::parseSrc(OrgLexer& lex) {
    start(orgSrcCode);
    lex.skip(OTkCommandPrefix);
    lex.skip(OTkCommandBegin);
    // header_args_lang
    {
        lex.skip(OTkCommandArgumentsBegin);

        const auto lang = lex.pop(OTkWord);
        if (lex.strVal().empty()) {
            empty();
        } else {
            token(orgIdent, lang);
        }

        parseSrcArguments(lex);
        lex.skip(OTkCommandArgumentsEnd);
    };
    // body
    {

        start(orgStmtList);
        lex.skip(OTkCommandContentStart);
        lex.skip(OTkCodeContentBegin);
        while (
            !lex.at(OrgTokSet{OTkCommandContentEnd, OTkCodeContentEnd})) {
            start(orgCodeLine);
            while (!lex.at(OrgTokSet{
                OTkCommandContentEnd, OTkNewline, OTkCodeContentEnd})) {
                switch (lex.kind()) {
                    case OTkCodeText: {
                        token(orgCodeText, lex.pop(OTkCodeText));
                        break;
                    }
                    case OTkParOpen: {
                        lex.skip(OTkParOpen);
                        lex.skip(OTkIdent);
                        lex.skip(OTkColon);
                        start(orgCodeCallout);
                        token(orgIdent, lex.pop(OTkIdent));
                        end();
                        lex.skip(OTkParClose);
                        break;
                    }
                    case OTkCodeContentEnd: {
                        break;
                        break;
                    }
                    case OTkDoubleAngleOpen: {
                        lex.skip(OTkDoubleAngleOpen);
                        start(orgCodeTangle);
                        parseCSVArguments(lex);
                        end();
                        lex.skip(OTkDoubleAngleClose);
                        break;
                    }
                    default: {
                        assert(false);
                    }
                }
            }
            if (lex.at(OTkNewline)) {
                lex.next();
            }
            end(); // finish code line
        }

        lex.skip(OTkCodeContentEnd);
        lex.skip(OTkCommandContentEnd);
        end(); // finish statement
    };
    // eval_result
    { empty(); };
    lex.skip(OTkCommandPrefix);
    lex.skip(OTkCommandEnd);
    return end();
}

OrgId OrgParser::parseListItemBody(OrgLexer& lex) {
    start(orgStmtList);
    while ((!(lex.at(OTkStmtListClose)))) {
        if (lex.at(OTkIndent, OTkListDash)) {
            lex.next();
            parseNestedList(lex);
            lex.skip(OTkDedent);
        } else {
            parseToplevelItem(lex);
        }
    }
    return end();
}

OrgId OrgParser::parseListItem(OrgLexer& lex) {
    start(orgListItem);
    // prefix
    { token(orgRawText, lex.pop(OTkListDash)); }
    // counter
    {
        empty(); // TODO parse counter
    }
    // checkbox
    {
        if (lex.at(OTkCheckbox)) {
            token(orgCheckbox, lex.pop());
        } else {
            empty();
        }
    }
    // tag
    bool isAnnotatedParagraph = false;
    {
        if (lex.at(OTkListDescOpen)) {
            isAnnotatedParagraph = true;
            lex.skip(OTkListDescOpen);
            start(orgAnnotatedParagraph);
            start(orgListTag);
            parseParagraph(lex, false);
            end();
            lex.skip(OTkListDescClose);
            lex.skip(OTkDoubleColon);
            end();
        } else {
            empty();
        }
    }
    // completion
    {
        assert(false && "TODO"); //
    }
    lex.skip(OTkListItemEnd);
    return end();
}

OrgId OrgParser::parseNestedList(OrgLexer& lex) {
    ParseCb nextLevel = [this](OrgLexer& lex) {
        lex.skip(OTkIndent);
        auto result = parseNestedList(lex);
        lex.skip(OTkDedent);
        return result;
    };

    start(orgList);
    while (lex.at(OTkListDash)) {
        parseListItem(lex);
        if (lex.at(OTkSameIndent)) {
            lex.next();
        } else if (lex.at(OTkDedent)) {
            return end();
        } else if (lex.at(OTkIndent)) {
            nextLevel(lex);
        } else if (lex.at(OTkListEnd)) {
            return end();
        } else {
            assert(false);
        }
    }
    return end();
}

OrgId OrgParser::parseList(OrgLexer& lex) {

    lex.skip(OTkListStart);
    const auto nested = lex.at(OTkIndent);
    if (nested) {
        lex.skip(OTkIndent);
    }
    auto result = parseNestedList(lex);
    if (nested) {
        lex.skip(OTkDedent);
    }
    lex.skip(OTkListEnd);
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
    start(orgLogbookClock);
    // CLOCK:
    lex.skip(OTkListClock);
    lex.skip(OTkParagraphStart);
    lex.trySkip(OTkSpace);
    lex.skip(OTkBigIdent);
    lex.skip(OTkColon);
    lex.trySkip(OTkSpace);

    parseTime(lex);

    lex.trySkip(OTkSpace);
    lex.skip(OTkParagraphEnd);
    lex.skip(OTkListItemEnd);
    return end();
}

OrgId OrgParser::parseLogbookListEntry(OrgLexer& lex) {
    lex.skip(OTkListDash);
    const auto pos = lex.find(
        OrgTokSet{OTkDoubleSlash}, OrgTokSet{OTkListItemEnd});

    const auto head = lex.pop(
        pos == -1 ? lex.find(OTkListItemEnd) - 1 : pos);
    // head_parser
    {
        auto sub = splinter(lex, head);
        sub.skip(OTkStmtListOpen);
        sub.skip(OTkParagraphStart);
        if (sub.at(OTkWord) && sub.strVal() == "State") {
            start(orgLogbookStateChange);
            sub.skip(OTkWord);
            sub.trySkip(OTkSpace);
            sub.skip(OTkQuoteOpen);
            token(orgBigIdent, sub.pop(OTkBigIdent));
            sub.skip(OTkQuoteClose);
            sub.trySkip(OTkSpace);
            if (sub.at(OTkQuoteOpen)) {
                sub.skip(OTkQuoteOpen);
                token(orgBigIdent, sub.pop(OTkBigIdent));
                sub.skip(OTkQuoteClose);
                sub.trySkip(OTkSpace);
            };
            parseTime(lex);
            end();
        } else if (lex.at(OTkWord) && lex.strVal() == "Refiled") {
            start(orgLogbookRefile);
            lex.skip(OTkWord, "Refiled");
            lex.trySkip(OTkSpace);
            lex.skip(OTkWord, "on");
            lex.trySkip(OTkSpace);
            parseTime(lex);
            lex.trySkip(OTkSpace);
            lex.skip(OTkWord, "from");
            lex.trySkip(OTkSpace);
            parseLink(lex);
            end();
        } else if (lex.at(OTkWord) && lex.strVal() == "Note") {
            start(orgLogbookNote);
            lex.skip(OTkWord, "Note");
            lex.trySkip(OTkSpace);
            lex.skip(OTkWord, "taken");
            lex.trySkip(OTkSpace);
            lex.skip(OTkWord, "on");
            lex.trySkip(OTkSpace);
            parseTime(lex);
            lex.trySkip(OTkSpace);
            if (lex.at(OTkDoubleSlash)) {
                lex.skip(OTkDoubleSlash);
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
            lex.skip(OTkListItemEnd);
        } else {
            Vec<OrgTokenId> tokens;
            tokens.push_back(lex.in->add(OrgToken(OTkParagraphStart)));
            tokens.append(lex.pop(lex.find(OTkListItemEnd)));

            tokens = strip(
                lex,
                tokens,
                {OTkNewline, OTkSpace},
                {OTkNewline, OTkSpace},
                {OTkStmtListOpen, OTkParagraphStart},
                {OTkStmtListClose, OTkParagraphEnd, OTkListItemEnd});

            auto sub = splinter(lex, tokens);
            parseListItemBody(sub);
        }
    }
    return end();
}

void OrgParser::parseLogbook(OrgLexer& lex) {
    start(orgLogbook);
    lex.skip(OTkColonLogbook);
    lex.skip(OTkLogbookStart);
    lex.skip(OTkListStart);

    const auto indented = lex.at(OTkIndent);
    if (indented) {
        lex.skip(OTkIndent);
    }
    while (!lex.at(indented ? OTkDedent : OTkListEnd)) {
        switch (lex.tok().kind) {
            case OTkListDash: {
                parseLogbookListEntry(lex);
                break;
            }
            case OTkListClock: {
                parseLogbookClockEntry(lex);
                break;
            }
            case OTkSameIndent: {
                lex.skip(OTkSameIndent);
                break;
            }
            default: {
                assert(false);
            }
        }
    }

    if (indented) {
        lex.skip(OTkDedent);
    }

    lex.skip(OTkListEnd);
    lex.skip(OTkLogbookEnd);
    lex.skip(OTkColonEnd);
}

OrgId OrgParser::parseDrawer(OrgLexer& lex) {
    start(orgDrawer);
    while (lex.at(OrgTokSet{
        OTkColonProperties, OTkColonLogbook, OTkColonDescription})) {
        switch (lex.tok().kind) {
            case OTkColonProperties: {
                lex.skip(OTkColonProperties);
                start(orgPropertyList);
                while (
                    lex.at(OrgTokSet{OTkColonIdent, OTkColonAddIdent})) {
                    start(
                        lex.at(OTkColonIdent) ? orgProperty
                                              : orgPropertyAdd);

                    token(
                        orgRawText,
                        lex.pop(
                            OrgTokSet{OTkColonIdent, OTkColonAddIdent}));

                    if (lex.at(OTkIdent)) {
                        token(orgIdent, lex.pop(OTkIdent));
                    }

                    token(orgRawText, lex.pop(OTkRawProperty));
                    end();
                }
                lex.skip(OTkColonEnd);
                end();
                break;
            }
            case OTkColonLogbook: {
                parseLogbook(lex);
                break;
            }
            case OTkColonDescription: {
                lex.skip(OTkColonDescription);
                start(orgSubtreeDescription);
                parseParagraph(lex, false);
                lex.skip(OTkColonEnd);
                end();
                break;
            }
        }
    }
    return end();
}

OrgId OrgParser::parseSubtree(OrgLexer& lex) {
    start(orgSubtree);
    // prefix
    { token(orgRawText, lex.pop(OTkSubtreeStars)); };
    // todo_status
    {
        if (lex.at(OTkSubtreeTodoState)) {
            token(orgBigIdent, lex.pop(OTkSubtreeTodoState));
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
        if (lex.at(OTkSubtreeTag)) {
            start(orgInlineStmtList);
            while (lex.at(OTkSubtreeTag)) {
                token(orgOrgTag, lex.pop(OTkSubtreeTag));
            }
            end();
        } else {
            empty();
        }
    }
    // subtree_time
    {

        start(orgStmtList);
        while (lex.at(OTkSubtreeTime) || lex.at(OTkBracketTime)) {
            start(orgTimeAssoc);
            if (lex.at(OTkSubtreeTime)) {
                token(orgBigIdent, lex.pop(OTkSubtreeTime));
            } else {
                empty();
            }
            token(orgTimeStamp, lex.pop(OTkBracketTime));
            end();
        }

        end();
    };
    // tree_drawer
    { parseDrawer(lex); };
    lex.skip(OTkSubtreeEnd);
    return end();
}

void OrgParser::skipLineCommand(OrgLexer& lex) {
    lex.skip(OTkCommandPrefix);
    lex.skip(OTkLineCommand);
    lex.skip(OTkColon);
}

OrgId OrgParser::parseOrgFile(OrgLexer& lex) {
    start(orgFile);
    if (lex.at(OTkQuoteOpen)) {
        lex.next();
        token(orgRawText, lex.pop(OTkRawText));
        lex.skip(OTkQuoteClose);
    } else {
        token(orgRawText, lex.pop(OTkRawText));
    }
    return end();
}

OrgId OrgParser::parseLineCommand(OrgLexer& lex) {
    const auto kind           = classifyCommand(lex.strVal(+1));
    auto       skipLineComand = [](OrgLexer& lex) {
        lex.skip(OTkCommandPrefix);
        lex.skip(OTkLineCommand);
        lex.skip(OTkColon);
    };

    switch (kind) {
        case ockInclude: {
            skipLineCommand(lex);
            lex.skip(OTkCommandArgumentsBegin);
            start(orgCommandInclude);
            parseOrgFile(lex);

            if (lex.at(OTkCommandValue)) {
                token(orgIdent, lex.pop(OTkCommandValue));
            } else {
                empty();
            }

            if (lex.at(OTkCommandValue)) {
                token(orgIdent, lex.pop(OTkCommandValue));
            } else {
                empty();
            }

            parseSrcArguments(lex);
            lex.skip(OTkCommandArgumentsEnd);
            break;
        }
        case ockAttrHtml: {
            skipLineCommand(lex);
            lex.skip(OTkCommandArgumentsBegin);
            start(orgCommandAttrHtml);
            parseSrcArguments(lex);
            end();
            lex.skip(OTkCommandArgumentsEnd);
            break;
        }
        case ockTitle: {
            skipLineCommand(lex);
            start(orgCommandTitle);
            parseParagraph(lex, false);
            end();
            break;
        }
        case ockCaption: {
            skipLineCommand(lex);
            start(orgCommandCaption);
            parseParagraph(lex, false);
            end();
            break;
        }

        case ockCreator:
        case ockOptions:
        case ockColumns:
        case ockAuthor:
        case ockLatexHeader:
        case ockLanguage: {
            OrgNodeKind newk;
            switch (kind) {
                case ockCreator: newk = orgCommandCreator; break;
                case ockLanguage: newk = orgCommandLanguage; break;
                case ockAuthor: newk = orgCommandAuthor; break;
                case ockOptions: newk = orgCommandOptions; break;
                case ockLatexHeader: newk = orgLatexHeader; break;
                case ockColumns: newk = orgColumns; break;
                default: orgEmpty;
            }
            skipLineCommand(lex);
            start(newk);
            token(orgRawText, lex.pop());
            end();
            break;
        }
        case ockFiletags: {
            skipLineCommand(lex);
            start(orgFiletags);
            token(orgOrgTag, lex.pop(OTkSubtreeTag));
            end();
            break;
        }
        case ockLatexClass:
        case ockLatexCompiler: {
            OrgNodeKind newk = orgEmpty;
            switch (kind) {
                case ockLatexCompiler: newk = orgLatexCompiler; break;
                case ockLatexClass: newk = orgLatexClass; break;
            }
            skipLineCommand(lex);
            start(newk);
            token(orgIdent, lex.pop());
            end();
        }

        case ockProperty: {
            skipLineCommand(lex);
            start(orgProperty);
            token(orgRawText, lex.pop(OTkIdent));
            empty();
            token(orgRawText, lex.pop(OTkRawProperty));
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
        case OTkParagraphStart: return parseParagraph(lex, true);
        case OTkTableBegin: return parseTable(lex);
        case OTkSubtreeStars: return parseSubtree(lex);
        case OTkListStart: return parseList(lex);
        case OTkTextSeparator: {
            return token(orgTextSeparator, lex.pop());
        }
        case OTkCommandPrefix: {
            const auto kind = classifyCommand(lex.strVal(1));
            switch (kind) {
                case ockBeginSrc: return parseSrc(lex);
                case ockBeginQuote:
                case ockBeginCenter:
                case ockBeginAdmonition: {
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
    start(orgStmtList);
    while (lex.hasNext()) {
        if (lex.at(OTkComment)) {
            lex.next();
        } else {
            parseToplevelItem(lex);
        };
    }
    return end();
}
