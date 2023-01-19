#include <parse/OrgTypes.hpp>

struct OrgParser {
    OrgNodeGroup* group;

    void  start(OrgNodeKind kind) { (void)group->startTree(kind); }
    OrgId end() { return group->endTree(); }
    OrgId token(OrgTokenKind kind, Lexer& lex) {
        return group->token(lex.get());
    }

    void parseParagraph(
        Lexer&           lex,
        const ParseConf& parseConf,
        const bool&      onToplevel);

    void parseTop(Lexer& lex);

    OrgId parseCSVArguments(Lexer& lex) {
        result.add(newTree(orgIdent, lex.pop(OTkIdent)));
        if (lex.at(OTkParOpen)) {
            lex.skip(OTkParOpen);
            while (lex.at(OTkRawText)) {
                result.add(newTree(orgRawText, lex.pop(OTkRawText)));
                if (lex.at(OTkComma)) {
                    lex.next();
                }
            }
            lex.skip(OTkParClose);
        }
    }

    OrgNode parseMacro(Lexer& lex) {
        OrgNode result;
        lex.skip(OTkMacroOpen);
        result = newTree(orgMacro, parseCSVArguments(lex, parseConf));
        ;
        lex.skip(OTkMacroClose);
        return result;
    };

    OrgNode parseRawUrl(Lexer& lex) {
        OrgNode result;
        result = newTree(orgRawLink, lex.pop(OTkRawUrl));
        ;
        return result;
    };

    OrgNode parseLink(Lexer& lex) {
        OrgNode result;
        result = newTree(orgLink);
        ;
        lex.skip(OTkLinkOpen);
        lex.skip(OTkLinkTargetOpen);
        if (lex[OTkLinkInternal]) {
            result.add(newEmptyNode());
            result.add(newTree(orgRawText, lex.pop(OTkLinkInternal)));
        } else if (lex[OTkLinkFull]) {
            result.add(newEmptyNode());
            result.add(newTree(orgRawText, lex.pop(OTkLinkFull)));
        } else {
            result.add(newTree(orgIdent, lex.pop(OTkLinkProtocol)));
            result.add(newTree(orgRawText, lex.pop(OTkLinkTarget)));
        };
        lex.skip(OTkLinkTargetClose);
        if ((((*(lex))) == (OTkLinkDescriptionOpen))) {

            auto sub = lex.getInside(
                {OTkLinkDescriptionOpen}, {OTkLinkDescriptionClose});
            ;
            ;
            result.add(newTree(orgParagraph, sub.parseText(parseConf)));
        } else {
            result.add(newEmptyNode());
        };
        lex.skip(OTkLinkClose);
        return result;
    };

    OrgNode parseInlineMath(Lexer& lex) {
        OrgNode result;
        /*!Parse inline math expression, starting with any of `$`, `$$`,
        `\(`, and `\[`.
        */

        const auto start = (*(lex));
        lex.skip(((regular) + (display)));

        const auto close = switch (start) {
            case OTkDollarOpen: {
                OTkDollarClose;
                break;
            }
            case OTkDoubleDollarOpen: {
                OTkDoubleDollarClose;
                break;
            }
            case OTkLatexParOpen: {
                OTkLatexParClose;
                break;
            }
            case OTkLatexBraceOpen: {
                OTkLatexBraceClose;
                break;
            }
            default: {
                throw newUnexpectedKindError((*(lex)));
            }
        }

        result = newTree(
            tern(((start)in(regular)), orgInlineMath, orgDisplayMath),
            newTree(orgRawText, lex.pop(OTkLatexInlineRaw)));
        lex.skip(close);
        return result;
    }

    OrgNode parseSymbol(Lexer& lex) {
        OrgNode result;
        lex.skip(OTkSymbolStart);
        result = newTree(orgSymbol, newTree(orgIdent, lex.pop(OTkIdent)));
        ;
        if (lex[OTkMetaBraceOpen]) {
            assert(false);
        } else {
            result.add(newEmptyNode());
        };
        while (lex[OTkMetaArgsOpen]) {
            lex.skip(OTkMetaArgsOpen);
            lex.skip(OTkMetaArgsBody);
            lex.skip(OTkMetaArgsClose);
        };
        return result;
    };

    OrgNode parseHashtag(Lexer& lex) {
        OrgNode result;
        result = newTree(
            orgHashTag, newTree(orgRawText, lex.pop(OTkHashTag)));
        ;
        if (lex[OTkHashTagSub]) {
            lex.skip(OTkHashTagSub);
            if (lex[OTkHashTag]) {
                result.add(lex.parseHashTag(parseConf));
            } else {
                lex.skip(OTkHashTagOpen);
                while (((notEmpty(lex)) && ((!(lex[OTkHashTagClose]))))) {
                    result.add(lex.parseHashTag(parseConf));
                    if (lex[OTkComma]) {
                        lex.next();
                    };
                };
                lex.skip(OTkHashTagClose);
            };
        };
        return result;
    };

    OrgNode parseTime(Lexer& lex) {
        OrgNode result;
        result = newTree(
            orgTimeStamp, lex.pop({OTkBracketTime, OTkAngleTime}));
        ;
        if (lex[OTkTimeDash]) {
            lex.skip(OTkTimeDash);
            result = newTree(
                orgTimeRange,
                result,
                newTree(
                    orgTimeStamp,
                    lex.pop({OTkBracketTime, OTkAngleTime})));
            ;
            if (lex[OTkTimeArrow]) {
                lex.skip(OTkTimeArrow);
                result[R"(diff)"] = newTree(
                    orgSimpleTime, lex.pop(OTkTimeDuration));
                ;
            };
        };
        return result;
    };


    void parseIdent(Lexer& lex) {}

    void parseSrcInline(Lexer& lex) {
        start(orgSrcInlineCode);
        parseIdent(lex);
        result[R"(lang)"] = newTree(orgIdent, lex.pop(OTkSrcName));
        result[R"(body)"] = newTree(
            orgCodeLine, newTree(orgCodeText, lex.pop(OTkSrcBody)));
        lex.skip(OTkSrcClose);
        end();
        return result;
    };

    OrgNode parseTable(Lexer& lex) {
        OrgNode result;
        result = newTree(orgTable);
        ;
        lex.skip(OTkTableBegin);
        lex.skip(OTkCmdArguments);
        result.add(newEmptyNode());

        OrgNode parseContent(Lexer & lex) {
            OrgNode result;

            auto sub = lex.getInside({OTkContentStart}, {OTkContentEnd});
            ;
            ;
            result = parseTop(sub, parseConf);
            ;
            return result;
        };
        while ((((*(lex))) != (OTkTableEnd))) {
            switch ((*(lex))) {
                case OTkPipeOpen: {

                    auto row = newTree(
                        orgTableRow, newEmptyNode(), newEmptyNode());
                    ;
                    ;
                    lex.skip(OTkPipeOpen);
                    row.add(newTree(
                        orgTableCell, newEmptyNode(), parseContent(lex)));
                    while ((((*(lex))) == (OTkPipeSeparator))) {
                        lex.skip(OTkPipeSeparator);
                        row.add(newTree(
                            orgTableCell,
                            newEmptyNode(),
                            parseContent(lex)));
                    };
                    lex.skip(OTkPipeClose);
                    result.add(row);
                    break;
                }
                case OTkPipeCellOpen: {
                    auto row = newTree(
                        orgTableRow, newEmptyNode(), newEmptyNode());
                    lex.skip(OTkPipeCellOpen);
                    row.add(newTree(
                        orgTableCell, newEmptyNode(), parseContent(lex)));
                    while ((((*(lex))) == (OTkPipeCellOpen))) {
                        lex.skip(OTkPipeCellOpen);
                        row.add(newTree(
                            orgTableCell,
                            newEmptyNode(),
                            parseContent(lex)));
                    };
                    result.add(row);
                    break;
                }
                case OTkRowSpec: {
                    auto row = newTree(orgTableRow, newEmptyNode());
                    lex.skip(OTkRowSpec);
                    lex.skip(OTkCmdArguments);
                    row.add(newEmptyNode());
                    row.add(newTree(
                        orgTableCell, newEmptyNode(), parseContent(lex)));
                    while ((((*(lex))) == (OTkCellSpec))) {
                        lex.skip(OTkCellSpec);
                        lex.skip(OTkCmdArguments);
                        row.add(newTree(
                            orgTableCell,
                            newEmptyNode(),
                            parseContent(lex)));
                    };
                    result.add(row);
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
        return result;
    };

    OrgNode parseParagraph(
        Lexer&           lex,
        const ParseConf& parseConf,
        const bool&      onToplevel) {
        OrgNode result;

        auto sub = lex.getInside({OTkParagraphStart}, {OTkParagraphEnd});
        ;
        ;

        const auto nodes = parseText(sub, parseConf);
        ;
        ;
        if (((nodes.notEmpty()) && (((nodes[0])of(orgFootnote))))) {
            result = newTree(
                orgAnnotatedParagraph,
                {
                    {R"(prefix)", nodes[0]},
                    {R"(body)",
                     newTree(orgParagraph, nodes[((1)..^ (1))])},
                });
            ;
        } else if (((((nodes.len()) == (1))) && (onToplevel))) {
            switch (nodes[0].kind) {
                case orgLink: {
                    result = nodes[0];
                    ;
                    break;
                }
                default: {
                    result = newTree(orgParagraph, nodes);
                    ;
                }
            };
        } else {
            result = newTree(orgParagraph, nodes);
            ;
        };
        return result;
    };

    OrgNode parseCommandArguments(Lexer& lex) {
        OrgNode result;
        result = newTree(orgInlineStmtList);
        ;
        while (lex[{OTkCommandValue, OTkCommandKey}]) {
            if (lex[OTkCommandKey]) {
                result.add(newTree(
                    orgCmdValue,
                    newTree(orgIdent, lex.pop(OTkCommandKey)),
                    newTree(orgRawtext, lex.pop(OTkCommandValue))));
            } else {
                result.add(newTree(
                    orgCmdValue,
                    newEmptyNode(),
                    newTree(orgRawText, lex.pop(OTkCommandValue))));
            };
        };
        return result;
    };

    OrgNode parseSrcArguments(Lexer& lex) {
        OrgNode result;
        result = newTree(orgCmdArguments);
        ;
        result[R"(flags)"] = newTree(orgInlineStmtList);
        ;
        while (lex[OTkCommandFlag]) {
            result[R"(flags)"].add(newTree(orgCmdFlag, lex.pop()));
        };
        result[R"(args)"] = parseCommandArguments(lex, parseConf);
        ;
        return result;
    };

    OrgNode parseTextWrapCommand(
        Lexer&                lex,
        const ParseConf&      parseConf,
        const OrgCommandKind& kind) {
        OrgNode result;
        switch (kind) {
            case ockBeginCenter: {
                result = newTree(orgCenterBlock);
                break;
            }
            case ockBeginQuote: {
                result = newTree(orgQuoteBlock);
                break;
            }
            case ockBeginAdmonition: {
                result = newTree(orgAdmonitionBlock);
                break;
            }
            default: {
                assert(false);
            }
        };
        lex.skip(OTkCommandPrefix);
        lex.skip(OTkCommandBegin);
        lex.skip(OTkCommandArgumentsBegin);
        if (lex[OTkRawText]) {
            lex.next();
        } else if (lex[OTkIdent]) {
            lex.next();
        };
        lex.skip(OTkCommandArgumentsEnd);
        lex.skip(OTkCommandContentStart);
        result.add(parseParagraph(lex, parseConf, true));
        lex.skip(OTkCommandContentEnd);
        lex.skip(OTkCommandPrefix);
        lex.skip(OTkCommandEnd);
        return result;
    };

    OrgNode parseSrc(Lexer& lex) {
        OrgNode result;
        result = newTree(orgSrcCode);
        ;
        lex.skip(OTkCommandPrefix);
        lex.skip(OTkCommandBegin);
        // header_args_lang
        {
            lex.skip(OTkCommandArgumentsBegin);

            const auto lang = lex.pop(OTkWord);
            ;
            ;
            result[R"(lang)"] = tern(
                lang.strVal().empty(),
                newEmptyNode(),
                newTree(orgIdent, lang));
            ;
            result[R"(header-args)"] = parseSrcArguments(lex, parseConf);
            ;
            lex.skip(OTkCommandArgumentsEnd);
        };
        // body
        {

            auto stmt = newTree(orgStmtList);
            ;
            ;
            lex.skip(OTkCommandContentStart);
            lex.skip(OTkCodeContentBegin);
            while ((!(lex[{OTkCommandContentEnd, OTkCodeContentEnd}]))) {

                auto line = newTree(orgCodeLine);
                ;
                ;
                while ((!(lex[{
                    OTkCommandContentEnd,
                    OTkNewline,
                    OTkCodeContentEnd}]))) {
                    switch ((*(lex))) {
                        case OTkCodeText: {
                            line.add(newTree(
                                orgCodeText, lex.pop(OTkCodeText)));
                            break;
                        }
                        case OTkParOpen: {
                            lex.skip(OTkParOpen);
                            lex.skip(OTkIdent);
                            lex.skip(OTkColon);
                            line.add(newTree(
                                orgCodeCallout,
                                newTree(orgIdent, lex.pop(OTkIdent))));
                            lex.skip(OTkParClose);
                            break;
                        }
                        case OTkCodeContentEnd: {
                            break;
                            ;
                            break;
                        }
                        case OTkDoubleAngleOpen: {
                            lex.skip(OTkDoubleAngleOpen);
                            line.add(newTree(
                                orgCodeTangle,
                                parseCSVArguments(lex, parseConf)));
                            lex.skip(OTkDoubleAngleClose);
                            break;
                        }
                        default: {
                            assert(false);
                        }
                    };
                };
                if (lex[OTkNewline]) {
                    lex.next();
                }
                stmt.add(line);
            };
            lex.skip(OTkCodeContentEnd);
            lex.skip(OTkCommandContentEnd);
            result.add(stmt);
        };
        // eval_result
        { result.add(newEmptyNode()); };
        lex.skip(OTkCommandPrefix);
        lex.skip(OTkCommandEnd);
        return result;
    };

    OrgNode parseNestedList(Lexer& lex) {
        OrgNode result;
        return result;
    };

    OrgNode parseListItemBody(Lexer& lex) {
        OrgNode result;
        /*!Parse *remaining* parts of the list item into a statement list
        node. This procedure does not require a starting stmt list open
        token, and is used for both regular lists and logbook notes.
        */
        ;
        result = newTree(orgStmtList);
        ;
        while ((!(lex[OTkStmtListClose]))) {
            if (lex[OTkIndent, OTkListDash]) {
                lex.next();
                result.add(parseNestedList(lex, parseConf));
                lex.skip(OTkDedent);
            } else {
                result.add(parseToplevelItem(lex, parseConf));
            };
        };
        if (((result.len()) == (0))) {
            result.add(newEmptyNode());
        };
        return result;
    };

    OrgNode parseListItem(Lexer& lex) {
        OrgNode result;
        /*!Recursively (handles nested list in body) parse a single list
        item starting from the list dash token.
        */
        ;
        result = newEmptiedTree(orgListItem);
        ;
        // prefix
        {
            result[R"(bullet)"] = newTree(
                orgRawText, lex.pop(OTkListDash));
            ;
        };
        // counter
        {
            result[R"(counter)"] = newEmptyNode();
            ;
        };
        // checkbox
        {
            if (lex[OTkCheckbox]) {
                result[R"(checkbox)"] = newTree(orgCheckbox, lex.pop());
                ;
            };
        };
        // tag
        {
            if (lex[OTkListDescOpen]) {
                lex.skip(OTkListDescOpen);

                auto header = newEmptiedTree(orgAnnotatedParagraph);
                ;
                ;
                header[R"(prefix)"] = newTree(
                    orgListTag, parseParagraph(lex, parseConf, false));
                ;
                lex.skip(OTkListDescClose);
                lex.skip(OTkDoubleColon);
                result[R"(header)"] = header;
                ;
            };
        };
        // completion
        {
            lex.skip(OTkStmtListOpen);

            const auto body = parseListItemBody(lex, parseConf);
            ;
            ;
            lex.skip(OTkStmtListClose);
            if (((result[R"(header)"])of(orgAnnotatedParagraph))) {
                result[R"(header)"][R"(body)"] = body[0];
                ;
            } else {
                result[R"(header)"] = body[0];
                ;
            };
            if (((1) < (len(body)))) {
                result[R"(body)"] = newTree(
                    orgStmtList, body[((1)..^ (1))]);
                ;
            } else {
                result[R"(body)"] = newTree(orgStmtList);
                ;
            };
        };
        lex.skip(OTkListItemEnd);
        return result;
    };

    OrgNode parseNestedList(Lexer& lex) {
        OrgNode result;
        result = newTree(orgList);
        ;

        OrgNode nextLevel(Lexer & lex) {
            OrgNode result;
            lex.skip(OTkIndent);
            result = parseNestedList(lex, parseConf);
            ;
            lex.skip(OTkDedent);
            return result;
        };
        while (lex[OTkListDash]) {
            result.add(lex.parseListItem(parseConf));
            if (lex[OTkSameIndent]) {
                lex.next();
            } else if (lex[OTkDedent]) {
                return;
                ;
            } else if (lex[OTkIndent]) {
                result[backIdx(1)][R"(body)"].add(
                    nextLevel(lex, parseConf));
            } else if (lex[OTkListEnd]) {
                return;
                ;
            } else {
                assert(false);
            }
        }
        return result;
    };

    OrgNode parseList(Lexer& lex) {
        OrgNode result;
        lex.skip(OTkListStart);
        const auto nested = lex[OTkIndent];
        if (nested) {
            lex.skip(OTkIndent);
        }
        result = parseNestedList(lex, parseConf);
        if (nested) {
            lex.skip(OTkDedent);
        }
        lex.skip(OTkListEnd);
        return result;
    };

    Vec<OrgTokenId> strip(
        const Vec<OrgTokenId>&   tokens,
        const set<OrgTokenKind>& leading,
        const set<OrgTokenKind>& trailing     = leading,
        const set<OrgTokenKind>& skipLeading  = {},
        const set<OrgTokenKind>& skipTrailing = skipLeading) {
        Vec<OrgTokenId> result;
        /*!Strip leading and traling tokens from the list
         */

        auto leftmost  = 0;
        auto rightmost = tokens.high();
        while (leftmost <= rightmost
               && (skipLeading + leading).contains(tokens[leftmost])) {
            ++leftmost;
        }

        while (leftmost <= rightmost
               && (skipTrailing + trailing).contains(tokens[rightmost])) {
            --rightmost;
        }

        for (const auto [idx, token] : tokens) {
            if (idx < leftmost) {
                if ((skipLeading.contains(at(token).kind))) {
                    result.add(token);
                }
            } else if (rightmost < idx) {
                if (skipTrailing.contains(token)) {
                    result.add(token);
                }
            } else {
                result.add(token);
            };
        };
        return result;
    };

    OrgNode parseLogbookClockEntry(
        Lexer&           lex,
        const ParseConf& parseConf) {
        OrgNode result;
        lex.skip(OTkListClock);
        lex.skip(OTkParagraphStart);
        lex.space();
        result = newTree(orgLogbookClock);
        ;
        assert(((lex.pop(OTkBigIdent).strVal()) == (R"(CLOCK)")));
        lex.skip(OTkColon);
        lex.space();
        result.add(parseTime(lex, parseConf));
        lex.space();
        lex.skip(OTkParagraphEnd);
        lex.skip(OTkListItemEnd);
        return result;
    };

    OrgNode parseLogbookListEntry(Lexer& lex) {
        OrgNode result;
        lex.skip(OTkListDash);

        const auto pos = lex.find(OTkDoubleSlash, {OTkListItemEnd});
        ;
        ;

        const auto head = tern(
            ((pos) == (-1)),
            lex.pop(((lex.find(OTkListItemEnd)) - (1))),
            lex.pop(pos));
        ;
        ;
        // head_parser
        {

            auto lex = initLexer(head);
            ;
            ;
            lex.skip(OTkStmtListOpen);
            lex.skip(OTkParagraphStart);
            if (((lex[OTkWord])
                 && (((lex.get().strVal()) == (R"(State)"))))) {
                result = newTree(orgLogbookStateChange);
                ;
                lex.skip(OTkWord);
                lex.space();
                lex.skip(OTkQuoteOpen);
                result[R"(newstate)"] = newTree(
                    orgBigIdent, lex.pop(OTkBigIdent));
                ;
                lex.skip(OTkQuoteClose);
                lex.space();
                assert(((lex.pop(OTkWord).strVal()) == (R"(from)")));
                lex.space();
                if (lex[OTkQuoteOpen]) {
                    lex.skip(OTkQuoteOpen);
                    result[R"(oldstate)"] = newTree(
                        orgBigIdent, lex.pop(OTkBigIdent));
                    ;
                    lex.skip(OTkQuoteClose);
                    lex.space();
                };
                result[R"(time)"] = parseTime(lex, parseConf);
                ;
            } else if (((lex[OTkWord])
                        && (((lex.get().strVal()) == (R"(Refiled)"))))) {
                result = newTree(orgLogbookRefile);
                ;
                doAssert(((lex.pop(OTkWord).strVal()) == (R"(Refiled)")));
                lex.space();
                doAssert(((lex.pop(OTkWord).strVal()) == (R"(on)")));
                lex.space();
                result[R"(time)"] = parseTime(lex, parseConf);
                ;
                lex.space();
                doAssert(((lex.pop(OTkWord).strVal()) == (R"(from)")));
                lex.space();
                result[R"(from)"] = parseLink(lex, parseConf);
                ;
            } else if (((lex[OTkWord])
                        && (((lex.get().strVal()) == (R"(Note)"))))) {
                result = newTree(orgLogbookNote);
                ;
                doAssert(((lex.pop(OTkWord).strVal()) == (R"(Note)")));
                lex.space();
                doAssert(((lex.pop(OTkWord).strVal()) == (R"(taken)")));
                lex.space();
                doAssert(((lex.pop(OTkWord).strVal()) == (R"(on)")));
                lex.space();
                result[R"(time)"] = parseTime(lex, parseConf);
                ;
                lex.space();
                if (lex[OTkDoubleSlash]) {
                    lex.skip(OTkDoubleSlash);
                };
            } else {
                assert(false);
            };
        };
        // body_parser
        {
            if (((pos) == (-1))) {
                result[R"(text)"] = newEmptyNode();
                lex.skip(OTkListItemEnd);
            } else {
                auto tokens
                    = (((@({initFakeTok(OTkParagraphStart)})))
                       & (lex.pop(lex.find(OTkListItemEnd))));
                tokens = tokens.strip(
                    leading      = {OTkNewline, OTkSpace},
                    trailing     = {OTkNewline, OTkSpace},
                    skipLeading  = {OTkStmtListOpen, OTkParagraphStart},
                    skipTrailing = {
                        OTkStmtListClose,
                        OTkParagraphEnd,
                        OTkListItemEnd});
                auto sub          = initLexer(tokens);
                result[R"(text)"] = parseListItemBody(sub, parseConf);
            }
        }
        return result;
    };

    void parseLogbook(Lexer& lex) {
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
                    parseLogbookListEntry(lex, parseConf);
                    break;
                }
                case OTkListClock: {
                    parseLogbookClockEntry(lex, parseConf);
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
        };

        if (indented) {
            lex.skip(OTkDedent);
        };

        lex.skip(OTkListEnd);
        lex.skip(OTkLogbookEnd);
        lex.skip(OTkColonEnd);
    }

    OrgNode parseDrawer(Lexer& lex) {
        start(orgDrawer);
        while (lex.at(IntSet{
            OTkColonProperties, OTkColonLogbook, OTKColonDescription})) {
            switch (lex.tok().kind) {
                case OTkColonProperties: {
                    lex.skip(OTkColonProperties);
                    auto properties = start(orgPropertyList);
                    while (lex[{OTkColonIdent, OTkColonAddIdent}]) {
                        auto prop = start(
                            lex.at(OTkColonIdent) ? orgProperty
                                                  : orgPropertyAdd);

                        token(
                            orgRawText,
                            lex.pop({OTkColonIdent, OTkColonAddIdent}));

                        if (lex[OTKIdent]) {
                            token(orgIdent, lex.pop(OTkIdent));
                        }

                        token(orgRawText, lex.pop(OTkRawProperty));
                        end();
                    }
                    lex.skip(OTkColonEnd);
                    break;
                }
                case OTkColonLogbook: {
                    result[R"(logbook)"] = parseLogbook(lex, parseConf);
                    break;
                }
                case OTkColonDescription: {
                    lex.skip(OTkColonDescription);
                    result[R"(description)"] = newTree(
                        orgSubtreeDescription);
                    ;
                    result[R"(description)"][R"(text)"] = parseParagraph(
                        lex, parseConf, false);
                    ;
                    lex.skip(OTkColonEnd);
                    break;
                }
                default: {
                    ;
                }
            };
        };
        return result;
    };

    OrgNode parseSubtree(Lexer& lex) {
        OrgNode result;
        result = newTree(orgSubtree);
        ;
        // prefix
        { result.add(newTree(orgRawText, lex.pop(OTkSubtreeStars))); };
        // todo_status
        {
            if (lex[OTkSubtreeTodoState]) {
                result.add(
                    newTree(orgBigIdent, lex.pop(OTkSubtreeTodoState)));
            } else {
                result.add(newEmptyNode());
            };
        };
        // urgency
        { result.add(newEmptyNode()); };
        // subtree_title
        { result.add(parseParagraph(lex, parseConf, false)); };
        // subtree_completion
        { result.add(newEmptyNode()); };
        // tree_tags
        {
            if (lex[OTkSubtreeTag]) {

                auto tags = newTree(orgInlineStmtList);
                ;
                ;
                while (lex[OTkSubtreeTag]) {
                    tags.add(newTree(orgOrgTag, lex.pop(OTkSubtreeTag)));
                };
                result.add(tags);
            } else {
                result.add(newEmptyNode());
            };
        };
        // subtree_time
        {

            auto times = newTree(orgStmtList);
            ;
            ;
            while (((lex[OTkSubtreeTime]) || (lex[OTkBracketTime]))) {

                auto time = newTree(orgTimeAssoc);
                ;
                ;
                if (lex[OTkSubtreeTime]) {
                    time.add(
                        newTree(orgBigIdent, lex.pop(OTkSubtreeTime)));
                } else {
                    time.add(newEmptyNode());
                };
                time.add(newTree(orgTimeStamp, lex.pop(OTkBracketTime)));
                times.add(time);
            };
            if (((times.len()) == (0))) {
                result.add(newEmptyNode());
            } else {
                result.add(times);
            };
        };
        // tree_drawer
        { result.add(parseDrawer(lex, parseConf)); };
        // content
        { result.add(newTree(orgStmtList)); };
        lex.skip(OTkSubtreeEnd);
        return result;
    };

    void skipLineCommand(Lexer& lex) {
        lex.skip(OTkCommandPrefix);
        lex.skip(OTkLineCommand);
        lex.skip(OTkColon);
    };
    /*

    template inDelimiters(lex: var Lexer; start, finish: OrgTokenKind;
    body: untyped): untyped = lex.skip(start) while ?lex and not
    lex[finish]: body lex.skip(finish)

    */
    ;

    /*

    template inCommandArguments(lex: var Lexer; body: untyped): untyped =
    inDelimiters(lex, OTkCommandArgumentsBegin, OTkCommandArgumentsEnd,
    body)

    */
    ;

    OrgNode parseOrgFile(Lexer& lex) {
        OrgNode result;
        result = newTree(orgFile);
        ;
        if (lex[OTkQuoteOpen]) {
            lex.next();
            result.add(newTree(orgRawText, lex.pop(OTkRawText)));
            lex.skip(OTkQuoteClose);
        } else {
            result.add(newTree(orgRawText, lex.pop(OTkRawText)));
        };
        return result;
    };

    OrgNode parseLineCommand(Lexer& lex) {
        OrgNode result;

        const auto kind = classifyCommand(lex.get((+(1))).strVal());
        ;
        ;
        switch (kind) {
            case ockInclude: {
                lex.skipLineCommand();
                lex.skip(OTkCommandArgumentsBegin);
                result = newTree(orgCommandInclude);
                ;
                result.add(parseOrgFile(lex, parseConf));
                if (lex[OTkCommandValue]) {
                    result.add(
                        newTree(orgIdent, lex.pop(OTkCommandValue)));
                } else {
                    result.add(newEmptyNode());
                };
                if (lex[OTkCommandValue]) {
                    result.add(
                        newTree(orgIdent, lex.pop(OTkCommandValue)));
                } else {
                    result.add(newEmptyNode());
                };
                result.add(parseSrcArguments(lex, parseConf));
                lex.skip(OTkCommandArgumentsEnd);
                break;
            }
            case ockAttrHtml: {
                lex.skipLineCommand();
                lex.skip(OTkCommandArgumentsBegin);
                result = newTree(
                    orgCommandAttrHtml, parseSrcArguments(lex, parseConf));
                ;
                lex.skip(OTkCommandArgumentsEnd);
                break;
            }
            case ockTitle: {
                lex.skipLineCommand();
                result = newTree(
                    orgCommandTitle,
                    parseParagraph(lex, parseConf, false));
                ;
                break;
            }
            case ockCaption: {
                lex.skipLineCommand();
                result = newTree(
                    orgCommandCaption,
                    parseParagraph(lex, parseConf, false));
                ;
                break;
            }
            case ockCreator:
            case ockOptions:
            case ockColumns:
            case ockAuthor:
            case ockLatexHeader:
            case ockLanguage: {

                const auto newk = switch (kind){case ockCreator :
                                                    {orgCommandCreator;
                break;
            }
            case ockLanguage: {
                orgCommandLanguage;
                break;
            }
            case ockAuthor: {
                orgCommandAuthor;
                break;
            }
            case ockOptions: {
                orgCommandOptions;
                break;
            }
            case ockLatexHeader: {
                orgLatexHeader;
                break;
            }
            case ockColumns: {
                orgColumns;
                break;
            }
            default: {
                orgEmpty;
            }
        };
        ;
        ;
        lex.skipLineCommand();
        result = newTree(newk);
        ;
        inCommandArguments(lex,
                           result.add(newTree(orgRawText, lex.pop())););
        break;
    }
    case ockFiletags: {
        lex.skipLineCommand();
        result = newTree(orgFiletags);
        ;
        inCommandArguments(
            lex, result.add(newTree(orgOrgTag, lex.pop(OtkSubtreeTag))););
        break;
    }
    case ockLatexClass:
    case ockLatexCompiler: {

        const auto newk = switch (kind){case ockLatexCompiler :
                                            {orgLatexCompiler;
        break;
    }
    case ockLatexClass: {
        orgLatexClass;
        break;
    }
    default: {
        orgEmpty;
    }
};
;
;
lex.skipLineCommand();
result = newTree(newk);
;
inCommandArguments(lex, result.add(newTree(orgIdent, lex.pop())););
break;
}
case ockProperty: {
    lex.skipLineCommand();
    inCommandArguments(lex,
                       result = newTree(
                           orgProperty,
                           newTree(orgRawText, lex.pop(OTkIdent)),
                           newEmptyNode(),
                           newTree(orgRawText, lex.pop(OTkRawProperty)));
                       ;);
    break;
}
default: {
    throw newUnexpectedKindError(kind, toStr(lex));
    ;
}
    }
    ;
    return result;
    }
    ;

    OrgNode parseToplevelItem(Lexer& lex) {
        OrgNode result;
        /*!Parse single toplevel entry from the input token stream -
        paragraph, list, table, subtree (not recursively), source code
        block, quote etc.
        */
        ;
        switch ((*(lex))) {
            case OTkParagraphStart: {
                result = parseParagraph(lex, parseConf, true);
                ;
                break;
            }
            case OTkTableBegin: {
                result = parseTable(lex, parseConf);
                ;
                break;
            }
            case OTkSubtreeStars: {
                result = parseSubtree(lex, parseConf);
                ;
                break;
            }
            case OTkListStart: {
                result = parseList(lex, parseConf);
                ;
                break;
            }
            case OTkTextSeparator: {
                result = newTree(orgTextSeparator, lex.pop());
                ;
                break;
            }
            case OTkCommandPrefix: {

                const auto kind = classifyCommand(
                    lex.get((+(1))).strVal());
                ;
                ;
                switch (kind) {
                    case ockBeginSrc: {
                        result = parseSrc(lex, parseConf);
                        ;
                        break;
                    }
                    case ockBeginQuote:
                    case ockBeginCenter:
                    case ockBeginAdmonition: {
                        result = parseTextWrapCommand(
                            lex, parseConf, kind);
                        ;
                        break;
                    }
                    default: {
                        result = parseLineCommand(lex, parseConf);
                        ;
                    }
                };
                break;
            }
            default: {
                throw newUnexpectedKindError((*(lex)), toStr(lex));
                ;
            }
        };
        return result;
    };

    OrgNode foldSubtrees(const Vec<OrgNode>& nodes) {
        OrgNode result;
        /*!Fold the tree structure into the final document output.
         */
        ;

        auto pos = 0;
        ;
        ;

        OrgNode tok() {
            OrgNode result;
            nodes[pos];
            return result;
        };

        int atLevel() {
            int result;
            result = tok()[R"(prefix)"].strVal().len();
            ;
            return result;
        };

        OrgNode aux() {
            OrgNode result;
            if (((tok())of(orgSubtree))) {
                result                  = tok();
                const auto currentLevel = atLevel();
                += pos;
                while (((pos) < (nodes.len()))) {
                    if (((tok())of(orgSubtree))) {
                        if (((currentLevel) < (atLevel()))) {
                            result[R"(body)"].add(aux());
                        } else {
                            return;
                            ;
                        };
                    } else {
                        result[R"(body)"].add(tok());
                        ++pos;
                    };
                };
            } else {
                result = tok();
                ++pos;
            };
            return result;
        }
        result = newTree(orgStmtList);
        while (((pos) < (nodes.len()))) {
            result.add(aux());
        };
        return result;
    };

    OrgNode parseTop(Lexer& lex) {
        while (lex.hasNext()) {
            if (lex.at(OTkComment)) {
                lex.next();
            } else {
                const auto top = parseToplevelItem(lex, parseConf);
                collect.add(top);
            };
        };
    };
    }
    }
    ;
