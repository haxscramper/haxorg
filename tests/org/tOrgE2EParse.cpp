#include "../common.hpp"
#include "org_parse_aux.hpp"
#include <gtest/gtest.h>

#include <sem/semdatastream.hpp>

#include <parse/OrgParser.hpp>
#include <parse/OrgTokenizer.hpp>
#include <gtest/gtest.h>

#include <lexbase/AstSpec.hpp>
#include <lexbase/AstDiff.hpp>
#include <lexbase/NodeTest.hpp>

import std.stdlib.diffs;

import std.stdlib.Filesystem;

template <
    /// Node kind
    typename N,
    /// Token kind
    typename K,
    /// Node value kind
    typename Val>
diff::ComparisonOptions<NodeId<N, K, Val>, Val> nodeAdapterComparisonOptions(
    /// Map DOD node ID to the node object
    Func<CR<Node<N, K, Val>>(NodeId<N, K, Val>)> getNode,
    /// Map DOD node value from node object
    Func<CR<Val>(NodeId<N, K, Val>)> getValue) {
    return {
        .getNodeValueImpl =
            [getValue](NodeId<N, K, Val> id) { return getValue(id); },
        .getNodeKindImpl =
            [getNode](NodeId<N, K, Val> id) {
                return static_cast<int>(getNode(id).kind);
            }};
}


TEST(TestFiles, AllNodeCoverage) {
    std::string file = (__CURRENT_FILE_DIR__ / "corpus/org/all.org");
    MockFull    p{false, false};
    std::string source = readFile(fs::path(file));
    p.run(source);

    SemSet            foundNodes;
    sem::ContextStore context;
    sem::OrgConverter converter{&context};
    sem::SemId node = converter.toDocument(OrgAdapter(&p.nodes, OrgId(0)));
    context.eachNode([&](sem::OrgVariant const& var) {
        std::visit(
            [&](auto const& id) { foundNodes.incl(id->getKind()); }, var);
    });

    using osk = OrgSemKind;
    SemSet wipNotParseable{
        osk::Include,
        osk::DocumentGroup,
        osk::Empty,
        osk::Row,
        osk::Table,
        osk::Completion,
        osk::CommandGroup,
        osk::Quote,
        osk::MarkQuote,
        osk::StmtList,
        osk::AdmonitionBlock,
        osk::FileTarget,
        osk::ParseError,
        osk::Code,
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

template <typename T>
int field_count() {
    int result = 0;
    for_each_field_with_bases<T>([&](auto const&) { ++result; });
    return result;
}


#define __eq(__Type)                                                      \
    bool operator==(CR<__Type> lhs, CR<__Type> rhs) {                     \
        return equal_on_all_fields<__Type>(lhs, rhs);                     \
    }                                                                     \
    bool operator!=(CR<__Type> lhs, CR<__Type> rhs) {                     \
        return (field_count<__Type> != 0)                                 \
            && !equal_on_all_fields<__Type>(lhs, rhs);                    \
    }

namespace sem {
EACH_ORG_NESTED_TYPE(__eq)
}

#undef __eq

bool operator==(CR<UserTime> lhs, CR<UserTime> rhs) {
    return lhs.time == rhs.time;
}

#warning Temp disabled implementation of the simple node API
#if false
TEST(SimpleNodeConversion, SingleHashTagToken) {
    MockFull p(false, false);
    p.run("#test", &T::lexText, &P::parseHashTag);
    EXPECT_EQ(p.n(0).kind, org::HashTag);
    EXPECT_EQ(p.n(1).kind, org::RawText);
}


TEST(SimpleNodeConversion, DoubleHashTag) {
    MockFull p(false, false);
    p.run("#test##a", &T::lexText, &P::parseHashTag);
    EXPECT_EQ(p.k(0), org::HashTag);
    EXPECT_EQ(p.k(1), org::RawText);
    EXPECT_EQ(p.s(1), "#test");
    std::string  buf;
    std::ostream ss{&buf};
    auto         spec = getOrgSpec();
    ss << "start validation output" << Qt::endl;
    ss << spec->validateSelf(p.a(0)) << "\n";
    ss << spec->validateSub(p.a(0), 0) << "\n";
    ss << spec->getSingleSubnodeIdx(p.a(0), OrgSpecName::Head);
    spec->getSingleSubnodeIdx(org::HashTag, OrgSpecName::Head);
    spec->getMultipleSubnode(p.a(0), OrgSpecName::Head);
    spec->fieldName(p.a(0), 0);

    spec->isSingleField(p.a(0), 0);
    spec->fieldDoc(p.a(0), 0);
}

TEST(SimpleNodeConversion, NestedHashTag) {
    MockFull p(false, false);
    p.run("#test##[a, b]", &T::lexText, &P::parseHashTag);
    auto node = yamlRepr(p.a(0));
    yamlRepr(p.nodes);
    yamlRepr(p.tokens);
    std::string  buf;
    std::ostream ss{&buf};
    auto         spec = getOrgSpec();
    ss << "yaml node\n" << yamlRepr(*spec, p.a(0)) << "\nend yaml node\n";
    ss << "json node\n" << jsonRepr(*spec, p.a(0)) << "\nend json node\n";
    ss << "flat repr\n" << jsonRepr(p.nodes) << "\nend flat nodes\n";
    ss << "token repr\n" << jsonRepr(p.tokens) << "\nend flat tokens\n";
    ss << "yaml node\n" << yamlRepr(p.a(0)) << "\nend yaml node\n";
    ss << "flat repr\n" << yamlRepr(p.nodes) << "\nend flat nodes\n";
    ss << "token repr\n" << yamlRepr(p.tokens) << "\nend flat tokens\n";

    // qcout << buf << Qt::endl;
    // auto hash = sem::OrgConverter{}.convertHashTag(nullptr, p.a(0));
}

TEST(SimpleNodeConversion, DiffCompilation) {
    MockFull p(false, false);
    p.run("#test##[a, b]", &T::lexText, &P::parseHashTag);
    auto cmp = nodeAdapterComparisonOptions<
        OrgNodeKind,
        OrgTokenKind,
        Str>(
        [&p](OrgId id) -> OrgNode { return p.nodes.at(id); },
        [&p](OrgId id) -> Str { return p.nodes.strVal(id); });
}

TEST(SimpleNodeConversion, GraphRepr) {
    MockFull p(false, false);
    p.run("#test##[a, b]", &T::lexText, &P::parseHashTag);
    auto g = graphRepr(&p.nodes, OrgId(0));

    std::stringstream os;
    boost::write_graphviz(
        os,
        g,
        [&g,
         &p](std::ostream& os, VertDesc<OrgNodeKind, OrgTokenKind> vert) {
            os << "[label=\"" << to_string(p.nodes.at(g[vert].id).kind)
               << "\"]";
        });
}
#endif

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

TEST(Algorithms, Partitioning) {
    Vec<int> it{1, 1, 2, 2, 3, 3, 4, 4, 3};
    auto     spans = partition<int, int>(
        it, [](CR<int> v) -> int { return v; });
    EXPECT_EQ(spans.size(), 5);
    EXPECT_EQ(spans[0].size(), 2);
    EXPECT_EQ(spans[1].size(), 2);
    EXPECT_EQ(spans[1_B].size(), 1);
}

TEST(Algorithms, PartitioningEmptyVector) {
    Vec<int> input;
    auto     result = partition<int, int>(
        input, [](CR<int> i) { return i % 2 == 0; });
    EXPECT_TRUE(result.empty());
}

TEST(Algorithms, PartitioningSingleElementVector) {
    Vec<int> input  = {1};
    auto     result = partition<int, int>(
        input, [](CR<int> i) { return i % 2 == 0; });
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], input);
}

TEST(Algorithms, PartitioningOddEvenNumbers) {
    Vec<int> input  = {1, 2, 3, 4, 5};
    auto     result = partition<int, int>(
        input, [](CR<int> i) { return i % 2 == 0; });
    EXPECT_EQ(result.size(), 5);
    EXPECT_EQ(result[0], Vec<int>({1}));
    EXPECT_EQ(result[1], Vec<int>({2}));
}

TEST(Algorithms, PartitioningPositiveNegativeNumbers) {
    Vec<int> input  = {-1, -2, 3, 4, -5};
    auto     result = partition<int, int>(
        input, [](CR<int> i) { return 0 <= i; });
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], Vec<int>({-1, -2}));
    EXPECT_EQ(result[1], Vec<int>({3, 4}));
    EXPECT_EQ(result[2], Vec<int>({-5}));
}
