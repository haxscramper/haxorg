#pragma once

#include <parse/OrgTypes.hpp>
#include <parse/OrgTokenizer.hpp>
#include <hstd/stdlib/sequtils.hpp>
#include <hstd/stdlib/Ptrs.hpp>

#include <lexbase/TraceBase.hpp>

using ParseCb = std::function<OrgId(OrgLexer&)>;

struct OrgParser : public OperationsTracer {
  public:
    bool TraceState;
    struct TokenWithValue {
        OrgTokenKind kind;
        std::string  value;
    };

    using OrgExpectable = Variant<
        OrgTokenKind,
        OrgTokSet,
        TokenWithValue,
        Vec<OrgTokenKind>>;

    // TODO Move out of the parser base
    struct Error : std::exception {
        Opt<OrgToken> token;
        OrgTokenId    id;
        Opt<LineCol>  loc;
        std::string   extraMsg;
        std::string   getLocMsg() const;

        Error(CR<OrgLexer> lex, CR<std::string> extraMsg = "")
            : id(lex.pos), extraMsg(extraMsg) {
            if (!lex.finished()) {
                token = lex.tok();
                loc   = OrgParser::getLoc(lex);
            }
        }
    };

    struct UnexpectedToken : public Error {
        OrgExpectable wanted;
        UnexpectedToken(
            CR<OrgLexer>      lex,
            CR<OrgExpectable> wanted) noexcept
            : Error(lex), wanted(wanted) {}

        const char* what() const noexcept override;
    };

    struct UnhandledToken : public Error {
        using Error::Error;
        UnhandledToken(CR<OrgLexer> lex) noexcept : Error(lex) {}
        const char* what() const noexcept override;
    };

    std::string getLocMsg(CR<OrgLexer> lex);

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

    struct Report {
        ReportKind kind;
        fs::path   location;
        int        line;
        Opt<Str>   name;
        Opt<Str>   subname;
        Opt<OrgId> node;
        OrgLexer*  lex = nullptr;
    };


  public:
    OrgParser() {}
    static SPtr<OrgParser> initImpl(OrgNodeGroup* _group, bool doTrace);

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
    OrgId parseListItemBody(OrgLexer& lex);
    OrgId parseListItem(OrgLexer& lex);
    OrgId parseTarget(OrgLexer& lex);
    OrgId parseNestedList(OrgLexer& lex);
    OrgId parseList(OrgLexer& lex);
    OrgId parseLatex(OrgLexer& lex);
    OrgId parseBlockExport(OrgLexer& lex);
    OrgId parseParagraph(OrgLexer& lex, bool onTopLevel);

    OrgId parseSubtree(OrgLexer& lex);
    OrgId parseSubtreeTodo(OrgLexer& lex);
    OrgId parseSubtreeUrgency(OrgLexer& lex);
    OrgId parseSubtreeDrawer(OrgLexer& lex);
    OrgId parseSubtreeCompletion(OrgLexer& lex);
    OrgId parseSubtreeTags(OrgLexer& lex);
    OrgId parseSubtreeTitle(OrgLexer& lex);
    OrgId parseSubtreeTimes(OrgLexer& lex);

    OrgId parseSubtreeLogbookClockEntry(OrgLexer& lex);
    OrgId parseSubtreeLogbookListEntry(OrgLexer& lex);
    OrgId parseSubtreeLogbook(OrgLexer& lex);
    OrgId parseSubtreeProperties(OrgLexer& lex);

    OrgId parseOrgFile(OrgLexer& lex);
    OrgId parseLineCommand(OrgLexer& lex);
    OrgId parseToplevelItem(OrgLexer& lex);
    OrgId parseTop(OrgLexer& lex);

    OrgId parseFull(OrgLexer& lex);
    OrgId parseTextWrapCommand(OrgLexer& lex, OrgCommandKind kind);
    void  extendSubtreeTrails(OrgId position);
    void  extendAttachedTrails(OrgId position);
    void  parseCSVArguments(OrgLexer& lex);


  protected:
    void skipLineCommand(OrgLexer& lex);

    CR<OrgNode> pending() const {
        CHECK(0 <= group->treeDepth());
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
        CHECK(0 <= group->treeDepth());
        return group->treeDepth();
    }

    OrgId start(OrgNodeKind kind) { return group->startTree(kind); }
    OrgId end() {
        CHECK(0 <= group->treeDepth());
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


    bool at(CR<OrgLexer> lex, CR<OrgParser::OrgExpectable> item);

    void expect(CR<OrgLexer> lex, CR<OrgParser::OrgExpectable> item);

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
    OrgParser(OrgNodeGroup* _group) : group(_group) {}

    void reserve(int size) { group->nodes.reserve(size); }

    void setReportHook(Func<void(CR<Report>)> in) { reportHook = in; }

    void setTraceUpdateHook(Func<void(CR<Report>, bool&, bool)> in) {
        traceUpdateHook = in;
    }

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

inline std::string to_string(OrgParser::TokenWithValue const& tok) {
    return "($# $#)" % to_string_vec(tok.kind, tok.value);
}
