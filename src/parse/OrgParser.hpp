#pragma once

#include <parse/OrgTypes.hpp>
#include <parse/OrgTokenizer.hpp>
#include <hstd/stdlib/sequtils.hpp>

#include <lexbase/TraceBase.hpp>

using ParseCb = std::function<OrgId(OrgLexer&)>;

struct OrgParser : public OperationsTracer {
  public:
    struct TokenWithValue {
        OrgTokenKind kind;
        QString      value;
    };

    using OrgExpectable = Variant<
        OrgTokenKind,
        OrgTokSet,
        TokenWithValue,
        Vec<OrgTokenKind>>;

    struct Errors {
        struct Base : std::exception {
            Opt<OrgToken> token;
            OrgTokenId    id;
            Opt<LineCol>  loc;
            QString       getLocMsg() const {
                return "$#:$# (pos $#)"
                     % to_string_vec(
                           loc ? loc->line : -1,
                           loc ? loc->column : -1,
                           id.isNil() ? "<none>"
                                            : to_string(id.getIndex()));
            }

            Base(CR<OrgLexer> lex, Opt<LineCol> loc = std::nullopt)
                : token(lex.tok()), id(lex.pos), loc(loc) {}
        };

        struct None : Base {
            None()
                : Base(
                    SubLexer<OrgTokenKind>{nullptr, Vec<OrgTokenId>{}},
                    std::nullopt) {}
        };

        struct UnexpectedToken : Base {
            OrgExpectable wanted;
            UnexpectedToken(
                CR<OrgLexer>      lex,
                Opt<LineCol>      loc,
                CR<OrgExpectable> wanted)
                : Base(lex, loc), wanted(wanted) {}

            const char* what() const noexcept override {
                return strdup(
                    "Expected $#, but got $# at $#"
                    % to_string_vec(
                        std::visit(
                            overloaded{
                                [](CR<TokenWithValue> it) {
                                    return "$# ('$#')"
                                         % to_string_vec(
                                               it.kind, it.value);
                                },
                                [](auto const& it) {
                                    return to_string(it);
                                }},
                            wanted),
                        token,
                        getLocMsg()));
            }
        };

        struct UnhandledToken : Base {
            using Base::Base;
            const char* what() const noexcept override {
                return strdup(
                    "Encountered $# at $#, which is was not expected"
                    % to_string_vec(token, getLocMsg()));
            }
        };
    };

    using Error = Variant<
        Errors::None,
        Errors::UnhandledToken,
        Errors::UnexpectedToken>;

    struct ParserError : std::exception {
        Error err;
        ParserError() : err(Errors::None()) {}
        explicit ParserError(CR<Error> err) : err(err) {}
        const char* what() const noexcept override {
            return std::visit(
                [](auto const& in) { return in.what(); }, err);
        }
        void setLoc(CR<LineCol> loc) {
            std::visit([&loc](auto& in) { in.loc = loc; }, err);
        }
    };

    Func<LineCol(CR<PosStr>)> locationResolver;

    ParserError wrapError(CR<Error> err, CR<OrgLexer> lex);

    Opt<LineCol> getLoc(CR<OrgLexer> lex);

  public:
    enum class ReportKind
    {
        EnterParse,
        LeaveParse,
        StartNode,
        EndNode,
        AddToken,
        Error
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

    OrgTokenId pop(OrgLexer& lex, CR<OrgExpectable> item);
    void       skip(OrgLexer& lex, CR<OrgExpectable> item);

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
