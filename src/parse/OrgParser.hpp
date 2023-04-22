#pragma once

#include <parse/OrgTypes.hpp>
#include <parse/OrgTokenizer.hpp>
#include <hstd/stdlib/sequtils.hpp>
#include <hstd/stdlib/Ptrs.hpp>

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
            QString       extraMsg;
            QString       getLocMsg() const;

            Base(CR<OrgLexer> lex, Opt<LineCol> loc = std::nullopt);

            Base(
                CR<OrgLexer> lex,
                CR<QString>  extraMsg,
                Opt<LineCol> loc = std::nullopt);
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

            const char* what() const noexcept override;
        };

        struct UnhandledToken : public Base {
            using Base::Base;
            const char* what() const noexcept override;
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

    virtual void setLocationResolver(Func<LineCol(CR<PosStr>)>) = 0;

    ParserError          wrapError(CR<Error> err, CR<OrgLexer> lex);
    virtual Opt<LineCol> getLoc(CR<OrgLexer> lex) = 0;
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
        QFileInfo  location;
        int        line;
        Opt<Str>   name;
        Opt<Str>   subname;
        Opt<OrgId> node;
        OrgLexer*  lex = nullptr;
    };

    virtual void setReportHook(Func<void(CR<Report>)>) = 0;
    virtual void setTraceUpdateHook(Func<void(CR<Report>, bool&, bool)>) = 0;

  public:
    OrgParser() {}
    static SPtr<OrgParser> initImpl(OrgNodeGroup* _group, bool doTrace);


    virtual OrgId parseFootnote(OrgLexer& lex)                   = 0;
    virtual OrgId parseCSVArguments(OrgLexer& lex)               = 0;
    virtual OrgId parseMacro(OrgLexer& lex)                      = 0;
    virtual OrgId parseRawUrl(OrgLexer& lex)                     = 0;
    virtual OrgId parseLink(OrgLexer& lex)                       = 0;
    virtual OrgId parseInlineMath(OrgLexer& lex)                 = 0;
    virtual OrgId parseSymbol(OrgLexer& lex)                     = 0;
    virtual OrgId parseHashTag(OrgLexer& lex)                    = 0;
    virtual OrgId parseTimeRange(OrgLexer& lex)                  = 0;
    virtual OrgId parseTimeStamp(OrgLexer& lex)                  = 0;
    virtual OrgId parseIdent(OrgLexer& lex)                      = 0;
    virtual OrgId parseSrcInline(OrgLexer& lex)                  = 0;
    virtual OrgId parseTable(OrgLexer& lex)                      = 0;
    virtual OrgId parseParagraph(OrgLexer& lex, bool onToplevel) = 0;
    virtual OrgId parsePlaceholder(OrgLexer& lex)                = 0;
    virtual OrgId parseTopParagraph(OrgLexer& lex)               = 0;
    virtual OrgId parseInlineParagraph(OrgLexer& lex)            = 0;
    virtual OrgId parseCommandArguments(OrgLexer& lex)           = 0;
    virtual OrgId parseSrcArguments(OrgLexer& lex)               = 0;
    virtual OrgId parseSrc(OrgLexer& lex)                        = 0;
    virtual OrgId parseExample(OrgLexer& lex)                    = 0;
    virtual OrgId parseListItemBody(OrgLexer& lex)               = 0;
    virtual OrgId parseListItem(OrgLexer& lex)                   = 0;
    virtual OrgId parseNestedList(OrgLexer& lex)                 = 0;
    virtual OrgId parseList(OrgLexer& lex)                       = 0;
    virtual OrgId parseLatex(OrgLexer& lex)                      = 0;

    virtual OrgId parseSubtree(OrgLexer& lex)             = 0;
    virtual OrgId parseSubtreeTodo(OrgLexer& str)         = 0;
    virtual OrgId parseSubtreeUrgency(OrgLexer& str)      = 0;
    virtual OrgId parseSubtreeDrawer(OrgLexer& lex)       = 0;
    virtual OrgId parseSubtreeCompletion(OrgLexer& lexer) = 0;
    virtual OrgId parseSubtreeTags(OrgLexer& lex)         = 0;
    virtual OrgId parseSubtreeTitle(OrgLexer& str)        = 0;
    virtual OrgId parseSubtreeTimes(OrgLexer& str)        = 0;

    virtual OrgId parseSubtreeLogbookClockEntry(OrgLexer& lex) = 0;
    virtual OrgId parseSubtreeLogbookListEntry(OrgLexer& lex)  = 0;
    virtual OrgId parseSubtreeLogbook(OrgLexer& lex)           = 0;
    virtual OrgId parseSubtreeProperties(OrgLexer& lex)        = 0;


    virtual OrgId parseOrgFile(OrgLexer& lex)      = 0;
    virtual OrgId parseLineCommand(OrgLexer& lex)  = 0;
    virtual OrgId parseToplevelItem(OrgLexer& lex) = 0;
    virtual OrgId parseTop(OrgLexer& lex)          = 0;

    virtual OrgId parseTextWrapCommand(OrgLexer& lex, OrgCommandKind kind) = 0;

    virtual void extendSubtreeTrails(OrgId position)  = 0;
    virtual void extendAttachedTrails(OrgId position) = 0;
};
