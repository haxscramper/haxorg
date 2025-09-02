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
        scope.manager.addDocument("word");
        scope.manager.addDocument("word second");
        auto treeV1 = DiagramTreeNode::FromDocument(
            scope.tree_context, scope.getRootV1());
        auto treeV2 = DiagramTreeNode::FromDocument(
            scope.tree_context, scope.getRootV2());

        applyEdits(
            treeV1, scope.manager.getDifference(0, 1), scope.context);
    }
};

HAXORG_QT_TEST_MAIN(HistoryManagerTest)
#include "tHistoryManagerTest.moc"
