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
    QString      getLocMsg(CR<OrgAdapter> adapter);

  public:
    enum class ReportKind
    {
        Enter,
        Leave,
        EnterField,
        LeaveField,
        Json,
    };

    struct Report {
        ReportKind       kind;
        QFileInfo        location;
        int              line;
        Opt<Str>         name;
        Opt<Str>         subname;
        Opt<OrgAdapter>  node;
        Opt<OrgSpecName> field;
        Org*             semResult;
    };

    int  depth = 0;
    void report(CR<Report> in);

    Func<void(CR<Report>)>              reportHook;
    Func<void(CR<Report>, bool&, bool)> traceUpdateHook;

  public:
    Wrap<Table>           convertTable(Up, In);
    Wrap<HashTag>         convertHashTag(Up, In);
    void                  convertSubtreeDrawer(Wrap<Subtree>&, In);
    void                  convertPropertyList(Wrap<Subtree>&, In);
    Wrap<Subtree>         convertSubtree(Up, In);
    Wrap<StmtList>        convertStmtList(Up, In);
    Wrap<Newline>         convertNewline(Up, In);
    Wrap<Word>            convertWord(Up, In);
    Wrap<Space>           convertSpace(Up, In);
    Wrap<Paragraph>       convertParagraph(Up, In);
    Wrap<TimeRange>       convertTimeRange(Up, In);
    Wrap<Time>            convertTime(Up, In);
    Wrap<Punctuation>     convertPunctuation(Up, In);
    Wrap<Link>            convertLink(Up, In);
    Wrap<BigIdent>        convertBigIdent(Up, In);
    Wrap<MarkQuote>       convertMarkQuote(Up, In);
    Wrap<Strike>          convertStrike(Up, In);
    Wrap<Verbatim>        convertVerbatim(Up, In);
    Wrap<Italic>          convertItalic(Up, In);
    Wrap<Par>             convertPar(Up, In);
    Wrap<Bold>            convertBold(Up, In);
    Wrap<RawText>         convertRawText(Up, In);
    Wrap<List>            convertList(Up, In);
    Wrap<ListItem>        convertListItem(Up, In);
    Wrap<Caption>         convertCaption(Up, In);
    Wrap<Quote>           convertQuote(Up, In);
    Wrap<Placeholder>     convertPlaceholder(Up, In);
    Wrap<LatexBody>       convertMath(Up, In);
    Wrap<Footnote>        convertFootnote(Up, In);
    Wrap<Include>         convertInclude(Up, In);
    Wrap<Escaped>         convertEscaped(Up, In);
    Wrap<TextSeparator>   convertTextSeparator(Up, In);
    Wrap<ParseError>      convertParseError(Up, In);
    Wrap<AtMention>       convertAtMention(Up, In);
    Wrap<Underline>       convertUnderline(Up, In);
    Wrap<AdmonitionBlock> convertAdmonitionBlock(Up, In);
    Wrap<Example>         convertExample(Up, In);
    Wrap<Center>          convertCenter(Up, In);
    Wrap<Monospace>       convertMonospace(Up, In);

    Vec<Wrap<Org>> flatConvertAttached(Up, In);

    template <typename T>
    Wrap<T> convertAllSubnodes(Up p, In a) {
        Wrap<T> res = std::make_shared<T>(p, a);

        for (const auto& sub : a) {
            res->push_back(convert(res.get(), sub));
        }

        return res;
    }

    template <typename T>
    Wrap<T> Sem(sem::Org* parent, OrgAdapter adapter) {
        Wrap<T> res = std::make_shared<T>(parent, adapter);
        res->loc    = getLoc(adapter);
        return res;
    }

    template <typename T>
    Wrap<T> SemLeaf(sem::Org* parent, OrgAdapter adapter) {
        auto res  = Sem<T>(parent, adapter);
        res->text = adapter.strVal();
        res->loc  = getLoc(adapter);
        return res;
    }

    Wrap<Org> convert(Up, In);

    Wrap<Document> toDocument(OrgAdapter tree);
};
}; // namespace sem
