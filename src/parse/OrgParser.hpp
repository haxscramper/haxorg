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
    virtual void reserve(int size) = 0;


  public:
    OrgParser() {}
    static SPtr<OrgParser> initImpl(OrgNodeGroup* _group, bool doTrace);

#define EACH_PARSER_METHOD(__IMPL)                                        \
    __IMPL(Footnote);                                                     \
    __IMPL(Macro);                                                        \
    __IMPL(RawUrl);                                                       \
    __IMPL(Link);                                                         \
    __IMPL(InlineMath);                                                   \
    __IMPL(Symbol);                                                       \
    __IMPL(HashTag);                                                      \
    __IMPL(TimeRange);                                                    \
    __IMPL(TimeStamp);                                                    \
    __IMPL(Ident);                                                        \
    __IMPL(SrcInline);                                                    \
    __IMPL(Table);                                                        \
    __IMPL(Placeholder);                                                  \
    __IMPL(TopParagraph);                                                 \
    __IMPL(InlineParagraph);                                              \
    __IMPL(CommandArguments);                                             \
    __IMPL(SrcArguments);                                                 \
    __IMPL(Src);                                                          \
    __IMPL(Example);                                                      \
    __IMPL(ListItemBody);                                                 \
    __IMPL(ListItem);                                                     \
    __IMPL(Target);                                                       \
    __IMPL(NestedList);                                                   \
    __IMPL(List);                                                         \
    __IMPL(Latex);                                                        \
                                                                          \
    __IMPL(Subtree);                                                      \
    __IMPL(SubtreeTodo);                                                  \
    __IMPL(SubtreeUrgency);                                               \
    __IMPL(SubtreeDrawer);                                                \
    __IMPL(SubtreeCompletion);                                            \
    __IMPL(SubtreeTags);                                                  \
    __IMPL(SubtreeTitle);                                                 \
    __IMPL(SubtreeTimes);                                                 \
                                                                          \
    __IMPL(SubtreeLogbookClockEntry);                                     \
    __IMPL(SubtreeLogbookListEntry);                                      \
    __IMPL(SubtreeLogbook);                                               \
    __IMPL(SubtreeProperties);                                            \
                                                                          \
    __IMPL(OrgFile);                                                      \
    __IMPL(LineCommand);                                                  \
    __IMPL(ToplevelItem);                                                 \
    __IMPL(Top);

#define _def(Kind) virtual OrgId parse##Kind(OrgLexer& lex) = 0;
    EACH_PARSER_METHOD(_def)
#undef _def

    virtual OrgId parseTextWrapCommand(OrgLexer& lex, OrgCommandKind kind) = 0;

    virtual void extendSubtreeTrails(OrgId position)  = 0;
    virtual void extendAttachedTrails(OrgId position) = 0;
    virtual void parseCSVArguments(OrgLexer& lex)     = 0;
};

inline QString to_string(OrgParser::TokenWithValue const& tok) {
    return "($# $#)" % to_string_vec(tok.kind, tok.value);
}
