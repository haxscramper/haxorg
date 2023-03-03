#include "OrgTokenizer.hpp"
#include <hstd/stdlib/algorithms.hpp>

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

#define __INIT_REPORT(__subname, __str)                                   \
    (Report{                                                              \
        .line     = __LINE__,                                             \
        .location = __CURRENT_FILE_PATH__,                                \
        .str      = &__str,                                               \
        .subname  = __subname,                                            \
    })

#define __trace2(__subname, __str)                                        \
    {                                                                     \
        Report rep = __INIT_REPORT(__subname, __str);                     \
        rep.kind   = ReportKind::Enter;                                   \
        rep.name   = __func__;                                            \
        report(rep);                                                      \
    }                                                                     \
                                                                          \
    finally CONCAT(close, __COUNTER__) = finally::init<Str>(              \
        ([&](CR<Str> name) {                                              \
            Report rep = __INIT_REPORT(__subname, __str);                 \
            rep.kind   = ReportKind::Leave;                               \
            rep.name   = name;                                            \
            report(rep);                                                  \
        }),                                                               \
        Str(__func__));


#define __push(token)                                                     \
    {                                                                     \
        Report rep = __INIT_REPORT(std::nullopt, str);                    \
        rep.kind   = ReportKind::Push;                                    \
        rep.tok    = token;                                               \
        auto id    = push(token);                                         \
        rep.id     = id;                                                  \
        report(rep);                                                      \
    }

#define __trace1(__subname) __trace2(__subname, str)
#define __trace0() __trace2(std::nullopt, str)

#define __trace(...)                                                      \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__trace, __VA_ARGS__)(__VA_ARGS__),             \
        BOOST_PP_EMPTY())

using ock = OrgCommandKind;
using otk = OrgTokenKind;

const auto commandNameMap = std::
    unordered_map<std::string, OrgCommandKind>{
        {"begin", ock::BeginDynamic},
        {"end", ock::EndDynamic},

        {"beginsrc", ock::BeginSrc},
        {"endsrc", ock::EndSrc},

        {"beginquote", ock::BeginQuote},
        {"endquote", ock::EndQuote},

        {"beginexample", ock::BeginExample},
        {"endexample", ock::EndExample},

        {"beginexport", ock::BeginExport},
        {"endexport", ock::EndExport},

        {"begintable", ock::BeginTable},
        {"endtable", ock::EndTable},

        {"begincenter", ock::BeginCenter},
        {"endcenter", ock::EndCenter},

        {"title", ock::Title},
        {"include", ock::Include},
        {"language", ock::Language},
        {"caption", ock::Caption},
        {"name", ock::Name},
        {"attrimg", ock::AttrImg},
        {"author", ock::Author},
        {"bind", ock::Bind},
        {"creator", ock::Creator},
        {"filetags", ock::Filetags},

        {"htmlhead", ock::HtmlHead},
        {"attrhtml", ock::AttrHtml},

        {"row", ock::Row},
        {"cell", ock::Cell},
        {"header", ock::Header},
        {"options", ock::Options},
        {"property", ock::Property},
        {"columns", ock::Columns},
        {"results", ock::Results},
        {"call", ock::Call},
        {"latexclass", ock::LatexClass},
        {"latexcompiler", ock::LatexCompiler},
        {"latexclassoptions", ock::LatexClassOptions},
        {"beginadmonition", ock::BeginAdmonition},
        {"endadmonition", ock::EndAdmonition},
        {"latexheader", ock::LatexHeader},
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
    slice('\x7F', high<char>())};


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
    {'*', {otk::BoldOpen, otk::BoldClose, otk::BoldInline}},
    {'/', {otk::ItalicOpen, otk::ItalicClose, otk::ItalicInline}},
    {'=', {otk::VerbatimOpen, otk::VerbatimClose, otk::VerbatimInline}},
    {'`', {otk::BacktickOpen, otk::BacktickClose, otk::BacktickInline}},
    {'~', {otk::MonospaceOpen, otk::MonospaceClose, otk::MonospaceInline}},
    {'_', {otk::UnderlineOpen, otk::UnderlineClose, otk::UnderlineInline}},
    {'+', {otk::StrikeOpen, otk::StrikeClose, otk::StrikeInline}},
    {'"', {otk::QuoteOpen, otk::QuoteClose, otk::None}},
}};


const CharSet ListStart = CharSet{'-', '+', '*'} + charsets::Digits
                        + charsets::AsciiLetters;

void OrgTokenizer::lexAngle(PosStr& str) {
    __trace();
    if (str.at("<%%")) {
        auto tok = str.tok(otk::DiaryTime, [](PosStr& str) {
            str.skip("<%%");
            skipBalancedSlice(
                str,
                {.openChars = CharSet{'('}, .closeChars = CharSet{')'}});
            str.skip(">");
        });
        __push(tok);
    } else if (str.at("<<<")) {
        __push((str.tok(otk::TripleAngleOpen, skipCount, 3)));
    } else if (str.at("<<")) {
        __push((str.tok(otk::DoubleAngleOpen, skipCount, 2)));
        __push((str.tok(otk::RawText, skipTo, '>')));
        __push((str.tok(otk::RawText, skipOne, ">>")));
    } else if (str.at(charsets::Digits, 1)) {
        auto skipAngles = [](PosStr& str) {
            str.skip('<');
            str.skipTo('>');
            str.skip('>');
        };

        __push((str.tok(otk::AngleTime, skipAngles)));

        if (str.at("--")) {
            __push((str.tok(otk::TimeDash, skipCount, 2)));
            __push((str.tok(otk::AngleTime, skipAngles)));
        }
    } else {
        __push((str.tok(otk::AngleOpen, skipCount, 1)));
        __push((str.tok(otk::RawText, skipTo, '>')));
        __push((str.tok(otk::AngleClose, skipOne, '>')));
    }
}

void OrgTokenizer::lexTime(PosStr& str) {
    __trace();
    if (str.at('<')) {
        lexAngle(str);
    } else if (str.at('[')) {
        auto skipBracket = [](PosStr& str) {
            str.skip('[');
            str.skipTo(']');
            str.skip(']');
        };

        __push((str.tok(otk::BracketTime, skipBracket)));
        if (str.at("--")) {
            __push((str.tok(otk::TimeDash, skipCount, 2)));
            __push((str.tok(otk::BracketTime, skipBracket)));
        }
    } else {
        throw str.makeUnexpected("'<' or '['", "time");
    }
}

void OrgTokenizer::lexLinkTarget(PosStr& str) {
    __trace();
    if (str.at("https") || str.at("http")) {
        assert(false && "FIXME");
    } else if (
        str.at("file") || str.at("attachment") || str.at("docview")
        || str.at('/') || str.at("./")) {

        if (str.at('.') || str.at('/')) {
            push(str.fakeTok(otk::LinkProtocol));
        } else {
            push(str.tok(otk::LinkProtocol, skipTo, ':'));
            str.skip(':');
        }

        push(str.tok(otk::LinkTarget, [](PosStr& str) {
            while (!str.finished() && !str.at("::")) {
                str.next();
            }
        }));

        if (str.at("::")) {
            push(str.tok(otk::LinkExtraSeparator, skipCount, 2));
            push(str.tok(otk::LinkExtra, skipPastEOF));
        }
    } else {
        if (str.hasAhead(':')) {
            push(str.tok(otk::LinkProtocol, skipTo, ':'));
            str.skip(':');
            push(str.tok(otk::LinkTarget, skipPastEOF));
        } else {
            push(str.tok(otk::LinkInternal, skipPastEOF));
        }
    }
}

void OrgTokenizer::lexBracket(PosStr& str) {
    __trace();
    if (str.at(R"([[)")) {
        push(str.tok(otk::LinkOpen, skipOne, '['));
        // link_token
        {
            push(str.tok(otk::LinkTargetOpen, skipOne, '['));
            PosStr target = str.slice(skipTo, ']');
            lexLinkTarget(target);
            push(str.tok(otk::LinkTargetClose, skipOne, ']'));
        };
        // description_token
        {
            if (str.at('[')) {
                push(str.tok(otk::LinkDescriptionOpen, skipOne, '['));
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

                push(str.tok(otk::LinkDescriptionClose, skipOne, ']'));
            }
        }
        push(str.tok(otk::LinkClose, skipOne, ']'));
    } else if (str.at(R"([fn:)")) {
        push(str.tok(otk::FootnoteStart, skipOne, "[fn"));
        if (str.at(R"(::)")) {
            push(str.tok(otk::DoubleColon, skipOne, R"(::)"));
            // FIXME
            // result.addExpandTok(str, otk::Text, str.skipTo(']'););
        } else {
            push(str.tok(otk::Colon, skipOne, ':'));
            push(str.tok(otk::Ident, skipTo, ']'));
        }
        push(str.tok(otk::FootnoteEnd, skipOne, ']'));
    } else {
        // FIXME
        // push(trySpecific(str, otk::Punctuation, 1, lexTime));
    }
}

void OrgTokenizer::lexTextChars(PosStr& str) {
    __trace();
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
            buf.push_back(str.tok(otk::SrcOpen, skipOne, "src"));
            if (str.at(CharSet{'_', '-'})) {
                str.next();
            }
        }

        if (str.at(charsets::IdentStartChars)) {
            // FIXME push buffer only if the whole sequence is
            // determined to be a valid structure
            push(buf);
            push(str.tok(
                otk::SrcName, skipZeroOrMore, charsets::IdentChars));
            if (str.at('[')) {
                push(str.tok(otk::SrcArgs, skipBrace, {1, -2}));
            }

            push(str.tok(otk::SrcBody, skipCurly, {1, -2}));
            push(str.fakeTok(otk::SrcClose));
            isStructure = true;
        } else {
            str.setPos(pos);
        }

    } else if (str.at("call[_-]?\\w+(\\[|\\{)")) {
        const auto    pos = str.getPos();
        Vec<OrgToken> buf;
        buf.push_back(str.tok(otk::CallOpen, skipOne, "call"));
        if (str.at(CharSet{'_', '-'})) {
            str.next();
        }
        if (str.at(charsets::IdentStartChars)) {
            push(buf);
            push(str.tok(
                otk::SrcName, skipZeroOrMore, charsets::IdentChars));
            if (str.at('[')) {
                push(str.tok(otk::CallInsideHeader, skipBrace, {1, -2}));
            };
            push(str.tok(otk::CallArgs, skipParen, {1, -2}));
            push(str.fakeTok(otk::CallClose));
            isStructure = true;
        } else {
            str.setPos(pos);
        }
    } else if (str.at("https://") || str.at("http://")) {
        push(str.tok(otk::RawUrl, skipBefore, charsets::Whitespace));
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
        push(str.popTok(allUp ? otk::BigIdent : otk::Word));
    }
}

void OrgTokenizer::lexParenArguments(PosStr& str) {
    __trace();
    push(str.tok(otk::ParOpen, skipOne, '('));
    while (!str.at(')')) {
        push(str.tok(otk::RawText, skipBefore, cr(CharSet{',', ')'})));
        if (str.at(',')) {
            push(str.tok(otk::Comma, skipOne, ','));
        }
        str.space();
    }
    push(str.tok(otk::ParOpen, skipOne, ')'));
}

void OrgTokenizer::lexText(PosStr& str) {
    __trace();
    const auto NonText = charsets::TextLineChars - charsets::AsciiLetters
                       - charsets::Utf8Any + CharSet{'\n', '/'};

    switch (str.get()) {
        case '\n': {
            push(str.tok(otk::Newline, skipCount, 1));
            break;
        }
        case ' ': {
            push(str.tok(otk::Space, [](PosStr& str) {
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
                result.push_back(str.tok(otk::HashTag, [](PosStr& str) {
                    str.trySkip('#');
                    str.skipZeroOrMore(charsets::IdentChars);
                }));

                while (str.at(R"(##)") && !str.at(R"(##[)")) {
                    result.push_back(
                        str.tok(otk::HashTagSub, skipOne, '#'));
                    result.push_back(
                        str.tok(otk::HashTag, [](PosStr& str) {
                            str.skip('#');
                            str.skipZeroOrMore(charsets::IdentChars);
                        }));
                }

                if (str.at(R"(##[)")) {
                    result.push_back(
                        str.tok(otk::HashTagSub, skipOne, '#'));
                    result.push_back(
                        str.tok(otk::HashTagOpen, skipOne, "#["));

                    while (!str.finished() && !str.at(']')) {
                        result.append(rec(str));
                        str.space();
                        if (str.at(',')) {
                            result.push_back(
                                str.tok(otk::Comma, skipOne, ','));
                            str.space();
                        }
                    }
                    result.push_back(
                        str.tok(otk::HashTagClose, skipOne, ']'));
                }
                return result;
            };

            push(rec(str));
            break;
        }
        case '@': {
            const auto AtChars = charsets::IdentChars + charsets::Utf8Any;
            if (str.at(AtChars, 1)) {
                push(str.tok(otk::AtMention, [&AtChars](PosStr& str) {
                    str.skip('@');
                    str.skipZeroOrMore(AtChars);
                }));
            } else {
                push(str.tok(otk::Punctuation, skipCount, 1));
            }
            break;
        }
        case '$': {
            auto          tmp = str;
            Vec<OrgToken> buf;
            try {
                if (tmp.at('$', 1)) {
                    buf.push_back(tmp.tok(otk::DollarOpen, skipOne, "$$"));
                    tmp.pushSlice();
                    bool hasEnd = false;
                    while (!tmp.finished() && !hasEnd) {
                        while (!tmp.finished() && !tmp.at('$')) {
                            tmp.next();
                        }
                        if (tmp.at("$$")) {
                            buf.push_back(tmp.popTok(otk::LatexInlineRaw));
                            hasEnd = true;
                        } else {
                            throw ImplementError();
                        }
                    }
                    // FIXME
                    // buf.add(tmp.tok(skip otk::DollarClose, '$', '$'));
                } else {
                    buf.push_back(tmp.tok(otk::DollarOpen, skipOne, '$'));
                    buf.push_back(
                        tmp.tok(otk::LatexInlineRaw, skipBefore, '$'));
                    buf.push_back(tmp.tok(otk::DollarClose, skipOne, '$'));
                }
                push(buf);
                str = tmp;
            } catch (UnexpectedCharError& err) {
                push(str.tok(otk::Punctuation, skipZeroOrMore, '$'));
            }
            break;
        }
        case '\\': {
            switch (str.get(1)) {
                case '[':
                case '(': {
                    const auto isInline = str.at('(', 1);
                    if (isInline) {
                        push(
                            str.tok(otk::LatexParOpen, skipOne, R"(\\()"));
                    } else {
                        push(str.tok(
                            otk::LatexBraceOpen, skipOne, R"(\\[)"));
                    }
                    push(str.tok(
                        otk::LatexInlineRaw, [&isInline](PosStr& str) {
                            while (
                                !str.at(isInline ? R"(\\))" : R"(\\])")) {
                                str.next();
                            }
                        }));
                    if (isInline) {
                        push(str.tok(otk::LatexParClose, skipOne, ")"));
                    } else {
                        push(str.tok(otk::LatexBraceClose, skipOne, "]"));
                    }
                    break;
                }
                case '\\': {
                    push(str.tok(otk::DoubleSlash, skipOne, R"(\\)"));
                    break;
                }
                default: {
                    if (str.at(OMarkupChars, 1)) {
                        push(str.tok(otk::Escaped, skipCount, 1));
                    } else if (str.at(
                                   charsets::IdentStartChars
                                       - CharSet{'_'},
                                   1)) {
                        push(str.tok(otk::SymbolStart, skipOne, '\\'));
                        push(str.tok(
                            otk::Ident,
                            skipZeroOrMore,
                            charsets::IdentChars));
                        if (str.at('[')) {
                            push(
                                str.tok(otk::MetaBraceOpen, skipOne, '['));
                            push(str.tok(
                                otk::MetaBraceBody, [](PosStr& str) {
                                    skipBalancedSlice(
                                        str,
                                        {.openChars    = {'['},
                                         .closeChars   = {']'},
                                         .skippedStart = true,
                                         .consumeLast  = false});
                                }));
                            push(str.tok(
                                otk::MetaBraceClose, skipOne, ']'));
                        }
                        while (str.at('{')) {
                            push(str.tok(otk::MetaArgsOpen, skipOne, '{'));
                            push(str.tok(
                                otk::MetaBraceBody, [](PosStr& str) {
                                    skipBalancedSlice(
                                        str,
                                        {.openChars    = {'{'},
                                         .closeChars   = {'}'},
                                         .skippedStart = true,
                                         .consumeLast  = false});
                                }));

                            push(
                                str.tok(otk::MetaArgsClose, skipOne, '}'));
                        }
                        break;
                    } else {
                        push(str.tok(otk::Escaped, skipCount, 2));
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
                push(
                    str.tok(markupConfig[start].inlineKind, skipCount, 2));
                push(str.tok(otk::RawText, [start](PosStr& str) {
                    while (!str.at(start, start)) {
                        str.next();
                    }
                }));
                push(
                    str.tok(markupConfig[start].inlineKind, skipCount, 2));
            } else {
                if (str.at(NonText, -1) || str.atStart()) {
                    push(str.tok(
                        markupConfig[start].startKind, skipCount, 1));
                    push(str.tok(otk::RawText, skipTo, start));
                    if (str.at(NonText, 1) || str.beforeEnd()) {
                        push(str.tok(
                            markupConfig[start].finishKind, skipCount, 1));
                    }
                } else {
                    push(str.tok(otk::Punctuation, skipCount, 1));
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
                push(str.tok(otk::Punctuation, skipCount, 1));
            }
            break;
        }

        case '[': {
            lexBracket(str);
            break;
        }
        case '(': {
            push(str.tok(otk::ParOpen, skipCount, 1));
            break;
        }
        case ')': {
            push(str.tok(otk::ParClose, skipCount, 1));
            break;
        }
        case ':': {
            push(str.tok(otk::Colon, skipCount, 1));
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
            push(str.tok(otk::Punctuation, skipCount, 1));
            break;
        }
        case '{': {
            if (str.at("{{{")) {
                push(str.tok(otk::MacroOpen, skipCount, 3));
                push(str.tok(otk::Ident, [](PosStr& str) {
                    while (!str.finished() && !str.at('(')
                           && !str.at("}}}")) {
                        str.next();
                    }
                }));

                if (str.at('(')) {
                    lexParenArguments(str);
                }
                if (!str.finished()) {
                    push(str.tok(otk::MacroOpen, skipOne, "}}}"));
                }
            } else {
                push(str.tok(otk::MaybeWord, skipCount, 1));
            }
            break;
        }
        case '^': {
            push(str.tok(otk::Circumflex, skipCount, 1));
            break;
        }
        default: {
            if (str.at(charsets::TextChars)) {
                lexTextChars(str);
            } else if (str.at(markupKeys - CharSet{'<', '~', '`', '='})) {
                const auto ch                        = str.get();
                const auto& [kOpen, kClose, kInline] = markupConfig[ch];
                if (str.at((+(1)), ch)) {
                    push(str.tok(kInline, skipCount, 2));
                } else if (str.at(NonText, -1) || str.atStart()) {
                    push(str.tok(kOpen, skipCount, 1));
                } else if (str.at(NonText, 1) || str.beforeEnd()) {
                    push(str.tok(kClose, skipCount, 1));
                } else {
                    push(str.tok(otk::Word, skipCount, 1));
                }
                break;
            } else {
                throw str.makeUnexpected("any text character", "text");
            }
        }
    }
}

void OrgTokenizer::lexProperties(PosStr& str) {
    __trace();
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
            push(Token(otk::ColonEnd, id.view));
        } else {
            push(Token(
                isAdd ? otk::ColonAddIdent : otk::ColonIdent, id.view));
            if (str.at(charsets::IdentStartChars)) {
                push(str.tok(otk::Ident, [](PosStr& str) {
                    while (!str.finished()
                           && str.at(
                               charsets::DashIdentChars + CharSet{'/'})) {
                        str.next();
                    }
                }));
                str.skip(':');
            }
            str.space();
            push(str.tok(otk::RawProperty, skipToEOL));
            str.skip('\n');
        }
    }
}

void OrgTokenizer::lexDescription(PosStr& str) {
    __trace();
    str.pushSlice();
    auto hasEnd = false;
    while (!str.finished() && !hasEnd) {
        while (!str.finished() && !str.at(":end:")) {
            str.next();
        }
        push(Token(otk::Text, str.popSlice().view));
        const auto id = str.slice([](PosStr& str) {
            str.skip(':');
            str.skipZeroOrMore(charsets::IdentChars);
            str.skip(':');
        });
        push(Token(otk::ColonEnd, id.view));
        hasEnd = true;
    }
}

void OrgTokenizer::lexLogbook(PosStr& str) {
    __trace();
    str.pushSlice();
    auto hasEnd = false;
    while (!str.finished() && !hasEnd) {
        while (!str.finished() && !str.at(":end:")) {
            str.next();
        }

        push(Token(otk::RawLogbook, str.popSlice().view));

        const auto id = str.slice([](PosStr& str) {
            str.skip(':');
            str.skipZeroOrMore(charsets::IdentChars);
            str.skip(':');
        });

        push(Token(otk::ColonEnd, id.view));
        hasEnd = true;
    };
}

void OrgTokenizer::lexDrawer(PosStr& str) {
    __trace();
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
            push(Token(otk::ColonProperties, id.view));
            lexProperties(str);
        } else if (norm == ":logbook:") {
            push(Token(otk::ColonLogbook, id.view));
            lexLogbook(str);
        } else if (norm == ":description:") {
            push(Token(otk::ColonDescription, id.view));
            lexDescription(str);
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

void OrgTokenizer::lexSubtreeTodo(PosStr& str) {
    __trace();
    auto tmp = str;
    tmp.pushSlice();
    tmp.skipZeroOrMore(charsets::HighAsciiLetters);
    if (tmp.at(' ')) {
        push(tmp.popTok(otk::SubtreeTodoState));
        str = tmp;
    }
}

void OrgTokenizer::lexSubtreeUrgency(PosStr& str) {
    __trace();
    if (str.at("[#")) {
        str.pushSlice();
        str.next(2);
        str.skip(charsets::HighAsciiLetters);
        str.skipZeroOrMore(charsets::HighAsciiLetters);
        str.skip(']');
        push(str.popTok(otk::SubtreeUrgency));
        str.space();
    }
}

void OrgTokenizer::lexSubtreeTitle(PosStr& str) {
    __trace();
    auto          body = str.slice(skipToEOL);
    Vec<OrgToken> headerTokens;
    body.skipToEOF();
    if (body.at(':')) {
        body.back();
        auto tagEnded = false;
        while (!body.finished() && !tagEnded) {
            const auto finish = body.getPos();
            while (!body.finished()
                   && !body.at(charsets::IdentChars + CharSet{'#', '@'})) {
                body.back();
            }

            const auto start = body.getPos() + 1;
            body.skip(':', -1);
            headerTokens.push_back(Token(
                otk::SubtreeTag, body.sliceBetween(start, finish).view));
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
                otk::SubtreeCompletion,
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
        headerTokens.push_back(Token(otk::Text, slice.view));
    }
    push(reversed(headerTokens));
}

void OrgTokenizer::lexSubtreeTimes(PosStr& str) {
    __trace();
    str.space();
    auto hadTimes = false;
    while (str.at(charsets::HighAsciiLetters)) {
        hadTimes   = true;
        auto times = str;
        times.space();
        const auto tag = times.slice(
            skipZeroOrMore, charsets::HighAsciiLetters);

        if (Vec<Str>{R"(deadline)", R"(closed)", R"(scheduled)"}.contains(
                normalize(tag.toStr()))) {
            push(Token(otk::SubtreeTime, tag.view));
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

void OrgTokenizer::lexSubtree(PosStr& str) {
    __trace();
    push(str.tok(otk::SubtreeStars, skipZeroOrMore, '*'));
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

void OrgTokenizer::lexSourceBlockContent(PosStr& str) {
    __trace();
    while (!str.finished()) {
        if (str.at(R"(<<)")) {
            auto          failedAt = -1;
            auto          tmp      = str;
            Vec<OrgToken> tmpRes;
            // try_tangle
            {
                tmpRes.push_back(
                    tmp.tok(otk::DoubleAngleOpen, skipOne, R"(<<)"));
                if (tmp.at(charsets::IdentChars)) {
                    tmpRes.push_back(tmp.tok(
                        otk::Ident, skipZeroOrMore, charsets::IdentChars));
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
                        tmp.tok(otk::DoubleAngleClose, skipOne, ">>"));
                } else {
                    failedAt = tmp.pos;
                    break;
                }
            }
            if (failedAt != -1) {
                push(str.tok(otk::CodeText, [&failedAt](PosStr& str) {
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
            push(str.tok(otk::ParOpen, skipOne, '('));
            push(str.tok(otk::Ident, skipOne, "refs"));
            push(str.tok(otk::Colon, skipOne, ":"));
            push(str.tok(
                otk::Ident,
                skipZeroOrMore,
                cr(charsets::IdentChars + CharSet{'-'})));
            push(str.tok(otk::ParClose, skipOne, ')'));

        } else if (str.at('\n')) {
            push(str.tok(otk::Newline, skipCount, 1));
        } else {
            push(str.tok(otk::CodeText, [](PosStr& str) {
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

void OrgTokenizer::lexCommandContent(
    PosStr&               str,
    const OrgCommandKind& kind) {
    __trace();
    push(str.fakeTok(otk::CommandContentStart));
    switch (kind) {
        case ock::BeginQuote:
        case ock::BeginCenter:
        case ock::BeginAdmonition: {
            push(str.tok(otk::Text, skipPastEOF));
            break;
        }
        case ock::BeginExample: {
            push(str.tok(otk::RawText, skipPastEOF));
            break;
        }
        case ock::BeginDynamic: {
            str.space();
            push(str.tok(otk::Text, skipPastEOF));
            break;
        }
        case ock::BeginSrc: {
            str.space();
            push(str.fakeTok(otk::CodeContentBegin));
            Vec<OrgToken> code;
            setBuffer(&code);
            {
                lexSourceBlockContent(str);
                if (code.back().kind == otk::CodeText
                    && all_of(code.back().text, [](char c) {
                           return c == ' ';
                       })) {
                    code.pop_back();
                }
                if (code.back().kind == otk::Newline) {
                    code.pop_back();
                }
                push(code);
                push(str.fakeTok(otk::CodeContentEnd));
            }
            clearBuffer();
            break;
        }
        default: {
            assert(false && "IMPLEMENT");
        }
    };
    push(str.fakeTok(otk::CommandContentEnd));
}

Vec<OrgToken> OrgTokenizer::lexDelimited(
    PosStr&                         str,
    const Pair<char, OrgTokenKind>& start,
    const Pair<char, OrgTokenKind>& finish,
    const OrgTokenKind&             middle) {
    __trace();
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

void OrgTokenizer::lexCommandArguments(
    PosStr&               str,
    const OrgCommandKind& kind) {
    __trace();
    OrgTokenKind wrapStart = otk::CommandArgumentsBegin;
    OrgTokenKind wrapEnd   = otk::CommandArgumentsEnd;
    switch (kind) {
        case ock::Title:
        case ock::Caption:
            wrapStart = otk::ParagraphStart;
            wrapEnd   = otk::ParagraphEnd;
    }

    push(str.fakeTok(wrapStart));
    std::function<void(PosStr&)> lexKeyValue;
    lexKeyValue = [this](PosStr& str) {
        while (!str.finished()) {
            switch ((str.get())) {
                case '-': {
                    push(str.tok(
                        otk::CommandFlag,
                        skipZeroOrMore,
                        cr(CharSet{'-'} + charsets::IdentChars)));
                    break;
                }
                case ':': {
                    push(str.tok(
                        otk::CommandKey,
                        skipZeroOrMore,
                        cr(charsets::IdentChars + CharSet{'-', ':'})));
                    break;
                }
                case ' ': {
                    str.space();
                    break;
                }
                default: {
                    push(str.tok(otk::CommandValue, [](PosStr& str) {
                        auto hasColon = false;
                        while (!str.finished() && !hasColon) {
                            while (!str.finished()
                                   && !str.at(charsets::HorizontalSpace)) {
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
        case ock::BeginQuote: {
            break;
        }
        case ock::Title: {
            while (!str.finished()) {
                lexText(str);
            }
            break;
        }
        case ock::Options: {
            while (!str.finished()) {
                switch (str.get()) {
                    case '\'':
                    case '*':
                    case '|':
                    case ':':
                    case '<':
                    case '\n':
                    case '^': {
                        push(str.tok(otk::RawText, skipCount, 1));
                        break;
                    }
                    case ' ': {
                        str.space();
                        break;
                    }
                    default: {
                        push(str.tok(otk::RawText, [](PosStr& str) {
                            while (!str.finished()
                                   && !str.at(charsets::HorizontalSpace)) {
                                str.next();
                            }
                        }));
                    }
                }
            }
            break;
        }
        case ock::Caption: {
            push(str.tok(otk::Text, skipPastEOF));
            break;
        }
        case ock::Call: {
            str.space();
            push(str.tok(
                otk::CallName, skipZeroOrMore, charsets::IdentChars));
            if (str.at('[')) {
                push(str.tok(
                    otk::CallInsideHeader, skipBalancedSlice, '[', ']'));
            }

            push(str.tok(otk::CallArgs, skipBalancedSlice, '(', ')'));
            if (!str.finished()) {
                push(str.tok(otk::RawText, skipPastEOF));
            }
            break;
        }
        case ock::BeginSrc: {
            push(str.tok(otk::Word, skipZeroOrMore, charsets::IdentChars));
            str.space();
            lexKeyValue(str);
            break;
        }
        case ock::BeginTable:
        case ock::AttrHtml: {
            lexKeyValue(str);
            break;
        }
        case ock::BeginDynamic: {
            push(str.tok(otk::Word, skipZeroOrMore, charsets::IdentChars));
            str.space();
            lexKeyValue(str);
            break;
        }
        case ock::Header: {
            str.space();
            lexKeyValue(str);
            break;
        }
        case ock::Author:
        case ock::Creator:
        case ock::Language: {
            str.space();
            push(str.tok(otk::RawText, skipPastEOF));
            break;
        }
        case ock::Property: {
            str.space();
            push(str.tok(otk::Ident, skipBefore, cr(CharSet{' ', ':'})));
            if (str.at(':')) {
                push(str.tok(otk::Colon, skipCount, 1));
                push(str.tok(otk::Ident, skipBefore, ' '));
            }
            str.space();
            push(str.tok(otk::RawProperty, skipPastEOF));
            break;
        }
        case ock::Filetags: {
            while (str.at(':')) {
                str.skip(':');
                if (!str.finished()) {
                    push(str.tok(otk::SubtreeTag, [](PosStr& str) {
                        while (!str.finished() && !str.at(':')) {
                            str.next();
                        }
                    }));
                }
            }
            break;
        }
        case ock::Include: {
            str.space();
            if (str.at('"')) {
                lexDelimited(
                    str,
                    {'"', otk::QuoteOpen},
                    {'"', otk::QuoteClose},
                    otk::RawText);
            } else {
                push(str.tok(otk::RawText, [](PosStr& str) {
                    while (!str.finished()
                           && !str.at(charsets::HorizontalSpace)) {
                        str.next();
                    }
                }));
            }
            lexKeyValue(str);
            break;
        }
        case ock::Name:
        case ock::LatexClass:
        case ock::LatexCompiler:
        case ock::BeginAdmonition: {
            str.space();
            push(str.tok(otk::Ident, skipPastEOF));
            break;
        }
        case ock::Columns:
        case ock::BeginExample:
        case ock::Results:
        case ock::LatexHeader:
        case ock::HtmlHead:
        case ock::BeginCenter:
        case ock::LatexClassOptions: {
            push(str.tok(otk::RawText, skipPastEOF));
            break;
        }
        default: {
            assert(false);
            // throw newUnexpectedKindError(kind, toStr(str));
            push(str.tok(otk::RawText, skipPastEOF));
        }
    }

    push(str.fakeTok(wrapEnd));
}

void OrgTokenizer::lexCommandBlock(PosStr& str) {
    __trace();
    const auto column = str.getColumn();
    push(str.tok(otk::CommandPrefix, skipOne, "#+"));
    const auto id = str.slice(skipZeroOrMore, OCommandChars);
    if (normalize(id.toStr()).startsWith("begin")) {
        push(Token(otk::CommandBegin, id.view));
        const auto sectionName = normalize(id.toStr()).dropPrefix("begin");
        const auto kind        = classifyCommand(id.toStr());
        if (kind == ock::BeginDynamic) {
            str.skip(':');
        }
        str.space();
        auto arguments = str.slice({0, -2}, skipPastEOL);
        lexCommandArguments(arguments, kind);
        auto found = false;
        str.pushSlice();
        while (!found && !str.finished()) {
            while (!str.finished()
                   && !(str.getColumn() == column && str.at(R"(#+)"))) {
                str.next();
            }
            assert(!str.finished());
            const auto   prefix = str.slice(skipCount, 2);
            const PosStr id     = str.slice(skipZeroOrMore, OCommandChars);
            if (normalize(id.toStr()) == "end" + sectionName) {
                found      = true;
                auto slice = str.popSlice((-((((1 + id.size()) + (3))))));
                lexCommandContent(slice, kind);
                push(Token(otk::CommandPrefix, prefix.view));
                push(Token(otk::CommandEnd, id.view));
            }
        }
        if (kind == ock::BeginDynamic) {
            str.skip(':');
        }
    } else {
        push(Token(otk::LineCommand, id.view));
        push(str.tok(otk::Colon, skipOne, ':'));
        str.space();
        auto args = str.slice(skipToEOL);
        lexCommandArguments(args, classifyCommand(id.toStr()));
        if (!str.finished()) {
            str.skip('\n');
        }
    }
}

bool OrgTokenizer::isFirstOnLine(CR<PosStr> str) {
    const auto set = charsets::Newline + CharSet{'\0'};
    auto       os  = getStream();
    if (str.at(set, -1)) {
        // str.print(os);
        return true;
    }

    auto pos = 0;
    while (str.at(charsets::HorizontalSpace, pos)) {
        // str.print(os, {.startOffset = pos});
        --pos;
    }
    return str.at(set, pos);
}

bool OrgTokenizer::atLogClock(CR<PosStr> str) {
    PosStr     tmp   = str;
    const auto ahead = tmp.slice(skipTo, '[');
    const auto space = ahead.getSkip('C');
    if (0 <= space) {
        for (const auto ch : ahead[slice(0, space - 1)].view) {
            if (ch != ' ') {
                return false;
            }
        }

        return ahead[slice(space, 1_B)].at("CLOCK:::");
    } else {
        return false;
    }
}

bool OrgTokenizer::atConstructStart(CR<PosStr> str) {
    if (!isFirstOnLine(str)) {
        return false;
    } else if (str.getIndent() == 0 && str.at('*')) {
        auto shift = 0;
        while (str.at('*', shift)) {
            ++shift;
        }
        return str.at(' ', shift);
    } else {
        return str.at("#+") || str.at("---");
    }
}

void OrgTokenizer::skipIndents(LexerStateSimple& state, PosStr& str) {
    using LK           = LexerStateSimple::LexerIndentKind;
    const auto skipped = state.skipIndent(str);
    for (const auto indent : skipped) {
        switch (indent) {
            case LK::likIncIndent: {
                push(str.fakeTok(otk::Indent));
                break;
            }
            case LK::likDecIndent: {
                push(str.fakeTok(otk::Dedent));
                break;
            }
            case LK::likSameIndent: {
                push(str.fakeTok(otk::SameIndent));
                break;
            }
            case LK::likNoIndent: {
                push(str.fakeTok(otk::NoIndent));
                break;
            }
            case LK::likEmptyLine: {
                assert(false);
                break;
            }
        }
    }
}

bool OrgTokenizer::atListStart(CR<PosStr> tmp) {
    auto          str = tmp;
    Vec<OrgToken> result;
    if (atConstructStart(str)) {
        return false;
    } else if (
        str.at(CharSet{'-', '+'})
        || (0 < str.getIndent() && str.at('*'))) {
        str.skip(ListStart);
        return str.at(' ');
    } else if (str.at(charsets::Digits + charsets::AsciiLetters)) {
        str.tok(otk::ListItemStart, [](PosStr& str) {
            if (str.at(charsets::Digits + charsets::AsciiLetters)) {
                str.next();
            } else {
                return;
            }
        });

        return str.at(')') || str.at('.');
    } else {
        if (str.at(CharSet{'-', '+', '*'})) {
            str.next();
        } else {
            return false;
        }

        return str.at(' ');
    }
}

/// REFACTOR don't mutate argument string, offload this to the proper
/// parsing procedure
bool OrgTokenizer::atListAhead(CR<PosStr> str) {
    if (!isFirstOnLine(str)) {
        return false;
    } else {
        auto tmp = str;
        tmp.space();
        return atListStart(tmp);
    }
}

void OrgTokenizer::lexListBullet(
    PosStr&           str,
    int               indent,
    LexerStateSimple& state) {
    __trace();
    if (str.at(CharSet{'-', '+'})
        || (0 < str.getIndent() && str.at('*'))) {
        __trace("At bullet list start");
        auto tok = str.tok(
            otk::ListItemStart, skipOne, cr(CharSet{'-', '+', '*'}));
        __push(tok);
        str.space();
    } else {
        __trace("At numbered list start");
        __push((str.tok(
            otk::ListStart,
            skipOne,
            cr(charsets::Digits + charsets::AsciiLetters))));

        str.skip(cr(CharSet{')', '.'}));
        str.space();
    }

    if (str.at("\\[[Xx - ]\\]")) {
        __push((str.tok(otk::Checkbox, [](PosStr& str) {
            str.skip('[');
            str.skip(CharSet{'X', 'x', ' ', '-'});
            str.skip(']');
        })));

        str.space();
    }
}

void OrgTokenizer::lexListDescription(
    PosStr&           str,
    int               indent,
    LexerStateSimple& state) {
    __trace("Try parsing list header");
    auto tmp = str;
    auto buf = Vec<OrgToken>{
        tmp.fakeTok(otk::ListDescOpen), tmp.fakeTok(otk::ParagraphStart)};

    while (!tmp.finished() && !tmp.at(charsets::Newline)) {
        if (tmp.at(':') && tmp.at("::")) {
            buf.push_back(tmp.fakeTok(otk::ParagraphEnd));
            buf.push_back(tmp.fakeTok(otk::ListDescClose));
            buf.push_back(tmp.tok(otk::DoubleColon, skipOne, "::"));
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

PosStr OrgTokenizer::popListBody(
    PosStr&           str,
    int               indent,
    LexerStateSimple& state) {
    __trace("List body");
    str.pushSlice();
    auto atEnd = false;
    // extend slice until new list start is not found - either via new
    // nested item or by indentation decrease.
    while (!str.finished() && !atEnd) {
        if (atLogClock(str)) {
            // Special handlig of `CLOCK:` entries in the subtree
            // logging drawer to make sure the content is skipped in
            // the right place.

            str.next();
            atEnd = true;
        } else if (atConstructStart(str) && (str.getIndent() <= indent)) {
            // If we are at the language construct start and it is
            // placed at the same level as prefix dash, treat it as
            // list end
            atEnd = true;
        } else if (atListAhead(str)) {
            // check if we are at the start of the new list - if we
            // are, stop parsing completely and apply all withheld
            // lexer changes, otherwise don't touch `atEnd` in order to
            // continue parsing.
            atEnd = true;
        } else {
            {
                // Two empty lines after list items should be treated
                // as list separator.
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
                // go to the start of the next line
                testIndent.skipPastEOL();
                while (testIndent.trySkipEmptyLine()) {}
                // Decide based on the indentation what to do next
                // indentation decreased, end of the list item
                if (testIndent.getIndent() < indent) {
                    atEnd = true;
                    // Non-list content that matches indentation of the
                    // current list item start.
                } else if (
                    testIndent.getIndent() == indent
                    && !atListAhead(str)) {
                    atEnd = true;
                }
                str.skipPastEOL();
            }
        }
    }

    return str.popSlice();
}


void OrgTokenizer::lexListItem(
    PosStr&           str,
    const int&        indent,
    LexerStateSimple& state) {
    __trace();
    lexListBullet(str, indent, state);
    lexListDescription(str, indent, state);

    auto slice = popListBody(str, indent, state);
    while (str.view.at(slice.view.size()) == '\n') {
        slice.view.remove_suffix(1);
    }

    auto token = Token(otk::StmtList, slice.view);
    pushResolved(token);
    __push(str.fakeTok(otk::ListItemEnd));
}

void OrgTokenizer::lexListItems(PosStr& str, LexerStateSimple& state) {
    __trace();
    assert(!str.at('\n'));
    while (atListAhead(str) || atLogClock(str)) {
        assert(!str.at('\n'));
        if (atLogClock(str)) {
            __trace("Lex log clock list");
            __push(str.fakeTok(otk::ListClock));
            str.pushSlice();
            str.skipToEOL();
            auto slice = str.popSlice();
            lexParagraph(slice);
            str.next();
            __push(str.fakeTok(otk::ListItemEnd));
        } else {
            skipIndents(state, str);
            const auto indent = str.getColumn();
            if (atListStart(str)) {
                __trace("Lexing nested list item");
                lexListItem(str, indent, state);
            } else {
                __trace("Lexing paragraph content");
                lexParagraph(str);
            }
        }
    }
    str.skipToEOL();
}

void OrgTokenizer::lexList(PosStr& str) {
    __trace();
    LexerStateSimple state{};
    __push(str.fakeTok(otk::ListStart));
    Vec<OrgToken> tokens;
    setBuffer(&tokens);
    lexListItems(str, state);
    clearBuffer();

    if (tokens[0].kind != otk::SameIndent) {
        __push(tokens[0]);
    }

    for (const auto& tok : tokens[slice(1, 1_B)]) {
        __push(tok);
    }

    while (state.hasIndent()) {
        state.popIndent();
        __push(str.fakeTok(otk::Dedent));
    }
    __push(str.fakeTok(otk::ListEnd));
}

void OrgTokenizer::lexParagraph(PosStr& str) {
    __trace();
    // Pick out large standalone paragraph block
    const auto indent = str.getIndent();
    auto       ended  = false;
    str.pushSlice();
    while (!str.finished() && !ended) {
        __trace(
            ("Lexer iteration, get indent: $#, current indent $#, at "
             "construct $#, at list $#, is first on line $#"
             % to_string_vec(
                 str.getIndent(),
                 indent,
                 atConstructStart(str),
                 atListAhead(str),
                 isFirstOnLine(str))));
        if (str.getIndent() == indent
            && (atConstructStart(str) || atListAhead(str))) {
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
                        "text line character or newline", R"(paragraph)");
                }
            }
        } else {
            str.next();
        }
    }

    int paragraphEndOffset = str.finished() ? 0 : -1;
    if (ended) {
        // last trailing newline and pargraph separator newline
        if (!str.finished()) {
            if (atConstructStart(str)) {
                paragraphEndOffset = -1;
            } else {
                paragraphEndOffset = -3;
            }
        } else {
            paragraphEndOffset = -2;
        }
    }
    paragraphEndOffset = 0;

    auto recTok = str.popTok(
        otk::Text, PosStr::Offset(0, paragraphEndOffset));
    // Put it for the recursive processing
    pushResolved(recTok);
}

void OrgTokenizer::lexTableState(
    PosStr&                         str,
    LexerState<OrgBlockLexerState>& state) {
    __trace();
    switch (str.at(0)) {
        case '#': {
            auto pos        = str.getPos();
            bool isTableCmd = true;
            str.next();
            if (str.at('+')) {
                str.skip('+');
                auto tmp = str.tok(
                    otk::TableBegin, skipOneOrMore, OCommandChars);
                auto kind = classifyCommand(tmp.strVal());
                switch (kind) {
                    case ock::BeginTable:
                        tmp.kind = otk::TableBegin;
                        break;
                    case ock::Row: tmp.kind = otk::RowSpec; break;
                    case ock::Cell: tmp.kind = otk::CellSpec; break;
                    case ock::EndTable: tmp.kind = otk::TableEnd; break;
                    default: isTableCmd = false; break;
                }
                if (isTableCmd) {
                    state.toFlag(OrgBlockLexerState::InHeader);
                    str.space();
                    if (!str.finished()) {
                        if (at(back()).kind == otk::TableEnd) {
                            state.toFlag(OrgBlockLexerState::Complete);
                        } else {
                            __push(
                                str.tok(otk::CmdArguments, skipTo, '\n'));
                            if (!str.finished()) {
                                str.skip('\n');
                                state.toFlag(OrgBlockLexerState::InBody);
                            }
                        }
                    }
                } else {
                    str.setPos(pos);
                    __push(str.tok(otk::Content, skipPastEOL));
                }
                break;
            }
        }
        case '|': {
            auto pos = str.getPos();
            str.skipBeforeEOL();
            if (str.at('|')) {
                str.setPos(pos);
                bool first = true;
                while (!str.finished() && str.at('|')) {
                    __push((str.tok(
                        first ? otk::PipeOpen : otk::PipeSeparator,
                        skipOne,
                        '|')));

                    first = false;
                    str.space();
                    if (!str.finished() && !str.at('\n')) {
                        __push((str.tok(otk::Content, [](PosStr& str) {
                            str.skipBefore(CharSet{'|', '\n'});
                            if (str.at(' ')) {
                                while (str.at(' ')) {
                                    str.back();
                                }
                                if (!str.at(' ')) {
                                    str.next();
                                }
                            } else {
                                str.next();
                            }
                        })));

                        str.space();
                    }
                }

                push(str.fakeTok(otk::PipeClose));
            } else {
                str.setPos(pos);
                push(str.tok(otk::PipeCellOpen, skipOne, '|'));
                str.space();
                push(str.tok(otk::Content, skipToEOL));
                if (!str.finished()) {
                    str.skip('\n');
                }
            }
            break;
        }
        case '\n': {
            str.next();
            lexTableState(str, state);
            break;
        }
        default: {
            if (state.topFlag() == OrgBlockLexerState::InHeader) {
                push(str.tok(otk::CmdArguments, skipPastEOL));
            } else {
                push(str.tok(otk::Content, [](PosStr& str) {
                    while (!str.finished() && !str.at(CharSet{'|', '#'})) {
                        str.skipPastEOL();
                    }
                    if (!str.finished()) {
                        str.back();
                    }
                }));

                if (!str.finished()) {
                    str.next();
                }
            }
        }
    }
}

void OrgTokenizer::lexTable(PosStr& str) {
    __trace();
    OrgTokenizer::LexerState<OrgBlockLexerState> state;
    state.lift(OrgBlockLexerState::None);

    while (!str.finished()
           && !(state.topFlag() == OrgBlockLexerState::Complete)) {
        lexTableState(str, state);
    }

    if (state.topFlag() == OrgBlockLexerState::Complete) {
        if (str.at(charsets::Newline)) {
            str.next();
        }
    }
}

void OrgTokenizer::lexStructure(PosStr& str) {
    __trace();
    // This procedure dispatches into toplevel lexer routines that are
    // meant to produce entries for the high-level document structure -
    // paragraphs, lists, subtrees, command blocks and so on.
    switch (str.get(0)) {
        case '\x00': break;
        case '#': {
            switch (str.get(1)) {
                case '+': {
                    if (str.at("#+begin-table")
                        || str.at("#+begin_table")) {
                        lexTable(str);
                    } else {
                        lexCommandBlock(str);
                    }
                    break;
                }
                case ' ': { // `# some text`
                    lexComment(str);
                    break;
                }
                default: {
                    if (charsets::IdentChars.contains(str.get(1))) {
                        lexParagraph(str);
                        break;
                    } else {
                        assert(false);
                        // throw newImplementError(str);
                    }
                }
            }
            break;
        }

        case '*': {
            // No whitespace between a start and a character means it
            // is a bold word, otherwise it is a structural element -
            // either subtree or a unordered list.
            bool hasSpace = str.at(CharSet{'*'}, 0)
                         && str.at(CharSet{' '}, 1);

            if (str.getColumn() == 0) {
                if (hasSpace) {
                    // `*bold*` world at the start of the paragraph
                    lexSubtree(str);
                } else {
                    // `* subtree` starting on the first line
                    lexParagraph(str);
                }
            } else {
                if (hasSpace) {
                    // `__* list item` on a line
                    lexList(str);
                } else {
                    lexParagraph(str);
                }
            }
            break;
        }

        case '-': {
            if (atConstructStart(str)) {
                push(str.tok(otk::TextSeparator, skipOneOrMore, '-'));
                str.skip('\n');
            } else {
                lexList(str);
            }
            break;
        }

        case '\n':
        case ' ': {
            if (atListAhead(str)) {
                lexList(str);
            } else {
                str.skipZeroOrMore(CharSet{' ', '\n'});
                lexStructure(str);
            }
            break;
        }

        default: {
            if ((charsets::MaybeLetters + CharSet{'~', '['})
                    .contains(str.get(0))) {
                lexParagraph(str);
            } else {
                // Text starts with inline or display latex math equation,
                // `\symbol`, macro call or any other type of the text.
                lexParagraph(str);
            }
        }
    }
}

void OrgTokenizer::report(CR<Report> in) {
    if (!trace) {
        return;
    }

    using fg = TermColorFg8Bit;
    if (in.kind == ReportKind::Enter) {
        ++depth;
    }

    ColStream os = getStream();
    os << repeat("  ", depth);


    switch (in.kind) {
        case ReportKind::SetBuffer: os << "  ! set buffer"; break;
        case ReportKind::ClearBuffer: os << "  ! clear buffer"; break;
        case ReportKind::PushResolved: {
            os << "  + push resolved " << in.tok;
            break;
        }

        case ReportKind::Push: {
            if (in.id.isNil()) {
                os << "  + buffer token " << in.tok;
            } else {
                os << "  + add token " << in.id.getIndex() << " "
                   << at(in.id);
            }
            os << " at " << fg::Cyan << in.line << os.end();
            break;
        }
        case ReportKind::Enter:
        case ReportKind::Leave: {
            os << (in.kind == ReportKind::Enter ? "> " : "< ") << fg::Green
               << in.name << os.end() << ":" << fg::Cyan << in.line
               << os.end();

            if (in.str != nullptr) {
                os << " [";
                in.str->print(os, PosStr::PrintParams({.withEnd = false}));
                os << "]";
            }

            if (in.subname.has_value()) {
                os << " " << in.subname.value();
            }

            break;
        }
    }


    endStream(os);

    if (in.kind == ReportKind::Leave) {
        --depth;
    }
}

void OrgTokenizer::pushResolved(CR<OrgToken> token) {
    report(Report{.kind = ReportKind::PushResolved, .tok = token});
    auto str = PosStr(token.text);
    switch (token.kind) {
        case otk::Text: {
            __push(str.fakeTok(otk::ParagraphStart));
            while (!str.finished()) {
                lexText(str);
            }
            __push(str.fakeTok(otk::ParagraphEnd));
            break;
        }

        case otk::RawLogbook: {
            auto str = PosStr(token.text);
            __push(str.fakeTok(otk::LogbookStart));
            while (!str.finished()) {
                if (atLogClock(str)) {
                    __push(str.tok(otk::Text, skipToEOL));
                    if (str.at(charsets::Newline)) {
                        str.next();
                        if (!atLogClock(str)) {
                            str.space();
                        }
                    }
                } else {
                    lexList(str);
                }
            }
            __push(str.fakeTok(otk::LogbookEnd));
            break;
        }

        case otk::Content: {
            __push(str.fakeTok(otk::ContentStart));
            lexGlobal(str);
            push(str.fakeTok(otk::ContentEnd));
            break;
        }

        case otk::StmtList: {
            push(str.fakeTok(otk::StmtListOpen));
            lexGlobal(str);
            push(str.fakeTok(otk::StmtListClose));
            break;
        }

        default: {
            push(token);
            break;
        }
    }
}

void OrgTokenizer::lexGlobal(PosStr& str) {
    __trace();
    while (!str.finished()) {
        lexStructure(str);
    }
}
