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
    Opt<int>      documentId = std::nullopt;

    OrgConverter(Opt<int> documentId = std::nullopt)
        : documentId(documentId) {
        spec = getOrgSpec();
    }

    OrgAdapter one(OrgAdapter node, OrgSpecName name) {
        return spec->getSingleSubnode(node, name);
    }

    Vec<OrgAdapter> many(OrgAdapter node, OrgSpecName name) {
        return spec->getMultipleSubnode(node, name);
    }

  public:
    SemId<Table>              convertTable(In);
    SemId<HashTag>            convertHashTag(In);
    void                      convertSubtreeDrawer(SemId<Subtree>&, In);
    void                      convertPropertyList(SemId<Subtree>&, In);
    SemId<SubtreeLog>         convertSubtreeLog(In);
    SemId<Subtree>            convertSubtree(In);
    SemId<StmtList>           convertStmtList(In);
    SemId<Newline>            convertNewline(In);
    SemId<Word>               convertWord(In);
    SemId<Space>              convertSpace(In);
    SemId<Paragraph>          convertParagraph(In);
    SemId<AnnotatedParagraph> convertAnnotatedParagraph(In);
    SemId<TimeRange>          convertTimeRange(In);
    SemId<Time>               convertTime(In);
    SemId<Punctuation>        convertPunctuation(In);
    SemId<Link>               convertLink(In);
    SemId<BigIdent>           convertBigIdent(In);
    SemId<MarkQuote>          convertMarkQuote(In);
    SemId<Strike>             convertStrike(In);
    SemId<Verbatim>           convertVerbatim(In);
    SemId<Italic>             convertItalic(In);
    SemId<Par>                convertPar(In);
    SemId<Bold>               convertBold(In);
    SemId<RawText>            convertRawText(In);
    SemId<List>               convertList(In);
    SemId<ListItem>           convertListItem(In);
    SemId<Tblfm>              convertTblfm(In);
    SemId<Caption>            convertCaption(In);
    SemId<Quote>              convertQuote(In);
    SemId<CommentBlock>       convertCommentBlock(In);
    SemId<Placeholder>        convertPlaceholder(In);
    SemId<LatexBody>          convertMath(In);
    SemId<Footnote>           convertFootnote(In);
    SemId<Include>            convertInclude(In);
    SemId<Escaped>            convertEscaped(In);
    SemId<TextSeparator>      convertTextSeparator(In);
    SemId<ParseError>         convertParseError(In);
    SemId<AtMention>          convertAtMention(In);
    SemId<Underline>          convertUnderline(In);
    SemId<AdmonitionBlock>    convertAdmonitionBlock(In);
    SemId<Example>            convertExample(In);
    SemId<Center>             convertCenter(In);
    SemId<Monospace>          convertMonospace(In);
    SemId<Symbol>             convertSymbol(In);
    SemId<Macro>              convertMacro(In);
    SemId<Export>             convertExport(In);
    SemId<CmdArgument>        convertCmdArgument(In);
    SemId<CmdArguments>       convertCmdArguments(In);
    SemId<Code>               convertCode(In);
    SemId<CmdAttr>            convertCmdAttr(In);

    Vec<SemId<Org>> flatConvertAttached(In);


    template <typename T>
    SemId<T> convertAllSubnodes(In a) {
        SemId<T> res = Sem<T>(a);

        for (const auto& sub : a) {
            auto conv = convert(sub);
            res->push_back(conv);
        }

        return res;
    }

    template <typename T>
    SemId<T> Sem(In adapter) {
        SemId<T> res    = SemId<T>::New(adapter);
        res->loc        = getLoc(adapter);
        res->documentId = documentId;
        return res;
    }

    template <typename T>
    SemId<T> SemLeaf(In adapter) {
        auto res  = Sem<T>(adapter);
        res->text = adapter.val().text;
        return res;
    }

    SemId<Org>      convert(In);
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
        SemId<sem::Org> semResult,
        int             line     = __builtin_LINE(),
        char const*     function = __builtin_FUNCTION());

    void print(
        std::string msg,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());
};
}; // namespace sem
