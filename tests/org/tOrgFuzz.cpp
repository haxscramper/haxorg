#include <gtest/gtest.h>
#include <fuzztest/fuzztest.h>
#include <absl/log/log.h>
#include <sem/SemOrgSerde.hpp>
#include <sem/SemOrgFormat.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <hstd/stdlib/Yaml.hpp>
#include <google/protobuf/text_format.h>
#include <sem/SemOrgSerdeDeclarations.hpp>

namespace prt = orgproto;
using osk     = OrgSemKind;
using namespace fuzztest;

void CheckAnyNodeFail(prt::AnyNode const& node) {
    {
        std::string textFormatStr;
        google::protobuf::TextFormat::PrintToString(node, &textFormatStr);
        writeFile("/tmp/protobuf_dump.txt", textFormatStr);
        LOG(INFO) << textFormatStr;
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

template <typename Node>
auto InitNode() {
    return Arbitrary<Node>() //
        .WithFieldUnset("loc")
        .WithFieldUnset("staticKind");
}

template <typename Node>
auto InitLeaf() {
    return InitNode<Node>().WithRepeatedFieldMaxSize("subnodes", 0);
}

template <typename Node>
Domain<Node> GenerateNode() {
    return InitNode<Node>() //
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
Domain<prt::Word> GenerateNode() {
    return InitLeaf<prt::Word>() //
        .WithStringField("text", InRegexp(R"(\w+)"));
}

template <>
Domain<prt::RawText> GenerateNode() {
    return InitLeaf<prt::RawText>() //
        .WithStringField("text", InRegexp(R"([a-zA-Z0-9_]+)"));
}

template <>
Domain<prt::Paragraph> GenerateNode() {
    return InitNode<prt::Paragraph>() //
        .WithRepeatedProtobufField(
            "subnodes",
            GenerateNodesKind(
                GenerateKind({
                    osk::Word,
                }),
                1));
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
Domain<prt::Document> GenerateNode() {
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
        google::protobuf::TextFormat::ParseFromString(
            it.as<std::string>(), &out);
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
