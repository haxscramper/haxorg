#pragma once

#include <sem/SemOrg.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <parse/OrgParser.hpp>

namespace sem {
struct OrgConverter : public OperationsTracer {
    using Up = SemId;
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
        SemId            semResult = SemId::Nil();
    };

    int  depth = 0;
    void report(CR<Report> in);

    Func<void(CR<Report>)>              reportHook;
    Func<void(CR<Report>, bool&, bool)> traceUpdateHook;

  public:
    SemIdT<Table>           convertTable(Up, In);
    SemIdT<HashTag>         convertHashTag(Up, In);
    void                    convertSubtreeDrawer(SemIdT<Subtree>&, In);
    void                    convertPropertyList(SemIdT<Subtree>&, In);
    SemIdT<SubtreeLog>      convertSubtreeLog(Up, In);
    SemIdT<Subtree>         convertSubtree(Up, In);
    SemIdT<StmtList>        convertStmtList(Up, In);
    SemIdT<Newline>         convertNewline(Up, In);
    SemIdT<Word>            convertWord(Up, In);
    SemIdT<Space>           convertSpace(Up, In);
    SemIdT<Paragraph>       convertParagraph(Up, In);
    SemIdT<TimeRange>       convertTimeRange(Up, In);
    SemIdT<Time>            convertTime(Up, In);
    SemIdT<Punctuation>     convertPunctuation(Up, In);
    SemIdT<Link>            convertLink(Up, In);
    SemIdT<BigIdent>        convertBigIdent(Up, In);
    SemIdT<MarkQuote>       convertMarkQuote(Up, In);
    SemIdT<Strike>          convertStrike(Up, In);
    SemIdT<Verbatim>        convertVerbatim(Up, In);
    SemIdT<Italic>          convertItalic(Up, In);
    SemIdT<Par>             convertPar(Up, In);
    SemIdT<Bold>            convertBold(Up, In);
    SemIdT<RawText>         convertRawText(Up, In);
    SemIdT<List>            convertList(Up, In);
    SemIdT<ListItem>        convertListItem(Up, In);
    SemIdT<Caption>         convertCaption(Up, In);
    SemIdT<Quote>           convertQuote(Up, In);
    SemIdT<Placeholder>     convertPlaceholder(Up, In);
    SemIdT<LatexBody>       convertMath(Up, In);
    SemIdT<Footnote>        convertFootnote(Up, In);
    SemIdT<Include>         convertInclude(Up, In);
    SemIdT<Escaped>         convertEscaped(Up, In);
    SemIdT<TextSeparator>   convertTextSeparator(Up, In);
    SemIdT<ParseError>      convertParseError(Up, In);
    SemIdT<AtMention>       convertAtMention(Up, In);
    SemIdT<Underline>       convertUnderline(Up, In);
    SemIdT<AdmonitionBlock> convertAdmonitionBlock(Up, In);
    SemIdT<Example>         convertExample(Up, In);
    SemIdT<Center>          convertCenter(Up, In);
    SemIdT<Monospace>       convertMonospace(Up, In);
    SemIdT<Symbol>          convertSymbol(Up, In);
    SemIdT<Macro>           convertMacro(Up, In);
    SemIdT<Export>          convertExport(Up, In);

    Vec<SemId> flatConvertAttached(Up, In);

    template <typename T>
    SemIdT<T> convertAllSubnodes(Up p, In a) {
        SemIdT<T> res = Sem<T>(p, a);

        for (const auto& sub : a) {
            res->push_back(convert(res, sub));
        }

        return res;
    }

    template <typename T>
    SemIdT<T> Sem(Up parent, In adapter) {
        SemIdT<T> res = GlobalStore::createInSame(
            parent, T::staticKind, parent, adapter);
        res->loc = getLoc(adapter);
        return res;
    }

    template <typename T>
    SemIdT<T> SemLeaf(Up parent, In adapter) {
        auto res  = Sem<T>(parent, adapter);
        res->text = adapter.strVal();
        res->loc  = getLoc(adapter);
        return res;
    }

    SemId            convert(Up, In);
    SemIdT<Document> toDocument(OrgAdapter tree);
};
}; // namespace sem
