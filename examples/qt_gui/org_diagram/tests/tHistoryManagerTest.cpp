#include <QTest>
#include <haxorg/sem/SemBaseApi.hpp>
#include <src/model/HistoryManager.hpp>
#include <src/utils/common.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "test.history"


class HistoryManagerTest : public QObject {
    Q_OBJECT


  private slots:
    struct ScopeV12 {
        org::imm::ImmAstContext::Ptr context;
        HistoryManager               manager;
        ScopeV12()
            : manager{org::imm::ImmAstContext::init_start_context()} {}

        org::imm::ImmAdapter getRootV1() const {
            return manager.getRoot(0);
        }

        org::imm::ImmAdapter getRootV2() const {
            return manager.getRoot(1);
        }
    };

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
        auto treeV1 = DiagramTreeNode::FromDocument(scope.getRootV1());
        auto treeV2 = DiagramTreeNode::FromDocument(scope.getRootV2());

        treeV1->apply(scope.manager.getDifference(0, 1));
    }
};

HAXORG_QT_TEST_MAIN(HistoryManagerTest)
#include "tHistoryManagerTest.moc"
