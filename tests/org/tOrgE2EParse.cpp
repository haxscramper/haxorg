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
#include <haxorg/sem/ImmOrgGraph.hpp>
#include <haxorg/sem/ImmOrgGraphBoost.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/graphviz.hpp>
#include <fstream>

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
    p.run(source);
    return p.toNode();
}

TEST(OrgApi, LinkResolution) {
    MockFull    p{false, false};
    std::string source = R"(
* Subtree
  :properties:
  :id: id-name
  :end:
)";

    p.run(source);
    sem::OrgDocumentContext ctx;
    auto                    node = p.toNode();
    ctx.addNodes(node);

    auto subtree_result = ctx.getSubtreeById("id-name");
    EXPECT_EQ(subtree_result.size(), 1);
}

TEST(OrgDocumentSelector, GetMatchingNodeByKind) {
    auto                     node = parseNode("bold");
    sem::OrgDocumentSelector selector;
    selector.searchAnyKind({OrgSemKind::Word}, true);

    auto words = selector.getMatches(node);

    EXPECT_EQ(words.size(), 1);
    EXPECT_EQ(words.at(0)->getKind(), OrgSemKind::Word);
    EXPECT_EQ(words.at(0).as<sem::Word>()->text, "bold");
}

TEST(OrgDocumentSelector, GetMultipleMatchingNodesByKind) {
    auto                     node = parseNode("word *bold*");
    sem::OrgDocumentSelector selector;
    selector.searchAnyKind({OrgSemKind::Word}, true);

    auto words = selector.getMatches(node);

    EXPECT_EQ(words.size(), 2);
    EXPECT_EQ(words.at(0).as<sem::Word>()->text, "word");
    EXPECT_EQ(words.at(1).as<sem::Word>()->text, "bold");
}

TEST(OrgDocumentSelector, GetDirectlyNestedNode) {
    auto                     node = parseNode("word *bold*");
    sem::OrgDocumentSelector selector;
    selector.searchAnyKind(
        {OrgSemKind::Bold}, false, selector.linkDirectSubnode());
    selector.searchAnyKind({OrgSemKind::Word}, true);

    auto words = selector.getMatches(node);

    EXPECT_EQ(words.size(), 1);
    EXPECT_EQ(words.at(0)->getKind(), OrgSemKind::Word);
    EXPECT_EQ(words.at(0).as<sem::Word>()->text, "bold");
}

TEST(OrgDocumentSelector, GetSubtreeByTitle) {
    auto doc = parseNode(R"(
* Title1
** Subtitle1
** Subtitle2

Paragraph under subtitle 2

* Multi-part title
)");

    {
        sem::OrgDocumentSelector selector;
        selector.searchSubtreePlaintextTitle("Title1", true);

        auto title1 = selector.getMatches(doc);
        EXPECT_EQ(title1.size(), 1);
        EXPECT_EQ(title1.at(0)->getKind(), OrgSemKind::Subtree);
    }

    {
        sem::OrgDocumentSelector selector;
        selector.searchSubtreePlaintextTitle(
            "Subtitle2", false, selector.linkIndirectSubnode());
        selector.searchAnyKind({OrgSemKind::Word}, true);

        auto words = selector.getMatches(doc);
        EXPECT_EQ(words.size(), 5);
        // Subtree nodes are added as targets in the post-order DFS
        // traversal over all 'nested' elements. First the words in subtree
        // are collected.
        EXPECT_EQ(words.at(0).as<sem::Word>()->text, "Paragraph");
        EXPECT_EQ(words.at(1).as<sem::Word>()->text, "under");
        EXPECT_EQ(words.at(2).as<sem::Word>()->text, "subtitle");
        EXPECT_EQ(words.at(3).as<sem::Word>()->text, "2");
        // Then visitation gets to the subtree title itself. Nested fields
        // for each node are iterated starting from the base's fields and
        // then to the concrete type -- also in the DFS order.
        EXPECT_EQ(words.at(4).as<sem::Word>()->text, "Subtitle2");
    }

    {
        sem::OrgDocumentSelector selector;
        selector.searchSubtreePlaintextTitle(
            "Subtitle2", false, selector.linkField("subnodes"));
        selector.searchAnyKind({OrgSemKind::Word}, true);

        auto words = selector.getMatches(doc);
        EXPECT_EQ(words.size(), 4);
        // Subtree nodes are added as targets in the post-order DFS
        // traversal over all 'nested' elements. First the words in subtree
        // are collected.
        EXPECT_EQ(words.at(0).as<sem::Word>()->text, "Paragraph");
        EXPECT_EQ(words.at(1).as<sem::Word>()->text, "under");
        EXPECT_EQ(words.at(2).as<sem::Word>()->text, "subtitle");
        EXPECT_EQ(words.at(3).as<sem::Word>()->text, "2");
    }
}

TEST(OrgDocumentSelector, GetSubtreeAtPath) {
    auto node = parseNode(R"(
* Title1
** Subtitle1
Content1
** Subtitle2
Content2
* Title2
)");

    sem::OrgDocumentSelector selector;
    selector.searchSubtreePlaintextTitle(
        "Title1", false, selector.linkIndirectSubnode());
    selector.searchSubtreePlaintextTitle("Subtitle1", true);
    auto matches = selector.getMatches(node);
    EXPECT_EQ(matches.size(), 1);
}

TEST(OrgDocumentSelector, EarlyVisitExit) {
    auto node = parseNode(R"(
*** Content
Subnode
** Other content
First
*** Nested subtree
)");

    sem::OrgDocumentSelector      selector;
    UnorderedMap<OrgSemKind, int> counts;

    selector.searchPredicate(
        [&](sem::SemId<sem::Org> const& node) -> sem::OrgSelectorResult {
            ++counts[node->getKind()];
            return sem::OrgSelectorResult{
                .isMatching     = node->is(OrgSemKind::Subtree),
                .tryNestedNodes = !node->is(OrgSemKind::Subtree),
            };
        },
        false);

    selector.getMatches(node);

    EXPECT_EQ(counts.at(OrgSemKind::Subtree), 2);
    EXPECT_EQ(counts.at(OrgSemKind::Document), 1);
    EXPECT_EQ(counts.get(OrgSemKind::Word), std::nullopt);
}

TEST(OrgDocumentSelector, NonLeafSubtrees) {
    auto doc = parseNode(R"(
* s1
** s2
* s3
*** s4
* s5
* s6
** s7
)");

    sem::OrgDocumentSelector selector;
    selector.searchAnyKind(
        {OrgSemKind::Subtree}, true, selector.linkIndirectSubnode());

    selector.searchAnyKind({OrgSemKind::Subtree}, false);

    Vec<sem::SemId<sem::Org>> subtrees = selector.getMatches(doc);

    EXPECT_EQ(subtrees.size(), 3);
    auto titles = subtrees
                | rv::transform([](sem::SemId<sem::Org> const& id) -> Str {
                      return sem::formatToString(
                          id.as<sem::Subtree>()->title);
                  })
                | rs::to<Vec>();

    rs::sort(titles);
    EXPECT_EQ(titles.at(0), "s1");
    EXPECT_EQ(titles.at(1), "s3");
    EXPECT_EQ(titles.at(2), "s6");
}

TEST(OrgDocumentSelector, SubtreesWithDateInTitleAndBody) {
    auto doc = parseNode(R"(
* [2024-02-12] In title
* In description
[2024-02-12]
)");

    {
        sem::OrgDocumentSelector selector;
        selector.searchAnyKind(
            {OrgSemKind::Subtree}, true, selector.linkField("title"));
        selector.searchAnyKind({OrgSemKind::Time}, false);
        auto subtrees = selector.getMatches(doc);
        EXPECT_EQ(subtrees.size(), 1);
    }

    {
        sem::OrgDocumentSelector selector;
        selector.searchAnyKind(
            {OrgSemKind::Subtree}, true, selector.linkIndirectSubnode());
        selector.searchAnyKind({OrgSemKind::Time}, false);
        auto subtrees = selector.getMatches(doc);
        EXPECT_EQ(subtrees.size(), 2);
    }
}

TEST(OrgApi, EachSubnodeWithContext) {
    auto node = parseNode(R"(*bold*)");
    Vec<Pair<sem::SemId<sem::Org>, Vec<sem::SubnodeVisitorCtxPart>>> ctx;

    sem::eachSubnodeRecWithContext(
        node,
        [&](sem::SemId<sem::Org> id, CVec<sem::SubnodeVisitorCtxPart> part)
            -> sem::SubnodeVisitorResult {
            ctx.push_back({id, part});
            return sem::SubnodeVisitorResult{};
        });

    EXPECT_EQ(ctx.at(0).first->getKind(), OrgSemKind::Document);
    EXPECT_EQ(ctx.at(1).first->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(ctx.at(2).first->getKind(), OrgSemKind::Bold);
    EXPECT_EQ(ctx.at(3).first->getKind(), OrgSemKind::Word);

    EXPECT_EQ(ctx.at(0).second.size(), 0);
    EXPECT_EQ(ctx.at(1).second.size(), 2);
    EXPECT_EQ(ctx.at(1).second.at(0).field.value(), "subnodes");
    EXPECT_EQ(ctx.at(1).second.at(1).index.value(), 0);
}

template <typename T>
sem::SemId<T> getFirstNode(sem::SemId<sem::Org> node) {
    sem::OrgDocumentSelector selector;
    selector.searchAnyKind({T::staticKind}, true);
    return selector.getMatches(node).at(0).as<T>();
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

TEST(OrgApi, SubtreePropertyModification) {
    auto doc = parseNode(R"(
* Subtree
)");

    auto tree = getFirstNode<sem::Subtree>(doc);
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

    auto args = link1->getArguments("attach-on-export");
    EXPECT_TRUE(args.has_value());
    EXPECT_EQ(args.value()->args.size(), 1);
    auto arg0 = args.value()->args.at(0);
    EXPECT_EQ(arg0->getBool(), true);
    EXPECT_EQ(arg0->getString(), "t");
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


TEST(ImmOrgApi, StoreNode) {
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

TEST(ImmOrgApi, RountripImmutableAst) {
    std::string file   = (__CURRENT_FILE_DIR__ / "corpus/org/all.org");
    std::string source = readFile(fs::path(file));
    org::ImmAstContext store;
    sem::SemId         write_node = parseNode(source);
    auto [store2, immer_root]     = store.addRoot(write_node);
    sem::SemId read_node          = store2.get(immer_root);

    Vec<compare_report> out;

    reporting_comparator<sem::SemId<sem::Org>>::compare(
        write_node, read_node, out, {});
    show_compare_reports(out);
}

TEST(ImmOrgApi, ReplaceSubnodeAtPath) {
    auto start_node   = parseNode("word0 word2 word4");
    auto replace_node = parseNode("wordXX").at(0).at(0);
    // Document[0].Paragraph[0]

    org::ImmAstContext start;

    auto version1  = start.init(start_node);
    auto store     = version1.context;
    auto paragraph = store.at(version1.epoch.getRoot())->subnodes.at(0);

    auto ctx      = store.getEditContext();
    auto word_xx  = store.add(replace_node, ctx);
    auto version2 = store.finishEdit(
        ctx,
        ctx.store().cascadeUpdate(
            ctx.store().setSubnode(paragraph, word_xx, 2, ctx), ctx));

    auto        store2 = version2.context;
    auto const& c = gen_view(version2.epoch.replaced.allReplacements())
                  | rs::to<Vec>();

    auto const& doc1_id = c.at(1).original;
    auto const& doc2_id = c.at(1).replaced;
    auto const& par1_id = c.at(0).original;
    auto const& par2_id = c.at(0).replaced;

    EXPECT_EQ(doc1_id.getKind(), OrgSemKind::Document);
    EXPECT_EQ(doc2_id.getKind(), OrgSemKind::Document);

    EXPECT_EQ(doc1_id.getNodeIndex(), 1);
    EXPECT_EQ(doc2_id.getNodeIndex(), 2);

    EXPECT_EQ(par1_id.getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ(par2_id.getKind(), OrgSemKind::Paragraph);

    EXPECT_EQ(par1_id.getNodeIndex(), 1);
    EXPECT_EQ(par2_id.getNodeIndex(), 2);

    auto const& doc1 = store2.at_t<org::ImmDocument>(doc1_id);
    auto const& doc2 = store2.at_t<org::ImmDocument>(doc2_id);

    auto const& par1 = store2.at_t<org::ImmParagraph>(par1_id);
    auto const& par2 = store2.at_t<org::ImmParagraph>(par2_id);

    EXPECT_EQ(doc1->subnodes.size(), 1);
    EXPECT_EQ(doc1->indexOf(par1_id), 0);
    EXPECT_FALSE(store.hasParent(par2_id));
    EXPECT_TRUE(store.hasParent(par1_id));
    EXPECT_EQ(store.getParent(par1_id).value(), doc1_id);

    EXPECT_EQ(doc2->subnodes.size(), 1);
    EXPECT_EQ(doc2->indexOf(par2_id), 0);
    EXPECT_FALSE(store2.hasParent(par1_id));
    EXPECT_TRUE(store2.hasParent(par2_id));
    EXPECT_EQ(store2.getParent(par2_id).value(), doc2_id);

    auto word0_id = par1->subnodes.at(0);
    auto word2_id = par1->subnodes.at(2);
    auto word4_id = par1->subnodes.at(4);

    EXPECT_EQ(word0_id.getKind(), OrgSemKind::Word);
    EXPECT_EQ(word2_id.getKind(), OrgSemKind::Word);
    EXPECT_EQ(word4_id.getKind(), OrgSemKind::Word);

    EXPECT_EQ(store.at_t<org::ImmWord>(word0_id)->text, "word0");
    EXPECT_EQ(store.at_t<org::ImmWord>(word2_id)->text, "word2");
    EXPECT_EQ(store.at_t<org::ImmWord>(word4_id)->text, "word4");

    auto gv = org::toGraphviz(
        {version1, version2},
        org::ImmAstGraphvizConf{
            .skippedKinds = SemSet{OrgSemKind::Space},
        });

    Graphviz gvc;
    gvc.renderToFile("/tmp/ReplaceSubnodeAtPath.png", gv);
    gvc.writeFile("/tmp/ReplaceSubnodeAtPath.dot", gv);
}

class ImmOrgApiEdit : public ::testing::Test {
  public:
    org::ImmAstContext start;

    Str getDebugFile(Str const& suffix) {
        auto dir = fs::path{"/tmp/haxorg_tests/ImmOrgApiEdit"};
        if (!fs::is_directory(dir)) { fs::create_directory(dir); }
        return fmt(
            "{}/{}_{}",
            dir.native(),
            ::testing::UnitTest::GetInstance()
                ->current_test_info()
                ->name(),
            suffix);
    }

    void setTraceFile(std::string const& path) {
        start.debug->setTraceFile(path);
    }

    org::ImmAstVersion getInitialVersion(Str const& text) {
        return start.init(parseNode(text));
    }

    void writeTreeRepr(
        org::ImmAdapter               n,
        Str const                     suffix,
        org::ImmAdapter::TreeReprConf conf = org::ImmAdapter::TreeReprConf{
            .withAuxFields = false,
        }) {
        writeFile(getDebugFile(suffix), n.treeRepr(conf).toString(false));
    }

    void writeGvHistory(
        const Vec<org::ImmAstVersion>& history,
        std::string                    suffix,
        org::ImmAstGraphvizConf const& conf = org::ImmAstGraphvizConf{
            .withAuxNodes    = true,
            .withEditHistory = true,
            .withNodePath    = true,
        }) {
        Graphviz gvc;
        auto     gv = org::toGraphviz(history, conf);
        gvc.writeFile(getDebugFile(suffix + ".dot"), gv);
        gvc.renderToFile(getDebugFile(suffix + ".png"), gv);
    }
};

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
        auto root = start.adapt(v1.epoch.getRoot());
        writeFile(
            "/tmp/SubtreePromotion_repr.txt",
            root.treeRepr().toString(false));
    }

    Vec<int> path{0, 1, 0};

    org::ImmAstVersion v2 = v1.context.getEditVersion(
        [&](org::ImmAstContext&     ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            auto root  = ctx->adapt(v1.epoch.getRoot());
            auto s3010 = root.at(path);
            EXPECT_EQ(s3010->getKind(), OrgSemKind::Subtree);
            EXPECT_EQ(s3010->as<org::ImmSubtree>()->level, 3);
            return ast.store->demoteSubtree(
                s3010.id, org::ImmAstStore::SubtreeMove::ForceLevels, ctx);
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

    org::ImmAstVersion v2 = v1.context.getEditVersion(
        [&](org::ImmAstContext&     ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            auto root = ctx->adapt(v1.epoch.getRoot());
            auto s201 = root.at({0, 1});
            EXPECT_EQ(s201->getKind(), OrgSemKind::Subtree);
            EXPECT_EQ(s201->as<org::ImmSubtree>()->level, 2);
            return ast.store->demoteSubtree(
                s201.id, org::ImmAstStore::SubtreeMove::ForceLevels, ctx);
        });

    writeGvHistory({v1, v2}, "v1_v2");

    auto r    = v2.getRootAdapter();
    auto s201 = r.at({0, 1});
    EXPECT_EQ(s201->getKind(), OrgSemKind::Subtree);
    EXPECT_EQ(s201->as<org::ImmSubtree>()->level, 3);
    auto s3010 = r.at({0, 1, 0});
    EXPECT_EQ(s3010->getKind(), OrgSemKind::Subtree);
    EXPECT_EQ(s3010->as<org::ImmSubtree>()->level, 4);
    auto levels = getDfsSubtreeLevels(r);
    EXPECT_EQ(levels, (Vec<int>{1, 2, 3, 3, 3, 4}));
}

TEST_F(ImmOrgApiEdit, RecursiveSubtreeDemote_All) {
    setTraceFile(getDebugFile("trace.txt"));
    org::ImmAstVersion v1 = getInitialVersion(getSubtreeDash());

    org::ImmAstVersion v2 = v1.context.getEditVersion(
        [&](org::ImmAstContext&     ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            auto root = ctx->adapt(v1.epoch.getRoot());
            auto s1   = root.at(0);
            return ast.store->demoteSubtree(
                s1.id, org::ImmAstStore::SubtreeMove::ForceLevels, ctx);
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

    org::ImmAstVersion v2 = v1.context.getEditVersion(
        [&](org::ImmAstContext&     ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            auto root = ctx->adapt(v1.epoch.getRoot());
            auto s1   = root.at({0, 0, 1});
            return ast.store->demoteSubtree(
                s1.id, org::ImmAstStore::SubtreeMove::ForceLevels, ctx);
        });


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

    org::ImmAstVersion v3 = v2.context.getEditVersion(
        [&](org::ImmAstContext&     ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            return ast.store->demoteSubtree(
                v2.getRootAdapter().at({0, 1}).id,
                org::ImmAstStore::SubtreeMove::ForceLevels,
                ctx);
        });

    writeTreeRepr(v3.getRootAdapter(), "repr_v3.txt");

    org::ImmAstVersion v4 = v3.context.getEditVersion(
        [&](org::ImmAstContext&     ast,
            org::ImmAstEditContext& ctx) -> org::ImmAstReplaceGroup {
            return ast.store->demoteSubtree(
                v3.getRootAdapter().at({0, 1}).id,
                org::ImmAstStore::SubtreeMove::ForceLevels,
                ctx);
        });

    writeTreeRepr(v4.getRootAdapter(), "repr_v4.txt");

    writeGvHistory({v1, v2, v3, v4}, "v1_v2_v3_v4");
}

TEST(ImmMapApi, AddNode) {
    auto n1 = parseNode("* subtree");

    org::ImmAstContext        store;
    org::graph::MapGraphState s1{};
    org::graph::MapOpsConfig  conf;
    conf.setTraceFile("/tmp/ImmMapApi_AddNode.txt");
    EXPECT_EQ(s1.graph.nodeCount(), 0);
    auto [store2, root] = store.addRoot(n1);
    auto s2 = org::graph::addNode(s1, org::ImmAdapter{root, &store}, conf);
    EXPECT_EQ(s2.graph.nodeCount(), 1);

    writeFile("/tmp/MapS2.json", to_json_eval(s2).dump(2));

    Graphviz gvc;
    auto     gv = s2.graph.toGraphviz(store2);
    gvc.renderToFile("/tmp/MapS2.png", gv);
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

    org::ImmAstContext       store;
    org::graph::MapOpsConfig conf;
    conf.setTraceFile("/tmp/AddNodeWithLinks_log.txt");
    auto [store2, root_node] = store.addRoot(n1);
    org::ImmAdapter root{root_node, &store};

    ColStream os;
    store.format(os);
    writeFile(
        "/tmp/AddNodeWithLinks_treerepr.txt",
        fmt("tree:\n{}\nbuffer:\n{}",
            root.treeRepr().toString(false),
            os.getBuffer().toString(false)));

    org::graph::MapGraphState s1{};
    auto s2 = org::graph::addNode(s1, root.at(1), conf);
    auto s3 = org::graph::addNode(s2, root.at(3), conf);

    EXPECT_EQ(s1.graph.nodeCount(), 0);
    EXPECT_EQ(s1.graph.edgeCount(), 0);
    EXPECT_EQ(s1.unresolved.size(), 0);

    EXPECT_EQ(s2.graph.nodeCount(), 1);
    EXPECT_EQ(s2.graph.edgeCount(), 0);
    EXPECT_EQ(s2.unresolved.size(), 1);

    EXPECT_EQ(s3.graph.nodeCount(), 2);
    EXPECT_EQ(s3.graph.edgeCount(), 1);
    EXPECT_EQ(s3.unresolved.size(), 0);

    writeFile(
        "/tmp/AddNodeWithLinks.json",
        to_json_eval(Vec<org::graph::MapGraphState>{
                         s1,
                         s2,
                         s3,
                     })
            .dump(2));

    Graphviz gvc;
    auto     gv = s3.graph.toGraphviz(store2);
    gvc.renderToFile("/tmp/AddNodeWithLinks.png", gv);
}


TEST(ImmMapApi, SubtreeBacklinks) {
    Str text1{R"(
* Subtree1
  :properties:
  :id: subtree-1
  :end:

- [[id:subtree-2]] :: Forward link
)"_ss};

    Str text2{R"(
* Subtree2
  :properties:
  :id: subtree-2
  :end:

- [[id:subtree-1]] :: Backlink
)"_ss};

    auto n1 = parseNode(text1);
    auto n2 = parseNode(text2);

    org::ImmAstContext       store;
    org::graph::MapOpsConfig conf;
    conf.setTraceFile("/tmp/SubtreeBacklinks_log.txt");

    auto [store2, root_1] = store.addRoot(n1);
    auto [store3, root_2] = store2.addRoot(n2);

    org::ImmAdapter file1{root_1, &store};
    org::ImmAdapter file2{root_2, &store};

    ColStream os;
    store.format(os);
    writeFile(
        "/tmp/SubtreeBacklinks_treerepr.txt",
        fmt("tree1:\n{}\ntree1:\n{}\nbuffer:\n{}",
            file1.treeRepr().toString(false),
            file2.treeRepr().toString(false),
            os.getBuffer().toString(false)));

    org::graph::MapGraphState s1{};
    auto s2 = org::graph::addNode(s1, file1.at(1), conf);
    auto s3 = org::graph::addNode(s2, file2.at(1), conf);

    EXPECT_EQ(s1.graph.nodeCount(), 0);
    EXPECT_EQ(s1.graph.edgeCount(), 0);
    EXPECT_EQ(s1.unresolved.size(), 0);

    EXPECT_EQ(s2.graph.nodeCount(), 1);
    EXPECT_EQ(s2.graph.edgeCount(), 0);
    EXPECT_EQ(s2.unresolved.size(), 1);

    EXPECT_EQ(s3.graph.nodeCount(), 2);
    EXPECT_EQ(s3.graph.edgeCount(), 2);
    EXPECT_EQ(s3.unresolved.size(), 0);

    writeFile(
        "/tmp/SubtreeBacklinks.json",
        to_json_eval(Vec<org::graph::MapGraphState>{
                         s1,
                         s2,
                         s3,
                     })
            .dump(2));

    Graphviz gvc;
    auto     gv = s3.graph.toGraphviz(store3);
    gvc.renderToFile("/tmp/SubtreeBacklinks.png", gv);
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

    org::ImmAstContext       store;
    org::graph::MapOpsConfig conf;
    auto [store2, root1] = store.addRoot(n);
    org::ImmAdapter           file{root1, &store};
    org::graph::MapGraphState s1{};

    ColStream os;
    store.format(os);
    writeFile(
        "/tmp/SubtreeFullMap_repr.txt",
        fmt("tree:\n{}\nbuffer:\n{}",
            file.treeRepr().toString(false),
            os.getBuffer().toString(false)));


    EXPECT_EQ(file.at(1)->getKind(), osk::Subtree);
    auto node_s10  = file.at({1, 0});
    auto node_p110 = file.at({1, 1, 0});
    auto node_s12  = file.at({1, 2});
    EXPECT_EQ(node_s10->getKind(), osk::Subtree);
    EXPECT_EQ(
        node_s10.as<org::ImmSubtree>()->treeId->value(),
        "c468e9c7-7422-4b17-8ccb-53575f186fe0");

    EXPECT_EQ(node_s12->getKind(), osk::Subtree);
    EXPECT_EQ(
        node_s12.as<org::ImmSubtree>()->treeId->value(),
        "6d6d6689-d9da-418d-9f91-1c8c4428e5af");


    conf.setTraceFile("/tmp/SubtreeFullMap_log.txt");

    auto s2 = org::graph::addNodeRec(s1, file, conf);

    EXPECT_TRUE(s2.graph.hasEdge(node_p110, node_s12));
    EXPECT_TRUE(s2.graph.hasEdge(node_p110, node_s10));

    Graphviz gvc;
    auto     gv = s2.graph.toGraphviz(store2);
    gv.setRankDirection(Graphviz::Graph::RankDirection::LR);
    gvc.writeFile("/tmp/SubtreeFullMap.dot", gv);
    gvc.renderToFile("/tmp/SubtreeFullMap.png", gv);
}

struct TestGraph {
    org::graph::MapGraph     g;
    Vec<org::graph::MapNode> nodes;
};

TestGraph create_test_graph() {
    org::graph::MapGraph g{};

    auto n0 = org::ImmId::FromValue(0);
    auto n1 = org::ImmId::FromValue(1);
    auto n2 = org::ImmId::FromValue(2);

    g.adjList = {
        {n0, {n1}},
        {n1, {n2}},
        {n2, {n0}},
    };

    g.nodeProps = g.nodeProps.set(n0, org::graph::MapNodeProp{});
    g.nodeProps = g.nodeProps.set(n1, org::graph::MapNodeProp{});
    g.nodeProps = g.nodeProps.set(n2, org::graph::MapNodeProp{});

    g.edgeProps = g.edgeProps.set({n0, n1}, org::graph::MapEdgeProp{});
    g.edgeProps = g.edgeProps.set({n1, n2}, org::graph::MapEdgeProp{});
    g.edgeProps = g.edgeProps.set({n2, n0}, org::graph::MapEdgeProp{});

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
    EXPECT_EQ(vertices[0], g.nodes.at(0));
    EXPECT_EQ(vertices[1], g.nodes.at(1));
    EXPECT_EQ(vertices[2], g.nodes.at(2));
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

    org::ImmAstContext       store;
    org::graph::MapOpsConfig conf;
    auto [store2, root1] = store.addRoot(n);
    org::ImmAdapter           file{root1, &store};
    org::graph::MapGraphState s1{};
    auto                      s2 = org::graph::addNodeRec(s1, file, conf);

    std::stringstream os;

    auto dp = org::graph::toGraphvizDynamicProperties(s2.graph);

    write_graphviz_dp(os, s2.graph, dp);

    writeFile("/tmp/BoostPropertyWriter.dot", os.str());
}
