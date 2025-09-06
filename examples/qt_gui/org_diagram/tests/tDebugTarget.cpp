#include "src/model/QtOrgAstModel.hpp"
#include <QTest>
#include <src/model/HistoryManager.hpp>
#include <src/utils/common.hpp>
#include <src/utils/test_utils.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "test.history"

using namespace test;

class DebugTarget : public QObject {
  public:
    void run_thing() {
        auto     __scope = trackTestExecution(this);
        ScopeV12 scope;
        scope.manager.addDocument("word");
        scope.manager.addDocument("word second");
        auto treeV1 = DiagramTreeNode::FromDocument(
            scope.tree_context, scope.getRootV1());

        applyEdits(
            treeV1, scope.manager.getDifference(0, 1), scope.context);

        auto treeV2 = DiagramTreeNode::FromDocument(
            scope.tree_context, scope.getRootV2());

        QCOMPARE_EQ2(treeV1->id.uniq(), treeV2->id.uniq());
    }
};

int main() {
    DebugTarget dt;
    dt.run_thing();
}
