#pragma once

#include <parse/OrgParser.hpp>
#pragma clang diagnostic ignored "-Wunused-result"
#pragma clang diagnostic ignored "-Wformat-security"


using otk = OrgTokenKind;
using org = OrgNodeKind;
using ock = OrgCommandKind;
using Err = OrgParser::Errors;

#include "OrgParserMacros.hpp"


namespace {

template <bool TraceState>
class OrgParserImpl : public OrgParser {

  protected:
    void skipLineCommand(OrgLexer& lex) {
        skip(lex, otk::CommandPrefix);
        skip(lex, otk::LineCommand);
        skip(lex, otk::Colon);
        while (lex.at(otk::SkipSpace)) {
            lex.next();
        }
    }

    CR<OrgNode> pending() const {
        Q_ASSERT(0 <= group->treeDepth());
        return group->lastPending();
    }

    OrgId fail(OrgTokenId invalid) {
        token(OrgNodeKind::ErrorToken, invalid);
        /// TODO insert token with error description
        token(OrgNodeKind::ErrorTerminator, OrgTokenId::Nil());
        OrgId failed           = end();
        group->at(failed).kind = OrgNodeKind::Error;
        return failed;
    }

    OrgId back() const { return group->nodes.back(); }

    int treeDepth() const {
        Q_ASSERT(0 <= group->treeDepth());
        return group->treeDepth();
    }

    OrgId start(OrgNodeKind kind) { return group->startTree(kind); }
    OrgId end() {
        Q_ASSERT(0 <= group->treeDepth());
        return group->endTree();
    }
    OrgId   empty() { return token(getEmpty()); }
    OrgNode getEmpty() { return OrgNode::Mono(OrgNodeKind::Empty); }
    OrgId   token(CR<OrgNode> node) { return group->token(node); }
    OrgId   token(OrgNodeKind kind, OrgTokenId tok) {
        return group->token(kind, tok);
    }

    OrgId fake(OrgNodeKind kind) {
        return group->token(
            kind, group->tokens->add(OrgToken(OrgTokenKind::None)));
    }


    bool at(CR<OrgLexer> lex, CR<OrgParser::OrgExpectable> item) {
        if (item.index() == 0 && lex.at(std::get<0>(item))) {
            return true;
        } else if (item.index() == 1 && lex.at(std::get<1>(item))) {
            return true;
        } else if (
            item.index() == 2 //
            && lex.at(std::get<2>(item).kind)
            && lex.tok().strVal() == std::get<2>(item).value) {
            return true;
        } else {
            return false;
        }
    }

    void expect(CR<OrgLexer> lex, CR<OrgParser::OrgExpectable> item) {
        if (!(at(lex, item))) {
            throw wrapError(
                Err::UnexpectedToken(lex, getLoc(lex), {item}), lex);
        }
    }

    OrgTokenId pop(OrgLexer& lex, CR<OrgParser::OrgExpectable> tok) {
        expect(lex, tok);
        return lex.pop();
    }

    void skip(OrgLexer& lex, CR<OrgParser::OrgExpectable> item) {
        expect(lex, item);
        lex.next();
    }


  public:
    int  depth = 0;
    void report(CR<Report> in);

    Func<void(CR<Report>)>              reportHook;
    Func<void(CR<Report>, bool&, bool)> traceUpdateHook;
    OrgNodeGroup*                       group = nullptr;
    OrgParserImpl(OrgNodeGroup* _group) : group(_group) {}

    virtual void reserve(int size) override { group->nodes.reserve(size); }

    void extendSubtreeTrails(OrgId position) override;
    void extendAttachedTrails(OrgId position) override;

    using OrgParser::OrgParser;
    Func<LineCol(CR<PosStr>)> locationResolver;


    void setReportHook(Func<void(CR<Report>)> in) override {
        reportHook = in;
    }

    void setTraceUpdateHook(
        Func<void(CR<Report>, bool&, bool)> in) override {
        traceUpdateHook = in;
    }

    void setLocationResolver(Func<LineCol(CR<PosStr>)> in) override {
        locationResolver = in;
    }


    virtual Opt<LineCol> getLoc(CR<OrgLexer> lex) override {
        if (!locationResolver) {
            return std::nullopt;
        }

        if (lex.finished()) {
            return std::nullopt;
        } else {
            for (int offset = 0;
                 lex.hasNext(-offset) || lex.hasNext(offset);
                 ++offset) {
                // Try incrementally widening lookarounds on the current
                // lexer position until there is a token that has proper
                // location information.
                for (int i : Vec<int>{-1, 1}) {
                    if (lex.hasNext(offset * i)) {
                        OrgToken tok = lex.tok(offset * i);
                        if (tok.hasData()) {
                            PosStr str{tok.getText()};
                            return locationResolver(str);
                        }
                        // If offset falls out of the lexer range on both
                        // ends, terminate lookup.
                    }
                }
            }
            return std::nullopt;
        }
    }

    Slice<OrgId> parseText(OrgLexer& lex);

    /// First pass of the text processing pass. Fold all known text
    /// structures into larger nodes, convert opening markup tokens into
    /// `XOpen` and `XClose` nodes.
    void textFold(OrgLexer& lex);

    /// Recursively fold text block in the specified range, updating nested
    /// markup nodes and converting `XOpen/XClose` elements to `X/Empty`
    /// nodes as needed.
    void parseTextRecursiveFold(Slice<OrgId> range);

#define OVERRIDE(Kind) virtual OrgId parse##Kind(OrgLexer& lex) override;
    EACH_PARSER_METHOD(OVERRIDE);
#undef OVERRIDE

    virtual OrgId parseFull(OrgLexer& lex);
    OrgId         parseParagraph(OrgLexer& lex, bool onToplevel);
    virtual OrgId parseTextWrapCommand(OrgLexer& lex, OrgCommandKind kind)
        override;

    void parseCSVArguments(OrgLexer& lex) override;
};


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


template <bool TraceState>
void OrgParserImpl<TraceState>::parseCSVArguments(OrgLexer& lex) {
    __perf_trace("parseCSVArguments");
    __trace();
    auto tok = token(org::Ident, pop(lex, otk::Ident));
    __token(tok);

    if (lex.at(otk::ParOpen)) {
        __skip(lex, otk::ParOpen);
        while (lex.at(otk::RawText)) {
            token(org::RawText, pop(lex, otk::RawText));
            if (lex.at(otk::Comma)) {
                lex.next();
            }
        }
        __skip(lex, otk::ParClose);
    }
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseMacro(OrgLexer& lex) {
    __perf_trace("parseMacro");
    __trace();
    __start(org::Macro);
    __skip(lex, otk::MacroOpen);
    parseCSVArguments(lex);
    __skip(lex, otk::MacroClose);
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseRawUrl(OrgLexer& lex) {
    __perf_trace("parseRawUrl");
    __trace();
    auto tok = token(org::RawLink, pop(lex, otk::RawUrl));
    __token(tok);
    return tok;
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parsePlaceholder(OrgLexer& lex) {
    __perf_trace("parsePlaceholder");
    __trace();
    __skip(lex, otk::GroupStart);
    __skip(lex, otk::AngleOpen);
    auto tok = token(org::Placeholder, pop(lex, otk::RawText));
    __token(tok);
    __skip(lex, otk::AngleClose);
    __skip(lex, otk::GroupEnd);

    return tok;
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseTarget(OrgLexer& lex) {
    __perf_trace("parseTarget");
    __trace();
    __skip(lex, otk::GroupStart);
    __skip(lex, otk::DoubleAngleOpen);
    auto tok = token(org::Target, pop(lex, otk::RawText));
    __token(tok);
    __skip(lex, otk::DoubleAngleClose);
    __skip(lex, otk::GroupEnd);

    return tok;
}


template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseLatex(OrgLexer& lex) {
    __perf_trace("parseLatex");
    __trace();
    __skip(lex, otk::GroupStart);
    __skip(lex, otk::LatexParOpen);
    auto tok = token(org::InlineMath, pop(lex, otk::LatexInlineRaw));
    __token(tok);
    __skip(lex, otk::LatexParClose);
    __skip(lex, otk::GroupEnd);
    return tok;
}

template <bool TraceState>
void OrgParserImpl<TraceState>::textFold(OrgLexer& lex) {
    __perf_trace("textFold");
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
            auto msg                                                      \
                = "Mismatched kind openings pending tree was '$#', but "  \
                  "found '$#' at $# parser $#"                            \
                % to_string_vec(                                          \
                      pending().kind,                                     \
                      org::Kind,                                          \
                      getLocMsg(lex),                                     \
                      __LINE__);                                          \
            __print(msg);                                                 \
            qFatal(strdup(msg));                                          \
            fail(pop(lex, otk::Kind##Close));                             \
        }                                                                 \
        break;                                                            \
    }

#define CASE_SINGLE(Kind)                                                 \
    case otk::Kind: {                                                     \
        auto t = token(org::Kind, pop(lex, otk::Kind));                   \
        __token(t);                                                       \
        break;                                                            \
    }

#define CASE_INLINE(Kind)                                                 \
    case otk::Kind##InlineOpen: {                                         \
        __start(org::Kind);                                               \
        lex.next();                                                       \
        textFold(lex);                                                    \
        break;                                                            \
    }                                                                     \
                                                                          \
    case otk::Kind##InlineClose: {                                        \
        if (pending().kind == org::Kind) {                                \
            __end();                                                      \
            lex.next();                                                   \
        } else {                                                          \
            fail(pop(lex, otk::Kind##InlineClose));                       \
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
            CASE_MARKUP(Monospace);
            CASE_MARKUP(Backtick);

            CASE_SINGLE(Space);
            CASE_SINGLE(Escaped);
            CASE_SINGLE(RawText);
            CASE_SINGLE(Newline);
            CASE_SINGLE(Word);
            CASE_SINGLE(BigIdent);
            CASE_SINGLE(Punctuation);
            CASE_SINGLE(Colon);

            CASE_INLINE(Bold);
            CASE_INLINE(Italic);
            CASE_INLINE(Backtick);

            case otk::Circumflex: {
                auto sub = token(
                    org::Punctuation, pop(lex, otk::Circumflex));
                __token(sub);
                break;
            }

            case otk::DoubleSlash: {
                auto sub = token(
                    org::Punctuation, pop(lex, otk::DoubleSlash));
                __token(sub);
                break;
            }

            case otk::MaybeWord: {
                auto sub = token(
                    org::Punctuation, pop(lex, otk::MaybeWord));
                __token(sub);
                break;
            }

                // CASE_MARKUP(Quote);
            case otk::QuoteOpen: {
                auto sub = token(
                    org::Punctuation, pop(lex, otk::QuoteOpen));
                __token(sub);
                break;
            }

            case otk::QuoteClose: {
                auto sub = token(
                    org::Punctuation, pop(lex, otk::QuoteClose));
                __token(sub);
                break;
            }

                // CASE_MARKUP(Par);
            case otk::ParOpen: {
                auto sub = token(org::Punctuation, pop(lex, otk::ParOpen));
                __token(sub);
                break;
            }

            case otk::ParClose: {
                auto sub = token(
                    org::Punctuation, pop(lex, otk::ParClose));
                __token(sub);
                break;
            }

            case otk::SrcOpen: parseSrcInline(lex); break;
            case otk::ActiveTimeBegin:
            case otk::InactiveTimeBegin: parseTimeRange(lex); break;
            case otk::HashTag: parseHashTag(lex); break;
            case otk::LinkOpen: parseLink(lex); break;
            case otk::MacroOpen: parseMacro(lex); break;
            case otk::RawUrl: parseRawUrl(lex); break;
            case otk::FootnoteStart: parseFootnote(lex); break;

            case otk::DollarOpen:
            case otk::LatexParOpen:
            case otk::DoubleDollarOpen:
            case otk::LatexBraceOpen: parseInlineMath(lex); break;

            case otk::SkipAny: {
                auto any = token(org::SkipAny, pop(lex, otk::SkipAny));
                __token(any);
                break;
            }

            case otk::AtMention: {
                auto any = token(org::AtMention, pop(lex, otk::AtMention));
                __token(any);
                break;
            }

            case otk::DoubleAngleOpen: {
                __skip(lex, otk::DoubleAngleOpen);
                auto tmp = token(org::Target, pop(lex, otk::RawText));
                __token(tmp);
                __skip(lex, otk::DoubleAngleClose);
                break;
            }

            case otk::TripleAngleOpen: {
                __skip(lex, otk::TripleAngleOpen);
                auto target = token(
                    org::RadioTarget, pop(lex, otk::RawText));
                __token(target);
                __skip(lex, otk::TripleAngleClose);
                break;
            }

            case otk::BoldInline:
            case otk::ItalicInline:
            case otk::VerbatimInline:
            case otk::MonospaceInline:
            case otk::BacktickInline:
            case otk::UnderlineInline:
            case otk::StrikeInline: {
                throw wrapError(
                    Err::UnhandledToken(
                        lex,
                        "Non-directional inline markup token incountered "
                        "during text parsing"),
                    lex);
            }

            case otk::GroupStart: {
                switch (lex.kind(+1)) {
                    case otk::LinkOpen: {
                        (void)parseLink(lex);
                        break;
                    }
                    case otk::FootnoteStart: {
                        (void)parseFootnote(lex);
                        break;
                    }
                    case otk::AngleOpen: {
                        (void)parsePlaceholder(lex);
                        break;
                    }
                    case otk::LatexParOpen: {
                        (void)parseLatex(lex);
                        break;
                    }
                    case otk::SymbolStart: {
                        (void)parseSymbol(lex);
                        break;
                    }
                    case otk::DoubleAngleOpen: {
                        (void)parseTarget(lex);
                        break;
                    }
                    default:
                        throw wrapError(Err::UnhandledToken(lex), lex);
                }
                break;
            }

            default: {
                throw wrapError(Err::UnhandledToken(lex), lex);
            }
        }
    }

#undef CASE_MARKUP
#undef CASE_SINGLE
#undef CASE_INLINE
}

template <bool TraceState>
Slice<OrgId> OrgParserImpl<TraceState>::parseText(OrgLexer& lex) {
    __perf_trace("parseText");
    __trace();
    OrgId   first     = back();
    QString forMsg    = getLocMsg(lex);
    int     treeStart = treeDepth();
    textFold(lex);
    int treeEnd = treeDepth();
    __print(
        "Trace levels after text fold start:$#, end:$#"
        % to_string_vec(treeStart, treeEnd));

    Q_ASSERT_X(
        treeStart <= treeEnd,
        "parseText",
        ("Text fold created unbalanced tree - starting with depth $# "
         "ended up on depth $# on position $# (starting from $#)"
         % to_string_vec(treeStart, treeEnd, getLocMsg(lex), forMsg)));

    while (treeStart < treeDepth()) {
        __print("Warn, force closing content on " + getLocMsg(lex));
        __end();
    }

    OrgId last = back();
    return slice(first, last);
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseLink(OrgLexer& lex) {
    __perf_trace("parseLink");
    __trace();
    __start(org::Link);
    __skip(lex, otk::GroupStart);
    __skip(lex, otk::LinkOpen);
    __skip(lex, otk::LinkTargetOpen);
    if (lex.at(otk::LinkInternal)) {
        empty();
        auto inter = token(org::RawText, pop(lex, otk::LinkInternal));
        __token(inter);
    } else if (lex.at(otk::LinkFull)) {
        empty();
        auto full = token(org::RawText, pop(lex, otk::LinkFull));
        __token(full);
    } else {
        auto prot = token(org::Ident, pop(lex, otk::LinkProtocol));
        __token(prot);
        auto target = token(org::RawText, pop(lex, otk::LinkTarget));
        __token(target);
    }
    __skip(lex, otk::LinkTargetClose);
    if (lex.at(otk::LinkDescriptionOpen)) {
        auto sub = SubLexer(
            lex.in,
            lex.getInside(
                {otk::LinkDescriptionOpen}, {otk::LinkDescriptionClose}));
        __start(org::Paragraph);
        parseText(sub);
        __end();

    } else {
        empty();
    }

    __skip(lex, otk::LinkClose);
    __skip(lex, otk::GroupEnd);
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseInlineMath(OrgLexer& lex) {
    __perf_trace("parseInlineMath");
    __trace();
    const auto startKind = lex.tok().kind;
    const auto regular   = OrgTokSet{otk::DollarOpen, otk::LatexParOpen};
    const auto display   = OrgTokSet{
        otk::DoubleDollarOpen, otk::LatexBraceOpen};

    __skip(lex, regular + display);
    __start(
        regular.contains(startKind) ? org::InlineMath : org::DisplayMath);

    OrgTokenKind close;
    switch (startKind) {
        case otk::DollarOpen: {
            __skip(lex, otk::DollarClose);
            break;
        }
        case otk::DoubleDollarOpen: {
            __skip(lex, otk::DoubleDollarClose);
            break;
        }
        case otk::LatexParOpen: {
            __skip(lex, otk::LatexParClose);
            break;
        }
        case otk::LatexBraceOpen: {
            __skip(lex, otk::LatexBraceClose);
            break;
        }
        default: {
            assert(false);
        }
    }

    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseSymbol(OrgLexer& lex) {
    __perf_trace("parseSymbol");
    __trace();
    __skip(lex, otk::GroupStart);
    __skip(lex, otk::SymbolStart);
    __start(org::Symbol);
    token(org::Ident, pop(lex, otk::Ident));

    while (lex.at(otk::MetaBraceOpen)) {
        __skip(lex, otk::MetaBraceOpen);
        token(org::RawText, pop(lex, otk::MetaBraceBody));
        __skip(lex, otk::MetaBraceClose);
    }

    while (lex.at(otk::MetaArgsOpen)) {
        __skip(lex, otk::MetaArgsOpen);
        parseParagraph(lex, false);
        __skip(lex, otk::MetaArgsClose);
    }

    __skip(lex, otk::GroupEnd);

    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseHashTag(OrgLexer& lex) {
    __perf_trace("parseHashTag");
    __trace();
    __start(org::HashTag);
    space(lex);
    if (lex.at(otk::AtMention)) {
        // Org-mode suppors tags like '@work' etc.
        token(org::RawText, pop(lex, otk::AtMention));
    } else {
        token(org::RawText, pop(lex, otk::HashTag));
    }

    if (lex.at(otk::HashTagSub)) {
        __skip(lex, otk::HashTagSub);
        if (lex.at(otk::HashTag)) {
            parseHashTag(lex);

        } else {
            __skip(lex, otk::HashTagOpen);
            while (!lex.finished() && !lex.at(otk::HashTagClose)) {
                parseHashTag(lex);
                if (lex.at(otk::Comma)) {
                    lex.next();
                }
            }
            __skip(lex, otk::HashTagClose);
        }
    }
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseTimeStamp(OrgLexer& lex) {
    __perf_trace("parseTimeStamp");
    __trace();
    expect(lex, OrgTokSet{otk::InactiveTimeBegin, otk::ActiveTimeBegin});
    bool active = lex.at(otk::ActiveTimeBegin);
    __skip(lex, active ? otk::ActiveTimeBegin : otk::InactiveTimeBegin);
    if (!lex.at(otk::DynamicTimeContent)) {
        if (active) {
            __start(org::StaticActiveTime);
        } else {
            __start(org::StaticInactiveTime);
        }

        // Date part is usually used, but I think supporting *time* stamps
        // also makes sense
        if (lex.at(otk::StaticTimeDatePart)) {
            auto year = token(
                org::RawText, pop(lex, otk::StaticTimeDatePart));
            __token(year);
            skipSpace(lex);
        } else {
            empty();
        }

        // Day can sometimes be added to the timestamp
        if (lex.at(otk::StaticTimeDayPart)) {
            auto day = token(
                org::RawText, pop(lex, otk::StaticTimeDayPart));
            __token(day);

            skipSpace(lex);
        } else {
            empty();
        }

        if (lex.at(otk::StaticTimeClockPart)) {
            auto clock = token(
                org::RawText, pop(lex, otk::StaticTimeClockPart));
            __token(clock);
            skipSpace(lex);
        } else {
            empty();
        }

        if (lex.at(otk::StaticTimeRepeater)) {
            auto repeater = token(
                org::RawText, pop(lex, otk::StaticTimeRepeater));
            __token(repeater);
            skipSpace(lex);
        } else {
            empty();
        }


        __end();

    } else {
        if (active) {
            __start(org::DynamicActiveTime);
        } else {
            __start(org::DynamicInactiveTime);
        }

        auto sub = token(org::RawText, pop(lex, otk::DynamicTimeContent));

        __end();
    }

    __skip(lex, active ? otk::ActiveTimeEnd : otk::InactiveTimeEnd);
    return back();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseTimeRange(OrgLexer& lex) {
    __perf_trace("parseTimeRange");
    __trace();
    const OrgTokSet times{
        otk::SkipSpace,
        otk::InactiveTimeBegin,
        otk::InactiveTimeEnd,
        otk::ActiveTimeBegin,
        otk::ActiveTimeEnd,
        otk::DynamicTimeContent,
        otk::StaticTimeDatePart,
        otk::StaticTimeDayPart,
        otk::StaticTimeClockPart,
        otk::StaticTimeRepeater,
    };


    if (lex.ahead(times, OrgTokSet{otk::TimeDash})) {
        __start(org::TimeRange);
        parseTimeStamp(lex);
        __skip(lex, otk::TimeDash);
        parseTimeStamp(lex);
        skipSpace(lex);
        if (lex.at(otk::TimeArrow)) {
            __skip(lex, otk::TimeArrow);
            skipSpace(lex);
            token(org::SimpleTime, pop(lex, otk::TimeDuration));
        } else {
            empty();
        }

        __end_return();
    } else {
        return parseTimeStamp(lex);
    }


    // __end_return();

    // if (lex.ahead(times, OrgTokSet{otk::TimeDash})) {
    //     __start(org::TimeRange);
    //     // IMPLEMENT check for identical start/end bracket categories:
    //     // `[]--[]` or `<>--<>` but not `<>--[]`
    //     token(org::Time, pop(lex, times));
    //     __skip(lex, otk::TimeDash);
    //     token(org::Time, pop(lex, times));

    //     if (lex.ahead(otk::SkipSpace, otk::TimeArrow)) {
    //         space(lex);
    //         __skip(lex, otk::TimeArrow);
    //         space(lex);
    //         token(org::SimpleTime, pop(lex, otk::TimeDuration));
    //     } else {
    //         empty();
    //     }

    //     __end_return();
    // } else {
    //     return token(org::Time, pop(lex, times));
    // }
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseFootnote(OrgLexer& lex) {
    __perf_trace("parseFootnote");
    __trace();
    __skip(lex, otk::GroupStart);
    // TODO replace 'footnote start' + '::' with a 'inline footnote start'
    // / 'footnote start nodes'
    __skip(lex, otk::FootnoteStart);
    if (lex.at(otk::Colon)) {
        __start(org::Footnote);
        __skip(lex, otk::Colon);
        parseIdent(lex);
    } else {
        __start(org::InlineFootnote);
        __skip(lex, otk::DoubleColon);
        parseInlineParagraph(lex);
    }

    __skip(lex, otk::FootnoteEnd);
    __skip(lex, otk::GroupEnd);

    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseIdent(OrgLexer& lex) {
    __perf_trace("parseIdent");
    __trace();
    auto tok = token(org::Ident, pop(lex, otk::Ident));
    __token(tok);
    return tok;
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseSrcInline(OrgLexer& lex) {
    __perf_trace("parseSrcInline");
    __trace();
    __start(org::SrcInlineCode);
    __skip(lex, otk::SrcOpen);
    {
        token(org::Ident, pop(lex, otk::SrcName));
        __start(org::CodeLine);
        token(org::CodeText, pop(lex, otk::SrcBody));
        __end();
    }
    __skip(lex, otk::SrcClose);
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseTable(OrgLexer& lex) {
    __perf_trace("parseTable");
    __trace();
    __start(org::Table);
    __skip(lex, otk::TableBegin);
    __skip(lex, otk::CmdArguments);
    empty();

    ParseCb parseContent = [this](OrgLexer& lex) {
        auto sub = SubLexer(
            lex.in, lex.getInside({otk::ContentStart}, {otk::ContentEnd}));

        return parseTop(sub);
    };

    while (!lex.at(otk::TableEnd)) {
        switch (lex.kind()) {
            case otk::PipeOpen: {
                __start(org::TableRow);
                empty();
                empty();

                __skip(lex, otk::PipeOpen);
                __start(org::TableCell);
                {
                    empty();
                    parseContent(lex);
                }
                __end();

                while (lex.at(otk::PipeSeparator)) {
                    __skip(lex, otk::PipeSeparator);
                    __start(org::TableCell);
                    {
                        empty();
                        parseContent(lex);
                    }
                    __end();
                }

                __skip(lex, otk::PipeClose);
                __end();
                break;
            }
            case otk::PipeCellOpen: {
                __start(org::TableRow);
                empty();
                empty();

                __skip(lex, otk::PipeCellOpen);
                __start(org::TableCell);
                {

                    empty();
                    parseContent(lex);
                }
                __end();

                while (lex.at(otk::PipeCellOpen)) {
                    __skip(lex, otk::PipeCellOpen);
                    __start(org::TableCell);
                    {
                        empty();
                        parseContent(lex);
                    }
                    __end();
                }

                __end();
                break;
            }
            case otk::RowSpec: {
                __start(org::TableRow);
                empty();
                __skip(lex, otk::RowSpec);
                __skip(lex, otk::CmdArguments);
                empty();
                __start(org::TableCell);
                {
                    empty();
                    parseContent(lex);
                }
                __end();
                while (lex.at(otk::CellSpec)) {
                    __skip(lex, otk::CellSpec);
                    __skip(lex, otk::CmdArguments);
                    __start(org::TableCell);
                    {
                        empty();
                        parseContent(lex);
                    }
                    __end();
                }

                __end();
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
    __skip(lex, otk::TableEnd);
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseParagraph(
    OrgLexer& lex,
    bool      onToplevel) {
    __perf_trace("parseParagraph");
    __trace();
    expect(lex, otk::ParagraphStart);
    const auto& paragraphTokens = lex.getInside(
        IntSet<OrgTokenKind>{otk::ParagraphStart},
        IntSet<OrgTokenKind>{otk::ParagraphEnd});

    if (paragraphTokens.empty()) {
        __start(org::Paragraph);
        __end();
        return back();
    }

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
                    default: {
                    }
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
                    default: {
                    }
                }
            }
        }
    }


    __start(org::Paragraph);
    auto nodes = parseText(sub);
    __end();
    return back();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseInlineParagraph(OrgLexer& lex) {
    __perf_trace("parseInlineParagraph");
    __trace();
    return parseParagraph(lex, false);
}


template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseTopParagraph(OrgLexer& lex) {
    __perf_trace("parseTopParagraph");
    __trace();
    return parseParagraph(lex, false);
}


template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseCommandArguments(OrgLexer& lex) {
    __perf_trace("parseCommandArguments");
    __trace();
    __start(org::InlineStmtList);
    while (lex.at(OrgTokSet{otk::CommandValue, otk::CommandKey})) {
        if (lex.at(otk::CommandKey)) {
            __start(org::CmdValue);
            {
                auto ident = token(org::Ident, pop(lex, otk::CommandKey));
                __token(ident);
                space(lex);
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
                space(lex);
                auto raw = token(
                    org::RawText, pop(lex, otk::CommandValue));
                __token(raw);
            }
            __end();
        }
    }

    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseSrcArguments(OrgLexer& lex) {
    __perf_trace("parseSrcArguments");
    __trace();
    __start(org::CmdArguments);
    __start(org::InlineStmtList);

    while (lex.at(otk::CommandFlag)) {
        token(org::CmdFlag, pop(lex, otk::CommandFlag));
    }
    __end();
    parseCommandArguments(lex);
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseTextWrapCommand(
    OrgLexer&      lex,
    OrgCommandKind kind) {
    __perf_trace("parseTextWrapCommand");
    __trace();
    switch (kind) {
        case ock::BeginCenter: __start(org::CenterBlock); break;
        case ock::BeginQuote: __start(org::QuoteBlock); break;
        case ock::BeginAdmonition: __start(org::AdmonitionBlock); break;
        default: wrapError(Err::UnhandledToken(lex), lex);
    }

    __skip(lex, otk::CommandPrefix);
    __skip(lex, otk::CommandBegin);
    space(lex);
    __skip(lex, otk::CommandArgumentsBegin);
    if (lex.at(otk::RawText)) {
        lex.next();
    } else if (lex.at(otk::Ident)) {
        lex.next();
    };
    __skip(lex, otk::CommandArgumentsEnd);
    __skip(lex, otk::CommandContentStart);
    parseParagraph(lex, true);
    __skip(lex, otk::CommandContentEnd);
    __skip(lex, otk::CommandPrefix);
    __skip(lex, otk::CommandEnd);
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseBlockExport(OrgLexer& lex) {
    __perf_trace("parseExample");
    __trace();
    __start(org::BlockExport);

    __skip(lex, otk::CommandPrefix);
    __skip(lex, otk::CommandBegin);

    // command arguments
    space(lex);
    __skip(lex, otk::CommandArgumentsBegin);
    auto args = token(org::Ident, pop(lex, otk::Ident));
    __token(args);
    __skip(lex, otk::CommandArgumentsEnd);

    // command content
    __skip(lex, otk::CommandContentStart);
    auto body = token(org::RawText, pop(lex, otk::RawText));
    __token(body);
    __skip(lex, otk::CommandContentEnd);

    __skip(lex, otk::CommandPrefix);
    __skip(lex, otk::CommandEnd);

    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseExample(OrgLexer& lex) {
    __perf_trace("parseExample");
    __trace();
    __start(org::Example);

    __skip(lex, otk::CommandPrefix);
    __skip(lex, otk::CommandBegin);

    { // command arguments
        __skip(lex, otk::CommandArgumentsBegin);
        auto args = token(org::RawText, pop(lex, otk::RawText));
        __token(args);
        __skip(lex, otk::CommandArgumentsEnd);
    }

    { // command content
        __skip(lex, otk::CommandContentStart);
        auto body = token(org::RawText, pop(lex, otk::RawText));
        __token(body);
        __skip(lex, otk::CommandContentEnd);
    }

    __skip(lex, otk::CommandPrefix);
    __skip(lex, otk::CommandEnd);

    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseSrc(OrgLexer& lex) {
    __perf_trace("parseSrc");
    __trace();
    __start(org::SrcCode);
    __skip(lex, otk::CommandPrefix);
    __skip(lex, otk::CommandBegin);
    // header_args_lang
    {
        skipSpace(lex);
        __skip(lex, otk::CommandArgumentsBegin);

        const auto lang = pop(lex, otk::Word);
        if (lex.strVal().empty()) {
            empty();
        } else {
            token(org::Ident, lang);
        }

        parseSrcArguments(lex);
        __skip(lex, otk::CommandArgumentsEnd);
    };
    // body
    {

        __start(org::StmtList);
        __skip(lex, otk::CommandContentStart);
        __skip(lex, otk::CodeContentBegin);
        while (!lex.at(
            OrgTokSet{otk::CommandContentEnd, otk::CodeContentEnd})) {
            __start(org::CodeLine);
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
                        __skip(lex, otk::ParOpen);
                        __skip(lex, otk::Ident);
                        __skip(lex, otk::Colon);
                        __start(org::CodeCallout);
                        token(org::Ident, pop(lex, otk::Ident));
                        __end();
                        __skip(lex, otk::ParClose);
                        break;
                    }
                    case otk::CodeContentEnd: {
                        break;
                        break;
                    }
                    case otk::DoubleAngleOpen: {
                        __skip(lex, otk::DoubleAngleOpen);
                        __start(org::CodeTangle);
                        parseCSVArguments(lex);
                        __end();
                        __skip(lex, otk::DoubleAngleClose);
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
            __end(); // finish code line
        }

        __skip(lex, otk::CodeContentEnd);
        __skip(lex, otk::CommandContentEnd);
        __end(); // finish statement
    };
    // eval_result
    { empty(); };
    __skip(lex, otk::CommandPrefix);
    __skip(lex, otk::CommandEnd);
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseListItemBody(OrgLexer& lex) {
    __perf_trace("parseListItemBody");
    __trace();
    __start(org::StmtList);
    while (!lex.at(otk::StmtListClose)) {
        if (lex.at(Vec<OrgTokenKind>{otk::Indent, otk::ListItemStart})) {
            lex.next();
            parseNestedList(lex);
            __skip(lex, otk::Dedent);
        } else {
            parseToplevelItem(lex);
        }
    }
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseListItem(OrgLexer& lex) {
    __perf_trace("parseListItem");
    __trace();
    __start(org::ListItem);
    // prefix, 0
    { token(org::RawText, pop(lex, otk::ListItemStart)); }
    skipSpace(lex);
    // counter, 1
    {
        empty(); // TODO parse counter
    }
    // checkbox 2
    {
        if (lex.at(otk::Checkbox)) {
            token(org::Checkbox, pop(lex, otk::Checkbox));
        } else {
            empty();
        }
    }
    // tag, 3
    bool isAnnotatedParagraph = false;
    {
        if (lex.at(otk::ListDescOpen)) {
            isAnnotatedParagraph = true;
            __skip(lex, otk::ListDescOpen);
            __start(org::AnnotatedParagraph);
            __start(org::ListTag);
            parseParagraph(lex, false);
            __end();
            __skip(lex, otk::DoubleColon);
            __skip(lex, otk::ListDescClose);
            __end();
        } else {
            empty();
        }
    }
    // completion, 4
    { empty(); }
    // body, 5
    {
        __skip(lex, otk::StmtListOpen);
        parseListItemBody(lex);
        __skip(lex, otk::StmtListClose);
    }
    __skip(lex, otk::ListItemEnd);
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseNestedList(OrgLexer& lex) {
    __perf_trace("parseNestedList");
    __trace();
    ParseCb nextLevel = [this](OrgLexer& lex) {
        __skip(lex, otk::Indent);
        auto result = parseNestedList(lex);
        __skip(lex, otk::Dedent);
        return result;
    };

    __start(org::List);
    while (lex.at(otk::ListItemStart)) {
        parseListItem(lex);
        if (lex.at(otk::SameIndent)) {
            lex.next();
        } else if (lex.at(otk::Dedent)) {
            __end_return();
        } else if (lex.at(otk::Indent)) {
            nextLevel(lex);
        } else if (lex.at(otk::ListEnd)) {
            __end_return();
        } else {
            assert(false);
        }
    }
    __end();
    return back();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseList(OrgLexer& lex) {
    __perf_trace("parseList");
    __trace();
    __skip(lex, otk::ListStart);
    const auto nested = lex.at(otk::Indent);
    if (nested) {
        __skip(lex, otk::Indent);
    }
    auto result = parseNestedList(lex);
    if (nested) {
        __skip(lex, otk::Dedent);
    }
    __skip(lex, otk::ListEnd);
    return result;
}


template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseSubtreeLogbookClockEntry(
    OrgLexer& lex) {
    __perf_trace("parseSubtreeLogbookClockEntry");
    __trace();
    __start(org::LogbookClock);
    // CLOCK:
    __skip(lex, otk::ListClock);
    __skip(lex, otk::ParagraphStart);
    space(lex);
    __skip(lex, otk::BigIdent);
    __skip(lex, otk::Colon);
    space(lex);

    parseTimeRange(lex);

    space(lex);
    __skip(lex, otk::ParagraphEnd);
    newline(lex);
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseSubtreeLogbookListEntry(
    OrgLexer& lex) {
    __perf_trace("parseSubtreeLogbookListEntry");
    __trace();
    __start(org::LogbookEntry);
    using V = TokenWithValue;

    __skip(lex, otk::ListItemStart);
    skipSpace(lex);
    __skip(lex, otk::StmtListOpen);
    __skip(lex, otk::ParagraphStart);
    if (lex.at(otk::Word) && lex.strVal() == "State") {
        // - State "WIP" from "TODO" [2023-01-01 Sun 23:32:22]
        __start(org::LogbookStateChange);
        {

            __skip(lex, (V{otk::Word, "State"}));
            space(lex);
            __skip(lex, otk::QuoteOpen);
            token(org::BigIdent, pop(lex, otk::BigIdent));
            __skip(lex, otk::QuoteClose);
            space(lex);
            __skip(lex, (V{otk::Word, "from"}));
            space(lex);
            if (lex.at(otk::QuoteOpen)) {
                __skip(lex, otk::QuoteOpen);
                token(org::BigIdent, pop(lex, otk::BigIdent));
                __skip(lex, otk::QuoteClose);
            } else {
                empty();
            }

            space(lex);
            parseTimeStamp(lex);
        }
        __end();
    } else if (lex.at(otk::Word) && lex.strVal() == "Refiled") {
        __start(org::LogbookRefile);
        {
            __skip(lex, (V{otk::Word, "Refiled"}));
            space(lex);
            __skip(lex, (V{otk::Word, "on"}));
            space(lex);
            parseTimeStamp(lex);
            space(lex);
            __skip(lex, (V{otk::Word, "from"}));
            space(lex);
            parseLink(lex);
        }
        __end();
    } else if (lex.at(otk::Word) && lex.strVal() == "Note") {
        __start(org::LogbookNote);
        {
            __skip(lex, (V{otk::Word, "Note"}));
            space(lex);
            __skip(lex, (V{otk::Word, "taken"}));
            space(lex);
            __skip(lex, (V{otk::Word, "on"}));
            space(lex);
            parseTimeStamp(lex);
            space(lex);
        }
        __end();
    } else if (lex.at(otk::Word) && lex.strVal() == "Priority") {
        __start(org::LogbookPriority);
        {
            __skip(lex, (V{otk::Word, "Priority"}));
            space(lex);
            __skip(lex, otk::QuoteOpen);
            auto first = token(org::Word, pop(lex, lex.kind()));
            __token(first);
            __skip(lex, otk::QuoteClose);
            space(lex);
            auto str    = lex.strVal();
            auto change = token(
                org::LogbookPriorityChangeAction, pop(lex, otk::Word));
            __token(change);
            space(lex);

            if (str == "Removed") {
                empty();
                __skip(lex, V({otk::Word, "on"}));
            } else if (str == "Changed") {
                __skip(lex, V({otk::Word, "From"}));
                space(lex);
                __skip(lex, otk::QuoteOpen);
                auto second = token(org::Word, pop(lex, lex.kind()));
                __token(second);
                __skip(lex, otk::QuoteClose);
                space(lex);
                __skip(lex, V({otk::Word, "at"}));
            } else if (str == "Added") {
                empty();
                __skip(lex, V({otk::Word, "at"}));
            } else {
                throw wrapError(
                    Err::UnhandledToken(
                        lex, "Unexpected priority action " + str),
                    lex);
            }

            space(lex);
            parseTimeStamp(lex);
        }
        __end();
    } else if (lex.at(otk::Word) && lex.strVal() == "Rescheduled") {
        __start(org::LogbookReschedule);
        {
            __skip(lex, (V{otk::Word, "Rescheduled"}));
            space(lex);
            __skip(lex, (V{otk::Word, "from"}));
            space(lex);
            __skip(lex, otk::QuoteOpen);
            parseTimeStamp(lex);
            __skip(lex, otk::QuoteClose);
            space(lex);
            __skip(lex, (V{otk::Word, "on"}));
            space(lex);
            parseTimeStamp(lex);
            space(lex);
        }
        __end();
    } else if (lex.at(otk::Word) && lex.strVal() == "Tag") {
        __start(org::LogbookTagChange);
        {
            __skip(lex, (V{otk::Word, "Tag"}));
            space(lex);
            __skip(lex, otk::QuoteOpen);
            parseHashTag(lex);
            __skip(lex, otk::QuoteClose);
            space(lex);
            auto sub = token(
                org::LogbookTagChangeAction, pop(lex, otk::Word));
            __token(sub);
            space(lex);
            __skip(lex, (V{otk::Word, "on"}));
            space(lex);
            parseTimeStamp(lex);
            space(lex);
        }
        __end();
    }

    newline(lex);
    space(lex);
    if (lex.at(otk::DoubleSlash)) {
        __start(org::StmtList);
        __skip(lex, otk::DoubleSlash);
        __skip(lex, otk::Newline);

        Vec<OrgTokenId> firstParagraph;
        while (!lex.at(otk::ParagraphEnd)) {
            firstParagraph.push_back(lex.pop());
        }

        auto sub = SubLexer(lex.in, firstParagraph);

        __skip(lex, otk::ParagraphEnd);

        while (!lex.at(otk::StmtListClose)) {
            parseToplevelItem(lex);
        }

        __skip(lex, otk::StmtListClose);
        __skip(lex, otk::ListItemEnd);
        __end();

    } else {
        __skip(lex, otk::ParagraphEnd);
        __skip(lex, otk::StmtListClose);
        __skip(lex, otk::ListItemEnd);
        empty();
    }


    // TODO handle optional logbook entry description or note
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseSubtreeLogbook(OrgLexer& lex) {
    __perf_trace("parseSubtreeLogbook");
    __trace();
    __start(org::Logbook);
    __skip(lex, otk::ColonLogbook);
    newline(lex);
    __skip(lex, otk::GroupStart);
    __skip(lex, otk::LogbookStart);

    skipSpace(lex);
    while (lex.at(otk::ListStart) || lex.at(otk::ListClock)) {
        switch (lex.tok().kind) {
            case otk::ListStart: {
                __skip(lex, otk::ListStart);
                __skip(lex, otk::Indent);
                while (lex.at(otk::ListItemStart)) {
                    parseSubtreeLogbookListEntry(lex);
                    if (lex.at(otk::SameIndent)) {
                        lex.next();
                    }
                }
                __skip(lex, otk::Dedent);
                __skip(lex, otk::ListEnd);
                space(lex);
                break;
            }
            case otk::ListClock: {
                parseSubtreeLogbookClockEntry(lex);
                space(lex);
                break;
            }
            default: {
                throw wrapError(Err::UnhandledToken(lex), lex);
            }
        }
    }

    space(lex);
    __skip(lex, otk::LogbookEnd);
    __skip(lex, otk::ColonEnd);
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseSubtreeProperties(OrgLexer& lex) {
    __perf_trace("parseSubtreeProperties");
    __trace();
    __skip(lex, otk::ColonProperties);
    __skip(lex, otk::SkipNewline);
    __skip(lex, otk::GroupStart);
    __skip(lex, otk::SkipSpace);
    __start(org::PropertyList);
    while (lex.at(otk::ColonIdent) || lex.at(otk::Punctuation)) {
        __trace("Parse single subtree property");
        __start(org::Property);
        // Optional exclusion rule description
        if (lex.at(otk::Punctuation)) {
            auto sub = token(org::Punctuation, pop(lex, otk::Punctuation));
            __token(sub);
        } else {
            empty();
        }

        // First ident
        auto name = token(org::RawText, pop(lex, otk::ColonIdent));
        __token(name);

        // Set rule for main property specification
        if (lex.at(otk::Punctuation)) {
            auto sub = token(org::Punctuation, pop(lex, otk::Punctuation));
            __token(sub);
        } else {
            empty();
        }

        // Optional sub-ident for the property name, like
        // `:header-args:cpp:`
        if (lex.at(otk::ColonIdent)) {
            auto sub = token(org::Ident, pop(lex, otk::ColonIdent));
            __token(sub);
        } else {
            empty();
        }

        // Set rule for sub-property specification
        if (lex.at(otk::Punctuation)) {
            auto sub = token(org::Punctuation, pop(lex, otk::Punctuation));
            __token(sub);
        } else {
            empty();
        }

        __skip(lex, otk::SkipSpace);

        QString strName = normalize(group->strVal(name));

        if (strName == "created") {
            parseTimeStamp(lex);
        } else {
            token(org::RawText, pop(lex, otk::RawProperty));
        }


        __skip(lex, otk::SkipNewline);
        __skip(lex, otk::SkipSpace);
        __end();
    }
    __skip(lex, otk::ColonEnd);
    __skip(lex, otk::GroupEnd);
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseSubtreeDrawer(OrgLexer& lex) {
    __perf_trace("parseSubtreeDrawer");
    __trace();
    __skip(lex, otk::GroupStart);
    __skip(lex, otk::SkipSpace);
    __start(org::Drawer);

    while (lex.at(OrgTokSet{
        otk::ColonProperties, otk::ColonLogbook, otk::ColonDescription})) {
        switch (lex.tok().kind) {
            case otk::ColonProperties: parseSubtreeProperties(lex); break;
            case otk::ColonLogbook: parseSubtreeLogbook(lex); break;
            case otk::ColonDescription: {
                __skip(lex, otk::ColonDescription);
                __start(org::SubtreeDescription);
                newline(lex);
                {
                    parseParagraph(lex, false);
                    __skip(lex, otk::ColonEnd);
                }
                __end();
                break;
            }
            default: {
            }
        }

        newline(lex);
        space(lex);
    }

    __skip(lex, otk::GroupEnd);
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseSubtreeCompletion(OrgLexer& lex) {
    __perf_trace("parseSubtreeCompletion");
    __trace();
    if (lex.at(otk::SkipNewline) || lex.at(otk::SubtreeTagSeparator)
        || lex.at(otk::SubtreeEnd)) {
        return empty();

    } else {
        __start(org::Completion);
        qDebug() << "Parse subtree completion [" << lex << "]";
        __end_return();
    }
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseSubtreeTodo(OrgLexer& lex) {
    __perf_trace("parseSubtreeTodo");
    __trace();
    skipSpace(lex);
    if (lex.at(otk::SubtreeTodoState)) {
        auto tmp = token(org::BigIdent, pop(lex, otk::SubtreeTodoState));
        __token(tmp);
        return tmp;
    } else {
        return empty();
    }
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseSubtreeUrgency(OrgLexer& lex) {
    __perf_trace("parseSubtreeUrgency");
    __trace();
    skipSpace(lex);
    if (lex.at(otk::SubtreeUrgency)) {
        return token(org::SubtreeUrgency, pop(lex, otk::SubtreeUrgency));
    } else {
        return empty();
    }
}


template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseSubtreeTitle(OrgLexer& lex) {
    __perf_trace("parseSubtreeTitle");
    __trace();
    skipSpace(lex);
    return parseParagraph(lex, false);
}


template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseSubtreeTags(OrgLexer& lex) {
    __perf_trace("parseSubtreeTags");
    __trace();
    if (lex.at(otk::SubtreeTagSeparator)) {
        __start(org::InlineStmtList);
        while (lex.at(otk::SubtreeTagSeparator)
               && lex.at(otk::HashTag, +1)) {
            __skip(lex, otk::SubtreeTagSeparator);
            parseHashTag(lex);
        }
        __skip(lex, otk::SubtreeTagSeparator);
        __end_return();
    } else {
        return empty();
    }
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseSubtreeTimes(OrgLexer& lex) {
    __perf_trace("parseSubtreeTimes");
    __trace();
    __start(org::StmtList);
    if (lex.ahead(
            OrgTokSet{otk::SkipSpace, otk::GroupStart},
            OrgTokSet{otk::SubtreeTime})) {
        __skip(lex, otk::GroupStart);
        __skip(lex, otk::SkipSpace);

        while (lex.at(otk::SubtreeTime)) {
            __start(org::TimeAssoc);
            if (lex.at(otk::SubtreeTime)) {
                token(org::BigIdent, pop(lex, otk::SubtreeTime));
            } else {
                empty();
            }
            space(lex);
            parseTimeStamp(lex);
            space(lex);
            __end();
        }

        newline(lex);
        __skip(lex, otk::GroupEnd);
    } else {
        __print("No subtree time");
    }

    __end_return();
}


template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseSubtree(OrgLexer& lex) {
    __perf_trace("parseSubtree");
    __trace();
    __start(org::Subtree);
    // prefix

    token(org::RawText, pop(lex, otk::SubtreeStars)); // 0
    parseSubtreeTodo(lex);                            // 1
    parseSubtreeUrgency(lex);                         // 2
    parseSubtreeTitle(lex);                           // 3
    parseSubtreeCompletion(lex);                      // 4
    parseSubtreeTags(lex);                            // 5

    if (!lex.at(otk::SubtreeEnd)) { // 6
        __skip(lex, otk::SkipNewline);
        parseSubtreeTimes(lex);
        newline(lex);
    } else {
        empty();
    }

    if (!lex.at(otk::SubtreeEnd)) { // 7
        parseSubtreeDrawer(lex);
        newline(lex);
    } else {
        empty();
    }

    start(org::StmtList); // 8
    end();

    __skip(lex, otk::SubtreeEnd);
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseOrgFile(OrgLexer& lex) {
    __perf_trace("parseOrgFile");
    __trace();
    __start(org::File);
    if (lex.at(otk::QuoteOpen)) {
        lex.next();
        token(org::RawText, pop(lex, otk::RawText));
        __skip(lex, otk::QuoteClose);
    } else {
        token(org::RawText, pop(lex, otk::RawText));
    }
    __end_return();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseLineCommand(OrgLexer& lex) {
    __perf_trace("parseLineCommand");
    __trace();
    const auto kind = classifyCommand(lex.strVal(+1));
    switch (kind) {
        case ock::Include: {
            skipLineCommand(lex);
            __skip(lex, otk::CommandArgumentsBegin);
            __start(org::CommandInclude);
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
            __skip(lex, otk::CommandArgumentsEnd);
            break;
        }

        case ock::AttrHtml: {
            skipLineCommand(lex);
            __skip(lex, otk::CommandArgumentsBegin);
            __start(org::CommandAttrHtml);
            parseSrcArguments(lex);
            __skip(lex, otk::CommandArgumentsEnd);
            break;
        }

        case ock::Title: {
            skipLineCommand(lex);
            __start(org::CommandTitle);
            parseParagraph(lex, false);
            break;
        }

        case ock::Caption: {
            skipLineCommand(lex);
            __start(org::CommandCaption);
            __start(org::CommandArguments);
            parseParagraph(lex, false);
            __end();
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
                default: {
                }
            }

            __start(newk);
            {
                skipLineCommand(lex);
                __skip(lex, otk::CommandArgumentsBegin);
                while (lex.at(otk::RawText)) {
                    token(org::RawText, pop(lex, otk::RawText));
                    if (lex.at(otk::SkipSpace)) {
                        skipSpace(lex);
                    }
                }
                __skip(lex, otk::CommandArgumentsEnd);
            }

            break;
        }

        case ock::Filetags: {
            skipLineCommand(lex);
            __start(org::Filetags);
            while (lex.at(otk::SubtreeTagSeparator)
                   && lex.at(otk::HashTag, +1)) {
                parseHashTag(lex);
            }
            __skip(lex, otk::SubtreeTagSeparator);
            break;
        }

        case ock::HtmlHead: {
            skipLineCommand(lex);
            __skip(lex, otk::CommandArgumentsBegin);
            __start(org::HtmlHead);
            token(org::RawText, pop(lex, otk::RawText));
            __skip(lex, otk::CommandArgumentsEnd);
            break;
        }

        case ock::LatexClassOptions: {
            skipLineCommand(lex);
            __skip(lex, otk::CommandArgumentsBegin);
            __start(org::LatexClassOptions);
            token(org::RawText, pop(lex, otk::RawText));
            __skip(lex, otk::CommandArgumentsEnd);
            break;
        }

        case ock::LatexClass:
        case ock::LatexCompiler: {
            OrgNodeKind newk = org::Empty;
            switch (kind) {
                case ock::LatexCompiler: newk = org::LatexCompiler; break;
                case ock::LatexClass: newk = org::LatexClass; break;
                default: {
                }
            }
            skipLineCommand(lex);
            __skip(lex, otk::CommandArgumentsBegin);
            __start(newk);
            token(org::Ident, pop(lex, otk::Ident));
            __skip(lex, otk::CommandArgumentsEnd);
            break;
        }


        case ock::Property: {
            skipLineCommand(lex);
            __start(org::Property);
            token(org::RawText, pop(lex, otk::Ident));
            empty();
            token(org::RawText, pop(lex, otk::RawProperty));
            break;
        }

        case ock::TableFormula: {
            skipLineCommand(lex);
            __start(org::CommandTblfm);
            __skip(lex, otk::CommandArgumentsBegin);
            token(org::RawText, pop(lex, otk::RawText));
            __skip(lex, otk::CommandArgumentsEnd);
            break;
        }

        default: {
            throw wrapError(
                Err::UnhandledToken(lex, to_string(kind)), lex);
        }
    }

    // Placeholder statement list that might be extended in a latter pass
    __start(org::StmtList);
    __end();
    // End main tree that was started in the case statement
    __end();


    return back();
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseToplevelItem(OrgLexer& lex) {
    __perf_trace("parseToplevelItem");
    __trace();
    switch (lex.kind()) {
        case otk::ParagraphStart: return parseParagraph(lex, true);
        case otk::TableBegin: return parseTable(lex);
        case otk::SubtreeStars: return parseSubtree(lex);
        case otk::ListStart: return parseList(lex);
        case otk::SkipAny:
            return token(org::SkipAny, pop(lex, otk::SkipAny));
        case otk::SkipSpace:
            return token(org::SkipSpace, pop(lex, otk::SkipSpace));
        case otk::SkipNewline:
            return token(org::SkipNewline, pop(lex, otk::SkipNewline));
        case otk::TextSeparator:
            return token(org::TextSeparator, pop(lex, otk::TextSeparator));

        case otk::CommandPrefix: {
            const auto kind = classifyCommand(lex.strVal(1));
            switch (kind) {
                case ock::BeginSrc: return parseSrc(lex);
                case ock::BeginExample: return parseExample(lex);
                case ock::BeginExport: return parseBlockExport(lex);
                case ock::BeginQuote:
                case ock::BeginCenter:
                case ock::BeginAdmonition:
                    return parseTextWrapCommand(lex, kind);

                default: return parseLineCommand(lex);
            }
            break;
        }
        default: {
            throw wrapError(Err::UnhandledToken(lex), lex);
        }
    }
}

template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseTop(OrgLexer& lex) {
    __perf_trace("parseTop");
    __trace();
    __start(org::StmtList);
    while (lex.hasNext()) {
        if (lex.at(otk::Comment)) {
            lex.next();
        } else {
            parseToplevelItem(lex);
        };
    }
    __end_return();
}


template <bool TraceState>
OrgId OrgParserImpl<TraceState>::parseFull(OrgLexer& lex) {
    __perf_trace("parseFull");
    __trace();
    auto id = parseTop(lex);
    extendSubtreeTrails(OrgId(0));
    extendAttachedTrails(OrgId(0));
    return id;
}


} // namespace

SPtr<OrgParser> OrgParser::initImpl(OrgNodeGroup* group, bool doTrace) {
    if (doTrace) {
        return SPtr<OrgParserImpl<true>>(new OrgParserImpl<true>(group));
    } else {
        return SPtr<OrgParserImpl<false>>(new OrgParserImpl<false>(group));
    }
}


void assertValidStructure(OrgNodeGroup* group, OrgId id) {
    using Id = OrgNodeGroup::Id;

    Func<void(Id)> aux;
    aux = [&](Id top) {
        auto& g = *group;
        Q_ASSERT(g.nodes.contains(top));
        if (g.at(top).isTerminal() || g.at(top).isMono()) {
            return;
        }

        Q_ASSERT(g.at(top).kind != org::Empty);

        Id start = top + 1;
        Id id    = start;

        if (Opt<Slice<Id>> extentOpt = g.allSubnodesOf(top)) {
            Slice<Id> extent = extentOpt.value();
            Q_ASSERT(g.nodes.contains(extent.first));
            Q_ASSERT(g.nodes.contains(extent.last));

            int index = 0;
            while (extent.contains(id)) {
                Q_ASSERT(g.nodes.contains(id));
                aux(id);

                id = id + g.at(id).getExtent();
                Q_ASSERT_X(
                    g.nodes.contains(id),
                    "next subnode",
                    "Step over the subnode of $# with extent $# yielded "
                    "id $# which is outsize of the group range (index is "
                    "$#, group size is $#), subnode index is $#, size "
                    "overflow is $#"
                        % to_string_vec(
                            start.getUnmasked(),
                            extent,
                            id.getUnmasked(),
                            id.getIndex(),
                            g.size(),
                            index,
                            id - g.nodes.back()));


                id = id + 1;
                ++index;
            }

            Q_ASSERT_X(
                extent.last + 1 == id,
                "range end",
                "Iteration over subnode ranges for $# did not end at the "
                "$# -- combined subnode extent strides summed up to $#. "
                "Total subnode count is $#, full extent is $#"
                    % to_string_vec(
                        top.getUnmasked(),
                        (extent.last + 1).getUnmasked(),
                        id.getUnmasked(),
                        index,
                        extent));
        }
    };

    aux(id);
}


template <bool TraceState>
void OrgParserImpl<TraceState>::extendSubtreeTrails(OrgId position) {
    __perf_trace("extendSubtreeTrails");
    Func<OrgId(OrgId, int)> aux;
    aux = [&](OrgId id, int level) -> OrgId {
        OrgId const start = id;
        // Iterate over all nodes until the end of the group or until exit
        // condition is met. This assumes non-restructured tree that has
        // subnodes positioned flatlyl on the top level
        auto& g = *group;
        while (id <= g.nodes.back()) {
            // NOTE: 'back' returns the last node, not one-past-last
            OrgNode node = g.at(id);
            if (node.kind == org::Subtree) {
                __print(
                    "Found subtree on the lower level " + to_string(id),
                    nullptr);
                OrgId const tree  = id;
                OrgId       subId = g.subnode(tree, 0);
                int         sub   = g.strVal(subId).size();
                if (level < sub) {
                    OrgId stmt = g.subnode(tree, 8);
                    Q_ASSERT(g.at(stmt).kind == org::StmtList);
                    id = aux(stmt + 1, sub);
                    Q_ASSERT(stmt + 1 <= id);
                    // AUX returns next position to start looping from, so
                    // the tree size is 'end - start - 1' to account for
                    // the offset.

                    // Extend the tree itself and nested statement list
                    g.at(stmt).extend((id - stmt) - 1);

                    g.at(tree).extend((id - tree) - 1);

                    auto treeSlice = g.allSubnodesOf(tree).value();
                    auto stmtSlice = g.allSubnodesOf(tree).value();

                    // Structural correctness checks -- mostly for
                    // debugging of the implementation, malformed incoming
                    // data is not expected.
                    assertValidStructure(group, tree);
                    Q_ASSERT(treeSlice.last <= g.nodes.back());
                    Q_ASSERT(stmtSlice.last <= g.nodes.back());
                    Q_ASSERT_X(
                        treeSlice.last == stmtSlice.last,
                        "extend tree",
                        "$# -- $#" % to_string_vec(treeSlice, stmtSlice));
                    Q_ASSERT_X(
                        treeSlice.contains(stmtSlice),
                        "statement containment",
                        "$# -- $#" % to_string_vec(treeSlice, stmtSlice));


                } else {
                    __print(
                        "Found subtree on the same level or above "
                            + to_string(id),
                        nullptr);
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
    };

    aux(position, 0);
    assertValidStructure(group, position);
}


template <bool TraceState>
void OrgParserImpl<TraceState>::extendAttachedTrails(OrgId position) {
    __perf_trace("extendAttachedTrails");
    Func<OrgId(OrgId)> aux;
    aux = [&](OrgId id) -> OrgId {
        auto& g = *group;

        OrgNode node = g.at(id);
        if (OrgAttachableCommands.contains(node.kind)) {
            OrgId const annotation = id;
            // Get ID of the nested statement list
            OrgId const stmt = g.subnode(annotation, 1);
            Q_ASSERT(g.at(stmt).kind == org::StmtList);
            // Next element after command block is the non-optional newline
            // to separate them.
            Q_ASSERT(g.at(stmt + 1).kind == org::SkipNewline);
            OrgId   nextId = stmt + 2;
            OrgNode next   = g.at(nextId);

            // qDebug() << "Next element from" << annotation << "has kind"
            //          << next.kind << "at" << nextId;

            if (OrgAttachableCommands.contains(next.kind)) {
                // Nested annotations are recursively placed inside
                // each other by extending the trail
                id = aux(nextId);
                g.at(annotation).extend((id - annotation) - 1);
                g.at(stmt).extend((id - stmt) - 1);

            } else if (OrgTrailableCommands.contains(next.kind)) {
                // Element that can be put as the final part of the
                // trailable statement
                if (auto nextSub = g.allSubnodesOf(nextId)) {
                    OrgId const end = nextSub->last;
                    g.at(annotation).extend(end - annotation);
                    g.at(stmt).extend(end - stmt);
                    id = end + 1;
                } else {
                    qWarning()
                        << "No subnodes found in the next node" << nextId;
                    ++id;
                }

            } else {
                // Next element after line command is neither trailable
                // nor another command. Switching the subnode kind to
                // empty.
                g.at(stmt) = getEmpty();
                ++id;
            }
        } else {
            ++id;
        }

        return id;
    };

    while (position < group->nodes.back()) {
        position = aux(position);
    }
}

template <bool TraceState>
void OrgParserImpl<TraceState>::report(CR<Report> in) {
    using fg = TermColorFg8Bit;

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

    if (in.kind == ReportKind::EnterParse
        || in.kind == ReportKind::StartNode) {
        ++depth;
    }

    ColStream os = getStream();
    os << repeat("  ", depth);

    auto printTokens = [&]() {
        if (in.lex != nullptr) {
            os << " [";
            OrgLexer::PrintParams params;
            in.lex->print(os, params);
            os << "]";
        }
    };

    auto getLoc = [&]() -> QString {
        QString res;
        if (in.lex != nullptr) {
            Opt<LineCol> loc = this->getLoc(*in.lex);
            if (loc.has_value()) {
                res = "$#:$# " % to_string_vec(loc->line, loc->column);
            }
        }
        return res;
    };

    if (treeDepth() < 0) {
        qFatal("Negative tree depth");
    }

    switch (in.kind) {
        case ReportKind::Error: {
            os << "  "
               << "error";
            break;
        }

        case ReportKind::Print: {
            os << "  " << in.line << getLoc() << ":" << in.subname.value();
            printTokens();
            break;
        }

        case ReportKind::AddToken: {
            auto id = in.node.value();
            os << "  # add [" << id.getIndex() << "] "
               << to_string(group->at(id).kind) << " at " << in.line
               << " with " << escape_literal(group->strVal(id));
            break;
        }

        case ReportKind::StartNode:
        case ReportKind::EndNode: {
            auto id = in.node.value();
            if (in.kind == ReportKind::StartNode) {
                os << "+ started node, level is " << treeDepth();
            } else {
                os << "- ended node, level is " << treeDepth();
            }

            os << " [" << id.getIndex() << "] "
               << to_string(group->at(id).kind) << " at " << in.line;
            if (in.kind == ReportKind::EndNode) {
                os << " ext=" << group->at(id).getExtent();
            }
            break;
        }

        case ReportKind::EnterParse:
        case ReportKind::LeaveParse: {
            os << (in.kind == ReportKind::EnterParse ? "> " : "< ") //
               << "~" << treeDepth() << " "                         //
               << fg::Green << in.name.value() << os.end() << ":"
               << fg::Cyan << in.line << os.end();

            if (in.subname.has_value()) {
                os << " <@" << in.subname.value() << ">";
            }

            printTokens();

            break;
        }
    }

    endStream(os);

    if (in.kind == ReportKind::LeaveParse
        || in.kind == ReportKind::EndNode) {
        --depth;
    }

    if (traceUpdateHook) {
        traceUpdateHook(in, trace, false);
    }
}
