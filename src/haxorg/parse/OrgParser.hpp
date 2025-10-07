#pragma once

#include <haxorg/parse/OrgTypes.hpp>
#include <haxorg/parse/OrgTokenizer.hpp>
#include <hstd/stdlib/sequtils.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/Exception.hpp>
#include <hstd/stdlib/Outcome.hpp>

#include <hstd/stdlib/TraceBase.hpp>

namespace org::parse {

struct parse_error : hstd::CRTP_hexception<parse_error> {};

using ParseCb = std::function<OrgId(OrgLexer&)>;

struct OrgParser : public hstd::OperationsTracer {
  public:
    using OrgExpectable = hstd::
        Variant<OrgTokenKind, OrgTokSet, hstd::Vec<OrgTokenKind>>;

    std::string getLocMsg(OrgLexer const& lex);
    parse_error fatalError(
        const OrgLexer&  lex,
        hstd::Str const& msg,
        int              line     = __builtin_LINE(),
        char const*      function = __builtin_FUNCTION());

  public:
    enum class ReportKind
    {
        EnterParse,
        LeaveParse,
        StartNode,
        EndNode,
        AddToken,
        Error,
        Print,
        FailTree,
    };

    struct Report : hstd::OperationsMsg {
        ReportKind       kind;
        hstd::Opt<OrgId> node = OrgId::Nil();
        OrgLexer const*  lex  = nullptr;
    };


  public:
    OrgParser() {}

    struct ParseFail {};
    struct ParseOk {
        hstd::Opt<OrgId> result;
        DESC_FIELDS(ParseOk, (result));
    };

    using MaybeTokenFail = hstd::Result<bool, OrgNodeMono::Error>;
    using ParseResult    = hstd::Result<ParseOk, ParseFail>;
    using LexResult      = hstd::Result<OrgTokenId, ParseFail>;

    ParseResult parseFootnote(OrgLexer& lex);
    ParseResult parseMacro(OrgLexer& lex);
    ParseResult parseCallArguments(OrgLexer& lex);
    ParseResult parseAttrValue(OrgLexer& lex);
    ParseResult parseAttrLisp(OrgLexer& lex);
    ParseResult parseLink(OrgLexer& lex);
    ParseResult parseInlineMath(OrgLexer& lex);
    ParseResult parseSymbol(OrgLexer& lex);
    ParseResult parseHashTag(OrgLexer& lex);
    ParseResult parseTimeRange(OrgLexer& lex);
    ParseResult parseTimeStamp(OrgLexer& lex);
    ParseResult parseSrcInline(OrgLexer& lex);
    ParseResult parseVerbatimOrMonospace(OrgLexer& lex);
    ParseResult parseAngleTarget(OrgLexer& lex);
    ParseResult parseTable(OrgLexer& lex);
    ParseResult parsePlaceholder(OrgLexer& lex);
    ParseResult parseCommandArguments(OrgLexer& lex);
    ParseResult parseSrcArguments(OrgLexer& lex);
    ParseResult parseSrc(OrgLexer& lex);
    ParseResult parseExample(OrgLexer& lex);
    ParseResult parseColonExample(OrgLexer& lex);
    ParseResult parseListItem(OrgLexer& lex);
    ParseResult parseList(OrgLexer& lex);
    ParseResult parseLatex(OrgLexer& lex);
    ParseResult parseBlockExport(OrgLexer& lex);
    ParseResult parseParagraph(OrgLexer& lex);
    ParseResult parseInlineExport(OrgLexer& lex);
    ParseResult parseCriticMarkup(OrgLexer& lex);

    ParseResult parseSubtree(OrgLexer& lex);
    ParseResult parseSubtreeTodo(OrgLexer& lex);
    ParseResult parseSubtreeUrgency(OrgLexer& lex);
    ParseResult parseSubtreeDrawer(OrgLexer& lex);
    ParseResult parseSubtreeCompletion(OrgLexer& lex);
    ParseResult parseSubtreeTags(OrgLexer& lex);
    ParseResult parseSubtreeTitle(OrgLexer& lex);
    ParseResult parseSubtreeTimes(OrgLexer& lex);

    ParseResult parseSubtreeLogbook(OrgLexer& lex);
    ParseResult parseSubtreeProperties(OrgLexer& lex);

    ParseResult parseOrgFile(OrgLexer& lex);
    ParseResult parseLineCommand(OrgLexer& lex);
    ParseResult parseStmtListItem(OrgLexer& lex);
    ParseResult parseTop(OrgLexer& lex);

    ParseResult parseTextWrapCommand(OrgLexer& lex);
    ParseResult parseCSVArguments(OrgLexer& lex);
    void        extendSubtreeTrails(OrgId position);

    OrgId parseFull(OrgLexer& lex);

    ParseResult subParseImpl(
        ParseResult (OrgParser::*func)(OrgLexer&),
        OrgLexer&   lex,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

  public:
    OrgNode const& pending() const {
        LOGIC_ASSERTION_CHECK(0 <= group->treeDepth(), "");
        return group->lastPending();
    }

    OrgId back() const { return group->nodes.back(); }

    int treeDepth() const {
        LOGIC_ASSERTION_CHECK(0 <= group->treeDepth(), "");
        return group->treeDepth();
    }


    OrgId empty(
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        return token(getEmpty(), line, function);
    }

    OrgNode getEmpty() { return OrgNode::Mono(OrgNodeKind::Empty); }

    bool at(OrgLexer const& lex, OrgParser::OrgExpectable const& item);

    std::string printLexerToString(OrgLexer& lex) const {
        return lex.printToString(
            [](hstd::ColStream& os, OrgToken const& t) {
                os << os.yellow() << escape_for_write(t.value.text)
                   << os.end() << hstd::fmt1(t.value);
            });
    }

    OrgId token(
        OrgNode const& node,
        int            line     = __builtin_LINE(),
        char const*    function = __builtin_FUNCTION());

    OrgId token(
        OrgNodeKind kind,
        OrgTokenId  tok,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    struct NodeGuard {
        int        startingDepth;
        OrgParser* parser;
        OrgId      startId = OrgId::Nil();

        OrgParser::ParseOk end() {
            auto result = parser->end_impl();
            LOGIC_ASSERTION_CHECK(
                parser->treeDepth() == startingDepth,
                "{} != {}",
                startingDepth,
                parser->treeDepth());

            return OrgParser::ParseOk{result};
        }
    };


    [[nodiscard]] NodeGuard start(
        OrgNodeKind kind,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    OrgId end_impl(
        std::string const& desc     = "",
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION());

    OrgNodeMono::Error error_value(
        std::string const& message,
        const OrgLexer&    lex,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION());

    ParseResult error_end(
        std::string const& message,
        const OrgLexer&    lex,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION()) {
        return error_end(
            error_value(message, lex, line, function), line, function);
    }

    OrgId error_token(
        OrgNodeMono::Error const& err,
        int                       line     = __builtin_LINE(),
        char const*               function = __builtin_FUNCTION());

    ParseResult error_end(
        OrgNodeMono::Error const& err,
        int                       line     = __builtin_LINE(),
        char const*               function = __builtin_FUNCTION());

    ParseResult maybe_error_end(
        MaybeTokenFail const& err,
        int                   line     = __builtin_LINE(),
        char const*           function = __builtin_FUNCTION());

    ParseResult maybe_recursive_error_end(
        ParseResult const& res,
        std::string const& on_fail_message,
        OrgLexer&          lex,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION());


    OrgId fake(
        OrgNodeKind kind,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    void fail(
        OrgLexer const& lex,
        OrgNode const&  replace,
        int             line     = __builtin_LINE(),
        char const*     function = __builtin_FUNCTION());

    [[nodiscard]] ParseResult expect(
        OrgLexer const&                 lex,
        OrgParser::OrgExpectable const& item,
        int                             line     = __builtin_LINE(),
        char const*                     function = __builtin_FUNCTION());

    OrgTokenId pop(
        OrgLexer&   lex,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        return pop(lex, std::nullopt, line, function).assume_value();
    }

    [[nodiscard]] LexResult pop(
        OrgLexer&                           lex,
        hstd::Opt<OrgParser::OrgExpectable> tok,
        int                                 line = __builtin_LINE(),
        char const* function                     = __builtin_FUNCTION());

    void skip(
        OrgLexer&   lex,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        std::ignore = skip(lex, std::nullopt, line, function);
    }

    [[nodiscard]] ParseResult skip(
        OrgLexer&                           lex,
        hstd::Opt<OrgParser::OrgExpectable> item,
        int                                 line = __builtin_LINE(),
        char const* function                     = __builtin_FUNCTION());

    void space(
        OrgLexer&   lex,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    void newline(
        OrgLexer&   lex,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    hstd::finally_std trace(
        OrgLexer&              lex,
        hstd::Opt<std::string> msg      = std::nullopt,
        int                    line     = __builtin_LINE(),
        char const*            function = __builtin_FUNCTION());

    void print(
        std::string const& msg,
        OrgLexer*          lexer    = nullptr,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION());


  public:
    void report(Report const& in);

    hstd::Func<void(Report const&)> reportHook;
    OrgNodeGroup*                   group = nullptr;
    OrgParser(OrgNodeGroup* _group) : group(_group) {}

    void reserve(int size) { group->nodes.reserve(size); }

    void setReportHook(hstd::Func<void(Report const&)> in) {
        reportHook = in;
    }

    static hstd::Opt<LineCol> getLoc(OrgLexer const& lex);

    hstd::Slice<OrgId> parseText(OrgLexer& lex);

    /// First pass of the text processing pass. Fold all known text
    /// structures into larger nodes, convert opening markup tokens into
    /// `XOpen` and `XClose` nodes.
    void textFold(OrgLexer& lex);

    /// Recursively fold text block in the specified range, updating nested
    /// markup nodes and converting `XOpen/XClose` elements to `X/Empty`
    /// nodes as needed.
    void parseTextRecursiveFold(hstd::Slice<OrgId> range);
};

} // namespace org::parse
