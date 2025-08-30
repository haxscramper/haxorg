#include "src/model/QtOrgAstModel.hpp"
#include <QTest>
#include <src/model/HistoryManager.hpp>
#include <src/utils/common.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "test.history"


class DebugTarget : public QObject {
  public:
    void run_thing() {}
};

int main() {
    DebugTarget dt;
    dt.run_thing();
}
