#pragma once

#include <string>

#include <hstd/stdlib/Array.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/charsets.hpp>

#include <lexbase/PosStr.hpp>
#include <parse/OrgToken.hpp>

struct ImplementError : public std::runtime_error {
    explicit ImplementError(const std::string& message = "")
        : std::runtime_error(message) {}
};


const auto commandNameMap = std::
    unordered_map<std::string, OrgCommandKind>{
        {"begin", ockBeginDynamic},
        {"end", ockEndDynamic},

        {"beginsrc", ockBeginSrc},
        {"endsrc", ockEndSrc},

        {"beginquote", ockBeginQuote},
        {"endquote", ockEndQuote},

        {"beginexample", ockBeginExample},
        {"endexample", ockEndExample},

        {"beginexport", ockBeginExport},
        {"endexport", ockEndExport},

        {"begintable", ockBeginTable},
        {"endtable", ockEndTable},

        {"begincenter", ockBeginCenter},
        {"endcenter", ockEndCenter},

        {"title", ockTitle},
        {"include", ockInclude},
        {"language", ockLanguage},
        {"caption", ockCaption},
        {"name", ockName},
        {"attrimg", ockAttrImg},
        {"author", ockAuthor},
        {"bind", ockBind},
        {"creator", ockCreator},
        {"filetags", ockFiletags},

        {"htmlhead", ockHtmlHead},
        {"attrhtml", ockAttrHtml},

        {"row", ockRow},
        {"cell", ockCell},
        {"header", ockHeader},
        {"options", ockOptions},
        {"property", ockProperty},
        {"columns", ockColumns},
        {"results", ockResults},
        {"call", ockCall},
        {"latexclass", ockLatexClass},
        {"latexcompiler", ockLatexCompiler},
        {"latexclassoptions", ockLatexClassOptions},
        {"beginadmonition", ockBeginAdmonition},
        {"endadmonition", ockEndAdmonition},
        {"latexheader", ockLatexHeader},
    };

OrgCommandKind classifyCommand(std::string const& command) {
    return commandNameMap.at(command);
}


CR<CharSet> OIdentChars{
    slice('a', 'z'),
    slice('A', 'Z'),
    '_',
    '-',
    slice('0', '9')};
CR<CharSet> OIdentStartChars = charsets::IdentChars
                             - CharSet{'_', '-', slice('0', '9')};

// IDEA in figure some additional unicode handing might be performed, but
// for now I just asume text is in UTF-8 and everything above 127 is a
// unicode rune too.

CR<CharSet> OWordChars = CharSet{
    slice('a', 'z'),
    slice('A', 'Z'),
    slice('0', '9'),
    slice('\x7F', '\xFF')};


CR<CharSet> OCommandChars = charsets::IdentChars + CharSet{'-', '_'};


CR<CharSet> OBigIdentChars  = CharSet{slice('A', 'Z')};
const char  OEndOfFile      = '\x00';
CR<CharSet> OBareIdentChars = charsets::AllChars - charsets::Whitespace;
CR<CharSet> OWhitespace     = charsets::Whitespace - CharSet{'\n'};
CR<CharSet> OEmptyChars     = OWhitespace + CharSet{OEndOfFile};
CR<CharSet> OLinebreaks     = charsets::Newlines + CharSet{OEndOfFile};
CR<CharSet> OMarkupChars    = CharSet{'*', '_', '/', '+', '~', '`'};
CR<CharSet> OVerbatimChars  = CharSet{'`', '~', '='};
CR<CharSet> OPunctChars = CharSet{'(', ')', '[', ']', '.', '?', '!', ','};
CR<CharSet> OPunctOpenChars    = CharSet{'(', '[', '{', '<'};
CR<CharSet> OPunctCloseChars   = CharSet{')', ']', '}', '>'};
CR<CharSet> ONumberedListChars = CharSet{slice('0', '9')}
                               + CharSet{slice('a', 'z')}
                               + CharSet{slice('A', 'Z')};
CR<CharSet> OBulletListChars = CharSet{'-', '+', '*'};
CR<CharSet> OListChars       = ONumberedListChars + OBulletListChars;


struct MarkupConfigPair {
    OrgTokenKind startKind;
    OrgTokenKind finishKind;
    OrgTokenKind inlineKind;
};


const CharSet markupKeys{'*', '/', '=', '`', '~', '_', '+', '"'};

/// Table of the markup config information, to reduce usage of the
/// character literals directly in the code.
const TypArray<char, MarkupConfigPair> markupConfig{{
    {'*', {OTkBoldOpen, OTkBoldClose, OTkBoldInline}},
    {'/', {OTkItalicOpen, OTkItalicClose, OTkItalicInline}},
    {'=', {OTkVerbatimOpen, OTkVerbatimClose, OTkVerbatimInline}},
    {'`', {OTkBacktickOpen, OTkBacktickClose, OTkBacktickInline}},
    {'~', {OTkMonospaceOpen, OTkMonospaceClose, OTkMonospaceInline}},
    {'_', {OTkUnderlineOpen, OTkUnderlineClose, OTkUnderlineInline}},
    {'+', {OTkStrikeOpen, OTkStrikeClose, OTkStrikeInline}},
    {'"', {OTkQuoteOpen, OTkQuoteClose, otNone}},
}};

struct OrgLexer {
    OrgTokenGroup* out;

    OrgLexer(OrgTokenGroup* _out) : out(_out) {}

    Vec<OrgToken>* buffer = nullptr;
    void           setBuffer(Vec<OrgToken>* _buffer) { buffer = _buffer; }
    void           clearBuffer() { buffer = nullptr; }


    void push(CR<OrgToken> tok) {
        if (buffer != nullptr) {
            buffer->push_back(tok);
        } else {
            out->push(tok);
        }
    }


    void push(CR<std::span<OrgToken>> tok) {
        if (buffer != nullptr) {
            buffer->append(tok);
        } else {
            out->push(tok);
        }
    }

    void push(CR<Vec<OrgToken>> tok) {
        if (buffer != nullptr) {
            buffer->append(tok);
        } else {
            out->push(tok);
        }
    }

    void lexAngle(PosStr& str) {
        if (str.at("<%%")) {
            push(str.tok(OTkDiaryTime, [](PosStr& str) {
                str.skip("<%%");
                skipBalancedSlice(
                    str,
                    {.openChars  = CharSet{'('},
                     .closeChars = CharSet{')'}});
                str.skip(">");
            }));
        } else if (str.at("<<<")) {
            push(str.tok(OTkTripleAngleOpen, skipCount, 3));
        } else if (str.at("<<")) {
            push(str.tok(OTkDoubleAngleOpen, skipCount, 2));
            push(str.tok(OTkRawText, skipTo, '>'));
            push(str.tok(OTkRawText, skipOne, ">>"));
        } else if (str.at(charsets::Digits, 1)) {
            auto skipAngles = [](PosStr& str) {
                str.skip('<');
                str.skipTo('>');
                str.skip('>');
            };

            push(str.tok(OTkAngleTime, skipAngles));

            if (str.at("--")) {
                push(str.tok(OTkTimeDash, skipCount, 2));
                push(str.tok(OTkAngleTime, skipAngles));
            }
        } else {
            push(str.tok(OTkAngleOpen, skipCount, 1));
            push(str.tok(OTkRawText, skipTo, '>'));
            push(str.tok(OTkAngleClose, skipOne, '>'));
        }
    }

    void lexTime(PosStr& str) {
        if (str.at('<')) {
            lexAngle(str);
        } else if (str.at('[')) {
            auto skipBracket = [](PosStr& str) {
                str.skip('[');
                str.skipTo(']');
                str.skip(']');
            };

            push(str.tok(OTkBracketTime, skipBracket));
            if (str.at("--")) {
                push(str.tok(OTkTimeDash, skipCount, 2));
                push(str.tok(OTkBracketTime, skipBracket));
            }
        } else {
            throw str.makeUnexpected("'<' or '['", "time");
        }
    }

    void lexLinkTarget(PosStr& str) {
        if (str.at(R"(https)") || str.at(R"(http)")) {
            assert(false && "FIXME");
        } else if (
            str.at(R"(file)")          //
            || str.at(R"(attachment)") //
            || str.at(R"(docview)")    //
            || str.at('/')             //
            || str.at(R"(./)")) {

            if (str.at('.') || str.at('/')) {
                assert(false && "FIXME");
                // push(
                //     result,
                //     str,
                //     result.add(
                //         initFakeTok(str, OTkLinkProtocol, R"(file)")));
            } else {
                push(str.tok(OTkLinkProtocol, skipTo, ':'));
                str.skip(':');
            }

            push(str.tok(OTkLinkTarget, [](PosStr& str) {
                while (!str.finished() && !str.at(R"(::)")) {
                    str.next();
                }
            }));

            if (str.at(R"(::)")) {
                push(str.tok(OTkLinkExtraSeparator, skipCount, 2));
                push(str.tok(OTkLinkExtra, skipPastEOF));
            }
        } else {
            if (str.hasAhead(':')) {
                push(str.tok(OTkLinkProtocol, skipTo, ':'));
                str.skip(':');
                push(str.tok(OTkLinkTarget, skipPastEOF));
            } else {
                push(str.tok(OTkLinkInternal, skipPastEOF));
            }
        }
    }

    void lexBracket(PosStr& str) {
        if (str.at(R"([[)")) {
            push(str.tok(OTkLinkOpen, skipOne, '['));
            // link_token
            {
                push(str.tok(OTkLinkTargetOpen, skipOne, '['));
                PosStr target = str.slice(skipBefore, ']');
                lexLinkTarget(target);
                push(str.tok(OTkLinkTargetClose, skipOne, ']'));
            };
            // description_token
            {
                if (str.at('[')) {
                    push(str.tok(OTkLinkDescriptionOpen, skipOne, '['));
                    PosStr desc = str.slice([](PosStr& str) {
                        int count = 0;
                        while (!str.finished()
                               && (!str.at(']') || (0 < count))) {

                            if (str.at('[')) {
                                ++count;
                            }
                            if (str.at(']')) {
                                --count;
                            }
                            str.next();
                        }
                    });

                    while (!desc.finished()) {
                        lexText(desc);
                    }

                    push(str.tok(OTkLinkDescriptionClose, skipOne, ']'));
                }
            }
            push(str.tok(OTkLinkClose, skipOne, ']'));
        } else if (str.at(R"([fn:)")) {
            push(str.tok(OTkFootnoteStart, skipOne, "[fn"));
            if (str.at(R"(::)")) {
                push(str.tok(OTkDoubleColon, skipOne, R"(::)"));
                // FIXME
                // result.addExpandTok(str, OTkText, str.skipTo(']'););
            } else {
                push(str.tok(OTkColon, skipOne, ':'));
                push(str.tok(OTkIdent, skipTo, ']'));
            }
            push(str.tok(OTkFootnoteEnd, skipOne, ']'));
        } else {
            // FIXME
            // push(trySpecific(str, OTkPunctuation, 1, lexTime));
        }
    }

    void lexTextChars(PosStr& str) {
        bool isStructure = false;
        auto skipCurly   = [](PosStr& str) {
            skipBalancedSlice(
                str,
                BalancedSkipArgs{.openChars = {'{'}, .closeChars = {'}'}});
        };

        auto skipParen = [](PosStr& str) {
            skipBalancedSlice(
                str,
                BalancedSkipArgs{.openChars = {'('}, .closeChars = {')'}});
        };

        auto skipBrace = [](PosStr& str) {
            skipBalancedSlice(
                str,
                BalancedSkipArgs{.openChars = {'['}, .closeChars = {']'}});
        };

        if (str.at("src[_-]?\\w+(\\[|\\{)")) {
            const auto    pos = str.getPos();
            Vec<OrgToken> buf;
            // Starting `src_` prefix
            {
                buf.push_back(str.tok(OTkSrcOpen, skipOne, "src"));
                if (str.at(CharSet{'_', '-'})) {
                    str.next();
                }
            }

            if (str.at(charsets::IdentStartChars)) {
                // FIXME push buffer only if the whole sequence is
                // determined to be a valid structure
                push(buf);
                push(str.tok(
                    OTkSrcName, skipZeroOrMore, charsets::IdentChars));
                if (str.at('[')) {
                    push(str.tok(OTkSrcArgs, skipBrace, {1, -2}));
                }

                push(str.tok(OTkSrcBody, skipCurly, {1, -2}));
                push(str.fakeTok(OTkSrcClose));
                isStructure = true;
            } else {
                str.setPos(pos);
            }

        } else if (str.at("call[_-]?\\w+(\\[|\\{)")) {
            const auto    pos = str.getPos();
            Vec<OrgToken> buf;
            buf.push_back(str.tok(OTkCallOpen, skipOne, "call"));
            if (str.at(CharSet{'_', '-'})) {
                str.next();
            }
            if (str.at(charsets::IdentStartChars)) {
                push(buf);
                push(str.tok(
                    OTkSrcName, skipZeroOrMore, charsets::IdentChars));
                if (str.at('[')) {
                    push(str.tok(OTkCallInsideHeader, skipBrace, {1, -2}));
                };
                push(str.tok(OTkCallArgs, skipParen, {1, -2}));
                push(str.fakeTok(OTkCallClose));
                isStructure = true;
            } else {
                str.setPos(pos);
            }
        } else if (str.at("https://") || str.at("http://")) {
            push(str.tok(OTkRawUrl, skipBefore, charsets::Whitespace));
        }
        if (!isStructure) {
            bool allUp = true;
            str.pushSlice();
            while (!str.finished()
                   && str.at(charsets::TextChars + CharSet{'-'})) {
                if (!str.at(charsets::HighAsciiLetters)) {
                    allUp = false;
                }
                str.next();
            }
            push(str.popTok(allUp ? OTkBigIdent : OTkWord));
        }
    }

    void lexParenArguments(PosStr& str) {
        push(str.tok(OTkParOpen, skipOne, '('));
        while (!str.at(')')) {
            push(str.tok(OTkRawText, skipBefore, cr(CharSet{',', ')'})));
            if (str.at(',')) {
                push(str.tok(OTkComma, skipOne, ','));
            }
            str.space();
        }
        push(str.tok(OTkParOpen, skipOne, ')'));
    };

    /*!Lex single text entry starting at current position
     */
    void lexText(PosStr& str) {
        const auto NonText = charsets::TextLineChars
                           - charsets::AsciiLetters - charsets::Utf8Any
                           + CharSet{'\n', '/'};

        switch (str.get()) {
            case '\n': {
                push(str.tok(OTkNewline, skipCount, 1));
                break;
            }
            case ' ': {
                push(str.tok(OTkSpace, [](PosStr& str) {
                    while (!str.finished() && str.at(' ')) {
                        str.next();
                    }
                }));
                break;
            }
            case '#': {
                std::function<Vec<OrgToken>(PosStr & str)> rec;
                rec = [&rec](PosStr& str) -> Vec<OrgToken> {
                    Vec<OrgToken> result;
                    result.push_back(str.tok(OTkHashTag, [](PosStr& str) {
                        if (str.at('#')) {
                            str.skip('#');
                        };
                        str.skipZeroOrMore(charsets::IdentChars);
                    }));

                    while (str.at(R"(##)") && !str.at(R"(##[)")) {
                        result.push_back(
                            str.tok(OTkHashTagSub, skipOne, '#'));
                        result.push_back(
                            str.tok(OTkHashTag, [](PosStr& str) {
                                str.skip('#');
                                str.skipZeroOrMore(charsets::IdentChars);
                            }));
                    }

                    if (str.at(R"(##[)")) {
                        result.push_back(
                            str.tok(OTkHashTagSub, skipOne, '#'));
                        result.push_back(
                            str.tok(OTkHashTagOpen, skipOne, "#["));

                        while (!str.finished() && !str.at(']')) {
                            result.append(rec(str));
                            str.space();
                            if (str.at(',')) {
                                result.push_back(
                                    str.tok(OTkComma, skipOne, ','));
                                str.space();
                            }
                        }
                        result.push_back(
                            str.tok(OTkHashTagClose, skipOne, ']'));
                    }
                    return result;
                };

                push(rec(str));
                break;
            }
            case '@': {
                const auto AtChars = charsets::IdentChars
                                   + charsets::Utf8Any;
                if (str.at(AtChars, 1)) {
                    push(str.tok(OTkAtMention, [&AtChars](PosStr& str) {
                        str.skip('@');
                        str.skipZeroOrMore(AtChars);
                    }));
                } else {
                    push(str.tok(OTkPunctuation, skipCount, 1));
                }
                break;
            }
            case '$': {
                auto          tmp = str;
                Vec<OrgToken> buf;
                try {
                    if (tmp.at('$', 1)) {
                        buf.push_back(
                            tmp.tok(OTkDollarOpen, skipOne, "$$"));
                        tmp.pushSlice();
                        bool hasEnd = false;
                        while (!tmp.finished() && !hasEnd) {
                            while (!tmp.finished() && !tmp.at('$')) {
                                tmp.next();
                            }
                            if (tmp.at("$$")) {
                                buf.push_back(
                                    tmp.popTok(OTkLatexInlineRaw));
                                hasEnd = true;
                            } else {
                                throw ImplementError();
                            }
                        }
                        // FIXME
                        // buf.add(tmp.tok(skip OTkDollarClose, '$', '$'));
                    } else {
                        buf.push_back(
                            tmp.tok(OTkDollarOpen, skipOne, '$'));
                        buf.push_back(
                            tmp.tok(OTkLatexInlineRaw, skipBefore, '$'));
                        buf.push_back(
                            tmp.tok(OTkDollarClose, skipOne, '$'));
                    }
                    push(buf);
                    str = tmp;
                } catch (UnexpectedCharError& err) {
                    push(str.tok(OTkPunctuation, skipZeroOrMore, '$'));
                }
                break;
            }
            case '\\': {
                switch (str.get(1)) {
                    case '[':
                    case '(': {
                        const auto isInline = str.at('(', 1);
                        if (isInline) {
                            push(str.tok(
                                OTkLatexParOpen, skipOne, R"(\\()"));
                        } else {
                            push(str.tok(
                                OTkLatexBraceOpen, skipOne, R"(\\[)"));
                        }
                        push(str.tok(
                            OTkLatexInlineRaw, [&isInline](PosStr& str) {
                                while (!str.at(
                                    isInline ? R"(\\))" : R"(\\])")) {
                                    str.next();
                                }
                            }));
                        if (isInline) {
                            push(str.tok(OTkLatexParClose, skipOne, ")"));
                        } else {
                            push(
                                str.tok(OTkLatexBraceClose, skipOne, "]"));
                        }
                        break;
                    }
                    case '\\': {
                        push(str.tok(OTkDoubleSlash, skipOne, R"(\\)"));
                        break;
                    }
                    default: {
                        if (str.at(OMarkupChars, 1)) {
                            push(str.tok(OTkEscaped, skipCount, 1));
                        } else if (str.at(
                                       charsets::IdentStartChars
                                           - CharSet{'_'},
                                       1)) {
                            push(str.tok(OTkSymbolStart, skipOne, '\\'));
                            push(str.tok(
                                OTkIdent,
                                skipZeroOrMore,
                                charsets::IdentChars));
                            if (str.at('[')) {
                                push(str.tok(
                                    OTkMetaBraceOpen, skipOne, '['));
                                push(str.tok(
                                    OTkMetaBraceBody, [](PosStr& str) {
                                        skipBalancedSlice(
                                            str,
                                            {.openChars    = {'['},
                                             .closeChars   = {']'},
                                             .skippedStart = true,
                                             .consumeLast  = false});
                                    }));
                                push(str.tok(
                                    OTkMetaBraceClose, skipOne, ']'));
                            }
                            while (str.at('{')) {
                                push(str.tok(
                                    OTkMetaArgsOpen, skipOne, '{'));
                                push(str.tok(
                                    OTkMetaBraceBody, [](PosStr& str) {
                                        skipBalancedSlice(
                                            str,
                                            {.openChars    = {'{'},
                                             .closeChars   = {'}'},
                                             .skippedStart = true,
                                             .consumeLast  = false});
                                    }));

                                push(str.tok(
                                    OTkMetaArgsClose, skipOne, '}'));
                            }
                            break;
                        } else {
                            push(str.tok(OTkEscaped, skipCount, 2));
                        }
                    }
                };
                break;
            }
            case '~':
            case '`':
            case '=': {
                const auto start = str.get();
                if (str.at(start, 1)) {
                    push(str.tok(
                        markupConfig[start].inlineKind, skipCount, 2));
                    push(str.tok(OTkRawText, [start](PosStr& str) {
                        while (!str.at(start, start)) {
                            str.next();
                        }
                    }));
                    push(str.tok(
                        markupConfig[start].inlineKind, skipCount, 2));
                } else {
                    if (str.at(NonText, -1) || str.atStart()) {
                        push(str.tok(
                            markupConfig[start].startKind, skipCount, 1));
                        push(str.tok(OTkRawText, skipTo, start));
                        if (str.at(NonText, 1) || str.beforeEnd()) {
                            push(str.tok(
                                markupConfig[start].finishKind,
                                skipCount,
                                1));
                        }
                    } else {
                        push(str.tok(OTkPunctuation, skipCount, 1));
                    }
                }
                break;
            }
            case '<': {
                try {
                    lexAngle(str);
                    // REFACTOR remove exception for control handling, make
                    // interface more explicit
                } catch (UnexpectedCharError&) {
                    push(str.tok(OTkPunctuation, skipCount, 1));
                }
                break;
            }

            case '[': {
                lexBracket(str);
                break;
            }
            case '(': {
                push(str.tok(OTkParOpen, skipCount, 1));
                break;
            }
            case ')': {
                push(str.tok(OTkParClose, skipCount, 1));
                break;
            }
            case ':': {
                push(str.tok(OTkColon, skipCount, 1));
                break;
            }
            case '\'':
            case '?':
            case '!':
            case '%':
            case ']':
            case '|':
            case '&':
            case ';':
            case '}':
            case '>': {
                push(str.tok(OTkPunctuation, skipCount, 1));
                break;
            }
            case '{': {
                if (str.at("{{{")) {
                    push(str.tok(OTkMacroOpen, skipCount, 3));
                    push(str.tok(OTkIdent, [](PosStr& str) {
                        while (!str.finished() && !str.at('(')
                               && !str.at("}}}")) {
                            str.next();
                        }
                    }));

                    if (str.at('(')) {
                        lexParenArguments(str);
                    }
                    if (!str.finished()) {
                        push(str.tok(OTkMacroOpen, skipOne, "}}}"));
                    }
                } else {
                    push(str.tok(OTkMaybeWord, skipCount, 1));
                }
                break;
            }
            case '^': {
                push(str.tok(OTkCircumflex, skipCount, 1));
                break;
            }
            default: {
                if (str.at(charsets::TextChars)) {
                    lexTextChars(str);
                } else if (str.at(
                               markupKeys - CharSet{'<', '~', '`', '='})) {
                    const auto ch                        = str.get();
                    const auto& [kOpen, kClose, kInline] = markupConfig
                        [ch];
                    if (str.at((+(1)), ch)) {
                        push(str.tok(kInline, skipCount, 2));
                    } else if (str.at(NonText, -1) || str.atStart()) {
                        push(str.tok(kOpen, skipCount, 1));
                    } else if (str.at(NonText, 1) || str.beforeEnd()) {
                        push(str.tok(kClose, skipCount, 1));
                    } else {
                        push(str.tok(OTkWord, skipCount, 1));
                    }
                    break;
                } else {
                    throw str.makeUnexpected("any text character", "text");
                }
            }
        }
    }

    void lexProperties(const PosStr& id, PosStr& str) {
        push(Token(OTkColonProperties, id.view));
        auto hasEnd = false;
        while (!str.finished() && !hasEnd) {
            str.space();
            auto       isAdd = false;
            const auto id    = str.slice([&isAdd](PosStr& str) {
                str.skip(':');
                str.skipZeroOrMore(charsets::IdentChars);
                if (str.at('+')) {
                    isAdd = true;
                }
                str.skip(':');
            });

            if (normalize(id.toStr()) == R"(:end:)") {
                hasEnd = true;
                push(Token(OTkColonEnd, id.view));
            } else {
                push(Token(
                    isAdd ? OTkColonAddIdent : OTkColonIdent, id.view));
                if (str.at(charsets::IdentStartChars)) {
                    push(str.tok(OTkIdent, [](PosStr& str) {
                        while (
                            !str.finished()
                            && str.at(
                                charsets::DashIdentChars + CharSet{'/'})) {
                            str.next();
                        }
                    }));
                    str.skip(':');
                }
                str.space();
                push(str.tok(OTkRawProperty, skipToEOL));
                str.skip('\n');
            }
        }
    }

    void lexDescription(const PosStr& id, PosStr& str) {
        push(Token(OTkColonDescription, id.view));
        str.pushSlice();
        auto hasEnd = false;
        while (!str.finished() && !hasEnd) {
            while (!str.finished() && !str.at(":end:")) {
                str.next();
            }
            push(Token(OTkText, str.popSlice().view));
            const auto id = str.slice([](PosStr& str) {
                str.skip(':');
                str.skipZeroOrMore(charsets::IdentChars);
                str.skip(':');
            });
            push(Token(OTkColonEnd, id.view));
            hasEnd = true;
        }
    }

    void lexLogbook(const PosStr& id, PosStr& str) {
        push(Token(OTkColonLogbook, id.view));
        str.pushSlice();
        auto hasEnd = false;
        while (!str.finished() && !hasEnd) {
            while (!str.finished() && !str.at(":end:")) {
                str.next();
            }

            push(Token(OTkRawLogbook, str.popSlice().view));

            const auto id = str.slice([](PosStr& str) {
                str.skip(':');
                str.skipZeroOrMore(charsets::IdentChars);
                str.skip(':');
            });

            push(Token(OTkColonEnd, id.view));
            hasEnd = true;
        };
    };

    void lexDrawer(PosStr& str) {
        auto strEnded = false;
        while (!str.finished() && !strEnded) {
            str.space();
            const auto id = str.slice([](PosStr& str) {
                str.skip(':');
                str.skipZeroOrMore(charsets::IdentChars);
                str.skip(':');
            });

            str.skip('\n');
            const Str norm = normalize(id.toStr());
            if (norm == ":properties:") {
                lexProperties(id, str);
            } else if (norm == ":logbook:") {
                lexLogbook(id, str);
            } else if (norm == ":description:") {
                lexDescription(id, str);
            } else {
                assert(false && "FIXME IMPLEMENT");
                // throw newImplementKindError(norm, toStr(str));
            }

            auto ahead = str;
            ahead.space();
            if (ahead.trySkip('\n')) {
                ahead.space();
                if (!ahead.at(':')) {
                    strEnded = true;
                    str      = ahead;
                }
            }
            if (!strEnded) {
                str.skipZeroOrMore('\n');
            }
        }
    }

    void lexSubtreeTodo(PosStr& str) {
        auto tmp = str;
        tmp.pushSlice();
        tmp.skipZeroOrMore(charsets::HighAsciiLetters);
        if (tmp.at(' ')) {
            push(tmp.popTok(OTkSubtreeTodoState));
            str = tmp;
        }
    }

    void lexSubtreeUrgency(PosStr& str) {
        if (str.at("[#")) {
            str.pushSlice();
            str.next(2);
            str.skip(charsets::HighAsciiLetters);
            str.skipZeroOrMore(charsets::HighAsciiLetters);
            str.skip(']');
            push(str.popTok(OTkSubtreeUrgency));
            str.space();
        }
    }

    void lexSubtreeTitle(PosStr& str) {
        auto          body = str.slice(skipToEOL);
        Vec<OrgToken> headerTokens;
        body.skipToEOF();
        if (body.at(':')) {
            body.back();
            auto tagEnded = false;
            while (!body.finished() && !tagEnded) {
                const auto finish = body.getPos();
                while (!body.finished()
                       && !body.at(
                           charsets::IdentChars + CharSet{'#', '@'})) {
                    body.back();
                }

                const auto start = body.getPos() + 1;
                body.skip(':', -1);
                headerTokens.push_back(Token(
                    OTkSubtreeTag, body.sliceBetween(start, finish).view));
                if (body.at(' ')) {
                    tagEnded = true;
                }
            }
            while (body.at(' ')) {
                body.back();
            }
        }
        if (body.at(']')) {
            auto tmp = body;
            try {
                const auto finish = tmp.getPos();
                tmp.skip(']', -1);
                tmp.skip(charsets::Digits, -1);
                while (tmp.at(charsets::Digits)) {
                    tmp.back();
                }
                if (str.at('%')) {
                    tmp.back();
                } else {
                    tmp.skip('/', -1);
                    tmp.skip(charsets::Digits, -1);
                    while (tmp.at(charsets::Digits)) {
                        tmp.back();
                    }
                }
                tmp.skip('[', -1, -1);

                const auto start = tmp.getPos() + 1;
                body             = tmp;
                headerTokens.push_back(Token(
                    OTkSubtreeCompletion,
                    tmp.sliceBetween(start, finish).view));
                while (body.at(' ')) {
                    body.next(-1);
                }
            } catch (UnexpectedCharError& err) { ; };
        }
        //
        {

            auto finish = body.getPos();
            body.skipToSOF();
            const auto start = body.getPos();
            auto       slice = str.sliceBetween(start, finish);
            headerTokens.push_back(Token(OTkText, slice.view));
        }
        push(headerTokens.reversed());
    }

    void lexSubtreeTimes(PosStr& str) {
        str.space();
        auto hadTimes = false;
        while (str.at(charsets::HighAsciiLetters)) {
            hadTimes   = true;
            auto times = str;
            times.space();
            const auto tag = times.slice(
                skipZeroOrMore, charsets::HighAsciiLetters);

            if (Vec<Str>{R"(deadline)", R"(closed)", R"(scheduled)"}
                    .contains(normalize(tag.toStr()))) {
                push(Token(OTkSubtreeTime, tag.view));
                times.skip(':');
                times.space();
                lexTime(times);
                times.space();
                str = times;
            } else {
                break;
            }
            times.space();
        }
        if (hadTimes) {
            str.skip('\n');
        }
    }

    void lexSubtree(PosStr& str) {
        push(str.tok(OTkSubtreeStars, skipZeroOrMore, '*'));
        str.skip(' ');
        str.space();
        lexSubtreeTodo(str);
        str.space();
        lexSubtreeUrgency(str);
        str.space();
        lexSubtreeTitle(str);
        str.trySkip('\n');
        lexSubtreeTimes(str);
        auto drawer = str;
        drawer.space();
        if (drawer.at(':')) {
            lexDrawer(drawer);
            str = drawer;
        }
    }

    void lexSourceBlockContent(PosStr& str) {
        while (!str.finished()) {
            if (str.at(R"(<<)")) {
                auto          failedAt = -1;
                auto          tmp      = str;
                Vec<OrgToken> tmpRes;
                // try_tangle
                {
                    tmpRes.push_back(
                        tmp.tok(OTkDoubleAngleOpen, skipOne, R"(<<)"));
                    if (tmp.at(charsets::IdentChars)) {
                        tmpRes.push_back(tmp.tok(
                            OTkIdent,
                            skipZeroOrMore,
                            charsets::IdentChars));
                    } else {
                        failedAt = tmp.pos;
                        break;
                    }
                    if (tmp.at('(')) {
                        setBuffer(&tmpRes);
                        lexParenArguments(str);
                        clearBuffer();
                    }
                    if (tmp.at(">>")) {
                        tmpRes.push_back(
                            tmp.tok(OTkDoubleAngleClose, skipOne, ">>"));
                    } else {
                        failedAt = tmp.pos;
                        break;
                    }
                }
                if (failedAt != -1) {
                    push(str.tok(OTkCodeText, [&failedAt](PosStr& str) {
                        while (((str.pos) < (failedAt))) {
                            str.next();
                        }
                    }));
                    str.setPos(failedAt);
                } else {
                    push(tmpRes);
                    str = tmp;
                }
            } else if (str.at(R"((refs:)")) {
                push(str.tok(OTkParOpen, skipOne, '('));
                push(str.tok(OTkIdent, skipOne, "refs"));
                push(str.tok(OTkColon, skipOne, ":"));
                push(str.tok(
                    OTkIdent,
                    skipZeroOrMore,
                    cr(charsets::IdentChars + CharSet{'-'})));
                push(str.tok(OTkParClose, skipOne, ')'));

            } else if (str.at('\n')) {
                push(str.tok(OTkNewline, skipCount, 1));
            } else {
                push(str.tok(OTkCodeText, [](PosStr& str) {
                    while (!str.finished()
                           && !(
                               str.at(R"(<<)")     //
                               || str.at("(refs:") //
                               || str.at('\n'))) {
                        str.next();
                    }
                }));
            }
        }
    }

    void lexCommandContent(PosStr& str, const OrgCommandKind& kind) {
        push(str.fakeTok(OTkCommandContentStart));
        switch (kind) {
            case ockBeginQuote:
            case ockBeginCenter:
            case ockBeginAdmonition: {
                push(str.tok(OTkText, skipPastEOF));
                break;
            }
            case ockBeginExample: {
                push(str.tok(OTkRawText, skipPastEOF));
                break;
            }
            case ockBeginDynamic: {
                str.space();
                push(str.tok(OTkText, skipPastEOF));
                break;
            }
            case ockBeginSrc: {
                str.space();
                push(str.fakeTok(OTkCodeContentBegin));
                Vec<OrgToken> code;
                setBuffer(&code);
                {
                    lexSourceBlockContent(str);
                    if (code.back().kind == OTkCodeText
                        && all_of(code.back().text, [](char c) {
                               return c == ' ';
                           })) {
                        code.pop_back();
                    }
                    if (code.back().kind == OTkNewline) {
                        code.pop_back();
                    }
                    push(code);
                    push(str.fakeTok(OTkCodeContentEnd));
                }
                clearBuffer();
                break;
            }
            default: {
                assert(false && "IMPLEMENT");
            }
        };
        push(str.fakeTok(OTkCommandContentEnd));
    }

    Vec<OrgToken> lexDelimited(
        PosStr&                         str,
        const Pair<char, OrgTokenKind>& start,
        const Pair<char, OrgTokenKind>& finish,
        const OrgTokenKind&             middle) {
        Vec<OrgToken> result;
        result.push_back(str.tok(start.second, skipOne, start.first));
        result.push_back(str.tok(middle, [&finish](PosStr& str) {
            while (!str.finished() && !str.at(finish.first)) {
                if (str.at('\\')) {
                    str.next(2);
                } else {
                    str.next();
                }
            }
        }));
        if (!str.finished()) {
            result.push_back(str.tok(finish.second, skipCount, 1));
        }
        return result;
    }

    void lexCommandArguments(PosStr& str, const OrgCommandKind& kind) {
        OrgTokenKind wrapStart = OTkCommandArgumentsBegin;
        OrgTokenKind wrapEnd   = OTkCommandArgumentsEnd;
        switch (kind) {
            case ockTitle:
            case ockCaption:
                wrapStart = OTkParagraphStart;
                wrapEnd   = OTkParagraphEnd;
        }

        push(str.fakeTok(wrapStart));
        std::function<void(PosStr&)> lexKeyValue;
        lexKeyValue = [this](PosStr& str) {
            while (!str.finished()) {
                switch ((str.get())) {
                    case '-': {
                        push(str.tok(
                            OTkCommandFlag,
                            skipZeroOrMore,
                            cr(CharSet{'-'} + charsets::IdentChars)));
                        break;
                    }
                    case ':': {
                        push(str.tok(
                            OTkCommandKey,
                            skipZeroOrMore,
                            cr(charsets::IdentChars + CharSet{'-', ':'})));
                        break;
                    }
                    case ' ': {
                        str.space();
                        break;
                    }
                    default: {
                        push(str.tok(OTkCommandValue, [](PosStr& str) {
                            auto hasColon = false;
                            while (!str.finished() && !hasColon) {
                                while (!str.finished()
                                       && !str.at(
                                           charsets::HorizontalSpace)) {
                                    str.next();
                                }
                                if (!str.finished()) {
                                    auto tmp = str;
                                    tmp.space();
                                    if (!tmp.at(':')) {
                                        tmp.next();
                                        str = tmp;
                                    } else {
                                        hasColon = true;
                                    }
                                }
                            }
                        }));
                    }
                }
            }
        };

        switch (kind) {
            case ockBeginQuote: {
                break;
            }
            case ockTitle: {
                while (!str.finished()) {
                    lexText(str);
                }
                break;
            }
            case ockOptions: {
                while (!str.finished()) {
                    switch (str.get()) {
                        case '\'':
                        case '*':
                        case '|':
                        case ':':
                        case '<':
                        case '\n':
                        case '^': {
                            push(str.tok(OTkRawText, skipCount, 1));
                            break;
                        }
                        case ' ': {
                            str.space();
                            break;
                        }
                        default: {
                            push(str.tok(OTkRawText, [](PosStr& str) {
                                while (!str.finished()
                                       && !str.at(
                                           charsets::HorizontalSpace)) {
                                    str.next();
                                }
                            }));
                        }
                    }
                }
                break;
            }
            case ockCaption: {
                push(str.tok(OTkText, skipPastEOF));
                break;
            }
            case ockCall: {
                str.space();
                push(str.tok(
                    OTkCallName, skipZeroOrMore, charsets::IdentChars));
                if (str.at('[')) {
                    push(str.tok(
                        OTkCallInsideHeader, skipBalancedSlice, '[', ']'));
                }

                push(str.tok(OTkCallArgs, skipBalancedSlice, '(', ')'));
                if (!str.finished()) {
                    push(str.tok(OTkRawText, skipPastEOF));
                }
                break;
            }
            case ockBeginSrc: {
                push(str.tok(
                    OTkWord, skipZeroOrMore, charsets::IdentChars));
                str.space();
                lexKeyValue(str);
                break;
            }
            case ockBeginTable:
            case ockAttrHtml: {
                lexKeyValue(str);
                break;
            }
            case ockBeginDynamic: {
                push(str.tok(
                    OTkWord, skipZeroOrMore, charsets::IdentChars));
                str.space();
                lexKeyValue(str);
                break;
            }
            case ockHeader: {
                str.space();
                lexKeyValue(str);
                break;
            }
            case ockAuthor:
            case ockCreator:
            case ockLanguage: {
                str.space();
                push(str.tok(OTkRawText, skipPastEOF));
                break;
            }
            case ockProperty: {
                str.space();
                push(str.tok(OTkIdent, skipBefore, cr(CharSet{' ', ':'})));
                if (str.at(':')) {
                    push(str.tok(OTkColon, skipCount, 1));
                    push(str.tok(OTkIdent, skipBefore, ' '));
                }
                str.space();
                push(str.tok(OTkRawProperty, skipPastEOF));
                break;
            }
            case ockFiletags: {
                while (str.at(':')) {
                    str.skip(':');
                    if (!str.finished()) {
                        push(str.tok(OTkSubtreeTag, [](PosStr& str) {
                            while (!str.finished() && !str.at(':')) {
                                str.next();
                            }
                        }));
                    }
                }
                break;
            }
            case ockInclude: {
                str.space();
                if (str.at('"')) {
                    lexDelimited(
                        str,
                        {'"', OTkQuoteOpen},
                        {'"', OTkQuoteClose},
                        OTkRawText);
                } else {
                    push(str.tok(OTkRawText, [](PosStr& str) {
                        while (!str.finished()
                               && !str.at(charsets::HorizontalSpace)) {
                            str.next();
                        }
                    }));
                }
                lexKeyValue(str);
                break;
            }
            case ockName:
            case ockLatexClass:
            case ockLatexCompiler:
            case ockBeginAdmonition: {
                str.space();
                push(str.tok(OTkIdent, skipPastEOF));
                break;
            }
            case ockColumns:
            case ockBeginExample:
            case ockResults:
            case ockLatexHeader:
            case ockHtmlHead:
            case ockBeginCenter:
            case ockLatexClassOptions: {
                push(str.tok(OTkRawText, skipPastEOF));
                break;
            }
            default: {
                assert(false);
                // throw newUnexpectedKindError(kind, toStr(str));
                push(str.tok(OTkRawText, skipPastEOF));
            }
        }

        push(str.fakeTok(wrapEnd));
    }

    void lexCommandBlock(PosStr& str) {
        const auto column = str.getColumn();
        push(str.tok(OTkCommandPrefix, skipOne, "#+"));
        const auto id = str.slice(skipZeroOrMore, OCommandChars);
        if (normalize(id.toStr()).startsWith("begin")) {
            push(Token(OTkCommandBegin, id.view));
            const auto sectionName = normalize(id.toStr())
                                         .dropPrefix("begin");
            const auto kind = classifyCommand(id.toStr());
            if (kind == ockBeginDynamic) {
                str.skip(':');
            }
            str.space();
            auto arguments = str.slice({0, -2}, skipPastEOL);
            lexCommandArguments(arguments, kind);
            auto found = false;
            str.pushSlice();
            while (!found && !str.finished()) {
                while (
                    !str.finished()
                    && !(str.getColumn() == column && str.at(R"(#+)"))) {
                    str.next();
                }
                assert(!str.finished());
                const auto   prefix = str.slice(skipCount, 2);
                const PosStr id = str.slice(skipZeroOrMore, OCommandChars);
                if (normalize(id.toStr()) == "end" + sectionName) {
                    found      = true;
                    auto slice = str.popSlice(
                        (-((((1 + id.size()) + (3))))));
                    lexCommandContent(slice, kind);
                    push(Token(OTkCommandPrefix, prefix.view));
                    push(Token(OTkCommandEnd, id.view));
                }
            }
            if (kind == ockBeginDynamic) {
                str.skip(':');
            }
        } else {
            push(Token(OTkLineCommand, id.view));
            push(str.tok(OTkColon, skipOne, ':'));
            str.space();
            auto args = str.slice(skipToEOL);
            lexCommandArguments(args, classifyCommand(id.toStr()));
            if (!str.finished()) {
                str.skip('\n');
            }
        }
    }

    bool isFirstOnLine(PosStr& str) {
        const auto set = charsets::Newline + CharSet{'\0'};
        if (str.at(set, -1)) {
            return true;
        }

        auto pos = 0;
        while (str.at(charsets::HorizontalSpace, pos)) {
            --pos;
        }
        return str.at(set, pos);
    };

    /*!Check if the string is positioned at the start of a logbook
    `CLOCK:` entry.
    */
    bool atLogClock(PosStr& str) {
        const auto ahead = str.slice(skipTo, '[');
        const auto space = ahead.getSkip('C');
        if (0 <= space) {
            for (const auto ch : ahead[slice(0, space - 1)].view) {
                if (ch != ' ') {
                    return false;
                }
            }

            return ahead[slice(space, 1_B)].at("CLOCK:");
        } else {
            return false;
        }
    }

    /*!Check if string is positioned at the start of toplevel language
    construct.
    */
    bool atConstructStart(PosStr& str) {
        bool result;
        if (!isFirstOnLine(str)) {
            return false;
        }
        if (str.getIndent() == 0 && str.at('*')) {
            auto shift = 0;
            while (str.at('*', shift)) {
                ++shift;
            }
            result = str.at(' ', shift);
        } else {
            result = str.at(R"(#+)") || str.at(R"(---)");
        }
        return result;
    }


    // Store common types of the lexer state
    template <typename Flag>
    struct HsLexerState {
        Vec<Flag> flagStack;
        Vec<int>  indent; /// Indentation steps encountered by the lexer
                          /// state
        /*!Check if state has any indentation levels stored
         */
        bool hasIndent() { return 0 < indent.size(); }

        enum LexerIndentKind
        {
            likIncIndent,  /// Indentation increased on current position
            likDecIndent,  /// Decreased on current position
            likSameIndent, /// No indentation change
            likEmptyLine,  /// Multiple whitespaces followed by newline -
                           /// special case for indented blocks.
            likNoIndent,   /// Not at position where indentation can be
                           /// determine (e.g. is inside of a identifier or
                           /// at the start of the line)
        };


        /// Get total indentation level from the state
        int getIndent() const {
            int result;
            for (const auto& level : indent) {
                result += level;
            }
            return result;
        }

        void addIndent(int ind) { indent.push_back(ind); }

        int popIndent() { return indent.pop_back_v(); }

        /// Skip all indentation levels in the lexer - consume leading
        /// whitespaces and calculate list of the indentation level
        /// changes.
        ///
        /// NOTE: indentation calculations are independent from the actual
        /// column values and are only based on the actual spaces used in
        /// the input.
        Vec<LexerIndentKind> skipIndent(PosStr& str) {
            Vec<LexerIndentKind> result;
            if (str.at(charsets::Newline)) {
                str.next();
            }

            int skip = 0;
            while (str.at(charsets::HorizontalSpace, skip)) {
                ++skip;
            }

            str.next(skip);
            if (str.at(charsets::Newline)) {
                result.push_back(likEmptyLine);
            } else {
                const int now = getIndent();
                if (skip == now) {
                    result.push_back(likSameIndent);
                } else if (now < skip) {
                    result.push_back(likIncIndent);
                    // add single indentation level;
                    addIndent(skip - now);
                } else if (skip < now) { // indentation level decreased
                                         // from the current one - pop all
                    // indentation levels until it will be the same.
                    while (skip < getIndent()) {
                        popIndent();
                        result.push_back(likDecIndent);
                    }
                }
            }

            return result;
        }
    };


    using HsLexerStateSimple = HsLexerState<char>;

    void skipIndents(HsLexerStateSimple& state, PosStr& str) {
        using LK           = HsLexerStateSimple::LexerIndentKind;
        const auto skipped = state.skipIndent(str);
        for (const auto indent : skipped) {
            switch (indent) {
                case LK::likIncIndent: {
                    push(str.fakeTok(OTkIndent));
                    break;
                }
                case LK::likDecIndent: {
                    push(str.fakeTok(OTkDedent));
                    break;
                }
                case LK::likSameIndent: {
                    push(str.fakeTok(OTkSameIndent));
                    break;
                }
                case LK::likNoIndent: {
                    push(str.fakeTok(OTkNoIndent));
                    break;
                }
                case LK::likEmptyLine: {
                    assert(false);
                    break;
                }
            }
        }
    }

    const CharSet ListStart = CharSet{'-', '+', '*'} + charsets::Digits
                            + charsets::AsciiLetters;

    /*!Attempt to parse list start dash
     */
    Vec<OrgToken> tryListStart(PosStr& str) {
        Vec<OrgToken> result;
        if (atConstructStart(str)) {
            return {};
        }
        auto tmp = str;


        if (tmp.at(CharSet{'-', '+'})
            || (0 < tmp.getIndent()) && tmp.at('*')) {
            result.push_back(tmp.tok(OTkListDash, skipOne, ListStart));

            if (!tmp.trySkip(' ')) {
                return {};
            }
            tmp.space();
        } else if (tmp.at(charsets::Digits + charsets::AsciiLetters)) {
            result.push_back(tmp.tok(OTkListDash, [](PosStr& str) {
                if (str.at(charsets::Digits + charsets::AsciiLetters)) {
                    str.next();
                } else {
                    return;
                }
            }));

            if (tmp.at(')') || tmp.at('.')) {
                tmp.next();
            } else {
                return {};
            }

            if (tmp.at(' ')) {
                tmp.next();
            } else {
                return {};
            }
        } else {
            if (tmp.at(CharSet{'-', '+', '*'})) {
                tmp.next();
            } else {
                return {};
            }

            if (tmp.at(' ')) {
                tmp.next();
            } else {
                return {};
            }
        }
        str = tmp;
        return result;
    }


    bool listAhead(PosStr& str) {
        bool result;
        if (!isFirstOnLine(str)) {
            return false;
        }

        const auto init = str.toStr();
        auto       tmp  = str;
        tmp.space();
        if (tmp.at(ListStart)) {
            if (tryListStart(tmp).empty()) {
                return false;
            } else {
                str = tmp;
                return true;
            }
        } else {
            return false;
        }
    }

    /*!Lex head starting from current position onwards. `indent` is the
indentation of the original list prefix -- dash, number or letter.
*/
    void lexListItem(
        PosStr&             str,
        const int&          indent,
        HsLexerStateSimple& state) {
        if (str.at("\\[[Xx - ]\\]")) {
            push(str.tok(OTkCheckbox, [](PosStr& str) {
                str.skip('[');
                str.skip(CharSet{'X', 'x', ' ', '-'});
                str.skip(']');
            }));

            str.space();
        }
        //
        {
            auto tmp = str;
            auto buf = Vec<OrgToken>{
                tmp.fakeTok(OTkListDescOpen),
                tmp.fakeTok(OTkParagraphStart)};

            while (!tmp.finished() && !tmp.at(charsets::Newline)) {
                if (tmp.at(':') && tmp.at("::")) {
                    buf.push_back(tmp.fakeTok(OTkParagraphEnd));
                    buf.push_back(tmp.fakeTok(OTkListDescClose));
                    buf.push_back(tmp.tok(OTkDoubleColon, skipOne, "::"));
                    str = tmp;
                    push(buf);
                    break;
                } else {
                    setBuffer(&buf);
                    lexText(tmp);
                    clearBuffer();
                }
            }
        }

        str.pushSlice();
        auto atEnd = false;
        while (!str.finished() && !atEnd) {
            if (atLogClock(str)) {
                str.next();
                atEnd = true;
            } else if (
                atConstructStart(str) && (str.getIndent() <= indent)) {
                atEnd = true;
            } else if (listAhead(str)) {
                atEnd = true;
            } else {
                //
                {
                    auto testTwoSpace = str;
                    testTwoSpace.space();
                    if (testTwoSpace.at(charsets::Newline)) {
                        testTwoSpace.next();
                        testTwoSpace.space();
                        if (testTwoSpace.at(charsets::Newline)) {
                            atEnd = true;
                        }
                    }
                }
                if (!atEnd) {
                    auto testIndent = str;
                    testIndent.skipPastEOL();
                    while (testIndent.trySkipEmptyLine()) {}
                    if (testIndent.getIndent() < indent) {
                        atEnd = true;
                    } else if (
                        testIndent.getIndent() == indent
                        && !listAhead(str)) {
                        atEnd = true;
                    }
                    str.skipPastEOL();
                }
            }
        }

        auto slice = str.popSlice(-1);
        while (str.view.at(slice.view.size()) == '\n') {
            slice.view.remove_suffix(1);
        }

        push(Token(OTkStmtList, slice.view));
        push(str.fakeTok(OTkListItemEnd));
    }

    void lexListItems(PosStr& str, HsLexerStateSimple& state) {
        assert(!str.at('\n'));
        while (listAhead(str) || atLogClock(str)) {
            assert(!str.at('\n'));
            if (atLogClock(str)) {
                push(str.fakeTok(OTkListClock));
                str.pushSlice();
                str.skipToEOL();
                auto slice = str.popSlice();
                lexParagraph(slice);
                str.next();
                push(str.fakeTok(OTkListItemEnd));
            } else {
                skipIndents(state, str);
                const auto indent = str.getColumn();
                auto       tmp    = str;
                const auto tokens = tryListStart(tmp);
                if (tokens.empty()) {
                    lexParagraph(str);
                } else {
                    str = tmp;
                    push(tokens);
                    lexListItem(str, indent, state);
                }
            }
        }
        str.skipToEOL();
    }

    void lexList(PosStr& str) {
        auto state = HsLexerStateSimple();
        push(str.fakeTok(OTkListStart));
        Vec<OrgToken> tokens;
        setBuffer(&tokens);
        lexListItems(str, state);
        clearBuffer();
        if (tokens[0].kind != OTkSameIndent) {
            push(tokens[0]);
        }
        push(tokens[slice(1, 1_B)]);
        while (state.hasIndent()) {
            state.popIndent();
            push(str.fakeTok(OTkDedent));
        }
        push(str.fakeTok(OTkListEnd));
    }

    void lexParagraph(PosStr& str) {
        const auto indent = str.getIndent();
        auto       ended  = false;
        str.pushSlice();
        while (!str.finished() && !ended) {
            if (str.getIndent() == indent
                && (atConstructStart(str) || listAhead(str))) {
                ended = true;
            } else if (str.at('\n')) {
                str.next();
                if (str.finished()) {
                    ended = true;
                } else {
                    if (str.at(charsets::TextLineChars)) {
                    } else if (str.at('\n')) {
                        str.next();
                        ended = true;
                    } else {
                        throw str.makeUnexpected(
                            "text line character or newline",
                            R"(paragraph)");
                    }
                }
            } else {
                str.next();
            }
        }

        int endOffset = -1;
        if (ended) {
            // last trailing newline and pargraph separator newline
            if (!str.finished()) {
                if (atConstructStart(str)) {
                    endOffset = -1;
                } else {
                    endOffset = -3;
                }
            } else {
                endOffset = -2;
            }
        }

        const auto slice = str.popSlice(endOffset);
        push(Token(OTkText, slice.view));
    }

    void lexComment(PosStr& str) { push(str.tok(OTkComment, skipToEOL)); }
};
