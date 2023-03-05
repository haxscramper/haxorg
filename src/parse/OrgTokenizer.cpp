#include "OrgTokenizer.hpp"

#include <hstd/stdlib/algorithms.hpp>
#include <hstd/stdlib/Debug.hpp>

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>


#define __INIT_REPORT(__subname, __str)                                   \
    (Report{                                                              \
        .line     = __LINE__,                                             \
        .location = __CURRENT_FILE_PATH__,                                \
        .str      = &__str,                                               \
        .subname  = __subname,                                            \
    })

#define __print(__text)                                                   \
    report(Report{                                                        \
        .line     = __LINE__,                                             \
        .location = __CURRENT_FILE_PATH__,                                \
        .kind     = ReportKind::Print,                                    \
        .subname  = __text});

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


#define __push_rep()                                                      \
    Report {                                                              \
        .line = __LINE__, .kind = ReportKind::Push,                       \
        .location = __CURRENT_FILE_PATH__                                 \
    }

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

const auto commandNameMap = std::unordered_map<QString, OrgCommandKind>{
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

OrgCommandKind classifyCommand(QString const& command) {
    QString norm = normalize(command);
    if (commandNameMap.contains(norm)) {
        return commandNameMap.at(norm);
    } else {
        throw KeyError(
            "Cannot classify command '$#' (normalized to '$#')"
            % to_string_vec(command, norm));
    }
}


CR<CharSet> OIdentChars{
    slice(QChar('a'), QChar('z')),
    slice(QChar('A'), QChar('Z')),
    QChar('_'),
    QChar('-'),
    slice(QChar('0'), QChar('9'))};
CR<CharSet> OIdentStartChars = charsets::IdentChars
                             - CharSet{
                                 QChar('_'),
                                 QChar('-'),
                                 slice(QChar('0'), QChar('9'))};


CR<CharSet> OCommandChars = charsets::IdentChars
                          + CharSet{QChar('-'), QChar('_')};


CR<CharSet> OBigIdentChars  = CharSet{slice(QChar('A'), QChar('Z'))};
const QChar OEndOfFile      = QChar('\x00');
CR<CharSet> OBareIdentChars = charsets::AllChars - charsets::Whitespace;
CR<CharSet> OWhitespace     = charsets::Whitespace - CharSet{QChar('\n')};
CR<CharSet> OEmptyChars     = OWhitespace + CharSet{OEndOfFile};
CR<CharSet> OLinebreaks     = charsets::Newlines + CharSet{OEndOfFile};
CR<CharSet> OMarkupChars    = CharSet{
    QChar('*'),
    QChar('_'),
    QChar('/'),
    QChar('+'),
    QChar('~'),
    QChar('`')};
CR<CharSet> OVerbatimChars = CharSet{QChar('`'), QChar('~'), QChar('=')};
CR<CharSet> OPunctChars    = CharSet{
    QChar('('),
    QChar(')'),
    QChar('['),
    QChar(']'),
    QChar('.'),
    QChar('?'),
    QChar('!'),
    QChar(',')};
CR<CharSet> OPunctOpenChars = CharSet{
    QChar('('),
    QChar('['),
    QChar('{'),
    QChar('<')};
CR<CharSet> OPunctCloseChars = CharSet{
    QChar(')'),
    QChar(']'),
    QChar('}'),
    QChar('>')};
CR<CharSet> ONumberedListChars = CharSet{slice(QChar('0'), QChar('9'))}
                               + CharSet{slice(QChar('a'), QChar('z'))}
                               + CharSet{slice(QChar('A'), QChar('Z'))};
CR<CharSet> OBulletListChars = CharSet{QChar('-'), QChar('+'), QChar('*')};
CR<CharSet> OListChars       = ONumberedListChars + OBulletListChars;


const QChar OSubtreeStart   = QChar('*');
const QChar OSubtreeOrList  = QChar('*');
const QChar OBulletListStar = QChar('*');
const QChar OSpace          = QChar(' ');
const QChar ONewline        = QChar('\n');

const CR<CharSet> OBulletListStart = CharSet{
    QChar('-'),
    QChar('+'),
    QChar('*')};

struct MarkupConfigPair {
    OrgTokenKind startKind;
    OrgTokenKind finishKind;
    OrgTokenKind inlineKind;
};


const CharSet markupKeys{
    QChar('*'),
    QChar('/'),
    QChar('='),
    QChar('`'),
    QChar('~'),
    QChar('_'),
    QChar('+'),
    QChar('"')};

// clang-format off
/// Table of the markup config information, to reduce usage of the
/// character literals directly in the code.
const TypArray<QChar, MarkupConfigPair> markupConfig{{
    {QChar('*'), {otk::BoldOpen,      otk::BoldClose,      otk::BoldInline}},
    {QChar('/'), {otk::ItalicOpen,    otk::ItalicClose,    otk::ItalicInline}},
    {QChar('='), {otk::VerbatimOpen,  otk::VerbatimClose,  otk::VerbatimInline}},
    {QChar('`'), {otk::BacktickOpen,  otk::BacktickClose,  otk::BacktickInline}},
    {QChar('~'), {otk::MonospaceOpen, otk::MonospaceClose, otk::MonospaceInline}},
    {QChar('_'), {otk::UnderlineOpen, otk::UnderlineClose, otk::UnderlineInline}},
    {QChar('+'), {otk::StrikeOpen,    otk::StrikeClose,    otk::StrikeInline}},
    {QChar('"'), {otk::QuoteOpen,     otk::QuoteClose,     otk::None}},
}};
// clang-format on


const CharSet ListStart = CharSet{QChar('-'), QChar('+'), QChar('*')}
                        + charsets::Digits + charsets::AsciiLetters;

void OrgTokenizer::lexAngle(PosStr& str) {
    __trace();
    if (str.at("<%%")) {
        auto tok = str.tok(otk::DiaryTime, [](PosStr& str) {
            str.skip("<%%");
            skipBalancedSlice(
                str,
                {.openChars  = CharSet{QChar('(')},
                 .closeChars = CharSet{QChar(')')}});
            str.skip(">");
        });
        __push(tok);
    } else if (str.at("<<<")) {
        __push((str.tok(otk::TripleAngleOpen, skipCount, 3)));
    } else if (str.at("<<")) {
        __push((str.tok(otk::DoubleAngleOpen, skipCount, 2)));
        __push((str.tok(otk::RawText, skipTo, QChar('>'))));
        __push((str.tok(otk::RawText, skipOne, ">>")));
    } else if (str.at(charsets::Digits, 1)) {
        auto skipAngles = [](PosStr& str) {
            str.skip(QChar('<'));
            str.skipTo(QChar('>'));
            str.skip(QChar('>'));
        };

        __push((str.tok(otk::AngleTime, skipAngles)));

        if (str.at("--")) {
            __push((str.tok(otk::TimeDash, skipCount, 2)));
            __push((str.tok(otk::AngleTime, skipAngles)));
        }
    } else {
        __push((str.tok(otk::AngleOpen, skipCount, 1)));
        __push((str.tok(otk::RawText, skipTo, QChar('>'))));
        __push((str.tok(otk::AngleClose, skipOne, QChar('>'))));
    }
}

void OrgTokenizer::lexTime(PosStr& str) {
    __trace();
    if (str.at(QChar('<'))) {
        lexAngle(str);
    } else if (str.at(QChar('['))) {
        auto skipBracket = [](PosStr& str) {
            str.skip(QChar('['));
            str.skipTo(QChar(']'));
            str.skip(QChar(']'));
        };

        auto time = str.tok(otk::BracketTime, skipBracket);
        __push(time);
        if (str.at("--")) {
            auto sep = str.tok(otk::TimeDash, skipCount, 2);
            __push(sep);
            auto time = str.tok(otk::BracketTime, skipBracket);
            __push(time);
        }
    } else {
        throw str.makeUnexpected("QChar('<') or QChar('[')", "time");
    }
}

void OrgTokenizer::lexLinkTarget(PosStr& str) {
    __trace();
    if (str.at("https") || str.at("http")) {
        assert(false && "FIXME");
    } else if (
        str.at("file") || str.at("attachment") || str.at("docview")
        || str.at(QChar('/')) || str.at("./")) {

        if (str.at(QChar('.')) || str.at(QChar('/'))) {
            auto protocol = str.fakeTok(otk::LinkProtocol);
            __push(protocol);
        } else {
            auto protocol = str.tok(otk::LinkProtocol, skipTo, QChar(':'));
            __push(protocol);
            str.skip(QChar(':'));
        }

        auto target = str.tok(otk::LinkTarget, [](PosStr& str) {
            while (!str.finished() && !str.at("::")) {
                str.next();
            }
        });
        __push(target);

        if (str.at("::")) {
            auto separator = str.tok(
                otk::LinkExtraSeparator, skipCount, 2);
            __push(separator);
            auto extra = str.tok(otk::LinkExtra, skipPastEOF);
            __push(extra);
        }
    } else {
        // Simple, non-URI protocols that don't have trailing extra
        // separator parametrization and all other cases (including
        // user-provided link templates)
        if (str.hasAhead(QChar(':'))) {
            auto protocol = str.tok(otk::LinkProtocol, skipTo, QChar(':'));
            __push(protocol);
            str.skip(QChar(':'));
            auto target = str.tok(otk::LinkTarget, skipPastEOF);
            __push(target);
        } else {
            auto intern = str.tok(otk::LinkInternal, skipPastEOF);
            __push(intern);
        }
    }
}

void OrgTokenizer::lexBracket(PosStr& str) {
    __trace();
    if (str.at("[[")) {
        auto open = str.tok(otk::LinkOpen, skipOne, QChar('['));
        __push(open);
        // link_token
        {
            auto open = str.tok(otk::LinkTargetOpen, skipOne, QChar('['));
            __push(open);
            PosStr target = str.slice(skipTo, QChar(']'));
            lexLinkTarget(target);
            auto close = str.tok(
                otk::LinkTargetClose, skipOne, QChar(']'));
            __push(close);
        };
        // description_token
        {
            if (str.at(QChar('['))) {
                auto descrOpen = str.tok(
                    otk::LinkDescriptionOpen, skipOne, QChar('['));
                __push(descrOpen);
                PosStr desc = str.slice([](PosStr& str) {
                    int count = 0;
                    while (!str.finished()
                           && (!str.at(QChar(']')) || (0 < count))) {

                        if (str.at(QChar('['))) {
                            ++count;
                        }
                        if (str.at(QChar(']'))) {
                            --count;
                        }
                        str.next();
                    }
                });

                while (!desc.finished()) {
                    lexText(desc);
                }

                auto descrClose = str.tok(
                    otk::LinkDescriptionClose, skipOne, QChar(']'));
                __push(descrClose);
            }
        }
        auto linkClose = str.tok(otk::LinkClose, skipOne, QChar(']'));
        __push(linkClose);
    } else if (str.at("[fn:")) {
        auto start = str.tok(otk::FootnoteStart, skipOne, "[fn");
        __push(start);
        if (str.at("::")) {
            auto couble = str.tok(otk::DoubleColon, skipOne, "::");
            __push(couble);
            // FIXME
            // result.addExpandTok(str, otk::Text,
            // str.skipTo(QChar(']')););
        } else {
            auto colon = str.tok(otk::Colon, skipOne, QChar(':'));
            __push(colon);
            auto ident = str.tok(otk::Ident, skipTo, QChar(']'));
            __push(ident);
        }
        auto end = str.tok(otk::FootnoteEnd, skipOne, QChar(']'));
        __push(end);
    } else {
        lexTime(str);
    }
}

void OrgTokenizer::lexTextChars(PosStr& str) {
    __trace();
    bool isStructure = false;
    auto skipCurly   = [](PosStr& str) {
        skipBalancedSlice(
            str,
            BalancedSkipArgs{
                  .openChars = {QChar('{')}, .closeChars = {QChar('}')}});
    };

    auto skipParen = [](PosStr& str) {
        skipBalancedSlice(
            str,
            BalancedSkipArgs{
                .openChars = {QChar('(')}, .closeChars = {QChar(')')}});
    };

    auto skipBrace = [](PosStr& str) {
        skipBalancedSlice(
            str,
            BalancedSkipArgs{
                .openChars = {QChar('[')}, .closeChars = {QChar(']')}});
    };

    if (str.at("src[_-]?\\w+(\\[|\\{)")) {
        const auto    pos = str.getPos();
        Vec<OrgToken> buf;
        // Starting `src_` prefix
        {
            buf.push_back(str.tok(otk::SrcOpen, skipOne, "src"));
            if (str.at(CharSet{QChar('_'), QChar('-')})) {
                str.next();
            }
        }

        if (str.at(charsets::IdentStartChars)) {
            // FIXME push buffer only if the whole sequence is
            // determined to be a valid structure
            for (const auto& tok : buf) {
                __push(tok);
            }
            auto name = str.tok(
                otk::SrcName, skipZeroOrMore, charsets::IdentChars);
            __push(name);
            if (str.at(QChar('['))) {
                auto args = str.tok(otk::SrcArgs, skipBrace, {1, -2});
                __push(args);
            }

            auto body = str.tok(otk::SrcBody, skipCurly, {1, -2});
            __push(body);
            auto close = str.fakeTok(otk::SrcClose);
            __push(close);
            isStructure = true;
        } else {
            str.setPos(pos);
        }

    } else if (str.at("call[_-]?\\w+(\\[|\\{)")) {
        const auto    pos = str.getPos();
        Vec<OrgToken> buf;
        buf.push_back(str.tok(otk::CallOpen, skipOne, "call"));
        if (str.at(CharSet{QChar('_'), QChar('-')})) {
            str.next();
        }
        if (str.at(charsets::IdentStartChars)) {
            for (const auto& tok : buf) {
                __push(tok);
            }
            auto name = str.tok(
                otk::SrcName, skipZeroOrMore, charsets::IdentChars);
            __push(name);
            if (str.at(QChar('['))) {
                auto header = str.tok(
                    otk::CallInsideHeader, skipBrace, {1, -2});
                __push(header);
            };
            auto args = str.tok(otk::CallArgs, skipParen, {1, -2});
            __push(args);
            auto close = str.fakeTok(otk::CallClose);
            __push(close);
            isStructure = true;
        } else {
            str.setPos(pos);
        }
    } else if (str.at("https://") || str.at("http://")) {
        auto url = str.tok(otk::RawUrl, skipBefore, charsets::Whitespace);
        __push(url);
    }
    if (!isStructure) {
        bool allUp = true;
        str.pushSlice();
        while (!str.finished()
               && str.at(charsets::TextChars + CharSet{QChar('-')})) {
            if (!str.at(charsets::HighAsciiLetters)) {
                allUp = false;
            }
            str.next();
        }
        auto name = str.popTok(allUp ? otk::BigIdent : otk::Word);
        __push(name);
    }
}

void OrgTokenizer::lexParenArguments(PosStr& str) {
    __trace();
    auto open = str.tok(otk::ParOpen, skipOne, QChar('('));
    __push(open);
    while (!str.at(QChar(')'))) {
        // Read argument until the first comma or closing parent
        auto raw = str.tok(
            otk::RawText,
            skipBefore,

            // TODO handle quoted strings and escaped commas
            cr(CharSet{QChar(','), QChar(')')}));
        __push(raw);

        // maybe lex comma
        if (str.at(QChar(','))) {
            auto comma = str.tok(otk::Comma, skipOne, QChar(','));
            __push(comma);
        }

        // optional space, not significant for argument passing
        str.space();
    }
    auto close = str.tok(otk::ParClose, skipOne, QChar(')'));
    __push(close);
}

void OrgTokenizer::lexTextDollar(PosStr& str) {
    __trace();
    auto          tmp = str;
    Vec<OrgToken> buf;
    try {
        if (tmp.at(QChar('$'), 1)) {
            buf.push_back(tmp.tok(otk::DollarOpen, skipOne, "$$"));
            tmp.pushSlice();
            bool hasEnd = false;
            while (!tmp.finished() && !hasEnd) {
                while (!tmp.finished() && !tmp.at(QChar('$'))) {
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
            // buf.add(tmp.tok(skip otk::DollarClose,
            // QChar('$'), QChar('$')));
        } else {
            buf.push_back(tmp.tok(otk::DollarOpen, skipOne, QChar('$')));
            buf.push_back(
                tmp.tok(otk::LatexInlineRaw, skipBefore, QChar('$')));
            buf.push_back(tmp.tok(otk::DollarClose, skipOne, QChar('$')));
        }
        for (const auto& tok : buf) {
            __push(tok);
        }
        str = tmp;
    } catch (UnexpectedCharError& err) {
        auto punct = str.tok(otk::Punctuation, skipZeroOrMore, QChar('$'));
        __push(punct);
    }
}

void OrgTokenizer::lexTextSlash(PosStr& str) {
    __trace();
    switch (str.get(1).unicode()) {
        case '[':
        case '(': {
            const auto isInline = str.at(QChar('('), 1);

            if (isInline) {
                auto open = str.tok(otk::LatexParOpen, skipOne, "\\(");
                __push(open);
            } else {
                auto open = str.tok(otk::LatexBraceOpen, skipOne, "\\[");
                __push(open);
            }

            auto latex = str.tok(
                otk::LatexInlineRaw, [&isInline](PosStr& str) {
                    while (!str.at(isInline ? "\\)" : "\\]")) {
                        str.next();
                    }
                });
            __push(latex);

            if (isInline) {
                auto close = str.tok(otk::LatexParClose, skipOne, ")");
                __push(close);
            } else {
                auto close = str.tok(otk::LatexBraceClose, skipOne, "]");
                __push(close);
            }

            break;
        }
        case '\\': {
            auto slash = str.tok(otk::DoubleSlash, skipOne, "\\");
            __push(slash);
            break;
        }
        default: {
            if (str.at(OMarkupChars, 1)) {
                auto esc = str.tok(otk::Escaped, skipCount, 1);
                __push(esc);
            } else if (str.at(
                           charsets::IdentStartChars - CharSet{QChar('_')},
                           1)) {
                auto sym = str.tok(otk::SymbolStart, skipOne, QChar('\\'));
                __push(sym);
                auto ident = str.tok(
                    otk::Ident, skipZeroOrMore, charsets::IdentChars);
                __push(ident);
                if (str.at(QChar('['))) {
                    auto open = str.tok(
                        otk::MetaBraceOpen, skipOne, QChar('['));
                    __push(open);
                    auto body = str.tok(
                        otk::MetaBraceBody, [](PosStr& str) {
                            skipBalancedSlice(
                                str,
                                {.openChars    = {QChar('[')},
                                 .closeChars   = {QChar(']')},
                                 .skippedStart = true,
                                 .consumeLast  = false});
                        });
                    __push(body);
                    auto close = str.tok(
                        otk::MetaBraceClose, skipOne, QChar(']'));
                    __push(close);
                }
                while (str.at(QChar('{'))) {
                    auto open = str.tok(
                        otk::MetaArgsOpen, skipOne, QChar('{'));
                    __push(open);
                    auto body = str.tok(
                        otk::MetaBraceBody, [](PosStr& str) {
                            skipBalancedSlice(
                                str,
                                {.openChars    = {QChar('{')},
                                 .closeChars   = {QChar('}')},
                                 .skippedStart = true,
                                 .consumeLast  = false});
                        });
                    __push(body);

                    auto close = str.tok(
                        otk::MetaArgsClose, skipOne, QChar('}'));
                    __push(close);
                }
                break;
            } else {
                auto esc = str.tok(otk::Escaped, skipCount, 2);
                __push(esc);
            }
        }
    }
}

const auto NonText = charsets::TextLineChars - charsets::AsciiLetters
                   - charsets::Utf8Any + CharSet{ONewline, QChar('/')};


void OrgTokenizer::lexTextVerbatim(PosStr& str) {
    __trace();
    const auto start = str.get();
    if (str.at(start, 1)) {
        auto open = str.tok(markupConfig[start].inlineKind, skipCount, 2);
        __push(open);
        auto text = str.tok(otk::RawText, [start](PosStr& str) {
            while (!(str.at(start, 0) && str.at(start, 1))) {
                str.next();
            }
        });
        __push(text);
        auto close = str.tok(markupConfig[start].inlineKind, skipCount, 2);
        __push(close);
    } else {
        if (str.at(NonText, -1) || str.atStart()) {
            auto open = str.tok(
                markupConfig[start].startKind, skipCount, 1);
            __push(open);
            auto text = str.tok(otk::RawText, skipTo, start);
            __push(text);
            if (str.at(NonText, 1) || str.beforeEnd()) {
                auto end = str.tok(
                    markupConfig[start].finishKind, skipCount, 1);
                __push(end);
            }
        } else {
            auto punct = str.tok(otk::Punctuation, skipCount, 1);
            __push(punct);
        }
    }
}

void OrgTokenizer::lexTextCurly(PosStr& str) {
    __trace();
    if (str.at("{{{")) {
        auto open = str.tok(otk::MacroOpen, skipCount, 3);
        __push(open);
        auto ident = str.tok(otk::Ident, [](PosStr& str) {
            while (!str.finished() && !str.at(QChar('('))
                   && !str.at("}}}")) {
                str.next();
            }
        });
        __push(ident);

        if (str.at(QChar('('))) {
            lexParenArguments(str);
        }
        if (!str.finished()) {
            auto close = str.tok(otk::MacroClose, skipOne, "}}}");
            __push(close);
        }
    } else {
        auto word = str.tok(otk::MaybeWord, skipCount, 1);
        __push(word);
    }
}

void OrgTokenizer::lexTextMarkup(PosStr& str) {
    __trace();
    const auto ch                        = str.get();
    const auto& [kOpen, kClose, kInline] = markupConfig[ch];
    if (str.at(ch, +1)) {
        auto tmp = str.tok(kInline, skipCount, 2);
        __push(tmp);
    } else if (str.at(NonText, -1) || str.atStart()) {
        auto tmp = str.tok(kOpen, skipCount, 1);
        __push(tmp);
    } else if (str.at(NonText, 1) || str.beforeEnd()) {
        auto tmp = str.tok(kClose, skipCount, 1);
        __push(tmp);
    } else {
        auto tmp = str.tok(otk::Word, skipCount, 1);
        __push(tmp);
    }
}

void OrgTokenizer::lexHashTag(PosStr& str) {
    __trace();
    auto head = str.tok(otk::HashTag, [](PosStr& str) {
        str.trySkip(QChar('#'));
        str.skipZeroOrMore(charsets::IdentChars);
    });
    __push(head);

    while (str.at("##") && !str.at("##")) {
        auto sub = str.tok(otk::HashTagSub, skipOne, QChar('#'));
        __push(sub);
        auto hash = str.tok(otk::HashTag, [](PosStr& str) {
            str.skip(QChar('#'));
            str.skipZeroOrMore(charsets::IdentChars);
        });
        __push(hash);
    }

    if (str.at("##[")) {
        auto join = str.tok(otk::HashTagSub, skipOne, QChar('#'));
        __push(join);
        auto open = str.tok(otk::HashTagOpen, skipOne, "#[");
        __push(open);

        while (!str.finished() && !str.at(QChar(']'))) {
            lexHashTag(str);
            str.space();
            if (str.at(QChar(','))) {
                auto comma = str.tok(otk::Comma, skipOne, QChar(','));
                __push(comma);
                str.space();
            }
        }

        auto close = str.tok(otk::HashTagClose, skipOne, QChar(']'));
        __push(close);
    }
}

void OrgTokenizer::lexText(PosStr& str) {
    __trace();

    switch (str.get().unicode()) {
        case '\n': {
            auto nl = str.tok(otk::Newline, skipCount, 1);
            __push(nl);
            break;
        }
        case ' ': {
            auto space = str.tok(otk::Space, [](PosStr& str) {
                while (!str.finished() && str.at(OSpace)) {
                    str.next();
                }
            });
            __push(space);
            break;
        }
        case '#': {
            lexHashTag(str);
            break;
        }
        case '@': {
            lexTextAtSign(str);
            break;
        }
        case '$': {
            lexTextDollar(str);
            break;
        }
        case '\\': {
            lexTextSlash(str);
            break;
        }
        case '~':
        case '`':
        case '=': {
            lexTextVerbatim(str);
            break;
        }
        case '<': {
            try {
                lexAngle(str);
                // REFACTOR remove exception for control handling, make
                // interface more explicit
            } catch (UnexpectedCharError&) {
                auto punct = str.tok(otk::Punctuation, skipCount, 1);
                __push(punct);
            }
            break;
        }

        case '[': {
            lexBracket(str);
            break;
        }
        case '(': {
            auto open = str.tok(otk::ParOpen, skipCount, 1);
            __push(open);
            break;
        }
        case ')': {
            auto close = str.tok(otk::ParClose, skipCount, 1);
            __push(close);
            break;
        }
        case ':': {
            auto colon = str.tok(otk::Colon, skipCount, 1);
            __push(colon);
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
            auto punct = str.tok(otk::Punctuation, skipCount, 1);
            __push(punct);
            break;
        }
        case '{': {
            lexTextCurly(str);
            break;
        }
        case '^': {
            auto circ = str.tok(otk::Circumflex, skipCount, 1);
            __push(circ);
            break;
        }
        default: {
            if (str.at(charsets::TextChars)) {
                lexTextChars(str);
            } else if (str.at(
                           markupKeys
                           - CharSet{
                               QChar('<'),
                               QChar('~'),
                               QChar('`'),
                               QChar('=')})) {
                lexTextMarkup(str);
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
            str.skip(QChar(':'));
            str.skipZeroOrMore(charsets::IdentChars);
            if (str.at(QChar('+'))) {
                isAdd = true;
            }
            str.skip(QChar(':'));
        });

        if (normalize(id.toStr()) == ":end:") {
            hasEnd   = true;
            auto end = Token(otk::ColonEnd, id.view);
            __push(end);
        } else {
            auto ident = Token(
                isAdd ? otk::ColonAddIdent : otk::ColonIdent, id.view);
            __push(ident);
            if (str.at(charsets::IdentStartChars)) {
                auto ident = str.tok(otk::Ident, [](PosStr& str) {
                    while (!str.finished()
                           && str.at(
                               charsets::DashIdentChars
                               + CharSet{QChar('/')})) {
                        str.next();
                    }
                });
                __push(ident);
                str.skip(QChar(':'));
            }
            str.space();
            auto prop = str.tok(otk::RawProperty, skipToEOL);
            __push(prop);
            str.skip(ONewline);
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
        auto text = Token(otk::Text, str.popSlice().view);
        __push(text);
        const auto id  = str.slice([](PosStr& str) {
            str.skip(QChar(':'));
            str.skipZeroOrMore(charsets::IdentChars);
            str.skip(QChar(':'));
        });
        auto       end = Token(otk::ColonEnd, id.view);
        __push(end);
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

        auto raw = Token(otk::RawLogbook, str.popSlice().view);
        __push(raw);

        const auto id = str.slice([](PosStr& str) {
            str.skip(QChar(':'));
            str.skipZeroOrMore(charsets::IdentChars);
            str.skip(QChar(':'));
        });

        auto end = Token(otk::ColonEnd, id.view);
        __push(end);
        hasEnd = true;
    };
}

void OrgTokenizer::lexDrawer(PosStr& str) {
    __trace();
    auto strEnded = false;
    while (!str.finished() && !strEnded) {
        str.space();
        const auto id = str.slice([](PosStr& str) {
            str.skip(QChar(':'));
            str.skipZeroOrMore(charsets::IdentChars);
            str.skip(QChar(':'));
        });

        str.skip(ONewline);
        const Str norm = normalize(id.toStr());
        if (norm == ":properties:") {
            auto prop = Token(otk::ColonProperties, id.view);
            __push(prop);
            lexProperties(str);
        } else if (norm == ":logbook:") {
            auto log = Token(otk::ColonLogbook, id.view);
            __push(log);
            lexLogbook(str);
        } else if (norm == ":description:") {
            auto desc = Token(otk::ColonDescription, id.view);
            __push(desc);
            lexDescription(str);
        } else {
            assert(false && "FIXME IMPLEMENT");
            // throw newImplementKindError(norm, toStr(str));
        }

        auto ahead = str;
        ahead.space();
        if (ahead.trySkip(ONewline)) {
            ahead.space();
            if (!ahead.at(QChar(':'))) {
                strEnded = true;
                str      = ahead;
            }
        }
        if (!strEnded) {
            str.skipZeroOrMore(ONewline);
        }
    }
}

void OrgTokenizer::lexSubtreeTodo(PosStr& str) {
    __trace();
    auto tmp = str;
    tmp.pushSlice();
    tmp.skipZeroOrMore(charsets::HighAsciiLetters);
    if (tmp.at(OSpace)) {
        auto state = tmp.popTok(otk::SubtreeTodoState);
        __push(state);
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
        str.skip(QChar(']'));
        auto urg = str.popTok(otk::SubtreeUrgency);
        __push(urg);
        str.space();
    }
}

void OrgTokenizer::lexSubtreeTitle(PosStr& str) {
    __trace();
    auto          body = str.slice(skipToEOL);
    Vec<OrgToken> headerTokens;
    body.skipToEOF();
    if (body.at(QChar(':'))) {
        body.back();
        auto tagEnded = false;
        while (!body.finished() && !tagEnded) {
            const auto finish = body.getPos();
            while (!body.finished()
                   && !body.at(
                       charsets::IdentChars
                       + CharSet{QChar('#'), QChar('@')})) {
                body.back();
            }

            const auto start = body.getPos() + 1;
            body.skip(QChar(':'), -1);
            headerTokens.push_back(Token(
                otk::SubtreeTag, body.sliceBetween(start, finish).view));
            if (body.at(OSpace)) {
                tagEnded = true;
            }
        }
        while (body.at(OSpace)) {
            body.back();
        }
    }
    if (body.at(QChar(']'))) {
        auto tmp = body;
        try {
            const auto finish = tmp.getPos();
            tmp.skip(QChar(']'), -1);
            tmp.skip(charsets::Digits, -1);
            while (tmp.at(charsets::Digits)) {
                tmp.back();
            }
            if (str.at(QChar('%'))) {
                tmp.back();
            } else {
                tmp.skip(QChar('/'), -1);
                tmp.skip(charsets::Digits, -1);
                while (tmp.at(charsets::Digits)) {
                    tmp.back();
                }
            }
            tmp.skip(QChar('['), -1, -1);

            const auto start = tmp.getPos() + 1;
            body             = tmp;
            headerTokens.push_back(Token(
                otk::SubtreeCompletion,
                tmp.sliceBetween(start, finish).view));
            while (body.at(OSpace)) {
                body.next(-1);
            }
        } catch (UnexpectedCharError& err) { ; };
    }
    //
    {
        auto finish = body.getPos();
        body.skipToSOF();
        const auto start = body.getPos();
        auto       slice = body.sliceBetween(start, finish);
        headerTokens.push_back(Token(otk::Text, slice.view));
    }

    for (const auto& tok : reversed(headerTokens)) {
        pushResolved(tok);
    }
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

        if (Vec<Str>{"deadline", "closed", "scheduled"}.contains(
                normalize(tag.toStr()))) {
            auto time = Token(otk::SubtreeTime, tag.view);
            __push(time);
            times.skip(QChar(':'));
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
        str.skip(ONewline);
    }
}

void OrgTokenizer::lexSubtree(PosStr& str) {
    __trace();
    auto stars = str.tok(otk::SubtreeStars, skipZeroOrMore, OSubtreeStart);
    __push(stars);
    str.skip(OSpace);
    str.space();
    lexSubtreeTodo(str);
    str.space();
    lexSubtreeUrgency(str);
    str.space();
    lexSubtreeTitle(str);
    str.trySkip(ONewline);
    lexSubtreeTimes(str);
    auto drawer = str;
    drawer.space();
    if (drawer.at(QChar(':'))) {
        lexDrawer(drawer);
        str = drawer;
    }
    auto end = str.fakeTok(otk::SubtreeEnd);
    __push(end);
}

void OrgTokenizer::lexSourceBlockContent(PosStr& str) {
    __trace();
    while (!str.finished()) {
        if (str.at("<<")) {
            auto          failedAt = -1;
            auto          tmp      = str;
            Vec<OrgToken> tmpRes;
            // try_tangle
            {
                tmpRes.push_back(
                    tmp.tok(otk::DoubleAngleOpen, skipOne, "<<"));
                if (tmp.at(charsets::IdentChars)) {
                    tmpRes.push_back(tmp.tok(
                        otk::Ident, skipZeroOrMore, charsets::IdentChars));
                } else {
                    failedAt = tmp.pos;
                    break;
                }
                if (tmp.at(QChar('('))) {
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
                auto text = str.tok(
                    otk::CodeText, [&failedAt](PosStr& str) {
                        while (((str.pos) < (failedAt))) {
                            str.next();
                        }
                    });
                __push(text);
                str.setPos(failedAt);
            } else {
                for (const auto& tok : tmpRes) {
                    __push(tok);
                }
                str = tmp;
            }
        } else if (str.at("(refs:")) {
            auto open = str.tok(otk::ParOpen, skipOne, QChar('('));
            __push(open);
            auto ident = str.tok(otk::Ident, skipOne, "refs");
            __push(ident);
            auto colon = str.tok(otk::Colon, skipOne, ":");
            __push(colon);
            auto target = str.tok(
                otk::Ident,
                skipZeroOrMore,
                cr(charsets::IdentChars + CharSet{QChar('-')}));
            __push(target);
            auto close = str.tok(otk::ParClose, skipOne, QChar(')'));
            __push(close);

        } else if (str.at(ONewline)) {
            auto nl = str.tok(otk::Newline, skipCount, 1);
            __push(nl);
        } else {
            auto text = str.tok(otk::CodeText, [](PosStr& str) {
                while (!str.finished()
                       && !(
                           str.at("<<")        //
                           || str.at("(refs:") //
                           || str.at(ONewline))) {
                    str.next();
                }
            });
            __push(text);
        }
    }
}

void OrgTokenizer::lexCommandContent(
    PosStr&               str,
    const OrgCommandKind& kind) {
    __trace();
    auto content = str.fakeTok(otk::CommandContentStart);
    __push(content);
    switch (kind) {
        case ock::BeginQuote:
        case ock::BeginCenter:
        case ock::BeginAdmonition: {
            auto text = str.tok(otk::Text, skipPastEOF);
            __push(text);
            break;
        }
        case ock::BeginExample: {
            auto text = str.tok(otk::RawText, skipPastEOF);
            __push(text);
            break;
        }
        case ock::BeginDynamic: {
            str.space();
            auto text = str.tok(otk::Text, skipPastEOF);
            __push(text);
            break;
        }
        case ock::BeginSrc: {
            str.space();
            auto content = str.fakeTok(otk::CodeContentBegin);
            __push(content);
            lexSourceBlockContent(str);
            auto start = str.fakeTok(otk::CodeContentEnd);
            __push(start);
            break;
        }
        default: {
            assert(false && "IMPLEMENT");
        }
    };
    auto end = str.fakeTok(otk::CommandContentEnd);
    __push(end);
}

Vec<OrgToken> OrgTokenizer::lexDelimited(
    PosStr&                          str,
    const Pair<QChar, OrgTokenKind>& start,
    const Pair<QChar, OrgTokenKind>& finish,
    const OrgTokenKind&              middle) {
    __trace();
    Vec<OrgToken> result;
    result.push_back(str.tok(start.second, skipOne, start.first));
    result.push_back(str.tok(middle, [&finish](PosStr& str) {
        while (!str.finished() && !str.at(finish.first)) {
            if (str.at(QChar('\\'))) {
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

void OrgTokenizer::lexCommandProperty(PosStr& str) {
    __trace();
    str.space();
    auto ident = str.tok(
        otk::Ident, skipBefore, cr(CharSet{OSpace, QChar(':')}));
    __push(ident);
    if (str.at(QChar(':'))) {
        auto colon = str.tok(otk::Colon, skipCount, 1);
        __push(colon);
        auto ident = str.tok(otk::Ident, skipBefore, OSpace);
        __push(ident);
    }
    str.space();
    auto prop = str.tok(otk::RawProperty, skipPastEOF);
    __push(prop);
}

void OrgTokenizer::lexTextAtSign(PosStr& str) {
    __trace();
    const auto AtChars = charsets::IdentChars + charsets::Utf8Any;
    if (str.at(AtChars, 1)) {
        auto mention = str.tok(otk::AtMention, [&AtChars](PosStr& str) {
            str.skip(QChar('@'));
            str.skipZeroOrMore(AtChars);
        });
        __push(mention);
    } else {
        auto punct = str.tok(otk::Punctuation, skipCount, 1);
        __push(punct);
    }
}

void OrgTokenizer::lexCommandBlockDelimited(
    PosStr& str,
    PosStr  id,
    int     column) {
    __trace();
    auto begin = Token(otk::CommandBegin, id.view);
    __push(begin);

    const auto sectionName = normalize(id.toStr()).dropPrefix("begin");
    const auto kind        = classifyCommand(id.toStr());
    if (kind == ock::BeginDynamic) {
        str.skip(QChar(':'));
    }
    str.space();
    __print(str.printToString());
    auto arguments = str.slice({0, -1}, skipPastEOL);
    lexCommandArguments(arguments, kind);
    auto found = false;
    str.pushSlice();
    while (!found && !str.finished()) {
        while (!str.finished()
               && !(str.getColumn() == column && str.at("#+"))) {
            str.next();
        }
        assert(!str.finished());
        const auto   prefix = str.slice(skipCount, 2);
        const PosStr id     = str.slice(skipZeroOrMore, OCommandChars);
        if (normalize(id.toStr()) == "end" + sectionName) {
            found      = true;
            auto slice = str.popSlice(
                {0,
                 -(1           /* Default offset */
                   + id.size() /* `end_<xxx>` */
                   + 3 /* and trailing newline */)});
            lexCommandContent(slice, kind);
            auto pt = Token(otk::CommandPrefix, prefix.view);
            __push(pt);
            auto end = Token(otk::CommandEnd, id.view);
            __push(end);
        } else {
            throw LexerError(
                "Missing closing 'end' for section block " + sectionName,
                0);
        }
    }
    if (kind == ock::BeginDynamic) {
        str.skip(QChar(':'));
    }
}

void OrgTokenizer::lexCommandCall(PosStr& str) {
    __trace();
    str.space();
    auto call = str.tok(
        otk::CallName, skipZeroOrMore, charsets::IdentChars);
    __push(call);
    if (str.at(QChar('['))) {
        auto header = str.tok(
            otk::CallInsideHeader,
            skipBalancedSlice,
            QChar('['),
            QChar(']'));
        __push(header);
    }

    auto args = str.tok(
        otk::CallArgs, skipBalancedSlice, QChar('('), QChar(')'));
    __push(args);
    if (!str.finished()) {
        auto text = str.tok(otk::RawText, skipPastEOF);
        __push(text);
    }
}

void OrgTokenizer::lexCommandOptions(PosStr& str) {
    __trace();
    while (!str.finished()) {
        switch (str.get().unicode()) {
            case '\'':
            case '*':
            case '|':
            case ':':
            case '<':
            case '\n':
            case '^': {
                auto text = str.tok(otk::RawText, skipCount, 1);
                __push(text);
                break;
            }
            case ' ': {
                str.space();
                break;
            }
            default: {
                auto raw = str.tok(otk::RawText, [](PosStr& str) {
                    while (!str.finished()
                           && !str.at(charsets::HorizontalSpace)) {
                        str.next();
                    }
                });
                __push(raw);
            }
        }
    }
}

void OrgTokenizer::lexCommandInclude(PosStr& str) {
    __trace();
    str.space();
    if (str.at(QChar('"'))) {
        lexDelimited(
            str,
            {QChar('"'), otk::QuoteOpen},
            {QChar('"'), otk::QuoteClose},
            otk::RawText);
    } else {
        auto text = str.tok(otk::RawText, [](PosStr& str) {
            while (!str.finished() && !str.at(charsets::HorizontalSpace)) {
                str.next();
            }
        });
        __push(text);
    }
    lexCommandKeyValue(str);
}

void OrgTokenizer::lexCommandKeyValue(PosStr& str) {
    __trace();
    while (!str.finished()) {
        switch (str.get().unicode()) {
            case '-': {
                auto flag = str.tok(
                    otk::CommandFlag,
                    skipZeroOrMore,
                    cr(CharSet{QChar('-')} + charsets::IdentChars));
                __push(flag);
                break;
            }
            case ':': {
                auto command = str.tok(
                    otk::CommandKey,
                    skipZeroOrMore,
                    cr(charsets::IdentChars
                       + CharSet{QChar('-'), QChar(':')}));
                __push(command);
                break;
            }
            case ' ': {
                str.space();
                break;
            }
            default: {
                auto value = str.tok(otk::CommandValue, [](PosStr& str) {
                    auto hasColon = false;
                    while (!str.finished() && !hasColon) {
                        while (!str.finished()
                               && !str.at(charsets::HorizontalSpace)) {
                            str.next();
                        }
                        if (!str.finished()) {
                            auto tmp = str;
                            tmp.space();
                            if (!tmp.at(QChar(':'))) {
                                tmp.next();
                                str = tmp;
                            } else {
                                hasColon = true;
                            }
                        }
                    }
                });
                __push(value);
            }
        }
    }
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

    auto start = str.fakeTok(wrapStart);
    __push(start);
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
            lexCommandOptions(str);
            break;
        }
        case ock::Caption: {
            auto caption = str.tok(otk::Text, skipPastEOF);
            __push(caption);
            break;
        }
        case ock::Call: {
            lexCommandCall(str);
            break;
        }
        case ock::BeginSrc: {
            auto src = str.tok(
                otk::Word, skipZeroOrMore, charsets::IdentChars);
            __push(src);
            str.space();
            lexCommandKeyValue(str);
            break;
        }
        case ock::BeginTable:
        case ock::AttrHtml: {
            lexCommandKeyValue(str);
            break;
        }
        case ock::BeginDynamic: {
            auto dyn = str.tok(
                otk::Word, skipZeroOrMore, charsets::IdentChars);
            __push(dyn);
            str.space();
            lexCommandKeyValue(str);
            break;
        }
        case ock::Header: {
            str.space();
            lexCommandKeyValue(str);
            break;
        }
        case ock::Author:
        case ock::Creator:
        case ock::Language: {
            str.space();
            auto lang = str.tok(otk::RawText, skipPastEOF);
            __push(lang);
            break;
        }
        case ock::Property: {
            lexCommandProperty(str);
            break;
        }
        case ock::Filetags: {
            while (str.at(QChar(':'))) {
                str.skip(QChar(':'));
                if (!str.finished()) {
                    auto subtree = str.tok(
                        otk::SubtreeTag, [](PosStr& str) {
                            while (!str.finished()
                                   && !str.at(QChar(':'))) {
                                str.next();
                            }
                        });
                    __push(subtree);
                }
            }
            break;
        }
        case ock::Include: {
            lexCommandInclude(str);
            break;
        }
        case ock::Name:
        case ock::LatexClass:
        case ock::LatexCompiler:
        case ock::BeginAdmonition: {
            str.space();
            auto ident = str.tok(otk::Ident, skipPastEOF);
            __push(ident);
            break;
        }
        case ock::Columns:
        case ock::BeginExample:
        case ock::Results:
        case ock::LatexHeader:
        case ock::HtmlHead:
        case ock::BeginCenter:
        case ock::LatexClassOptions: {
            auto text = str.tok(otk::RawText, skipPastEOF);
            __push(text);
            break;
        }
        default: {
            assert(false);
            // throw newUnexpectedKindError(kind, toStr(str));
            auto text = str.tok(otk::RawText, skipPastEOF);
            __push(text);
        }
    }

    auto end = str.fakeTok(wrapEnd);
    __push(end);
}

void OrgTokenizer::lexCommandBlock(PosStr& str) {
    __trace();

    // Store position of the command start - content be dedented or
    // indented
    // arbitrarily, so `#+begin_src` starting at column 2 might have content
    // that starts on the column 0.
    const auto column = str.getColumn();
    auto       prefix = str.tok(otk::CommandPrefix, skipOne, "#+");
    __push(prefix);
    const auto id = str.slice(skipZeroOrMore, OCommandChars);
    if (normalize(id.toStr()).startsWith("begin")) {
        lexCommandBlockDelimited(str, id, column);
    } else {
        auto line = Token(otk::LineCommand, id.view);
        __push(line);
        auto colon = str.tok(otk::Colon, skipOne, QChar(':'));
        __push(colon);
        str.space();
        auto args = str.slice(skipToEOL);
        lexCommandArguments(args, classifyCommand(id.toStr()));
        if (!str.finished()) {
            str.skip(ONewline);
        }
    }
}

bool OrgTokenizer::isFirstOnLine(CR<PosStr> str) {
    const auto set = charsets::Newline + CharSet{QChar('\0')};
    if (str.at(set, -1)) {
        return true;
    }

    auto pos = -1;
    while (str.at(charsets::HorizontalSpace, pos)) {
        --pos;
    }
    return str.at(set, pos);
}

bool OrgTokenizer::atLogClock(CR<PosStr> str) {
    PosStr     tmp   = str;
    const auto ahead = tmp.slice(skipTo, QChar('['));
    const auto space = ahead.getSkip(QChar('C'));
    if (0 <= space) {
        for (const auto ch : ahead[slice(0, space - 1)].view) {
            if (ch != OSpace) {
                return false;
            }
        }

        return ahead[slice(space, 1_B)].at("CLOCK:::");
    } else {
        return false;
    }
}

bool OrgTokenizer::atSubtreeStart(CR<PosStr> str) {
    if (str.getIndent() == 0 && str.at(OSubtreeStart)) {
        auto shift = 0;
        while (str.at(OSubtreeStart, shift)) {
            ++shift;
        }
        return str.at(OSpace, shift);
    } else {
        return false;
    }
}

bool OrgTokenizer::atConstructStart(CR<PosStr> str) {
    if (!isFirstOnLine(str)) {
        return false;
    } else if (atSubtreeStart(str)) {
        return true;
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
                auto tmp = str.fakeTok(otk::Indent);
                __push(tmp);
                break;
            }
            case LK::likDecIndent: {
                auto tmp = str.fakeTok(otk::Dedent);
                __push(tmp);
                break;
            }
            case LK::likSameIndent: {
                auto tmp = str.fakeTok(otk::SameIndent);
                __push(tmp);
                break;
            }
            case LK::likNoIndent: {
                auto tmp = str.fakeTok(otk::NoIndent);
                __push(tmp);
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
        str.at(CharSet{QChar('-'), QChar('+')})
        || (0 < str.getIndent() && str.at(OSubtreeStart))) {
        str.skip(ListStart);
        return str.at(OSpace);
    } else if (str.at(charsets::Digits + charsets::AsciiLetters)) {
        // HACK only handle lists that start with 1-3 characters, `AAAAA.`
        // won't be hadled. This is a temporary workaround to allow
        // `regularWord.` at the start of the text. Ideally list detection
        // should consider the context.
        // for _ in 0 .. 2:
        //
        // NOTE seems like org-mode only handles list elements with a
        // single starting letter and I don't think there is any reason to
        // implement a different handlig mode.
        str.tok(otk::ListItemStart, [](PosStr& str) {
            if (str.at(charsets::Digits + charsets::AsciiLetters)) {
                str.next();
            } else {
                return;
            }
        });

        return str.at(QChar(')')) || str.at(QChar('.'));
    } else {
        if (str.at(OBulletListStart)) {
            str.next();
        } else {
            return false;
        }

        return str.at(OSpace);
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
    if (str.at(CharSet{QChar('-'), QChar('+')})
        || (0 < str.getIndent() && str.at(OBulletListStar))) {
        __trace("At bullet list start");
        auto tok = str.tok(otk::ListItemStart, skipOne, OBulletListStart);
        __push(tok);
        str.space();
    } else {
        __trace("At numbered list start");
        __push((str.tok(
            otk::ListStart,
            skipOne,
            cr(charsets::Digits + charsets::AsciiLetters))));

        str.skip(cr(CharSet{QChar(')'), QChar('.')}));
        str.space();
    }

    if (str.at("\\[[Xx - ]\\]")) {
        __push((str.tok(otk::Checkbox, [](PosStr& str) {
            str.skip(QChar('['));
            str.skip(CharSet{QChar('X'), QChar('x'), OSpace, QChar('-')});
            str.skip(QChar(']'));
        })));

        str.space();
    }
}

void OrgTokenizer::lexListDescription(
    PosStr&           str,
    int               indent,
    LexerStateSimple& state) {
    __trace("Try parsing list header");
    Opt<PosStr> descriptionSlice;
    PosStr      tmp = str;
    tmp.pushSlice();
    while (!tmp.finished() && !tmp.at(charsets::Newline)) {
        if (tmp.at("::")) {
            descriptionSlice = tmp.popSlice();
            break;
        } else {
            tmp.next();
        }
    }

    if (descriptionSlice.has_value()) {
        auto open = str.fakeTok(otk::ListDescOpen);
        __push(open);
        auto desc  = Token(otk::Text, descriptionSlice.value().view);
        auto close = str.fakeTok(otk::ListDescClose);
        __push(close);
        auto colon = tmp.tok(otk::DoubleColon, skipOne, "::");
        __push(colon);
        str = tmp;
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
    while (str.view.at(slice.view.size()) == ONewline) {
        slice.view.chop(1);
    }

    auto token = Token(otk::StmtList, slice.view);
    pushResolved(token);
    __push(str.fakeTok(otk::ListItemEnd));
}

void OrgTokenizer::lexListItems(PosStr& str, LexerStateSimple& state) {
    __trace();
    assert(!str.at(ONewline));
    while (atListAhead(str) || atLogClock(str)) {
        // Minor hack -- in order to avoid logic duplication for logbook
        // and non-logbook parsers this function handles both edge cases.
        // The `CLOCK` entries are simply skipped, so the list lexer is not
        // especially troubled by the indentation levels: from the
        // standpoint of `skipIndents()` processing only happens on the
        // well-formed and well-indented list (not sure how often this
        // holds in reality though)
        assert(!str.at(ONewline));
        if (atLogClock(str)) {
            __push(str.fakeTok(otk::ListClock));
            str.pushSlice();
            str.skipToEOL();
            auto slice = str.popSlice();
            lexParagraph(slice);
            str.next();
            __push(str.fakeTok(otk::ListItemEnd));
        } else {
            // List start detection should handle several edge cases that
            // are hard to distinguish from each other, so first lexing is
            // /tried/, on success all changes are applied, on failure
            // entry is processed like a normal text element, without going
            // into deeper nesting levels.
            skipIndents(state, str);
            const auto indent = str.getColumn();
            if (atListStart(str)) {
                lexListItem(str, indent, state);
            } else {
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
        // __trace(
        //     ("Lexer iteration, get indent: $#, current indent $#, at "
        //      "construct $#, at list $#, is first on line $#"
        //      % to_string_vec(
        //          str.getIndent(),
        //          indent,
        //          atConstructStart(str),
        //          atListAhead(str),
        //          isFirstOnLine(str))));
        if (str.getIndent() == indent
            && (atConstructStart(str) || atListAhead(str))) {
            ended = true;
        } else if (str.at(ONewline)) {
            str.next();
            if (str.finished()) {
                ended = true;
            } else {
                if (str.at(charsets::TextLineChars)) {
                } else if (str.at(ONewline)) {
                    str.next();
                    ended = true;
                } else {
                    throw str.makeUnexpected(
                        "text line character or newline", "paragraph");
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
    switch (str.get().unicode()) {
        case '#': {
            auto pos        = str.getPos();
            bool isTableCmd = true;
            str.next();
            if (str.at(QChar('+'))) {
                str.skip(QChar('+'));
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
                            __push(str.tok(
                                otk::CmdArguments, skipTo, ONewline));
                            if (!str.finished()) {
                                str.skip(ONewline);
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
            if (str.at(QChar('|'))) {
                str.setPos(pos);
                bool first = true;
                while (!str.finished() && str.at(QChar('|'))) {
                    __push((str.tok(
                        first ? otk::PipeOpen : otk::PipeSeparator,
                        skipOne,
                        QChar('|'))));

                    first = false;
                    str.space();
                    if (!str.finished() && !str.at(ONewline)) {
                        __push((str.tok(otk::Content, [](PosStr& str) {
                            str.skipBefore(CharSet{QChar('|'), ONewline});
                            if (str.at(OSpace)) {
                                while (str.at(OSpace)) {
                                    str.back();
                                }
                                if (!str.at(OSpace)) {
                                    str.next();
                                }
                            } else {
                                str.next();
                            }
                        })));

                        str.space();
                    }
                }

                auto close = str.fakeTok(otk::PipeClose);
                __push(close);
            } else {
                str.setPos(pos);
                auto open = str.tok(
                    otk::PipeCellOpen, skipOne, QChar('|'));
                __push(open);
                str.space();
                auto content = str.tok(otk::Content, skipToEOL);
                __push(content);
                if (!str.finished()) {
                    str.skip(ONewline);
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
                auto arguments = str.tok(otk::CmdArguments, skipPastEOL);
                __push(arguments);
            } else {
                auto content = str.tok(otk::Content, [](PosStr& str) {
                    while (!str.finished()
                           && !str.at(CharSet{QChar('|'), QChar('#')})) {
                        str.skipPastEOL();
                    }
                    if (!str.finished()) {
                        str.back();
                    }
                });
                __push(content);

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
    switch (str.get(0).unicode()) {
        case '\x00': break;
        case '#': {
            switch (str.get(1).unicode()) {
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
                        // Paragraph starts with hashtag `#testing something`
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
            // No whitespace between a start and a character means it is a
            // bold word, otherwise it is a structural element - either
            // subtree or a unordered list.
            if (str.getColumn() == 0) {
                if (atSubtreeStart(str)) {
                    // `*bold*` world at the start of the paragraph
                    lexSubtree(str);
                } else {
                    // `* subtree` starting on the first line
                    lexParagraph(str);
                }
            } else {
                if (str.at(OSubtreeOrList, 0)
                    && str.at(CharSet{OSpace}, 1)) {
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
                auto sep = str.tok(
                    otk::TextSeparator, skipOneOrMore, QChar('-'));
                __push(sep);
                str.skip(ONewline);
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
                str.skipZeroOrMore(CharSet{OSpace, ONewline});
                lexStructure(str);
            }
            break;
        }

        default: {
            if ((charsets::MaybeLetters + CharSet{QChar('~'), QChar('[')})
                    .contains(str.get(0))) {
                lexParagraph(str);
            } else {
                // Text starts with inline or display latex math
                // equation,
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
        case ReportKind::Print: {
            os << "  " << in.line << ":" << in.subname.value();
            break;
        }

        case ReportKind::SetBuffer: {
            os << "  ! set buffer";
            break;
        }

        case ReportKind::ClearBuffer: {
            os << "  ! clear buffer";
            break;
        }

        case ReportKind::PushResolved: {
            os << "  + push resolved";
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
    auto str = PosStr(token.getText());
    switch (token.kind) {
        case otk::Text: {
            // generic 'text' token was found somewhere in the main
            // structure of
            // the document - list content, `#+caption` element etc. In that
            // context it only had defined boundaries but further lexing
            // was deferred until now, to avoid repeating the same
            // construct dozen times.
            __push(str.fakeTok(otk::ParagraphStart));
            while (!str.finished()) {
                lexText(str);
            }
            __push(str.fakeTok(otk::ParagraphEnd));
            break;
        }

        case otk::RawLogbook: {
            auto str = PosStr(token.getText());
            __push(str.fakeTok(otk::LogbookStart));
            // Logbook is made up of several list entries which in turn
            // (that's why the first pass is constrained to list and second
            // is not constrained to anything) might contain complex nested
            // elements
            while (!str.finished()) {
                if (atLogClock(str)) {
                    __push(str.tok(otk::Text, skipToEOL));
                    // text processing about should not include end of
                    // line.
                    if (str.at(charsets::Newline)) {
                        str.next();
                        // If this is a joined list of log entires skip
                        // only newline, otherwise cut all leading spaces
                        // to avoid messing up indentation in the list
                        // parser.
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
            // Table might contain any structure, including more complex
            // elements such as lists, code blocks, other tables and so on.
            // This is an imporvement on top of the regular org-mode syntax
            // (although IIUC elisp parser would also allow for structures
            // like these)
            lexGlobal(str);
            auto end = str.fakeTok(otk::ContentEnd);
            __push(end);
            break;
        }

        case otk::StmtList: {
            auto open = str.fakeTok(otk::StmtListOpen);
            __push(open);
            lexGlobal(str);
            auto close = str.fakeTok(otk::StmtListClose);
            __push(close);
            break;
        }

        default: {
            __push(token);
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
