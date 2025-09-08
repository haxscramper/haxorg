#include <QTest>
#include <haxorg/sem/SemBaseApi.hpp>
#include <src/model/HistoryManager.hpp>
#include <src/utils/common.hpp>
#include <src/utils/test_utils.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "test.history"

using namespace test;

class HistoryManagerTest : public QObject {
    Q_OBJECT


  private slots:
    void testFromRegularText() {
        HistoryManager manager{
            org::imm::ImmAstContext::init_start_context()};
        manager.addDocument("*bold*");
        manager.addDocument("/italic/");
    }

    void testGetSimpleDifference() {
        HistoryManager manager{
            org::imm::ImmAstContext::init_start_context()};
        manager.addDocument("word");
        manager.addDocument("word second");
    }

    void testTreeEdits() {
        auto     __scope = trackTestExecution(this);
        ScopeV12 scope;
        scope.manager.addDocument(R"(
* layer 1
** item 1
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 12, "y": 90}
    :prop_args:haxorg_diagram_node: :some-value t
    :end:
)");
        scope.manager.addDocument(R"(
* layer 1
** item 1
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 142, "y": 900}
    :prop_args:haxorg_diagram_node: :some-value t
    :end:
)");
        auto treeV1 = FromDocument(scope.tree_context, scope.getRootV1());

        HSLOG_INFO(
            _cat,
            "treeV1 adapter repr\n",
            scope.getRootV1().treeReprString());

        HSLOG_INFO(
            _cat,
            "treeV2 adapter repr\n",
            scope.getRootV2().treeReprString());

        HSLOG_INFO(
            _cat, "treeV1 before edit\n", treeV1.format().toString(false));
    }

    void testDepletedEdits() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            R"(
* layer
)",
            R"(
* layer
)"};
        QCOMPARE_EQ(scope.edits.size(), 0);
        log_collection(
            "test", hstd::log::severity_level::trace, scope.edits)
            .end();
    }

    void testLeafChange() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            R"(
* layer
** item 1
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 12, "y": 90}
    :prop_args:haxorg_diagram_node: :some-value t
    :end:
)",
            R"(
* layer
** item 1
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 142, "y": 900}
    :prop_args:haxorg_diagram_node: :some-value t
    :end:
)"};
        QCOMPARE_EQ(scope.edits.size(), 2);
        log_collection(
            "test", hstd::log::severity_level::trace, scope.edits)
            .end();
    }
};

HAXORG_QT_TEST_MAIN(HistoryManagerTest)
#include "tHistoryManagerTest.moc"
