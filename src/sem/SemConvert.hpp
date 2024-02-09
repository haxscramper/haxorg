#pragma once

#include <sem/SemOrg.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <parse/OrgParser.hpp>
#include <parse/OrgSpec.hpp>

namespace sem {
struct OrgConverter : public OperationsTracer {
    using Up = SemId<Org>;
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


            std::string getLocMsg() const {
                return "$#:$# (pos $#)"
                     % to_string_vec(
                           loc ? loc->line : -1,
                           loc ? loc->column : -1,
                           adapter ? fmt1(adapter->id.getIndex())
                                   : fmt1("<none>"));
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

    ConvertError wrapError(CR<Error> err, CR<OrgAdapter> adapter);
    Opt<LineCol> getLoc(CR<OrgAdapter> adapter);
    std::string  getLocMsg(CR<OrgAdapter> adapter);

  public:
    enum class ReportKind
    {
        Enter,
        Leave,
        EnterField,
        LeaveField,
        Json,
        Print,
    };

    struct Report : OperationsMsg {
        ReportKind       kind;
        Opt<OrgAdapter>  node;
        Opt<OrgSpecName> field;
        SemId<Org>       semResult = SemId<Org>::Nil();
    };

    int  depth = 0;
    void report(CR<Report> in);

    Func<void(CR<Report>)>              reportHook;
    Func<void(CR<Report>, bool&, bool)> traceUpdateHook;

  public:
    UPtr<OrgSpec> spec;
    ContextStore* context;

    OrgConverter(ContextStore* context) : context(context) {
        spec = getOrgSpec();
    }

    OrgAdapter one(OrgAdapter node, OrgSpecName name) {
        return spec->getSingleSubnode(node, name);
    }

    Vec<OrgAdapter> many(OrgAdapter node, OrgSpecName name) {
        return spec->getMultipleSubnode(node, name);
    }

  public:
    SemId<Table>           convertTable(Up, In);
    SemId<HashTag>         convertHashTag(Up, In);
    void                   convertSubtreeDrawer(SemId<Subtree>&, In);
    void                   convertPropertyList(SemId<Subtree>&, In);
    SemId<SubtreeLog>      convertSubtreeLog(Up, In);
    SemId<Subtree>         convertSubtree(Up, In);
    SemId<StmtList>        convertStmtList(Up, In);
    SemId<Newline>         convertNewline(Up, In);
    SemId<Word>            convertWord(Up, In);
    SemId<Space>           convertSpace(Up, In);
    SemId<Paragraph>       convertParagraph(Up, In);
    SemId<TimeRange>       convertTimeRange(Up, In);
    SemId<Time>            convertTime(Up, In);
    SemId<Punctuation>     convertPunctuation(Up, In);
    SemId<Link>            convertLink(Up, In);
    SemId<BigIdent>        convertBigIdent(Up, In);
    SemId<MarkQuote>       convertMarkQuote(Up, In);
    SemId<Strike>          convertStrike(Up, In);
    SemId<Verbatim>        convertVerbatim(Up, In);
    SemId<Italic>          convertItalic(Up, In);
    SemId<Par>             convertPar(Up, In);
    SemId<Bold>            convertBold(Up, In);
    SemId<RawText>         convertRawText(Up, In);
    SemId<List>            convertList(Up, In);
    SemId<ListItem>        convertListItem(Up, In);
    SemId<Tblfm>           convertTblfm(Up, In);
    SemId<Caption>         convertCaption(Up, In);
    SemId<Quote>           convertQuote(Up, In);
    SemId<Placeholder>     convertPlaceholder(Up, In);
    SemId<LatexBody>       convertMath(Up, In);
    SemId<Footnote>        convertFootnote(Up, In);
    SemId<Include>         convertInclude(Up, In);
    SemId<Escaped>         convertEscaped(Up, In);
    SemId<TextSeparator>   convertTextSeparator(Up, In);
    SemId<ParseError>      convertParseError(Up, In);
    SemId<AtMention>       convertAtMention(Up, In);
    SemId<Underline>       convertUnderline(Up, In);
    SemId<AdmonitionBlock> convertAdmonitionBlock(Up, In);
    SemId<Example>         convertExample(Up, In);
    SemId<Center>          convertCenter(Up, In);
    SemId<Monospace>       convertMonospace(Up, In);
    SemId<Symbol>          convertSymbol(Up, In);
    SemId<Macro>           convertMacro(Up, In);
    SemId<Export>          convertExport(Up, In);
    SemId<CmdArgument>     convertCmdArgument(Up, In);
    SemId<CmdArguments>    convertCmdArguments(Up, In);
    SemId<Code>            convertCode(Up, In);

    Vec<SemId<Org>> flatConvertAttached(Up, In);


    template <typename T>
    SemId<T> convertAllSubnodes(Up p, In a) {
        SemId<T> res = Sem<T>(p, a);

        for (const auto& sub : a) {
            auto conv = convert(res, sub);
            res->push_back(conv);
        }

        return res;
    }

    template <typename T>
    SemId<T> Sem(Up parent, In adapter) {
        SemId<T> res = SemId<T>::New(adapter);
        res->loc     = getLoc(adapter);
        return res;
    }

    template <typename T>
    SemId<T> SemLeaf(Up parent, In adapter) {
        auto res  = Sem<T>(parent, adapter);
        res->text = adapter.val().text;
        res->loc  = getLoc(adapter);
        return res;
    }

    SemId<Org>      convert(Up, In);
    SemId<Document> toDocument(OrgAdapter tree);

    finally trace(
        In          adapter,
        Opt<Str>    subname  = std::nullopt,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    finally field(
        OrgSpecName name,
        In          adapter,
        Opt<Str>    subname  = std::nullopt,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    void print_json(
        SemId<sem::Org>       semResult,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    void print(
        std::string msg,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());
};
}; // namespace sem
