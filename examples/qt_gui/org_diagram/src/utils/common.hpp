#pragma once

#include <hstd/ext/logger.hpp>
#include "log_graph_tracker.hpp"
#include <QDebug>
#include <QObject>
#include <QTest>
#include <QObject>
#include <QMetaObject>
#include <QDebug>

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
