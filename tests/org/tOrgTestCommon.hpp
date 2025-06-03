#include "../common.hpp"

#include <haxorg/parse/OrgParser.hpp>
#include <haxorg/parse/OrgTokenizer.hpp>


#include <haxorg/lexbase/AstSpec.hpp>
#include <hstd/ext/astdiff.hpp>
#include <haxorg/test/NodeTest.hpp>

#include <hstd/stdlib/diffs.hpp>

#include <hstd/stdlib/Filesystem.hpp>
#include <haxorg/sem/SemOrgSerde.hpp>
#if ORG_DEPS_USE_PROTOBUF
#    include <google/protobuf/util/json_util.h>
#endif
#include <haxorg/exporters/ExporterJson.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <haxorg/sem/ImmOrgEdit.hpp>
#include <haxorg/sem/ImmOrgGraph.hpp>
#include <haxorg/sem/ImmOrgGraphBoost.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/graphviz.hpp>
#include <haxorg/sem/perfetto_org.hpp>
#include <haxorg/exporters/exportertree.hpp>

using namespace hstd;
using namespace org;

GTEST_ADL_PRINT_TYPE(imm::ImmAdapter);
GTEST_ADL_PRINT_TYPE(imm::ImmUniqId);
GTEST_ADL_PRINT_TYPE(org::graph::MapNode);
GTEST_ADL_PRINT_TYPE(org::graph::MapEdge);
GTEST_ADL_PRINT_TYPE(Vec<Str>);
GTEST_ADL_PRINT_TYPE(Vec<Vec<Str>>);
GTEST_ADL_PRINT_TYPE(UserTimeBreakdown);

#pragma clang diagnostic ignored "-Wreorder-init-list"
#include <haxorg/test/org_parse_aux.hpp>
#include <gtest/gtest.h>


void writeTreeRepr(
    imm::ImmAdapter               n,
    Str const                     suffix,
    imm::ImmAdapter::TreeReprConf conf = imm::ImmAdapter::TreeReprConf{
        .withAuxFields = true,
    });

void writeTreeRepr(sem::SemId<sem::Org> node, CR<Str> full);


GTEST_ADL_PRINT_TYPE(OrgSemKind);
GTEST_ADL_PRINT_TYPE(imm::ImmId);


template <typename T>
struct TestValueFormat {
    static std::string format(T const& t) { return fmt1(t); }
};


template <typename T1, typename T2>
struct TestValueCompareFormat {
    static std::string format(
        T1 const&   t1,
        T2 const&   t2,
        char const* lhs,
        char const* rhs) {
        return fmt(
            "Expected equality of these values:\n  {}\n    {}\n  "
            "{}\n "
            "   {}",
            lhs,
            t1,
            rhs,
            t2);
    }
};

template <typename T1, typename T2>
std::string format_test_fail(
    T1 const&   t1,
    T2 const&   t2,
    char const* lhs,
    char const* rhs) {
    return TestValueCompareFormat<T1, T2>::format(t1, t2, lhs, rhs);
}

// use when shitty ADL lookup solution that 1000IQ shitbags from google
// cooked fails to work. Not like there are any other ways to make test
// suite print values in some sane capacity, greasy cumshots are splattered
// over the docs are not worth shit, they don't even match whatever is in
// the `gtest.h` header. `AbslStringify`, right. Fuck you.
#define EXPECT_EQ2(lhs, rhs)                                              \
    EXPECT_EQ(lhs, rhs) << format_test_fail(lhs, rhs, #lhs, #rhs)


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
void equality_compare_impl(
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

#define EQUALITY_COMPARE_TRIVIAL(__type)                                  \
    template <>                                                           \
    struct reporting_comparator<__type> {                                 \
        static void compare(                                              \
            CR<__type>                  lhs,                              \
            CR<__type>                  rhs,                              \
            Vec<compare_report>&        out,                              \
            Vec<compare_context> const& context) {                        \
            equality_compare_impl<__type>(lhs, rhs, out, context);        \
        }                                                                 \
    };

template <typename T>
struct reporting_comparator {};

EQUALITY_COMPARE_TRIVIAL(int);
EQUALITY_COMPARE_TRIVIAL(bool);
EQUALITY_COMPARE_TRIVIAL(hstd::Str);
EQUALITY_COMPARE_TRIVIAL(std::string);
EQUALITY_COMPARE_TRIVIAL(float);
EQUALITY_COMPARE_TRIVIAL(u64);
EQUALITY_COMPARE_TRIVIAL(cctz::civil_second);
EQUALITY_COMPARE_TRIVIAL(cctz::time_zone);


template <typename K, typename V, typename Container>
struct reporting_comparator_key_value {
    static void compare(
        CR<Container>               lhs,
        CR<Container>               rhs,
        Vec<compare_report>&        out,
        Vec<compare_context> const& context) {
        hstd::UnorderedSet<K> lhs_keys;
        hstd::UnorderedSet<K> rhs_keys;
        for (auto const& [key, value] : lhs) { lhs_keys.incl(key); }
        for (auto const& [key, value] : rhs) { rhs_keys.incl(key); }
        for (auto const& shared_key : (lhs_keys & rhs_keys)) {
            reporting_comparator<V>::compare(
                lhs.at(shared_key),
                rhs.at(shared_key),
                out,
                context
                    + Vec<compare_context>{{
                        .field = maybe_format(shared_key),
                        .type  = "UnorderedMap",
                    }});
        }

        for (auto const& lhs_only : lhs_keys - rhs_keys) {
            out.push_back({
                .context = context,
                .message = fmt(
                    "no key of type {} '{}' in lhs on {}",
                    value_metadata<K>::typeName(),
                    maybe_format(lhs_only),
                    __LINE__),
            });
        }

        for (auto const& rhs_only : rhs_keys - lhs_keys) {
            out.push_back({
                .context = context,
                .message = fmt(
                    "no key of type {} '{}' in rhs on {}",
                    value_metadata<K>::typeName(),
                    maybe_format(rhs_only),
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

template <IsEnum E>
struct reporting_comparator<E> {
    static void compare(
        CR<E>                       lhs,
        CR<E>                       rhs,
        Vec<compare_report>&        out,
        Vec<compare_context> const& context) {
        equality_compare_impl<E>(lhs, rhs, out, context);
    }
};


template <typename T>
struct reporting_comparator<immer::box<T>> {
    static void compare(
        CR<immer::box<T>>           lhs,
        CR<immer::box<T>>           rhs,
        Vec<compare_report>&        out,
        Vec<compare_context> const& context) {
        reporting_comparator<T>::compare(
            lhs.get(), rhs.get(), out, context);
    }
};

template <typename K, typename V>
struct reporting_comparator<UnorderedMap<K, V>>
    : reporting_comparator_key_value<K, V, UnorderedMap<K, V>> {};

template <typename K, typename V>
struct reporting_comparator<std::unordered_map<K, V>>
    : reporting_comparator_key_value<K, V, std::unordered_map<K, V>> {};

template <typename K, typename V>
struct reporting_comparator<immer::map<K, V>>
    : reporting_comparator_key_value<K, V, immer::map<K, V>> {};

template <typename K, typename V>
struct reporting_comparator<hstd::ext::ImmMap<K, V>>
    : reporting_comparator_key_value<K, V, hstd::ext::ImmMap<K, V>> {};

template <typename T, typename Container>
struct reporting_comparator_indexed_sequence {
    static void compare(
        CR<Container>               lhs,
        CR<Container>               rhs,
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

template <typename T>
struct reporting_comparator<hstd::Vec<T>>
    : reporting_comparator_indexed_sequence<T, hstd::Vec<T>> {};

template <typename T>
struct reporting_comparator<std::vector<T>>
    : reporting_comparator_indexed_sequence<T, std::vector<T>> {};

template <typename T>
struct reporting_comparator<immer::flex_vector<T>>
    : reporting_comparator_indexed_sequence<T, immer::flex_vector<T>> {};

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
                .message = fmt(
                    "variant index differ {} != {} on {} for {}",
                    lhs.index(),
                    rhs.index(),
                    __LINE__,
                    value_metadata<V>::typeName()),
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


template <>
struct reporting_comparator<org::imm::ImmAstStore> {
    static void compare(
        CR<org::imm::ImmAstStore>   lhs,
        CR<org::imm::ImmAstStore>   rhs,
        Vec<compare_report>&        out,
        Vec<compare_context> const& context) {
#define _kind(__Kind)                                                     \
    reporting_comparator<                                                 \
        org::imm::ImmAstKindStore<org::imm::Imm##__Kind>>::               \
        compare(lhs.store##__Kind, rhs.store##__Kind, out, context);
        EACH_SEM_ORG_KIND(_kind)
#undef _kind
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
compare_report cmp_field_value(
    CR<Obj> lhs,
    CR<Obj> rhs,
    Field Obj::*fieldPtr) {
    return reporting_comparator<decltype(lhs.*fieldPtr)>::compare(
        lhs.*fieldPtr, rhs.*fieldPtr);
};

void show_compare_reports(Vec<compare_report> const& out);


sem::SemId<sem::Org> testParseString(
    std::string const&         text,
    std::optional<std::string> debug = std::nullopt);

template <typename T>
std::string dbgString(
    sem::SemId<T> const& id,
    char const*          function = __builtin_FUNCTION(),
    int                  line     = __builtin_LINE(),
    char const*          file     = __builtin_FILE()) {
    return fmt(
        "{}:{}\n{}",
        function,
        line,
        org::exportToTreeString(
            id.asOrg(),
            org::OrgTreeExportOpts{
                .withColor = false,
            }));
}

template <typename T>
std::string dbgString(
    Vec<sem::SemId<T>> const& id,
    char const*               function = __builtin_FUNCTION(),
    int                       line     = __builtin_LINE(),
    char const*               file     = __builtin_FILE()) {
    std::string result;
    for (auto const& i : enumerator(id)) {
        if (i.is_first()) { result += "\n"; }
        result += dbgString(i.value(), function, line, file);
    }
    return result;
}

template <typename T>
sem::SemId<T> parseOne(
    std::string const&         text,
    std::optional<std::string> debug = std::nullopt) {
    auto node = testParseString(text, debug);
    if (T::staticKind == node->getKind()) {
        return node.as<T>();
    } else {
        auto one = org::asOneNode(node);
        while (T::staticKind != one->getKind()) {
            LOGIC_ASSERTION_CHECK(
                one->subnodes.has(0),
                "Parsed node does not have item at index 0: {}",
                org::exportToTreeString(
                    node, org::OrgTreeExportOpts{.withColor = false}));
            one = one.at(0);
        }
        return one.as<T>();
    }
}

template <typename T>
struct ImmTestResult {
    imm::ImmAstContext::Ptr context;
    imm::ImmAstVersion      version;
    imm::ImmAdapterT<T>     node;
};

template <
    sem::IsOrg Sem,
    typename Imm = imm::sem_to_imm_map<Sem>::imm_type>
ImmTestResult<Imm> immConv(
    imm::ImmAstContext::Ptr ctx,
    sem::SemId<Sem> const&  id) {
    ImmTestResult<Imm> res;
    res.context = ctx;
    res.version = res.context->init(id.asOrg());
    res.node    = res.version.getRootAdapter().template as<Imm>();
    return res;
}

template <
    sem::IsOrg Sem,
    typename Imm = imm::sem_to_imm_map<Sem>::imm_type>
ImmTestResult<Imm> immConv(sem::SemId<Sem> const& id) {
    return immConv(imm::ImmAstContext::init_start_context(), id);
}

struct ImmOrgApiTestBase : public ::testing::Test {
    imm::ImmAstContext::Ptr start;

    ImmOrgApiTestBase()
        : start{imm::ImmAstContext::init_start_context()} {}

    void setTraceFile(std::string const& path) {
        start->debug->setTraceFile(path);
    }

    imm::ImmAstVersion getInitialVersion(
        Str const&                 text,
        std::optional<std::string> debug = std::nullopt) {
        return start->init(testParseString(text, debug));
    }

    void writeGvHistory(
        const Vec<imm::ImmAstVersion>& history,
        std::string                    suffix,
        imm::ImmAstGraphvizConf const& conf = imm::ImmAstGraphvizConf{
            .withAuxNodes    = true,
            .withEditHistory = true,
        }) {
        hstd::ext::Graphviz gvc;
        auto                gv = imm::toGraphviz(history, conf);
        gvc.writeFile(getDebugFile(suffix + ".dot"), gv);
        gvc.renderToFile(getDebugFile(suffix + ".png"), gv);
    }
};
