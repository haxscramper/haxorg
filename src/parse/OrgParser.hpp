#pragma once

#include <parse/OrgTypes.hpp>
#include <parse/OrgTokenizer.hpp>
#include <hstd/stdlib/sequtils.hpp>
#include <hstd/stdlib/Ptrs.hpp>

#include <lexbase/TraceBase.hpp>

using ParseCb = std::function<OrgId(OrgLexer&)>;

struct OrgParser : public OperationsTracer {
  public:
    bool TraceState = false;

    using OrgExpectable = Variant<
        OrgTokenKind,
        OrgTokSet,
        Vec<OrgTokenKind>>;

    std::string       getLocMsg(CR<OrgLexer> lex);
    [[noreturn]] void fatalError(
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
        Print
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
    OrgId parseRawUrl(OrgLexer& lex);
    OrgId parseLink(OrgLexer& lex);
    OrgId parseInlineMath(OrgLexer& lex);
    OrgId parseSymbol(OrgLexer& lex);
    OrgId parseHashTag(OrgLexer& lex);
    OrgId parseTimeRange(OrgLexer& lex);
    OrgId parseTimeStamp(OrgLexer& lex);
    OrgId parseIdent(OrgLexer& lex);
    OrgId parseSrcInline(OrgLexer& lex);
    OrgId parseTable(OrgLexer& lex);
    OrgId parsePlaceholder(OrgLexer& lex);
    OrgId parseTopParagraph(OrgLexer& lex);
    OrgId parseInlineParagraph(OrgLexer& lex);
    OrgId parseCommandArguments(OrgLexer& lex);
    OrgId parseSrcArguments(OrgLexer& lex);
    OrgId parseSrc(OrgLexer& lex);
    OrgId parseExample(OrgLexer& lex);
    OrgId parseListItem(OrgLexer& lex);
    OrgId parseTarget(OrgLexer& lex);
    OrgId parseList(OrgLexer& lex);
    OrgId parseLatex(OrgLexer& lex);
    OrgId parseBlockExport(OrgLexer& lex);
    OrgId parseParagraph(OrgLexer& lex);

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
    void  extendAttachedTrails(OrgId position);
    void  parseCSVArguments(OrgLexer& lex);


  protected:
    CR<OrgNode> pending() const {
        CHECK(0 <= group->treeDepth());
        return group->lastPending();
    }

    OrgId fail(OrgTokenId invalid) {
        (void)token(OrgNodeKind::ErrorToken, invalid);
        /// TODO insert token with error description
        (void)token(OrgNodeKind::ErrorTerminator, OrgTokenId::Nil());
        OrgId failed           = end();
        group->at(failed).kind = OrgNodeKind::Error;
        return failed;
    }

    OrgId back() const { return group->nodes.back(); }

    int treeDepth() const {
        CHECK(0 <= group->treeDepth());
        return group->treeDepth();
    }


    OrgId   empty() { return token(getEmpty()); }
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

    OrgId end(
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    OrgId fake(
        OrgNodeKind kind,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

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

    finally trace(
        OrgLexer&        lex,
        Opt<std::string> msg      = std::nullopt,
        int              line     = __builtin_LINE(),
        char const*      function = __builtin_FUNCTION());

    void print(
        std::string const& msg,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        OrgLexer*          lexer    = nullptr);


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
