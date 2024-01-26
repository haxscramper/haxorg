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
using namespace fuzztest;

void CheckAnyNodeFail(prt::AnyNode const& node) {
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
Domain<prt::AnyNode> GenerateAnyNodeWrapper(
    Domain<NodeType> nodeGenerator) {
    return ConstructorOf<prt::AnyNode>(
        [nodeGenerator](NodeType subNode) -> prt::AnyNode {
            prt::AnyNode anyNode;

        // Use the macro to set the appropriate field on AnyNode
#define _case(_fieldEnum, _field, _Kind)                                  \
    if constexpr (std::is_same<NodeType, prt::_Kind>::value) {            \
        *anyNode.mutable_##_field() = subNode;                            \
    }

            EACH_ANY_NODE_PROTO_FIELD(_case)
#undef _case

            return anyNode;
        },
        nodeGenerator // Pass the subnode generator
    );
}

Domain<prt::Document> GenerateDocumentSubnode() {

}

Domain<prt::AnyNode> ArbitraryNodeDomain() {
    return GenerateAnyNodeWrapper(GenerateDocumentSubnode());
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
    .WithDomains(ArbitraryNodeDomain())
    .WithSeeds(LoadFuzzSeeds())
    //
    ;
