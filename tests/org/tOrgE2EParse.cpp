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

#include <hstd/stdlib/diffs.hpp>

#include <hstd/stdlib/Filesystem.hpp>
#include <sem/SemOrgSerde.hpp>
#include <google/protobuf/util/json_util.h>
#include <exporters/ExporterJson.hpp>

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

struct compare_context {
    std::string type;
    std::string field;
};

struct compare_report {
    std::string          message;
    Vec<compare_context> context;
};

template <typename T>
    requires std::formattable<T, char>
std::string maybe_format(const T& value) {
    return std::format("{}", value);
}

template <typename T>
    requires(!std::formattable<T, char>)
std::string maybe_format(const T&) {
    return "<non-formattable>";
}

template <typename T>
struct reporting_comparator {
    static void compare(
        CR<T>                       lhs,
        CR<T>                       rhs,
        Vec<compare_report>&        out,
        Vec<compare_context> const& context) {
        if (!(lhs == rhs)) {
            out.push_back({
                .context = context,
                .message = std::format(
                    "{} != {} on {}",
                    escape_literal(maybe_format(lhs)),
                    escape_literal(maybe_format(rhs)),
                    __LINE__),
            });
        }
    }
};

template <typename T>
struct reporting_comparator<std::optional<T>> {
    static void compare(
        CR<std::optional<T>>        lhs,
        CR<std::optional<T>>        rhs,
        Vec<compare_report>&        out,
        Vec<compare_context> const& context) {
        if (lhs.has_value() != rhs.has_value()) {
            out.push_back({
                .context = context,
                .message = fmt("on {}", __LINE__),
            });
        } else if (lhs.has_value()) {
            reporting_comparator<T>::compare(*lhs, *rhs, out, context);
        }
    }
};

template <typename T>
struct reporting_comparator<Vec<T>> {
    static void compare(
        CR<Vec<T>>                  lhs,
        CR<Vec<T>>                  rhs,
        Vec<compare_report>&        out,
        Vec<compare_context> const& context) {
        if (lhs.size() != rhs.size()) {
            out.push_back({
                .context = context,
                .message = fmt("on {}", __LINE__),
            });
        } else {
            for (int i = 0; i < lhs.size(); ++i) {
                reporting_comparator<T>::compare(
                    lhs.at(i),
                    rhs.at(i),
                    out,
                    context
                        + Vec<compare_context>{{
                            .field = fmt("{}", i),
                            .type  = "Vec",
                        }});
            }
        }
    }
};

template <IsVariant V>
struct reporting_comparator<V> {
    static void compare(
        CR<V>                       lhs,
        CR<V>                       rhs,
        Vec<compare_report>&        out,
        Vec<compare_context> const& context) {
        if (lhs.index() != rhs.index()) {
            out.push_back({
                .context = context,
                .message = fmt("on {}", __LINE__),
            });
        } else {
            std::visit(
                [&]<typename T>(T const& it) {
                    reporting_comparator<T>::compare(
                        it,
                        std::get<T>(rhs),
                        out,
                        context
                            + Vec<compare_context>{{
                                .field = fmt("{}", lhs.index()),
                                .type  = "Variant",
                            }});
                },
                lhs);
        }
    }
};


template <typename T>
concept IsRecord = std::is_class<T>::value;

template <DescribedRecord T>
struct reporting_comparator<T> {
    static void compare(
        CR<T>                       lhs,
        CR<T>                       rhs,
        Vec<compare_report>&        out,
        Vec<compare_context> const& context) {
        for_each_field_with_bases<std::remove_cvref_t<T>>(
            [&](auto const& field) {
                reporting_comparator<
                    std::remove_cvref_t<decltype(lhs.*field.pointer)>>::
                    compare(
                        lhs.*field.pointer,
                        rhs.*field.pointer,
                        out,
                        context
                            + Vec<compare_context>{{
                                .field = field.name,
                                .type  = demangle(typeid(T).name()),
                            }});
            });
    }
};

template <typename T>
struct reporting_comparator<sem::SemIdT<T>> {
    static void compare(
        CR<sem::SemIdT<T>>          lhs,
        CR<sem::SemIdT<T>>          rhs,
        Vec<compare_report>&        out,
        Vec<compare_context> const& context) {
        if (lhs.isNil() != rhs.isNil()) {
            out.push_back({
                .context = context,
                .message = fmt("on {}", __LINE__),
            });
        } else if (!lhs.isNil()) {
            reporting_comparator<T>::compare(
                *lhs.get(), *rhs.get(), out, context);
        }
    }
};

template <>
struct reporting_comparator<sem::SemId> {
    static void compare(
        CR<sem::SemId>              lhs,
        CR<sem::SemId>              rhs,
        Vec<compare_report>&        out,
        Vec<compare_context> const& context) {
        if (lhs.isNil() != rhs.isNil()) {
            out.push_back({
                .context = context,
                .message = fmt("on {}", __LINE__),
            });
        } else if (lhs.isNil()) {
            // pass
        } else if (lhs->getKind() != rhs->getKind()) {
            out.push_back({
                .context = context,
                .message = fmt(
                    "kind mismatch {} != {}",
                    lhs->getKind(),
                    rhs->getKind()),
            });
        } else {
            switch (lhs->getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind:                                              \
        reporting_comparator<sem::SemIdT<sem::__Kind>>::compare(          \
            lhs.as<sem::__Kind>(), rhs.as<sem::__Kind>(), out, context);  \
        break;

                EACH_SEM_ORG_KIND(_case)
#undef _case
            }
        }
    }
};

template <typename Obj, typename Field>
compare_report cmp_field_value(CR<T> lhs, CR<T> rhs, Field T::*fieldPtr) {
    return reporting_comparator<decltype(lhs.*fieldPtr)>::compare(
        lhs.*fieldPtr, rhs.*fieldPtr);
};


template <typename T>
auto cmp_stores(
    sem::KindStore<T> const& lhsStore,
    sem::KindStore<T> const& rhsStore,
    Vec<compare_report>&     out) {
    EXPECT_EQ(lhsStore.values.size(), rhsStore.values.size())
        << fmt("{}", T::staticKind);
    for (int i = 0; i < lhsStore.size(); ++i) {
        reporting_comparator<T>::compare(
            lhsStore.values.at(i), rhsStore.values.at(i), out, {});
    }
}

TEST(TestFiles, AllNodeSerde) {
    std::string file = (__CURRENT_FILE_DIR__ / "corpus/org/all.org");
    MockFull    p{false, false};
    std::string source = readFile(fs::path(file));
    p.run(source);

    sem::ContextStore write_context;
    sem::OrgConverter converter{&write_context};
    sem::SemId        write_node = converter.toDocument(
        OrgAdapter(&p.nodes, OrgId(0)));
    orgproto::AnyNode result;
    proto_serde<orgproto::AnyNode, sem::SemId>::write(&result, write_node);

    std::string                              json_string;
    google::protobuf::util::JsonPrintOptions options;
    options.add_whitespace = true;
    auto status            = google::protobuf::util::MessageToJsonString(
        result, &json_string, options);

    writeFile("/tmp/proto_write.json", json_string);

    sem::ContextStore read_context;
    sem::SemId        read_node = sem::SemId::Nil();
    proto_serde<orgproto::AnyNode, sem::SemId>::read(
        &read_context, result, read_node);

    json write_json = ExporterJson{}.evalTop(write_node);
    json read_json  = ExporterJson{}.evalTop(read_node);

    writeFile("/tmp/node_write.json", write_json.dump(2));
    writeFile("/tmp/node_read.json", read_json.dump(2));

    EXPECT_EQ(write_context.stores.size(), 1);
    EXPECT_EQ(read_context.stores.size(), 1);

    sem::ParseUnitStore const& original = write_context.stores.at(0);
    sem::ParseUnitStore const& parsed   = read_context.stores.at(0);
    Vec<compare_report>        out;

#define _case(__Kind)                                                     \
    {                                                                     \
        cmp_stores<sem::__Kind>(                                          \
            original.store##__Kind, parsed.store##__Kind, out);           \
    }

    EACH_SEM_ORG_KIND(_case)
#undef _case

    for (auto const& it : out) {
        std::string ctx = it.context
                        | rv::transform(
                              [](compare_context const& c) -> std::string {
                                  return fmt("{}.{}", c.type, c.field);
                              })
                        | rv::intersperse("->") //
                        | rv::join              //
                        | rs::to<std::string>();

        ADD_FAILURE() << fmt(
            "{} failed: original != parsed {}", ctx, it.message);
    }
}

TEST(TestFiles, AllNodeCoverage) {
    GTEST_SKIP();
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
