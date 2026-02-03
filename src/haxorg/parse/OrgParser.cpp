#include <haxorg/parse/OrgParser.hpp>
#pragma clang diagnostic ignored "-Wunused-result"
#pragma clang diagnostic ignored "-Wformat-security"
#include <haxorg/sem/perfetto_org.hpp>
#include <boost/preprocessor.hpp>
#include <hstd/stdlib/Formatter.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <haxorg/parse/OrgTypesFormatter.hpp>

#pragma clang diagnostic error "-Wunused-result"


using otk = OrgTokenKind;
using onk = OrgNodeKind;

using namespace org::parse;
using namespace hstd;

using TokSet = IntSet<OrgTokenKind>;

namespace {


org::sem::OrgDiagnostics::ParseError ParseErrorInit(
    std::string_view   name,
    std::string        code,
    std::string const& brief,
    std::string const& detail) {
    org::sem::OrgDiagnostics::ParseError result;
    result.errName = std::string{name};
    result.errCode = code;
    result.brief   = brief;
    result.detail  = detail;
    return result;
}

struct ErrorTable {
#define P_ERROR(__fieldname, __short, __long)                                              \
    static const inline org::sem::OrgDiagnostics::ParseError __fieldname = ParseErrorInit( \
        #__fieldname,                                                                      \
        ::org::fieldname_to_code(#__fieldname),                                            \
        __short,                                                                           \
        __long);

    P_ERROR(FallbackError, "Default fallback error", "");
    P_ERROR(UnexpectedToken, "Found unexpected token during parsing", "");
    P_ERROR(MissingClosingParen, "Expected closing `)`", "");
    P_ERROR(MissingClosingBracket, "Expected closing `]`", "");
    P_ERROR(
        MissingMacroClose,
        "Expected `}}}` after macro close",
        "Inline macro call can be either `{{{macro-name}}}` or "
        "`{{{macro-name(arg1, arg2)}}}`.");
    P_ERROR(
        UnexpectedTableElement,
        "Unexpected element at the top table level.",
        "Block-style table can only have pipe-style (leading `|`) or "
        "CMD-style rows (`#+row`).");
    P_ERROR(
        MissingPropertyContinuation,
        "Missing propery block continuation after the `:property:` start",
        ":properties: must be immediately followed by the property list "
        "starting from the next line");

#undef P_ERROR
};


const OrgTokSet Newline{
    otk::Newline,
    otk::LongNewline,
    otk::MediumNewline,
};

const OrgTokSet ParagraphTerminator{
    otk::MediumNewline,
    otk::LongNewline,
    otk::SubtreeStars,
    otk::ListBegin,
    otk::ListItemBegin,
    otk::CmdSrcBegin,
    otk::CmdSrcEnd,
    otk::CmdQuoteEnd,
    otk::CmdQuoteBegin,
    otk::StmtListEnd,
    otk::CmdPrefix,
    otk::StmtListEnd,
    otk::LeadingPipe,
    otk::ListItemEnd,
    otk::Indent,
    otk::Dedent,
    otk::SameIndent,
};

OrgTokSet ListStarts{
    otk::LeadingMinus,
    otk::LeadingNumber,
    otk::LeadingPlus,
    otk::TreeClock,
};

const OrgTokSet BlockTerminator{
    otk::SubtreeStars,
};
} // namespace

#define SUB_PARSE_2(__kind, __lex)                                        \
    BOOST_OUTCOME_TRYX(maybe_recursive_error_end(                         \
        parse##__kind(__lex), ErrorTable::FallbackError, __lex))

#define SUB_PARSE_3(__kind, __lex, __on_failure)                          \
    BOOST_OUTCOME_TRYX(maybe_recursive_error_end(                         \
        parse##__kind(__lex), ErrorTable::__on_failure, __lex))

#define SUB_PARSE_IMPL(__count) BOOST_PP_CAT(SUB_PARSE_, __count)

#define SUB_PARSE(...)                                                    \
    SUB_PARSE_IMPL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__))(__VA_ARGS__)


#define TRY_SKIP_2(__lex, __expected)                                     \
    BOOST_OUTCOME_TRY(skip(__lex, __expected, ErrorTable::UnexpectedToken))

#define TRY_SKIP_3(__lex, __expected, __message)                          \
    BOOST_OUTCOME_TRY(skip(__lex, __expected, ErrorTable::__message))

#define TRY_SKIP_IMPL(__count) BOOST_PP_CAT(TRY_SKIP_, __count)

#define TRY_SKIP(...)                                                     \
    TRY_SKIP_IMPL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__))(__VA_ARGS__)


#define TRY_POPX(__lex, __expression)                                     \
    BOOST_OUTCOME_TRYX(pop(__lex, __expression))

void OrgParser::space(OrgLexer& lex, int line, char const* function) {
    while (lex.at(OrgTokSet{otk::Whitespace, otk::LeadingSpace})) {
        std::ignore = skip(
            lex, std::nullopt, std::nullopt, line, function);
    }
}

void OrgParser::newline(OrgLexer& lex, int line, char const* function) {
    while (lex.at(Newline)) {
        std::ignore = skip(
            lex, std::nullopt, std::nullopt, line, function);
    }
}

SubLexer<OrgTokenKind, OrgFill> subToEol(
    OrgLexer& lex,
    OrgTokSet Terminator = ParagraphTerminator) {
    SubLexer sub{lex};
    while (lex.can_search(Terminator)) { sub.add(lex.pop()); }
    if (!sub.tokens.empty()) { sub.start(); }
    return sub;
}

OrgParser::ParseResult OrgParser::parseCSVArguments(OrgLexer& lex) {
    __perf_trace("parsing", "parseCSVArguments");
    auto __trace = trace(lex);
    token(
        onk::Word,
        TRY_POPX(
            lex,
            (OrgTokSet{
                otk::Word,
                otk::SrcContent,
            })));

    if (lex.at(otk::ParBegin)) {
        TRY_SKIP(lex, otk::ParBegin);
        while (lex.at(otk::RawText)) {
            token(onk::RawText, TRY_POPX(lex, otk::RawText));
            if (lex.at(otk::Comma)) { skip(lex); }
        }
        TRY_SKIP(lex, otk::ParEnd);
    }

    return ParseOk{};
}

OrgParser::ParseResult OrgParser::subParseImpl(
    OrgParser::ParseResult (OrgParser::*func)(OrgLexer&),
    OrgLexer&   lex,
    int         line,
    char const* function) {
    return (this->*func)(lex);
}


OrgParser::ParseResult OrgParser::parseMacro(OrgLexer& lex) {
    __perf_trace("parsing", "parseMacro");
    auto __trace = trace(lex);

    int closingOffset = 0;
    while (lex.hasNext(closingOffset)
           && !lex.at(otk::CurlyEnd, closingOffset)) {
        ++closingOffset;
    }

    bool hasClose = lex.at(otk::CurlyEnd, closingOffset)
                 && lex.at(otk::CurlyEnd, closingOffset + 1)
                 && lex.at(otk::CurlyEnd, closingOffset + 2);

    auto macroGuard = start(onk::Macro);
    TRY_SKIP(lex, otk::CurlyBegin);
    TRY_SKIP(lex, otk::CurlyBegin);
    TRY_SKIP(lex, otk::CurlyBegin);
    token(onk::Word, TRY_POPX(lex, OrgTokSet{otk::Word}));

    SUB_PARSE(CallArguments, lex);

    for (int i = 0; i <= 2; ++i) {
        if (lex.at(otk::CurlyEnd)) {
            std::ignore = skip(lex, otk::CurlyEnd);
        } else {
            LOGIC_ASSERTION_CHECK_FMT(!hasClose, "");
            return error_end(ErrorTable::MissingMacroClose, lex);
        }
    }

    LOGIC_ASSERTION_CHECK_FMT(hasClose, "");
    return macroGuard->end();
}

OrgParser::ParseResult OrgParser::parseCallArguments(OrgLexer& lex) {
    __perf_trace("parsing", "parseCallArguments");
    auto __trace   = trace(lex);
    auto stmtGuard = start(onk::InlineStmtList);
    if (lex.at(otk::ParBegin)) {
        TRY_SKIP(lex, otk::ParBegin);
        while (lex.can_search(otk::ParEnd)) {
            SUB_PARSE(AttrValue, lex);
            space(lex);
            if (lex.at(otk::Comma)) {
                std::ignore = skip(lex, otk::Comma);
                space(lex);
            }
        }


        TRY_SKIP(lex, otk::ParEnd, MissingClosingParen);
    }

    return stmtGuard->end();
}


OrgParser::ParseResult OrgParser::parseAttrValue(OrgLexer& lex) {
    __perf_trace("parsing", "parseAttrColonKeyValue");
    auto __trace   = trace(lex);
    auto attrGuard = start(onk::AttrValue);

    if (lex.at(
            IntSet<OrgTokenKind>{
                otk::CmdColonIdent,
                otk::CmdRawArg,
                otk::ParBegin,
            })) {
        print("Attribute value was lexed with explicit argument tokens");
        if (lex.at(otk::CmdColonIdent)) {
            // `:ident`
            token(onk::Word, TRY_POPX(lex, otk::CmdColonIdent));
            space(lex);
        } else {
            empty();
        }

        IntSet<OrgTokenKind> eqTokens{
            otk::Equals,
            otk::VerbatimBegin,
            otk::VerbatimEnd,
            otk::VerbatimUnknown};

        if (lex.at(otk::CmdRawArg) && lex.at(eqTokens, +1)) {
            // `key=`
            token(onk::RawText, TRY_POPX(lex, otk::CmdRawArg));
            TRY_SKIP(lex, eqTokens);
            space(lex);
        } else {
            empty();
        }

        if (lex.at(otk::ParBegin)) {
            SUB_PARSE(AttrLisp, lex);
        } else if (lex.at(otk::CmdRawArg)) {
            token(onk::RawText, TRY_POPX(lex, otk::CmdRawArg));
        } else {
            empty();
        }

        if (lex.at(otk::BraceBegin)) {
            auto stmtGuard = start(onk::InlineStmtList);
            TRY_SKIP(lex, otk::BraceBegin);
            while (lex.at(otk::CmdRawArg) || lex.at(otk::Comma)) {
                if (lex.at(otk::Comma)) {
                    empty();
                    std::ignore = skip(lex, otk::Comma);
                    space(lex);
                } else {
                    token(onk::RawText, TRY_POPX(lex, otk::CmdRawArg));
                    space(lex);
                    if (lex.at(otk::Comma)) {
                        std::ignore = skip(lex, otk::Comma);
                        space(lex);
                    }
                }
            }

            TRY_SKIP(lex, otk::BraceEnd, MissingClosingBracket);
            stmtGuard->end();
        } else {
            empty();
        }
    } else {
        // `{{{macro(with some parameter that looks like actual text)}}}}`
        // is lexed as a part of the text, so tokens in the argument list
        // are not 'correct'.
        print("Argument value was lexed using random tokens");
        empty();

        if (lex.at(OrgTokSet{otk::Word, otk::RawText})
            && lex.at(
                OrgTokSet{
                    otk::Equals,
                    otk::VerbatimBegin,
                    otk::VerbatimEnd,
                    otk::VerbatimUnknown,
                },
                +1)) {
            token(onk::RawText, pop(lex));
            skip(lex);
        } else {
            empty();
        }

        auto stmtGuard = start(onk::InlineStmtList);
        while (lex.can_search(OrgTokSet{otk::ParEnd, otk::Comma})) {
            token(onk::RawText, pop(lex));
        }
        stmtGuard->end();
        empty();
    }


    return attrGuard->end();
}

OrgParser::ParseResult OrgParser::parseAttrLisp(OrgLexer& lex) {
    __perf_trace("parsing", "parseAttrLisp");
    auto __trace   = trace(lex);
    auto lispGuard = start(onk::AttrLisp);
    if (lex.at(otk::ParBegin)) {
        auto stmtGuard = start(onk::InlineStmtList);
        TRY_SKIP(lex, otk::ParBegin);
        space(lex);
        while (lex.can_search(otk::ParEnd)) {
            SUB_PARSE(AttrLisp, lex);
            space(lex);
        }
        TRY_SKIP(lex, otk::ParEnd, MissingClosingParen);
        stmtGuard->end();
    } else {
        token(onk::RawText, pop(lex));
    }

    return lispGuard->end();
}


OrgParser::ParseResult OrgParser::parsePlaceholder(OrgLexer& lex) {
    __perf_trace("parsing", "parsePlaceholder");
    auto __trace = trace(lex);
    if (lex.at(otk::Placeholder)) {
        return ParseOk{token(onk::Placeholder, pop(lex))};
    } else {
        return ParseOk{token(onk::Punctuation, pop(lex))};
    }
}


OrgParser::ParseResult OrgParser::parseLatex(OrgLexer& lex) {
    __perf_trace("parsing", "parseLatex");
    auto __trace = trace(lex);
    TRY_SKIP(lex, otk::LatexParBegin);
    auto res = token(onk::InlineMath, TRY_POPX(lex, otk::LatexInlineRaw));
    TRY_SKIP(lex, otk::LatexParEnd);
    return ParseOk{res};
}


void OrgParser::textFold(OrgLexer& lex) {
    // Text fold method will consume all tokens in the lexer, folding into
    // series of tree nodes.
    auto __trace = trace(lex);

    Func<ParseResult()> aux;
    auto                _begin = [&](onk Kind) {
        print(fmt("begin {}", Kind));
        int        startDepth = treeDepth();
        OrgTokenId startToken = pop(lex);
        start_no_guard(Kind);
        std::ignore = aux();
        print(
            fmt("Started on {} exited on {} tok {}",
                startDepth,
                treeDepth(),
                startToken));
        // If the function returned earlier because the input has ended
        // before the markup opening was terminated it means there is no
        // correct markup in the text and it must be converted to the
        // punctuation.
        //
        // `*bold` -> `aux(*)` -- after pushing `bold` as a workd and
        // returning, the `aux(*)` will convert `Bold` into
        // `Punctuation(*)`
        if (startDepth < treeDepth()) {
            print(fmt(
                "Folding unclosed with token {}", lex.in->at(startToken)));
            auto unclosed = group->pendingTrees.back();
            group->nodes.at(unclosed).kind = onk::Punctuation;
            group->nodes.at(unclosed).value = startToken;
            group->pendingTrees.pop_back();
        }
    };

    auto _end = [&](onk Kind) {
        print(fmt("end {}", Kind));
        if (pending().kind == Kind) {
            end_impl();
            skip(lex);
        } else {
            token(onk::Punctuation, pop(lex));
        }
    };

    auto _unknown = [&](onk Kind) {
        print(fmt("unknown {}", Kind));
        if (pending().kind == Kind) {
            _end(Kind);
        } else {
            _begin(Kind);
        }
    };

    auto _single = [&]() -> ParseResult {
        switch (lex.kind()) {
            case otk::BoldBegin: _begin(onk::Bold); break;
            case otk::BoldEnd: _end(onk::Bold); break;
            case otk::BoldUnknown: _unknown(onk::Bold); break;
            case otk::ItalicBegin: _begin(onk::Italic); break;
            case otk::ItalicEnd: _end(onk::Italic); break;
            case otk::ItalicUnknown: _unknown(onk::Italic); break;
            case otk::UnderlineBegin: _begin(onk::Underline); break;
            case otk::UnderlineEnd: _end(onk::Underline); break;
            case otk::UnderlineUnknown: _unknown(onk::Underline); break;
            case otk::StrikeBegin: _begin(onk::Strike); break;
            case otk::StrikeEnd: _end(onk::Strike); break;
            case otk::StrikeUnknown: _unknown(onk::Strike); break;

            case otk::Whitespace: token(onk::Space, pop(lex)); break;
            case otk::CurlyBegin: {
                if (lex.at(
                        Vec{otk::CurlyBegin,
                            otk::CurlyBegin,
                            otk::CurlyBegin})) {
                    SUB_PARSE(Macro, lex);
                } else {
                    token(onk::Punctuation, pop(lex));
                }
                break;
            }

            case otk::AngleEnd: {
                token(onk::Punctuation, pop(lex));
                break;
            }

            case otk::Escaped: token(onk::Escaped, pop(lex)); break;
            case otk::RawText: token(onk::RawText, pop(lex)); break;
            case otk::Newline: token(onk::Newline, pop(lex)); break;
            case otk::Word: token(onk::Word, pop(lex)); break;
            case otk::BigIdent: token(onk::BigIdent, pop(lex)); break;
            case otk::Punctuation:
                token(onk::Punctuation, pop(lex));
                break;

            case otk::Colon: token(onk::Colon, pop(lex)); break;
            case otk::MiscUnicode:
            case otk::Time:
            case otk::Date:
            case otk::SubtreePriority:
            case otk::Number: {
                token(onk::Word, pop(lex));
                break;
            }

            case otk::CriticAddBegin:
            case otk::CriticDeleteBegin:
            case otk::CriticReplaceBegin:
            case otk::CriticCommentBegin:
            case otk::CriticHighlightBegin: {
                SUB_PARSE(CriticMarkup, lex);
                break;
            }

            case otk::Placeholder: {
                SUB_PARSE(Placeholder, lex);
                break;
            }

            case otk::ActiveDynamicTimeContent:
            case otk::InactiveDynamicTimeContent: {
                SUB_PARSE(TimeRange, lex);
                break;
            }

            case otk::AngleBegin: {
                if (lex.at(otk::Date, +1)) {
                    SUB_PARSE(TimeRange, lex);
                } else {
                    SUB_PARSE(Placeholder, lex);
                }
                break;
            }

            case otk::InlineExportBackend: {
                SUB_PARSE(InlineExport, lex);
                break;
            }

            case otk::TextSrcBegin: {
                SUB_PARSE(SrcInline, lex);
                break;
            }
            case otk::HashIdent: {
                SUB_PARSE(HashTag, lex);
                break;
            }
            case otk::LinkProtocolHttp:
            case otk::LinkProtocol:
            case otk::LinkBegin: {
                SUB_PARSE(Link, lex);
                break;
            }
            case otk::FootnoteInlineBegin:
            case otk::FootnoteLinked: {
                SUB_PARSE(Footnote, lex);
                break;
            }
            case otk::Symbol: {
                SUB_PARSE(Symbol, lex);
                break;
            }

            case otk::BraceBegin: {
                if (lex.at(otk::Date, +1)) {
                    SUB_PARSE(TimeRange, lex);
                } else {
                    token(onk::Punctuation, pop(lex));
                }
                break;
            }

            case otk::At: {
                token(onk::AtMention, TRY_POPX(lex, otk::At));
                break;
            }

            case otk::VerbatimBegin:
            case otk::MonospaceBegin: {
                SUB_PARSE(VerbatimOrMonospace, lex);
                break;
            }

            case otk::DoubleAngleBegin:
            case otk::TripleAngleBegin: {
                SUB_PARSE(AngleTarget, lex);
                break;
            }

            case otk::Comment:
            case otk::LeadingSpace: {
                skip(lex);
                break;
            }

            case otk::LinkEnd:
            case otk::LinkDescriptionBegin:
            case otk::LinkTargetEnd: {
                if (lex.tok()->text.empty()) {
                    skip(lex);
                } else {
                    token(onk::Punctuation, pop(lex));
                }
                break;
            }

            default: {
                token(onk::Punctuation, pop(lex));
                break;
            }
        }

        return ParseOk{};
    };


    aux = [&]() -> ParseResult {
        auto __trace = trace(lex, std::nullopt, __LINE__, "aux");

        while (!lex.finished()) {
            // ignoring all failures in the text parsing: while parsing
            // paragraph there is no need to search for the next
            // synchronization points. Take the next token and try to parse
            // it. All paragraphs are processed with sub-lexers, so it is
            // safe to eagerly process everything.
            std::ignore = _single();
        }

        return ParseOk{};
    };

    std::ignore = aux();
}


Slice<OrgId> OrgParser::parseText(OrgLexer& lex) {
    auto        __trace   = trace(lex);
    OrgId       first     = back();
    std::string forMsg    = getLocMsg(lex);
    int         treeStart = treeDepth();
    textFold(lex);
    int treeEnd = treeDepth();
    print(
        hstd::fmt(
            "Trace levels after text fold start:{} end:{}",
            treeStart,
            treeEnd));

    if (treeStart != treeEnd) {
        auto msg = fmt(
            "Text fold created unbalanced tree - starting with depth {} "
            "ended up on depth {} on position {} (starting from {})",
            treeStart,
            treeEnd,
            getLocMsg(lex),
            forMsg);

        throw fatalError(lex, msg);
    }

    OrgId last = back();
    return slice(first, last);
}


OrgParser::ParseResult OrgParser::parseLink(OrgLexer& lex) {
    __perf_trace("parsing", "parseLink");
    auto __trace = trace(lex);
    if (lex.at(otk::LinkProtocolHttp)) {
        auto linkGuard = start(onk::Link);
        token(onk::Word, TRY_POPX(lex, otk::LinkProtocolHttp));
        token(onk::RawText, TRY_POPX(lex, otk::LinkTarget));
        empty();
        return linkGuard->end();
    } else {
        auto linkGuard = start(onk::Link);
        TRY_SKIP(lex, otk::LinkBegin);
        // LOG(INFO) << fmt1(lex.tok()->line);
        switch (lex.kind()) {
            case otk::LinkProtocolHttp: {
                token(onk::Word, TRY_POPX(lex, otk::LinkProtocolHttp));
                token(onk::RawText, TRY_POPX(lex, otk::LinkTarget));
                break;
            }
            case otk::LinkProtocolId: {
                token(onk::Word, TRY_POPX(lex, otk::LinkProtocolId));
                token(onk::RawText, TRY_POPX(lex, otk::LinkTarget));
                break;
            }
            case otk::LinkProtocolTitle: {
                empty();
                token(onk::RawText, TRY_POPX(lex, otk::LinkProtocolTitle));
                break;
            }
            case otk::LinkProtocolCustomId: {
                token(onk::Word, TRY_POPX(lex, otk::LinkProtocolCustomId));
                token(onk::RawText, TRY_POPX(lex, otk::LinkTarget));
                break;
            }
            case otk::LinkProtocolAttachment: {
                token(
                    onk::Word, TRY_POPX(lex, otk::LinkProtocolAttachment));
                token(onk::RawText, TRY_POPX(lex, otk::LinkTarget));
                break;
            }
            case otk::LinkProtocolFile: {
                token(onk::Word, TRY_POPX(lex, otk::LinkProtocolFile));
                token(onk::RawText, TRY_POPX(lex, otk::LinkTarget));
                break;
            }
            case otk::LinkTargetFile: {
                empty();
                token(onk::RawText, TRY_POPX(lex, otk::LinkTargetFile));
                break;
            }
            case otk::LinkProtocolInternal: {
                empty();
                token(
                    onk::RawText,
                    TRY_POPX(lex, otk::LinkProtocolInternal));
                break;
            }
            default:
                token(onk::Word, TRY_POPX(lex, otk::LinkProtocol));
                SubLexer sub{lex};
                while (!lex.at(OrgTokSet{otk::LinkSplit, otk::LinkEnd})) {
                    sub.add(pop(lex));
                }
                if (sub.empty()) {
                    empty();
                } else {
                    sub.start();
                    SUB_PARSE(Paragraph, sub);
                }
        }

        if (lex.at(otk::LinkSplit)) {
            TRY_SKIP(lex, otk::LinkSplit);
            SubLexer sub{lex};
            while (lex.can_search(otk::LinkEnd)) { sub.add(pop(lex)); }
            if (sub.empty()) {
                empty();
            } else {
                sub.start();
                SUB_PARSE(Paragraph, sub);
            }
        } else {
            empty();
        }


        TRY_SKIP(lex, otk::LinkEnd);
        return linkGuard->end();
    }
}


OrgParser::ParseResult OrgParser::parseInlineMath(OrgLexer& lex) {
    __perf_trace("parsing", "parseInlineMath");
    auto __trace = trace(lex);

    auto guard = start(onk::InlineMath);


    return guard->end();
}


OrgParser::ParseResult OrgParser::parseSymbol(OrgLexer& lex) {
    __perf_trace("parsing", "parseSymbol");
    auto __trace     = trace(lex);
    auto symbolGuard = start(onk::Symbol);
    token(onk::Word, TRY_POPX(lex, otk::Symbol));

    {
        auto stmtGuard = start(onk::InlineStmtList);
        while (lex.at(otk::BraceBegin)) {
            TRY_SKIP(lex, otk::BraceBegin);
            token(onk::RawText, pop(lex));
            TRY_SKIP(lex, otk::BraceEnd);
        }
        stmtGuard->end();
    }

    {
        auto stmtGuard = start(onk::InlineStmtList);
        while (lex.at(otk::CurlyBegin)) {
            if (lex.at(Vec{otk::CurlyBegin, otk::CurlyEnd})) {
                empty();
                TRY_SKIP(lex, otk::CurlyBegin);
                TRY_SKIP(lex, otk::CurlyEnd);
            } else {
                auto sub = SubLexer(
                    lex.in,
                    lex.getInside({otk::CurlyBegin}, {otk::CurlyEnd}));
                auto paragraphGuard = start(onk::Paragraph);
                parseText(sub);
                paragraphGuard->end();
            }
        }
        stmtGuard->end();
    }

    return symbolGuard->end();
}


OrgParser::ParseResult OrgParser::parseHashTag(OrgLexer& lex) {
    auto __trace = trace(lex);

    struct HashState {
        OrgId result;
        bool  doubleSkip;
    };

    using HashResult = hstd::Result<HashState, ParseFail>;
    Func<HashResult(OrgLexer & lex)> aux;


    aux = [&](OrgLexer& lex) -> HashResult {
        auto __trace   = trace(lex, "aux", __LINE__, "aux");
        auto hashGuard = start(onk::HashTag);
        space(lex);
        if (lex.at(otk::At)) {
            // Org-mode suppors tags like '@work' etc.
            token(onk::RawText, TRY_POPX(lex, otk::At));
        } else {
            token(
                onk::RawText,
                TRY_POPX(
                    lex,
                    (OrgTokSet{
                        otk::HashIdent, otk::Word, otk::BigIdent})));
        }

        bool doubleSkip = false;

        if (lex.at(otk::DoubleHash)) {
            TRY_SKIP(lex, otk::DoubleHash);
            if (lex.at(
                    OrgTokSet{otk::HashIdent, otk::Word, otk::BigIdent})) {
                auto sub = aux(lex);
                if (sub) {
                    if (sub.assume_value().doubleSkip) {
                        print("double skip");
                        return HashState{
                            .result = hashGuard->end().result.value()};
                    }
                } else {
                    return sub.assume_error();
                }

            } else {
                TRY_SKIP(lex, otk::BraceBegin);
                while (
                    !lex.finished()
                    && !lex.at(OrgTokSet{otk::BraceEnd, otk::LinkEnd})) {
                    auto result = aux(lex);
                    if (result) {
                        if (result.assume_value().doubleSkip) {
                            print("double skip");
                            return HashState{
                                .result = hashGuard->end().result.value()};
                        }
                        if (lex.at(otk::Comma)) { skip(lex); }
                        space(lex);
                    } else {
                        return result.assume_error();
                    }
                }

                if (lex.at(otk::LinkEnd)) {
                    doubleSkip = true;
                    TRY_SKIP(lex, otk::LinkEnd);
                } else {
                    TRY_SKIP(lex, otk::BraceEnd);
                }
            }
        }

        return HashState{
            .result     = hashGuard->end().result.value(),
            .doubleSkip = doubleSkip,
        };
    };

    auto result = BOOST_OUTCOME_TRYX(aux(lex));
    return ParseOk{result.result};
}


OrgParser::ParseResult OrgParser::parseTimeStamp(OrgLexer& lex) {
    auto __trace   = trace(lex);
    auto start_tok = lex.tok();
    BOOST_OUTCOME_TRY(expect(
        lex,
        OrgTokSet{
            otk::BraceBegin,
            otk::AngleBegin,
            otk::InactiveDynamicTimeContent,
            otk::ActiveDynamicTimeContent,
        }));

    bool active = lex.at(
        OrgTokSet{
            otk::AngleBegin,
            otk::ActiveDynamicTimeContent,
        });

    ParseResult result = ParseOk{};

    if (lex.at(
            OrgTokSet{
                otk::InactiveDynamicTimeContent,
                otk::ActiveDynamicTimeContent})) {
        std::unique_ptr<NodeGuard>
            timeGuard = active ? start(onk::DynamicActiveTime)
                               : start(onk::DynamicInactiveTime);
        if (active) {
            TRY_SKIP(lex, otk::ActiveDynamicTimeContent);
        } else {
            TRY_SKIP(lex, otk::InactiveDynamicTimeContent);
        }

        std::function<ParseResult()> aux;
        aux = [&]() -> ParseResult {
            if (lex.at(otk::ParBegin)) {
                auto stmtGuard = start(onk::InlineStmtList);
                TRY_SKIP(lex, otk::ParBegin);
                space(lex);
                while (lex.can_search(otk::ParEnd)) {
                    SUB_PARSE(AttrLisp, lex);
                    space(lex);
                }
                TRY_SKIP(lex, otk::ParEnd);
                return stmtGuard->end();
            } else {
                return ParseOk{token(onk::RawText, pop(lex))};
            }
        };


        std::ignore = aux();

        result = timeGuard->end();
    } else {
        std::unique_ptr<NodeGuard>
            timeGuard = active ? start(onk::StaticActiveTime)
                               : start(onk::StaticInactiveTime);
        if (active) {
            TRY_SKIP(lex, otk::AngleBegin);
        } else {
            TRY_SKIP(lex, otk::BraceBegin);
        }

        // Date part is usually used, but I think supporting *time* stamps
        // also makes sense
        if (lex.at(otk::Date)) {
            token(onk::RawText, TRY_POPX(lex, otk::Date));
            space(lex);
        } else {
            empty();
        }

        // Day can sometimes be added to the timestamp
        if (lex.at(otk::Word)) {
            skip(lex);
            space(lex);
        }

        if (lex.at(otk::Time)) {
            token(onk::RawText, TRY_POPX(lex, otk::Time));
            space(lex);
        } else {
            empty();
        }


        // timezone
        if (lex.at(otk::StrikeBegin) && lex.at(otk::Number, +1)) {
            skip(lex);
            token(onk::RawText, TRY_POPX(lex, otk::Number));
            space(lex);
        } else {
            empty();
        }


        if (lex.at(otk::TimeRepeaterSpec)) {
            auto stmtGuard = start(onk::InlineStmtList);
            while (lex.at(otk::TimeRepeaterSpec)) {
                auto stmtGuard = start(onk::InlineStmtList);
                token(onk::RawText, TRY_POPX(lex, otk::TimeRepeaterSpec));
                while (lex.at(otk::TimeRepeaterDuration)) {
                    token(onk::RawText, pop(lex));
                }
                stmtGuard->end();
                space(lex);
            }
        } else {
            empty();
        }

        if (lex.at(otk::TimeWarnPeriod)) {
            token(onk::RawText, TRY_POPX(lex, otk::TimeWarnPeriod));
        } else {
            empty();
        }
    }

    TRY_SKIP(lex, active ? otk::AngleEnd : otk::BraceEnd);
    return result;
}


OrgParser::ParseResult OrgParser::parseTimeRange(OrgLexer& lex) {
    auto            __trace = trace(lex);
    const OrgTokSet times{
        otk::BraceBegin,
        otk::BraceEnd,
        otk::AngleBegin,
        otk::AngleEnd,
        otk::InactiveDynamicTimeContent,
        otk::ActiveDynamicTimeContent,
        otk::Date,
        otk::Word,
        otk::Time,
        otk::Number,
        otk::StrikeBegin,
        otk::Whitespace,
        otk::TimeRepeaterSpec,
        otk::TimeWarnPeriod,
        otk::TimeRepeaterDuration,
    };

    Lexer tmp{lex.in};
    tmp.pos          = lex.pos;
    bool isTimeRange = false;
    while (!tmp.finished() && tmp.at(times)) {
        if (tmp.at(otk::AngleEnd) && tmp.at(otk::DoubleDash, +1)
            && tmp.at(
                OrgTokSet{otk::AngleBegin, otk::ActiveDynamicTimeContent},
                +2)) {
            isTimeRange = true;
            break;
        } else if (
            tmp.at(otk::BraceEnd) && tmp.at(otk::DoubleDash, +1)
            && tmp.at(
                OrgTokSet{
                    otk::BraceBegin, otk::InactiveDynamicTimeContent},
                +2)) {
            isTimeRange = true;
            break;
        } else {
            tmp.next();
        }
    }

    if (isTimeRange) {
        message("correct time range found");
        auto rangeGuard = start(onk::TimeRange);
        SUB_PARSE(TimeStamp, lex);
        TRY_SKIP(lex, otk::DoubleDash);
        SUB_PARSE(TimeStamp, lex);
        if (lex.ahead({otk::Whitespace}, {otk::TimeArrow})) {
            space(lex);
            TRY_SKIP(lex, otk::TimeArrow);
            space(lex);
            token(onk::SimpleTime, TRY_POPX(lex, otk::Time));
        } else {
            empty();
        }

        return rangeGuard->end();
    } else {
        return SUB_PARSE(TimeStamp, lex);
    }
}


OrgParser::ParseResult OrgParser::parseFootnote(OrgLexer& lex) {
    __perf_trace("parsing", "parseFootnote");
    auto __trace = trace(lex);
    if (lex.at(otk::FootnoteLinked)) {
        auto footnoteGuard = start(onk::Footnote);
        empty();
        token(onk::RawText, pop(lex));
        return footnoteGuard->end();
    } else {
        auto inlineGuard = start(onk::InlineFootnote);
        TRY_SKIP(lex, otk::FootnoteInlineBegin);
        SubLexer sub{lex};
        while (!lex.finished() && !lex.at(otk::BraceEnd)) {
            sub.add(pop(lex));
        }
        sub.start();
        SUB_PARSE(Paragraph, sub);
        TRY_SKIP(lex, otk::BraceEnd, MissingClosingBracket);
        return inlineGuard->end();
    }
}


OrgParser::ParseResult OrgParser::parseSrcInline(OrgLexer& lex) {
    __perf_trace("parsing", "parseSrcInline");
    auto __trace   = trace(lex);
    auto codeGuard = start(onk::SrcInlineCode);
    {
        token(onk::Word, TRY_POPX(lex, otk::TextSrcBegin)); // lang

        { // header args
            empty();
        }
        auto lineGuard = start(onk::CodeLine); // body
        {
            int balance = 1;
            TRY_SKIP(lex, otk::CurlyBegin);
            while (!lex.finished() && 0 < balance) {
                if (lex.at(otk::CurlyEnd)) {
                    if (balance == 1) {
                        TRY_SKIP(lex, otk::CurlyEnd);
                    } else {
                        token(onk::CodeText, pop(lex));
                    }
                    --balance;
                } else {
                    token(onk::CodeText, pop(lex));
                }
            }
        }
        lineGuard->end();
    }
    empty(); // TODO Parse result call
    return codeGuard->end();
}

OrgParser::ParseResult OrgParser::parseVerbatimOrMonospace(OrgLexer& lex) {
    __perf_trace("parsing", "parseVerbatimOrMonospace");
    auto __trace = trace(lex);
    bool m       = lex.kind() == otk::MonospaceBegin;

    auto postBeginLex = lex.getPos();
    auto startGuard   = start(m ? onk::Monospace : onk::Verbatim);
    auto begin_token  = pop(
        lex, m ? otk::MonospaceBegin : otk::VerbatimBegin);

    int  newlineCount = 0;
    bool foundEnd     = false;

    while (!lex.finished() && !foundEnd) {
        switch (lex.kind()) {
            case otk::VerbatimEnd:
            case otk::MonospaceEnd: {
                if (lex.at(m ? otk::MonospaceEnd : otk::VerbatimEnd)) {
                    foundEnd = true;
                } else {
                    token(onk::RawText, pop(lex));
                }

                break;
            }
            case otk::Newline: {
                if (2 < newlineCount) {
                    foundEnd = true;
                } else {
                    ++newlineCount;
                    token(onk::RawText, pop(lex));
                }
                break;
            }

            case otk::Placeholder: {
                SUB_PARSE(Placeholder, lex);
                break;
            }
            default: {
                token(onk::RawText, pop(lex));
            }
        }
    }

    if (lex.at(m ? otk::MonospaceEnd : otk::VerbatimEnd)) {
        skip(lex);
        return startGuard->end();
    } else {
        if (TraceState) {
            print(
                fmt("Reset monospace parse position. Removing tail at {}, "
                    "moving lexer from {} to {}",
                    startGuard->startId,
                    lex.getPos(),
                    postBeginLex));
        }

        auto result = startGuard->end();
        group->removeTail(startGuard->startId);
        lex.setPos(postBeginLex);
        token(onk::Punctuation, pop(lex));
        return result;
    }
}

OrgParser::ParseResult OrgParser::parseAngleTarget(OrgLexer& lex) {
    bool            radio = lex.kind() == otk::TripleAngleBegin;
    const OrgTokSet AngleTargetContent{
        otk::RawText,
        otk::Whitespace,
        otk::Word,
        otk::BigIdent,
    };

    auto end   = radio ? otk::TripleAngleEnd : otk::DoubleAngleEnd;
    auto begin = radio ? otk::TripleAngleBegin : otk::DoubleAngleBegin;

    if (lex.ahead(OrgTokSet{otk::Whitespace, otk::Word, begin}, end)) {
        TRY_SKIP(lex, begin);
        auto radioGuard = start(onk::RadioTarget);
        while (lex.can_search(end)) {
            switch (lex.kind()) {
                case otk::RawText: token(onk::RawText, pop(lex)); break;
                case otk::Whitespace: token(onk::Space, pop(lex)); break;
                case otk::Word: token(onk::Word, pop(lex)); break;
                case otk::BigIdent: token(onk::BigIdent, pop(lex)); break;
                default:
            }
        }
        TRY_SKIP(lex, end);
        return radioGuard->end();
    } else {
        return ParseOk{token(onk::Punctuation, pop(lex))};
    }
}

OrgParser::ParseResult OrgParser::parseTablePipeRow(OrgLexer& lex) {
    auto rowGuard = start(onk::TableRow);
    empty();                               // no row parameters
    empty();                               // no row-level text
    auto listGuard = start(onk::StmtList); // List of rows

    while (lex.at(OrgTokSet{otk::LeadingPipe, otk::Pipe})) {
        auto cellGuard = start(onk::TableCell);
        empty();                                   // No cell parameters
        auto     listGuard = start(onk::StmtList); // Cell content
        SubLexer sub{lex};
        skip(lex);
        OrgTokSet CellEnd{otk::Pipe, otk::TrailingPipe};
        OrgTokSet CellStart{otk::Pipe, otk::LeadingPipe};
        while (lex.can_search(CellEnd)) {
            if (lex.at(otk::Whitespace)
                && (lex.at(CellEnd, +1) || lex.at(CellStart, -1))) {
                lex.next();
            } else {
                sub.add(pop(lex));
            }
        }
        if (sub.empty()) {
            auto guard = start(onk::Paragraph);
            guard->end();
        } else {
            sub.start();
            SUB_PARSE(Paragraph, sub);
        }

        listGuard->end();
        cellGuard->end();
    }
    BOOST_OUTCOME_TRY(skip(lex, otk::TrailingPipe));
    if (lex.at(Newline)) { skip(lex); }

    listGuard->end();
    return rowGuard->end();
}

OrgParser::ParseResult OrgParser::parseTableBlockRow(OrgLexer& lex) {
    TRY_SKIP(lex, otk::CmdPrefix);
    TRY_SKIP(lex, otk::CmdRow);
    auto rowGuard = start(onk::TableRow);
    SUB_PARSE(CommandArguments, lex);
    empty();
    newline(lex);

    auto stmtGuard = start(onk::StmtList);
    if (lex.at(otk::LeadingPipe)) {
        while (lex.at(otk::LeadingPipe)) {
            TRY_SKIP(lex, otk::LeadingPipe);
            space(lex);
            auto cellGuard = start(onk::TableCell);
            empty();
            auto stmtGuard = start(onk::StmtList);
            auto sub       = subToEol(lex);
            if (sub.empty()) {
                empty();
            } else {
                SUB_PARSE(Paragraph, sub);
            }
            stmtGuard->end();
            cellGuard->end();
            newline(lex);
        }
    } else {
        while (lex.at(Vec{otk::CmdPrefix, otk::CmdCell})) {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, otk::CmdCell);
            auto cellGuard = start(onk::TableCell);
            SUB_PARSE(CommandArguments, lex);
            auto stmtGuard = start(onk::StmtList);
            while (!(
                lex.at(otk::CmdPrefix)
                && lex.at(
                    OrgTokSet{otk::CmdCell, otk::CmdRow, otk::CmdTableEnd},
                    +1))) {
                SUB_PARSE(StmtListItem, lex);
            }
            stmtGuard->end();
            cellGuard->end();
        }
    }

    stmtGuard->end();
    return rowGuard->end();
}


OrgParser::ParseResult OrgParser::parseTable(OrgLexer& lex) {
    __perf_trace("parsing", "parseTable");
    auto __trace = trace(lex);


    if (lex.at(OrgTokSet{otk::LeadingPipe, otk::TableSeparator})) {
        auto tableGuard = start(onk::Table);
        empty(); // No table command arguments for a pipe table
        while (lex.at(OrgTokSet{otk::LeadingPipe, otk::TableSeparator})) {
            switch (lex.kind()) {
                case otk::LeadingPipe: {
                    SUB_PARSE(TablePipeRow, lex);
                    break;
                }
                case otk::TableSeparator: {
                    lex.next();
                    newline(lex);
                    break;
                }
                default: {
                }
            }
        }
        return tableGuard->end();
    } else {
        auto     tableGuard = start(onk::Table);
        Vec<otk> TableEnd{otk::CmdPrefix, otk::CmdTableEnd};

        TRY_SKIP(lex, otk::CmdPrefix);
        TRY_SKIP(lex, otk::CmdTableBegin);
        SUB_PARSE(CommandArguments, lex);
        newline(lex);

        while (lex.can_search(TableEnd)) {
            switch (lex.kind()) {
                case otk::LeadingPipe: {
                    SUB_PARSE(TablePipeRow, lex);
                    break;
                }
                case otk::CmdPrefix: {
                    SUB_PARSE(TableBlockRow, lex);
                    break;
                }
                default: {
                    return error_end(
                        ErrorTable::UnexpectedTableElement, lex);
                }
            }
        }


        TRY_SKIP(lex, otk::CmdPrefix);
        TRY_SKIP(lex, otk::CmdTableEnd);
        return tableGuard->end();
    }
}


OrgParser::ParseResult OrgParser::parseParagraph(OrgLexer& lex) {
    auto paragraphGuard = start(onk::Paragraph);
    parseText(lex);
    return paragraphGuard->end();
}

OrgParser::ParseResult OrgParser::parseInlineExport(OrgLexer& lex) {
    auto exportGuard = start(onk::InlineExport);
    token(onk::RawText, TRY_POPX(lex, otk::InlineExportBackend));
    token(onk::RawText, TRY_POPX(lex, otk::InlineExportContent));
    return exportGuard->end();
}

OrgParser::ParseResult OrgParser::parseCriticMarkup(OrgLexer& lex) {
    __perf_trace("parsing", "parseCriticMarkup");
    auto __trace = trace(lex);
    otk  e;
    switch (lex.kind()) {
        case otk::CriticDeleteBegin: e = otk::CriticDeleteEnd; break;
        case otk::CriticAddBegin: e = otk::CriticAddEnd; break;
        case otk::CriticCommentBegin: e = otk::CriticCommentEnd; break;
        case otk::CriticReplaceBegin: e = otk::CriticReplaceEnd; break;
        case otk::CriticHighlightBegin: e = otk::CriticHighlightEnd; break;
        default: {
        }
    }

    auto criticGuard = start(onk::CriticMarkStructure);
    token(onk::RawText, pop(lex));
    if (e == otk::CriticReplaceEnd) {
        SubLexer sub{lex};
        while (lex.can_search(otk::CriticReplaceMiddle)) {
            sub.add(lex.pop());
        }

        if (sub.empty()) {
            empty();
        } else {
            sub.start();
            SUB_PARSE(Paragraph, sub);
        }
        TRY_SKIP(lex, otk::CriticReplaceMiddle);
    } else {
        empty();
    }

    SubLexer sub{lex};
    while (lex.can_search(e)) { sub.add(lex.pop()); }

    sub.start();
    SUB_PARSE(Paragraph, sub);
    TRY_SKIP(lex, e);
    return criticGuard->end();
}

OrgParser::ParseResult OrgParser::parseCommandArguments(OrgLexer& lex) {
    __perf_trace("parsing", "parseCommandArguments");
    auto __trace = trace(lex);
    space(lex);
    auto stmtGuard = start(onk::InlineStmtList);
    while (lex.at(OrgTokSet{otk::CmdRawArg, otk::CmdColonIdent})) {
        SUB_PARSE(AttrValue, lex);
        space(lex);
    }

    return stmtGuard->end();
}


OrgParser::ParseResult OrgParser::parseSrcArguments(OrgLexer& lex) {
    __perf_trace("parsing", "parseSrcArguments");
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(Newline)) {
        empty();
        empty();
        return ParseOk{};
    } else {
        auto attrGuard = start(onk::Attrs);
        auto stmtGuard = start(onk::InlineStmtList);
        {
            while (lex.at(otk::CmdFlag)) {
                token(onk::CmdFlag, TRY_POPX(lex, otk::CmdFlag));
            }
        }
        stmtGuard->end();
        SUB_PARSE(CommandArguments, lex);
        return attrGuard->end();
    }
}


OrgParser::ParseResult OrgParser::parseTextWrapCommand(OrgLexer& lex) {
    __perf_trace("parsing", "parseTextWrapCommand");
    TRY_SKIP(lex, otk::CmdPrefix);
    auto __trace = trace(lex);

    bool isDynamic = lex.kind() == otk::CmdDynamicBlockBegin;


    std::unique_ptr<NodeGuard> guard =
        [&]() -> std::unique_ptr<NodeGuard> {
        switch (lex.kind()) {
            case otk::CmdVerseBegin: return start(onk::BlockVerse);
            case otk::CmdCenterBegin: return start(onk::BlockCenter);
            case otk::CmdQuoteBegin: return start(onk::BlockQuote);
            case otk::CmdCommentBegin: return start(onk::BlockComment);
            case otk::CmdDynamicBlockBegin:
                return start(onk::BlockDynamicFallback);
            default: throw fatalError(lex, "unhandled token");
        }
    }();

    OrgTokenKind endTok = [&]() {
        switch (lex.kind()) {
            case otk::CmdVerseBegin: return otk::CmdVerseEnd;
            case otk::CmdCenterBegin: return otk::CmdCenterEnd;
            case otk::CmdQuoteBegin: return otk::CmdQuoteEnd;
            case otk::CmdCommentBegin: return otk::CmdCommentEnd;
            case otk::CmdDynamicBlockBegin:
                token(onk::Word, lex.get());
                return otk::CmdDynamicBlockEnd;
            default: throw fatalError(lex, "unhandled token");
        }
    }();

    std::string tmp = lex.val().text;
    skip(lex);

    if (lex.at(Newline)) {
        empty();
    } else {
        space(lex);
        SUB_PARSE(CommandArguments, lex);
        space(lex);
    }

    TRY_SKIP(lex, Newline);

    if (isDynamic) {
        hstd::replace_all(tmp, "begin", "end");
        Str endName = normalize(tmp);
        print(fmt("Dynamic block, name {}", endName));
        while (lex.can_search(Vec<otk>{otk::CmdPrefix, endTok})
               && lex.hasNext(2)
               && normalize(lex.val(1).text) != endName) {
            SUB_PARSE(StmtListItem, lex);
            if (lex.at(BlockTerminator)) {
                print(fmt("block terminator {}", lex));
                break;
            }
        }
    } else {
        while (lex.can_search(Vec<otk>{otk::CmdPrefix, endTok})) {
            SUB_PARSE(StmtListItem, lex);
            if (lex.at(BlockTerminator)) {
                print(fmt("block terminator {}", lex));
                break;
            }
        }
    }

    TRY_SKIP(lex, otk::CmdPrefix);
    TRY_SKIP(lex, endTok);
    return guard->end();
}


OrgParser::ParseResult OrgParser::parseBlockExport(OrgLexer& lex) {
    __perf_trace("parsing", "parseExample");
    auto __trace     = trace(lex);
    auto exportGuard = start(onk::BlockExport);

    TRY_SKIP(lex, otk::CmdPrefix);
    TRY_SKIP(lex, otk::CmdExportBegin);

    // command arguments
    space(lex);
    token(onk::Word, TRY_POPX(lex, otk::CmdRawArg));
    space(lex);
    SUB_PARSE(CommandArguments, lex);
    newline(lex);

    // command content
    auto stmtGuard = start(onk::StmtList);
    while (lex.at(OrgTokSet{otk::CmdExportLine, otk::Newline})) {
        token(onk::RawText, pop(lex));
    }
    stmtGuard->end();

    TRY_SKIP(lex, otk::CmdPrefix);
    TRY_SKIP(lex, otk::CmdExportEnd);

    return exportGuard->end();
}


OrgParser::ParseResult OrgParser::parseColonExample(OrgLexer& lex) {
    __perf_trace("parsing", "parseColonExample");

    auto __trace = trace(lex);


    auto exampleGuard = start(onk::ColonExample);
    while (lex.at(OrgTokSet{otk::ColonExampleLine, otk::Colon})) {
        if (lex.at(otk::ColonExampleLine)) {
            token(onk::RawText, pop(lex));
        } else {
            empty();
            TRY_SKIP(lex, otk::Colon);
        }

        if (lex.at(otk::Newline)) { skip(lex); }
    }

    return exampleGuard->end();
}

OrgParser::ParseResult OrgParser::parseExample(OrgLexer& lex) {
    __perf_trace("parsing", "parseExample");
    auto __trace      = trace(lex);
    auto exampleGuard = start(onk::BlockExample);

    TRY_SKIP(lex, otk::CmdPrefix);
    TRY_SKIP(lex, otk::CmdExampleBegin);

    { // command arguments
        SUB_PARSE(CommandArguments, lex);
        newline(lex);
    }

    { // command content
        while (lex.at(OrgTokSet{otk::CmdExampleLine, otk::Newline})) {
            if (lex.at(Vec{otk::Newline, otk::CmdPrefix})) {
                skip(lex);
            } else {
                token(onk::RawText, pop(lex));
            }
        }
    }

    TRY_SKIP(lex, otk::CmdPrefix);
    TRY_SKIP(lex, otk::CmdExampleEnd);

    return exampleGuard->end();
}


OrgParser::ParseResult OrgParser::parseSrc(OrgLexer& lex) {
    __perf_trace("parsing", "parseSrc");
    auto __trace    = trace(lex);
    auto blockGuard = start(onk::BlockCode);
    TRY_SKIP(lex, otk::CmdPrefix);
    TRY_SKIP(lex, otk::CmdSrcBegin);
    // header_args_lang
    {
        space(lex);
        if (lex.at(otk::CmdRawArg)) {
            if (lex.val().text.empty()) {
                empty();
            } else {
                token(onk::Word, TRY_POPX(lex, otk::CmdRawArg));
            }
        } else {
            empty();
        }

        space(lex);

        SUB_PARSE(SrcArguments, lex);
    };
    // body
    {

        auto stmtListGuard = start(onk::StmtList);
        TRY_SKIP(lex, otk::CmdContentBegin);
        while (lex.can_search(Vec{otk::CmdPrefix, otk::CmdSrcEnd})) {
            auto codeLineGuard = start(onk::CodeLine);
            while (lex.can_search(
                OrgTokSet{otk::CmdContentEnd, otk::Newline})) {
                switch (lex.kind()) {
                    case otk::SrcContent: {
                        token(
                            onk::CodeText, TRY_POPX(lex, otk::SrcContent));
                        break;
                    }
                    case otk::ParBegin: {
                        TRY_SKIP(lex, otk::ParBegin);
                        TRY_SKIP(lex, otk::Word);
                        TRY_SKIP(lex, otk::Colon);
                        auto calloutGuard = start(onk::CodeCallout);
                        token(onk::Word, TRY_POPX(lex, otk::Word));
                        calloutGuard->end();
                        TRY_SKIP(lex, otk::ParEnd);
                        break;
                    }
                    case otk::DoubleAngleBegin: {
                        bool hasClose = false;
                        for (int offset = 0; lex.hasNext(offset);
                             ++offset) {
                            if (lex.at(otk::DoubleAngleEnd, offset)) {
                                hasClose = true;
                                break;
                            } else if (lex.at(otk::Newline, offset)) {
                                break;
                            }
                        }
                        if (hasClose) {
                            TRY_SKIP(lex, otk::DoubleAngleBegin);
                            auto tangleGuard = start(onk::CodeTangle);
                            SUB_PARSE(CSVArguments, lex);
                            tangleGuard->end();
                            TRY_SKIP(lex, otk::DoubleAngleEnd);
                        } else {
                            token(
                                onk::CodeText,
                                TRY_POPX(lex, otk::DoubleAngleBegin));
                        }
                        break;
                    }
                    case otk::DoubleAngleEnd: {
                        token(
                            onk::CodeText,
                            TRY_POPX(lex, otk::DoubleAngleEnd));
                        break;
                    }
                    default: {
                        throw fatalError(
                            lex,
                            fmt("Unhandled code parse token {}",
                                lex.tok()));
                    }
                }
            }
            if (lex.at(otk::Newline)) { skip(lex); }
            codeLineGuard->end(); // finish code line
        }

        stmtListGuard->end(); // finish statement
    };

    TRY_SKIP(lex, otk::CmdPrefix);
    TRY_SKIP(lex, otk::CmdSrcEnd);


    // eval_result
    if (lex.ahead(
            Newline + OrgTokSet{otk::Whitespace},
            Vec<OrgTokenKind>{
                otk::CmdPrefix,
                otk::CmdResults,
            })) {
        while (!lex.at(otk::CmdPrefix)) {
            space(lex);
            newline(lex);
        }
        TRY_SKIP(lex, otk::CmdPrefix);
        TRY_SKIP(lex, otk::CmdResults);
        auto resultGuard = start(onk::CmdResults);
        space(lex);
        SUB_PARSE(CommandArguments, lex);
        newline(lex);
        if (!lex.at(otk::SubtreeStars)) {
            SUB_PARSE(StmtListItem, lex);
        } else {
            empty();
        }
        resultGuard->end();
    } else {
        empty();
    }

    return blockGuard->end();
}


OrgParser::ParseResult OrgParser::parseListItem(OrgLexer& lex) {
    __perf_trace("parsing", "parseListItem");
    auto __trace       = trace(lex);
    auto listItemGuard = start(onk::ListItem);
    // prefix, 0
    { token(onk::RawText, TRY_POPX(lex, ListStarts)); }
    space(lex);
    // counter, 1
    {
        empty(); // TODO parse counter
    }
    // checkbox 2
    {
        if (lex.at(otk::Checkbox)) {
            token(onk::Checkbox, TRY_POPX(lex, otk::Checkbox));
            space(lex);
        } else {
            empty();
        }
    }
    // tag, 3
    {
        // Search ahead for the description list tag
        Lexer<OrgTokenKind, OrgFill> tmp{lex.in};
        tmp.pos                  = lex.pos;
        auto const colon_pattern = Vec<otk>{
            otk::Whitespace,
            otk::DoubleColon,
            otk::Whitespace,
        };

        while (tmp.can_search(colon_pattern)) {
            if (tmp.at(Newline)) { break; }
            tmp.next();
        }

        if (tmp.finished()) {
            print("Sub-lexer reached end without header");
        } else {
            print(fmt(
                "Searched for double colon to {} tmp-pos {} lex-pos {}",
                tmp.tok(),
                tmp.pos,
                lex.pos));
        }

        if (tmp.at(colon_pattern)) {
            SubLexer sub{lex};

            while (lex.can_search(colon_pattern)) { sub.add(lex.pop()); }

            if (sub.empty()) {
                empty();
            } else {
                sub.start();
                SUB_PARSE(Paragraph, sub);
                lex.skip(otk::Whitespace);
                lex.skip(otk::DoubleColon);
                space(lex);
            }
        } else {
            empty();
        }
    }
    // body, 5
    auto stmtListGuard = start(onk::StmtList);
    {
        while (lex.can_search(
            OrgTokSet{otk::Dedent, otk::SameIndent, otk::ListItemEnd})) {
            SUB_PARSE(StmtListItem, lex);
        }
    }

    if (lex.at(otk::ListItemEnd)) { skip(lex); }

    stmtListGuard->end();
    return listItemGuard->end();
}


OrgParser::ParseResult OrgParser::parseList(OrgLexer& lex) {
    __perf_trace("parsing", "parseList");
    auto __trace = trace(lex);
    auto check   = start(onk::List);

    print(fmt("{}", lex.tok()));

    while (lex.at(ListStarts)
           || (lex.at(otk::LeadingSpace) && lex.at(ListStarts, +1))) {
        SUB_PARSE(ListItem, lex);
        if (lex.at(otk::SameIndent)) { skip(lex); }
    }

    return check->end();
}


OrgParser::ParseResult OrgParser::parseSubtreeLogbook(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtreeLogbook");
    auto __trace     = trace(lex);
    auto drawerGuard = start(onk::DrawerLogbook);
    TRY_SKIP(lex, otk::ColonLogbook);
    newline(lex);

    space(lex);

    TRY_SKIP(lex, otk::Indent);
    SUB_PARSE(List, lex);
    if (lex.at(otk::StmtListEnd)) {
        TRY_SKIP(lex, otk::StmtListEnd);
        TRY_SKIP(lex, otk::ListItemEnd);
    }
    TRY_SKIP(lex, otk::Dedent);

    space(lex);
    TRY_SKIP(lex, otk::ColonEnd);
    return drawerGuard->end();
}


OrgParser::ParseResult OrgParser::parseSubtreeProperties(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtreeProperties");
    auto __trace = trace(lex);
    TRY_SKIP(lex, otk::ColonProperties);
    TRY_SKIP(lex, otk::Newline, MissingPropertyContinuation);
    auto propertyListGuard = start(onk::DrawerPropertyList);
    while (lex.can_search(otk::ColonEnd)) {
        trace(lex, "Parse single subtree property");
        auto head = lex.kind();
        if (!TokSet{
                otk::ColonLiteralProperty,
                otk::ColonArgumentsProperty,
                otk::ColonPropertyText}
                 .contains(head)) {
            return error_end(ErrorTable::MissingPropertyContinuation, lex);
        }

        auto propertyGuard = start(onk::DrawerProperty);
        token(onk::RawText, TRY_POPX(lex, head));
        switch (head) {
            case otk::ColonLiteralProperty: {
                token(onk::RawText, TRY_POPX(lex, otk::RawText));
                break;
            }

            case otk::ColonArgumentsProperty: {
                SUB_PARSE(CommandArguments, lex);
                break;
            }

            case otk::ColonPropertyText: {
                space(lex);
                SubLexer sub{lex};
                while (lex.can_search(Newline)) { sub.add(lex.pop()); }
                sub.start();
                SUB_PARSE(Paragraph, sub);
                break;
            }
            default: {
            }
        }
        TRY_SKIP(lex, otk::Newline);
        propertyGuard->end();
    }

    TRY_SKIP(lex, otk::ColonEnd);
    return propertyListGuard->end();
}


OrgParser::ParseResult OrgParser::parseSubtreeDrawer(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtreeDrawer");
    auto __trace     = trace(lex);
    auto drawerGuard = start(onk::Drawer);

    while (lex.at(OrgTokSet{otk::ColonProperties, otk::ColonLogbook})) {
        switch (lex.tok().kind) {
            case otk::ColonProperties: {
                BOOST_OUTCOME_TRY(parseSubtreeProperties(lex));
                break;
            }
            case otk::ColonLogbook: {
                BOOST_OUTCOME_TRY(parseSubtreeLogbook(lex));
                break;
            }
            default:
        }

        newline(lex);
        space(lex);
    }

    return drawerGuard->end();
}

void tokenFormat(ColStream& os, OrgToken const& t) { os << t->text; }

OrgParser::ParseResult OrgParser::parseSubtreeCompletion(OrgLexer& lex) {
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(otk::SubtreeCompletion)) {
        return ParseOk{token(onk::SubtreeCompletion, pop(lex))};
    } else {
        return ParseOk{empty()};
    }
}


OrgParser::ParseResult OrgParser::parseSubtreeTodo(OrgLexer& lex) {
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(
            Vec{otk::BigIdent, otk::Whitespace, otk::SubtreePriority})) {
        return ParseOk{token(onk::BigIdent, pop(lex))};
    } else {
        return ParseOk{empty()};
    }
}


OrgParser::ParseResult OrgParser::parseSubtreeUrgency(OrgLexer& lex) {
    auto __trace = trace(lex);
    space(lex);
    if (lex.at(otk::SubtreePriority)) {
        return ParseOk{token(onk::SubtreeUrgency, pop(lex))};
    } else {
        return ParseOk{empty()};
    }
}


OrgParser::ParseResult OrgParser::parseSubtreeTitle(OrgLexer& lex) {
    auto __trace = trace(lex);
    space(lex);
    SubLexer sub{lex};

    auto is_at_subtree_tags = [](OrgLexer& lex) {
        const IntSet<OrgTokenKind> tree_tags{
            otk::Colon,
            otk::Word,
            otk::DoubleHash,
            otk::At,
            otk::BigIdent,
        };

        if (!lex.at(otk::Colon)) { return false; }

        auto ahead = lex.whole_fixed().range_current()
                   | rv::take_while([&](OrgToken const& t) -> bool {
                         return tree_tags.contains(t.kind);
                     })
                   | rs::to<std::vector>;

        auto tag_end = lex.begin() + ahead.size();
        return tag_end == lex.whole_fixed().end()
            || Newline.contains(tag_end->kind);
    };

    while (lex.can_search(Newline)     //
           && !is_at_subtree_tags(lex) //
           && !lex.at(otk::SubtreeCompletion)) {
        sub.add(pop(lex));
    }

    if (sub.empty()) {
        empty();
    } else {
        sub.start();
        SUB_PARSE(Paragraph, sub);
    }

    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseSubtreeTags(OrgLexer& lex) {
    auto __trace = trace(lex);
    if (lex.at(otk::Colon)) {
        auto stmtGuard = start(onk::InlineStmtList);
        while (
            lex.at(otk::Colon)
            && lex.at(OrgTokSet{otk::Word, otk::At, otk::BigIdent}, +1)) {
            TRY_SKIP(lex, otk::Colon);
            SUB_PARSE(HashTag, lex);
        }
        TRY_SKIP(lex, OrgTokSet{otk::Colon} + Newline);
        return stmtGuard->end();
    } else {
        return ParseOk{empty()};
    }
}


OrgParser::ParseResult OrgParser::parseSubtreeTimes(OrgLexer& lex) {
    auto __trace = trace(lex);
    if ((lex.at(otk::LeadingSpace) && lex.at(otk::TreeTime, +1))
        || lex.at(otk::TreeTime)) {
        space(lex);
        auto subtreeTimesGuard = start(onk::StmtList);
        while (lex.at(otk::TreeTime)
               || (lex.at(otk::Newline) && lex.at(otk::TreeTime, +1))) {
            newline(lex);
            auto stmtGuard = start(onk::InlineStmtList);
            token(onk::Word, pop(lex));
            space(lex);
            SUB_PARSE(TimeRange, lex);
            space(lex);
            stmtGuard->end();
        }

        // Optional standalone timestamp or time range right after the
        // subtree. The check is for token sequence
        // <newline> <space>? <angle/brace> <date>
        auto [it, lex_end] = lex.whole_fixed().range_current();
        if (it != lex_end && it->kind == otk::Newline) {
            ++it;
            if (it == lex_end) { goto not_a_timestamp; }
            if (it->kind == otk::LeadingSpace) { ++it; }
            if (it == lex_end) { goto not_a_timestamp; }
            if (it->kind != otk::AngleBegin
                && it->kind != otk::BraceBegin) {
                goto not_a_timestamp;
            }

            ++it;

            if (it == lex_end) { goto not_a_timestamp; }
            if (it->kind == otk::Date) {
                lex.skip(otk::Newline);
                space(lex);
                auto stmtGuard = start(onk::InlineStmtList);
                empty();
                SUB_PARSE(TimeRange, lex);
                space(lex);
                stmtGuard->end();
            }

        not_a_timestamp:
        }

        return subtreeTimesGuard->end();

    } else {
        return ParseOk{empty()};
    }
}


OrgParser::ParseResult OrgParser::parseSubtree(OrgLexer& lex) {
    __perf_trace("parsing", "parseSubtree");
    auto __trace      = trace(lex);
    auto subtreeGuard = start(onk::Subtree);
    // prefix

    std::optional<ParseFail> parseFail;

    // subtree processing gets special treatment because the structure of
    // the subtree is very important to the final document, so having
    // exactly 8 subnodes, with the last one being StmtList is required to
    // properly form the document down the line.
    auto parseElement =
        [&](OrgParser::ParseResult (OrgParser::*func)(OrgLexer&)) {
            if (parseFail) {
                empty();
            } else {
                auto result = (this->*func)(lex);
                if (result.has_error()) {
                    parseFail = result.assume_error();
                }
            }
        };

    token(onk::RawText, TRY_POPX(lex, otk::SubtreeStars)); // 0
    parseElement(&OrgParser::parseSubtreeTodo);            // 1
    parseElement(&OrgParser::parseSubtreeUrgency);         // 2
    space(lex);                                            //
    parseElement(&OrgParser::parseSubtreeTitle);           // 3
    parseElement(&OrgParser::parseSubtreeCompletion);      // 4
    space(lex);
    parseElement(&OrgParser::parseSubtreeTags); // 5

    if (lex.at(otk::Newline)) { newline(lex); }
    parseElement(&OrgParser::parseSubtreeTimes); // 6

    if (lex.at(otk::Newline)) { newline(lex); }

    if (lex.at(OrgTokSet{otk::ColonProperties, otk::ColonLogbook})) { // 7
        parseElement(&OrgParser::parseSubtreeDrawer);
    } else {
        empty();
    }

    newline(lex);

    auto stmtListGuard = start(onk::StmtList); // 8
    stmtListGuard->end();

    if (parseFail) {
        return parseFail.value();
    } else {
        return subtreeGuard->end();
    }
}


OrgParser::ParseResult OrgParser::parseOrgFile(OrgLexer& lex) {
    __perf_trace("parsing", "parseOrgFile");
    auto __trace   = trace(lex);
    auto fileGuard = start(onk::File);
    logic_todo_impl();
    return fileGuard->end();
}


OrgParser::ParseResult OrgParser::parseLineCommand(OrgLexer& lex) {
    __perf_trace("parsing", "parseLineCommand");
    auto __trace  = trace(lex);
    auto cmd_kind = lex.kind(+1);

    OrgTokSet raw_arg_cmd_value{
        otk::CmdRawArg,
        otk::BraceBegin,
        otk::BraceEnd,
        otk::Comma,
        otk::Equals,
        otk::RawText,
    };

    auto get_cmd_arguments = [&]() -> ParseResult {
        auto stmtGuard = start(onk::InlineStmtList);
        while (lex.at(raw_arg_cmd_value)) {
            token(onk::RawText, TRY_POPX(lex, raw_arg_cmd_value));
        }
        return stmtGuard->end();
    };

    std::unique_ptr<NodeGuard> cmdGuard;
    switch (cmd_kind) {
        case otk::CmdBindRaw:
        case otk::CmdCategoryRaw:
        case otk::CmdSetupfileRaw:
        case otk::CmdPrioritiesRaw:
        case otk::CmdSeqTodoRaw:
        case otk::CmdTagsRaw:
        case otk::CmdMacroRaw:
        case otk::CmdLinkRaw:
        case otk::CmdLatexHeaderExtraRaw:
        case otk::CmdExcludeTagsRaw:
        case otk::CmdSelectTagsRaw:
        case otk::CmdDrawersRaw:
        case otk::CmdConstants:
        case otk::CmdCustomRaw: {
            cmdGuard = start(onk::CmdCustomRawCommand);
            TRY_SKIP(lex, otk::CmdPrefix);
            token(onk::RawText, TRY_POPX(lex, cmd_kind));
            space(lex);
            while (lex.at(otk::RawText)) {
                token(onk::RawText, TRY_POPX(lex, otk::RawText));
                if (lex.at(otk::Whitespace)) { space(lex); }
            }
            break;
        }

        case otk::CmdDateRaw:
        case otk::CmdDescription: {
            TRY_SKIP(lex, otk::CmdPrefix);
            cmdGuard = start(onk::CmdCustomTextCommand);
            token(onk::RawText, TRY_POPX(lex, cmd_kind));
            space(lex);
            auto attrsGuard = start(onk::Attrs);
            auto sub        = subToEol(
                lex, ParagraphTerminator + OrgTokSet{otk::Newline});
            if (sub.empty()) {
                empty();
            } else {
                SUB_PARSE(Paragraph, sub);
            }
            attrsGuard->end();
            break;
        }

        case otk::CmdHtmlHeadRaw: {
            TRY_SKIP(lex, otk::CmdPrefix);
            cmdGuard = start(onk::CmdCustomArgsCommand);
            token(onk::RawText, TRY_POPX(lex, cmd_kind));
            space(lex);
            SUB_PARSE(CommandArguments, lex);
            break;
        }

        case otk::CmdCall: {
            cmdGuard = start(onk::CmdCallCode);
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, otk::CmdCall);
            space(lex);
            // Name
            token(onk::Word, TRY_POPX(lex, otk::CmdRawArg));
            space(lex);

            // HeaderArgs
            if (lex.at(otk::BraceBegin)) {
                TRY_SKIP(lex, otk::BraceBegin);
                SUB_PARSE(CommandArguments, lex);
                TRY_SKIP(lex, otk::BraceEnd);
            } else {
                empty();
            }

            space(lex);

            // Args
            if (lex.at(otk::ParBegin)) {
                SUB_PARSE(CallArguments, lex);
            } else {
                empty();
            }

            space(lex);

            // EndArgs
            SUB_PARSE(CommandArguments, lex);

            break;
        }

        case otk::CmdAuthor:
        case otk::CmdCreator:
        case otk::CmdTitle:
        case otk::CmdCaption: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, cmd_kind);
            space(lex);
            switch (cmd_kind) {
                case otk::CmdAuthor:
                    cmdGuard = start(onk::CmdAuthor);
                    break;
                case otk::CmdCreator:
                    cmdGuard = start(onk::CmdCreator);
                    break;
                case otk::CmdTitle: cmdGuard = start(onk::CmdTitle); break;
                case otk::CmdCaption:
                    cmdGuard = start(onk::CmdCaption);
                    break;
                default: throw fatalError(lex, "unhandled command kind");
            }

            auto attrsGuard = start(onk::Attrs);
            auto sub        = subToEol(
                lex, ParagraphTerminator + OrgTokSet{otk::Newline});
            if (sub.empty()) {
                empty();
            } else {
                SUB_PARSE(Paragraph, sub);
            }
            break;
        }


        case otk::CmdEmailRaw:
        case otk::CmdLatexHeader:
        case otk::CmdStartup:
        case otk::CmdLanguage: {
            switch (cmd_kind) {
                case otk::CmdEmailRaw:
                    cmdGuard = start(onk::CmdEmail);
                    break;
                case otk::CmdLanguage:
                    cmdGuard = start(onk::CmdLanguage);
                    break;
                case otk::CmdLatexHeader:
                    cmdGuard = start(onk::CmdLatexHeader);
                    break;
                case otk::CmdStartup:
                    cmdGuard = start(onk::CmdStartup);
                    break;
                default: throw fatalError(lex, "");
            }

            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, cmd_kind);
            space(lex);
            while (lex.at(OrgTokSet{otk::RawText, otk::CmdRawArg})) {
                token(onk::RawText, pop(lex));
                space(lex);
            }
            break;
        }

        case otk::CmdFiletags: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, otk::CmdFiletags);
            space(lex);
            cmdGuard = start(onk::CmdFiletags);
            while (lex.at(OrgTokSet{otk::Word, otk::BigIdent}, +1)) {
                if (lex.at(otk::Colon)) {
                    skip(lex);
                } else {
                    space(lex);
                }
                SUB_PARSE(HashTag, lex);
                space(lex);
            }
            if (lex.at(otk::Colon)) { skip(lex); }
            break;
        }


        case otk::CmdLatexClass:
        case otk::CmdLatexCompiler: {
            TRY_SKIP(lex, otk::CmdPrefix);
            switch (cmd_kind) {
                case otk::CmdLatexCompiler: {
                    cmdGuard = start(onk::CmdLatexCompiler);
                    TRY_SKIP(lex, otk::CmdLatexCompiler);
                    break;
                }
                case otk::CmdLatexClass: {
                    cmdGuard = start(onk::CmdLatexClass);
                    TRY_SKIP(lex, otk::CmdLatexClass);
                    break;
                }
                default:
            }

            space(lex);
            token(onk::Word, TRY_POPX(lex, otk::CmdRawArg));
            break;
        }


        case otk::CmdLatexClassOptions: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, otk::CmdLatexClassOptions);
            space(lex);
            cmdGuard = start(onk::CmdLatexClassOptions);
            BOOST_OUTCOME_TRY(get_cmd_arguments());
            break;
        }

        case otk::CmdPropertyRaw: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, cmd_kind);
            space(lex);
            cmdGuard = start(onk::CmdPropertyRaw);
            token(onk::RawText, TRY_POPX(lex, otk::RawText));
            break;
        }

        case otk::CmdPropertyText: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, cmd_kind);
            space(lex);
            cmdGuard = start(onk::CmdPropertyArgs);
            token(onk::RawText, TRY_POPX(lex, otk::CmdRawArg));
            SUB_PARSE(CommandArguments, lex);
            SUB_PARSE(Paragraph, lex);
            break;
        }

        case otk::CmdInclude: {
            cmdGuard = start(onk::CmdInclude);
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, otk::CmdInclude);
            space(lex);
            SUB_PARSE(CommandArguments, lex);
            break;
        }

        case otk::CmdAttr: {
            cmdGuard = start(onk::CmdAttr);
            TRY_SKIP(lex, otk::CmdPrefix);
            token(onk::Word, TRY_POPX(lex, otk::CmdAttr));
            space(lex);
            SUB_PARSE(CommandArguments, lex);
            break;
        }

        case otk::CmdName:
        case otk::CmdResults:
        case otk::CmdHeader: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, cmd_kind);
            switch (cmd_kind) {
                case otk::CmdHeader:
                    cmdGuard = start(onk::CmdHeader);
                    break;
                case otk::CmdName: cmdGuard = start(onk::CmdName); break;
                case otk::CmdResults:
                    cmdGuard = start(onk::CmdResults);
                    break;
                default:
            }


            space(lex);
            SUB_PARSE(CommandArguments, lex);
            break;
        }


        case otk::CmdPropertyArgs: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, cmd_kind);
            space(lex);
            cmdGuard = start(onk::CmdPropertyArgs);
            token(onk::RawText, TRY_POPX(lex, otk::CmdRawArg));
            SUB_PARSE(CommandArguments, lex);
            break;
        }

        case otk::CmdOptions: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, cmd_kind);
            space(lex);
            cmdGuard = start(onk::CmdOptions);
            BOOST_OUTCOME_TRY(get_cmd_arguments());
            break;
        }

        case otk::CmdKeywordsRaw:
        case otk::CmdTblfm:
        case otk::CmdColumns: {
            TRY_SKIP(lex, otk::CmdPrefix);
            TRY_SKIP(lex, cmd_kind);
            space(lex);
            switch (cmd_kind) {
                case otk::CmdTblfm: cmdGuard = start(onk::CmdTblfm); break;
                case otk::CmdColumns:
                    cmdGuard = start(onk::CmdColumns);
                    break;
                case otk::CmdKeywordsRaw:
                    cmdGuard = start(onk::CmdKeywords);
                    break;
                default: throw fatalError(lex, "asdf");
            }
            BOOST_OUTCOME_TRY(get_cmd_arguments());
            break;
        }


        default: {
            throw fatalError(
                lex, fmt("Unhandled command kind {}", lex.kind(+1)));
        }
    }

    newline(lex);

    // End main tree that was started in the case statement
    return cmdGuard->end();
}


OrgParser::ParseResult OrgParser::parseStmtListItem(OrgLexer& lex) {
    auto __trace = trace(lex);
    switch (lex.kind()) {
        case otk::SubtreeStars: {
            return parseSubtree(lex);
            break;
        }
        case otk::Indent: {
            TRY_SKIP(lex, otk::Indent);
            auto res = parseList(lex);
            TRY_SKIP(lex, otk::Dedent);
            return res;
        }

        case otk::Whitespace: {
            token(onk::Space, TRY_POPX(lex, otk::Whitespace));
            break;
        }

        case otk::MediumNewline:
        case otk::LongNewline:
        case otk::Newline: {
            token(onk::Newline, pop(lex));
            break;
        }
        case otk::TextSeparator: {
            token(onk::TextSeparator, TRY_POPX(lex, otk::TextSeparator));
            break;
        }

        case otk::TableSeparator:
        case otk::LeadingPipe: {
            return parseTable(lex);
        }
        case otk::ColonExampleLine: {
            return parseColonExample(lex);
        }

        case otk::CmdPrefix: {
            switch (lex.kind(+1)) {
                case otk::CmdSrcBegin: {
                    return parseSrc(lex);
                }
                case otk::CmdExampleBegin: {
                    return parseExample(lex);
                }
                case otk::CmdExportBegin: {
                    return parseBlockExport(lex);
                }
                case otk::CmdVerseBegin:
                case otk::CmdCenterBegin:
                case otk::CmdCommentBegin:
                case otk::CmdDynamicBlockBegin:
                case otk::CmdQuoteBegin: {
                    return parseTextWrapCommand(lex);
                }
                case otk::CmdTableBegin: {
                    return parseTable(lex);
                }
                default: {
                    return parseLineCommand(lex);
                }
            }
            break;
        }
        default: {
            SubLexer sub{lex};
            while (lex.can_search(ParagraphTerminator)) {
                sub.add(lex.pop());
            }

            sub.start();
            return parseParagraph(sub);
        }
    }

    return ParseOk{};
}


OrgParser::ParseResult OrgParser::parseTop(OrgLexer& lex) {
    __perf_trace("parsing", "parseTop");
    auto __trace       = trace(lex);
    auto stmtListGuard = start(onk::StmtList);
    while (!lex.finished()) {
        if (lex.at(otk::Comment)) {
            skip(lex);
        } else {
            auto result = parseStmtListItem(lex);
            if (result.has_error()) {
                auto syncSkipGuard = start(onk::ErrorSkipGroup);

                while (lex.can_search(Newline)) {
                    token(onk::ErrorSkipToken, pop(lex));
                }

                syncSkipGuard->end();
            }
        };
    }
    return stmtListGuard->end();
}


OrgId OrgParser::parseFull(OrgLexer& lex) {
    __perf_trace("parsing", "parseFull");
    auto __trace = trace(lex);
    auto result  = parseTop(lex);
    extendSubtreeTrails(OrgId(0));
    return result.assume_value().result.value();
}

std::string OrgParser::printLexerToString(OrgLexer& lex) const {
    return lex.printToString([](hstd::ColStream& os, OrgToken const& t) {
        os << os.yellow() << escape_for_write(t.value.text) << os.end()
           << hstd::fmt1(t.value);
    });
}


bool OrgParser::at(CR<OrgLexer> lex, CR<OrgExpectable> item) {
    if (item.index() == 0 && lex.at(std::get<0>(item))) {
        return true;
    } else if (item.index() == 1 && lex.at(std::get<1>(item))) {
        return true;
    } else if (item.index() == 2) {
        auto const& tokens = std::get<Vec<OrgTokenKind>>(item);
        for (int i = 0; i < tokens.size(); ++i) {
            if (!lex.at(tokens.at(i), i)) { return false; }
        }

        return true;
    } else {
        return false;
    }
}


void assertValidStructure(OrgNodeGroup* group, OrgId id) {
    using Id = OrgNodeGroup::Id;

    Func<void(Id)> aux;
    aux = [&](Id top) {
        auto& g = *group;
        LOGIC_ASSERTION_CHECK_FMT(g.nodes.contains(top), "");
        auto fmt_id = [&](CR<Id> id) {
            return fmt("{} {}", id.format(), g.at(id).kind);
        };
        if (g.at(top).isTerminal() || g.at(top).isMono()) { return; }

        LOGIC_ASSERTION_CHECK_FMT(g.at(top).kind != onk::Empty, "");

        Id start = top + 1;
        Id id    = start;


        if (Opt<Slice<Id>> extentOpt = g.allSubnodesOf(top)) {
            Slice<Id> extent = extentOpt.value();
            LOGIC_ASSERTION_CHECK_FMT(g.nodes.contains(extent.first), "");
            LOGIC_ASSERTION_CHECK_FMT(g.nodes.contains(extent.last), "");

            Opt<OrgToken> first_token;
            for (auto const& id : extent) {
                if (g.at(id).isTerminal()) {
                    first_token = g.tokens->at(g.at(id).getToken());
                }
            }

            int     index = 0;
            Vec<Id> visited;
            while (extent.contains(id)) {
                LOGIC_ASSERTION_CHECK_FMT(g.nodes.contains(id), "");
                aux(id);
                visited.push_back(id);

                id = id + g.at(id).getExtent();
                LOGIC_ASSERTION_CHECK_FMT(
                    g.nodes.contains(id),
                    "next subnode"
                    "Step over the subnode of {} with extent {} "
                    "yielded id {} which is outsize of the group "
                    "range (index is {}, group size is {}), "
                    "subnode index is {}, size overflow is {}. First "
                    "token is {}",
                    fmt_id(start),
                    extent,
                    id.getUnmasked(),
                    id.getIndex(),
                    g.size(),
                    index,
                    id - g.nodes.back(),
                    first_token);


                id = id + 1;
                ++index;
            }

            LOGIC_ASSERTION_CHECK_FMT(
                extent.last + 1 == id,
                "range end Iteration over subnode ranges for {} did not "
                "end at the {} -- combined subnode extent strides summed "
                "up to {}. Total subnode count is {}, full extent is {} "
                "visited subnodes {}. First token is {}",
                top.getUnmasked(),
                (extent.last + 1).getUnmasked(),
                id.getUnmasked(),
                index,
                extent,
                visited | rv::transform(fmt_id) | rs::to<Vec>(),
                first_token);
        }
    };

    aux(id);
}


namespace {
OrgId extendSubtreeTrailsImpl(OrgParser* parser, OrgId id, int level) {
    OrgId const start = id;
    // Iterate over all nodes until the end of the group or until exit
    // condition is met. This assumes non-restructured tree that has
    // subnodes positioned flatlyl on the top level
    auto& g = *parser->group;
    while (id <= g.nodes.back()) {
        // NOTE: 'back' returns the last node, not one-past-last
        OrgNode node = g.at(id);
        if (node.kind == onk::Subtree) {
            if (parser->TraceState) {
                parser->print(
                    "Found subtree on the lower level " + id.format());
            }
            OrgId const tree = id;
            if (g.size(tree) == 0 && parser->TraceState) {
                parser->message(g.treeRepr(tree));
            }

            OrgId subId = g.subnode(tree, 0);
            int   sub   = g.val(subId).text.size();
            if (level < sub) {
                OrgId stmt = g.subnode(tree, 8);
                LOGIC_ASSERTION_CHECK_FMT(
                    g.at(stmt).kind == onk::StmtList
                        || g.at(stmt).kind == onk::ErrorSkipGroup,
                    "{}",
                    g.at(stmt));

                id = extendSubtreeTrailsImpl(parser, stmt + 1, sub);
                LOGIC_ASSERTION_CHECK_FMT(stmt + 1 <= id, "");
                // AUX returns next position to start looping from, so
                // the tree size is 'end - start - 1' to account for
                // the offset.

                // Extend the tree itself and nested statement list
                int stmt_extend = (id - stmt) - 1;
                int tree_extend = (id - tree) - 1;
                g.at(stmt).extend(stmt_extend);
                g.at(tree).extend(tree_extend);

                if (parser->TraceState) {
                    parser->print(
                        fmt("Found nested subtree tree={} stmt={} "
                            "tree-extend={} stmt-extend={}",
                            tree.format(),
                            stmt.format(),
                            tree_extend,
                            stmt_extend));
                }

                auto treeSlice = g.allSubnodesOf(tree).value();
                auto stmtSlice = g.allSubnodesOf(tree).value();

                // Structural correctness checks -- mostly for
                // debugging of the implementation, malformed incoming
                // data is not expected.
                assertValidStructure(parser->group, tree);
                LOGIC_ASSERTION_CHECK_FMT(
                    treeSlice.last <= g.nodes.back(), "");
                LOGIC_ASSERTION_CHECK_FMT(
                    stmtSlice.last <= g.nodes.back(), "");
                LOGIC_ASSERTION_CHECK_FMT(
                    treeSlice.last == stmtSlice.last,
                    "extend tree {} -- {}",
                    treeSlice,
                    stmtSlice);
                LOGIC_ASSERTION_CHECK_FMT(
                    treeSlice.contains(stmtSlice),
                    "statement containment {} -- {}",
                    treeSlice,
                    stmtSlice);


            } else {
                if (parser->TraceState) {
                    parser->print(
                        "Found subtree on the same level or above "
                        + id.format());
                }
                // Found subtree on the same level or above
                break;
            }
        } else {
            // Node is not a subtree, skipping.
            ++id;
        }
    }

    // Return next starting position for the caller start
    return id;
}
} // namespace

void OrgParser::extendSubtreeTrails(OrgId position) {
    __perf_trace("parsing", "extendSubtreeTrails");
    extendSubtreeTrailsImpl(this, position, 0);
    assertValidStructure(group, position);
}

OrgParser::ParseOk OrgParser::NodeGuard::end(
    const std::string& desc,
    int                line,
    const char*        function) {
    LOGIC_ASSERTION_CHECK_FMT(
        !startId.isNil(), "Trying to close nil tree");
    auto result = parser->end_impl(
        desc + (debug.empty() ? "" : " for guard '" + debug + "'"),
        line,
        function);
    LOGIC_ASSERTION_CHECK_FMT(
        parser->treeDepth() == startingDepth,
        "{} != {} at {}:{}",
        startingDepth,
        parser->treeDepth(),
        function,
        line);

    this->closed = true;
    return OrgParser::ParseOk{result};
}
