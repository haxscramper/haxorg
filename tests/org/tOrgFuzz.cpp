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
        &generated_context, node, generated_node);

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

struct GenerateNodeOptions {
    bool        withAttached              = false;
    int         line                      = __builtin_LINE();
    Str         debugMessage              = "";
    Opt<SemSet> allowedSubnodes           = std::nullopt;
    Opt<SemSet> allowedTransitiveSubnodes = std::nullopt;
    int         minSubnodeCount           = 1;
    Opt<int>    maxSubnodeCount           = std::nullopt;

    Opt<SemSet> withoutTransitive(SemSet discarded) {
        Opt<SemSet> result = allowedTransitiveSubnodes;
        if (result) {
            for (auto const& it : discarded) { result.value().excl(it); }
        }
        return result;
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
auto InitNode(CR<GenerateNodeOptions> opts) {
    json debug;
    to_json(
        debug,
        GenerateNodeDebug{
            .line    = opts.line,
            .message = opts.debugMessage,
        });

    auto tmp = Arbitrary<Node>() //
                   .WithFieldUnset("loc")
                   .WithStringField("debug", Just(debug.dump()))
                   .WithEnumField(
                       "staticKind",
                       Just(static_cast<int>(
                           proto_org_map<Node>::org_kind::staticKind)));


    if (opts.withAttached || !HasField(Node, attached)) {
        return std::move(tmp);
    } else {
        return std::move(tmp).WithRepeatedFieldMaxSize("attached", 0);
    }
}

template <typename Node>
auto InitLeaf(CR<GenerateNodeOptions> opts) {
    return InitNode<Node>(opts) //
        .WithRepeatedFieldMaxSize("subnodes", 0);
}


template <typename Node>
Domain<Node> GenerateNode(CR<GenerateNodeOptions> opts) {
    return InitNode<Node>(opts) //
        ;
}

Domain<prt::AnyNode> GenerateAnyNode(
    Domain<OrgSemKind>      kind,
    CR<GenerateNodeOptions> opts);

Domain<OrgSemKind> GenerateKindSet(SemSet const& values) {
    std::vector<OrgSemKind> items;
    for (auto const& it : values) { items.push_back(it); }
    return ElementOf<OrgSemKind>(items);
}

Domain<OrgSemKind> GenerateKind(Vec<OrgSemKind> const& values) {
    return ElementOf<OrgSemKind>(values);
}

Domain<prt::AnyNode> MapAnyNodeKind(OrgSemKind kind);

Domain<std::vector<prt::AnyNode>> GenerateNodesKind(
    Domain<OrgSemKind>      kind,
    CR<GenerateNodeOptions> opts) {
    if (opts.maxSubnodeCount) {
        return VectorOf(GenerateAnyNode(kind, opts))
            .WithMinSize(opts.minSubnodeCount)
            .WithMaxSize(opts.maxSubnodeCount.value());

    } else {
        return VectorOf(GenerateAnyNode(kind, opts))
            .WithMinSize(opts.minSubnodeCount);
    }
}

template <>
Domain<prt::Word> GenerateNode(CR<GenerateNodeOptions> opts) {
    return InitLeaf<prt::Word>(opts) //
        .WithOptionalStringField(
            "text", NonNull(OptionalOf(InRegexp(R"(\w+)"))));
}

template <>
Domain<prt::Space> GenerateNode(CR<GenerateNodeOptions> opts) {
    return InitLeaf<prt::Space>(opts) //
        .WithOptionalStringField(
            "text",
            NonNull(
                OptionalOf(StringOf(ElementOf({' '})).WithMinSize(1))));
}

template <>
Domain<prt::RawText> GenerateNode(CR<GenerateNodeOptions> opts) {
    return InitLeaf<prt::RawText>(opts) //
        .WithStringField("text", InRegexp(R"([a-zA-Z0-9_]+)"));
}

template <typename T>
auto VectorOfN(CR<T> values, int size) {
    return VectorOf(values).WithMinSize(size).WithMaxSize(size);
}

Domain<std::vector<prt::AnyNode>> GenerateSpaceSeparatedNodes(
    CR<GenerateNodeOptions> opts) {
    return FlatMap(
        [opts](int n) -> Domain<std::vector<prt::AnyNode>> {
            return VectorOfN(
                FlatMap(
                    [opts, index = 0](int) -> Domain<prt::AnyNode> {
                        int start = index;
                        ++const_cast<int&>(index);
                        if (start % 2 == 0) {
                            return GenerateAnyNode(
                                GenerateKindSet(
                                    opts.allowedSubnodes.value()),
                                opts);
                        } else {
                            return GenerateAnyNode(
                                GenerateKind({osk::Space}), opts);
                        }
                    },
                    Just(0)),
                2 * n + 1)
                //
                ;
        },
        InRange(
            opts.minSubnodeCount,
            opts.maxSubnodeCount ? opts.maxSubnodeCount.value() : 16));
}


Domain<std::vector<prt::AnyNode>> GenerateParagraphDomain(
    CR<GenerateNodeOptions> opts) {
    SemSet paragraphContent = SemSet{
        osk::Word,
        osk::Bold,
        osk::Italic,
        osk::Verbatim,
        osk::Punctuation,
        osk::Link,
        osk::Monospace,
        osk::Time,
        osk::TimeRange,
    };

    return GenerateSpaceSeparatedNodes({
        .allowedSubnodes           = paragraphContent,
        .allowedTransitiveSubnodes = opts.allowedTransitiveSubnodes
                                       ? opts.allowedTransitiveSubnodes
                                             .value()
                                       : paragraphContent,
    });
}

template <>
Domain<prt::Paragraph> GenerateNode(CR<GenerateNodeOptions> opts) {
    return InitNode<prt::Paragraph>(opts) //
        .WithRepeatedProtobufField(
            "subnodes", GenerateParagraphDomain(opts));
}

template <>
Domain<prt::DocumentOptions> GenerateNode(CR<GenerateNodeOptions> opts) {
    return InitLeaf<prt::DocumentOptions>(opts);
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
Domain<prt::Document> GenerateNode(CR<GenerateNodeOptions> opts) {
    return InitNode<prt::Document>(GenerateNodeOptions{}) //
        .WithRepeatedFieldMaxSize("idTable", 0)
        .WithRepeatedFieldMaxSize("nameTable", 0)
        .WithRepeatedFieldMaxSize("footnoteTable", 0)
        .WithRepeatedFieldMaxSize("anchorTable", 0)
        .WithProtobufField(
            "title", GenerateNode<prt::Paragraph>(GenerateNodeOptions{}))
        .WithProtobufField(
            "author", GenerateNode<prt::Paragraph>(GenerateNodeOptions{}))
        .WithProtobufField(
            "creator", GenerateNode<prt::Paragraph>(GenerateNodeOptions{}))
        .WithProtobufField(
            "email", GenerateNode<prt::RawText>(GenerateNodeOptions{}))
        .WithProtobufField(
            "options",
            GenerateNode<prt::DocumentOptions>(GenerateNodeOptions{}))
        .WithStringField("language", StringOf(LowerChar()))
        .WithStringField("exportFileName", StringOf(PrintableAsciiChar()))
        .WithRepeatedProtobufField(
            "subnodes",
            GenerateNodesKind(
                GenerateKind({
                    osk::Paragraph,
                }),
                {.minSubnodeCount = 5}));
}

Domain<prt::AnyNode> MapAnyNodeKind(
    OrgSemKind              kind,
    CR<GenerateNodeOptions> opts) {
    switch (kind) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind:                                              \
        return Map(                                                       \
            ConvertAnyNode<prt::__Kind>,                                  \
            GenerateNode<prt::__Kind>(opts));

        EACH_SEM_ORG_KIND(_case)
#undef _case
    }
}

Domain<prt::AnyNode> GenerateAnyNode(
    Domain<OrgSemKind>      domain,
    CR<GenerateNodeOptions> opts) {
    return FlatMap(
        [opts](OrgSemKind it) { return MapAnyNodeKind(it, opts); },
        domain);
}

Domain<prt::AnyNode> GenerateDocumentNode(
    CR<GenerateNodeOptions> opts = GenerateNodeOptions{}) {
    return GenerateAnyNodeWrapper(GenerateNode<prt::Document>(opts));
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
    .WithDomains(GenerateDocumentNode())
    // .WithSeeds(LoadFuzzSeeds())
    //
    ;
