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

std::shared_ptr<hstd::log::log_graph_tracker> get_tracker();
hstd::ext::Graphviz::Graph                    get_tracker_graph();

#define TRACKED_SLOT(...) HSLOG_TRACKED_SLOT(get_tracker(), __VA_ARGS__)
#define TRACKED_EMIT(...) HSLOG_TRACKED_EMIT(get_tracker(), __VA_ARGS__)
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
        node.getProperty(kind),
        hstd::fmt("Property '{}' not found", kind));

    BOOST_OUTCOME_TRY_SUB_VARIANT(json_data, property, CustomSubtreeJson);
    return hstd::from_json_eval<T>(json_data.value.getRef());
}


outcome::result<org::sem::AttrGroup const*, std::string> getFlagProperty(
    org::imm::ImmAdapterT<org::imm::ImmSubtree> const& node,
    std::string const&                                 kind);

bool hasProperty(
    org::imm::ImmAdapterT<org::imm::ImmSubtree> const& node,
    std::string const&                                 kind);
