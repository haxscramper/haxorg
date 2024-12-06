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
#include <haxorg/exporters/exportertree.hpp>

Str getDebugFile(Str const& suffix);

void writeTreeRepr(
    org::ImmAdapter               n,
    Str const                     suffix,
    org::ImmAdapter::TreeReprConf conf = org::ImmAdapter::TreeReprConf{
        .withAuxFields = true,
    });

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
        inline std::string PrintToString(__type const& value) {           \
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
GTEST_ADL_PRINT_TYPE(Str);
GTEST_ADL_PRINT_TYPE(Vec<Vec<Str>>);
GTEST_ADL_PRINT_TYPE(UserTimeBreakdown);


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

void show_compare_reports(Vec<compare_report> const& out);


sem::SemId<sem::Org> testParseString(
    std::string const&         text,
    std::optional<std::string> debug = std::nullopt);

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
    auto node = testParseString(text, debug);
    if (T::staticKind == node->getKind()) {
        return node.as<T>();
    } else {
        auto one = sem::asOneNode(node);
        while (T::staticKind != one->getKind()) { one = one.at(0); }
        return one.as<T>();
    }
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

struct ImmOrgApiTestBase : public ::testing::Test {
    org::ImmAstContext start;

    void setTraceFile(std::string const& path) {
        start.debug->setTraceFile(path);
    }

    org::ImmAstVersion getInitialVersion(Str const& text) {
        return start.init(testParseString(text));
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