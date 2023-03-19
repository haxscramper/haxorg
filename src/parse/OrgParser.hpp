#pragma once

#include <parse/OrgTypes.hpp>
#include <parse/OrgTokenizer.hpp>
#include <hstd/stdlib/sequtils.hpp>

#include <lexbase/TraceBase.hpp>

using ParseCb = std::function<OrgId(OrgLexer&)>;

struct OrgParser : public OperationsTracer {
  public:
    enum class ReportKind
    {
        EnterParse,
        LeaveParse,
        StartNode,
        EndNode,
        AddToken
    };

    struct Report {
        ReportKind kind;
        fs::path   location;
        int        line;
        Opt<Str>   name;
        Opt<Str>   subname;
        Opt<OrgId> node;
        OrgLexer*  lex = nullptr;
    };

    int  depth = 0;
    void report(CR<Report> in);

    Func<void(CR<Report>)>              reportHook;
    Func<void(CR<Report>, bool&, bool)> traceUpdateHook;

  public:
    OrgNodeGroup* group;
    inline OrgParser(OrgNodeGroup* _group) : group(_group) {}


    inline CR<OrgNode> pending() const { return group->lastPending(); }

    inline OrgId fail(OrgTokenId invalid) {
        token(OrgNodeKind::ErrorToken, invalid);
        /// TODO insert token with error description
        token(OrgNodeKind::ErrorTerminator, OrgTokenId::Nil());
        OrgId failed           = end();
        group->at(failed).kind = OrgNodeKind::Error;
    }

    inline OrgId back() const { return group->nodes.back(); }

    inline OrgId start(OrgNodeKind kind) { return group->startTree(kind); }
    inline OrgId end() { return group->endTree(); }
    inline OrgId empty() { return token(OrgNode(OrgNodeKind::Empty)); }
    inline OrgId token(CR<OrgNode> node) { return group->token(node); }
    inline OrgId token(OrgNodeKind kind, OrgTokenId tok) {
        return group->token(kind, tok);
    }

    inline OrgId fake(OrgNodeKind kind) {
        return group->token(
            kind, group->tokens->add(OrgToken(OrgTokenKind::None)));
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

    OrgId parseFootnote(OrgLexer& lex);
    OrgId parseCSVArguments(OrgLexer& lex);
    OrgId parseMacro(OrgLexer& lex);
    OrgId parseRawUrl(OrgLexer& lex);
    OrgId parseLink(OrgLexer& lex);
    OrgId parseInlineMath(OrgLexer& lex);
    OrgId parseSymbol(OrgLexer& lex);
    OrgId parseHashTag(OrgLexer& lex);
    OrgId parseTime(OrgLexer& lex);
    OrgId parseIdent(OrgLexer& lex);
    OrgId parseSrcInline(OrgLexer& lex);
    OrgId parseTable(OrgLexer& lex);
    OrgId parseParagraph(OrgLexer& lex, bool onToplevel);
    OrgId parseTopParagraph(OrgLexer& lex);
    OrgId parseInlineParagraph(OrgLexer& lex);
    OrgId parseCommandArguments(OrgLexer& lex);
    OrgId parseSrcArguments(OrgLexer& lex);
    OrgId parseSrc(OrgLexer& lex);
    OrgId parseListItemBody(OrgLexer& lex);
    OrgId parseListItem(OrgLexer& lex);
    OrgId parseNestedList(OrgLexer& lex);
    OrgId parseList(OrgLexer& lex);
    OrgId parseLogbookClockEntry(OrgLexer& lex);
    OrgId parseLogbookListEntry(OrgLexer& lex);
    OrgId parseLogbook(OrgLexer& lex);
    OrgId parseDrawer(OrgLexer& lex);
    OrgId parseSubtree(OrgLexer& lex);
    OrgId parseOrgFile(OrgLexer& lex);
    OrgId parseLineCommand(OrgLexer& lex);
    OrgId parseToplevelItem(OrgLexer& lex);
    OrgId parseTop(OrgLexer& lex);

    OrgId parseTextWrapCommand(OrgLexer& lex, OrgCommandKind kind);
    void  skipLineCommand(OrgLexer& lex);
};
