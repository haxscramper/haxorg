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

#define __print2(__text, __str)                                           \
    report(Report{                                                        \
        .line     = __LINE__,                                             \
        .location = __CURRENT_FILE_PATH__,                                \
        .kind     = ReportKind::Print,                                    \
        .str      = __str,                                                \
        .subname  = __text});

#define __print1(__text) __print2(__text, &str)

#define __print(...)                                                      \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__print, __VA_ARGS__)(__VA_ARGS__),             \
        BOOST_PP_EMPTY())


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

#define __push2(token, __is_buffered)                                     \
    {                                                                     \
        Report rep      = __INIT_REPORT(std::nullopt, str);               \
        rep.kind        = ReportKind::Push;                               \
        rep.tok         = token;                                          \
        auto id         = push(token);                                    \
        rep.id          = id;                                             \
        rep.addBuffered = __is_buffered;                                  \
        report(rep);                                                      \
    }

#define __push1(token) __push2(token, false);

#define __push(...)                                                       \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__push, __VA_ARGS__)(__VA_ARGS__),              \
        BOOST_PP_EMPTY())

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


struct AdvCheck {
    int           pos = 0;
    CR<PosStr>    str;
    OrgTokenizer* tok;
    QString       func;
    struct Error : public std::runtime_error {
        explicit Error(QString const& msg)
            : std::runtime_error(msg.toStdString()) {}
    };

    AdvCheck(CR<PosStr> str, OrgTokenizer* tok, CR<QString> func)
        : pos(str.getPos()), str(str), tok(tok), func(func) {}
    ~AdvCheck() {
        if (!(pos < str.getPos())) {
            throw Error(
                "Positional string did not advance at $# in $#: position "
                "remained equal to $#. Str: '$#'"
                % to_string_vec(
                    tok->getLoc(str),
                    func,
                    pos,
                    str.printToString({.withSeparation = false}, false)));
        }
    }
};

#define __adv_check()                                                     \
    AdvCheck CONCAT(advance, __COUNTER__){str, this, __func__};

const CharSet ListStart = CharSet{QChar('-'), QChar('+'), QChar('*')}
                        + charsets::Digits + charsets::AsciiLetters;
using Err = OrgTokenizer::Errors;

void OrgTokenizer::oskipOne(PosStr& str, CR<PosStr::CheckableSkip> skip) {
    if (str.atAny(skip)) {
        str.skipAny(skip);
    } else {
        throw wrapError(Err::UnexpectedChar(str, skip));
    }
}

OrgToken OrgTokenizer::error(CR<TokenizerError> err) {
    auto tmp = err;
    if (locationResolver) {
        PosStr str{err.getView(), err.getPos()};
        tmp.setLoc(locationResolver(str));
    }
    errors.push_back(err);
    return Token(otk::ErrorTerminator, errors.high());
}

#define __report_error(err)                                               \
    {                                                                     \
        Report rep = Report(                                              \
            {.line  = __LINE__,                                           \
             .kind  = ReportKind::Error,                                  \
             .name  = __func__,                                           \
             .error = err});                                              \
        report(rep);                                                      \
    }

#define __report_and_throw(expr)                                          \
    {                                                                     \
        auto __err = TokenizerError(expr);                                \
        if (locationResolver) {                                           \
            PosStr str{__err.getView(), __err.getPos()};                  \
            __err.setLoc(locationResolver(str));                          \
        }                                                                 \
                                                                          \
        __report_error(__err);                                            \
        throw __err;                                                      \
    }

#define __start(str) startGroup(str);
#define __end(str) endGroup(str);

#define __fail_group(err)                                                 \
    auto tok = error(err);                                                \
    __report_error(err);                                                  \
    __push(tok);                                                          \
    __end(str);


void OrgTokenizer::spaceSkip(PosStr& str, bool require) {
    OrgToken tmp = require ? str.tok(
                       otk::SkipSpace,
                       skipOneOrMore,
                       charsets::HorizontalSpace)
                           : str.tok(
                               otk::SkipSpace,
                               skipZeroOrMore,
                               charsets::HorizontalSpace);

    if (0 < tmp.size()) {
        __push(tmp);
    }
}

void OrgTokenizer::startGroup(PosStr& str) {
    auto   token = str.fakeTok(otk::GroupStart);
    Report rep   = __INIT_REPORT(std::nullopt, str);
    rep.kind     = ReportKind::Push;
    rep.tok      = token;
    auto id      = push(token);
    rep.id       = id;
    report(rep);
    groupStack.push_back(id);
}


void OrgTokenizer::endGroup(PosStr& str) {
    auto   token = str.fakeTok(otk::GroupEnd);
    Report rep   = __INIT_REPORT(std::nullopt, str);
    rep.kind     = ReportKind::Push;
    rep.tok      = token;
    auto id      = push(token);
    rep.id       = id;
    report(rep);
    OrgTokenId start = groupStack.pop_back_v();
    // might be nil if we are in the buffered lexer at the moment
    if (!start.isNil()) {
        at(start).text = static_cast<int>(distance(start, id));
    }
}

void OrgTokenizer::newlineSkip(PosStr& str) {
    auto tmp = str.tok(otk::SkipNewline, skipOne, cr(QChar('\n')));
    __push(tmp);
}

QString OrgTokenizer::debugPos(CR<PosStr> str) const {
    QString res;
    if (locationResolver) {
        auto loc = locationResolver(str);
        res      = "$#:$#" % to_string_vec(loc.line, loc.column);
    }

    return res;
}

bool OrgTokenizer::lexAngle(PosStr& str) {
    __trace();
    __start(str);
    try {
        if (str.at("<%%")) {
            auto tok = str.tok(otk::DiaryTime, [this](PosStr& str) {
                oskipOne(str, "<%%");
                skipBalancedSlice(
                    str,
                    {.openChars  = CharSet{QChar('(')},
                     .closeChars = CharSet{QChar(')')}});
                oskipOne(str, ">");
            });
            __push(tok);
        } else if (str.at("<<<")) {
            __push((str.tok(otk::TripleAngleOpen, skipCount, 3)));
        } else if (str.at("<<")) {
            __push((str.tok(otk::DoubleAngleOpen, skipCount, 2)));
            __push((str.tok(otk::RawText, skipTo, QChar('>'))));
            __push((str.tok(otk::RawText, skipCb(">>"))));
        } else if (str.at(charsets::Digits, 1)) {
            auto skipAngles = [this](PosStr& str) {
                oskipOne(str, QChar('<'));
                str.skipTo(QChar('>'));
                oskipOne(str, QChar('>'));
            };

            __push((str.tok(otk::AngleTime, skipAngles)));

            if (str.at("--")) {
                __push((str.tok(otk::TimeDash, skipCount, 2)));
                __push((str.tok(otk::AngleTime, skipAngles)));
            }
        } else {
            __push((str.tok(otk::AngleOpen, skipCount, 1)));
            __push((str.tok(otk::RawText, skipTo, QChar('>'))));
            __push((str.tok(otk::AngleClose, skipCb('>'))));
        }
        return true;
    } catch (TokenizerError& err) {
        __fail_group(err);
        return false;
    }
}

bool OrgTokenizer::lexTime(PosStr& str) {
    __trace();
    if (str.at(QChar('<'))) {
        lexAngle(str);
    } else if (str.at(QChar('['))) {
        auto skipBracket = [this](PosStr& str) {
            oskipOne(str, QChar('['));
            str.skipTo(QChar(']'));
            oskipOne(str, QChar(']'));
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

    if (str.at(" => ")) {
        spaceSkip(str);
        auto arr = str.tok(otk::TimeArrow, skipOne, "=>");
        __push(arr);
        spaceSkip(str);
        auto dur = str.tok(otk::TimeDuration, [this](PosStr& str) {
            while (str.get().isDigit()) {
                str.next();
            }
            oskipOne(str, ':');
            while (str.get().isDigit()) {
                str.next();
            }

            str.trySkip("am")        //
                || str.trySkip("pm") //
                || str.trySkip("AM") //
                || str.trySkip("PM");
        });
        __push(dur);
    }

    return true;
}

bool OrgTokenizer::lexLinkTarget(PosStr& str) {
    __trace();
    if (str.at("https") || str.at("http")) {
        auto tok = str.tok(otk::LinkFull, [](PosStr& str) {
            while (str.notAt(' ')) {
                str.next();
            }
        });
        __push(tok);
    } else if (
        str.at("file") || str.at("attachment") || str.at("docview")
        || str.at(QChar('/')) || str.at("./")) {

        if (str.at(QChar('.')) || str.at(QChar('/'))) {
            auto protocol = str.fakeTok(otk::LinkProtocol);
            __push(protocol);
        } else {
            auto protocol = str.tok(otk::LinkProtocol, skipTo, QChar(':'));
            __push(protocol);
            oskipOne(str, QChar(':'));
        }

        auto target = str.tok(otk::LinkTarget, [](PosStr& str) {
            while (str.notAt("::")) {
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
            oskipOne(str, QChar(':'));
            auto target = str.tok(otk::LinkTarget, skipPastEOF);
            __push(target);
        } else {
            auto intern = str.tok(otk::LinkInternal, skipPastEOF);
            __push(intern);
        }
    }
    return true;
}

bool OrgTokenizer::lexLink(PosStr& str) {
    __trace();
    __start(str);
    try {
        auto open = str.tok(otk::LinkOpen, skipCb('['));
        __push(open);
        // link_token
        {
            auto open = str.tok(otk::LinkTargetOpen, skipCb('['));
            __push(open);
            PosStr target = str.slice(skipTo, QChar(']'));
            lexLinkTarget(target);
            auto close = str.tok(otk::LinkTargetClose, skipCb(']'));
            __push(close);
        };
        // description_token
        {
            if (str.at(QChar('['))) {
                auto descrOpen = str.tok(
                    otk::LinkDescriptionOpen, skipCb('['));
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
                    otk::LinkDescriptionClose, skipCb(']'));
                __push(descrClose);
            }
        }
        auto linkClose = str.tok(otk::LinkClose, skipCb((']')));
        __push(linkClose);
        __end(str);
        return true;
    } catch (TokenizerError& err) {
        __fail_group(err);
        return false;
    }
}

bool OrgTokenizer::lexFootnote(PosStr& str) {
    __trace();
    __start(str);

    try {
        auto start = str.tok(otk::FootnoteStart, skipCb("[fn"));
        __push(start);
        if (str.at("::")) {
            auto couble = str.tok(otk::DoubleColon, skipCb("::"));
            __push(couble);
            // FIXME
            // result.addExpandTok(str, otk::Text,
            // str.skipTo(QChar(']')););
        } else {
            auto colon = str.tok(otk::Colon, skipCb(':'));
            __push(colon);
            auto ident = str.tok(otk::Ident, skipTo, QChar(']'));
            __push(ident);
        }
        auto end = str.tok(otk::FootnoteEnd, skipCb(']'));
        __push(end);
        __end(str);
        return true;
    } catch (TokenizerError& err) {
        __fail_group(err);
        return false;
    }
}

bool OrgTokenizer::lexBracket(PosStr& str) {
    __trace();
    if (str.at("[[")) {
        lexLink(str);
    } else if (str.at("[fn:") || str.at("[FN:")) {
        lexFootnote(str);
    } else {
        lexTime(str);
    }
    return true;
}

void skipCurly(PosStr& str) {
    skipBalancedSlice(
        str,
        BalancedSkipArgs{
            .openChars  = {QChar('{')},
            .endChars   = CharSet{},
            .closeChars = {QChar('}')}});
}

void skipParen(PosStr& str) {
    skipBalancedSlice(
        str,
        BalancedSkipArgs{
            .openChars  = {QChar('(')},
            .endChars   = CharSet{},
            .closeChars = {QChar(')')}});
}

void skipBrace(PosStr& str) {
    skipBalancedSlice(
        str,
        BalancedSkipArgs{
            .openChars  = {QChar('[')},
            .endChars   = CharSet{},
            .closeChars = {QChar(']')}});
}


bool OrgTokenizer::lexTextSrc(PosStr& str) {
    __trace();
    const auto    pos = str.getPos();
    Vec<OrgToken> buf;
    // Starting `src_` prefix
    {
        buf.push_back(str.tok(otk::SrcOpen, skipCb("src")));
        if (str.at(CharSet{QChar('_'), QChar('-')})) {
            str.next();
        }
    }

    if (str.at(charsets::IdentStartChars)) {
        // TODO push buffer only if the whole sequence is determined to be
        // a valid structure, otherwise roll back to the starting position
        // and lex things as 'maybe words'.
        for (const auto& tok : buf) {
            __push(tok, true);
        }
        auto name = str.tok(
            otk::SrcName, skipZeroOrMore, charsets::IdentChars);
        __push(name);
        if (str.at(QChar('['))) {
            auto args = str.tok(otk::SrcArgs, skipBrace, {1, -2});
            __push(args);
        }

        auto body = str.tok(otk::SrcBody, skipCurly, {1, -2});
        // TODO issue a warning if content contains too much elements that
        // might be invalid in particular context. Maybe this should be
        // done on a higher level, when language elements are decided.
        // Another possible solution is to provide diagnostic if there are
        // more than 3 lines of text in the source code. Something like
        // "are you sure you don't want to use source *block* instead?"
        __push(body);
        auto close = str.fakeTok(otk::SrcClose);
        __push(close);
    } else {
        str.setPos(pos);
        lexTextWord(str);
    }
    return true;
}

bool OrgTokenizer::lexTextCall(PosStr& str) {
    __trace();
    const auto    pos = str.getPos();
    Vec<OrgToken> buf;
    buf.push_back(str.tok(otk::CallOpen, skipCb("call")));
    if (str.at(CharSet{QChar('_'), QChar('-')})) {
        str.next();
    }
    if (str.at(charsets::IdentStartChars)) {
        for (const auto& tok : buf) {
            __push(tok, true);
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
    } else {
        str.setPos(pos);
        lexTextWord(str);
    }
    return true;
}


bool OrgTokenizer::lexTextWord(PosStr& str) {
    __trace();
    // TODO handle other cases like
    //
    // - Possible link google.com
    // - Possible e-mail address random@zyx.org
    // - Other URL formats
    // - words with dashes

    bool allUp = true;
    auto tok   = str.tok(otk::Word, [&](PosStr& str) {
        while (!str.finished() && str.get().isLetterOrNumber()) {
            if (str.get().toUpper() != str.get()) {
                __print(
                    ("'$#' is not a title case"
                     % to_string_vec(str.get())));
                allUp = false;
            }
            str.next();
        }
    });

    if (allUp) {
        tok.kind = otk::BigIdent;
    }

    __push(tok);
    return true;
}

/// Lex single text element that starts with an character -- `src_`,
/// `call_`, regular word, etc.
bool OrgTokenizer::lexTextChars(PosStr& str) {
    __trace();
    __adv_check();
    bool isStructure = false;

    if (str.at("src_") && str.getSkip('{', [](CR<PosStr> str, int offset) {
            return str.get(offset).isLetterOrNumber()
                || str.get(offset) == '_';
        })) {
        lexTextSrc(str);
    } else if (str.at("call[_-]?\\w+(\\[|\\{)")) {
        lexTextCall(str);
    } else if (str.at("https://") || str.at("http://")) {
        auto url = str.tok(otk::RawUrl, skipBefore, charsets::Whitespace);
        __push(url);
    } else {
        lexTextWord(str);
    }

    return true;
}

bool OrgTokenizer::lexParenArguments(PosStr& str) {
    __trace();
    auto open = str.tok(otk::ParOpen, skipCb('('));
    __push(open);
    while (str.notAt(QChar(')'))) {
        // Read argument until the first comma or closing parent
        auto raw = str.tok(
            otk::RawText,
            skipBefore,

            // TODO handle quoted strings and escaped commas
            cr(CharSet{QChar(','), QChar(')')}));
        __push(raw);

        // maybe lex comma
        if (str.at(QChar(','))) {
            auto comma = str.tok(otk::Comma, skipCb(','));
            __push(comma);
        }

        // optional space, not significant for argument passing
        spaceSkip(str);
    }
    auto close = str.tok(otk::ParClose, skipCb(')'));
    __push(close);
    return true;
}

bool OrgTokenizer::lexTextDollar(PosStr& str) {
    __trace();
    auto          tmp = str;
    Vec<OrgToken> buf;
    try {
        if (tmp.at(QChar('$'), 1)) {
            buf.push_back(tmp.tok(otk::DollarOpen, skipCb("$$")));
            tmp.pushSlice();
            bool hasEnd = false;
            while (!tmp.finished() && !hasEnd) {
                while (tmp.notAt(QChar('$'))) {
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
            qDebug() << getLoc(str) << str;

            buf.push_back(tmp.tok(otk::DollarOpen, skipCb('$')));
            buf.push_back(
                tmp.tok(otk::LatexInlineRaw, skipBefore, QChar('$')));
            buf.push_back(tmp.tok(otk::DollarClose, skipCb('$')));
        }
        for (const auto& tok : buf) {
            __push(tok);
        }
        str = tmp;
    } catch (UnexpectedCharError& err) {
        auto punct = str.tok(otk::Punctuation, skipZeroOrMore, QChar('$'));
        __push(punct);
    }
    return true;
}

bool OrgTokenizer::lexSlashEntity(PosStr& str) {
    __trace();
    __start(str);
    try {
        if (str.at(OMarkupChars, 1)) {
            auto esc = str.tok(otk::Escaped, skipCount, 1);
            __push(esc);
        } else if (str.at(
                       charsets::IdentStartChars - CharSet{QChar('_')},
                       1)) {
            auto sym = str.tok(otk::SymbolStart, skipCb('\\'));
            __push(sym);
            auto ident = str.tok(
                otk::Ident, skipZeroOrMore, charsets::IdentChars);
            __push(ident);
            if (str.at(QChar('['))) {
                auto open = str.tok(otk::MetaBraceOpen, skipCb('['));
                __push(open);
                auto body = str.tok(otk::MetaBraceBody, [](PosStr& str) {
                    skipBalancedSlice(
                        str,
                        {.openChars    = {QChar('[')},
                         .closeChars   = {QChar(']')},
                         .skippedStart = true,
                         .consumeLast  = false});
                });
                __push(body);
                auto close = str.tok(otk::MetaBraceClose, skipCb(']'));
                __push(close);
            }
            while (str.at(QChar('{'))) {
                auto open = str.tok(otk::MetaArgsOpen, skipCb('{'));
                __push(open);
                auto body = str.tok(otk::MetaBraceBody, [](PosStr& str) {
                    skipBalancedSlice(
                        str,
                        {.openChars    = {QChar('{')},
                         .closeChars   = {QChar('}')},
                         .skippedStart = true,
                         .consumeLast  = false});
                });
                __push(body);

                auto close = str.tok(otk::MetaArgsClose, skipCb('}'));
                __push(close);
            }
        } else {
            auto esc = str.tok(otk::Escaped, skipCount, 2);
            __push(esc);
        }
        return true;
    } catch (TokenizerError& err) {
        __fail_group(err);
        return false;
    }
}

bool OrgTokenizer::lexSlashMath(PosStr& str) {
    __trace();
    __start(str);
    try {
        const auto isInline = str.at(QChar('('), 1);

        if (isInline) {
            auto open = str.tok(otk::LatexParOpen, skipCb("\\("));
            __push(open);
        } else {
            auto open = str.tok(otk::LatexBraceOpen, skipCb("\\["));
            __push(open);
        }

        auto latex = str.tok(
            otk::LatexInlineRaw, [&isInline](PosStr& str) {
                while (str.notAt(isInline ? "\\)" : "\\]")) {
                    str.next();
                }
            });
        __push(latex);

        if (isInline) {
            auto close = str.tok(otk::LatexParClose, skipCb(")"));
            __push(close);
        } else {
            auto close = str.tok(otk::LatexBraceClose, skipCb("]"));
            __push(close);
        }

        __end(str);
        return true;
    } catch (TokenizerError& err) {
        __fail_group(err);
        return false;
    }
}

bool OrgTokenizer::lexTextSlash(PosStr& str) {
    __trace();
    switch (str.get(1).unicode()) {
        case '[':
        case '(': {
            lexSlashMath(str);
            break;
        }
        case '\\': {
            auto slash = str.tok(otk::DoubleSlash, skipCb("\\"));
            __push(slash);
            break;
        }
        default: {
            lexSlashEntity(str);
        }
    }
    return true;
}

const auto NonText = CharSet{
    ONewline,
    OSpace,
    QChar(','),
    QChar('.'),
    QChar('\''),
    QChar('"'),
    QChar('/'),
} + charsets::PunctChars + charsets::AllSpace;


bool OrgTokenizer::lexTextVerbatim(PosStr& str) {
    __trace();
    const auto start = str.get();
    if (str.at(start, 1)) {
        auto open = str.tok(markupConfig[start].inlineKind, skipCount, 2);
        __push(open);
        auto text = str.tok(otk::RawText, [start](PosStr& str) {
            while (!str.finished()
                   && !(str.at(start, 0) && str.at(start, 1))) {
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
            auto text = str.tok(otk::RawText, [this, &start](PosStr& str) {
                bool ended = false;
                while (!str.finished() && !ended) {
                    while (str.notAt(start)) {
                        str.next();
                    }
                    if (str.at(start)
                        && (str.at(NonText, +1) || !str.hasNext(1))) {
                        ended = true;
                    } else {
                        str.next();
                    }
                }
            });

            __push(text);
            auto end = str.tok(
                markupConfig[start].finishKind, skipCb(start));
            __push(end);
        } else {
            auto punct = str.tok(otk::Punctuation, skipCount, 1);
            __push(punct);
        }
    }
    return true;
}

bool OrgTokenizer::lexTextCurly(PosStr& str) {
    __trace();
    if (str.at("{{{")) {
        auto open = str.tok(otk::MacroOpen, skipCount, 3);
        __push(open);
        auto ident = str.tok(otk::Ident, [](PosStr& str) {
            while (str.notAt(QChar('(')) && str.notAt("}}}")) {
                str.next();
            }
        });
        __push(ident);

        if (str.at(QChar('('))) {
            lexParenArguments(str);
        }
        if (!str.finished()) {
            auto close = str.tok(otk::MacroClose, skipCb("}}}"));
            __push(close);
        }
    } else {
        auto word = str.tok(otk::MaybeWord, skipCount, 1);
        __push(word);
    }
    return true;
}

bool OrgTokenizer::lexTextMarkup(PosStr& str) {
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
    return true;
}

bool OrgTokenizer::lexHashTag(PosStr& str) {
    __trace();
    auto head = str.tok(otk::HashTag, [](PosStr& str) {
        str.trySkip(QChar('#'));
        str.skipZeroOrMore(charsets::IdentChars);
    });
    __push(head);

    while (str.at("##") && str.notAt("##[")) {
        auto sub = str.tok(otk::HashTagSub, skipCb(('#')));
        __push(sub);
        auto hash = str.tok(otk::HashTag, [this](PosStr& str) {
            oskipOne(str, QChar('#'));
            str.skipZeroOrMore(charsets::IdentChars);
        });
        __push(hash);
    }

    if (str.at("##[")) {
        auto join = str.tok(otk::HashTagSub, skipCb(('#')));
        __push(join);
        auto open = str.tok(otk::HashTagOpen, skipCb("#["));
        __push(open);

        while (str.notAt(QChar(']'))) {
            lexHashTag(str);
            spaceSkip(str);
            if (str.at(QChar(','))) {
                auto comma = str.tok(otk::Comma, skipCb((',')));
                __push(comma);
                spaceSkip(str);
            }
        }

        auto close = str.tok(otk::HashTagClose, skipCb((']')));
        __push(close);
    }
    return true;
}

bool OrgTokenizer::lexText(PosStr& str) {
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
            // TODO handle more edge cases for the latex token placement
            if (str.get(-1) == ' ') {
                lexTextDollar(str);
            } else {
                auto punct = str.tok(otk::Punctuation, skipCount, 1);
                __push(punct);
            }
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
        case '-':
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
            if (str.at(
                    markupKeys
                    - CharSet{
                        QChar('<'), QChar('~'), QChar('`'), QChar('=')})) {
                lexTextMarkup(str);
            } else if (str.get().isLetterOrNumber()) {
                lexTextChars(str);
            } else if (str.get().isPunct()) {
                auto punct = str.tok(otk::Punctuation, skipCount, 1);
                __push(punct);
            } else {
                auto circ = str.tok(otk::RawText, skipCount, 1);
                __push(circ);
                break;
            }
        }
    }
    return true;
}

bool OrgTokenizer::lexProperties(PosStr& str) {
    __trace();
    __start(str);
    try {
        auto hasEnd = false;
        while (!str.finished() && !hasEnd) {
            spaceSkip(str);
            auto       isAdd = false;
            const auto id    = str.slice([this, &isAdd](PosStr& str) {
                oskipOne(str, QChar(':'));
                str.skipZeroOrMore(charsets::IdentChars);
                if (str.at(QChar('+'))) {
                    isAdd = true;
                }
                oskipOne(str, QChar(':'));
            });

            if (normalize(id.toStr()) == "end") {
                hasEnd   = true;
                auto end = Token(otk::ColonEnd, id.view);
                __push(end);
            } else if (Vec<Str>{"end", "logbook", "description"}.contains(
                           normalize(id.toStr()))) {
                auto err = Errors::MissingElement(
                    str, "closing :end:", "property drawer");
                __report_and_throw((err));
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
                    oskipOne(str, QChar(':'));
                }
                spaceSkip(str);
                auto prop = str.tok(otk::RawProperty, skipToEOL);
                __push(prop);
                newlineSkip(str);
            }
        }
        __end(str);
        return true;
    } catch (TokenizerError& err) {
        __fail_group(err);
        return false;
    }
}

bool OrgTokenizer::lexDescription(PosStr& str) {
    __trace();
    str.pushSlice();
    auto hasEnd = false;
    while (!str.finished() && !hasEnd) {
        while (str.notAt(":end:")) {
            str.next();
        }
        auto text = Token(otk::Text, str.popSlice().view);
        pushResolved(text);
        const auto id  = str.slice([this](PosStr& str) {
            oskipOne(str, QChar(':'));
            str.skipZeroOrMore(charsets::IdentChars);
            oskipOne(str, QChar(':'));
        });
        auto       end = Token(otk::ColonEnd, id.view);
        __push(end);
        hasEnd = true;
    }
    return true;
}

bool OrgTokenizer::lexLogbook(PosStr& str) {
    __trace();
    __start(str);
    try {
        str.pushSlice();
        auto hasEnd = false;
        while (!str.finished() && !hasEnd) {
            str.space();
            if (!str.finished() && !(str.at(":end:") || str.at(":END"))) {
                str.skipToNextLine();
                continue;
            }

            auto slice = str.popSlice();
            auto raw   = Token(otk::RawLogbook, slice.view);
            pushResolved(raw);

            const auto id = str.slice([this](PosStr& str) {
                oskipOne(str, QChar(':'));
                str.skipZeroOrMore(charsets::IdentChars);
                oskipOne(str, QChar(':'));
            });

            auto end = Token(otk::ColonEnd, id.view);
            __push(end);
            hasEnd = true;
        }
        return true;
    } catch (TokenizerError& err) {
        __fail_group(err);
        return false;
    }
}

bool OrgTokenizer::lexDrawer(PosStr& str) {
    __trace();
    __start(str);
    spaceSkip(str);
    auto strEnded = false;
    while (!str.finished() && !strEnded) {
        // qDebug() << str;
        spaceSkip(str);
        const auto id = str.slice([this](PosStr& str) {
            oskipOne(str, QChar(':'));
            str.skipZeroOrMore(charsets::IdentChars);
            oskipOne(str, QChar(':'));
        });

        const Str norm = normalize(id.toStr());
        if (norm == "properties") {
            auto prop = Token(otk::ColonProperties, id.view);
            __push(prop);
            // newline skip is replicated across all branches to ensure
            // correct token ordering for skipped content
            newlineSkip(str);
            lexProperties(str);
        } else if (norm == "logbook") {
            auto log = Token(otk::ColonLogbook, id.view);
            __push(log);
            newlineSkip(str);
            lexLogbook(str);
        } else if (norm == "description") {
            auto desc = Token(otk::ColonDescription, id.view);
            __push(desc);
            newlineSkip(str);
            lexDescription(str);
        } else {
            throw ImplementError(
                "Drawer element '$#' has not been implemented yet "
                "(normalized as '$#')"
                % to_string_vec(id.toStr(), norm));
        }
        // qDebug() << str;

        auto ahead = str;
        ahead.space();
        if (ahead.trySkip(ONewline)) {
            ahead.space();
            if (ahead.notAt(QChar(':'))) {
                strEnded = true;
                str      = ahead;
            }
        }
        // qDebug() << strEnded;
        if (!strEnded) {
            while (str.at(ONewline)) {
                newlineSkip(str);
            }
        }
        // qDebug() << str;
    }
    __end(str);
    return true;
}

bool OrgTokenizer::lexSubtreeTodo(PosStr& str) {
    __trace();
    auto tmp = str;
    tmp.pushSlice();
    tmp.skipZeroOrMore(charsets::HighAsciiLetters);
    if (tmp.at(OSpace)) {
        auto state = tmp.popTok(otk::SubtreeTodoState);
        __push(state);
        str = tmp;
    }
    return true;
}

bool OrgTokenizer::lexSubtreeUrgency(PosStr& str) {
    __trace();
    if (str.at("[#")) {
        str.pushSlice();
        str.next(2);
        oskipOne(str, charsets::HighAsciiLetters);
        str.skipZeroOrMore(charsets::HighAsciiLetters);
        oskipOne(str, QChar(']'));
        auto urg = str.popTok(otk::SubtreeUrgency);
        __push(urg);
        spaceSkip(str);
    }
    return true;
}

bool OrgTokenizer::lexSubtreeTitle(PosStr& str) {
    __trace();
    spaceSkip(str);
    auto body = str.slice(skipToEOL);

    QStringView      full = body.view;
    Opt<QStringView> tags;
    Opt<QStringView> completion;
    QStringView      title;

    if (full.endsWith(':')) {
        int shift = full.size() - 1;
        while (0 <= shift
               && (CharSet{QChar(':'), QChar('#'), QChar('@'), QChar('_')}
                       .contains(full.at(shift))
                   || full.at(shift).isLetterOrNumber())) {
            --shift;
        }

        tags = full.sliced(shift + 1, full.size() - shift - 1);
        full = full.sliced(0, shift).trimmed();
    }

    if (full.endsWith(']')) {
        int shift = full.size() - 1;
        if (full.at(shift) == ']') {
            --shift;
        } else {
            goto not_progress;
        }

        if (full.at(shift) == '%') {
            --shift;
            if (full.at(shift).isDigit()) {
                while (full.at(shift).isDigit()) {
                    --shift;
                }
            } else {
                goto not_progress;
            }

            if (full.at(shift) == '[') {
                --shift;
            } else {
                goto not_progress;
            }

        } else if (full.at(shift).isDigit()) {
            while (full.at(shift).isDigit()) {
                --shift;
            }

            if (full.at(shift) == '/') {
                --shift;
            } else {
                goto not_progress;
            }

            if (full.at(shift).isDigit()) {
                while (full.at(shift).isDigit()) {
                    --shift;
                }
            } else {
                goto not_progress;
            }
        } else {
            goto not_progress;
        }

        completion = full.sliced(shift + 1, full.size() - 1 - shift);
        full       = full.sliced(0, shift).trimmed();

    not_progress : {}
    }


    __print(
        ("Title parts: $# $# $#" % to_string_vec(full, completion, tags)));

    pushResolved(Token(otk::Text, full));

    if (completion.has_value()) {

        //   const auto finish = tmp.getPos();
        // tmp.skip(QChar(']'), -1);
        // tmp.skip(charsets::Digits, -1);
        // while (tmp.at(charsets::Digits)) {
        //     tmp.back();
        // }
        // if (str.at(QChar('%'))) {
        //     tmp.back();
        // } else {
        //     tmp.skip(QChar('/'), -1);
        //     tmp.skip(charsets::Digits, -1);
        //     while (tmp.at(charsets::Digits)) {
        //         tmp.back();
        //     }
        // }
        // tmp.skip(QChar('['), -1, -1);

        // const auto start = tmp.getPos() + 1;
        // body             = tmp;
        // headerTokens.push_back(Token(
        //     otk::SubtreeCompletion,
        //     tmp.sliceBetween(start, finish).view));
        // // __trace("Added progress", body);
        // while (body.at(OSpace)) {
        //     body.next(-1);
        // }
    }


    if (tags.has_value()) {
        PosStr str{tags.value()};
        while (str.at(':') && str.hasNext(1)) {
            auto sep = str.tok(otk::SubtreeTagSeparator, skipCount, 1);
            __push(sep);
            lexHashTag(str);
        }

        auto sep = str.tok(otk::SubtreeTagSeparator, skipCount, 1);
        __push(sep);
    }

    return true;
}

bool OrgTokenizer::lexSubtreeTimes(PosStr& str) {
    __trace();
    __start(str);
    try {
        bool done     = false;
        bool hadTimes = false;
        while (!done) {
            spaceSkip(str);
            auto ahead = str.getAhead(slice(0, 10)).toLower();
            if (ahead.startsWith("deadline:")
                || ahead.startsWith("closed:")
                || ahead.startsWith("scheduled:")) {
                auto tag = str.tok(
                    otk::SubtreeTime,
                    skipOneOrMore,
                    charsets::HighAsciiLetters);
                __push(tag);
                oskipOne(str, ':');
                spaceSkip(str);
                lexTime(str);
                hadTimes = true;
            } else {
                done = true;
            }
        }
        if (hadTimes) {
            newlineSkip(str);
        }
        __end(str);
        return true;

    } catch (TokenizerError& err) {
        __fail_group(err);
        return false;
    }
}

bool OrgTokenizer::lexSubtree(PosStr& str) {
    __trace();
    auto stars = str.tok(otk::SubtreeStars, skipZeroOrMore, OSubtreeStart);
    __push(stars);
    spaceSkip(str);
    lexSubtreeTodo(str);
    spaceSkip(str);
    lexSubtreeUrgency(str);
    spaceSkip(str);
    lexSubtreeTitle(str);
    __print(str.printToString());
    if (str.at(ONewline)) {
        newlineSkip(str);
    }

    __print(str.printToString());
    int skip = str.getSkip('\n');
    __print("Has next line? $#" % to_string_vec(skip));
    if (0 <= skip) {
        auto ahead = str.getAhead(slice(0, skip)).toLower();
        __print("Parse subtree etc. " + ahead);
        if (ahead.contains("deadline:") || ahead.contains("closed:")
            || ahead.contains("scheduled:")) {
            lexSubtreeTimes(str);
        } else {
            __print("No subtree times detected");
        }

        if (str.getSkip(
                ':',
                [](CR<PosStr> str, int skip) -> bool {
                    return str.notAt(' ', skip);
                })
            != -1) {
            lexDrawer(str);
        } else {
            __print("No subtree drawer detected");
        }
    }

    auto end = str.fakeTok(otk::SubtreeEnd);
    __push(end);
    return true;
}

bool OrgTokenizer::lexSourceBlockContent(PosStr& str) {
    __trace();
    while (!str.finished()) {
        if (str.at("<<")) {
            auto          failedAt = -1;
            auto          tmp      = str;
            Vec<OrgToken> tmpRes;
            // try_tangle
            {
                tmpRes.push_back(
                    tmp.tok(otk::DoubleAngleOpen, skipCb("<<")));
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
                        tmp.tok(otk::DoubleAngleClose, skipCb(">>")));
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
                    __push(tok, true);
                }
                str = tmp;
            }
        } else if (str.at("(refs:")) {
            auto open = str.tok(otk::ParOpen, skipCb(('(')));
            __push(open);
            auto ident = str.tok(otk::Ident, skipCb("refs"));
            __push(ident);
            auto colon = str.tok(otk::Colon, skipCb(":"));
            __push(colon);
            auto target = str.tok(
                otk::Ident,
                skipZeroOrMore,
                cr(charsets::IdentChars + CharSet{QChar('-')}));
            __push(target);
            auto close = str.tok(otk::ParClose, skipCb((')')));
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
    return true;
}

bool OrgTokenizer::lexCommandContent(
    PosStr&               str,
    const OrgCommandKind& kind) {
    __trace();
    auto content = str.fakeTok(otk::CommandContentStart);
    __push(content);
    switch (kind) {
        case ock::BeginQuote:
        case ock::BeginCenter:
        case ock::BeginAdmonition: {
            pushResolved(str.tok(otk::Text, skipPastEOF));
            break;
        }
        case ock::BeginExample: {
            auto text = str.tok(otk::RawText, skipPastEOF);
            __push(text);
            break;
        }
        case ock::BeginDynamic: {
            spaceSkip(str);
            auto text = str.tok(otk::Text, skipPastEOF);
            pushResolved(text);
            break;
        }
        case ock::BeginSrc: {
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
    return true;
}

Vec<OrgToken> OrgTokenizer::lexDelimited(
    PosStr&                          str,
    const Pair<QChar, OrgTokenKind>& start,
    const Pair<QChar, OrgTokenKind>& finish,
    const OrgTokenKind&              middle) {
    __trace();
    Vec<OrgToken> result;
    result.push_back(str.tok(start.second, skipCb(start.first)));
    result.push_back(str.tok(middle, [&finish](PosStr& str) {
        while (str.notAt(finish.first)) {
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

bool OrgTokenizer::lexCommandProperty(PosStr& str) {
    __trace();
    spaceSkip(str);
    auto ident = str.tok(
        otk::Ident, skipBefore, cr(CharSet{OSpace, QChar(':')}));
    __push(ident);
    if (str.at(QChar(':'))) {
        auto colon = str.tok(otk::Colon, skipCount, 1);
        __push(colon);
        auto ident = str.tok(otk::Ident, skipBefore, OSpace);
        __push(ident);
    }
    spaceSkip(str);
    auto prop = str.tok(otk::RawProperty, skipPastEOF);
    __push(prop);
    return true;
}

bool OrgTokenizer::lexTextAtSign(PosStr& str) {
    __trace();
    const auto AtChars = charsets::IdentChars + charsets::Utf8Any;
    if (str.at(AtChars, 1)) {
        auto mention = str.tok(
            otk::AtMention, [this, &AtChars](PosStr& str) {
                oskipOne(str, QChar('@'));
                str.skipZeroOrMore(AtChars);
            });
        __push(mention);
    } else {
        auto punct = str.tok(otk::Punctuation, skipCount, 1);
        __push(punct);
    }
    return true;
}

bool OrgTokenizer::lexCommandBlockDelimited(
    PosStr& str,
    PosStr  id,
    int     column) {
    __trace();
    auto begin = Token(otk::CommandBegin, id.view);
    __push(begin);

    const auto sectionName = normalize(id.toStr()).dropPrefix("begin");
    const auto kind        = classifyCommand(id.toStr());
    if (kind == ock::BeginDynamic) {
        oskipOne(str, QChar(':'));
    }
    spaceSkip(str);
    __print(str.printToString());
    auto arguments = str.slice({0, -1}, skipPastEOL);
    lexCommandArguments(arguments, kind);
    auto found = false;
    str.pushSlice();
    __trace("Search for block end");
    while (!found && !str.finished()) {
        str.space();
        if (!str.finished()
            && !(
                str.getColumn() == column
                && (str.at("#+end") || str.at("#+END")))) {
            str.skipToNextLine();
            continue;
        }

        const auto   prefix = str.slice(skipCount, 2);
        const PosStr id     = str.slice(skipZeroOrMore, OCommandChars);
        if (normalize(id.toStr()) == normalize("end" + sectionName)) {
            found = true;
            int offset
                = (1           /* Default offset */
                   + id.size() /* `end_<xxx>` */
                   + 3 /* and trailing newline */);
            auto slice = str.popSlice({0, -offset});
            lexCommandContent(slice, kind);
            auto pt = Token(otk::CommandPrefix, prefix.view);
            __push(pt);
            auto end = Token(otk::CommandEnd, id.view);
            __push(end);
        } else {
            auto err = Errors::MissingElement(
                str, "closing end", "section block " + sectionName);
            __report_and_throw((err));
        }
    }

    assert(found);
    if (kind == ock::BeginDynamic) {
        oskipOne(str, QChar(':'));
    }

    return true;
}

bool OrgTokenizer::lexCommandCall(PosStr& str) {
    __trace();
    spaceSkip(str);
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
    return true;
}

bool OrgTokenizer::lexCommandOptions(PosStr& str) {
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
                spaceSkip(str);
                break;
            }
            default: {
                auto raw = str.tok(otk::RawText, [](PosStr& str) {
                    while (str.notAt(charsets::HorizontalSpace)) {
                        str.next();
                    }
                });
                __push(raw);
            }
        }
    }
    return true;
}

bool OrgTokenizer::lexCommandInclude(PosStr& str) {
    __trace();
    spaceSkip(str);
    if (str.at(QChar('"'))) {
        lexDelimited(
            str,
            {QChar('"'), otk::QuoteOpen},
            {QChar('"'), otk::QuoteClose},
            otk::RawText);
    } else {
        auto text = str.tok(otk::RawText, [](PosStr& str) {
            while (str.notAt(charsets::HorizontalSpace)) {
                str.next();
            }
        });
        __push(text);
    }
    lexCommandKeyValue(str);
    return true;
}

bool OrgTokenizer::lexCommandKeyValue(PosStr& str) {
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
                spaceSkip(str);
                break;
            }
            default: {
                auto value = str.tok(otk::CommandValue, [](PosStr& str) {
                    auto hasColon = false;
                    while (!str.finished() && !hasColon) {
                        while (str.notAt(charsets::HorizontalSpace)) {
                            str.next();
                        }
                        if (!str.finished()) {
                            auto tmp = str;
                            tmp.space();
                            if (tmp.notAt(QChar(':'))) {
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
    return true;
}

bool OrgTokenizer::lexCommandArguments(
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
            pushResolved(caption);
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
            spaceSkip(str);
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
            spaceSkip(str);
            lexCommandKeyValue(str);
            break;
        }
        case ock::Header: {
            spaceSkip(str);
            lexCommandKeyValue(str);
            break;
        }
        case ock::Author:
        case ock::Creator:
        case ock::Language: {
            spaceSkip(str);
            auto lang = str.tok(otk::RawText, skipPastEOF);
            __push(lang);
            break;
        }
        case ock::Property: {
            lexCommandProperty(str);
            break;
        }
        case ock::Filetags: {
            while (str.at(':') && str.hasNext(1)) {
                auto sep = str.tok(otk::SubtreeTagSeparator, skipCount, 1);
                __push(sep);
                lexHashTag(str);
            }

            auto sep = str.tok(otk::SubtreeTagSeparator, skipCount, 1);
            __push(sep);

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
            spaceSkip(str);
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
        case ock::BeginQuote:
        case ock::LatexClassOptions: {
            auto text = str.tok(otk::RawText, skipPastEOF);
            __push(text);
            break;
        }

        default: {
            assert(false);
            auto text = str.tok(otk::RawText, skipPastEOF);
            __push(text);
        }
    }

    auto end = str.fakeTok(wrapEnd);
    __push(end);
    return true;
}

bool OrgTokenizer::lexCommandBlock(PosStr& str) {
    __trace();
    // Store position of the command start - content be dedented or
    // indented arbitrarily, so `#+begin_src` starting at column 2 might
    // have content that starts on the column 0.
    const auto column = str.getColumn();
    auto       prefix = str.tok(otk::CommandPrefix, skipCb("#+"));
    __push(prefix);
    const auto id = str.slice(skipZeroOrMore, OCommandChars);
    if (normalize(id.toStr()).startsWith("begin")) {
        lexCommandBlockDelimited(str, id, column);
    } else {
        auto line = Token(otk::LineCommand, id.view);
        __push(line);
        auto colon = str.tok(otk::Colon, skipCb((':')));
        __push(colon);
        spaceSkip(str);
        auto args = str.slice(skipToEOL);
        lexCommandArguments(args, classifyCommand(id.toStr()));
    }
    if (!str.finished()) {
        newlineSkip(str);
    }

    return true;
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
        if (0 < space) {
            for (const auto ch : ahead[slice(0, space - 1)].view) {
                if (ch != OSpace) {
                    return false;
                }
            }
        }

        return ahead[slice(space, 1_B)].at("CLOCK:");
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
    if (str.getColumn() != 0) {
        qCritical() << str << str.getColumn();
        qFatal(
            "Indentation can be skipped only starting from the 0th "
            "column");
    }

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
        oskipOne(str, ListStart);
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

bool OrgTokenizer::lexListBullet(
    PosStr&           str,
    int               indent,
    LexerStateSimple& state) {
    __trace();
    if (str.at(CharSet{QChar('-'), QChar('+')})
        || (0 < str.getIndent() && str.at(OBulletListStar))) {
        __trace("At bullet list start");
        auto tok = str.tok(otk::ListItemStart, skipCb(OBulletListStart));
        __push(tok);
        spaceSkip(str);
    } else {
        __trace("At numbered list start");
        auto start = str.tok(
            otk::ListStart,
            skipCb(charsets::Digits + charsets::AsciiLetters));

        __push(start);

        oskipOne(str, cr(CharSet{QChar(')'), QChar('.')}));
        spaceSkip(str);
    }

    if (str.at("\\[[Xx - ]\\]")) {
        auto tok = str.tok(otk::Checkbox, [this](PosStr& str) {
            oskipOne(str, QChar('['));
            oskipOne(
                str, CharSet{QChar('X'), QChar('x'), OSpace, QChar('-')});
            oskipOne(str, QChar(']'));
        });
        __push(tok);

        spaceSkip(str);
    }
    return true;
}

bool OrgTokenizer::lexListDescription(
    PosStr&           str,
    int               indent,
    LexerStateSimple& state) {
    __trace("Try parsing list header");
    Opt<PosStr> descriptionSlice;

    // Start temporary buffer and and string
    PosStr        tmp = str;
    Vec<OrgToken> buffer;
    setBuffer(&buffer);
    int skip = tmp.getSkip('\n');
    // Remember max position
    int maxPos = tmp.getPos() + skip;

    // Assume we know the description colon is present
    __push(tmp.fakeTok(otk::ListDescOpen));
    __push(tmp.fakeTok(otk::ParagraphStart));
    // Lex until the maximum position is reached
    while (tmp.getPos() < maxPos && tmp.notAt("::")) {
        // Char lexer will buffer content
        lexText(tmp);
    }

    // If we are indeed on the double colon separator, skip remaining parts
    if (tmp.at("::")) {
        __push(tmp.fakeTok(otk::ParagraphEnd));
        // Colon separator
        auto colon = tmp.tok(otk::DoubleColon, skipCb("::"));
        __push(colon);
        __push(tmp.fakeTok(otk::ListDescClose));
        // Move tokens from buffer
        for (const auto& tok : buffer) {
            __push(tok, true);
        }
        // Set updated string.
        str = tmp;
    }

    clearBuffer();

    return true;
}

void OrgTokenizer::lexListBody(
    PosStr&           str,
    int               column,
    LexerStateSimple& state) {
    __trace("List body");
    auto start = str.fakeTok(otk::StmtListOpen);
    __push(start);

    auto atEnd = false;
    // extend slice until new list start is not found - either via new
    // nested item or by indentation decrease.
    while (!str.finished() && !atEnd) {
        if (atLogClock(str)) {
            __print("Found log lock in list body, stopping");
            // Special handlig of `CLOCK:` entries in the subtree
            // logging drawer to make sure the content is skipped in
            // the right place.

            str.next();
            atEnd = true;
        } else if (atConstructStart(str) && (str.getColumn() <= column)) {
            __print("Found dedented construct");
            // If we are at the language construct start and it is
            // placed at the same level as prefix dash, treat it as
            // list end
            atEnd = true;
        } else if (atListAhead(str)) {
            __print("Found another list ahead");
            // check if we are at the start of the new list - if we
            // are, stop parsing completely and apply all withheld
            // lexer changes, otherwise don't touch `atEnd` in order to
            // continue parsing.
            atEnd = true;
        } else if (2 < getVerticalSpaceCount(str)) {
            __print("Two vertical spaces");
            // Two empty lines after list items should be treated
            // as list separator.
            atEnd = true;
        } else {
            auto tmp = str;
            tmp.space();
            __trace(
                "Process non-ending list content, column: current=$#, "
                "given=$#, skipped=$#"
                % to_string_vec(str.getColumn(), column, tmp.getColumn()));

            // Decide based on the indentation what to do next
            // indentation decreased, end of the list item
            if (tmp.getColumn() < column) {
                // Non-list content that matches indentation of the
                // current list item start.
                __print("Dedented non-list content");
                atEnd = true;
            } else {
                if (str.at("#+")) {
                    __print("Command block");
                    lexCommandBlock(str);
                } else {
                    __print("Text paragrapah");
                    lexParagraph(str);
                    // After paragraph has been lexed string will be
                    // positioned at the start of the next line
                }

                // Skip newline after the paragraph construct. Only one
                // line is optionally skipped because any larger number of
                // spaces is treated as list content break.
                if (str.at(ONewline)) {
                    newlineSkip(str);
                }
            }
        }
    }

    auto end = str.fakeTok(otk::StmtListClose);
    __push(end);
}


bool OrgTokenizer::lexListItem(
    PosStr&           str,
    const int&        column,
    LexerStateSimple& state) {
    __trace();
    lexListBullet(str, column, state);
    lexListDescription(str, column, state);
    lexListBody(str, column, state);
    __push(str.fakeTok(otk::ListItemEnd));
    return true;
}

bool OrgTokenizer::lexListItems(PosStr& str, LexerStateSimple& state) {
    __trace();
    assert(!str.at(ONewline));
    while (atListAhead(str) || atLogClock(str)) {
        assert(!str.at(ONewline));
        skipIndents(state, str);
        const auto column = str.getColumn();
        if (atListStart(str)) {
            lexListItem(str, column, state);
        } else {
            lexParagraph(str);
        }
    }

    return true;
}

bool OrgTokenizer::lexList(PosStr& str) {
    __trace();
    LexerStateSimple state{};
    __push(str.fakeTok(otk::ListStart));
    Vec<OrgToken> tokens;
    setBuffer(&tokens);
    lexListItems(str, state);
    clearBuffer();

    if (tokens[0].kind != otk::SameIndent) {
        __push(tokens[0], true);
    }

    for (const auto& tok : tokens[slice(1, 1_B)]) {
        __push(tok, true);
    }

    while (state.hasIndent()) {
        state.popIndent();
        __push(str.fakeTok(otk::Dedent));
    }
    __push(str.fakeTok(otk::ListEnd));
    return true;
}

int OrgTokenizer::getVerticalSpaceCount(CR<PosStr> str) {
    int  spaceCount = 0;
    auto tmp        = str;
    while (true) {
        tmp.space();
        if (tmp.at(charsets::Newline)) {
            tmp.next();
            ++spaceCount;
        } else {
            return spaceCount;
        }
    }
    return spaceCount;
}

bool OrgTokenizer::lexParagraph(PosStr& str) {
    __trace();
    // Pick out large standalone paragraph block until some construct is
    // encountered or empty line is reached.
    const auto column   = str.getColumn();
    auto       ended    = false;
    int        startPos = str.getPos();
    str.pushSlice();
    while (!str.finished() && !ended) {
        if (atConstructStart(str) //
            || atListAhead(str)   //
            || str.finished()     //
            || 1 < getVerticalSpaceCount(str)) {
            ended = true;
        } else {
            str.next();
        }
    }

    // Skip roll back extra spaces that were captured in the paragraph.
    // This is made in order to avoid cutting too much text in case of `-
    // Item\n__- Nested List` -- in this case nested list element will have
    // it's prefix indentation lexed by the 'Item' paragraph, which is not
    // desirable.
    while (str.at(ONewline, -1)) {
        str.back();
        while (str.at(OSpace, -1)) {
            str.back();
        }
    }

    // Add last trailing newline. The paragraph will be comprised of
    // `some_text\n`. After paragraph finished lexing positional string
    // will be placed at the start of the subsequent line
    if (str.at(ONewline)) {
        str.next();
    }

    if (startPos < str.getPos()) {
        // Depleted case with no paragraph content, for example we tried to
        // parse `\n\n\n` or some similar location. In this case backward
        // walk for trimming trailing spacing might reduce the position
        auto recTok = str.popTok(otk::Text);
        // Put it for the recursive processing, paragraph start/end
        // elements will be added there.
        pushResolved(recTok);
        // Paragraph processing itself does not need wrapping group and
        // always succeds.
        return true;
    } else {
        str.setPos(startPos);
        auto skip = str.tok(otk::SkipAny, skipCount, 1);
        __push(skip);
        return false;
    }
}

bool OrgTokenizer::lexTableState(
    PosStr&                         str,
    LexerState<OrgBlockLexerState>& state) {
    __trace();
    switch (str.get().unicode()) {
        case '#': {
            auto pos        = str.getPos();
            bool isTableCmd = true;
            str.next();
            if (str.at(QChar('+'))) {
                oskipOne(str, QChar('+'));
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
                    spaceSkip(str);
                    if (!str.finished()) {
                        if (at(back()).kind == otk::TableEnd) {
                            state.toFlag(OrgBlockLexerState::Complete);
                        } else {
                            __push(str.tok(
                                otk::CmdArguments, skipTo, ONewline));
                            if (!str.finished()) {
                                newlineSkip(str);
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
                    spaceSkip(str);
                    if (str.notAt(ONewline)) {
                        __push((str.tok(otk::Content, [](PosStr& str) {
                            str.skipBefore(CharSet{QChar('|'), ONewline});
                            if (str.at(OSpace)) {
                                while (str.at(OSpace)) {
                                    str.back();
                                }
                                if (str.notAt(OSpace)) {
                                    str.next();
                                }
                            } else {
                                str.next();
                            }
                        })));

                        spaceSkip(str);
                    }
                }

                auto close = str.fakeTok(otk::PipeClose);
                __push(close);
            } else {
                str.setPos(pos);
                auto open = str.tok(otk::PipeCellOpen, skipCb(('|')));
                __push(open);
                spaceSkip(str);
                auto content = str.tok(otk::Content, skipToEOL);
                __push(content);
                if (!str.finished()) {
                    newlineSkip(str);
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
                    while (str.notAt(CharSet{QChar('|'), QChar('#')})) {
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
    return true;
}

bool OrgTokenizer::lexTable(PosStr& str) {
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
    return true;
}

bool OrgTokenizer::lexStructure(PosStr& str) {
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
                } else if (atListStart(str)) {
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
                newlineSkip(str);
            } else if (atListStart(str)) {
                lexList(str);
            } else {
                lexParagraph(str);
            }
            break;
        }

        case '\n': {
            newlineSkip(str);
            break;
        }
        case ' ': {
            spaceSkip(str);
            if (atListAhead(str)) {
                qDebug() << str;
                auto err = Errors::UnexpectedConstruct(
                    str,
                    "encountered indented list during top-level "
                    "lexing. Column was $#, but top-level lists "
                    "should only start the 0th column. Either dedent "
                    "the list accordingly or reduce preceding "
                    "vertical spacing (if this is a dangling list)"
                        % to_string_vec(str.getColumn()));
                __report_and_throw(err);
            } else {
                lexStructure(str);
            }
            break;
        }

        default: {
            if (atListStart(str)) {
                // Numbered list
                lexList(str);
            } else if ((charsets::MaybeLetters
                        + CharSet{QChar('~'), QChar('[')})
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
    return true;
}

void OrgTokenizer::report(CR<Report> in) {
    if (reportHook) {
        reportHook(in);
    }

    if (traceUpdateHook) {
        traceUpdateHook(in, trace, true);
    }
    if (!trace) {
        if (traceUpdateHook) {
            traceUpdateHook(in, trace, false);
        }
        return;
    }


    using fg = TermColorFg8Bit;
    if (in.kind == ReportKind::Enter) {
        ++depth;
    }

    ColStream os = getStream();
    os << repeat("  ", depth);


    auto getLoc = [&]() -> QString {
        QString res;
        if (locationResolver && in.str != nullptr) {
            LineCol loc = locationResolver(*in.str);
            res         = "$#:$# " % to_string_vec(loc.line, loc.column);
        }
        return res;
    };

    auto printString = [&]() {
        if (in.str != nullptr) {
            os << " [";
            in.str->print(
                os,
                PosStr::PrintParams(
                    {.withEnd        = false,
                     .maxTokens      = 100,
                     .withSeparation = false}));
            os << "]";
        }
    };

    switch (in.kind) {
        case ReportKind::Print: {
            os << "  " << in.line << getLoc() << ":" << in.subname.value();
            printString();
            break;
        }

        case ReportKind::SetBuffer: {
            os << "  ! set buffer";
            break;
        }

        case ReportKind::Error: {
            os << "  ! error " << in.error.what();
            break;
        }

        case ReportKind::ClearBuffer: {
            os << "  ! clear buffer" << getLoc();
            break;
        }

        case ReportKind::PushResolved: {
            os << "  + push resolved" << getLoc();
            break;
        }

        case ReportKind::Push: {
            if (in.id.isNil()) {
                os << "  + buffer token " << getLoc() << in.tok;
            } else {
                os << "  + add token " << getLoc() << in.id.getIndex()
                   << " " << at(in.id);
            }
            os << " at " << fg::Cyan << in.line << os.end();
            break;
        }
        case ReportKind::Enter:
        case ReportKind::Leave: {
            os << (in.kind == ReportKind::Enter ? "> " : "< ") << fg::Green
               << getLoc() << in.name << os.end() << ":" << fg::Cyan
               << in.line << os.end();

            printString();
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

    if (traceUpdateHook) {
        traceUpdateHook(in, trace, false);
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
                __trace("Logbook element group");
                auto tmp = str;
                tmp.space();
                if (atLogClock(tmp)) {
                    spaceSkip(str);
                    auto clock = str.fakeTok(otk::ListClock);
                    __push(clock);
                    auto log = str.tok(otk::Text, skipToEOL);
                    pushResolved(log);
                    // text processing about should not include end of
                    // line.
                    if (!str.finished()) {
                        newlineSkip(str);
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

bool OrgTokenizer::lexGlobal(PosStr& str) {
    __trace();
    while (!str.finished()) {
        lexStructure(str);
    }
    return true;
}
