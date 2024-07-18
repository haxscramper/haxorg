#include <test/org_parse_aux.hpp>
#include <gtest/gtest.h>

#include <parse/OrgParser.hpp>
#include <parse/OrgTokenizer.hpp>
#include <gtest/gtest.h>

#include <lexbase/AstSpec.hpp>
#include <lexbase/AstDiff.hpp>
#include <test/NodeTest.hpp>

#include <hstd/stdlib/diffs.hpp>

#include <hstd/stdlib/Filesystem.hpp>
#include <sem/SemOrgSerde.hpp>
#include <google/protobuf/util/json_util.h>
#include <exporters/ExporterJson.hpp>
#include <sem/SemBaseApi.hpp>

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
                .message = fmt("on {}", __LINE__),
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
    sem::OrgConverter converter{};
    sem::SemId node = converter.toDocument(OrgAdapter(&p.nodes, OrgId(0)));

    using osk = OrgSemKind;
    SemSet wipNotParseable{
        osk::Include,
        osk::DocumentGroup,
        osk::Empty,
        osk::Row,
        osk::Table,
        osk::Completion,
        osk::CmdGroup,
        osk::BlockQuote,
        osk::MarkQuote,
        osk::StmtList,
        osk::BlockAdmonition,
        osk::FileTarget,
        osk::ParseError,
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
