#pragma once

#include <parse/OrgTypes.hpp>
#include <parse/OrgTokenizer.hpp>
#include <hstd/stdlib/sequtils.hpp>

#include <lexbase/TraceBase.hpp>

using ParseCb = std::function<OrgId(OrgLexer&)>;

struct OrgParserImplBase;

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
            QString       extraMsg;
            QString       getLocMsg() const {
                return "$#:$# (pos $#)"
                     % to_string_vec(
                           loc ? loc->line : -1,
                           loc ? loc->column : -1,
                           id.isNil() ? "<none>"
                                            : to_string(id.getIndex()));
            }

            Base(CR<OrgLexer> lex, Opt<LineCol> loc = std::nullopt)
                : token(lex.tok()), id(lex.pos), loc(loc) {
                extraMsg = lex.printToString(false);
            }

            Base(
                CR<OrgLexer> lex,
                CR<QString>  extraMsg,
                Opt<LineCol> loc = std::nullopt)
                : token(lex.tok())
                , id(lex.pos)
                , loc(loc)
                , extraMsg(extraMsg) {}
        };

        struct None : Base {
            None()
                : Base(
                    SubLexer<OrgTokenKind>{nullptr, Vec<OrgTokenId>{}},
                    std::nullopt) {}
        };

        struct UnexpectedToken : public Base {
            OrgExpectable wanted;
            UnexpectedToken(
                CR<OrgLexer>      lex,
                Opt<LineCol>      loc,
                CR<OrgExpectable> wanted)
                : Base(lex, loc), wanted(wanted) {}

            const char* what() const noexcept override {
                return strdup(
                    "Expected $#, but got $# at $# ($#)"
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
                        this->token,
                        getLocMsg(),
                        this->extraMsg));
            }
        };

        struct UnhandledToken : public Base {
            using Base::Base;
            const char* what() const noexcept override {
                return strdup(
                    "Encountered $# at $#, which is was not expected ($#)"
                    % to_string_vec(
                        this->token, getLocMsg(), this->extraMsg));
            }
        };
    };

    using Error = Variant<
        typename Errors::None,
        typename Errors::UnhandledToken,
        typename Errors::UnexpectedToken>;

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

    void                 setLocationResolver(Func<LineCol(CR<PosStr>)>);
    ParserError          wrapError(CR<Error> err, CR<OrgLexer> lex);
    virtual Opt<LineCol> getLoc(CR<OrgLexer> lex);
    QString              getLocMsg(CR<OrgLexer> lex);

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

    int  depth = 0;
    void report(CR<Report> in);

    Func<void(CR<Report>)>              reportHook;
    Func<void(CR<Report>, bool&, bool)> traceUpdateHook;

  public:
    OrgNodeGroup*                      group = nullptr;
    std::shared_ptr<OrgParserImplBase> impl  = nullptr;
    OrgParser(OrgNodeGroup* _group) : group(_group) {}
    void initImpl(bool doTrace);


    inline CR<OrgNode> pending() const { return group->lastPending(); }

    inline OrgId fail(OrgTokenId invalid) {
        token(OrgNodeKind::ErrorToken, invalid);
        /// TODO insert token with error description
        token(OrgNodeKind::ErrorTerminator, OrgTokenId::Nil());
        OrgId failed           = end();
        group->at(failed).kind = OrgNodeKind::Error;
        return failed;
    }

    inline OrgId back() const { return group->nodes.back(); }

    int          treeDepth() const { return group->treeDepth(); }
    inline OrgId start(OrgNodeKind kind) { return group->startTree(kind); }
    inline OrgId end() { return group->endTree(); }
    inline OrgId empty() { return token(getEmpty()); }
    inline OrgNode getEmpty() { return OrgNode::Mono(OrgNodeKind::Empty); }
    inline OrgId   token(CR<OrgNode> node) { return group->token(node); }
    inline OrgId   token(OrgNodeKind kind, OrgTokenId tok) {
        return group->token(kind, tok);
    }

    inline OrgId fake(OrgNodeKind kind) {
        return group->token(
            kind, group->tokens->add(OrgToken(OrgTokenKind::None)));
    }

    void       expect(CR<OrgLexer> lex, CR<OrgExpectable> item);
    OrgTokenId pop(OrgLexer& lex, CR<OrgExpectable> item);
    void       skip(OrgLexer& lex, CR<OrgExpectable> item);

    virtual OrgId parseFootnote(OrgLexer& lex);
    virtual OrgId parseCSVArguments(OrgLexer& lex);
    virtual OrgId parseMacro(OrgLexer& lex);
    virtual OrgId parseRawUrl(OrgLexer& lex);
    virtual OrgId parseLink(OrgLexer& lex);
    virtual OrgId parseInlineMath(OrgLexer& lex);
    virtual OrgId parseSymbol(OrgLexer& lex);
    virtual OrgId parseHashTag(OrgLexer& lex);
    virtual OrgId parseTimeRange(OrgLexer& lex);
    virtual OrgId parseTimeStamp(OrgLexer& lex);
    virtual OrgId parseIdent(OrgLexer& lex);
    virtual OrgId parseSrcInline(OrgLexer& lex);
    virtual OrgId parseTable(OrgLexer& lex);
    virtual OrgId parseParagraph(OrgLexer& lex, bool onToplevel);
    virtual OrgId parsePlaceholder(OrgLexer& lex);
    virtual OrgId parseTopParagraph(OrgLexer& lex);
    virtual OrgId parseInlineParagraph(OrgLexer& lex);
    virtual OrgId parseCommandArguments(OrgLexer& lex);
    virtual OrgId parseSrcArguments(OrgLexer& lex);
    virtual OrgId parseSrc(OrgLexer& lex);
    virtual OrgId parseExample(OrgLexer& lex);
    virtual OrgId parseListItemBody(OrgLexer& lex);
    virtual OrgId parseListItem(OrgLexer& lex);
    virtual OrgId parseNestedList(OrgLexer& lex);
    virtual OrgId parseList(OrgLexer& lex);
    virtual OrgId parseLatex(OrgLexer& lex);

    virtual OrgId parseSubtree(OrgLexer& lex);
    virtual OrgId parseSubtreeTodo(OrgLexer& str);
    virtual OrgId parseSubtreeUrgency(OrgLexer& str);
    virtual OrgId parseSubtreeDrawer(OrgLexer& lex);
    virtual OrgId parseSubtreeCompletion(OrgLexer& lexer);
    virtual OrgId parseSubtreeTags(OrgLexer& lex);
    virtual OrgId parseSubtreeTitle(OrgLexer& str);
    virtual OrgId parseSubtreeTimes(OrgLexer& str);

    virtual OrgId parseSubtreeLogbookClockEntry(OrgLexer& lex);
    virtual OrgId parseSubtreeLogbookListEntry(OrgLexer& lex);
    virtual OrgId parseSubtreeLogbook(OrgLexer& lex);
    virtual OrgId parseSubtreeProperties(OrgLexer& lex);


    virtual OrgId parseOrgFile(OrgLexer& lex);
    virtual OrgId parseLineCommand(OrgLexer& lex);
    virtual OrgId parseToplevelItem(OrgLexer& lex);
    virtual OrgId parseTop(OrgLexer& lex);

    virtual OrgId parseTextWrapCommand(OrgLexer& lex, OrgCommandKind kind);

    void skipLineCommand(OrgLexer& lex);
    void extendSubtreeTrails(OrgId position);
    void extendAttachedTrails(OrgId position);
};
