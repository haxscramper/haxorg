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

        if (!field->is_repeated()
            && !reflection->HasField(message, field)) {
            continue; // Skip non-set fields
        }

        oss << indent << "  " << field->name() << ": ";

        if (field->cpp_type()
            == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE) {
            if (field->is_repeated()) {
                int count = reflection->FieldSize(message, field);
                oss << "[\n";
                for (int j = 0; j < count; ++j) {
                    const gpb::Message& subMessage = //
                        reflection->GetRepeatedMessage(message, field, j);
                    PrintMessageWithTypeName(subMessage, oss, depth + 2);
                }
                oss << indent << "  "
                    << "]\n";
            } else {
                const gpb::Message& subMessage = //
                    reflection->GetMessage(message, field);
                PrintMessageWithTypeName(subMessage, oss, depth + 1);
            }
        } else {
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

    return anyNode;
}

template <typename NodeType>
Domain<prt::AnyNode> GenerateAnyNodeWrapper(
    Domain<NodeType> nodeGenerator) {
    return Map(
        ConvertAnyNode<NodeType>,
        nodeGenerator // Pass the subnode generator
    );
}

struct GenerateNodeOptions {
    bool withAttached = false;
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
auto InitNode(CR<GenerateNodeOptions> opts = GenerateNodeOptions{}) {
    auto tmp = Arbitrary<Node>() //
                   .WithFieldUnset("loc")
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
auto InitLeaf(CR<GenerateNodeOptions> opts = GenerateNodeOptions{}) {
    return InitNode<Node>(opts).WithRepeatedFieldMaxSize("subnodes", 0);
}


template <typename Node>
Domain<Node> GenerateNode(
    CR<GenerateNodeOptions> opts = GenerateNodeOptions{}) {
    return InitNode<Node>(opts) //
        ;
}

Domain<prt::AnyNode> GenerateAnyNode(Domain<OrgSemKind> kind);

Domain<OrgSemKind> GenerateKindSet(SemSet const& values) {
    std::vector<OrgSemKind> items;
    for (auto const& it : values) { items.push_back(it); }
    return ElementOf<OrgSemKind>(items);
}

Domain<OrgSemKind> GenerateKind(Vec<OrgSemKind> const& values) {
    return ElementOf<OrgSemKind>(values);
}

prt::AnyNode MapAnyNodeKind(OrgSemKind kind);

Domain<std::vector<prt::AnyNode>> GenerateNodesKind(
    Domain<OrgSemKind> kind,
    int                min,
    int                max = -1) {
    if (max == -1) {
        return VectorOf(GenerateAnyNode(kind)).WithMinSize(min);
    } else {
        return VectorOf(GenerateAnyNode(kind))
            .WithMinSize(min)
            .WithMaxSize(max);
    }
}

template <>
Domain<prt::Word> GenerateNode(CR<GenerateNodeOptions> opts) {
    return InitLeaf<prt::Word>(opts) //
        .WithStringField("text", InRegexp(R"(\w+)"));
}

template <>
Domain<prt::RawText> GenerateNode(CR<GenerateNodeOptions> opts) {
    return InitLeaf<prt::RawText>(opts) //
        .WithStringField("text", InRegexp(R"([a-zA-Z0-9_]+)"));
}

template <>
Domain<prt::Paragraph> GenerateNode(CR<GenerateNodeOptions> opts) {
    return InitNode<prt::Paragraph>(opts) //
        .WithRepeatedProtobufField(
            "subnodes",
            GenerateNodesKind(
                GenerateKind({
                    osk::Word,
                }),
                3));
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
    return InitNode<prt::Document>() //
        .WithRepeatedFieldMaxSize("idTable", 0)
        .WithRepeatedFieldMaxSize("nameTable", 0)
        .WithRepeatedFieldMaxSize("footnoteTable", 0)
        .WithRepeatedFieldMaxSize("anchorTable", 0)
        // DOC explain why this node, despite being an `optional Paragraph`
        // is assigned with a non-optional domain.
        .WithProtobufField("title", GenerateNode<prt::Paragraph>())
        .WithProtobufField("author", GenerateNode<prt::Paragraph>())
        .WithProtobufField("creator", GenerateNode<prt::Paragraph>())
        .WithProtobufField("email", GenerateNode<prt::RawText>())
        .WithProtobufField("options", GenerateNode<prt::DocumentOptions>())
        .WithStringField("language", StringOf(LowerChar()))
        .WithStringField("exportFileName", StringOf(PrintableAsciiChar()))
        .WithRepeatedProtobufField(
            "subnodes",
            GenerateNodesKind(
                GenerateKind({
                    osk::Paragraph,
                }),
                1));
}

prt::AnyNode MapAnyNodeKind(OrgSemKind kind) {
    switch (kind) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind:                                              \
        return ConvertAnyNode(GenerateNode<prt::__Kind>());

        EACH_SEM_ORG_KIND(_case)
#undef _case
    }
}

Domain<prt::AnyNode> GenerateAnyNode(Domain<OrgSemKind> domain) {
    return Map(MapAnyNodeKind, domain);
}

Domain<prt::AnyNode> GenerateAnyNode() {
    return GenerateAnyNodeWrapper(GenerateNode<prt::Document>());
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
    .WithDomains(GenerateAnyNode())
    // .WithSeeds(LoadFuzzSeeds())
    //
    ;
