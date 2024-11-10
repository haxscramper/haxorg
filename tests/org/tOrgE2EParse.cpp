#include <haxorg/test/org_parse_aux.hpp>
#include <gtest/gtest.h>

#include <haxorg/parse/OrgParser.hpp>
#include <haxorg/parse/OrgTokenizer.hpp>
#include <gtest/gtest.h>

#include <haxorg/lexbase/AstSpec.hpp>
#include <haxorg/lexbase/AstDiff.hpp>
#include <haxorg/test/NodeTest.hpp>

#include <hstd/stdlib/diffs.hpp>

#include <hstd/stdlib/Filesystem.hpp>
#include <haxorg/sem/SemOrgSerde.hpp>
#include <google/protobuf/util/json_util.h>
#include <haxorg/exporters/ExporterJson.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/sem/ImmOrgEdit.hpp>
#include <haxorg/sem/ImmOrgGraph.hpp>
#include <haxorg/sem/ImmOrgGraphBoost.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/graphviz.hpp>
#include <fstream>
#include <haxorg/sem/perfetto_org.hpp>

void addNodeRec(
    org::graph::MapGraphState& g,
    org::ImmAdapter const&     node,
    org::graph::MapConfig&     conf) {
    Func<void(org::ImmAdapter const&)> aux;
    aux = [&](org::ImmAdapter const& node) {
        conf.message(fmt("recursive add {}", node), "addNodeRec");
        auto __tmp = conf.scopeLevel();
        switch (node->getKind()) {
            case OrgSemKind::Document:
            case OrgSemKind::ListItem:
            case OrgSemKind::List: {
                for (auto const& it : node) { aux(it); }
                break;
            }
            case OrgSemKind::Paragraph: {
                if (auto par = node.as<org::ImmParagraph>();
                    org::graph::hasGraphAnnotations(par)) {
                    addNode(g, node, conf);
                }
                break;
            }
            case OrgSemKind::Subtree: {
                if (auto tree = node.as<org::ImmSubtree>();
                    org::graph::hasGraphAnnotations(tree)) {
                    addNode(g, node, conf);
                }

                for (auto const& it : node) { aux(it); }
                break;
            }
            default: {
            }
        }
    };

    aux(node);
}
Str getDebugFile(Str const& suffix) {
    auto dir = fs::path{
        fmt("/tmp/haxorg_tests/{}",
            ::testing::UnitTest::GetInstance()
                ->current_test_info()
                ->test_suite_name())};
    if (!fs::is_directory(dir)) { createDirectory(dir); }
    return fmt(
        "{}/{}_{}",
        dir.native(),
        ::testing::UnitTest::GetInstance()->current_test_info()->name(),
        suffix);
}

void writeTreeRepr(
    org::ImmAdapter               n,
    Str const                     suffix,
    org::ImmAdapter::TreeReprConf conf = org::ImmAdapter::TreeReprConf{
        .withAuxFields = true,
    }) {
    writeFile(getDebugFile(suffix), n.treeRepr(conf).toString(false));
}

// adl-based customization points is the most disgusting degenerate idea
// you can possible have. The shit doesn't work reliably, you need to do
// some fucking magic with namespaces and whatever the fuck else, it does
// not work again, and with functions you need to specify the concrete type
// for every type. If this was a structure I could've used `std::format`
// with some form of concept here, if the library was actually written with
// this in mind.
#define GTEST_ADL_PRINT_TYPE(__type)                                      \
    namespace testing {                                                   \
        template <>                                                       \
        std::string PrintToString(__type const& value) {                  \
            return fmt1(value);                                           \
        }                                                                 \
    } // namespace testing

GTEST_ADL_PRINT_TYPE(OrgSemKind);
GTEST_ADL_PRINT_TYPE(org::ImmId);
GTEST_ADL_PRINT_TYPE(org::ImmAdapter);
GTEST_ADL_PRINT_TYPE(org::ImmUniqId);
GTEST_ADL_PRINT_TYPE(org::graph::MapNode);
GTEST_ADL_PRINT_TYPE(org::graph::MapEdge);
GTEST_ADL_PRINT_TYPE(Vec<Str>);

Str getSelfTest(org::ImmAdapter const& it) {
    return fmt(
        R"(
auto {0} = {1};
EXPECT_EQ({0}->getKind(), OrgSemKind::{2});
)",
        it.id,
        it.selfSelect(),
        it->getKind());
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
    return fmt("<non-formattable {}>", demangle(typeid(T).name()));
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
                    "{} != {} on {} for {}",
                    escape_literal(maybe_format(lhs)),
                    escape_literal(maybe_format(rhs)),
                    __LINE__,
                    demangle(typeid(T).name())),
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

template <typename K, typename V>
struct reporting_comparator<UnorderedMap<K, V>> {
    static void compare(
        CR<UnorderedMap<K, V>>      lhs,
        CR<UnorderedMap<K, V>>      rhs,
        Vec<compare_report>&        out,
        Vec<compare_context> const& context) {
        if (lhs.size() != rhs.size()) {
            out.push_back({
                .context = context,
                .message = fmt(
                    "lhs.size() != rhs.size() ({} != {}) on {}",
                    lhs.size(),
                    rhs.size(),
                    __LINE__),
            });
        } else {
            for (auto const& it : lhs.keys()) {
                if (rhs.contains(it)) {
                    reporting_comparator<V>::compare(
                        lhs.at(it),
                        rhs.at(it),
                        out,
                        context
                            + Vec<compare_context>{{
                                .field = maybe_format(it),
                                .type  = "UnorderedMap",
                            }});
                } else {
                    out.push_back({
                        .context = context,
                        .message = fmt(
                            "no '{}' in rhs on {}",
                            maybe_format(it),
                            __LINE__),
                    });
                }
            }
            for (int i = 0; i < lhs.size(); ++i) {}
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
                .message = fmt(
                    "lhs.size() != rhs.size() ({} != {}) on {}",
                    lhs.size(),
                    rhs.size(),
                    __LINE__),
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
struct reporting_comparator<sem::SemId<T>> {
    static void compare(
        CR<sem::SemId<T>>           lhs,
        CR<sem::SemId<T>>           rhs,
        Vec<compare_report>&        out,
        Vec<compare_context> const& context) {
        if (lhs.isNil() != rhs.isNil()) {
            out.push_back({
                .context = context,
                .message = fmt(
                    "nil on {} -- lhs.isNil:{} rhs.isNil:{}",
                    __LINE__,
                    lhs.isNil(),
                    rhs.isNil()),
            });
        } else if (!lhs.isNil()) {
            reporting_comparator<T>::compare(
                *lhs.get(), *rhs.get(), out, context);
        }
    }
};

template <>
struct reporting_comparator<sem::SemId<sem::Org>> {
    static void compare(
        CR<sem::SemId<sem::Org>>    lhs,
        CR<sem::SemId<sem::Org>>    rhs,
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
        reporting_comparator<sem::SemId<sem::__Kind>>::compare(           \
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

void show_compare_reports(Vec<compare_report> const& out) {
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

TEST(TestFiles, AllNodeSerde) {
    std::string file = (__CURRENT_FILE_DIR__ / "corpus/org/all.org");
    MockFull    p{false, false};
    std::string source = readFile(fs::path(file));
    p.run(source);

    sem::OrgConverter converter{};
    sem::SemId        write_node = converter.toDocument(
        OrgAdapter(&p.nodes, OrgId(0)));
    orgproto::AnyNode result;
    proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(
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
    proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::read(
        result,
        proto_write_accessor<sem::SemId<sem::Org>>::for_ref(read_node));

    {
        orgproto::AnyNode result2;
        proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(
            &result2, read_node);
        std::string proto_read_json;
        (void)google::protobuf::util::MessageToJsonString(
            result2, &proto_read_json, options);

        writeFile("/tmp/proto_read.json", proto_read_json);
    }

    json write_json = ExporterJson{}.evalTop(write_node);
    json read_json  = ExporterJson{}.evalTop(read_node);

    writeFile("/tmp/node_write.json", write_json.dump(2));
    writeFile("/tmp/node_read.json", read_json.dump(2));

    Vec<compare_report> out;

    reporting_comparator<sem::SemId<sem::Org>>::compare(
        write_node, read_node, out, {});

    show_compare_reports(out);
}

TEST(TestFiles, AllNodeCoverage) {
    GTEST_SKIP();
    std::string file = (__CURRENT_FILE_DIR__ / "corpus/org/all.org");
    MockFull    p{false, false};
    std::string source = readFile(fs::path(file));
    p.run(source);

    SemSet            foundNodes;
    sem::OrgConverter converter{};
    sem::SemId node = converter.toDocument(OrgAdapter(&p.nodes, OrgId(0)));

    using osk = OrgSemKind;
    SemSet wipNotParseable{
        osk::Include,
        osk::DocumentGroup,
        osk::Empty,
        osk::Row,
        osk::Table,
        osk::SubtreeCompletion,
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

sem::SemId<sem::Org> parseNode(CR<Str> source) {
    MockFull p{false, false};
    {
        __perf_trace("parsing", "parse node");
        p.run(source);
    }
    {
        __perf_trace("convert", "convert");
        return p.toNode();
    }
}

struct ImmOrgApiTestBase : public ::testing::Test {
    org::ImmAstContext start;

    void setTraceFile(std::string const& path) {
        start.debug->setTraceFile(path);
    }

    org::ImmAstVersion getInitialVersion(Str const& text) {
        return start.init(parseNode(text));
    }

    void writeGvHistory(
        const Vec<org::ImmAstVersion>& history,
        std::string                    suffix,
        org::ImmAstGraphvizConf const& conf = org::ImmAstGraphvizConf{
            .withAuxNodes    = true,
            .withEditHistory = true,
        }) {
        Graphviz gvc;
        auto     gv = org::toGraphviz(history, conf);
        gvc.writeFile(getDebugFile(suffix + ".dot"), gv);
        gvc.renderToFile(getDebugFile(suffix + ".png"), gv);
    }
};

struct ImmOrgDocumentSelector : public ImmOrgApiTestBase {};

TEST_F(ImmOrgDocumentSelector, GetMatchingNodeByKind) {
    auto                     node = getInitialVersion("bold");
    org::OrgDocumentSelector selector;
    selector.searchAnyKind({OrgSemKind::Word}, true);

    auto words = selector.getMatches(node.getRootAdapter());

    EXPECT_EQ(words.size(), 1);
    EXPECT_EQ(words.at(0)->getKind(), OrgSemKind::Word);
    EXPECT_EQ(words.at(0).as<org::ImmWord>()->text, "bold");
}

TEST_F(ImmOrgDocumentSelector, GetMultipleMatchingNodesByKind) {
    auto                     node = getInitialVersion("word *bold*");
    org::OrgDocumentSelector selector;
    selector.searchAnyKind({OrgSemKind::Word}, true);

    auto words = selector.getMatches(node.getRootAdapter());

    EXPECT_EQ(words.size(), 2);
    EXPECT_EQ(words.at(0).as<org::ImmWord>()->text, "word");
    EXPECT_EQ(words.at(1).as<org::ImmWord>()->text, "bold");
}

TEST_F(ImmOrgDocumentSelector, GetDirectlyNestedNode) {
    auto                     node = getInitialVersion("word *bold*");
    org::OrgDocumentSelector selector;
    selector.searchAnyKind(
        {OrgSemKind::Bold}, false, selector.linkDirectSubnode());
    selector.searchAnyKind({OrgSemKind::Word}, true);

    auto words = selector.getMatches(node.getRootAdapter());

    EXPECT_EQ(words.size(), 1);
    EXPECT_EQ(words.at(0)->getKind(), OrgSemKind::Word);
    EXPECT_EQ(words.at(0).as<org::ImmWord>()->text, "bold");
}

TEST_F(ImmOrgDocumentSelector, GetSubtreeByTitle) {
    auto doc = getInitialVersion(R"(
* Title1
** Subtitle1
** Subtitle2

Paragraph under subtitle 2

* Multi-part title
)");

    if (true) {
        org::OrgDocumentSelector selector;
        selector.setTraceFile(getDebugFile("title_search_1"));
        selector.searchSubtreePlaintextTitle({"Title1"}, true);

        auto title1 = selector.getMatches(doc.getRootAdapter());
        EXPECT_EQ(title1.size(), 1);
        EXPECT_EQ(title1.at(0)->getKind(), OrgSemKind::Subtree);
    }

    if (true) {
        org::OrgDocumentSelector selector;
        selector.setTraceFile(getDebugFile("title_search_2"));
        selector.searchSubtreePlaintextTitle(
            {"Subtitle2"}, false, selector.linkIndirectSubnode());
        selector.searchAnyKind({OrgSemKind::Word}, true);

        auto words = selector.getMatches(doc.getRootAdapter());
        EXPECT_EQ(words.size(), 5) << fmt1(words);
        // Subtree nodes are added as targets in the post-order DFS
        // traversal over all 'nested' elements. First the words in subtree
        // are collected.
        EXPECT_EQ(words.at(0).as<org::ImmWord>()->text, "Paragraph");
        EXPECT_EQ(words.at(1).as<org::ImmWord>()->text, "under");
        EXPECT_EQ(words.at(2).as<org::ImmWord>()->text, "subtitle");
        EXPECT_EQ(words.at(3).as<org::ImmWord>()->text, "2");
        // Then visitation gets to the subtree title itself. Nested fields
        // for each node are iterated starting from the base's fields and
        // then to the concrete type -- also in the DFS order.
        EXPECT_EQ(
            words.at(4).as<org::ImmWord>()->text->toBase(), "Subtitle2");
    }

    if (true) {
        org::OrgDocumentSelector selector;
        selector.setTraceFile(getDebugFile("title_search_3"));
        selector.searchSubtreePlaintextTitle(
            {"Subtitle2"},
            false,
            selector.linkField(org::ImmReflFieldId::FromTypeField(
                &org::ImmOrg::subnodes)));
        selector.searchAnyKind({OrgSemKind::Word}, true);

        auto words = selector.getMatches(doc.getRootAdapter());
        EXPECT_EQ(words.size(), 4);
        // Subtree nodes are added as targets in the post-order DFS
        // traversal over all 'nested' elements. First the words in subtree
        // are collected.
        EXPECT_EQ(words.at(0).as<org::ImmWord>()->text, "Paragraph");
        EXPECT_EQ(words.at(1).as<org::ImmWord>()->text, "under");
        EXPECT_EQ(words.at(2).as<org::ImmWord>()->text, "subtitle");
        EXPECT_EQ(words.at(3).as<org::ImmWord>()->text, "2");
    }
}

TEST_F(ImmOrgDocumentSelector, GetSubtreeAtPath) {
    auto node = getInitialVersion(R"(
* Title1
** Subtitle1
Content1
** Subtitle2
Content2
* Title2
)");

    org::OrgDocumentSelector selector;
    selector.searchSubtreePlaintextTitle(
        {"Title1"}, false, selector.linkIndirectSubnode());
    selector.searchSubtreePlaintextTitle({"Subtitle1"}, true);
    auto matches = selector.getMatches(node.getRootAdapter());
    EXPECT_EQ(matches.size(), 1);
}

TEST_F(ImmOrgDocumentSelector, EarlyVisitExit) {
    auto node = getInitialVersion(R"(
*** Content
Subnode
** Other content
First
*** Nested subtree
)");

    org::OrgDocumentSelector      selector;
    UnorderedMap<OrgSemKind, int> counts;

    selector.searchPredicate(
        [&](org::ImmAdapter const& node) -> org::OrgSelectorResult {
            ++counts[node->getKind()];
            return org::OrgSelectorResult{
                .isMatching     = node->is(OrgSemKind::Subtree),
                .tryNestedNodes = !node->is(OrgSemKind::Subtree),
            };
        },
        false);

    selector.getMatches(node.getRootAdapter());

    EXPECT_EQ(counts.at(OrgSemKind::Subtree), 2);
    EXPECT_EQ(counts.at(OrgSemKind::Document), 1);
    EXPECT_EQ(counts.get(OrgSemKind::Word), std::nullopt);
}

TEST_F(ImmOrgDocumentSelector, NonLeafSubtrees) {
    auto doc = getInitialVersion(R"(
* s1
** s2
* s3
*** s4
* s5
* s6
** s7
)");

    org::OrgDocumentSelector selector;
    selector.searchAnyKind(
        {OrgSemKind::Subtree}, true, selector.linkIndirectSubnode());

    selector.searchAnyKind({OrgSemKind::Subtree}, false);

    Vec<org::ImmAdapter> subtrees = selector.getMatches(
        doc.getRootAdapter());

    EXPECT_EQ(subtrees.size(), 3);
    auto titles = subtrees
                | rv::transform([](org::ImmAdapter const& id) -> Vec<Str> {
                      return flatWords(id.at(
                          org::ImmReflFieldId::FromTypeField<
                              org::ImmSubtree>(&org::ImmSubtree::title)));
                  })
                | rs::to<Vec>();

    std::sort(titles.begin(), titles.end());
    EXPECT_EQ(titles.at(0), Vec<Str>{"s1"});
    EXPECT_EQ(titles.at(1), Vec<Str>{"s3"});
    EXPECT_EQ(titles.at(2), Vec<Str>{"s6"});
}

TEST_F(ImmOrgDocumentSelector, SubtreesWithDateInTitleAndBody) {
    auto doc = getInitialVersion(R"(
* [2024-02-12] In title
* In description
[2024-02-12]
)");

    {
        org::OrgDocumentSelector selector;
        selector.searchAnyKind(
            {OrgSemKind::Subtree},
            true,
            selector.linkField(org::ImmReflFieldId::FromTypeField(
                &org::ImmSubtree::title)));
        selector.searchAnyKind({OrgSemKind::Time}, false);
        auto subtrees = selector.getMatches(doc.getRootAdapter());
        EXPECT_EQ(subtrees.size(), 1);
    }

    {
        org::OrgDocumentSelector selector;
        selector.searchAnyKind(
            {OrgSemKind::Subtree}, true, selector.linkIndirectSubnode());
        selector.searchAnyKind({OrgSemKind::Time}, false);
        auto subtrees = selector.getMatches(doc.getRootAdapter());
        EXPECT_EQ(subtrees.size(), 2);
    }
}

#define EXPECT_EQ2(lhs, rhs)                                              \
    {                                                                     \
        auto lhs_val = lhs;                                               \
        auto rhs_val = rhs;                                               \
        if (lhs != rhs) {                                                 \
            FAIL() << fmt(                                                \
                "Expected equality of these values:\n  {}\n    {}\n  "    \
                "{}\n "                                                   \
                "   {}",                                                  \
                #lhs,                                                     \
                lhs,                                                      \
                #rhs,                                                     \
                rhs);                                                     \
        }                                                                 \
    }

TEST(OrgApi, NamedPropertyModification) {
    auto doc = parseNode(R"(* Subtree)");

    auto tree = doc.at(0).as<sem::Subtree>();
    tree->setPropertyStrValue("123", "bookmark_pos");

    Str formatted = sem::formatToString(doc);
    EXPECT_NE(formatted.find(":bookmark_pos: 123"), -1) << formatted;

    tree->removeProperty("bookmark_pos");
    formatted = sem::formatToString(doc);
    EXPECT_EQ(formatted.find(":bookmark_pos: 123"), -1) << formatted;
}

TEST(OrgApi, LinkAttachedGet1) {
    auto doc = parseNode(
        R"(#+attr_link: :attach-method copy :attach-on-export t
[[attachment:image 1.jpg]]
)");

    EXPECT_EQ2(doc->getKind(), OrgSemKind::Document);
    auto par = doc->subnodes.at(0);
    EXPECT_EQ2(par->getKind(), OrgSemKind::Paragraph);
    auto link = par->subnodes.at(0);
    EXPECT_EQ2(link->getKind(), OrgSemKind::Link);

    auto link1 = link.getAs<sem::Link>();
    ASSERT_TRUE(link1 != nullptr);

    auto args = link1->getAttrs("attach-on-export");
    EXPECT_EQ(args.size(), 1);
    auto arg0 = args.at(0);
    EXPECT_EQ(arg0.getBool(), true);
    EXPECT_EQ(arg0.getString(), "t");
}

TEST(OrgApi, TracerOperations1) {
    auto     text = R"(
* Subtree
  :properties:
  :key: value
  :end:
)";
    MockFull p{true, true};
    fs::path tokenizer_trace{"/tmp/TraceOperations1_tokenizer_trace.txt"};
    p.tokenizer->setTraceFile(tokenizer_trace);
    p.tokenizer->traceStructured = true;

    fs::path parser_trace{"/tmp/TraceOperations1_parser_trace.txt"};
    p.parser->setTraceFile(parser_trace);
    p.parser->traceStructured = true;

    sem::OrgConverter converter{};
    fs::path          sem_trace{"/tmp/TraceOperations1_sem_trace.txt"};
    converter.setTraceFile(sem_trace);
    converter.traceStructured = true;

    fs::path      lex_trace{"/tmp/TraceOperations1_lex_trace.txt"};
    std::ofstream fileTrace{lex_trace.c_str()};

    LexerParams params;
    params.traceStructured = true;
    params.maxUnknown      = 1;
    params.traceStream     = &fileTrace;
    p.tokenizeBase(text, params);
    p.tokenizeConvert();
    p.parse();

    auto document = converter.toDocument(OrgAdapter(&p.nodes, OrgId(0)));

    ExporterJson exp{};
    fs::path     exp_trace{"/tmp/TraceOperations1_exp_trace.txt"};
    exp.setTraceFile(exp_trace);
    exp.traceStructured = true;
    exp.evalTop(document);
}

sem::SemId<sem::Org> testParseString(
    std::string const&         text,
    std::optional<std::string> debug = std::nullopt) {
    MockFull          p{debug.has_value(), debug.has_value()};
    sem::OrgConverter converter{};
    LexerParams       params;
    params.maxUnknown = 1;
    if (debug) {
        fs::path tokenizer_trace{debug.value() + "_tokenizer_trace.txt"};
        fs::path parser_trace{debug.value() + "_parser_trace.txt"};
        fs::path sem_trace{debug.value() + "_sem_trace.txt"};
        fs::path lex_trace{debug.value() + "_lex_trace.txt"};
        p.tokenizer->setTraceFile(tokenizer_trace);
        p.parser->setTraceFile(parser_trace);
        converter.setTraceFile(sem_trace);
        p.parser->traceColored    = false;
        p.tokenizer->traceColored = false;
        std::ofstream fileTrace{lex_trace.c_str()};

        params.traceStream = &fileTrace;
        p.tokenizeBase(text, params);
    } else {
        p.tokenizeBase(text, params);
    }

    p.tokenizeConvert();
    p.parse();

    if (debug) {
        std::stringstream buffer;
        ColStream         os{buffer};
        os.colored = false;
        OrgAdapter(&p.nodes, OrgId(0))
            .treeRepr(os, 0, OrgNodeGroup::TreeReprConf{});

        writeFile(
            fs::path{debug.value() + "_parse_tree.txt"}, buffer.str());
    }

    return converter.toDocument(OrgAdapter(&p.nodes, OrgId(0)));
}

template <typename T>
void dbgString(
    sem::SemId<T> const& id,
    char const*          function = __builtin_FUNCTION(),
    int                  line     = __builtin_LINE(),
    char const*          file     = __builtin_FILE()) {
    LOG(INFO) << fmt(
        "{}:{}\n{}",
        function,
        line,
        sem::exportToTreeString(id.asOrg(), sem::OrgTreeExportOpts{}));
}

template <typename T>
void dbgString(
    Vec<sem::SemId<T>> const& id,
    char const*               function = __builtin_FUNCTION(),
    int                       line     = __builtin_LINE(),
    char const*               file     = __builtin_FILE()) {
    for (auto const& i : id) { dbgString(i, function, line, file); }
}

template <typename T>
sem::SemId<T> parseOne(
    std::string const&         text,
    std::optional<std::string> debug = std::nullopt) {
    auto one = sem::asOneNode(testParseString(text, debug));

    while (T::staticKind != one->getKind()) { one = one.at(0); }
    return one.as<T>();
}

template <typename T>
struct ImmTestResult {
    org::ImmAstContext  context;
    org::ImmAstVersion  version;
    org::ImmAdapterT<T> node;
};

template <
    sem::IsOrg Sem,
    typename Imm = org::sem_to_imm_map<Sem>::imm_type>
ImmTestResult<Imm> immConv(sem::SemId<Sem> const& id) {
    ImmTestResult<Imm> res;
    res.version = res.context.init(id.asOrg());
    res.node    = res.version.getRootAdapter().template as<Imm>();
    return res;
}

TEST(OrgApi, ParagraphBody) {
    {
        auto par = parseOne<sem::Paragraph>("NOTE: content");
        EXPECT_TRUE(par->hasAdmonition());
        EXPECT_EQ(par->getAdmonitions().at(0), "NOTE");
        EXPECT_FALSE(par.isNil());
        auto body = par->getBody();
        EXPECT_EQ(body.size(), 1);
        EXPECT_TRUE(body.at(0)->is(OrgSemKind::Word));
    }

    {
        auto par = parseOne<sem::Paragraph>("NOTE:");
        EXPECT_FALSE(par.isNil());
        auto body = par->getBody();
        EXPECT_EQ(body.size(), 0);
    }

    {
        auto par  = immConv(parseOne<sem::Paragraph>("NOTE: content"));
        auto body = par.node.getBody();
        EXPECT_EQ(body.size(), 1);
        EXPECT_TRUE(body.at(0)->is(OrgSemKind::Word));
    }

    {
        auto par = parseOne<sem::Paragraph>("[fn:footnote] content");
        EXPECT_FALSE(par.isNil());
        auto body = par->getBody();
        EXPECT_EQ(body.size(), 1);
        EXPECT_TRUE(body.at(0)->is(OrgSemKind::Word));
    }

    {
        auto par = parseOne<sem::Paragraph>(
            "[fn::inline footnote] content");
        EXPECT_FALSE(par.isNil());
        auto body = par->getBody();
        EXPECT_EQ(body.size(), 3);
        EXPECT_TRUE(body.at(0)->is(OrgSemKind::InlineFootnote));
        EXPECT_TRUE(body.at(2)->is(OrgSemKind::Word));
    }
}

TEST(OrgApi, CustomBlocks) {
    auto block = parseOne<sem::BlockDynamicFallback>(
        R"(#+begin_random_content
body of the random
#+end_random_content)");

    EXPECT_EQ(block->name, "randomcontent");
    auto body = block.at(0);
    EXPECT_EQ(body->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(body.at(0)->getKind(), OrgSemKind::Word);
    EXPECT_EQ(body.at(0).as<sem::Word>()->text, "body");
}

TEST(OrgApi, BlockAttachment) {
    {
        auto block = parseOne<sem::BlockExample>(
            R"(#+caption: example *caption*
#+begin_example
content
#+end_example)");

        auto caption = block->getCaption();
        // dbgString(caption);
        EXPECT_EQ(caption.size(), 1);
        auto cap0 = caption.at(0);
        EXPECT_EQ(cap0->getKind(), OrgSemKind::Paragraph);
        EXPECT_EQ(cap0.size(), 3);
        EXPECT_EQ(cap0.at(0)->getKind(), OrgSemKind::Word);
        EXPECT_EQ(cap0.at(2)->getKind(), OrgSemKind::Bold);
    }

    {
        auto block = parseOne<sem::BlockExample>(
            R"(#+name: example-block-one
#+begin_example
content
#+end_example)");

        auto name = block->getName();
        EXPECT_EQ(name.size(), 1);
        EXPECT_EQ(name.at(0), "example-block-one");
    }
}

TEST(OrgApi, SubtreeArchiveProperties) {
    auto tree = parseOne<sem::Subtree>(
        R"(** COMPLETED Usable code coverage output generator
     CLOSED: [2024-11-01 Fri 20:59:49 +04]
     :PROPERTIES:
     :CREATED:  [2024-05-31 Fri 23:38:18 +04]
     :ID:       5ab53c80-6d65-4768-84c6-d881ce47cf0e
     :ARCHIVE_TIME: 2024-11-01 Fri 21:00:18 +04
     :ARCHIVE_FILE: ~/projects.org
     :ARCHIVE_OLPATH: Haxorg/Infrastructure/Code coverage
     :ARCHIVE_CATEGORY: projects
     :ARCHIVE_TODO: COMPLETED
     :ARCHIVE:  %s_archive::* Misc
     :END:
)",
        getDebugFile("trace"));

    // dbgString(tree);

    {
        auto olpath = sem::getSubtreeProperties<
            sem::NamedProperty::ArchiveOlpath>(tree);
        EXPECT_EQ(olpath.size(), 1);
        auto const& p = olpath.at(0).path.path;
        EXPECT_EQ(p.at(0), "Haxorg");
        EXPECT_EQ(p.at(1), "Infrastructure");
        EXPECT_EQ(p.at(2), "Code coverage");
    }

    {
        auto p = sem::getSubtreeProperties<
            sem::NamedProperty::ArchiveFile>(tree);
        EXPECT_EQ(p.size(), 1);
        EXPECT_EQ(p.at(0).file, "~/projects.org");
    }


    {
        auto p = sem::getSubtreeProperties<
            sem::NamedProperty::ArchiveCategory>(tree);
        EXPECT_EQ(p.size(), 1);
        EXPECT_EQ(p.at(0).category, "projects");
    }
    {
        auto p = sem::getSubtreeProperties<
            sem::NamedProperty::ArchiveTodo>(tree);
        EXPECT_EQ(p.size(), 1);
        EXPECT_EQ(p.at(0).todo, "COMPLETED");
    }

    {
        auto p = sem::getSubtreeProperties<
            sem::NamedProperty::ArchiveTarget>(tree);
        EXPECT_EQ(p.size(), 1);
        EXPECT_EQ(p.at(0).pattern, "%s_archive");
        EXPECT_EQ(p.at(0).path.path.size(), 1);
        EXPECT_EQ(p.at(0).path.path.at(0), "Misc");
    }
}

TEST(OrgApi, HashtagParse) {
    using V = Vec<Vec<Str>>;
    {
        auto h = parseOne<sem::HashTag>("#hashtag");
        EXPECT_EQ(h->head, "hashtag");
        EXPECT_EQ(h->subtags.size(), 0);
        EXPECT_EQ(h->getFlatHashes(), V{{"hashtag"}});
    }
    {
        auto h = parseOne<sem::HashTag>("#hashtag##[sub]");
        EXPECT_EQ(h->head, "hashtag");
        EXPECT_EQ(h->subtags.size(), 1);
        auto flat = h->getFlatHashes();
        EXPECT_EQ(flat.size(), 2);
        EXPECT_EQ(flat.at(0), Vec<Str>{"hashtag"});
        EXPECT_EQ(flat.at(1), (Vec<Str>{"hashtag", "sub"}));
    }

    {
        auto h = parseOne<sem::HashTag>("#one##[two##[three,four,five]]");
        EXPECT_EQ(h->head, "one");
        EXPECT_EQ(h->subtags.size(), 1);
        auto flat = h->getFlatHashes();
        EXPECT_EQ(flat.size(), 5);
        EXPECT_EQ(flat.at(0), Vec<Str>{"one"});
        EXPECT_EQ(flat.at(1), (Vec<Str>{"one", "two"}));
        EXPECT_EQ(flat.at(2), (Vec<Str>{"one", "two", "three"}));
        EXPECT_EQ(flat.at(3), (Vec<Str>{"one", "two", "four"}));
        EXPECT_EQ(flat.at(4), (Vec<Str>{"one", "two", "five"}));
    }

    {
        auto par = immConv(parseOne<sem::HashTag>("#hashtag##[sub]"));
        auto h   = par.node;
        EXPECT_EQ(h->head, "hashtag");
        EXPECT_EQ(h->subtags.size(), 1);
        auto flat = h.getFlatHashes();
        EXPECT_EQ(flat.size(), 2);
        EXPECT_EQ(flat.at(0), Vec<Str>{"hashtag"});
        EXPECT_EQ(flat.at(1), (Vec<Str>{"hashtag", "sub"}));
    }
}

TEST(OrgApi, SubtreeLogParsing) {
    {
        auto s = parseOne<sem::Subtree>(R"(**** COMPLETED Subtree
     CLOSED: [2000-01-03 Wed 10:43:40 +04]
     :PROPERTIES:
     :CREATED:  [2000-01-03 Wed 09:51:41 +04]
     :END:
     :LOGBOOK:
     - Tag "#work##xasd" Added on [2000-01-03 Wed 09:52:00 +04]
     CLOCK: [2000-01-03 Wed 09:51:50 +04]--[2000-01-03 Wed 10:43:40 +04] =>  0:52
     - State "WIP"        from "TODO"       [2000-01-03 Wed 09:51:50 +04]
     - State "COMPLETED"  from "WIP"        [2000-01-03 Wed 10:43:40 +04]
     :END:)");

        EXPECT_EQ(s->logbook.size(), 4);
        auto const& l = s->logbook;
        EXPECT_TRUE(l.at(0)->isTag());
        EXPECT_TRUE(l.at(1)->isClock());
        EXPECT_TRUE(l.at(2)->isState());
        EXPECT_TRUE(l.at(3)->isState());
        EXPECT_EQ(l.at(0)->getTag().on->getYear(), 2000);
        EXPECT_EQ(l.at(0)->getTag().on->getMinute(), 52);
        EXPECT_EQ(l.at(1)->getClock().from->getMinute(), 51);
        EXPECT_EQ(l.at(1)->getClock().to.value()->getMinute(), 43);
        EXPECT_EQ(l.at(2)->getState().from, "TODO"_ss);
        EXPECT_EQ(l.at(2)->getState().to, "WIP"_ss);
        EXPECT_EQ(l.at(3)->getState().to, "COMPLETED"_ss);
        EXPECT_EQ(l.at(3)->getState().from, "WIP"_ss);
    }
}

TEST(OrgApi, WordParsing) {
    {
        auto w = parseOne<sem::Word>("test");
        EXPECT_EQ(w->text, "test"_ss);
    }
    {
        auto w = parseOne<sem::Word>("test-one");
        EXPECT_EQ(w->text, "test-one"_ss);
    }
    {
        auto w = parseOne<sem::Word>("don't");
        EXPECT_EQ(w->text, "don't"_ss);
    }
}

TEST(OrgApi, TblfmExpression) {
    {
        auto t = parseOne<sem::CmdTblfm>(
            R"(#+TBLFM: $6=vsum($P1..$P3)::$7=10*$Tot/$max;%.1f::$at=vmean(@-2..@-1);%.1f)",
            getDebugFile("trace"));
    }
}

TEST(OrgApi, LinkTarget) {
    {
        auto l = parseOne<sem::Link>(
            R"([[* Title]])", getDebugFile("subtree_title"));
        auto const& t = l->target;
        EXPECT_EQ(t.getKind(), sem::LinkTarget::Kind::SubtreeTitle);
        EXPECT_EQ(t.getSubtreeTitle().level, 1);
        EXPECT_EQ(t.getSubtreeTitle().title.path.size(), 1);
        EXPECT_EQ(t.getSubtreeTitle().title.path.at(0), "Title");
    }
    {
        auto l = parseOne<sem::Link>(
            R"([[** Title/Sub]])", getDebugFile("subtree_title"));
        auto const& t = l->target;
        EXPECT_EQ(t.getKind(), sem::LinkTarget::Kind::SubtreeTitle);
        EXPECT_EQ(t.getSubtreeTitle().level, 2);
        EXPECT_EQ(t.getSubtreeTitle().title.path.size(), 2);
        EXPECT_EQ(t.getSubtreeTitle().title.path.at(0), "Title");
        EXPECT_EQ(t.getSubtreeTitle().title.path.at(1), "Sub");
    }
    {
        auto l = parseOne<sem::Link>(
            R"([[#custom-id]])", getDebugFile("custom_id"));
        auto const& t = l->target;
        EXPECT_EQ(t.getKind(), sem::LinkTarget::Kind::CustomId);
        EXPECT_EQ(t.getCustomId().text, "custom-id");
    }
}

TEST(OrgApi, ColumnView) {
    {
        auto c = parseOne<sem::CmdColumns>(
            R"(#+columns: %20ITEM %9Approved(Approved?){X} %Owner %11Status %10Time_Spent{:})",
            getDebugFile("subtree_title"));
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

struct ImmOrgApi : ImmOrgApiTestBase {};


TEST_F(ImmOrgApi, StoreNode) {
    auto node          = parseNode(R"(
** ~pyhaxorg~
    CLOSED: [2024-06-22 Sat 22:00:27 +04]
    :PROPERTIES:
    :CREATED:  [2023-07-30 Sun 20:51:39 +04]
    :END:

=pybind11= python module exposing the org-mode AST for scripting. intern intern intern intern
)");
    auto [store, root] = org::ImmAstContext{}.addRoot(node);
    ColStream os;
    store.format(os);
    writeFile("/tmp/StoreNode.txt", os.getBuffer().toString(false));
}

TEST_F(ImmOrgApi, RountripImmutableAst) {
    std::string file   = (__CURRENT_FILE_DIR__ / "corpus/org/all.org");
    std::string source = readFile(fs::path(file));
    org::ImmAstContext store;
    sem::SemId         write_node = parseNode(source);
    org::ImmAstVersion v1         = store.addRoot(write_node);
    sem::SemId         read_node  = v1.context.get(v1.getRoot());

    Vec<compare_report> out;

    reporting_comparator<sem::SemId<sem::Org>>::compare(
        write_node, read_node, out, {});
    show_compare_reports(out);
}

TEST_F(ImmOrgApi, ImmAstFieldIteration) {
    org::ImmAstContext store;
    for (auto const& k : sliceT<OrgSemKind>()) {
        if (k != OrgSemKind::None) {
            switch_node_nullptr(k, [&]<typename N>(N*) {
                N                         tmp{};
                ReflRecursiveVisitContext ctx;
                Vec<org::ImmReflPathBase> paths;
                reflVisitAll<N>(
                    tmp,
                    org::ImmReflPathBase{},
                    ctx,
                    [&]<typename T>(
                        org::ImmReflPathBase const& path, T const& value) {
                        paths.push_back(path);
                    });
            });
        }
    }
}


TEST_F(ImmOrgApi, ItearteParentNodes) {
    setTraceFile(getDebugFile("trace.txt"));
    start.track->isTrackingParent = [](org::ImmAdapter const&) {
        return true;
    };


    auto start_node   = parseNode("word0 word2 word4");
    auto replace_node = parseNode("wordXX").at(0).at(0);
    auto v1           = start.init(start_node);
    auto r            = v1.getRootAdapter();
    auto doc_id       = r;
    auto par_id       = doc_id.at(0);
    auto space_id     = par_id.at(1);

    EXPECT_EQ(space_id->getKind(), OrgSemKind::Space);
    {
        org::ImmParentIdVec parents = v1.context.getParentIds(space_id.id);
        EXPECT_EQ(parents.size(), 1);
        EXPECT_TRUE(parents.contains(par_id.id));
        EXPECT_EQ(parents.size(), 1);
    }

    {
        org::ParentPathMap parents = v1.context.getParentsFor(space_id.id);
        EXPECT_EQ(parents.size(), 1);
        EXPECT_TRUE(parents.contains(par_id.id));
        EXPECT_EQ(parents.at(par_id.id).size(), 2);
        EXPECT_EQ(
            parents.at(par_id.id).at(0).path.at(0).getFieldName().name,
            org::ImmReflFieldId::FromTypeField(&org::ImmOrg::subnodes));
        EXPECT_EQ(
            parents.at(par_id.id).at(0).path.at(1).getIndex().index, 1);
        EXPECT_EQ(
            parents.at(par_id.id).at(1).path.at(0).getFieldName().name,
            org::ImmReflFieldId::FromTypeField(&org::ImmOrg::subnodes));
        EXPECT_EQ(
            parents.at(par_id.id).at(1).path.at(1).getIndex().index, 3);
    }


    {
        Vec<org::ImmUniqId> paths = v1.context.getPathsFor(space_id.id);
        EXPECT_EQ(paths.size(), 2);
        auto const& p0 = paths.at(0);
        auto const& p1 = paths.at(1);
        EXPECT_EQ(p0.path.root, doc_id.id);
        EXPECT_EQ(p1.path.root, doc_id.id);
    }
}

TEST_F(ImmOrgApi, ReplaceSubnodeAtPath) {
    setTraceFile(getDebugFile("trace.txt"));
    start.track->isTrackingParent = [](org::ImmAdapter const&) {
        return true;
    };


    auto start_node   = parseNode("word0 word2 word4");
    auto replace_node = parseNode("wordXX").at(0).at(0);
    auto version1     = start.init(start_node);
    auto store        = version1.context;
    auto paragraph    = version1.getRootAdapter().at(0);
    auto ctx          = store.getEditContext();
    auto __absl_scope = ctx.collectAbslLogs();
    auto word_xx      = store.add(replace_node, ctx);
    auto version2     = store.finishEdit(
        ctx,
        ctx.store().cascadeUpdate(
            version1.getRootAdapter(),
            setSubnode(paragraph, word_xx, 2, ctx),
            ctx));

    auto        store2 = version2.context;
    auto const& c = gen_view(version2.epoch.replaced.allReplacements())
                  | rs::to<Vec>();

    auto const& doc1_id = ctx->adapt(c.at(0).original.value());
    auto const& doc2_id = ctx->adapt(c.at(0).replaced);
    auto const& par1_id = ctx->adapt(c.at(1).original.value());
    auto const& par2_id = ctx->adapt(c.at(1).replaced);

    EXPECT_EQ(doc1_id->getKind(), OrgSemKind::Document);
    EXPECT_EQ(doc2_id->getKind(), OrgSemKind::Document);

    EXPECT_EQ(doc1_id.id.getNodeIndex(), 1);
    EXPECT_EQ(doc2_id.id.getNodeIndex(), 2);

    EXPECT_EQ(par1_id->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(par2_id->getKind(), OrgSemKind::Paragraph);

    EXPECT_EQ(par1_id.id.getNodeIndex(), 1);
    EXPECT_EQ(par2_id.id.getNodeIndex(), 2);

    auto const& doc1 = doc1_id.value<org::ImmDocument>();
    auto const& doc2 = doc2_id.value<org::ImmDocument>();
    auto const& par1 = par1_id.value<org::ImmParagraph>();
    auto const& par2 = par2_id.value<org::ImmParagraph>();

    EXPECT_EQ(doc1.subnodes.size(), 1);
    EXPECT_EQ(doc1.indexOf(par1_id.id), 0);

    EXPECT_EQ(doc2.subnodes.size(), 1);
    EXPECT_EQ(doc2.indexOf(par2_id.id), 0);


    auto space_id = par1_id.at(1);
    auto word0_id = par1_id.at(0);
    auto word2_id = par1_id.at(2);
    auto word4_id = par1_id.at(4);

    EXPECT_EQ(space_id, par1_id.at(3));
    EXPECT_EQ(space_id, par2_id.at(1));
    EXPECT_EQ(space_id, par2_id.at(3));

    EXPECT_TRUE(store2.track->isParentOf(par2_id.id, space_id.id));
    {
        auto parents = store.track->getParentIds(space_id.id);
        EXPECT_EQ(parents.size(), 1);
        EXPECT_EQ(parents.at(0), par1_id.id);
    }

    {
        auto parents = store2.track->getParentIds(space_id.id);
        EXPECT_EQ(parents.size(), 1);
        EXPECT_EQ(parents.at(0), par2_id.id);
    }


    EXPECT_EQ(word0_id->getKind(), OrgSemKind::Word);
    EXPECT_EQ(word2_id->getKind(), OrgSemKind::Word);
    EXPECT_EQ(word4_id->getKind(), OrgSemKind::Word);

    EXPECT_EQ(word0_id.value<org::ImmWord>().text, "word0");
    EXPECT_EQ(word2_id.value<org::ImmWord>().text, "word2");
    EXPECT_EQ(word4_id.value<org::ImmWord>().text, "word4");

    auto gv = org::toGraphviz(
        {version1, version2},
        org::ImmAstGraphvizConf{
            .skippedKinds = SemSet{OrgSemKind::Space},
        });

    Graphviz gvc;
    gvc.renderToFile("/tmp/ReplaceSubnodeAtPath.png", gv);
    gvc.writeFile("/tmp/ReplaceSubnodeAtPath.dot", gv);
}


struct ImmOrgApiEdit : ImmOrgApiTestBase {};

Vec<int> getDfsSubtreeLevels(org::ImmAdapter n) {
    Vec<int>                    result;
    Func<void(org::ImmAdapter)> aux;
    aux = [&](org::ImmAdapter n) {
        if (auto tree = n.asOpt<org::ImmSubtree>()) {
            result.push_back(tree.value()->level);
        }
        for (auto const& it : n.sub()) { aux(it); }
    };
    aux(n);
    return result;
}

Str getSubtreeDash() {
    // 0     * s1
    // 0.0   ** s200
    // 0.0.0 *** s3000
    // 0.0.1 *** s3001
    // 0.1   ** s201
    // 0.1.0 *** s3010
    return R"(* s1
** s200
*** s3000
*** s3001
** s201
*** s3010
)";
}

TEST_F(ImmOrgApiEdit, LeafSubtreeDemote) {
    setTraceFile(getDebugFile("trace.txt"));
    org::ImmAstVersion v1 = getInitialVersion(getSubtreeDash());

    {
        auto root = v1.getRootAdapter();
        writeFile(
            "/tmp/SubtreePromotion_repr.txt",
            root.treeRepr().toString(false));
    }

    Vec<int> path{0, 1, 0};

    org::ImmAstVersion v2 = v1.getEditVersion(
        [&](org::ImmAstContext&     ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            auto root  = v1.getRootAdapter();
            auto s3010 = root.at(path);
            EXPECT_EQ(s3010->getKind(), OrgSemKind::Subtree);
            EXPECT_EQ(s3010->as<org::ImmSubtree>()->level, 3);
            return demoteSubtree(
                s3010, org::SubtreeMove::ForceLevels, ctx);
        });

    org::ImmAdapter::TreeReprConf conf{.withAuxFields = true};

    writeFile(
        getDebugFile("repr_v1.txt"),
        v1.getRootAdapter().treeRepr(conf).toString(false));

    writeFile(
        getDebugFile("repr_v2.txt"),
        v2.getRootAdapter().treeRepr(conf).toString(false));

    ColStream os;
    start.format(os);
    writeFile(getDebugFile("store.txt"), os.getBuffer().toString(false));
    writeGvHistory({v1, v2}, "v1_v2");

    {
        auto r     = v1.getRootAdapter();
        auto s3010 = r.at(path);
        EXPECT_EQ(s3010->getKind(), OrgSemKind::Subtree);
        EXPECT_EQ(s3010->as<org::ImmSubtree>()->level, 3);
        auto levels = getDfsSubtreeLevels(r);
        EXPECT_EQ(levels, (Vec<int>{1, 2, 3, 3, 2, 3}));
    }

    {
        auto r     = v2.getRootAdapter();
        auto s3010 = r.at(path);
        EXPECT_EQ(s3010->getKind(), OrgSemKind::Subtree);
        EXPECT_EQ(s3010->as<org::ImmSubtree>()->level, 4);
        auto levels = getDfsSubtreeLevels(r);
        EXPECT_EQ(levels, (Vec<int>{1, 2, 3, 3, 2, 4}));
    }
}

TEST_F(ImmOrgApiEdit, RecursiveSubtreeDemote_OneNested) {
    setTraceFile(getDebugFile("trace.txt"));
    org::ImmAstVersion v1 = getInitialVersion(getSubtreeDash());
    writeTreeRepr(v1.getRootAdapter(), "repr_v1.txt");

    org::ImmAstVersion v2 = v1.getEditVersion(
        [&](org::ImmAstContext&     ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            auto root = v1.getRootAdapter();
            auto s201 = root.at(Vec{0, 1});
            EXPECT_EQ(s201->getKind(), OrgSemKind::Subtree);
            EXPECT_EQ(s201->as<org::ImmSubtree>()->level, 2);
            return demoteSubtree(s201, org::SubtreeMove::ForceLevels, ctx);
        });

    writeGvHistory({v1, v2}, "v1_v2");

    auto r = v2.getRootAdapter();
    writeTreeRepr(r, "repr_v2.txt");
    auto s201 = r.at(Vec{0, 0, 2});
    EXPECT_EQ(s201->getKind(), OrgSemKind::Subtree);
    EXPECT_EQ(s201->as<org::ImmSubtree>()->level, 3);
    auto s3010 = r.at({0, 0, 2, 0});
    EXPECT_EQ(s3010->getKind(), OrgSemKind::Subtree);
    EXPECT_EQ(s3010->as<org::ImmSubtree>()->level, 4);
    auto levels = getDfsSubtreeLevels(r);
    EXPECT_EQ(levels, (Vec<int>{1, 2, 3, 3, 3, 4}));
}

TEST_F(ImmOrgApiEdit, RecursiveSubtreeDemote_All) {
    setTraceFile(getDebugFile("trace.txt"));
    org::ImmAstVersion v1 = getInitialVersion(getSubtreeDash());

    org::ImmAstVersion v2 = v1.getEditVersion(
        [&](org::ImmAstContext&     ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            auto root = v1.getRootAdapter();
            auto s1   = root.at(0);
            return demoteSubtree(s1, org::SubtreeMove::ForceLevels, ctx);
        });

    writeGvHistory({v1, v2}, "v1_v2");

    EXPECT_EQ(
        getDfsSubtreeLevels(v1.getRootAdapter()),
        (Vec<int>{1, 2, 3, 3, 2, 3}));

    EXPECT_EQ(
        getDfsSubtreeLevels(v2.getRootAdapter()),
        (Vec<int>{2, 3, 4, 4, 3, 4}));
}

TEST_F(ImmOrgApiEdit, RecursiveSubtreeDemote_WithParentChange) {
    setTraceFile(getDebugFile("trace.txt"));
    org::ImmAstVersion v1 = getInitialVersion(getSubtreeDash());

    auto demotePath = [&](org::ImmAstVersion v,
                          CVec<int>          path) -> org::ImmAstVersion {
        return v.getEditVersion(
            [&](org::ImmAstContext&     ast,
                org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
                auto root = v.getRootAdapter();
                auto s1   = root.at(path);
                return demoteSubtree(
                    s1, org::SubtreeMove::ForceLevels, ctx);
            });
    };

    org::ImmAstVersion v2 = demotePath(v1, {0, 0, 1});

    {
        auto r = v2.getRootAdapter();

        writeTreeRepr(v1.getRootAdapter(), "repr_v1.txt");
        writeTreeRepr(v2.getRootAdapter(), "repr_v2.txt");
        writeGvHistory({v1, v2}, "v1_v2");

        EXPECT_EQ(getDfsSubtreeLevels(r), (Vec<int>{1, 2, 3, 4, 2, 3}));

        Vec<int> p0000 = {0, 0, 0, 0};
        Vec<int> p000  = {0, 0, 0};
        Vec<int> p00   = {0, 0};
        Vec<int> p0    = {0};


        EXPECT_TRUE(r.at(p0000).is(OrgSemKind::Subtree));
        EXPECT_EQ(r.at(p0000).as<org::ImmSubtree>()->level, 4);
        EXPECT_EQ(r.at(p0000).getParent().value().id, r.at(p000).id);
        EXPECT_EQ(r.at(p000).at(0).id, r.at(p0000).id);

        EXPECT_EQ(r.at(p000).as<org::ImmSubtree>()->level, 3);
        EXPECT_EQ(r.at(p000).getParent().value().id, r.at(p00).id);
        EXPECT_EQ(r.at(p00).at(0).id, r.at(p000).id);

        EXPECT_EQ(r.at(p00).as<org::ImmSubtree>()->level, 2);
        EXPECT_EQ(r.at(p0).at(0).id, r.at(p00).id);
    }

    org::ImmAstVersion v3 = demotePath(v2, {0, 1});
    writeTreeRepr(v3.getRootAdapter(), "repr_v3.txt");
    org::ImmAstVersion v4 = demotePath(v3, {0, 0, 1});
    writeTreeRepr(v4.getRootAdapter(), "repr_v4.txt");
    org::ImmAstVersion v5 = demotePath(v4, {0, 0, 0, 1});
    writeTreeRepr(v5.getRootAdapter(), "repr_v5.txt");
    writeGvHistory(
        {v1, v2, v3, v4, v5},
        "v_final",
        org::ImmAstGraphvizConf{
            .withAuxNodes      = true,
            .withEditHistory   = false,
            .withEpochClusters = false,
        });

    {
        auto r = v5.getRootAdapter();
        EXPECT_TRUE(
            r.at({0, 0, 0, 0, 0, 0}).isSubnodeOf(r.at({0, 0, 0, 0, 0})));
        EXPECT_EQ(
            r.at({0, 0, 0, 0, 0, 0}).as<org::ImmSubtree>()->level, 6);
        EXPECT_EQ(
            r.at({0, 0, 0, 0, 0, 0}).as<org::ImmSubtree>()->level, 6);
        EXPECT_EQ(r.at({0, 0, 0, 0, 0}).as<org::ImmSubtree>()->level, 5);
        EXPECT_EQ(r.at({0, 0, 0, 0}).as<org::ImmSubtree>()->level, 4);
        EXPECT_EQ(r.at({0, 0, 0}).as<org::ImmSubtree>()->level, 3);
    }
}

TEST_F(ImmOrgApiEdit, PhysicalDemote) {
    setTraceFile(getDebugFile("trace.txt"));
    org::ImmAstVersion v1 = getInitialVersion(getSubtreeDash());
    writeTreeRepr(v1.getRootAdapter(), "repr_v1.txt");

    org::ImmAstVersion v2 = v1.getEditVersion(
        [&](org::ImmAstContext&     ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            auto root = v1.getRootAdapter();
            auto s1   = root.at(Vec{0, 0});
            return demoteSubtree(s1, org::SubtreeMove::Physical, ctx);
        });

    writeGvHistory({v1, v2}, "v1_v2");
    writeTreeRepr(v2.getRootAdapter(), "repr_v2.txt");

    EXPECT_EQ(
        getDfsSubtreeLevels(v1.getRootAdapter()),
        (Vec<int>{1, 2, 3, 3, 2, 3}));

    EXPECT_EQ(
        getDfsSubtreeLevels(v2.getRootAdapter()),
        (Vec<int>{1, 3, 3, 3, 2, 3}));
}

TEST_F(ImmOrgApiEdit, ResetTitle) {
    setTraceFile(getDebugFile("trace.txt"));
    org::ImmAstVersion v1 = getInitialVersion("* subtree");
    writeTreeRepr(v1.getRootAdapter(), "repr_v1.txt");

    org::ImmAstVersion v2 = v1.getEditVersion(
        [&](org::ImmAstContext&     ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            return ctx.store().updateNode<org::ImmSubtree>(
                v1.getRootAdapter().at(0), ctx, [&](org::ImmSubtree tree) {
                    tree.title = ctx->add(
                                        sem::asOneNode(
                                            sem::parseString("replaced")),
                                        ctx)
                                     .as<org::ImmParagraph>();
                    return tree;
                });
        });

    writeGvHistory({v1, v2}, "v1_v2");
    writeTreeRepr(v2.getRootAdapter(), "repr_v2.txt");

    {
        auto tree = v1.getRootAdapter().at(0).as<org::ImmSubtree>();
        EXPECT_EQ(
            tree.pass(tree->title).at(0).as<org::ImmWord>()->text,
            "subtree");
    }

    {
        auto tree = v2.getRootAdapter().at(0).as<org::ImmSubtree>();
        EXPECT_EQ(
            tree.pass(tree->title).at(0).as<org::ImmWord>()->text,
            "replaced");
    }
}

TEST_F(ImmOrgApiEdit, MoveSubnodes) {
    setTraceFile(getDebugFile("trace.txt"));
    org::ImmAstVersion v1 = getInitialVersion("zero one two three");

    auto move =
        [&](int position, int offset, bool bounded) -> org::ImmAstVersion {
        return v1.getEditVersion(
            [&](org::ImmAstContext&     ast,
                org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
                auto update = moveSubnode(
                    v1.getRootAdapter().at(0),
                    position,
                    offset,
                    ctx,
                    bounded);
                if (update) {
                    return *update;
                } else {
                    return {};
                }
            });
    };

    Func<Vec<Str>(org::ImmAdapter const&)> flat;
    flat = [&](org::ImmAdapter const& it) -> Vec<Str> {
        Vec<Str> result;
        if (auto i = it.asOpt<org::ImmWord>(); i) {
            result.push_back(i.value()->text);
        } else if (auto i = it.asOpt<org::ImmSpace>(); i) {
            result.push_back(i.value()->text);
        } else {
            for (auto const& sub : it.sub()) { result.append(flat(sub)); }
        }

        return result;
    };

    writeGvHistory({v1}, "graph_v1");

    org::ImmAstVersion v2 = move(0, 2, true);
    org::ImmAstVersion v3 = move(0, 4, true);
    org::ImmAstVersion v4 = move(2, -2, true);

    writeGvHistory({v1, v2, v3, v4}, "graph");
    EXPECT_EQ(
        flat(v1.getRootAdapter()),
        (Vec<Str>{"zero", " ", "one", " ", "two", " ", "three"}));
    EXPECT_EQ(
        flat(v2.getRootAdapter()),
        (Vec<Str>{" ", "one", "zero", " ", "two", " ", "three"}));
    EXPECT_EQ(
        flat(v3.getRootAdapter()),
        (Vec<Str>{" ", "one", " ", "two", "zero", " ", "three"}));
    EXPECT_EQ(
        flat(v4.getRootAdapter()),
        (Vec<Str>{"one", "zero", " ", " ", "two", " ", "three"}));
}

struct ImmOrgApiAppModel : ImmOrgApiTestBase {
    struct Row {
        org::ImmAdapter nameOrigin;
        std::string     name;
        org::ImmAdapter storyEventOrigin;
        std::string     storyEvent;
        Vec<Row>        nested;
        DESC_FIELDS(
            Row,
            (nameOrigin, name, storyEventOrigin, storyEvent, nested));
    };

    Row buildRow(org::ImmAdapterT<org::ImmSubtree> tree) {
        Row result;
        result.name       = join(" ", flatWords(tree.getTitle()));
        result.nameOrigin = tree.getTitle();
        for (auto const& sub : tree.subAs<org::ImmList>()) {
            if (sub.isDescriptionList()) {
                for (auto const& item : sub.subAs<org::ImmListItem>()) {
                    auto flat = flatWords(item.getHeader().value());
                    for (auto const& word : flat) {
                        if (word == "story_event") {
                            result.storyEventOrigin = item.at(0);
                            result.storyEvent       = join(
                                " ", flatWords(item.at(0)));
                        }
                    }
                }
            }
        }

        for (auto const& sub : tree.subAs<org::ImmSubtree>()) {
            result.nested.push_back(buildRow(sub));
        }

        return result;
    }

    Vec<Row> buildRows(org::ImmAdapter root) {
        Vec<Row> result;
        for (auto const& tree : root.subAs<org::ImmSubtree>()) {
            result.push_back(buildRow(tree));
        }

        return result;
    }
};

TEST_F(ImmOrgApiAppModel, CreateModel) {
    org::ImmAstVersion v1 = getInitialVersion(R"(
* Entry 1
** Subtree 2

- =story_event= :: Description

** Subtree 3
)");

    Vec<Row> rows = buildRows(v1.getRootAdapter());
    EXPECT_EQ(rows.size(), 1);
    EXPECT_EQ(rows.at(0).nested.size(), 2);
    EXPECT_EQ(rows.at(0).name, "Entry 1");
    EXPECT_EQ(rows.at(0).nested.at(0).name, "Subtree 2");
    EXPECT_EQ(rows.at(0).nested.at(0).storyEvent, "Description");
}

TEST_F(ImmOrgApiAppModel, EditModel) {
    setTraceFile(getDebugFile("trace.txt"));
    org::ImmAstVersion v1 = getInitialVersion(R"(
* Entry 1
** Subtree 2
- =story_event= :: Description
)");

    Vec<Row> rows1 = buildRows(v1.getRootAdapter());
    writeTreeRepr(v1.getRootAdapter(), "v1.txt");
    {
        EXPECT_EQ(rows1.size(), 1);
        EXPECT_EQ(rows1.at(0).nested.size(), 1);
        EXPECT_EQ(rows1.at(0).name, "Entry 1");
        EXPECT_EQ(rows1.at(0).nested.at(0).name, "Subtree 2");
        EXPECT_EQ(rows1.at(0).nested.at(0).storyEvent, "Description");
    }

    org::ImmAstVersion v2 = v1.getEditVersion(
        [&](org::ImmAstContext&     ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            auto                    t2 = rows1.at(0).nested.at(0);
            org::ImmAstReplaceGroup result;
            result.incl(org::replaceNode(
                t2.nameOrigin,
                ast.add(
                    sem::asOneNode(sem::parseString("New title")), ctx),
                ctx));
            result.incl(org::replaceNode(
                t2.storyEventOrigin,
                ast.add(
                    sem::asOneNode(
                        sem::parseString("New story event description")),
                    ctx),
                ctx));
            return result;
        });

    writeTreeRepr(v2.getRootAdapter(), "v2.txt");
    writeGvHistory(
        {v1, v2},
        "graph.png",
        org::ImmAstGraphvizConf{
            .withAuxNodes    = true,
            .withEditHistory = false,
        });
    {
        Vec<Row> rows2 = buildRows(v2.getRootAdapter());
        EXPECT_EQ(rows2.size(), 1);
        EXPECT_EQ(rows2.at(0).nested.size(), 1);
        EXPECT_EQ(rows2.at(0).name, "Entry 1");
        EXPECT_EQ(rows2.at(0).nested.at(0).name, "New title");
        EXPECT_EQ(
            rows2.at(0).nested.at(0).storyEvent,
            "New story event description");
    }
}


TEST(ImmMapApi, AddNode) {
    auto n1 = parseNode("* subtree");

    org::ImmAstContext    store;
    org::graph::MapConfig conf;
    conf.setTraceFile(getDebugFile("ImmMapApi_AddNode.txt"));
    org::ImmAstVersion        v1 = store.addRoot(n1);
    org::graph::MapGraphState s1{v1.context};
    EXPECT_EQ(s1.graph.nodeCount(), 0);
    org::graph::addNode(s1, v1.getRootAdapter(), conf);
    EXPECT_EQ(s1.graph.nodeCount(), 1);

    Graphviz gvc;
    auto     gv = s1.graph.toGraphviz(v1.context);
    gvc.renderToFile(getDebugFile("MapS2.png"), gv);
}

TEST(ImmMapApi, AddNodeWithLinks) {
    Str text{R"(
Paragraph [[id:subtree-id]]

* Subtree
  :properties:
  :id: subtree-id
  :end:
)"_ss};

    auto n1 = parseNode(text);

    org::ImmAstContext    store;
    org::graph::MapConfig conf;
    conf.setTraceFile(getDebugFile("log"));
    store.debug->setTraceFile(conf.getTraceFile());
    org::ImmAstVersion v1   = store.addRoot(n1);
    auto               root = v1.getRootAdapter();

    org::graph::MapGraphState s1{v1.context};

    EXPECT_EQ(s1.graph.nodeCount(), 0);
    EXPECT_EQ(s1.graph.edgeCount(), 0);
    EXPECT_EQ(s1.unresolved.size(), 0);

    conf.message("add first node");
    {
        auto __scope = conf.scopeLevel();
        auto par     = root.at(1);
        org::graph::addNode(s1, par, conf);
        EXPECT_EQ(par->getKind(), OrgSemKind::Paragraph);
        EXPECT_EQ(s1.graph.nodeCount(), 1);
        EXPECT_EQ(s1.graph.edgeCount(), 0);
        ASSERT_EQ(s1.unresolved.size(), 1);
        EXPECT_EQ(*s1.unresolved.begin(), par.uniq());
    }

    conf.message("add second node");
    {
        auto __scope = conf.scopeLevel();
        org::graph::addNode(s1, root.at(3), conf);
        EXPECT_EQ(s1.graph.nodeCount(), 2);
        EXPECT_EQ(s1.graph.edgeCount(), 1);
        EXPECT_EQ(s1.unresolved.size(), 0);
    }

    Graphviz gvc;
    auto     gv = s1.graph.toGraphviz(v1.context);
    gvc.renderToFile(getDebugFile("AddNodeWithLinks.png"), gv);
}


TEST(ImmMapApi, SubtreeBacklinks) {
    Str text1{R"(
* Subtree1
  :properties:
  :id: subtree-1
  :end:

#+attr_list: :attached subtree
- [[id:subtree-2]] :: Forward link
)"_ss};

    Str text2{R"(
* Subtree2
  :properties:
  :id: subtree-2
  :end:

#+attr_list: :attached subtree
- [[id:subtree-1]] :: Backlink
)"_ss};

    auto n1 = parseNode(text1);
    auto n2 = parseNode(text2);

    org::ImmAstContext    store;
    org::graph::MapConfig conf;
    conf.setTraceFile(getDebugFile("SubtreeBacklinks_log.txt"));

    org::ImmAstVersion v2 = store.addRoot(n1);
    org::ImmAstVersion v3 = v2.context.addRoot(n2);


    org::graph::MapGraphState s1{v3.context};

    EXPECT_EQ(s1.graph.nodeCount(), 0);
    EXPECT_EQ(s1.graph.edgeCount(), 0);
    EXPECT_EQ(s1.unresolved.size(), 0);

    org::graph::addNode(s1, v2.getRootAdapter().at(1), conf);
    EXPECT_EQ(s1.graph.nodeCount(), 1);
    EXPECT_EQ(s1.graph.edgeCount(), 0);
    EXPECT_EQ(s1.unresolved.size(), 1);

    org::graph::addNode(s1, v3.getRootAdapter().at(1), conf);
    EXPECT_EQ(s1.graph.nodeCount(), 2);
    EXPECT_EQ(s1.graph.edgeCount(), 2);
    EXPECT_EQ(s1.unresolved.size(), 0);

    Graphviz gvc;
    auto     gv = s1.graph.toGraphviz(v3.context);
    gvc.renderToFile(getDebugFile("SubtreeBacklinks.png"), gv);
}

Str getFullMindMapText() {
    Vec<Str> text{
        R"(
* Mind map nodes are made from subtrees
)",
        R"(
** Subtrees can be nested for clustering
   :PROPERTIES:
   :ID:       c468e9c7-7422-4b17-8ccb-53575f186fe0
   :END:
)",
        R"(
** More than one subtree can exist in cluster
)",
        R"(
Tree  description, maybe  on multiple  lines.
Can include  [[id:c468e9c7-7422-4b17-8ccb-53575f186fe0][links]] to  other trees.
Links are attached to specific [[id:6d6d6689-d9da-418d-9f91-1c8c4428e5af][rows]] in the text
so it is easier to track which part of the
description refers to the [[id:9879fed7-f0a4-44bd-bf56-983279afc622][other]] tree
)",
        R"(- )",
        R"(when [[id:c468e9c7-7422-4b17-8ccb-53575f186fe0][link]] :: Description lists can be used for annotated links

)",
        R"(  Multiple paragraphs attached to link
)",
        R"(
used in description list it's placed as annotation to the graph node.
Description can take multiple lines[fn:lines-20].
)",
        R"(
[fn:lines-20]  Footnotes  are placed  into  separate  nodes. You  can  have
nested[fn:nested-23]
)",
        R"(
[fn:nested-23] footnotes
)",
        R"(
** Extra entries
   :PROPERTIES:
   :ID:       6d6d6689-d9da-418d-9f91-1c8c4428e5af
   :END:
)",
        R"(
Parent subtrees can contain some things.
)",
        R"(
* Several clusters can exist
)",
        R"(
Nested subtrees
Multiline [[id:6d6d6689-d9da-418d-9f91-1c8c4428e5af][Extra entries]]
)",
        R"(
** With multiple nodes
   :PROPERTIES:
   :ID:       9879fed7-f0a4-44bd-bf56-983279afc622
   :END:
)",
        R"(
** And even nested
)",
        R"(
*** Clusters
)",
        R"(
*** And nodes
)",
        R"(
*** Intercluster links are possible
)",
        R"(
[[id:c468e9c7-7422-4b17-8ccb-53575f186fe0][Annotation for the target subtree]]
[[id:XXSDASD][Unresolved subtree]]
)",
        "- ",
        "Regular list element\n",
        "- ",
        "Two items in a list\n",
    };
    return join("", text);
}

using osk = OrgSemKind;

TEST(ImmMapApi, SubtreeFullMap) {
    auto n = parseNode(getFullMindMapText());

    org::ImmAstContext store;

    org::ImmAstVersion        v2 = store.addRoot(n);
    org::graph::MapGraphState s1{v2.context};
    org::ImmAdapter           file = v2.getRootAdapter();

    EXPECT_EQ(file.at(1)->getKind(), osk::Subtree);
    auto node_s10  = file.at(Vec{1, 0});
    auto node_p110 = file.at({1, 1, 0});
    auto node_s12  = file.at(Vec{1, 2});
    EXPECT_EQ(node_s10->getKind(), osk::Subtree);
    EXPECT_EQ(
        node_s10.as<org::ImmSubtree>()->treeId->value(),
        "c468e9c7-7422-4b17-8ccb-53575f186fe0");

    EXPECT_EQ(node_s12->getKind(), osk::Subtree);
    EXPECT_EQ(
        node_s12.as<org::ImmSubtree>()->treeId->value(),
        "6d6d6689-d9da-418d-9f91-1c8c4428e5af");


    org::graph::MapConfig conf;
    conf.setTraceFile(getDebugFile("conf"));
    addNodeRec(s1, v2.getRootAdapter(), conf);

    EXPECT_TRUE(s1.graph.hasEdge(node_p110.uniq(), node_s12.uniq()));
    EXPECT_TRUE(s1.graph.hasEdge(node_p110.uniq(), node_s10.uniq()));

    Graphviz gvc;
    auto     gv = s1.graph.toGraphviz(v2.context);
    gv.setRankDirection(Graphviz::Graph::RankDirection::LR);
    gvc.writeFile("/tmp/SubtreeFullMap.dot", gv);
    gvc.renderToFile("/tmp/SubtreeFullMap.png", gv);
}

Str getSubtreeBlockText() {
    return Str{R"str(
* Subtree 1
  :properties:
  :id: subtree_1
  :end:

#+attr_list: :attached subtree
- [[id:subtree_2]] :: Describe link to subtree 2
- [[internal_1]] :: Describe link to internal

<<internal_1>> Internal paragraph [fn:footnote_1]

#+begin_comment :attach above
Comment for the paragraph content above
#+end_comment

[fn:footnote_1] Definition of the footnote 1

Second paragraph [fn:footnote_2]

[fn:footnote_2] Footnote 2 [fn:recursive_1]

[fn:recursive_1] Recursive footnote 1 [fn:recursive_2]

[fn:recursive_2] Recursive footnote 2

* Subtree 2
  :properties:
  :id: subtree_2
  :end:

- [[id:subtree_2]] :: Standalone description list targeting subtree
- [[id:subtree_1]] :: Targeting subtree one
- [[internal_1]] :: Targeting standalone paragraph 1
- [[named-paragraph-one]] :: Targeting named paragraph

#+name: named-paragraph-one
Paragraph with name annotations
)str"};
}

struct DocItem {
    org::ImmAdapter id;
    DESC_FIELDS(DocItem, (id));
};

struct DocBlock {
    Vec<DocItem>  items;
    Vec<DocBlock> nested;
    DESC_FIELDS(DocBlock, (items, nested));
};

DocBlock fromAst(org::ImmAdapter const& id) {
    SemSet Skip{OrgSemKind::Newline};

    DocBlock result;
    switch (id->getKind()) {
        case OrgSemKind::Document: {
            for (auto const& sub : id.sub()) {
                if (!Skip.contains(sub->getKind())) {
                    result.nested.push_back(fromAst(sub));
                }
            }
            break;
        }
        case OrgSemKind::Subtree: {
            result.items.push_back(DocItem{.id = id});
            for (auto const& sub : id.sub()) {
                if (!Skip.contains(sub->getKind())) {
                    result.nested.push_back(fromAst(sub));
                }
            }
            break;
        }

        default: {
            if (!org::graph::isAttachedDescriptionList(id)) {
                result.items.push_back(DocItem{.id = id});
            }

            break;
        }
    }

    return result;
}

void addAll(
    org::graph::MapGraphState& state,
    DocBlock const&            block,
    org::graph::MapConfig&     conf) {
    for (auto const& it : block.items) {
        org::graph::addNode(state, it.id, conf);
    }

    for (auto const& it : block.nested) { addAll(state, it, conf); }
}

TEST(ImmMapApi, SubtreeBlockMap) {
    auto n = parseNode(getSubtreeBlockText());
    sem::exportToTreeFile(
        n,
        getDebugFile("sem_tree.txt"),
        sem::OrgTreeExportOpts{
            .withColor = false,
        });


    org::ImmAstContext store;
    store.debug->setTraceFile(getDebugFile("store"));
    org::ImmAstVersion v    = store.addRoot(n);
    org::ImmAdapter    root = v.getRootAdapter();

    writeTreeRepr(
        root,
        "imm_path.txt",
        org::ImmAdapter::TreeReprConf{
            .withAuxFields = true,
        });


    writeTreeRepr(
        root,
        "imm_tree.txt",
        org::ImmAdapter::TreeReprConf{
            .withReflFields = true,
            .withAuxFields  = true,
        });


    org::graph::MapConfig conf;
    conf.setTraceFile(getDebugFile("graph"));
    org::graph::MapGraphState state{v.context};
    DocBlock                  doc = fromAst(root);
    addAll(state, doc, conf);

    org::ImmAdapter comment   = root.at({1, 3});
    org::ImmAdapter par_above = root.at({1, 1});
    EXPECT_EQ(comment->getKind(), OrgSemKind::BlockComment);
    EXPECT_EQ(par_above->getKind(), OrgSemKind::Paragraph);

    state.graph.addEdge(
        org::graph::MapEdge{
            .source = org::graph::MapNode{par_above.uniq()},
            .target = org::graph::MapNode{comment.uniq()}},
        org::graph::MapEdgeProp{});

    Graphviz gvc;
    auto     gv = state.graph.toGraphviz(v.context);
    // gv.setRankDirection(Graphviz::Graph::RankDirection::LR);
    gvc.writeFile(getDebugFile("map.dot"), gv);
    gvc.renderToFile(getDebugFile("map.png"), gv);

    // org::eachSubnodeRec(root, [](org::ImmAdapter const& it) {
    //     if (SemSet{
    //             OrgSemKind::Subtree,
    //             OrgSemKind::Paragraph,
    //             OrgSemKind::List}
    //             .contains(it->getKind())) {
    //         std::cout << getSelfTest(it).toBase() << std::endl;
    //     }
    // });

    auto List_1         = root.at(1).at(0);
    auto List_2         = root.at(2).at(0);
    auto Paragraph_10   = root.at(1).at(9);
    auto Paragraph_11   = root.at(1).at(11);
    auto Paragraph_12   = root.at(1).at(13);
    auto Paragraph_14   = root.at(2).at(0).at(0).at(0);
    auto Paragraph_16   = root.at(2).at(0).at(1).at(0);
    auto Paragraph_17   = root.at(2).at(0).at(2).at(0);
    auto Paragraph_19   = root.at(2).at(0).at(3).at(0);
    auto Paragraph_20   = root.at(2).at(1);
    auto Paragraph_3    = root.at(1).at(0).at(0).at(0);
    auto Paragraph_5    = root.at(1).at(0).at(1).at(0);
    auto Paragraph_6    = root.at(1).at(1);
    auto Paragraph_7    = root.at(1).at(3).at(0);
    auto Paragraph_8    = root.at(1).at(5);
    auto Paragraph_9    = root.at(1).at(7);
    auto Subtree_1      = root.at(1);
    auto Subtree_2      = root.at(2);
    auto BlockComment_1 = root.at(1).at(3);

    EXPECT_EQ(List_1->getKind(), OrgSemKind::List);
    EXPECT_EQ(List_2->getKind(), OrgSemKind::List);
    EXPECT_EQ(Paragraph_10->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_11->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_12->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_14->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_16->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_17->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_19->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_20->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_3->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_5->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_6->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_7->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_8->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Paragraph_9->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(Subtree_1->getKind(), OrgSemKind::Subtree);
    EXPECT_EQ(Subtree_2->getKind(), OrgSemKind::Subtree);
    EXPECT_EQ(BlockComment_1->getKind(), OrgSemKind::BlockComment);

    EXPECT_EQ(
        (org::flatWords(Paragraph_20)),
        (Vec<Str>{"Paragraph", "with", "name", "annotations"}));

    EXPECT_EQ(
        (org::flatWords(Paragraph_6)),
        (Vec<Str>{"Internal", "paragraph"}));


    EXPECT_EQ(
        (org::flatWords(Paragraph_9)), (Vec<Str>{"Second", "paragraph"}));

    EXPECT_EQ((org::flatWords(Paragraph_10)), (Vec<Str>{"Footnote", "2"}));

    EXPECT_EQ(
        (org::flatWords(Paragraph_11)),
        (Vec<Str>{"Recursive", "footnote", "1"}));

    EXPECT_EQ(
        (org::flatWords(Paragraph_12)),
        (Vec<Str>{"Recursive", "footnote", "2"}));


    EXPECT_EQ(
        (org::flatWords(Subtree_1.as<org::ImmSubtree>().getTitle())),
        (Vec<Str>{"Subtree", "1"}));

    EXPECT_EQ(
        (org::flatWords(Subtree_2.as<org::ImmSubtree>().getTitle())),
        (Vec<Str>{"Subtree", "2"}));

    auto& g = state.graph;

    g.hasEdge(List_2, Paragraph_20);
    g.hasEdge(List_2, Subtree_1);
    g.hasEdge(List_2, Subtree_2);
    g.hasEdge(List_2, Paragraph_6);
    g.hasEdge(Subtree_1, Subtree_2);
    g.hasEdge(Subtree_1, Paragraph_6);
    g.hasEdge(Paragraph_6, BlockComment_1);
    g.hasEdge(Paragraph_9, Paragraph_10);
    g.hasEdge(Paragraph_10, Paragraph_11);
    g.hasEdge(Paragraph_11, Paragraph_12);
}

TEST(ImmMapApi, Doc1Graph) {
    __perf_trace("imm", "run test");
    fs::path file = fs::path{std::getenv("HOME")}
                  / std::string{"tmp/doc_graph.org"};

    if (!fs::exists(file)) { return; }
    auto n = parseNode(readFile(file));

    org::ImmAstContext store;
    org::ImmAstVersion v = store.addRoot(n);
    // return;

    // writeTreeRepr(
    //     v.getRootAdapter(),
    //     "imm.txt",
    //     org::ImmAdapter::TreeReprConf{
    //         .withReflFields = true,
    //         .withAuxFields  = true,
    //     });

    {
        int count = 0;
        __perf_trace("imm", "iterate each sem node");
        sem::eachSubnodeRec(n, [&](sem::OrgArg) { ++count; });
        _dbg(count);
    }

    {
        int count = 0;
        __perf_trace("imm", "iterate each node with path");
        org::eachSubnodeRec(
            v.getRootAdapter(), true, [&](org::ImmAdapter const&) {
                ++count;
            });
        _dbg(count);
    }

    {
        int count = 0;
        __perf_trace("imm", "iterate each node without path");
        org::eachSubnodeRec(
            v.getRootAdapter(), false, [&](org::ImmAdapter const&) {
                ++count;
            });
        _dbg(count);
    }

    org::ImmAdapter root = v.getRootAdapter();

    org::graph::MapConfig     conf;
    org::graph::MapGraphState state{v.context};
    addNodeRec(state, root, conf);

    Graphviz                       gvc;
    org::graph::MapGraph::GvConfig gvConf;
    gvConf.acceptNode = [&](org::graph::MapNode const& node) {
        return 0 < state.graph.inDegree(node)
            || 0 < state.graph.outDegree(node);
    };
    auto gv = state.graph.toGraphviz(v.context, gvConf);
    gvc.writeFile(getDebugFile("map.dot"), gv);
    gvc.renderToFile(
        getDebugFile("map.png"),
        gv,
        Graphviz::RenderFormat::PNG,
        Graphviz::LayoutType::Sfdp);
}

struct TestGraph {
    org::graph::MapGraph     g;
    Vec<org::graph::MapNode> nodes;
};

TestGraph create_test_graph() {
    org::graph::MapGraph g{};

    auto n0 = org::ImmUniqId{org::ImmId::FromValue(0)};
    auto n1 = org::ImmUniqId{org::ImmId::FromValue(1)};
    auto n2 = org::ImmUniqId{org::ImmId::FromValue(2)};

    g.adjList = {
        {n0, {n1}},
        {n1, {n2}},
        {n2, {n0}},
    };

    g.nodeProps.insert_or_assign(n0, org::graph::MapNodeProp{});
    g.nodeProps.insert_or_assign(n1, org::graph::MapNodeProp{});
    g.nodeProps.insert_or_assign(n2, org::graph::MapNodeProp{});

    g.edgeProps.insert_or_assign({n0, n1}, org::graph::MapEdgeProp{});
    g.edgeProps.insert_or_assign({n1, n2}, org::graph::MapEdgeProp{});
    g.edgeProps.insert_or_assign({n2, n0}, org::graph::MapEdgeProp{});

    return TestGraph{
        .g     = g,
        .nodes = {n0, n1, n2},
    };
}


TEST(ImmMapApi, VertexCount) {
    auto g            = create_test_graph();
    auto num_vertices = boost::num_vertices(g.g);
    EXPECT_EQ(num_vertices, 3);
}

TEST(ImmMapApi, EdgeCount) {
    auto g         = create_test_graph();
    auto num_edges = boost::num_edges(g.g);
    EXPECT_EQ(num_edges, 3);
}

TEST(ImmMapApi, Vertices) {
    auto g                = create_test_graph();
    auto [v_begin, v_end] = boost::vertices(g.g);
    std::vector<org::graph::MapNode> vertices(v_begin, v_end);
    std::sort(vertices.begin(), vertices.end());

    EXPECT_EQ(vertices.size(), 3);
}

TEST(ImmMapApi, Edges) {
    auto g                = create_test_graph();
    auto [e_begin, e_end] = boost::edges(g.g);
    std::vector<org::graph::MapEdge> edges(e_begin, e_end);

    EXPECT_EQ(edges.size(), 3);
    EXPECT_NE(
        std::find(
            edges.begin(),
            edges.end(),
            org::graph::MapEdge{g.nodes.at(0), g.nodes.at(1)}),
        edges.end());
    EXPECT_NE(
        std::find(
            edges.begin(),
            edges.end(),
            org::graph::MapEdge{g.nodes.at(1), g.nodes.at(2)}),
        edges.end());
    EXPECT_NE(
        std::find(
            edges.begin(),
            edges.end(),
            org::graph::MapEdge{g.nodes.at(2), g.nodes.at(0)}),
        edges.end());
}

TEST(ImmMapApi, AdjacentVertices) {
    auto g                    = create_test_graph();
    auto [adj_begin, adj_end] = boost::adjacent_vertices(
        g.nodes.at(0), g.g);

    std::vector<org::graph::MapNode> adjacent_vertices(adj_begin, adj_end);

    EXPECT_EQ(adjacent_vertices.size(), 1);
    EXPECT_EQ(adjacent_vertices[0], g.nodes.at(1));
}

TEST(ImmMapApi, OutDegree) {
    auto g          = create_test_graph();
    auto out_degree = boost::out_degree(g.nodes.at(0), g.g);
    EXPECT_EQ(out_degree, 1);
}

TEST(ImmMapApi, OutEdges) {
    auto g                  = create_test_graph();
    auto [oe_begin, oe_end] = boost::out_edges(g.nodes.at(0), g.g);
    std::vector<org::graph::MapEdge> out_edges(oe_begin, oe_end);

    EXPECT_EQ(out_edges.size(), 1);
    EXPECT_EQ(
        out_edges[0], (org::graph::MapEdge{g.nodes.at(0), g.nodes.at(1)}));
}

TEST(ImmMapApi, SourceAndTarget) {
    auto                g = create_test_graph();
    org::graph::MapEdge e{g.nodes.at(0), g.nodes.at(1)};
    auto                src = boost::source(e, g.g);
    auto                tgt = boost::target(e, g.g);

    EXPECT_EQ(src, g.nodes.at(0));
    EXPECT_EQ(tgt, g.nodes.at(1));
}

TEST(ImmMapApi, BoostPropertyWriter) {
    auto n = parseNode(getFullMindMapText());

    org::ImmAstContext        store;
    org::graph::MapConfig     conf;
    org::ImmAstVersion        v2   = store.addRoot(n);
    org::ImmAdapter           file = v2.getRootAdapter();
    org::graph::MapGraphState s1{v2.context};
    addNodeRec(s1, file, conf);

    std::stringstream os;

    auto dp = org::graph::toGraphvizDynamicProperties(s1.graph);

    write_graphviz_dp(os, s1.graph, dp);

    writeFile("/tmp/BoostPropertyWriter.dot", os.str());
}
