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
        auto             __scope = trackTestExecution(this);
        ScopeDiagramTree scope;
        auto             v1   = scope.getAdapter("* document level");
        auto             tree = FromDocument(
            scope.tree_context,
            v1.getRootAdapter().as<org::imm::ImmDocument>());
    }
};

int main() {
    DebugTarget dt;
    dt.run_thing();
}
