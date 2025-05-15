#pragma once

#include <haxorg/parse/OrgTypes.hpp>
#include <haxorg/parse/OrgTokenizer.hpp>
#include <hstd/stdlib/sequtils.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/Exception.hpp>

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

    OrgId parseFootnote(OrgLexer& lex);
    OrgId parseMacro(OrgLexer& lex);
    OrgId parseCallArguments(OrgLexer& lex);
    OrgId parseAttrValue(OrgLexer& lex);
    OrgId parseAttrLisp(OrgLexer& lex);
    OrgId parseLink(OrgLexer& lex);
    OrgId parseInlineMath(OrgLexer& lex);
    OrgId parseSymbol(OrgLexer& lex);
    OrgId parseHashTag(OrgLexer& lex);
    OrgId parseTimeRange(OrgLexer& lex);
    OrgId parseTimeStamp(OrgLexer& lex);
    OrgId parseSrcInline(OrgLexer& lex);
    OrgId parseVerbatimOrMonospace(OrgLexer& lex);
    OrgId parseAngleTarget(OrgLexer& lex);
    OrgId parseTable(OrgLexer& lex);
    OrgId parsePlaceholder(OrgLexer& lex);
    OrgId parseCommandArguments(OrgLexer& lex);
    OrgId parseSrcArguments(OrgLexer& lex);
    OrgId parseSrc(OrgLexer& lex);
    OrgId parseExample(OrgLexer& lex);
    OrgId parseColonExample(OrgLexer& lex);
    OrgId parseListItem(OrgLexer& lex);
    OrgId parseList(OrgLexer& lex);
    OrgId parseLatex(OrgLexer& lex);
    OrgId parseBlockExport(OrgLexer& lex);
    OrgId parseParagraph(OrgLexer& lex);
    OrgId parseInlineExport(OrgLexer& lex);
    OrgId parseCriticMarkup(OrgLexer& lex);

    OrgId parseSubtree(OrgLexer& lex);
    OrgId parseSubtreeTodo(OrgLexer& lex);
    OrgId parseSubtreeUrgency(OrgLexer& lex);
    OrgId parseSubtreeDrawer(OrgLexer& lex);
    OrgId parseSubtreeCompletion(OrgLexer& lex);
    OrgId parseSubtreeTags(OrgLexer& lex);
    OrgId parseSubtreeTitle(OrgLexer& lex);
    OrgId parseSubtreeTimes(OrgLexer& lex);

    OrgId parseSubtreeLogbook(OrgLexer& lex);
    OrgId parseSubtreeProperties(OrgLexer& lex);

    OrgId parseOrgFile(OrgLexer& lex);
    OrgId parseLineCommand(OrgLexer& lex);
    OrgId parseStmtListItem(OrgLexer& lex);
    OrgId parseTop(OrgLexer& lex);

    OrgId parseFull(OrgLexer& lex);
    OrgId parseTextWrapCommand(OrgLexer& lex);
    void  extendSubtreeTrails(OrgId position);
    void  parseCSVArguments(OrgLexer& lex);

    OrgId subParseImpl(
        OrgId (OrgParser::*func)(OrgLexer&),
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

    OrgId token(
        OrgNode const& node,
        int            line     = __builtin_LINE(),
        char const*    function = __builtin_FUNCTION());

    OrgId token(
        OrgNodeKind kind,
        OrgTokenId  tok,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());


    OrgId start(
        OrgNodeKind kind,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    OrgId error_token(
        std::string const& message,
        OrgLexer&          lex,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION());

    OrgId end(
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    OrgId fake(
        OrgNodeKind kind,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    void fail(
        OrgLexer const& lex,
        OrgNode const&  replace,
        int             line     = __builtin_LINE(),
        char const*     function = __builtin_FUNCTION());

    void expect(
        OrgLexer const&                 lex,
        OrgParser::OrgExpectable const& item,
        int                             line     = __builtin_LINE(),
        char const*                     function = __builtin_FUNCTION());

    OrgTokenId pop(
        OrgLexer&                           lex,
        hstd::Opt<OrgParser::OrgExpectable> tok  = std::nullopt,
        int                                 line = __builtin_LINE(),
        char const* function                     = __builtin_FUNCTION());

    void skip(
        OrgLexer&                           lex,
        hstd::Opt<OrgParser::OrgExpectable> item = std::nullopt,
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
