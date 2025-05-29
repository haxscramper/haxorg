#include "tOrgTestCommon.hpp"

#include <haxorg/sem/SemOrgCereal.hpp>

using namespace org::parse;
using namespace org::test;

Str getSelfTest(org::imm::ImmAdapter const& it) {
    return fmt(
        R"(
auto {0} = {1};
EXPECT_EQ({0}->getKind(), OrgSemKind::{2});
)",
        it.id,
        it.selfSelect(),
        it->getKind());
}

TEST(TestFiles, OrgCerealSerdeRoundtrip) {
    auto node = org::parseFile(
        __CURRENT_FILE_DIR__ / "corpus/org/py_validated_all.org",
        // "/home/haxscramper/tmp/doc1.org",
        OrgParseParameters::shared());
    auto start_context = org::imm::ImmAstContext::init_start_context();
    start_context->addRoot(node);

    std::string binary_buffer = org::imm::serializeToText(start_context);
    writeFile(
        "/tmp/msgpack_first_dump.json",
        org::imm::serializeFromTextToTreeDump(binary_buffer));

    writeFile("/tmp/msgpack_dump.bin", binary_buffer);
    auto final_context = org::imm::ImmAstContext::init_start_context();
    org::imm::serializeFromText(binary_buffer, final_context);

    writeFile(
        "/tmp/msgpack_second_dump.json",
        org::imm::serializeFromTextToTreeDump(
            org::imm::serializeToText(final_context)));

    Vec<compare_report> out;

    reporting_comparator<org::imm::ImmAstStore>::compare(
        *start_context->store, *final_context->store, out, {});

    show_compare_reports(out);
}

TEST(TestFiles, AllNodeSerdeRoundtrip) {
#if ORG_DEPS_USE_PROTOBUF
    std::string file
        = (__CURRENT_FILE_DIR__ / "corpus/org/py_validated_all.org");
    MockFull    p{false, false};
    std::string source = readFile(fs::path(file));
    p.run(source);

    sem::OrgConverter converter{};
    sem::SemId        write_node = converter
                                .convertDocument(
                                    OrgAdapter(&p.nodes, OrgId(0)))
                                .value();
    orgproto::AnyNode result;
    org::algo::proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(
        &result, write_node);

    google::protobuf::util::JsonPrintOptions options;
    options.add_whitespace = true;

    {
        std::string proto_write_json;
        (void)google::protobuf::util::MessageToJsonString(
            result, &proto_write_json, options);

        writeFile("/tmp/proto_write.json", proto_write_json);
    }

    sem::SemId read_node = sem::SemId<sem::Org>::Nil();
    org::algo::proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::read(
        result,
        org::algo::proto_write_accessor<sem::SemId<sem::Org>>::for_ref(
            read_node));

    {
        orgproto::AnyNode result2;
        org::algo::proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::
            write(&result2, read_node);
        std::string proto_read_json;
        (void)google::protobuf::util::MessageToJsonString(
            result2, &proto_read_json, options);

        writeFile("/tmp/proto_read.json", proto_read_json);
    }

    json write_json = org::algo::ExporterJson{}.evalTop(write_node);
    json read_json  = org::algo::ExporterJson{}.evalTop(read_node);

    writeFile("/tmp/node_write.json", write_json.dump(2));
    writeFile("/tmp/node_read.json", read_json.dump(2));

    Vec<compare_report> out;

    reporting_comparator<sem::SemId<sem::Org>>::compare(
        write_node, read_node, out, {});

    show_compare_reports(out);
#endif
}

TEST(TestFiles, AllNodeCoverage) {
    GTEST_SKIP();
    std::string file
        = (__CURRENT_FILE_DIR__ / "corpus/org/py_validated_all.org");
    MockFull    p{false, false};
    std::string source = readFile(fs::path(file));
    p.run(source);

    SemSet            foundNodes;
    sem::OrgConverter converter{};
    sem::SemId        node = converter
                          .convertDocument(OrgAdapter(&p.nodes, OrgId(0)))
                          .value();

    using osk = OrgSemKind;
    SemSet wipNotParseable{
        osk::CmdInclude,
        osk::DocumentGroup,
        osk::Empty,
        osk::Row,
        osk::Table,
        osk::BlockQuote,
        osk::MarkQuote,
        osk::StmtList,
        osk::BlockAdmonition,
        osk::FileTarget,
        osk::BlockCode,
        osk::SubtreeLog,
        osk::Escaped,
        osk::Par,
    };

    if (!(foundNodes & wipNotParseable).empty()) {
        FAIL() << "Hack plug with fake found nodes covers too much:"
               << fmt1(foundNodes & wipNotParseable);
    }

    foundNodes.incl(wipNotParseable);

    SemSet expectedNodes;
    for (auto const& value : sliceT<OrgSemKind>()) {
        expectedNodes.incl(value);
    }

    if (expectedNodes.size() != foundNodes.size()) {
        Vec<OrgSemKind> diff;
        for (auto const& v : expectedNodes - foundNodes) {
            diff.push_back(v);
        }
        std::string missing = join(
            ", ", map(diff, [](OrgSemKind value) { return fmt1(value); }));
        FAIL() << "'all.org' test file missing node coverage for "
               << diff.size() << " nodes: '" << missing << "'";
    }
}

TEST(SimpleNodeConversion, LCSCompile) {
    Vec<int> first{1, 2, 3};
    Vec<int> second{1, 2, 3};
    auto     res = longestCommonSubsequence<int>(
        first,
        second,
        [](CR<int> lhs, CR<int> rhs) { return lhs == rhs; },
        [](CR<int> lhs, CR<int> rhs) {
            if (lhs == rhs) {
                return 1;
            } else {
                return 0;
            }
        });
    // You may want to add test conditions to check the results.
}

TEST(SimpleNodeConversion, MyersDiffCompile) {
    Vec<int> first{1, 2, 3};
    Vec<int> second{1, 2, 3};
    auto res = myersDiff<int>(first, second, [](CR<int> lhs, CR<int> rhs) {
        return lhs == rhs;
    });
    // You may want to add test conditions to check the results.
}
