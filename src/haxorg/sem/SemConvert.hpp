#pragma once

#include <haxorg/sem/SemOrg.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <haxorg/parse/OrgParser.hpp>
#include <haxorg/parse/OrgSpec.hpp>

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

    template <typename T>
    struct ConvResult {
        struct Node {
            SemId<T> node;
        };

        struct Error {
            SemId<ErrorGroup> error;
        };

        SUB_VARIANTS(Kind, Data, data, getKind, Node, Error);
        Data data;

        Opt<SemId<ErrorGroup>> optError() const {
            return isError() ? std::make_optional(error()) : std::nullopt;
        }

        Opt<SemId<T>> optNode() const {
            return isNode() ? std::make_optional(value()) : std::nullopt;
        }

        ConvResult(SemId<T> value) : data{Node{.node = value}} {}

        ConvResult(SemId<ErrorGroup> error)
            : data{Error{.error = error}} {}

        SemId<Org> unwrap() const {
            return isNode() ? value().asOrg() : error().asOrg();
        }

        SemId<T>          value() const { return getNode().node; }
        SemId<ErrorGroup> error() const { return getError().error; }
    };

  public:
    Opt<SemId<ErrorGroup>> convertPropertyList(SemId<Subtree>&, In);
    Opt<SemId<ErrorGroup>> convertSubtreeDrawer(SemId<Subtree>&, In);
    Vec<ConvResult<Org>>   flatConvertAttached(Vec<In> items);
    Vec<ConvResult<Org>>   flatConvertAttachedSubnodes(In item);

    ConvResult<BlockDynamicFallback> convertBlockDynamicFallback(In);
    void convertDocumentOptions(SemId<DocumentOptions> opts, OrgAdapter a);

    ConvResult<Table>           convertTable(In);
    ConvResult<HashTag>         convertHashTag(In);
    ConvResult<SubtreeLog>      convertSubtreeLog(In);
    ConvResult<Subtree>         convertSubtree(In);
    ConvResult<StmtList>        convertStmtList(In);
    ConvResult<Newline>         convertNewline(In);
    ConvResult<Word>            convertWord(In);
    ConvResult<Space>           convertSpace(In);
    ConvResult<Paragraph>       convertParagraph(In);
    ConvResult<TimeRange>       convertTimeRange(In);
    ConvResult<Time>            convertTime(In);
    ConvResult<Punctuation>     convertPunctuation(In);
    ConvResult<Link>            convertLink(In);
    ConvResult<BigIdent>        convertBigIdent(In);
    ConvResult<MarkQuote>       convertMarkQuote(In);
    ConvResult<Strike>          convertStrike(In);
    ConvResult<Verbatim>        convertVerbatim(In);
    ConvResult<Italic>          convertItalic(In);
    ConvResult<Par>             convertPar(In);
    ConvResult<Bold>            convertBold(In);
    ConvResult<RawText>         convertRawText(In);
    ConvResult<RadioTarget>     convertRadioTarget(In);
    ConvResult<TextTarget>      convertTextTarget(In);
    ConvResult<List>            convertList(In);
    ConvResult<ListItem>        convertListItem(In);
    ConvResult<CmdTblfm>        convertCmdTblfm(In);
    ConvResult<CmdCaption>      convertCmdCaption(In);
    ConvResult<BlockQuote>      convertBlockQuote(In);
    ConvResult<BlockComment>    convertBlockComment(In);
    ConvResult<Placeholder>     convertPlaceholder(In);
    ConvResult<Latex>           convertMath(In);
    ConvResult<InlineFootnote>  convertInlineFootnote(In);
    ConvResult<CmdInclude>      convertCmdInclude(In);
    ConvResult<Escaped>         convertEscaped(In);
    ConvResult<TextSeparator>   convertTextSeparator(In);
    ConvResult<AtMention>       convertAtMention(In);
    ConvResult<Underline>       convertUnderline(In);
    ConvResult<BlockAdmonition> convertBlockAdmonition(In);
    ConvResult<BlockExample>    convertBlockExample(In);
    ConvResult<ColonExample>    convertColonExample(In);
    ConvResult<BlockCenter>     convertBlockCenter(In);
    ConvResult<Monospace>       convertMonospace(In);
    ConvResult<Symbol>          convertSymbol(In);
    ConvResult<Macro>           convertMacro(In);
    ConvResult<BlockExport>     convertBlockExport(In);
    ConvResult<CmdColumns>      convertCmdColumns(In);
    ConvResult<BlockCode>       convertBlockCode(In);
    ConvResult<Call>            convertCall(In);
    ConvResult<CmdAttr>         convertCmdAttr(In);
    ConvResult<CmdName>         convertCmdName(In);
    ConvResult<InlineExport>    convertInlineExport(In);

    sem::AttrGroup convertCallArguments(CVec<In>, In source);
    sem::AttrValue convertAttr(In);
    sem::AttrGroup convertAttrs(In);

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
        SemId<T> res = SemId<T>::New(adapter);
        res->loc     = getLoc(adapter);
        return res;
    }

    template <typename T>
    SemId<T> SemLeaf(In adapter) {
        auto res  = Sem<T>(adapter);
        res->text = adapter.val().text;
        return res;
    }

    SemId<ErrorItem> SemErrorItem(
        In          adapter,
        CR<Str>     message,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    SemId<ErrorGroup> SemError(
        In          adapter,
        CR<Str>     message,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    SemId<ErrorGroup> SemError(
        In                    adapter,
        Vec<SemId<ErrorItem>> errors   = {},
        int                   line     = __builtin_LINE(),
        char const*           function = __builtin_FUNCTION());

    SemId<Org>      convert(In);
    SemId<Document> toDocument(OrgAdapter tree);

    finally_std trace(
        Opt<In>     adapter,
        Opt<Str>    subname  = std::nullopt,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());

    finally_std field(
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
