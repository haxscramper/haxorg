#include "OrgTokenizer.hpp"

#include <hstd/stdlib/algorithms.hpp>
#include <hstd/stdlib/Debug.hpp>

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>


using ock = OrgCommandKind;
using otk = OrgTokenKind;

using Err = OrgTokenizer::Errors;

struct OrgTokenizerImplBase
    : public Tokenizer<OrgTokenKind>
    , public OrgTokenizer {

  public:
    TokenizerError wrapError(CR<Error> err) {
        TokenizerError result{err};
        if (locationResolver) {
            PosStr str{result.getView(), result.getPos()};
            result.setLoc(locationResolver(str));
        }
        return result;
    }

    OrgToken error(CR<TokenizerError> err) {
        auto tmp = err;
        if (locationResolver) {
            PosStr str{err.getView(), err.getPos()};
            tmp.setLoc(locationResolver(str));
        }
        errors.push_back(err);
        return Token(OrgTokenKind::ErrorTerminator, errors.high());
    }


    /// Resolve positional string into line and column information
    OrgTokenizer::LocationResolverCb locationResolver;
    OrgTokenizer::ReportHookCb       reportHook;
    /// Update trace enable/disable state. Called before and after each
    /// report is processed. First argument is the report, second is the
    /// reference to the `trace` member and the last one provides
    /// information about call location (before report or after report).
    OrgTokenizer::TraceUpdateHookCb traceUpdateHook;

    void setReportHook(Func<void(CR<Report>)> locationResolver) override {
        reportHook = locationResolver;
    }

    void setTraceUpdateHook(
        Func<void(CR<Report>, bool&, bool)> locationResolver) override {
        traceUpdateHook = locationResolver;
    }

    void setLocationResolver(
        Func<LineCol(CR<PosStr>)> locationResolver) override {
        locationResolver = locationResolver;
    }

    Opt<LineCol> getLoc(CR<PosStr> str) override {
        if (locationResolver) {
            return locationResolver(str);
        } else {
            return std::nullopt;
        }
    }

    OrgTokenizerImplBase(OrgTokenGroup* out)
        : Tokenizer<OrgTokenKind>(out) {}


    QString debugPos(CR<PosStr> str) const {
        QString res;
        if (locationResolver) {
            auto loc = locationResolver(str);
            res      = "$#:$#" % to_string_vec(loc.line, loc.column);
        }

        return res;
    }

    void setBuffer(Vec<OrgToken>* buffer) {
        report(Report{.kind = ReportKind::SetBuffer});
        Base::setBuffer(buffer);
    }

    void clearBuffer() {
        report(Report{.kind = ReportKind::ClearBuffer});
        Base::clearBuffer();
    }

    void       push(CR<std::span<OrgToken>> tok) { Base::push(tok); }
    void       push(CR<Vec<OrgToken>> tok) { Base::push(tok); }
    OrgTokenId push(CR<OrgToken> tok) { return Base::push(tok); }

    int  depth = 0;
    void report(CR<Report> in) {
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
                res = "$#:$# " % to_string_vec(loc.line, loc.column);
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
                os << "  " << in.line << getLoc() << ":"
                   << in.subname.value();
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
                os << (in.kind == ReportKind::Enter ? "> " : "< ")
                   << fg::Green << getLoc() << in.name << os.end() << ":"
                   << fg::Cyan << in.line << os.end();

                if (in.subname.has_value()) {
                    os << " " << in.subname.value();
                }

                printString();

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


    void oskipOne(PosStr& str, CR<PosStr::CheckableSkip> skip) {
        if (str.atAny(skip)) {
            str.skipAny(skip);
        } else {
            throw wrapError(Err::UnexpectedChar(str, skip));
        }
    }

    PosStr::AdvanceCb skipCb(CR<PosStr::CheckableSkip> item) {
        return [item, this](PosStr& str) { oskipOne(str, item); };
    }


    int getVerticalSpaceCount(CR<PosStr> str) {
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
};


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


namespace {


PosStr spaced(PosStr tmp) {
    tmp.space();
    return tmp;
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


template <bool TraceState>
struct OrgTokenizerImpl : OrgTokenizerImplBase {
    OrgTokenizerImpl(OrgTokenGroup* out) : OrgTokenizerImplBase(out) {}

    /// Push complex token into recursive processing pipeline. Used for
    /// table content (which might contain more blocks of texts, some
    /// paragraph elements, more content etc), regular `Text` token
    /// (contained in a lot of places, first picked out from the
    /// 'surrounding' and then re-lexed again (the best example where this
    /// might be needed is `#+title:` followed by regular paragraph, but
    /// things like link descriptions might contain nested paragraphs as
    /// well))
    void pushResolved(CR<OrgToken> token);

    virtual Vec<OrgToken> lexDelimited(
        PosStr&                          str,
        const Pair<QChar, OrgTokenKind>& start,
        const Pair<QChar, OrgTokenKind>& finish,
        const OrgTokenKind&              middle) override;

    void endGroup(PosStr& str);
    void startGroup(PosStr& str);


    /// Check if the string is positioned at the start of a logbook
    /// `CLOCK:` entry.
    virtual bool atLogClock(CR<PosStr> str) override;

    /// Check if string is positioned at the start of toplevel language
    /// construct.
    virtual bool atConstructStart(CR<PosStr> str) override;
    virtual bool atSubtreeStart(CR<PosStr> str) override;

    using LexerStateSimple = LexerState<char>;

    virtual void skipIndents(LexerStateSimple& state, PosStr& str)
        override;


    /// Attempt to parse list start dash
    virtual bool atListStart(CR<PosStr> str) override;
    virtual bool atListAhead(CR<PosStr> str) override;

    /// Lex head starting from current position onwards. `indent` is the
    /// indentation of the original list prefix -- dash, number or letter.
    virtual bool lexListItem(
        PosStr&           str,
        const int&        indent,
        LexerStateSimple& state) override;

    virtual bool lexListBullet(
        PosStr&           str,
        int               indent,
        LexerStateSimple& state) override;
    virtual bool lexListDescription(
        PosStr&           str,
        int               indent,
        LexerStateSimple& state) override;
    virtual void lexListBody(
        PosStr&           str,
        int               indent,
        LexerStateSimple& state) override;


    virtual bool lexListItems(PosStr& str, LexerStateSimple& state)
        override;
    virtual bool lexTableState(
        PosStr&                         str,
        LexerState<OrgBlockLexerState>& state) override;
    virtual bool lexCommandContent(PosStr& str, const OrgCommandKind& kind)
        override;
    virtual bool lexCommandArguments(
        PosStr&               str,
        const OrgCommandKind& kind) override;
    virtual bool lexCommandBlockDelimited(
        PosStr& str,
        PosStr  id,
        int     column) override;

#define _def(Kind) virtual bool lex##Kind(PosStr& str) override;
    EACH_SIMPLE_TOKENIZER_METHOD(_def);
#undef _def

    virtual bool isFirstOnLine(CR<PosStr> str) override;

    virtual void spaceSkip(PosStr& str, bool require = false) override;
    virtual void newlineSkip(PosStr& str) override;
};


const auto NonText = CharSet{
    ONewline,
    OSpace,
    QChar(','),
    QChar('.'),
    QChar('\''),
    QChar('"'),
    QChar('/'),
} + charsets::PunctChars + charsets::AllSpace;


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


#define TRACE_STATE true
#include <parse/OrgTokenizer.cxx>
#define TRACE_STATE false
#include <parse/OrgTokenizer.cxx>

// -----------


} // namespace


SPtr<OrgTokenizer> OrgTokenizer::initImpl(
    OrgTokenGroup* out,
    bool           doTrace) {
    if (doTrace) {
        return std::make_shared<OrgTokenizerImpl<true>>(out);
    } else {
        return std::make_shared<OrgTokenizerImpl<false>>(out);
    }
}
