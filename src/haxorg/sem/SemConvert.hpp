#pragma once

#include <haxorg/sem/SemOrg.hpp>
#include <hstd/stdlib/Ptrs.hpp>
#include <haxorg/parse/OrgParser.hpp>
#include <haxorg/parse/OrgSpec.hpp>

namespace org::sem {
struct OrgConverter : public hstd::OperationsTracer {
    using Up = SemId<Org>;
    using In = parse::OrgAdapter;

  public:
    struct Errors {
        struct Base : std::exception {
            hstd::Opt<parse::LineCol>    loc;
            hstd::Opt<parse::OrgAdapter> adapter;
            hstd::Opt<Org*>              node;
            Base(
                hstd::Opt<parse::LineCol>    loc     = std::nullopt,
                hstd::Opt<parse::OrgAdapter> adapter = std::nullopt,
                hstd::Opt<Org*>              node    = std::nullopt)
                : loc(loc), adapter(adapter), node(node) {}


            std::string getLocMsg() const {
                return hstd::fmt(
                    "{}:{} (pos {})",
                    loc ? loc->line : -1,
                    loc ? loc->column : -1,
                    adapter ? hstd::fmt1(adapter->id.getIndex())
                            : hstd::fmt1("<none>"));
            }
        };

        struct None : Base {};

        struct UnhandledKind : Base {
            OrgNodeKind kind;
            UnhandledKind(OrgNodeKind kind) : kind(kind) {}
            const char* what() const noexcept override {
                return hstd::strdup(hstd::fmt(
                    "Unexpected kind {} at {}", kind, getLocMsg()));
            };
        };
    };

    using Error = hstd::Variant<Errors::None, Errors::UnhandledKind>;


    struct ConvertError : std::exception {
        Error err;
        ConvertError() : err(Errors::None()) {}
        explicit ConvertError(Error const& err) : err(err) {}
        const char* what() const noexcept override {
            return std::visit(
                [](auto const& in) { return in.what(); }, err);
        }
        void setLoc(org::parse::LineCol const& loc) {
            std::visit([&loc](auto& in) { in.loc = loc; }, err);
        }

        void setAdapter(org::parse::OrgAdapter const& adapter) {
            std::visit(
                [&adapter](auto& in) { in.adapter = adapter; }, err);
        }


        hstd::Opt<org::parse::OrgAdapter> getAdapter() const {
            return std::visit(
                [](auto& in) -> hstd::Opt<org::parse::OrgAdapter> {
                    return in.adapter;
                },
                err);
        }
    };

    ConvertError wrapError(
        Error const&                  err,
        org::parse::OrgAdapter const& adapter);
    hstd::Opt<org::parse::LineCol> getLoc(
        org::parse::OrgAdapter const& adapter);
    std::string getLocMsg(org::parse::OrgAdapter const& adapter);

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

    struct Report : hstd::OperationsMsg {
        ReportKind                   kind;
        hstd::Opt<parse::OrgAdapter> node;
        hstd::Opt<OrgSpecName>       field;
        SemId<Org>                   semResult = SemId<Org>::Nil();
    };

    void report(Report const& in);

  public:
    hstd::UPtr<OrgSpec> spec;
    hstd::Opt<int>      documentId = std::nullopt;

    OrgConverter(hstd::Opt<int> documentId = std::nullopt)
        : documentId(documentId) {
        spec = getOrgSpec();
    }

    org::parse::OrgAdapter one(
        org::parse::OrgAdapter node,
        OrgSpecName            name) {
        return spec->getSingleSubnode(node, name);
    }

    hstd::Vec<org::parse::OrgAdapter> many(
        org::parse::OrgAdapter node,
        OrgSpecName            name) {
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

        hstd::Opt<SemId<ErrorGroup>> optError() const {
            return isError() ? std::make_optional(error()) : std::nullopt;
        }

        hstd::Opt<SemId<T>> optNode() const {
            return isNode() ? std::make_optional(value()) : std::nullopt;
        }

        operator bool() const { return isNode(); }

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
    hstd::Opt<SemId<ErrorGroup>> convertPropertyList(SemId<Subtree>&, In);
    hstd::Opt<SemId<ErrorGroup>> convertSubtreeDrawer(SemId<Subtree>&, In);
    hstd::Vec<ConvResult<Org>>   flatConvertAttached(hstd::Vec<In> items);
    hstd::Vec<ConvResult<Org>>   flatConvertAttachedSubnodes(In item);

    ConvResult<BlockDynamicFallback> convertBlockDynamicFallback(In);
    void                             convertDocumentOptions(
                                    SemId<DocumentOptions> opts,
                                    parse::OrgAdapter      a);

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
    ConvResult<CmdCall>         convertCmdCall(In);
    ConvResult<CmdAttr>         convertCmdAttr(In);
    ConvResult<CmdName>         convertCmdName(In);
    ConvResult<InlineExport>    convertInlineExport(In);
    ConvResult<Document>        convertDocument(In);

    sem::AttrValue convertAttr(In);
    sem::AttrGroup convertAttrs(In);
    sem::LispCode  convertLisp(In);

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
        In               adapter,
        hstd::Str const& message,
        int              line     = __builtin_LINE(),
        char const*      function = __builtin_FUNCTION());

    SemId<ErrorGroup> SemError(
        In               adapter,
        hstd::Str const& message,
        int              line     = __builtin_LINE(),
        char const*      function = __builtin_FUNCTION());

    SemId<ErrorGroup> SemError(
        In                          adapter,
        hstd::Vec<SemId<ErrorItem>> errors   = {},
        int                         line     = __builtin_LINE(),
        char const*                 function = __builtin_FUNCTION());

    SemId<Org> convert(In);

    hstd::finally_std trace(
        hstd::Opt<In>        adapter,
        hstd::Opt<hstd::Str> subname  = std::nullopt,
        int                  line     = __builtin_LINE(),
        char const*          function = __builtin_FUNCTION());

    hstd::finally_std field(
        OrgSpecName          name,
        In                   adapter,
        hstd::Opt<hstd::Str> subname  = std::nullopt,
        int                  line     = __builtin_LINE(),
        char const*          function = __builtin_FUNCTION());

    void print_json(
        SemId<sem::Org> semResult,
        int             line     = __builtin_LINE(),
        char const*     function = __builtin_FUNCTION());

    void print(
        std::string msg,
        int         line     = __builtin_LINE(),
        char const* function = __builtin_FUNCTION());
};
}; // namespace org::sem
