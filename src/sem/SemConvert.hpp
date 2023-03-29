#pragma once

#include <sem/SemOrg.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <parse/OrgParser.hpp>

namespace sem {
struct OrgConverter {
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
    virtual UPtr<Table>    convertTable(Up, In);
    virtual UPtr<HashTag>  convertHashTag(Up, In);
    virtual UPtr<Subtree>  convertSubtree(Up, In);
    virtual UPtr<StmtList> convertStmtList(Up, In);

    virtual UPtr<Org> convert(Up, In);
};
}; // namespace sem
