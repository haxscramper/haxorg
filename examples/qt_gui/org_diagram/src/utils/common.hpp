#pragma once

#include <hstd/ext/logger.hpp>
#include "log_graph_tracker.hpp"
#include <QDebug>
#include <QObject>
#include <QTest>
#include <QObject>
#include <QMetaObject>
#include <QDebug>
#include <haxorg/sem/ImmOrg.hpp>
#include <boost/outcome.hpp>
#include <hstd/stdlib/Ptrs.hpp>

namespace hstd {

template <class T, class D, class U>
    requires(requires(std::unique_ptr<U, D>::pointer p) {
                dynamic_cast<std::unique_ptr<T, D>::pointer>(p);
            })
constexpr auto dynamic_pointer_cast(std::unique_ptr<U, D>&& r) noexcept
    -> std::unique_ptr<T, D> {
    static_assert(
        !std::is_array_v<T> && !std::is_array_v<U>,
        "don't work with array of polymorphic objects");
    if (auto p = dynamic_cast<std::unique_ptr<T, D>::pointer>(r.get())) {
        r.release();
        return std::unique_ptr<T, D>(p, std::forward<D>(r.get_deleter()));
    } else if constexpr (
        !std::is_pointer_v<D> && std::is_default_constructible_v<D>) {
        return {};
    } else if constexpr (std::is_copy_constructible_v<D>) {
        return std::unique_ptr<T, D>(nullptr, r.get_deleter());
    } else {
        static_assert(false, "unable to create an empty unique_ptr");
    }
}


template <typename T>
struct WPtr_safe : std::weak_ptr<T> {
    std::shared_ptr<T> lock() const { return hstd::safe_wptr_lock(this); }
};

template <typename Derived, typename Base>
struct SharedPtrApiDerived {
    // Re-introduce shared() with correct return type
    template <typename... Args>
    static std::shared_ptr<Derived> shared(Args&&... args) {
        return std::make_shared<Derived>(std::forward<Args>(args)...);
    }

    // Re-introduce clone_this() with correct return type
    std::shared_ptr<Derived> clone_this() {
        return std::make_shared<Derived>(
            static_cast<const Derived&>(*this));
    }

    // Type aliases for the derived class
    using Ptr  = std::shared_ptr<Derived>;
    using WPtr = WPtr_safe<Derived>;

    // Re-introduce shared_from_this with correct return type
    std::shared_ptr<Derived> mshared_from_this() const {
        auto base_ptr = static_cast<const Base*>(this)
                            ->mshared_from_this();
        return std::static_pointer_cast<Derived>(base_ptr);
    }

    WPtr_safe<Derived> weak_from_this() const {
        return WPtr{mweak_from_this()};
    }

    // Re-introduce weak_from_this with correct return type
    WPtr_safe<Derived> mweak_from_this() const {
        auto base_weak = static_cast<const Base*>(this)->mweak_from_this();
        return std::static_pointer_cast<Derived>(base_weak.lock());
    }

    std::shared_ptr<Base> dyn_cast_base() const {
        return dyn_cast<Base>();
    }

    template <typename T>
    std::shared_ptr<T> dyn_cast() const {
        return std::dynamic_pointer_cast<T>(
            static_cast<Derived const*>(this)->mshared_from_this());
    }

    template <typename T>
    bool isinstance() const {
        return std::dynamic_pointer_cast<T>(
            static_cast<Derived const*>(this));
    }
};

#define HSTD_SHARED_PTR_API_USING_DERIVED(__Derived, __Base)              \
    using ::hstd::SharedPtrApiDerived<__Derived, __Base>::WPtr;

} // namespace hstd


template <typename T>
hstd::log::log_record log_collection(
    char const*               cat,
    hstd::log::severity_level severity,
    std::vector<T> const&     items,
    int                       line     = __builtin_LINE(),
    char const*               function = __builtin_FUNCTION(),
    char const*               file     = __builtin_FILE()) {
    auto res = ::hstd::log::log_record{}
                   .file(file)
                   .line(line)
                   .category(cat)
                   .function(function)
                   .severity(severity);
    res.fmt_message(
        "std::vector<{}> with {} items:",
        hstd::value_metadata<T>::typeName(),
        items.size());
    for (int i = 0; i < items.size(); ++i) {
        res.fmt_message("\n[{}]: {}", i, hstd::fmt1(items.at(i)));
    }
    return res;
}

std::shared_ptr<hstd::log::log_graph_tracker> get_tracker();
hstd::ext::Graphviz::Graph                    get_tracker_graph();

#define TRACKED_SLOT(...) HSLOG_TRACKED_SLOT(get_tracker(), __VA_ARGS__)
#define TRACKED_EMIT(...) HSLOG_TRACKED_EMIT(get_tracker(), __VA_ARGS__)
#define TRACKED_SCOPE(...) HSLOG_TRACKED_SCOPE(get_tracker(), __VA_ARGS__)
#define TRACKED_FUNCTION(...)                                             \
    HSLOG_TRACKED_FUNCTION(get_tracker(), __VA_ARGS__)
#define TRACKED_CONNECT(...)                                              \
    HSLOG_TRACKED_CONNECT(get_tracker(), __VA_ARGS__)
#define TRACKED_OBJECT(...)                                               \
    HSLOG_TRACKED_OBJECT(get_tracker(), __VA_ARGS__)

hstd::fs::path getDebugFile(
    QObject*         testClass,
    const hstd::Str& suffix = "");

template <typename T>
std::string qdebug_to_str(T const& index) {
    QString output;
    QDebug(&output).noquote().nospace() << index;
    return output.toStdString();
}

namespace hstd {
hstd::Vec<ColText> split(ColText const& text, Str const& delimiter);
} // namespace hstd

hstd::finally_std trackTestExecution(
    QObject*         testClas,
    hstd::Str const& suffix   = "",
    int              line     = __builtin_LINE(),
    char const*      function = __builtin_FUNCTION(),
    char const*      file     = __builtin_FILE());

void customMessageHandler(
    QtMsgType                 type,
    const QMessageLogContext& context,
    const QString&            msg_in);

hstd::ColText printModelTree(
    const QAbstractItemModel* model,
    const QModelIndex&        parent = QModelIndex{},
    hstd::Opt<hstd::Func<hstd::ColText(QModelIndex const&)>> toString = std::
        nullopt,
    bool           ignoreExceptions = false,
    hstd::Opt<int> maxDepth         = std::nullopt);

#define HAXORG_QT_TEST_MAIN(Test_Class)                                   \
    int main(int argc, char* argv[]) {                                    \
        QT_PREPEND_NAMESPACE(                                             \
            QTest::Internal::callInitMain)<Test_Class>();                 \
        qInstallMessageHandler(customMessageHandler);                     \
        q_register_metatypes();                                           \
        QTEST_QAPP_SETUP(QApplication);                                   \
        Test_Class tc;                                                    \
        hstd::log::push_sink(hstd::log::init_file_sink(                   \
            getDebugFile(&tc, "main.log").native()));                     \
        TESTLIB_SELFCOVERAGE_START(#Test_Class)                           \
        QTEST_SET_MAIN_SOURCE_PATH;                                       \
        return QTest ::qExec(&tc, argc, argv);                            \
    }


template <QTest::ComparisonOperation op, typename T1, typename T2>
bool haxorg_qCompareOp(
    T1&&        qt_lhs_arg,
    T2&&        qt_rhs_arg,
    const char* lhsExpr,
    const char* rhsExpr,
    const char* file,
    int         line) {
    using Comparator = QTest::Internal::Compare<op>;
    bool success     = Comparator::compare(
        std::forward<T1>(qt_lhs_arg), std::forward<T2>(qt_lhs_arg));
    return QTest::reportResult(
        success,
        [&qt_lhs_arg] {
            return qstrdup(::hstd::fmt1(qt_lhs_arg).c_str());
        },
        [&qt_rhs_arg] {
            return qstrdup(::hstd::fmt1(qt_rhs_arg).c_str());
        },
        lhsExpr,
        rhsExpr,
        op,
        file,
        line);
}

#define QCOMPARE_OP2_IMPL(lhs, rhs, op, opId)                             \
    do {                                                                  \
        if (!haxorg_qCompareOp<QTest::ComparisonOperation::opId>(         \
                lhs, rhs, #lhs, #rhs, __FILE__, __LINE__)) {              \
            QTEST_FAIL_ACTION;                                            \
        }                                                                 \
    } while (false)

#define QCOMPARE_EQ2(computed, baseline)                                  \
    QCOMPARE_OP2_IMPL(computed, baseline, ==, Equal)
#define QCOMPARE_NE2(computed, baseline)                                  \
    QCOMPARE_OP2_IMPL(computed, baseline, !=, NotEqual)
#define QCOMPARE_LT2(computed, baseline)                                  \
    QCOMPARE_OP2_IMPL(computed, baseline, <, LessThan)
#define QCOMPARE_LE2(computed, baseline)                                  \
    QCOMPARE_OP2_IMPL(computed, baseline, <=, LessThanOrEqual)
#define QCOMPARE_GT2(computed, baseline)                                  \
    QCOMPARE_OP2_IMPL(computed, baseline, >, GreaterThan)
#define QCOMPARE_GE2(computed, baseline)                                  \
    QCOMPARE_OP_IMPL(computed, baseline, >=, GreaterThanOrEqual)

namespace outcome = BOOST_OUTCOME_V2_NAMESPACE;

/// \brief Macro to handle std::optional - converts to outcome::result
#define BOOST_OUTCOME_TRY_OPTIONAL(var, optional_expr, error_msg)         \
    auto BOOST_OUTCOME_UNIQUE_NAME = (optional_expr);                     \
    if (!BOOST_OUTCOME_UNIQUE_NAME.has_value()) {                         \
        return ::outcome::failure(error_msg);                             \
    }                                                                     \
    auto const& var = std::move(BOOST_OUTCOME_UNIQUE_NAME.value());

/// \brief Macro to handle is<X>() + get<X>() pattern
#define BOOST_OUTCOME_TRY_VALIDATE_GET(                                   \
    var, obj, check_method, get_method, error_msg)                        \
    if (!(obj).check_method()) { return ::outcome::failure(error_msg); }  \
    auto const& var = (obj).get_method();

/// \brief Alternative macro if get_method() doesn't return optional
#define BOOST_OUTCOME_TRY_VALIDATE_GET_DIRECT(                            \
    var, obj, check_method, get_method, error_msg)                        \
    if (!(obj).check_method()) { return ::outcome::failure(error_msg); }  \
    auto const& var = (obj).get_method();


#define BOOST_OUTCOME_TRY_SUB_VARIANT(var, obj, variant_name)             \
    BOOST_OUTCOME_TRY_VALIDATE_GET(                                       \
        var,                                                              \
        obj,                                                              \
        is##variant_name,                                                 \
        get##variant_name,                                                \
        hstd::fmt(                                                        \
            "Expected sub variant '{}' but got '{}'",                     \
            #variant_name,                                                \
            obj.sub_variant_get_kind()))

template <typename T>
outcome::result<T, std::string> getStructuredProperty(
    org::imm::ImmAdapterT<org::imm::ImmSubtree> const& node,
    std::string const&                                 kind) {
    BOOST_OUTCOME_TRY_OPTIONAL(
        property,
        node.getProperty("customsubtreejson", kind),
        hstd::fmt("Property :prop_json:{}: not found", kind));

    BOOST_OUTCOME_TRY_SUB_VARIANT(json_data, property, CustomSubtreeJson);
    return hstd::from_json_eval<T>(json_data.value.getRef());
}

namespace hstd {

struct described_predicate_error {
    int         line;
    char const* function;
    char const* file;
    std::string text;

    ::hstd::logic_assertion_error as_exception(char const* expr) {
        return ::hstd::logic_assertion_error::init(
            ::hstd::fmt("{}: {}", expr, text), line, function, file);
    }

    static described_predicate_error init(
        std::string const& message,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE()) {
        return described_predicate_error{line, function, file, message};
    }
};

using described_predicate_result = outcome::
    result<bool, described_predicate_error>;

#define LOGIC_ASSERTION_CHECK_DESCRIBED(expr)                             \
    if (::hstd::described_predicate_result tmp = expr; !(tmp)) {          \
        throw tmp.error().as_exception(#expr);                            \
    }

} // namespace hstd

outcome::result<org::sem::AttrGroup const*, std::string> getFlagProperty(
    org::imm::ImmAdapterT<org::imm::ImmSubtree> const& node,
    std::string const&                                 kind);

bool hasProperty(
    org::imm::ImmAdapterT<org::imm::ImmSubtree> const& node,
    std::string const&                                 kind);

bool hasJsonProperty(
    org::imm::ImmAdapterT<org::imm::ImmSubtree> const& node,
    std::string const&                                 kind);

bool hasArgsProperty(
    org::imm::ImmAdapterT<org::imm::ImmSubtree> const& node,
    std::string const&                                 kind);

void q_register_metatypes();
