#pragma once

#include <haxorg/parse/OrgTypes.hpp>
#include <haxorg/parse/OrgTokenizer.hpp>
#include <hstd/stdlib/sequtils.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/Exception.hpp>

#include <hstd/stdlib/TraceBase.hpp>

struct parse_error : CRTP_hexception<parse_error> {};

using ParseCb = std::function<OrgId(OrgLexer&)>;

struct OrgParser : public OperationsTracer {
  public:
    using OrgExpectable = Variant<
        OrgTokenKind,
        OrgTokSet,
        Vec<OrgTokenKind>>;

    std::string getLocMsg(CR<OrgLexer> lex);
    parse_error fatalError(
        const OrgLexer& lex,
        CR<Str>         msg,
        int             line     = __builtin_LINE(),
        char const*     function = __builtin_FUNCTION());

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

    struct Report : OperationsMsg {
        ReportKind      kind;
        Opt<OrgId>      node = OrgId::Nil();
        OrgLexer const* lex  = nullptr;
    };


  public:
    OrgParser() {}

    OrgId parseFootnote(OrgLexer& lex);
    OrgId parseMacro(OrgLexer& lex);
    void  parseCallArguments(OrgLexer& lex);
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
    CR<OrgNode> pending() const {
        CHECK(0 <= group->treeDepth());
        return group->lastPending();
    }

    OrgId back() const { return group->nodes.back(); }

    int treeDepth() const {
        CHECK(0 <= group->treeDepth());
        return group->treeDepth();
    }


    OrgId empty(
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION()) {
        return token(getEmpty(), line, function);
    }

    OrgNode getEmpty() { return OrgNode::Mono(OrgNodeKind::Empty); }

    bool at(CR<OrgLexer> lex, CR<OrgParser::OrgExpectable> item);

    OrgId token(
        CR<OrgNode> node,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

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
        CR<OrgLexer> lex,
        CR<OrgNode>  replace,
        int          line     = __builtin_LINE(),
        char const*  function = __builtin_FUNCTION());

    void expect(
        CR<OrgLexer>                 lex,
        CR<OrgParser::OrgExpectable> item,
        int                          line     = __builtin_LINE(),
        char const*                  function = __builtin_FUNCTION());

    OrgTokenId pop(
        OrgLexer&                     lex,
        Opt<OrgParser::OrgExpectable> tok      = std::nullopt,
        int                           line     = __builtin_LINE(),
        char const*                   function = __builtin_FUNCTION());

    void skip(
        OrgLexer&                     lex,
        Opt<OrgParser::OrgExpectable> item     = std::nullopt,
        int                           line     = __builtin_LINE(),
        char const*                   function = __builtin_FUNCTION());

    void space(
        OrgLexer&   lex,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    void newline(
        OrgLexer&   lex,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    finally_std trace(
        OrgLexer&        lex,
        Opt<std::string> msg      = std::nullopt,
        int              line     = __builtin_LINE(),
        char const*      function = __builtin_FUNCTION());

    void print(
        std::string const& msg,
        OrgLexer*          lexer    = nullptr,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION());


  public:
    int  depth = 0;
    void report(CR<Report> in);

    Func<void(CR<Report>)> reportHook;
    OrgNodeGroup*          group = nullptr;
    OrgParser(OrgNodeGroup* _group) : group(_group) {}

    void reserve(int size) { group->nodes.reserve(size); }

    void setReportHook(Func<void(CR<Report>)> in) { reportHook = in; }

    static Opt<LineCol> getLoc(CR<OrgLexer> lex);

    Slice<OrgId> parseText(OrgLexer& lex);

    /// First pass of the text processing pass. Fold all known text
    /// structures into larger nodes, convert opening markup tokens into
    /// `XOpen` and `XClose` nodes.
    void textFold(OrgLexer& lex);

    /// Recursively fold text block in the specified range, updating nested
    /// markup nodes and converting `XOpen/XClose` elements to `X/Empty`
    /// nodes as needed.
    void parseTextRecursiveFold(Slice<OrgId> range);
};
