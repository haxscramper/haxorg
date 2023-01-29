#include <parse/OrgTypes.hpp>
#include <parse/OrgTokenizer.hpp>
#include <hstd/stdlib/sequtils.hpp>

using ParseCb = std::function<OrgId(OrgLexer&)>;

struct OrgParser {
    OrgNodeGroup* group;
    inline OrgParser(OrgNodeGroup* _group) : group(_group) {}


    inline void  start(OrgNodeKind kind) { (void)group->startTree(kind); }
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

    OrgId parseCSVArguments(OrgLexer& lex);

    OrgId parseMacro(OrgLexer& lex);

    OrgId parseRawUrl(OrgLexer& lex);

    OrgId parseText(OrgLexer& lex);

    OrgId parseLink(OrgLexer& lex);

    OrgId parseInlineMath(OrgLexer& lex);

    OrgId parseSymbol(OrgLexer& lex);

    OrgId parseHashTag(OrgLexer& lex);

    OrgId parseTime(OrgLexer& lex);

    void parseIdent(OrgLexer& lex);

    OrgId parseSrcInline(OrgLexer& lex);

    OrgId parseTable(OrgLexer& lex);

    OrgId parseParagraph(OrgLexer& lex, bool onToplevel);

    OrgId parseCommandArguments(OrgLexer& lex);

    OrgId parseSrcArguments(OrgLexer& lex);

    OrgId parseTextWrapCommand(OrgLexer& lex, OrgCommandKind kind);

    OrgId parseSrc(OrgLexer& lex);

    OrgId parseListItemBody(OrgLexer& lex);

    OrgId parseListItem(OrgLexer& lex);

    OrgId parseNestedList(OrgLexer& lex);

    OrgId parseList(OrgLexer& lex);

    OrgId parseLogbookClockEntry(OrgLexer& lex);

    OrgId parseLogbookListEntry(OrgLexer& lex);

    void parseLogbook(OrgLexer& lex);

    OrgId parseDrawer(OrgLexer& lex);

    OrgId parseSubtree(OrgLexer& lex);

    void skipLineCommand(OrgLexer& lex);

    OrgId parseOrgFile(OrgLexer& lex);

    OrgId parseLineCommand(OrgLexer& lex);

    OrgId parseToplevelItem(OrgLexer& lex);

    OrgId parseTop(OrgLexer& lex);
};
