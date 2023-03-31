#pragma once

#include <sem/SemOrg.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <parse/OrgParser.hpp>

namespace sem {
struct OrgConverter : public OperationsTracer {
    using Up = Org*;
    using In = OrgAdapter;

  public:
    struct Errors {
        struct Base : std::exception {
            Opt<LineCol>    loc;
            Opt<OrgAdapter> adapter;
            Opt<Org*>       node;
            Base(
                Opt<LineCol>    loc     = std::nullopt,
                Opt<OrgAdapter> adapter = std::nullopt,
                Opt<Org*>       node    = std::nullopt)
                : loc(loc), adapter(adapter), node(node) {}


            QString getLocMsg() const {
                return "$#:$# (pos $#)"
                     % to_string_vec(
                           loc ? loc->line : -1,
                           loc ? loc->column : -1,
                           adapter ? to_string(adapter->id.getIndex())
                                   : to_string("<none>"));
            }
        };

        struct None : Base {};

        struct UnhandledKind : Base {
            OrgNodeKind kind;
            UnhandledKind(OrgNodeKind kind) : kind(kind) {}
            const char* what() const noexcept override {
                return strdup(
                    "Unexpected kind $# at $#"
                    % to_string_vec(kind, getLocMsg()));
            };
        };
    };

    using Error = Variant<Errors::None, Errors::UnhandledKind>;


    struct ConvertError : std::exception {
        Error err;
        ConvertError() : err(Errors::None()) {}
        explicit ConvertError(CR<Error> err) : err(err) {}
        const char* what() const noexcept override {
            return std::visit(
                [](auto const& in) { return in.what(); }, err);
        }
        void setLoc(CR<LineCol> loc) {
            std::visit([&loc](auto& in) { in.loc = loc; }, err);
        }

        void setAdapter(CR<OrgAdapter> adapter) {
            std::visit(
                [&adapter](auto& in) { in.adapter = adapter; }, err);
        }


        Opt<OrgAdapter> getAdapter() const {
            return std::visit(
                [](auto& in) -> Opt<OrgAdapter> { return in.adapter; },
                err);
        }
    };

    Func<LineCol(CR<PosStr>)> locationResolver;
    ConvertError wrapError(CR<Error> err, CR<OrgAdapter> adapter);
    Opt<LineCol> getLoc(CR<OrgAdapter> adapter);

  public:
    enum class ReportKind
    {
        Enter,
        Leave,
    };

    struct Report {
        ReportKind      kind;
        fs::path        location;
        int             line;
        Opt<Str>        name;
        Opt<Str>        subname;
        Opt<OrgAdapter> node;
    };

    int  depth = 0;
    void report(CR<Report> in);

    Func<void(CR<Report>)>              reportHook;
    Func<void(CR<Report>, bool&, bool)> traceUpdateHook;

  public:
    virtual Wrap<Table>       convertTable(Up, In);
    virtual Wrap<HashTag>     convertHashTag(Up, In);
    virtual Wrap<Subtree>     convertSubtree(Up, In);
    virtual Wrap<StmtList>    convertStmtList(Up, In);
    virtual Wrap<SkipNewline> convertSkipNewline(Up, In);
    virtual Wrap<Word>        convertWord(Up, In);
    virtual Wrap<Space>       convertSpace(Up, In);
    virtual Wrap<Paragraph>   convertParagraph(Up, In);
    virtual Wrap<TimeRange>   convertTimeRange(Up, In);
    virtual Wrap<Time>        convertTime(Up, In);
    virtual Wrap<Punctuation> convertPunctuation(Up, In);
    virtual Wrap<Link>        convertLink(Up, In);
    virtual Wrap<BigIdent>    convertBigIdent(Up, In);

    virtual Wrap<Org> convert(Up, In);
};
}; // namespace sem
