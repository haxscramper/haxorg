#include "hstd/stdlib/Json.hpp"
#include <gtest/gtest.h>
#include <fuzztest/fuzztest.h>
#include <absl/log/log.h>
#include <sem/SemOrgSerde.hpp>
#include <sem/SemOrgFormat.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Yaml.hpp>
#include <google/protobuf/text_format.h>
#include <google/protobuf/util/json_util.h>
#include <sem/SemOrgSerdeDeclarations.hpp>
#include <immer/vector.hpp>
#include <immer/box.hpp>

namespace prt = orgproto;
namespace gpb = ::google::protobuf;
using osk     = OrgSemKind;
using namespace fuzztest;

void PrintMessageWithTypeName(
    const gpb::Message& message,
    std::ostringstream& oss,
    int                 depth) {
    const gpb::Descriptor* descriptor = message.GetDescriptor();
    const gpb::Reflection* reflection = message.GetReflection();
    std::string indent(depth * 2, ' '); // Indentation for pretty printing

    oss << indent << descriptor->name() << " {\n";

    for (int i = 0; i < descriptor->field_count(); ++i) {
        const gpb::FieldDescriptor* field = descriptor->field(i);

        if ((!field->is_repeated()
             && !reflection->HasField(message, field))
            || (field->is_repeated()
                && reflection->FieldSize(message, field) == 0)) {
            continue; // Skip non-set fields
        }


        if (field->cpp_type()
            == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE) {
            if (field->is_repeated()) {
                int count = reflection->FieldSize(message, field);
                oss << indent << "  " << field->name() << ": [\n";
                for (int j = 0; j < count; ++j) {
                    const gpb::Message& subMessage = //
                        reflection->GetRepeatedMessage(message, field, j);
                    PrintMessageWithTypeName(subMessage, oss, depth + 2);
                }
                oss << indent << "  "
                    << "]\n";
            } else {
                oss << indent << "  " << field->name() << ":\n";
                const gpb::Message& subMessage = //
                    reflection->GetMessage(message, field);
                PrintMessageWithTypeName(subMessage, oss, depth + 2);
            }
        } else {
            oss << indent << "  " << field->name() << ": ";
            std::string fieldText;
            if (field->is_repeated()) {
                oss << "[ ";
                int count = reflection->FieldSize(message, field);
                for (int j = 0; j < count; ++j) {
                    google::protobuf::TextFormat::PrintFieldValueToString(
                        message, field, j, &fieldText);
                    oss << fieldText << (j < count - 1 ? " " : "");
                }
                oss << " ]\n";
            } else if (field->name() == "debug") {
                oss << reflection->GetString(message, field) << "\n";
            } else {
                google::protobuf::TextFormat::PrintFieldValueToString(
                    message, field, -1, &fieldText);
                oss << fieldText << "\n";
            }
        }
    }

    oss << indent << "}\n";
}

std::string PrintWithTypeName(const gpb::Message& message) {
    std::ostringstream oss;
    PrintMessageWithTypeName(message, oss, 0);
    return oss.str();
}


void CheckAnyNodeFail(prt::AnyNode const& node) {
    {
        gpb::util::JsonPrintOptions options;
        options.add_whitespace = true;
        std::string jsonFormatStr;
        std::string textFormatStr = PrintWithTypeName(node);
        (void)gpb::util::MessageToJsonString(
            node, &jsonFormatStr, options);
        writeFile("/tmp/protobuf_dump.json", jsonFormatStr);
        writeFile("/tmp/protobuf_dump.txt", textFormatStr);
    }
    sem::ContextStore generated_context;
    sem::SemId        generated_node = sem::SemId::Nil();
    proto_serde<orgproto::AnyNode, sem::SemId>::read(
        &generated_context,
        node,
        proto_write_accessor<sem::SemId>::for_ref(generated_node));

    sem::Formatter      formatter;
    sem::Formatter::Res generated_layout = formatter.toString(
        generated_node);
    std::string generated_text = formatter.store.toString(
        generated_layout);

    writeFile("/tmp/formatted.org", generated_text);
}

template <typename NodeType>
prt::AnyNode ConvertAnyNode(NodeType const& subNode) {
    prt::AnyNode anyNode;


    // Use the macro to set the appropriate field on AnyNode
#define _case(_fieldEnum, _field, _Kind)                                  \
    if constexpr (std::is_same<NodeType, prt::_Kind>::value) {            \
        *anyNode.mutable_##_field() = subNode;                            \
    }

    EACH_ANY_NODE_PROTO_FIELD(_case)
#undef _case

    CHECK(anyNode.kind_case() != orgproto::AnyNode::KIND_NOT_SET)
        << demangle(typeid(subNode).name());

    return anyNode;
}

template <typename NodeType>
Domain<prt::AnyNode> GenerateAnyNodeWrapper(
    Domain<NodeType> nodeGenerator) {
    return Map(ConvertAnyNode<NodeType>, nodeGenerator);
}

struct GenerateNodeDebug {
    DECL_FIELDS(
        GenerateNodeDebug,
        (),
        ((int), line, __builtin_LINE()),
        ((Str), message, ""));
};

struct GenerateNodePath {
    OrgSemKind kind;
    SemSet     expand;
};

struct GenerateNodeOptions {
    int      line             = __builtin_LINE();
    Str      debugMessage     = "";
    int      minSubnodeCount  = 1;
    Opt<int> maxSubnodeCount  = std::nullopt;
    int      minAttachedCount = 0;
    int      maxAttachedCount = 0;
};

template <typename T>
Domain<T> GenerateEnumSet(Slice<T> const& values) {
    std::vector<T> items;
    for (auto const& it : values) { items.push_back(it); }
    return ElementOf<T>(items);
}

template <typename T>
Domain<T> GenerateEnumSet(IntSet<T> const& values) {
    std::vector<T> items;
    for (auto const& it : values) { items.push_back(it); }
    return ElementOf<T>(items);
}

Domain<OrgSemKind> GenerateKindSet(SemSet const& values) {
    std::vector<OrgSemKind> items;
    for (auto const& it : values) { items.push_back(it); }
    return ElementOf<OrgSemKind>(items);
}

struct GenerateNodeContext {
    immer::vector<GenerateNodePath> steps;
    immer::box<GenerateNodeOptions> opts;

    GenerateNodeContext operator&(GenerateNodePath other) const {
        return GenerateNodeContext{
            .steps = steps.push_back(other),
            .opts  = opts,
        };
    }

    GenerateNodeContext withoutSubnodes() const {
        return GenerateNodeContext{
            .steps = steps,
            .opts  = opts.update([](GenerateNodeOptions opts) {
                opts.minSubnodeCount = 0;
                opts.maxSubnodeCount = 0;
                return opts;
            })};
    }

    auto getSubnodeDomain(auto filler) const {
        if (opts->maxSubnodeCount) {
            return VectorOf(filler)
                .WithMinSize(opts->minSubnodeCount)
                .WithMaxSize(*opts->maxSubnodeCount);
        } else {
            return VectorOf(filler).WithMinSize(opts->minSubnodeCount);
        }
    }

    Domain<OrgSemKind> getDomain() const {
        SemSet result{sliceT<OrgSemKind>()};
        for (auto const& it : steps) {
            result.excl(it.kind);
            result.incl(it.expand);
            switch (it.kind) {
                case OrgSemKind::Document: {
                    result.excl(OrgSemKind::DocumentOptions);
                    result.excl(OrgSemKind::DocumentGroup);
                    break;
                }
                default: {
                }
            }
        }


        return GenerateKindSet(result);
    }
};


#define HasField(C, Field)                                                       \
    []() {                                                                       \
        return overloaded{                                                       \
            []<typename T>(int)                                                  \
                -> decltype(std::declval<T>().Field, void(), std::true_type()) { \
                return {};                                                       \
            },                                                                   \
            []<typename T>(...) { return std::false_type{}; }}                   \
            .template operator()<C>(0);                                          \
    }()

template <typename Node>
auto InitNode(CR<GenerateNodeContext> ctx) {
    json debug;
    to_json(
        debug,
        GenerateNodeDebug{
            .line    = ctx.opts.get().line,
            .message = ctx.opts.get().debugMessage,
        });

    auto tmp = Arbitrary<Node>() //
                   .WithFieldUnset("loc")
                   .WithStringField("debug", Just(debug.dump()))
                   .WithEnumField(
                       "staticKind",
                       Just(static_cast<int>(
                           proto_org_map<Node>::org_kind::staticKind)));


    if (!HasField(Node, attached)) {
        return std::move(tmp);
    } else {
        return std::move(tmp).WithRepeatedFieldSize(
            "attached",
            ctx.opts.get().minAttachedCount,
            ctx.opts.get().maxAttachedCount);
    }
}

template <typename Node>
auto InitLeaf(CR<GenerateNodeContext> ctx) {
    return InitNode<Node>(ctx) //
        .WithRepeatedFieldMaxSize("subnodes", 0);
}


template <typename Node>
Domain<Node> GenerateNode(CR<GenerateNodeContext> ctx);

#define _inst(__Kind)                                                     \
    template <>                                                           \
    Domain<prt::__Kind> GenerateNode(CR<GenerateNodeContext> ctx);

EACH_SEM_ORG_KIND(_inst)
#undef _inst

Domain<prt::AnyNode> GenerateAnyNode(
    Domain<OrgSemKind>      kind,
    CR<GenerateNodeContext> ctx);


Domain<OrgSemKind> GenerateKind(Vec<OrgSemKind> const& values) {
    return ElementOf<OrgSemKind>(values);
}

Domain<prt::AnyNode> MapAnyNodeKind(OrgSemKind kind);

Domain<std::vector<prt::AnyNode>> GenerateNodesKind(
    Domain<OrgSemKind>      kind,
    CR<GenerateNodeContext> ctx) {
    if (ctx.opts.get().maxSubnodeCount) {
        return VectorOf(GenerateAnyNode(kind, ctx))
            .WithMinSize(ctx.opts.get().minSubnodeCount)
            .WithMaxSize(ctx.opts.get().maxSubnodeCount.value());

    } else {
        return VectorOf(GenerateAnyNode(kind, ctx))
            .WithMinSize(ctx.opts.get().minSubnodeCount);
    }
}

auto AlwaysSet(auto domain) { return NonNull(OptionalOf(domain)); }

Domain<int> StaticCastEnum(auto domain) {
    return Map(
        [](auto value) -> int { return static_cast<int>(value); }, domain);
}


template <>
Domain<prt::Word> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitLeaf<prt::Word>(ctx) //
        .WithOptionalStringField("text", AlwaysSet(InRegexp(R"(\w+)")));
}

template <>
Domain<prt::BigIdent> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitLeaf<prt::BigIdent>(ctx) //
        .WithOptionalStringField(
            "text", AlwaysSet(InRegexp(R"([A-Z][_A-Z]+[A-Z])")));
}

template <>
Domain<prt::Space> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitLeaf<prt::Space>(ctx) //
        .WithOptionalStringField(
            "text", AlwaysSet(StringOf(ElementOf({' '})).WithMinSize(1)));
}

Domain<prt::UserTime> GenerateUserTime() {
    return Map(
        [](CR<UserTime> time) -> prt::UserTime {
            prt::UserTime result;
            proto_serde<prt::UserTime, UserTime>::write(&result, time);
            return result;
        },
        StructOf<UserTime>(
            Arbitrary<absl::Time>(),
            Just<absl::TimeZone>(absl::UTCTimeZone()),
            GenerateEnumSet<UserTime::Alignment>(
                sliceT<UserTime::Alignment>())));
}

template <>
Domain<prt::FileTarget> GenerateNode<prt::FileTarget>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::FileTarget>(ctx);
}
template <>
Domain<prt::SubtreeLog> GenerateNode<prt::SubtreeLog>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::SubtreeLog>(ctx);
}
template <>
Domain<prt::DocumentGroup> GenerateNode<prt::DocumentGroup>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::DocumentGroup>(ctx);
}
template <>
Domain<prt::Monospace> GenerateNode<prt::Monospace>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Monospace>(ctx);
}
template <>
Domain<prt::Completion> GenerateNode<prt::Completion>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Completion>(ctx);
}
template <>
Domain<prt::Code> GenerateNode<prt::Code>(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Code>(ctx);
}
template <>
Domain<prt::StmtList> GenerateNode<prt::StmtList>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::StmtList>(ctx);
}
template <>
Domain<prt::Punctuation> GenerateNode<prt::Punctuation>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Punctuation>(ctx);
}
template <>
Domain<prt::Export> GenerateNode<prt::Export>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Export>(ctx);
}
template <>
Domain<prt::Table> GenerateNode<prt::Table>(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Table>(ctx);
}
template <>
Domain<prt::CmdArgument> GenerateNode<prt::CmdArgument>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::CmdArgument>(ctx);
}
template <>
Domain<prt::Footnote> GenerateNode<prt::Footnote>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Footnote>(ctx);
}
template <>
Domain<prt::Row> GenerateNode<prt::Row>(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Row>(ctx);
}
template <>
Domain<prt::InlineMath> GenerateNode<prt::InlineMath>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::InlineMath>(ctx);
}
template <>
Domain<prt::Escaped> GenerateNode<prt::Escaped>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Escaped>(ctx);
}
template <>
Domain<prt::AdmonitionBlock> GenerateNode<prt::AdmonitionBlock>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::AdmonitionBlock>(ctx);
}
template <>
Domain<prt::Include> GenerateNode<prt::Include>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Include>(ctx);
}
template <>
Domain<prt::Empty> GenerateNode<prt::Empty>(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Empty>(ctx);
}
template <>
Domain<prt::AtMention> GenerateNode<prt::AtMention>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::AtMention>(ctx);
}
template <>
Domain<prt::List> GenerateNode<prt::List>(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::List>(ctx);
}
template <>
Domain<prt::Placeholder> GenerateNode<prt::Placeholder>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Placeholder>(ctx);
}
template <>
Domain<prt::HashTag> GenerateNode<prt::HashTag>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::HashTag>(ctx);
}
template <>
Domain<prt::TextSeparator> GenerateNode<prt::TextSeparator>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::TextSeparator>(ctx);
}
template <>
Domain<prt::Example> GenerateNode<prt::Example>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Example>(ctx);
}
template <>
Domain<prt::ParseError> GenerateNode<prt::ParseError>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::ParseError>(ctx);
}
template <>
Domain<prt::ListItem> GenerateNode<prt::ListItem>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::ListItem>(ctx);
}
template <>
Domain<prt::MarkQuote> GenerateNode<prt::MarkQuote>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::MarkQuote>(ctx);
}
template <>
Domain<prt::Par> GenerateNode<prt::Par>(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Par>(ctx);
}
template <>
Domain<prt::CmdArguments> GenerateNode<prt::CmdArguments>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::CmdArguments>(ctx);
}
template <>
Domain<prt::Link> GenerateNode<prt::Link>(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Link>(ctx);
}
template <>
Domain<prt::CommandGroup> GenerateNode<prt::CommandGroup>(
    CR<GenerateNodeContext> ctx) {
    return InitNode<prt::CommandGroup>(ctx);
}

template <>
Domain<prt::Time> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Time>(ctx.withoutSubnodes()) //
        .WithProtobufField(
            "repeat",
            Arbitrary<prt::Time::Repeat>()
                .WithInt32Field("count", InRange(0, 1200))
                .WithOptionalEnumField(
                    "period",
                    AlwaysSet(          //
                        StaticCastEnum( //
                            GenerateEnumSet(
                                sliceT<sem::Time::Repeat::Period>()))))
                .WithOptionalEnumField(
                    "mode",
                    AlwaysSet(          //
                        StaticCastEnum( //
                            GenerateEnumSet(
                                sliceT<sem::Time::Repeat::Mode>())))))
        .WithProtobufField(
            "static",
            Arbitrary<prt::Time::Static>().WithProtobufField(
                "time", GenerateUserTime()));
}


template <>
Domain<prt::Newline> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitLeaf<prt::Newline>(ctx) //
        .WithOptionalStringField(
            "text", AlwaysSet(StringOf(Just('\n')).WithSize(1)));
}

auto LowerIdent() { return StringOf(LowerChar()).WithMinSize(3); }

template <>
Domain<prt::RawText> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitLeaf<prt::RawText>(ctx) //
        .WithStringField("text", InRegexp(R"([a-zA-Z0-9_]+)"));
}

template <>
Domain<prt::Symbol> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Symbol>(ctx) //
        .WithOptionalStringField("name", AlwaysSet(LowerIdent()))
        .WithRepeatedProtobufField(
            "positional",
            VectorOf( //
                GenerateNode<prt::Paragraph>(ctx))
                .WithMaxSize(3))
        .WithRepeatedProtobufField(
            "parameters",
            VectorOf( //
                Arbitrary<orgproto::Symbol::Param>()
                    .WithStringField("key", LowerIdent())
                    .WithOptionalStringField(
                        "value", AlwaysSet(LowerIdent())))
                .WithMaxSize(4))
        .WithRepeatedFieldMaxSize("subnodes", 0);
}

template <>
Domain<prt::Subtree> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Subtree>(ctx) //
        .WithOptionalStringField(
            "treeid", OptionalOf(StringOf(LowerChar()).WithMinSize(12)))
        .WithOptionalStringField(
            "todo", OptionalOf(StringOf(UpperChar()).WithMinSize(3)))
        .WithProtobufField(
            "completion", GenerateNode<prt::Completion>(ctx))
        .WithProtobufField(
            "description", GenerateNode<prt::Paragraph>(ctx))
        .WithProtobufField("closed", GenerateNode<prt::Time>(ctx))
        .WithProtobufField("scheduled", GenerateNode<prt::Time>(ctx))
        .WithProtobufField("deadline", GenerateNode<prt::Time>(ctx))
        .WithRepeatedProtobufField(
            "subnodes", VectorOf(GenerateAnyNode(ctx.getDomain(), ctx)))
        //
        ;
}

template <>
Domain<prt::Macro> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Macro>(ctx.withoutSubnodes()) //
        ;
}

template <typename T>
auto VectorOfN(CR<T> values, int size) {
    return VectorOf(values).WithMinSize(size).WithMaxSize(size);
}

Domain<std::vector<prt::AnyNode>> GenerateSpaceSeparatedNodes(
    CR<GenerateNodeContext> ctx) {
    return FlatMap(
        [ctx](int n) -> Domain<std::vector<prt::AnyNode>> {
            return VectorOfN(
                FlatMap(
                    [ctx, index = 0](int) -> Domain<prt::AnyNode> {
                        int start = index;
                        ++const_cast<int&>(index);
                        if (start % 2 == 0) {
                            return GenerateAnyNode(ctx.getDomain(), ctx);
                        } else {
                            return GenerateAnyNode(
                                GenerateKind({osk::Space}), ctx);
                        }
                    },
                    Just(0)),
                2 * n + 1)
                //
                ;
        },
        InRange(
            ctx.opts.get().minSubnodeCount,
            ctx.opts.get().maxSubnodeCount
                ? ctx.opts.get().maxSubnodeCount.value()
                : 16));
}

template <>
Domain<prt::Center> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Center>(ctx).WithRepeatedProtobufField(
        "subnodes",
        VectorOf(GenerateNode<prt::Paragraph>(ctx)).WithMinSize(1));
}

template <>
Domain<prt::Quote> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Quote>(ctx).WithRepeatedProtobufField(
        "subnodes",
        VectorOf(GenerateNode<prt::Paragraph>(ctx)).WithMinSize(1));
}

template <>
Domain<prt::TimeRange> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::TimeRange>(ctx.withoutSubnodes())
        .WithOptionalProtobufField(
            "from", AlwaysSet(GenerateNode<prt::Time>(ctx)))
        .WithOptionalProtobufField(
            "to", AlwaysSet(GenerateNode<prt::Time>(ctx)));
}

template <>
Domain<prt::Bold> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Bold>(ctx).WithRepeatedProtobufField(
        "subnodes", GenerateSpaceSeparatedNodes(ctx));
}

template <>
Domain<prt::Verbatim> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Verbatim>(ctx).WithRepeatedProtobufField(
        "subnodes", GenerateSpaceSeparatedNodes(ctx));
}

template <>
Domain<prt::Italic> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Italic>(ctx).WithRepeatedProtobufField(
        "subnodes", GenerateSpaceSeparatedNodes(ctx));
}

template <>
Domain<prt::Underline> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Underline>(ctx).WithRepeatedProtobufField(
        "subnodes", GenerateSpaceSeparatedNodes(ctx));
}

template <>
Domain<prt::Strike> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Strike>(ctx).WithRepeatedProtobufField(
        "subnodes", GenerateSpaceSeparatedNodes(ctx));
}

template <>
Domain<prt::Paragraph> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Paragraph>(ctx).WithRepeatedProtobufField(
        "subnodes", GenerateSpaceSeparatedNodes(ctx));
}

template <>
Domain<prt::DocumentOptions> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitLeaf<prt::DocumentOptions>(ctx);
}

template <typename T>
fuzztest::Domain<std::optional<T>> ProtoOptionalOf(
    const fuzztest::Domain<T>& messageDomain) {
    return fuzztest::OneOf(
        NullOpt<T>(),
        Map([](T value) -> std::optional<T> { return std::move(value); },
            std::move(messageDomain)));
}

template <>
Domain<prt::Document> GenerateNode(CR<GenerateNodeContext> ctx) {
    return InitNode<prt::Document>(ctx) //
        .WithRepeatedFieldMaxSize("idTable", 0)
        .WithRepeatedFieldMaxSize("nameTable", 0)
        .WithRepeatedFieldMaxSize("footnoteTable", 0)
        .WithRepeatedFieldMaxSize("anchorTable", 0)
        .WithProtobufField("title", GenerateNode<prt::Paragraph>(ctx))
        .WithProtobufField("author", GenerateNode<prt::Paragraph>(ctx))
        .WithProtobufField("creator", GenerateNode<prt::Paragraph>(ctx))
        .WithProtobufField("email", GenerateNode<prt::RawText>(ctx))
        .WithProtobufField(
            "options", GenerateNode<prt::DocumentOptions>(ctx))
        .WithStringField("language", StringOf(LowerChar()))
        .WithStringField("exportFileName", StringOf(PrintableAsciiChar()))
        .WithRepeatedProtobufField(
            "subnodes",
            GenerateNodesKind(
                GenerateKind({
                    osk::Paragraph,
                }),
                ctx));
}

Domain<prt::AnyNode> MapAnyNodeKind(
    OrgSemKind              kind,
    CR<GenerateNodeContext> ctx) {
    switch (kind) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind:                                              \
        return Map(                                                       \
            ConvertAnyNode<prt::__Kind>, GenerateNode<prt::__Kind>(ctx));

        EACH_SEM_ORG_KIND(_case)
#undef _case
    }
}

Domain<prt::AnyNode> GenerateAnyNode(
    Domain<OrgSemKind>      domain,
    CR<GenerateNodeContext> ctx) {
    return FlatMap(
        [ctx](OrgSemKind it) { return MapAnyNodeKind(it, ctx); }, domain);
}

Domain<prt::AnyNode> GenerateDocumentNode(CR<GenerateNodeContext> ctx) {
    return GenerateAnyNodeWrapper(GenerateNode<prt::Document>(ctx));
}

auto seedCorpus = __CURRENT_FILE_DIR__ / "tOrgFuzzSeeds.yaml";
std::vector<std::tuple<prt::AnyNode>> LoadFuzzSeeds() {
    yaml content = YAML::LoadFile(seedCorpus.native());
    std::vector<std::tuple<prt::AnyNode>> result;
    for (auto const& it : content) {
        prt::AnyNode out;
        gpb::TextFormat::ParseFromString(it.as<std::string>(), &out);
        result.push_back({out});
    }
    return result;
}

TEST(OrgParseFuzz, CheckDeterministic) {
    for (auto const& it : LoadFuzzSeeds()) {
        CheckAnyNodeFail(std::get<0>(it));
    }
}

FUZZ_TEST(OrgParseFuzz, CheckAnyNodeFail)
    //
    .WithDomains(GenerateDocumentNode(GenerateNodeContext{}))
    // .WithSeeds(LoadFuzzSeeds())
    //
    ;
